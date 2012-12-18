#include "global.h"
#include "Shape_O.h"

Shape_O::Shape_O(Grid* grid, int x, int y)
{
	this->x  = x;
	this->y  = y;
	this->falling = true;
	this->null = false;
	switchGrid(grid);
}

Shape_O::~Shape_O(void)
{
	// no op
}

void Shape_O::moveLeft(Grid* grid) {
	if (falling == true) {
		if ((grid->getValue(x-1, y) == EMPTY) && (grid->getValue(x-1, y+1) == EMPTY) && ((x-1) >= 0)) {
			grid->setValue(x+1, y, EMPTY);
			grid->setValue(x+1, y+1, EMPTY);
			grid->setValue(x-1, y, O);
			grid->setValue(x-1, y+1, O);
			x--;
		}
	}
}

void Shape_O::moveRight(Grid* grid) {
	if (falling == true) {
		if ((grid->getValue(x+2, y) == EMPTY) && (grid->getValue(x+2, y+1) == EMPTY) && ((x+2) < (grid->getGridWidth()))) {
			grid->setValue(x, y, EMPTY);
			grid->setValue(x, y+1, EMPTY);
			grid->setValue(x+2, y, O);
			grid->setValue(x+2, y+1, O);
			x++;
		}
	}
}

void Shape_O::moveDown(Grid* grid) {
	if (falling == true) {
		if ((grid->getValue(x, y+2) == EMPTY) && (grid->getValue(x+1, y+2) == EMPTY) && (y+2 < grid->getGridHeight())) {
			grid->setValue(x, y, EMPTY);
			grid->setValue(x+1, y, EMPTY);
			grid->setValue(x, y+2, O);
			grid->setValue(x+1, y+2, O);
			y++;
		} else {
			falling = false;
		}
	}
}

void Shape_O::rotate(Grid* grid) {
	// no op
}

bool Shape_O::isFalling() {
	return falling;
}

bool Shape_O::isNull() {
	return null;
}

void Shape_O::switchGrid(Grid* grid) {
	if ((grid->getValue(x, y) == EMPTY) && 
		(grid->getValue(x, y+1) == EMPTY) && 
		(grid->getValue(x+1, y) == EMPTY) &&
		(grid->getValue(x+1, y+1) == EMPTY)) {
			grid->setValue(x, y, O);
			grid->setValue(x, y+1, O);
			grid->setValue(x+1, y, O);
			grid->setValue(x+1, y+1, O);
	} else {
		null = true;
	}
}