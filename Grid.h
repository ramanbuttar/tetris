#pragma once	// include this file only once

class Grid {
public:
   Grid();
   Grid(size_t horizontal_size, size_t vertical_size);
   ~Grid();
   void clearGrid();
   void printGrid();
   void drawGridLines();
   void drawGridBorder();
   void drawGridContents();
   int deleteFilledRows();
   void setValue(unsigned int x, unsigned int y, int value);
   int getValue(unsigned int x, unsigned int y);
   void setGridMargins(unsigned int top, unsigned int right, unsigned int bottom, unsigned int left);
   void setGridBlockSize(unsigned int size);
   int getGridWidth();
   int getGridHeight();
   void setGridColor(float r, float g, float b);
private:
   size_t width, height, margin_left, margin_right, margin_top, margin_bottom, block_size;
   unsigned int* matrix;
   float* gridColor;
   void drawBlock(unsigned int x, unsigned int y, float r, float g, float b);
};