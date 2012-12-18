#include "global.h"
#include "Shape_T.h"

Shape_T::Shape_T(Grid* grid, int pos_x, int pos_y)
{
	this->x  = pos_x;
	this->y  = pos_y;
	this->falling = true;
	this->null = false;
	this->state = (State)(rand() % 4);
	switchGrid(grid);
}

Shape_T::~Shape_T(void)
{
}

void Shape_T::moveLeft(Grid* grid) {
	if (falling == true) {
		if (state == SOUTH) {
			if ((grid->getValue(x-2, y) == EMPTY) && (grid->getValue(x-1, y+1) == EMPTY) && ((x-2) >= 0)) {
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x-2, y, T);
				grid->setValue(x-1, y+1, T);
				x--;
			}
		} else  if (state == NORTH) {
			if ((grid->getValue(x-2, y) == EMPTY) && (grid->getValue(x-1, y-1) == EMPTY) && ((x-2) >= 0)) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x-1, y-1, T);
				grid->setValue(x-2, y, T);
				x--;
			}
		} else  if (state == EAST) {
			if ((grid->getValue(x-1, y-1) == EMPTY) && (grid->getValue(x-1, y) == EMPTY) && (grid->getValue(x-1, y+1) == EMPTY) && ((x-1) >= 0)) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x-1, y-1, T);
				grid->setValue(x-1, y, T);
				grid->setValue(x-1, y+1, T);
				x--;
			}
		} else  if (state == WEST) {
			if ((grid->getValue(x-1, y-1) == EMPTY) && (grid->getValue(x-2, y) == EMPTY) && (grid->getValue(x-1, y+1) == EMPTY) && ((x-2) >= 0)) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x, y, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x-1, y-1, T);
				grid->setValue(x-2, y, T);
				grid->setValue(x-1, y+1, T);
				x--;
			}
		}
	}
}

void Shape_T::moveRight(Grid* grid) {
	if (falling == true) {
		if (state == SOUTH) {
			if ((grid->getValue(x+2, y) == EMPTY) && (grid->getValue(x+1, y+1) == EMPTY) && ((x+2) < grid->getGridWidth())) {
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x+2, y, T);
				grid->setValue(x+1, y+1, T);
				x++;
			}
		} else  if (state == NORTH) {
			if ((grid->getValue(x+2, y) == EMPTY) && (grid->getValue(x+1, y-1) == EMPTY) && ((x+2) < grid->getGridWidth())) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x+1, y-1, T);
				grid->setValue(x+2, y, T);
				x++;
			}
		} else  if (state == EAST) {
			if ((grid->getValue(x+1, y-1) == EMPTY) && (grid->getValue(x+2, y) == EMPTY) && (grid->getValue(x+1, y+1) == EMPTY) && ((x+2) < grid->getGridWidth())) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x, y, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x+1, y-1, T);
				grid->setValue(x+2, y, T);
				grid->setValue(x+1, y+1, T);
				x++;
			}
		} else  if (state == WEST) {
			if ((grid->getValue(x+1, y-1) == EMPTY) && (grid->getValue(x+1, y) == EMPTY) && (grid->getValue(x+1, y+1) == EMPTY) && ((x+1) < grid->getGridWidth())) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x+1, y-1, T);
				grid->setValue(x+1, y, T);
				grid->setValue(x+1, y+1, T);
				x++;
			}
		}
	}
}

void Shape_T::moveDown(Grid* grid) {
	if (falling == true) {
		if (state == SOUTH) {
			if ((grid->getValue(x-1, y+1) == EMPTY) && (grid->getValue(x, y+2) == EMPTY) && (grid->getValue(x+1, y+1) == EMPTY) && ((y+2) < grid->getGridHeight())) {
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x, y, EMPTY);
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x-1, y+1, T);
				grid->setValue(x, y+1, T);
				grid->setValue(x+1, y+1, T);
				grid->setValue(x, y+2, T);
				y++;
			} else {
				falling = false;
			}
		} else if (state == NORTH) {
			if ((grid->getValue(x-1, y+1) == EMPTY) && (grid->getValue(x, y+1) == EMPTY) && (grid->getValue(x+1, y+1) == EMPTY) && ((y+1) < grid->getGridHeight())) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x-1, y+1, T);
				grid->setValue(x, y+1, T);
				grid->setValue(x+1, y+1, T);
				y++;
			} else {
				falling = false;
			}
		} else if (state == EAST) {

			if ((grid->getValue(x, y+2) == EMPTY) && (grid->getValue(x+1, y+1) == EMPTY) && ((y+2) < grid->getGridHeight())) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x+1, y, EMPTY);     
				grid->setValue(x+1, y+1, T);
				grid->setValue(x, y+2, T);
				y++;
			} else {
				falling = false;
			}
		} else if (state == WEST) {
			if ((grid->getValue(x, y+2) == EMPTY) && (grid->getValue(x-1, y+1) == EMPTY) && ((y+2) < grid->getGridHeight())) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x-1, y+1, T);
				grid->setValue(x, y+2, T);
				y++;
			} else {
				falling = false;
			}
		}
	}
}

void Shape_T::rotate(Grid* grid) {
	if (falling == true) {
		if (state == SOUTH) {
			if ((grid->getValue(x, y-1) == EMPTY) && ((y-1) >= 0)) {
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x, y-1, T);
				state = WEST;
			}
		} else if (state == NORTH) {
			if ((grid->getValue(x, y+1) == EMPTY) && ((y+1) < grid->getGridHeight())) {
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x, y+1, T);
				state = EAST;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x-1, y) == EMPTY) && ((x-1) >= 0)) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x-1, y, T);
				state = SOUTH;
			}
		} else if (state == WEST) {
			if ((grid->getValue(x+1, y) == EMPTY) && ((x+1) < grid->getGridWidth())) {
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x+1, y, T);
				state = NORTH;
			}
		}
	}
}

bool Shape_T::isFalling() {
	return falling;
}

bool Shape_T::isNull() {
	return null;
}

void Shape_T::switchGrid(Grid* grid) {
	if (state == SOUTH) {
		/*
		* [x-1, y][x, y][x+1, y]
		*        [x, y+1]
		*/
		/*if ((x-1) < 0) {
		this->x = 1;
		} else if ((x+1) >= grid->getGridWidth()) {
		this->x = grid->getGridWidth() - 1;
		}
		if (y < 0) {
		this->y = 0;
		} else if ((y+1) >= grid->getGridHeight()) {
		this->y = grid->getGridHeight() - 1;
		}*/
		if ((grid->getValue(x-1, y) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) && 
			(grid->getValue(x+1, y) == EMPTY) &&
			(grid->getValue(x, y+1) == EMPTY)) {
				grid->setValue(x-1, y, T);
				grid->setValue(x, y, T);
				grid->setValue(x+1, y, T);
				grid->setValue(x, y+1, T);
		} else {
			null = true;
		}
	} else if (state == NORTH) {
		/*
		*        [x, y-1]
		* [x-1, y][x, y][x+1, y]
		*/
		if ((grid->getValue(x, y-1) == EMPTY) && 
			(grid->getValue(x-1, y) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) &&
			(grid->getValue(x+1, y) == EMPTY)) {
				grid->setValue(x, y-1, T);
				grid->setValue(x-1, y, T);
				grid->setValue(x, y, T);
				grid->setValue(x+1, y, T);
		} else {
			null = true;
		}
	} else if (state == EAST) {
		/*
		* [x, y-1]
		* [x, y][x+1, y]
		* [x, y+1]
		*/
		if ((grid->getValue(x, y-1) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) && 
			(grid->getValue(x+1, y) == EMPTY) &&
			(grid->getValue(x, y+1) == EMPTY)) {
				grid->setValue(x, y-1, T);
				grid->setValue(x, y, T);
				grid->setValue(x+1, y, T);
				grid->setValue(x, y+1, T);
		} else {
			null = true;
		}
	} else if (state == WEST) {
		/*
		*         [x, y-1]
		* [x-1, y][x, y]
		*         [x, y+1]
		*/
		if ((grid->getValue(x, y-1) == EMPTY) && 
			(grid->getValue(x-1, y) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) &&
			(grid->getValue(x, y+1) == EMPTY)) {
				grid->setValue(x, y-1, T);
				grid->setValue(x-1, y, T);
				grid->setValue(x, y, T);
				grid->setValue(x, y+1, T);
		} else {
			null = true;
		}
	}
}