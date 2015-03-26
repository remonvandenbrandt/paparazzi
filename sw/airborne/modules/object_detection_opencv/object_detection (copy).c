/*
 * Copyright (C) 2015  Lodewijk Sikkel <l.n.c.sikkel@tudelft.nl>
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/**
 * @file modules/object_detection/object_detection.c
 * File describing the main thread of the object detection module
 */

#include "object_detection.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lib/v4l/v4l2.h"

// OpenCV libraries
#include <opencv/cv.h>
#define CV_H

#include <opencv/highgui.h>
//#include <opencv/cvwimage.h>
//#include <opencv/cvaux.h>
#include <opencv/cxcore.h>

 // Threaded computer vision
#include <pthread.h>

// The video device
#ifndef OBJECT_DETECTION_DEVICE
#define OBJECT_DETECTION_DEVICE "/dev/video1"
#endif
// PRINT_CONFIG_VAR(OBJECT_DETECTION_DEVICE);

// The video device size (width, height)
#ifndef OBJECT_DETECTION_DEVICE_SIZE
#define OBJECT_DETECTION_DEVICE_SIZE 1280,720
#endif
#define __SIZE_HELPER(x, y) #x", "#y
#define _SIZE_HELPER(x) __SIZE_HELPER(x)
// PRINT_CONFIG_MSG("OBJECT_DETECTION_DEVICE_SIZE = " _SIZE_HELPER(OBJECT_DETECTION_DEVICE_SIZE));

// The video device buffers (the amount of V4L2 buffers)
#ifndef OBJECT_DETECTION_DEVICE_BUFFERS
#define OBJECT_DETECTION_DEVICE_BUFFERS 10
#endif
// PRINT_CONFIG_VAR(OBJECT_DETECTION_DEVICE_BUFFERS);

// The place where the shots are saved (without slash on the end)
#ifndef OBJECT_DETECTION_SHOT_PATH
//#define OBJECT_DETECTION_SHOT_PATH "/data/video/usb0"
#define OBJECT_DETECTION_SHOT_PATH "/data/video/raw"
#endif
// PRINT_CONFIG_VAR(VIEWVIDEO_SHOT_PATH);

CvCapture *capture; 
IplImage *yuv, *rgb, *gray, *threshold, *hsv, *channel0;

char filename[128];
uint8_t counter;
CvSeq* contours = 0;
CvSeq* approx = 0;

struct v4l2_device *dev; // --> the video device

static void *object_detection_thread(void *data);
static void *object_detection_thread(void *data __attribute__((unused))) {
  printf("[object_detection-thread] Start object detection thread\n");

  // Start the streaming of the V4L2 device
  if (!v4l2_start_capture(dev)) {
    printf("[object_detection-thread] Could not start capture of %s.\n", dev->name);
    return 0;
  }

  while(TRUE) {
    // Wait for a new frame (blocking)
    v4l2_image_get_opencv(dev, yuv);
    CvMemStorage* storage = cvCreateMemStorage(0);

    // Convert the color space
    cvCvtColor(yuv, rgb, CV_YUV2RGB_Y422);
    cvCvtColor(rgb,hsv,CV_BGR2HSV);


    int ch[] = { 2,0,};
    cvMixChannels(&hsv,1,&channel0,1,ch,1);
    cvThreshold(channel0,threshold,200,255,0);

    cvFindContours( threshold, storage, &contours, sizeof(CvContour),CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );
    CvRect r;
    CvSeq* result;
    static CvScalar colors = { 0,0,255};
	while(contours)
	{
		//obtain a sequence of points of contour, pointed by the variable 'contour'
		result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);
		r = cvBoundingRect( result,1 );

		if (r.height*r.width > 10000 && ((r.height)/(r.width)) > 1.3) {
			printf("x-%d y-%d h-%d w-%d\n",r.x,r.y,r.height,r.width );

			//cvRectangle( rgb, cvPoint( r.x, r.y ), cvPoint( r.x + r.width, r.y + r.height),colors,1,CV_AA,0);
		}

		contours = contours->h_next;
	}






    //CvSeq* contours = 0;
    //CvMemStorage* storage = cvCreateMemStorage(0);

    // Convert the color space
    //cvCvtColor(yuv, rgb, CV_YUV2RGB_Y422);
    //cvCvtColor(rgb, gray, CV_RGB2GRAY);

    //cvThreshold(gray,threshold,200,255,0);
    //cvFindContours(threshold, storage, &contours, sizeof(CvContour),CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

    //contours = cvApproxPoly( contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, 3, 1 );
    //if( contours ){
    //for( CvSeq* c=first_contour; c!=NULL; c=c->h_next ){
	//printf(contours->);
	//printf("%d",cvBoundingRect(contours,1).height);
//	cvBoundingRect(c);
	//cvDrawContours(gray,contours,cvScalarAll(255),cvScalarAll(255),10,cvLine(4) );
    //}




    //int from_to[] = { 1,0};
    //cvMixChannels(hsv,1,channel,2,from_to,1);


    // Store the image /* TODO: Put this function in the run() function
//    printf("[object_detection-thread] trying to save image\n");
   // sprintf(filename, "%s/image_%03d.jpg", OBJECT_DETECTION_SHOT_PATH, counter);
    //cvSaveImage((const char *)filename, threshold, 0);
    //counter++;

    // Free the image 
    v4l2_image_free_opencv(dev, yuv);
    cvReleaseMemStorage(&storage);
    cvReleaseImage(&img);
  }
  return 0;
}

void object_detection_init(void) {

    yuv = cvCreateImageHeader(cvSize(1280, 720), IPL_DEPTH_8U, 2);
    rgb = cvCreateImage(cvSize(1280, 720), IPL_DEPTH_8U, 3);
    hsv = cvCreateImage(cvSize(1280, 720), IPL_DEPTH_8U, 3);
 // gray = cvCreateImage(cvSize(1280, 720), IPL_DEPTH_8U, 1);

    channel0 = cvCreateImage(cvSize(1280, 720), IPL_DEPTH_8U, 1);
    threshold = cvCreateImage(cvSize(1280, 720), IPL_DEPTH_8U, 1);

  counter = 0;

  // Initialize the V4L2 device
  dev = v4l2_init(OBJECT_DETECTION_DEVICE, OBJECT_DETECTION_DEVICE_SIZE, OBJECT_DETECTION_DEVICE_BUFFERS);
  if (dev == NULL) {
    printf("[viewvideo] Could not initialize the %s V4L2 device.\n", OBJECT_DETECTION_DEVICE);
    return;
  }
}

void object_detection_start(void) {
  // Start the streaming thread
  pthread_t tid;
  if (pthread_create(&tid, NULL, object_detection_thread, NULL) != 0) {
    printf("[object_detection] Could not create capturing thread.\n");
    return;
  }
}

void object_detection_stop(void) {
  // Stop the capturing
  if (!v4l2_stop_capture(dev)) {
    printf("[viewvideo] Could not stop capture of %s.\n", dev->name);
    return;
  }
}

void object_detection_run(void) {

}


