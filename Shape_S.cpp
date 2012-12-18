#include "global.h"
#include "Shape_S.h"

Shape_S::Shape_S(Grid* grid, int pos_x, int pos_y)
{
	this->x  = pos_x;
	this->y  = pos_y;
	this->falling = true;
	this->null = false;
	this->state = (State)(rand() % 2);
	switchGrid(grid);
}

Shape_S::~Shape_S(void)
{
	// no op
}

void Shape_S::moveLeft(Grid* grid) {
	if (falling == true) {
		if (state == NORTH) {
			if ((grid->getValue(x-1, y-1) == EMPTY) && 
				(grid->getValue(x-1, y) == EMPTY) &&
				(grid->getValue(x, y+1) == EMPTY) &&
				((x-1) >= 0)) {
					grid->setValue(x, y-1, EMPTY);
					grid->setValue(x+1, y, EMPTY);
					grid->setValue(x+1, y+1, EMPTY);
					grid->setValue(x-1, y-1, S);
					grid->setValue(x-1, y, S);
					grid->setValue(x, y+1, S);
					x--;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x-1, y) == EMPTY) && (grid->getValue(x-2, y+1) == EMPTY) && ((x-2) >= 0)) {
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x, y+1, EMPTY);
				grid->setValue(x-1, y, S);
				grid->setValue(x-2, y+1, S);
				x--;
			}
		}
	}
}

void Shape_S::moveRight(Grid* grid) {
	if (falling == true) {
		if (state == NORTH) {
			if ((grid->getValue(x+1, y-1) == EMPTY) &&
				(grid->getValue(x+2, y) == EMPTY) &&
				(grid->getValue(x+2, y+1) == EMPTY) &&
				((x+2) < grid->getGridWidth())) {
					grid->setValue(x, y-1, EMPTY);
					grid->setValue(x, y, EMPTY);
					grid->setValue(x+1, y+1, EMPTY);
					grid->setValue(x+1, y-1, S);
					grid->setValue(x+2, y, S);
					grid->setValue(x+2, y+1, S);
					x++;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x+2, y) == EMPTY) && (grid->getValue(x+1, y+1) == EMPTY) && ((x+2) < grid->getGridWidth())) {
				grid->setValue(x, y, EMPTY);
				grid->setValue(x-1, y+1, EMPTY);
				grid->setValue(x+2, y, S);
				grid->setValue(x+1, y+1, S);
				x++;
			}
		}
	}
}

void Shape_S::moveDown(Grid* grid) {
	if (falling == true) {
		if (state == NORTH) {
			if ((grid->getValue(x, y+1) == EMPTY) && (grid->getValue(x+1, y+2) == EMPTY) && (y+2 < grid->getGridHeight())) {
				grid->setValue(x, y-1, EMPTY);
				grid->setValue(x+1, y, EMPTY);
				grid->setValue(x, y+1, S);
				grid->setValue(x+1, y+2, S);
				y++;
			} else {
				falling = false;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x+1, y+1) == EMPTY) &&
				(grid->getValue(x-1, y+2) == EMPTY) &&
				(grid->getValue(x, y+2) == EMPTY) &&
				(y+2 < grid->getGridHeight())) {
					grid->setValue(x, y, EMPTY);
					grid->setValue(x+1, y, EMPTY);
					grid->setValue(x-1, y+1, EMPTY);
					grid->setValue(x+1, y+1, S);
					grid->setValue(x-1, y+2, S);
					grid->setValue(x, y+2, S);
					y++;
			} else {
				falling = false;
			}
		}
	}
}

void Shape_S::rotate(Grid* grid) {
	if (falling == true) {
		if (state == NORTH) {
			if ((grid->getValue(x, y+1) == EMPTY) && 
				(grid->getValue(x-1, y+1) == EMPTY) &&
				((x-1) >= 0)) {
					grid->setValue(x, y-1, EMPTY);
					grid->setValue(x+1, y+1, EMPTY);
					grid->setValue(x, y+1, S);
					grid->setValue(x-1, y+1, S);
					state = EAST;
			}
		} else if (state == EAST) {
			if ((grid->getValue(x, y-1) == EMPTY) &&
				(grid->getValue(x+1, y+1) == EMPTY) &&
				((y-1) >= 0)) {
					grid->setValue(x, y+1, EMPTY);
					grid->setValue(x-1, y+1, EMPTY);
					grid->setValue(x, y-1, S);
					grid->setValue(x+1, y+1, S);
					state = NORTH;
			}
		}
	}
}

bool Shape_S::isFalling() {
	return falling;
}

bool Shape_S::isNull() {
	return null;
}

void Shape_S::switchGrid(Grid* grid) {
	if (state == NORTH) {
		/*
		* [x, y-1]
		* [x, y][x+1, y]
		*		[x+1, y+1]
		*/
		if ((grid->getValue(x, y-1) == EMPTY) && 
			(grid->getValue(x, y) == EMPTY) && 
			(grid->getValue(x+1, y) == EMPTY) &&
			(grid->getValue(x+1, y+1) == EMPTY)) {
				grid->setValue(x, y-1, S);
				grid->setValue(x, y, S);
				grid->setValue(x+1, y, S);
				grid->setValue(x+1, y+1, S);
		} else {
			null = true;
		}
	} else if (state == EAST) {
		/*
		*			[x, y][x+1, y]
		* [x-1, y+1][x, y+1]
		*/
		if ((grid->getValue(x, y) == EMPTY) && 
			(grid->getValue(x+1, y) == EMPTY) && 
			(grid->getValue(x-1, y+1) == EMPTY) &&
			(grid->getValue(x, y+1) == EMPTY)) {
				grid->setValue(x, y, S);
				grid->setValue(x+1, y, S);
				grid->setValue(x-1, y+1, S);
				grid->setValue(x, y+1, S);
		} else {
			null = true;
		}
	}
}