/*
 * Copyright (C) 2015 Freek van Tienen <freek.v.tienen@gmail.com>
 *
 * This file is part of Paparazzi.
 *
 * Paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * Paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * @file modules/computer_vision/lib/vision/image.h
 * Image helper functions like resizing, color filter, converters...
 */

#ifndef _CV_LIB_VISION_IMAGE_H
#define _CV_LIB_VISION_IMAGE_H

#include "std.h"
#include <sys/time.h>

/* The different type of images we currently support */
enum image_type {
  IMAGE_YUV422,     //< UYVY format (uint16 per pixel)
  IMAGE_GRAYSCALE,  //< Grayscale image with only the Y part (uint8 per pixel)
  IMAGE_JPEG,       //< An JPEG encoded image (not per pixel encoded)
  IMAGE_GRADIENT    //< An image gradient (int16 per pixel)
};

/* Main image structure */
struct image_t {
  enum image_type type;   //< The image type
  uint16_t w;             //< Image width
  uint16_t h;             //< Image height
  struct timeval ts;      //< The timestamp of creation

  uint8_t buf_idx;        //< Buffer index for V4L2 freeing
  uint32_t buf_size;      //< The buffer size
  void *buf;              //< Image buffer (depending on the image_type)
};

/* Image point structure */
struct point_t {
  uint16_t x;             //< The x coordinate of the point
  uint16_t y;             //< The y coordinate of the point
};

/* Usefull image functions */
void image_create(struct image_t *img, uint16_t width, uint16_t height, enum image_type type);
void image_free(struct image_t *img);
void image_copy(struct image_t *input, struct image_t *output);
void image_to_grayscale(struct image_t *input, struct image_t *output);
uint32_t image_yuv422_colorfilt(struct image_t *input, struct image_t *output, uint32_t *bins, uint16_t bins_cnt,
  uint8_t y_m, uint8_t y_M, uint8_t u_m, uint8_t u_M, uint8_t v_m, uint8_t v_M);
void image_yuv422_downsample(struct image_t *input, struct image_t *output, uint16_t downsample);
void image_subpixel_window(struct image_t *input, struct image_t *output, struct point_t *center, uint16_t subpixel_factor);
void image_gradients(struct image_t *input, struct image_t *dx, struct image_t *dy);
void image_calculate_g(struct image_t *dx, struct image_t *dy, int32_t *g);
uint32_t image_difference(struct image_t *img_a, struct image_t *img_b, struct image_t *diff);
int32_t image_multiply(struct image_t *img_a, struct image_t *img_b, struct image_t *mult);
void image_show_points(struct image_t *img, struct point_t *points, uint16_t points_cnt);
void image_show_flow(struct image_t *img, struct point_t *points, struct point_t *new_points, uint16_t points_cnt, bool_t *status_points);
void image_draw_line(struct image_t *img, struct point_t *from, struct point_t *to);
void get_integral_image( struct image_t* img, uint32_t* int_img, uint16_t px_start , uint16_t img_h);
int median (struct image_t* img, uint16_t px_start, uint16_t img_h);
uint8_t get_obs_response(uint32_t *integral_image, uint16_t width, uint16_t x, uint16_t y, uint16_t feature_size, uint32_t px_inner, uint8_t median_val);

#endif
