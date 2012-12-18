#include "global.h"
#include "Shape_L.h"

Shape_L::Shape_L(Grid* grid, int pos_x, int pos_y)
{
	this->x  = pos_x;
	this->y  = pos_y;
	this->falling = true;
	this->null = false;
	this->state = (State)(rand() % 4);
	switchGrid(grid);
}

Shape_L::~Shape_L(void)
{
}

void Shape_L::moveLeft(Grid* grid) {
	if (falling == true) {
		if (state == SOUTH) {
			if ((grid->getValue(x-2, y-1) == EMPTY) && (grid->getValue(x-1, y) == EMPTY) && (grid->getValue(x-1, y+1) == EMPTY) && ((x-2) >= 0)) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x, y, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x-2, y-1, L);
				grid->setValue(x-1, y, L);
				grid->setValue(x-1, y+1, L);
				x--;
			}
		} else  if (state == NORTH) {
			if ((grid->getValue(x-1, y-1) == EMPTY) && (grid->getValue(x-1, y) == EMPTY) && (grid->getValue(x-1, y+1) == EMPTY) && ((x-1) >= 0)) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x, y, EMPTY);
				grid->setValue(x+1, y+1, EMPTY);
				grid->setValue(x-1, y-1, L);
				grid->setValue(x-1, y, L);
				grid->setValue(x-1, y+1, L);
				x--;
			}
		} else  if (state == EAST) {
			if ((grid->getValue(x-2, y) == EMPTY) && (grid->getValue(x-2, y+1) == EMPTY) && ((x-2) >= 0)) {
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x-1, y+1, EMPTY);
				grid->setValue(x-2, y, L);
				grid->setValue(x-2, y+1, L);
				x--;
			}
		} else  if (state == WEST) {
			if ((grid->getValue(x, y-1) == EMPTY) && (grid->getValue(x-2, y) == EMPTY) && ((x-2) >= 0)) {
				grid->setValue(x+1, y-1, EMPTY);
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x, y-1, L);
				grid->setValue(x-2, y, L);
				x--;
			}
		}
	}
}

void Shape_L::moveRight(Grid* grid) {
	if (falling == true) {
		if (state == SOUTH) {
			if ((grid->getValue(x+1, y-1) == EMPTY) && (grid->getValue(x+1, y) == EMPTY) && (grid->getValue(x+1, y+1) == EMPTY) && ((x+1) < grid->getGridWidth())) {
				grid->setValue(x-1, y-1, EMPTY);
				grid->setValue(x, y, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x+1, y-1, L);
				grid->setValue(x+1, y, L);
				grid->setValue(x+1, y+1, L);
				x++;
			}
		} else  if (state == NORTH) {
			if ((grid->getValue(x+1, y-1) == EMPTY) && (grid->getValue(x+1, y) == EMPTY) && (grid->getValue(x+2, y+1) == EMPTY) && ((x+2) < grid->getGridWidth())) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x, y, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x+1, y-1, L);
				grid->setValue(x+1, y, L);
				grid->setValue(x+2, y+1, L);
				x++;
			}
		} else  if (state == EAST) {
			if ((grid->getValue(x+2, y) == EMPTY) && (grid->getValue(x, y+1) == EMPTY) && ((x+2) < grid->getGridWidth())) {
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x-1, y+1, EMPTY);
				grid->setValue(x+2, y, L);
				grid->setValue(x, y+1, L);
				x++;
			}
		} else  if (state == WEST) {
			if ((grid->getValue(x+2, y-1) == EMPTY) && (grid->getValue(x+2, y) == EMPTY) && ((x+2) < grid->getGridWidth())) {
				grid->setValue(x+1, y-1, EMPTY);
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x+2, y-1, L);
				grid->setValue(x+2, y, L);
				x++;
			}
		}
	}
}

void Shape_L::moveDown(Grid* grid) {
	if (falling == true) {
		if (state == SOUTH) {
			if ((grid->getValue(x-1, y) == EMPTY) && (grid->getValue(x, y+2) == EMPTY) && ((y+2) < grid->getGridHeight())) {
				grid->setValue(x-1, y-1, EMPTY);
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x-1, y, L);
				grid->setValue(x, y+2, L);
				y++;
			} else {
				falling = false;
			}
		} else if (state == NORTH) {
			if ((grid->getValue(x, y+2) == EMPTY) && (grid->getValue(x+1, y+2) == EMPTY) && ((y+2) < grid->getGridHeight())) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x+1, y+1, EMPTY);
				grid->setValue(x, y+2, L);
				grid->setValue(x+1, y+2, L);
				y++;
			} else {
				falling = false;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x-1, y+2) == EMPTY) && (grid->getValue(x, y+1) == EMPTY) && (grid->getValue(x+1, y+1) == EMPTY) && ((y+2) < grid->getGridHeight())) {
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x, y, EMPTY);
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x, y+1, L);
				grid->setValue(x+1, y+1, L);
				grid->setValue(x-1, y+2, L);
				y++;
			} else {
				falling = false;
			}
		} else if (state == WEST) {
			if ((grid->getValue(x-1, y+1) == EMPTY) && (grid->getValue(x, y+1) == EMPTY) && (grid->getValue(x+1, y+1) == EMPTY) && ((y+1) < grid->getGridHeight())) {
				grid->setValue(x+1, y-1, EMPTY);
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x, y, EMPTY);
				grid->setValue(x-1, y+1, L);
				grid->setValue(x, y+1, L);
				grid->setValue(x+1, y+1, L);
				y++;
			} else {
				falling = false;
			}
		}
	}
}

void Shape_L::rotate(Grid* grid) {
	if (falling == true) {
		if (state == SOUTH) {
			if ((grid->getValue(x-1, y) == EMPTY) && (grid->getValue(x+1, y) == EMPTY) && (grid->getValue(x+1, y-1) == EMPTY) && ((x+1) < grid->getGridWidth())) {
				grid->setValue(x-1, y-1, EMPTY);
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x-1, y, L);
				grid->setValue(x+1, y, L);
				grid->setValue(x+1, y-1, L);
				state = WEST;
			}
		} else if (state == NORTH) {
			if ((grid->getValue(x+1, y) == EMPTY) && (grid->getValue(x-1, y) == EMPTY) && (grid->getValue(x-1, y+1) == EMPTY) && ((x-1) >= 0)) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x+1, y+1, EMPTY);
				grid->setValue(x+1, y, L);
				grid->setValue(x-1, y, L);
				grid->setValue(x-1, y+1, L);
				state = EAST;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x-1, y-1) == EMPTY) && (grid->getValue(x, y-1) == EMPTY) && (grid->getValue(x, y+1) == EMPTY) && ((y-1) >= 0)) {
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x-1, y+1, EMPTY);
				grid->setValue(x-1, y-1, L);
				grid->setValue(x, y-1, L);
				grid->setValue(x, y+1, L);
				state = SOUTH;
			}
		} else if (state == WEST) {
			if ((grid->getValue(x, y-1) == EMPTY) && (grid->getValue(x, y+1) == EMPTY) && (grid->getValue(x+1, y+1) == EMPTY) && ((y+1) < grid->getGridHeight())) {
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x+1, y-1, EMPTY);
				grid->setValue(x, y-1, L);
				grid->setValue(x, y+1, L);
				grid->setValue(x+1, y+1, L);
				state = NORTH;
			}
		}
	}
}

bool Shape_L::isFalling() {
	return falling;
}

bool Shape_L::isNull() {
	return null;
}

void Shape_L::switchGrid(Grid* grid) {
	if (state == SOUTH) {
		/*
		* [x-1, y-1][x, y-1]
		*           [x, y]
		*           [x, y+1]
		*/
		if ((grid->getValue(x-1, y-1) == EMPTY) && 
			(grid->getValue(x, y-1) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) &&
			(grid->getValue(x, y+1) == EMPTY)) {
				grid->setValue(x-1, y-1, L);
				grid->setValue(x, y-1, L);
				grid->setValue(x, y, L);
				grid->setValue(x, y+1, L);
		} else {
			null = true;
		}
	} else if (state == NORTH) {
		/*
		* [x, y-1]
		* [x, y]
		* [x, y+1][x+1, y+1]
		*/
		if ((grid->getValue(x, y-1) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) && 
			(grid->getValue(x, y+1) == EMPTY) &&
			(grid->getValue(x+1, y+1) == EMPTY)) {
				grid->setValue(x, y-1, L);
				grid->setValue(x, y, L);
				grid->setValue(x, y+1, L);
				grid->setValue(x+1, y+1, L);
		} else {
			null = true;
		}
	} else if (state == EAST) {
		/*
		* [x-1, y][x, y][x+1, y]
		* [x-1, y+1]
		*/
		if ((grid->getValue(x-1, y) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) && 
			(grid->getValue(x+1, y) == EMPTY) &&
			(grid->getValue(x-1, y+1) == EMPTY)) {
				grid->setValue(x-1, y, L);
				grid->setValue(x, y, L);
				grid->setValue(x+1, y, L);
				grid->setValue(x-1, y+1, L);
		} else {
			null = true;
		}
	} else if (state == WEST) {
		/*
		*              [x+1, y-1]
		* [x-1, y][x, y][x+1, y]
		*/
		if ((grid->getValue(x+1, y-1) == EMPTY) && 
			(grid->getValue(x-1, y) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) &&
			(grid->getValue(x+1, y) == EMPTY)) {
				grid->setValue(x+1, y-1, L);
				grid->setValue(x-1, y, L);
				grid->setValue(x, y, L);
				grid->setValue(x+1, y, L);
		} else {
			null = true;
		}
	}
}