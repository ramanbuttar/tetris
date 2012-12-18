#include "global.h"
#include "Shape_Z.h"

Shape_Z::Shape_Z(Grid* grid, int pos_x, int pos_y)
{
	this->x  = pos_x;
	this->y  = pos_y;
	this->falling = true;
	this->null = false;
	this->state = (State)(rand() % 2);
	switchGrid(grid);
}

Shape_Z::~Shape_Z(void)
{
	// no op
}

void Shape_Z::moveLeft(Grid* grid) {
	if (falling == true) {
		if (state == NORTH) {
			if ((grid->getValue(x-1, y-1) == EMPTY) && 
				(grid->getValue(x-2, y) == EMPTY) &&
				(grid->getValue(x-2, y+1) == EMPTY) &&
				((x-2) >= 0)) {
					grid->setValue(x, y-1, EMPTY);
					grid->setValue(x, y, EMPTY);
					grid->setValue(x-1, y+1, EMPTY);
					grid->setValue(x-1, y-1, Z);
					grid->setValue(x-2, y, Z);
					grid->setValue(x-2, y+1, Z);
					x--;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x-2, y) == EMPTY) && (grid->getValue(x-1, y+1) == EMPTY) && ((x-2) >= 0)) {
				grid->setValue(x, y, EMPTY);
				grid->setValue(x+1, y+1, EMPTY);
				grid->setValue(x-2, y, Z);
				grid->setValue(x-1, y+1, Z);
				x--;
			}
		}
	}
}

void Shape_Z::moveRight(Grid* grid) {
	if (falling == true) {
		if (state == NORTH) {
			if ((grid->getValue(x+1, y-1) == EMPTY) &&
				(grid->getValue(x+1, y) == EMPTY) &&
				(grid->getValue(x, y+1) == EMPTY) &&
				((x+1) < grid->getGridWidth())) {
					grid->setValue(x, y-1, EMPTY);
					grid->setValue(x-1, y, EMPTY);
					grid->setValue(x-1, y+1, EMPTY);
					grid->setValue(x+1, y-1, Z);
					grid->setValue(x+1, y, Z);
					grid->setValue(x, y+1, Z);
					x++;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x+1, y) == EMPTY) && (grid->getValue(x+2, y+1) == EMPTY) && ((x+2) < grid->getGridWidth())) {
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x+1, y, Z);
				grid->setValue(x+2, y+1, Z);
				x++;
			}
		}
	}
}

void Shape_Z::moveDown(Grid* grid) {
	if (falling == true) {
		if (state == NORTH) {
			if ((grid->getValue(x, y+1) == EMPTY) && (grid->getValue(x-1, y+2) == EMPTY) && (y+2 < grid->getGridHeight())) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x, y+1, Z);
				grid->setValue(x-1, y+2, Z);
				y++;
			} else {
				falling = false;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x-1, y+1) == EMPTY) &&
				(grid->getValue(x, y+2) == EMPTY) &&
				(grid->getValue(x+1, y+2) == EMPTY) &&
				(y+2 < grid->getGridHeight())) {
					grid->setValue(x-1, y, EMPTY);
					grid->setValue(x, y, EMPTY);
					grid->setValue(x+1, y+1, EMPTY);
					grid->setValue(x-1, y+1, Z);
					grid->setValue(x, y+2, Z);
					grid->setValue(x+1, y+2, Z);
					y++;
			} else {
				falling = false;
			}
		}
	}
}

void Shape_Z::rotate(Grid* grid) {
	if (falling == true) {
		if (state == NORTH) {
			if ((grid->getValue(x, y+1) == EMPTY) && 
				(grid->getValue(x+1, y+1) == EMPTY) &&
				((x+1) < grid->getGridWidth())) {
					grid->setValue(x, y-1, EMPTY);
					grid->setValue(x-1, y+1, EMPTY);
					grid->setValue(x, y+1, Z);
					grid->setValue(x+1, y+1, Z);
					state = EAST;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x, y-1) == EMPTY) &&
				(grid->getValue(x-1, y+1) == EMPTY) &&
				((y-1) >= 0)) {
					grid->setValue(x, y+1, EMPTY);
					grid->setValue(x+1, y+1, EMPTY);
					grid->setValue(x, y-1, Z);
					grid->setValue(x-1, y+1, Z);
					state = NORTH;
			}
		}
	}
}

bool Shape_Z::isFalling() {
	return falling;
}

bool Shape_Z::isNull() {
	return null;
}

void Shape_Z::switchGrid(Grid* grid) {
	if (state == NORTH) {
		/*
		*	      [x, y-1]
		*  [x-1, y][x, y]
		* [x-1, y+1]
		*/
		if ((grid->getValue(x, y-1) == EMPTY) && 
			(grid->getValue(x-1, y) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) &&
			(grid->getValue(x-1, y+1) == EMPTY)) {
				grid->setValue(x, y-1, Z);
				grid->setValue(x-1, y, Z);
				grid->setValue(x, y, Z);
				grid->setValue(x-1, y+1, Z);
		} else {
			null = true;
		}
	} else if (state == EAST) {
		/*
		* [x-1, y][x, y]
		*		 [x, y+1][x+1, y+1]
		*/
		if ((grid->getValue(x-1, y) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) && 
			(grid->getValue(x, y+1) == EMPTY) &&
			(grid->getValue(x+1, y+1) == EMPTY)) {
				grid->setValue(x-1, y, Z);
				grid->setValue(x, y, Z);
				grid->setValue(x, y+1, Z);
				grid->setValue(x+1, y+1, Z);
		} else {
			null = true;
		}
	}
}