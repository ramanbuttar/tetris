#pragma once	// include this file only once
#include "Shape.h"

class Shape_O:
	public Shape {
public:
	Shape_O(Grid* grid, int pos_x, int pos_y);
	virtual ~Shape_O();
	void moveLeft(Grid* grid);
	void moveRight(Grid* grid);
	void moveDown(Grid* grid);
	void rotate(Grid* grid);
	bool isFalling();
	bool isNull();
	void switchGrid(Grid* grid);
};
