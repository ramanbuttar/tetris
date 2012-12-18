#include "global.h"
#include "Grid.h"
#include "Shape.h"

/* Default constructor */
Grid::Grid(void)
{
}

/* Creates a grid with specified horizontal and vertical size */
Grid::Grid(size_t horizontal_size, size_t vertical_size) {
   this->width = horizontal_size;
   this->height = vertical_size;
   this->matrix = new unsigned int[width*height];
   this->gridColor = new float[3];
   // Default values
   setGridMargins(0, 0, 0, 0);
   setGridBlockSize(25);
   setGridColor(0.5, 0.5, 0.5); /* Gray */
   clearGrid();
}

/* Default destructor */
Grid::~Grid(void) {
   delete [] matrix;
   delete gridColor;
}

/* Initializes the grid to contain zeros */
void Grid::clearGrid() {
   /*
   for (size_t row(0); row != height; ++row) {
      for (size_t col(0); col != width; ++col) {
      }
   }
   */

   for (unsigned int row=0; row < height; row++) {
      for (unsigned int col=0; col < width; col++) {
         matrix[width*row + col] = 0;
      }
   }
}

/* Prints the values of the grid */
void Grid::printGrid() {
   for (unsigned int row=0; row < height; row++) {
      for (unsigned int col=0; col < width; col++) {
         std::cout << getValue(col, row) << " ";
      }
      std::cout << "\n";
   }
   std::cout << "\n";
}

/* Draws the grid lines on the screen */
void Grid::drawGridLines()
{
	glColor3fv(gridColor); 

   /* Draw Horizontal Lines */
   for (unsigned int row = 0; row <= height; row++) {
      glBegin(GL_LINE_LOOP);
      glVertex2i(margin_left, margin_top + (block_size*row));
      glVertex2i((block_size*width) + margin_left, margin_top + (block_size*row));
      glEnd();
   }

   /* Draw Vertical Lines */
   for (unsigned int col = 0; col <= width; col++) {
      glBegin(GL_LINE_LOOP);
      glVertex2i(margin_left + (block_size*col), margin_top);
      glVertex2i(margin_left + (block_size*col), (block_size*height) + margin_top);
      glEnd();
   }
}

/* Draws the outer border of the grid on the screen */
void Grid::drawGridBorder()
{
	glColor3fv(gridColor); 

   /* Draw Horizontal Lines */
	glBegin(GL_LINE_LOOP);
      glVertex2i(margin_left, margin_top + (block_size*0));
      glVertex2i((block_size*width) + margin_left, margin_top + (block_size*0));
	glEnd();

	glBegin(GL_LINE_LOOP);
      glVertex2i(margin_left, margin_top + (block_size*height));
      glVertex2i((block_size*width) + margin_left, margin_top + (block_size*height));
	glEnd();

   /* Draw Vertical Lines */
	glBegin(GL_LINE_LOOP);
      glVertex2i(margin_left + (block_size*0), margin_top);
      glVertex2i(margin_left + (block_size*0), (block_size*height) + margin_top);
	glEnd();

	glBegin(GL_LINE_LOOP);
      glVertex2i(margin_left + (block_size*width), margin_top);
      glVertex2i(margin_left + (block_size*width), (block_size*height) + margin_top);
	glEnd();
}

/* Draws blocks in the grid on the screen */
void Grid::drawGridContents()
{
	int shape = Shape::EMPTY;
	for (unsigned int row=0; row < height; row++) {
		for (unsigned int col=0; col < width; col++) {
			shape = getValue(col, row);
			switch(shape) {
			case Shape::I:
				// draw in Red
				drawBlock(col, row, 1.0, 0.0, 0.0);
				break;
			case Shape::J:
				// draw in Green
				drawBlock(col, row, 0.0, 1.0, 0.0);
				break;
			case Shape::L:
				// draw in Blue
				drawBlock(col, row, 0.0, 0.0, 1.0);
				break;
			case Shape::O:
				// draw in Yellow
				drawBlock(col, row, 1.0, 1.0, 0.0);
				break;
			case Shape::S:
				// draw in Purple
				drawBlock(col, row, 1.0, 0.0, 1.0);
				break;
			case Shape::T:
				// draw in Aqua
				drawBlock(col, row, 0.0, 1.0, 1.0);
				break;
			case Shape::Z:
				// draw in White
				drawBlock(col, row, 1.0, 1.0, 1.0);
				break;
			}
		}
	}
}

/* Deletes a row if it has been filled completely and shifts down the rows above */
/* Returns the number of rows cleared */
int Grid::deleteFilledRows()
{
   bool filledRow = false;
   int rowsCleared = 0;
   // Start at bottom of the grid since that is more likely to be filled
   for (int row = height-1; row >= 0; row--) {
      filledRow = true;
      for (unsigned int col = 0; col < width; col++) {
         if (getValue(col, row) == Shape::EMPTY) {
            // if any empty block encountered in a row, the row is not filled completely
            filledRow = false;
            break;
         }
      }
      if (filledRow == true) {
         // delete the current filled row
         // copy the row above to the current row
         // reset the row above to be empty
         for (int row2 = row; row2 >= 0; row2--) {
            for (unsigned int col = 0; col < width; col++) {
               if (row2 > 0 ) {
                  setValue(col, row2, getValue(col, row2-1));
               } else if (row2 == 0 ) {
                  setValue(col, row2, 0);
               }
            }
         }
         // increment row to examine the current row again
         row++;
         // increment counter to keep track of how many rows cleared
         rowsCleared++;
      }
   }
   return rowsCleared;
}

/* Sets provided grid location x, y to be given integer value */
void Grid::setValue(unsigned int x, unsigned int y, int value)
{
   matrix[width*y + x] = value;
}

/* Gets the grid block's value at specified location x, y */
int Grid::getValue(unsigned int x, unsigned int y)
{
   return matrix[width*y + x];
}

/* Sets grid margins to the provided values */
void Grid::setGridMargins(unsigned int top, unsigned int right, unsigned int bottom, unsigned int left)
{
   margin_top = top;
   margin_right = right;
   margin_bottom = bottom;
   margin_left = left;
}

/* Sets grid block size to the provided value */
void Grid::setGridBlockSize(unsigned int size)
{
   block_size = size;
}

/* Returns grid's width */
int Grid::getGridWidth()
{
   return width;
}

/* Returns grid's height */
int Grid::getGridHeight()
{
   return height;
}

/* Sets color for drawing grid lines and border to the provided RGB values */
void Grid::setGridColor(float r, float g, float b)
{
   gridColor[0] = r;
   gridColor[1] = g;
   gridColor[2] = b;
}

/* Draws a block with specified RGB color at given location x, y on the screen */
void Grid::drawBlock(unsigned int x, unsigned int y, float r, float g, float b)
{
   /* Draw a filled rectangle */
   glColor3f(r, g, b);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_QUADS);
      glVertex2i(margin_left + (block_size*x), margin_top + (block_size*y));
      glVertex2i(margin_left + (block_size*x), margin_top + (block_size*y) + block_size);
      glVertex2i(margin_left + (block_size*x) + block_size, margin_top + (block_size*y) + block_size);
      glVertex2i(margin_left + (block_size*x) + block_size, margin_top + (block_size*y));
   glEnd();

   /* Draw an empty rectangle to serve as the outline */
   glColor3f(0.5, 0.5, 0.5); // Gray
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_QUADS);
      glVertex2i(margin_left + (block_size*x), margin_top + (block_size*y));
      glVertex2i(margin_left + (block_size*x), margin_top + (block_size*y) + block_size);
      glVertex2i(margin_left + (block_size*x) + block_size, margin_top + (block_size*y) + block_size);
      glVertex2i(margin_left + (block_size*x) + block_size, margin_top + (block_size*y));
   glEnd();
}