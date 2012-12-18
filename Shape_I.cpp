#include "global.h"
#include "Shape_I.h"

Shape_I::Shape_I(Grid* grid, int pos_x, int pos_y)
{
	this->x  = pos_x;
	this->y  = pos_y;
	this->falling = true;
	this->null = false;
	this->state = (State)(rand() % 2);
	switchGrid(grid);
}

Shape_I::~Shape_I(void)
{
	// no op
}

void Shape_I::moveLeft(Grid* grid) {
	if (falling == true) {
		if (state == NORTH) {
			if ((grid->getValue(x-1, y-1) == EMPTY) && 
				(grid->getValue(x-1, y) == EMPTY) &&
				(grid->getValue(x-1, y+1) == EMPTY) &&
				(grid->getValue(x-1, y+2) == EMPTY) &&
				((x-1) >= 0)) {
					grid->setValue(x, y-1, EMPTY);
					grid->setValue(x, y, EMPTY);
					grid->setValue(x, y+1, EMPTY);
					grid->setValue(x, y+2, EMPTY);
					grid->setValue(x-1, y-1, I);
					grid->setValue(x-1, y, I);
					grid->setValue(x-1, y+1, I);
					grid->setValue(x-1, y+2, I);
					x--;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x-2, y) == EMPTY) && ((x-2) >= 0)) {
				grid->setValue(x+2, y, EMPTY);
				grid->setValue(x-2, y, I);
				x--;
			}
		}
	}
}

void Shape_I::moveRight(Grid* grid) {
	if (falling == true) {
		if (state == NORTH) {
			if ((grid->getValue(x+1, y-1) == EMPTY) &&
				(grid->getValue(x+1, y) == EMPTY) &&
				(grid->getValue(x+1, y+1) == EMPTY) &&
				(grid->getValue(x+1, y+2) == EMPTY) &&
				((x+1) < grid->getGridWidth())) {
					grid->setValue(x, y-1, EMPTY);
					grid->setValue(x, y, EMPTY);
					grid->setValue(x, y+1, EMPTY);
					grid->setValue(x, y+2, EMPTY);
					grid->setValue(x+1, y-1, I);
					grid->setValue(x+1, y, I);
					grid->setValue(x+1, y+1, I);
					grid->setValue(x+1, y+2, I);
					x++;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x+3, y) == EMPTY) && ((x+3) < grid->getGridWidth())) {
				grid->setValue(x-1, y, EMPTY);
				grid->setValue(x+3, y, I);
				x++;
			}
		}
	}
}

void Shape_I::moveDown(Grid* grid) {
	if (falling == true) {
		if (state == NORTH) {
			if ((grid->getValue(x, y+3) == EMPTY) && (y+3 < grid->getGridHeight())) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x, y+3, I);
				y++;
			} else {
				falling = false;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x-1, y+1) == EMPTY) &&
				(grid->getValue(x, y+1) == EMPTY) &&
				(grid->getValue(x+1, y+1) == EMPTY) &&
				(grid->getValue(x+2, y+1) == EMPTY) &&
				(y+1 < grid->getGridHeight())) {
					grid->setValue(x-1, y, EMPTY);
					grid->setValue(x, y, EMPTY);
					grid->setValue(x+1, y, EMPTY);
					grid->setValue(x+2, y, EMPTY);
					grid->setValue(x-1, y+1, I);
					grid->setValue(x, y+1, I);
					grid->setValue(x+1, y+1, I);
					grid->setValue(x+2, y+1, I);
					y++;
			} else {
				falling = false;
			}
		}
	}
}

void Shape_I::rotate(Grid* grid) {
	if (falling == true) {
		if (state == NORTH) {
			if ((grid->getValue(x-1, y) == EMPTY) && 
				(grid->getValue(x+1, y) == EMPTY) &&
				(grid->getValue(x+2, y) == EMPTY) &&
				((x-1) >= 0) && ((x+2) < grid->getGridWidth())) {
					grid->setValue(x, y-1, EMPTY);
					grid->setValue(x, y+1, EMPTY);
					grid->setValue(x, y+2, EMPTY);
					grid->setValue(x-1, y, I);
					grid->setValue(x+1, y, I);
					grid->setValue(x+2, y, I);
					state = EAST;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x, y-1) == EMPTY) &&
				(grid->getValue(x, y+1) == EMPTY) &&
				(grid->getValue(x, y+2) == EMPTY) &&
				((y-1) >= 0) && ((y+2) < grid->getGridHeight())) {
					grid->setValue(x-1, y, EMPTY);
					grid->setValue(x+1, y, EMPTY);
					grid->setValue(x+2, y, EMPTY);
					grid->setValue(x, y-1, I);
					grid->setValue(x, y+1, I);
					grid->setValue(x, y+2, I);
					state = NORTH;
			}
		}
	}
}

bool Shape_I::isFalling() {
	return falling;
}

bool Shape_I::isNull() {
	return null;
}

void Shape_I::switchGrid(Grid* grid) {
	if (state == NORTH) {
		/*
		* [x, y-1]
		* [x, y]
		* [x, y+1]
		* [x, y+2]
		*/
		if ((grid->getValue(x, y-1) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) && 
			(grid->getValue(x, y+1) == EMPTY) &&
			(grid->getValue(x, y+2) == EMPTY)) {
				grid->setValue(x, y-1, I);
				grid->setValue(x, y, I);
				grid->setValue(x, y+1, I);
				grid->setValue(x, y+2, I);
		} else {
			null = true;
		}
	} else if (state == EAST) {
		/*
		* [x-1, y][x, y][x+1, y][x+2, y]
		*/
		if ((grid->getValue(x-1, y) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) && 
			(grid->getValue(x+1, y) == EMPTY) &&
			(grid->getValue(x+2, y) == EMPTY)) {
				grid->setValue(x-1, y, I);
				grid->setValue(x, y, I);
				grid->setValue(x+1, y, I);
				grid->setValue(x+2, y, I);
		} else {
			null = true;
		}
	}	
}