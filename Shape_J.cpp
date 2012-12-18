#include "global.h"
#include "Shape_J.h"

Shape_J::Shape_J(Grid* grid, int pos_x, int pos_y)
{
	this->x  = pos_x;
	this->y  = pos_y;
	this->falling = true;
	this->null = false;
	this->state = (State)(rand() % 4);
	switchGrid(grid);
}

Shape_J::~Shape_J(void)
{
}

void Shape_J::moveLeft(Grid* grid) {
	if (falling == true) {
		if (state == SOUTH) {
			if ((grid->getValue(x-1, y-1) == EMPTY) && (grid->getValue(x-1, y) == EMPTY) && (grid->getValue(x-1, y+1) == EMPTY) && ((x-1) >= 0)) {
				grid->setValue(x+1, y-1, EMPTY);
				grid->setValue(x, y, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x-1, y-1, J);
				grid->setValue(x-1, y, J);
				grid->setValue(x-1, y+1, J);
				x--;
			}
		} else  if (state == NORTH) {
			if ((grid->getValue(x-1, y-1) == EMPTY) && (grid->getValue(x-1, y) == EMPTY) && (grid->getValue(x-2, y+1) == EMPTY) && ((x-2) >= 0)) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x, y, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x-1, y-1, J);
				grid->setValue(x-1, y, J);
				grid->setValue(x-2, y+1, J);
				x--;
			}
		} else  if (state == EAST) {
			if ((grid->getValue(x-2, y-1) == EMPTY) && (grid->getValue(x-2, y) == EMPTY) && ((x-2) >= 0)) {
				grid->setValue(x-1, y-1, EMPTY);
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x-2, y-1, J);
				grid->setValue(x-2, y, J);
				x--;
			}
		} else  if (state == WEST) {
			if ((grid->getValue(x-2, y) == EMPTY) && (grid->getValue(x, y+1) == EMPTY) && ((x-2) >= 0)) {
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x+1, y+1, EMPTY);
				grid->setValue(x-2, y, J);
				grid->setValue(x, y+1, J);
				x--;
			}
		}
	}
}

void Shape_J::moveRight(Grid* grid) {
	if (falling == true) {
		if (state == SOUTH) {
			if ((grid->getValue(x+2, y-1) == EMPTY) && (grid->getValue(x+1, y) == EMPTY) && (grid->getValue(x+1, y+1) == EMPTY) && ((x+2) < grid->getGridWidth())) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x, y, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x+2, y-1, J);
				grid->setValue(x+1, y, J);
				grid->setValue(x+1, y+1, J);
				x++;
			}
		} else  if (state == NORTH) {
			if ((grid->getValue(x+1, y-1) == EMPTY) && (grid->getValue(x+1, y) == EMPTY) && (grid->getValue(x+1, y+1) == EMPTY) && ((x+1) < grid->getGridWidth())) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x, y, EMPTY);
				grid->setValue(x-1, y+1, EMPTY);
				grid->setValue(x+1, y-1, J);
				grid->setValue(x+1, y, J);
				grid->setValue(x+1, y+1, J);
				x++;
			}
		} else  if (state == EAST) {
			if ((grid->getValue(x, y-1) == EMPTY) && (grid->getValue(x+2, y) == EMPTY) && ((x+2) < grid->getGridWidth())) {
				grid->setValue(x-1, y-1, EMPTY);
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x, y-1, J);
				grid->setValue(x+2, y, J);
				x++;
			}
		} else  if (state == WEST) {
			if ((grid->getValue(x+2, y) == EMPTY) && (grid->getValue(x+2, y+1) == EMPTY) && ((x+2) < grid->getGridWidth())) {
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x+1, y+1, EMPTY);
				grid->setValue(x+2, y, J);
				grid->setValue(x+2, y+1, J);
				x++;
			}
		}
	}
}

void Shape_J::moveDown(Grid* grid) {
	if (falling == true) {
		if (state == SOUTH) {
			if ((grid->getValue(x+1, y) == EMPTY) && (grid->getValue(x, y+2) == EMPTY) && ((y+2) < grid->getGridHeight())) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x+1, y-1, EMPTY);
				grid->setValue(x+1, y, J);
				grid->setValue(x, y+2, J);
				y++;
			} else {
				falling = false;
			}
		} else if (state == NORTH) {
			if ((grid->getValue(x-1, y+2) == EMPTY) && (grid->getValue(x, y+2) == EMPTY) && ((y+2) < grid->getGridHeight())) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x-1, y+1, EMPTY);
				grid->setValue(x-1, y+2, J);
				grid->setValue(x, y+2, J);
				y++;
			} else {
				falling = false;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x-1, y+1) == EMPTY) && (grid->getValue(x, y+1) == EMPTY) && (grid->getValue(x+1, y+1) == EMPTY) && ((y+1) < grid->getGridHeight())) {
				grid->setValue(x-1, y-1, EMPTY);
				grid->setValue(x, y, EMPTY);
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x-1, y+1, J);
				grid->setValue(x, y+1, J);
				grid->setValue(x+1, y+1, J);
				y++;
			} else {
				falling = false;
			}
		} else if (state == WEST) {
			if ((grid->getValue(x-1, y+1) == EMPTY) && (grid->getValue(x, y+1) == EMPTY) && (grid->getValue(x+1, y+2) == EMPTY) && ((y+2) < grid->getGridHeight())) {
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x, y, EMPTY);
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x-1, y+1, J);
				grid->setValue(x, y+1, J);
				grid->setValue(x+1, y+2, J);
				y++;
			} else {
				falling = false;
			}
		}
	}
}

void Shape_J::rotate(Grid* grid) {
	if (falling == true) {
		if (state == SOUTH) {
			if ((grid->getValue(x-1, y) == EMPTY) && (grid->getValue(x+1, y) == EMPTY) && (grid->getValue(x+1, y+1) == EMPTY) && ((x-1) >= 0)) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x+1, y-1, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x-1, y, J);
				grid->setValue(x+1, y, J);
				grid->setValue(x+1, y+1, J);
				state = WEST;
			}
		} else if (state == NORTH) {
			if ((grid->getValue(x-1, y-1) == EMPTY) && (grid->getValue(x-1, y) == EMPTY) && (grid->getValue(x+1, y) == EMPTY) && ((x+1) < grid->getGridWidth())) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x-1, y+1, EMPTY);
				grid->setValue(x-1, y-1, J);
				grid->setValue(x-1, y, J);
				grid->setValue(x+1, y, J);
				state = EAST;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x, y-1) == EMPTY) && (grid->getValue(x+1, y-1) == EMPTY) && (grid->getValue(x, y+1) == EMPTY) && ((y+1) < grid->getGridHeight())) {
				grid->setValue(x-1, y-1, EMPTY);
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x, y-1, J);
				grid->setValue(x+1, y-1, J);
				grid->setValue(x, y+1, J);
				state = SOUTH;
			}
		} else if (state == WEST) {
			if ((grid->getValue(x, y-1) == EMPTY) && (grid->getValue(x-1, y+1) == EMPTY) && (grid->getValue(x, y+1) == EMPTY) && ((y-1) >= 0)) {
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x+1, y+1, EMPTY);
				grid->setValue(x, y-1, J);
				grid->setValue(x-1, y+1, J);
				grid->setValue(x, y+1, J);
				state = NORTH;
			}
		}
	}
}

bool Shape_J::isFalling() {
	return falling;
}

bool Shape_J::isNull() {
	return null;
}

void Shape_J::switchGrid(Grid* grid) {
	if (state == SOUTH) {
		/*
		* [x, y-1][x+1, y-1]
		* [x, y]
		* [x, y+1]
		*/
		if ((grid->getValue(x, y-1) == EMPTY) && 
			(grid->getValue(x+1, y-1) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) &&
			(grid->getValue(x, y+1) == EMPTY)) {
				grid->setValue(x, y-1, J);
				grid->setValue(x+1, y-1, J);
				grid->setValue(x, y, J);
				grid->setValue(x, y+1, J);
		} else {
			null = true;
		}
	} else if (state == NORTH) {
		/*
		*			 [x, y-1]
		*		      [x, y]
		* [x-1, y+1][x, y+1]
		*/
		if ((grid->getValue(x, y-1) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) && 
			(grid->getValue(x-1, y+1) == EMPTY) &&
			(grid->getValue(x, y+1) == EMPTY)) {
				grid->setValue(x, y-1, J);
				grid->setValue(x, y, J);
				grid->setValue(x-1, y+1, J);
				grid->setValue(x, y+1, J);
		} else {
			null = true;
		}
	} else if (state == EAST) {
		/*
		* [x-1, y-1]
		* [x-1, y][x, y][x+1, y]
		*/
		if ((grid->getValue(x-1, y-1) == EMPTY) && 
			(grid->getValue(x-1, y) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) &&
			(grid->getValue(x+1, y) == EMPTY)) {
				grid->setValue(x-1, y-1, J);
				grid->setValue(x-1, y, J);
				grid->setValue(x, y, J);
				grid->setValue(x+1, y, J);
		} else {
			null = true;
		}
	} else if (state == WEST) {
		/*
		* [x-1, y][x, y][x+1, y]
		*			   [x+1, y+1]
		*/
		if ((grid->getValue(x-1, y) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) && 
			(grid->getValue(x+1, y) == EMPTY) &&
			(grid->getValue(x+1, y+1) == EMPTY)) {
				grid->setValue(x-1, y, J);
				grid->setValue(x, y, J);
				grid->setValue(x+1, y, J);
				grid->setValue(x+1, y+1, J);
		} else {
			null = true;
		}
	}
}