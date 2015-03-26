/*
 * Copyright (C) 2015 Lodewijk Sikkel <l.n.c.sikkel@tudelft.nl>
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
 * along with Paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/**
 * @file modules/object_detection/object_detection.h
 * File describing the main thread of the object detection module
 */

#ifndef OBJECT_DETECTION_MODULE_H
#define OBJECT_DETECTION_MODULE_H

#include "std.h"

// Module functions
void object_detection_init(void);
void object_detection_start(void);
void object_detection_stop(void);
void object_detection_run(void);

struct obstacleStruct{
    int x, y, h, w;
};

struct obstacleStruct obstacle;
extern struct obstacleStruct *getObstacle(void);

#endif /* OBJECT_DETECTION_MODULE_H */
