#include "global.h"
#include "Block.h"

Block::Block(void)
{
}

Block::~Block(void)
{
}

void Block::drawBlk(int x, int y, float r, float g, float b) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2i(x*BLOCK_SIZE + MARGIN_LEFT, y*BLOCK_SIZE + MARGIN_TOP);
        glVertex2i(x*BLOCK_SIZE + MARGIN_LEFT, y*BLOCK_SIZE + BLOCK_SIZE + MARGIN_TOP);
        glVertex2i(x*BLOCK_SIZE + BLOCK_SIZE + MARGIN_LEFT, y*BLOCK_SIZE + BLOCK_SIZE + MARGIN_TOP);
        glVertex2i(x*BLOCK_SIZE + BLOCK_SIZE + MARGIN_LEFT, y*BLOCK_SIZE + MARGIN_TOP);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.5, 0.5, 0.5); // Gray
    glBegin(GL_QUADS);
        glVertex2i(x*BLOCK_SIZE + MARGIN_LEFT, y*BLOCK_SIZE + MARGIN_TOP);
        glVertex2i(x*BLOCK_SIZE + MARGIN_LEFT, y*BLOCK_SIZE + BLOCK_SIZE + MARGIN_TOP);
        glVertex2i(x*BLOCK_SIZE + BLOCK_SIZE + MARGIN_LEFT, y*BLOCK_SIZE + BLOCK_SIZE + MARGIN_TOP);
        glVertex2i(x*BLOCK_SIZE + BLOCK_SIZE + MARGIN_LEFT, y*BLOCK_SIZE + MARGIN_TOP);
    glEnd();

    glFlush();
}