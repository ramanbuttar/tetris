// Tetris.cpp : Defines the entry point for the application.

#include "global.h"
#include "Shape_I.h"
#include "Shape_J.h"
#include "Shape_L.h"
#include "Shape_O.h"
#include "Shape_S.h"
#include "Shape_T.h"
#include "Shape_Z.h"
#include "Grid.h"
#include <ctime>

// Used to determine which callback is used for animation
// IDLE takes up more CPU Power but animation is smoother
enum CallbackMode {IDLE, TIMER};
CallbackMode cbMode = IDLE;

// Used to display appropriate messages when game has just
// started, is paused or is over
enum GameMode {START, PLAYING, PAUSE, OVER};
GameMode mode = START;

// Used by IDLE and TIMER callbacks to control the pace
// of animation
unsigned int time1, time2 = 0;
unsigned int score = 0, speed = SPEED_NORMAL;
Shape *current, *next = NULL;
Grid *field, *nextField, *saveField = NULL;

/* Draw provided string at specified x and y positions on the 
   screen
*/
void drawText(unsigned int x, unsigned int y, char* text) {
	glColor3f(1.0, 1.0, 1.0); /* White */
	glRasterPos2i(x, y);
	for (unsigned int i = 0; i < (int)strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		//glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	}
}

/* Draw provided number at specified x and y positions on the 
   screen
   The number can have a maximum of 9 digits
*/
void drawNumber(unsigned int x, unsigned int y, int number) {
	// find out how many digits the number has
	// to determine how much space to allocate in the buffer
	/*
   int temp = number;
	int count = 0;
	while(temp != 0)
	{
	   temp  /= 10;
	   count++;
	}
   */

	// This buffer places a max limit of 9 digits on the number
	char str[10];
	_itoa_s(number, str, 10);
	drawText(x, y, str);
}

/* Returns a random Shape and places it in block 1, 1 of 
   specified grid
*/
Shape* getRandomShape(Grid* grid) {
	Shape* shape = NULL;
	switch((rand() % SHAPE_COUNT) + 1) {
	  case Shape::I:
		  shape = new Shape_I(grid, 1, 1);
		  break;
	  case Shape::J:
		  shape = new Shape_J(grid, 1, 1);
		  break;
	  case Shape::L:
		  shape = new Shape_L(grid, 1, 1);
		  break;
	  case Shape::O:
		  shape = new Shape_O(grid, 1, 1);
		  break;
	  case Shape::S:
		  shape = new Shape_S(grid, 1, 1);
		  break;
	  case Shape::T:
		  shape = new Shape_T(grid, 1, 1);
		  break;
	  case Shape::Z:
		  shape = new Shape_Z(grid, 1, 1);
		  break;
	}
	return shape;
}

/* Gets a new random shape and stops if there is no space
   to put it in the grid
*/
void getNewShape() {
	if (next == NULL) {
      // First time when game starts
		current = getRandomShape(field);
		next = getRandomShape(nextField);
	} else {
		delete current;
		current = next;
		current->switchGrid(field);
		nextField->clearGrid();
		next = getRandomShape(nextField);
	}

	//delete current;
	//current = getRandomShape(field);

	// Check if Game Over
	if (current->isNull()) {
      mode = OVER;
      glutPostRedisplay();
      if (cbMode == IDLE) {
		   glutIdleFunc(NULL);
      } else if (cbMode == TIMER) {
		   glutTimerFunc(speed, NULL, 0);
	   }
   }
}

/* Resets all the grids and variables to their original values */
void resetGame() {
	field->clearGrid();
	nextField->clearGrid();
	saveField->clearGrid();
	delete next;
	next = NULL;
	score = 0;
	speed = SPEED_NORMAL;
	getNewShape();
	mode = START;
}

/* The display callback method for OpenGL */
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	field->drawGridLines();
	//field->drawGridBorder();
	field->drawGridContents();

	drawText((VIEW_WIDTH + MARGIN_LEFT) / 2.5, BLOCK_SIZE*2, "Raman's TETRIS");
	drawText(VIEW_WIDTH + MARGIN_LEFT + BLOCK_SIZE/2, MARGIN_TOP + BLOCK_SIZE, "Score: ");
	drawNumber(VIEW_WIDTH + MARGIN_LEFT + BLOCK_SIZE/2, MARGIN_TOP + BLOCK_SIZE*2, score);

	drawText(VIEW_WIDTH + MARGIN_LEFT + BLOCK_SIZE/2, MARGIN_TOP*3 - BLOCK_SIZE/2, "Next Shape:");
	//nextField->drawGridLines();
	nextField->drawGridBorder();
	nextField->drawGridContents();

	//drawText(VIEW_WIDTH + MARGIN_LEFT + BLOCK_SIZE/2, MARGIN_TOP*6 - BLOCK_SIZE/2, "Saved Shape:");
	//saveField->drawGridLines();
	//saveField->drawGridBorder();
	//saveField->drawGridContents();

	if (mode == START) {
		drawText((VIEW_WIDTH + MARGIN_LEFT) / 2.5, (VIEW_HEIGHT + MARGIN_TOP) / 2, "Press 'p' to play.");
	} else if (mode == PAUSE) {
		drawText((VIEW_WIDTH + MARGIN_LEFT) / 2.25, (VIEW_HEIGHT + MARGIN_TOP) / 2.2, "Game Paused");
		drawText((VIEW_WIDTH + MARGIN_LEFT) / 2.5, (VIEW_HEIGHT + MARGIN_TOP) / 2, "Press 'p' to resume.");
	} else if (mode == OVER) {
		drawText((VIEW_WIDTH + MARGIN_LEFT) / 2.25, (VIEW_HEIGHT + MARGIN_TOP) / 2.2, "Game Over");
		drawText((VIEW_WIDTH + MARGIN_LEFT) / 2.8, (VIEW_HEIGHT + MARGIN_TOP) / 2, "Press 'p' to play again.");
	}

	glFlush();  /* flush any buffered graphics commands */
	glutSwapBuffers();
}

/* The idle callback method for OpenGL */
void idle(void)
{
	time2 = glutGet(GLUT_ELAPSED_TIME) / speed % 10;
	if (time1 != time2) {
		time1 = time2;
		if (mode == PLAYING) {
			if (current->isFalling()) {
				current->moveDown(field);
			} else {
				score += field->deleteFilledRows();
				getNewShape();
			}
		}
	}
	glutPostRedisplay();
}

/* The timer callback method for OpenGL */
void timer(int par)
{
	if (mode == PLAYING) {
		time2++;
		if (current->isFalling()) {
			current->moveDown(field);
		} else {
			score += field->deleteFilledRows();
			getNewShape();
		}

		glutTimerFunc(speed, timer, 0);
	}
	glutPostRedisplay();
}

/* The keys callback method for OpenGL */
void Keys(unsigned char key, int x, int y) {
	if (key == 'q' || key == 'Q') { 
      // quit
		exit(0); 
	} else if (key == 'r' || key == 'R') { 
      // reset game
		if (mode == PLAYING) {
			resetGame();
			mode = PLAYING;
		}
	} else if (key == 'p' || key == 'P') { 
      // start/pause/resume game
		if (mode == OVER) {
			resetGame();
		} else if ((mode == PAUSE) || (mode == START)) {
			mode = PLAYING;
			if (cbMode == IDLE) {
				glutIdleFunc(idle);
			} else if (cbMode == TIMER) {
				glutTimerFunc(speed, timer, 0);
			}
		} else if (mode == PLAYING) {
         mode = PAUSE;
			speed = SPEED_NORMAL;
			if (cbMode == IDLE) {
				glutPostRedisplay();
				glutIdleFunc(NULL);
			}
		}
	}
}

/* The special keys (pressed) callback method for OpenGL */
void Special_Keys_Down(int key, int x, int y) {
	if (mode == PLAYING) {
		switch(key) {
		 case GLUT_KEY_LEFT:
			 current->moveLeft(field);
			 break;
		 case GLUT_KEY_RIGHT:
			 current->moveRight(field);
			 break;
		 case GLUT_KEY_UP:
			 current->rotate(field);
			 break;
		 case GLUT_KEY_DOWN:
			 /*
          while (current->isFalling()) {
				 current->moveDown(field);
			 }
			 score += field->deleteFilledRows();
			 getNewShape();
          */
			 speed = SPEED_FAST;
			 break;
		}
	}
}

/* The special keys (released) callback method for OpenGL */
void Special_Keys_Up(int key, int x, int y) {
	if (mode == PLAYING) {
		switch(key) {
		 case GLUT_KEY_DOWN:
			 speed = SPEED_NORMAL;
		}
	}
}

/* Initialization method */
void init() {
	glViewport(0, 0, VIEW_WIDTH + MARGIN_LEFT + MARGIN_RIGHT, VIEW_HEIGHT + MARGIN_TOP + MARGIN_BOTTOM);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, VIEW_WIDTH + MARGIN_LEFT + MARGIN_RIGHT, VIEW_HEIGHT + MARGIN_TOP + MARGIN_BOTTOM, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
   
   // Seed Random
	srand((unsigned)time(0));

	field = new Grid(VIEW_WIDTH/BLOCK_SIZE, VIEW_HEIGHT/BLOCK_SIZE);
	field->setGridMargins(MARGIN_TOP, MARGIN_RIGHT, MARGIN_BOTTOM, MARGIN_LEFT);
	field->setGridBlockSize(BLOCK_SIZE);

	nextField = new Grid(4, 4);
	nextField->setGridMargins(MARGIN_TOP*3, MARGIN_RIGHT, MARGIN_BOTTOM, VIEW_WIDTH + MARGIN_LEFT + BLOCK_SIZE/2);
	nextField->setGridBlockSize(BLOCK_SIZE);
	nextField->setGridColor(1.0, 1.0, 1.0);

	saveField = new Grid(4, 4);
	saveField->setGridMargins(MARGIN_TOP*6, MARGIN_RIGHT, MARGIN_BOTTOM, VIEW_WIDTH + MARGIN_LEFT + BLOCK_SIZE/2);
	saveField->setGridBlockSize(BLOCK_SIZE);
	saveField->setGridColor(1.0, 1.0, 1.0);

	getNewShape();
}

/* Main method */
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(VIEW_WIDTH + MARGIN_LEFT + MARGIN_RIGHT, VIEW_HEIGHT + MARGIN_TOP + MARGIN_BOTTOM);
	glutCreateWindow("Tetris");

	init();

	glutKeyboardFunc(Keys);
	glutSpecialFunc(Special_Keys_Down);
	glutSpecialUpFunc(Special_Keys_Up);
	glutIgnoreKeyRepeat(false);
	//glutReshapeFunc(Reshape);
	glutDisplayFunc(display);

	if (cbMode == IDLE) {
		glutIdleFunc(NULL);
	} else if (cbMode == TIMER) {
		glutTimerFunc(speed, NULL, 0);
	}

	glutMainLoop();
}