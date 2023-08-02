

#include "glLib.hpp"

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // clear color buffer
    glColor3f(1.0, 0.0, 0.0); // draw in red
    glBegin(GL_POLYGON); // draw a polygon
    glColor3f(1.0, 0.0, 0.0); glVertex3f(0.25, 0.25, 0.0);
    glColor3f(0.0, 1.0, 0.0); glVertex3f(0.75, 0.25, 0.0);
    glColor3f(1.0, 0.0, 0.0); glVertex3f(0.75, 0.75, 0.0);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(0.25, 0.75, 0.0);
    glEnd();
    glFlush(); // flush output to screen
}