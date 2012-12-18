#pragma once	// include this file only once
#include "Grid.h"

class Shape {
public:
   // First value must be EMPTY
   enum ShapeType {EMPTY, I, J, L, O, S, T, Z};
   Shape();
   virtual ~Shape();
   virtual void moveLeft(Grid* grid){};
   virtual void moveRight(Grid* grid){};
   virtual void moveDown(Grid* grid){};
   virtual void rotate(Grid* grid){};
   virtual bool isFalling(){return false;};
   virtual bool isNull(){return false;};
   virtual void switchGrid(Grid* grid){};
protected:
   int x, y;
   bool falling, null;
   // First two values must contain NORTH and EAST (order could be swapped though)
   enum State {NORTH, EAST, SOUTH, WEST};
   State state;
};