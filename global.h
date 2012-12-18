#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <math.h>
#include <GL/glut.h>			// Header File For The GLu32 Library
//#include <glut.h>

#define VIEW_WIDTH 400
#define VIEW_HEIGHT 800

#define MARGIN_TOP BLOCK_SIZE*3
#define MARGIN_RIGHT BLOCK_SIZE*6
#define MARGIN_BOTTOM BLOCK_SIZE*1
#define MARGIN_LEFT BLOCK_SIZE*2

#define BLOCK_SIZE 25

#define SPEED_NORMAL 250   /* milliseconds */
#define SPEED_FAST 5       /* milliseconds */

#define SHAPE_COUNT 7