#pragma once	// include this file only once
#include "Shape.h"

class Shape_T:
	public Shape {
public:
	Shape_T(Grid* grid, int pos_x, int pos_y);
	virtual ~Shape_T();
	void moveLeft(Grid* grid);
	void moveRight(Grid* grid);
	void moveDown(Grid* grid);
	void rotate(Grid* grid);
	bool isFalling();
	bool isNull();
	void switchGrid(Grid* grid);
};
