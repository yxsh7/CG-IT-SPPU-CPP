#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

using namespace std;

int y = 0;          // Variable to track the y-coordinate of the triangle
int x = 0;          // Variable to track the x-coordinate of the rectangle
int direction = 1;  // Variable to control the direction of the triangle movement

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Set clear color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);        // Set the 2D orthographic projection
}

void object1()
{
    glClear(GL_COLOR_BUFFER_BIT);      // Clear the color buffer
    
    // Draw the triangle
    glColor3f(0, 1, 0);                 // Set drawing color to green
    glBegin(GL_POLYGON);                // Start drawing a polygon
        glVertex2i(320, 240 + y);       // Define the vertices of the triangle
        glVertex2i(280, 200 + y);
        glVertex2i(360, 200 + y);
    glEnd();                            // End drawing the polygon
    
    // Draw the rectangle
    glColor3f(0.5, 0, 0.5);             // Set drawing color to purple
    glBegin(GL_POLYGON);                // Start drawing a polygon
        glVertex2i(120 + x, 180);       // Define the vertices of the rectangle
        glVertex2i(200 + x, 180);
        glVertex2i(200 + x, 220);
        glVertex2i(120 + x, 220);
    glEnd();                            // End drawing the polygon
    
    glutSwapBuffers();                  // Swap the front and back buffers to display the objects
}

void timer(int)
{
    glutPostRedisplay();                // Mark the current window as needing to be redisplayed
    glutTimerFunc(1000 / 60, timer, 0); // Set a timer callback to trigger every 1/60th of a second
    
    // Update the triangle's movement
    if (direction == 1)
    {
        y = y + 3;                      // Move the triangle upwards
        if (y >= 220)
            direction = -1;             // Reverse direction when reaching the upper boundary
    }
    else if (direction == -1)
    {
        y = y - 3;                      // Move the triangle downwards
        if (y <= -240)
            direction = 1;              // Reverse direction when reaching the lower boundary
    }
    
    // Update the rectangle's movement
    x = x + 3;                          // Move the rectangle to the right
    if (x >= 500)
        x = -400;                       // Reset the x-coordinate when reaching the right boundary
}

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);                          // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    // Set the display mode to use double buffering and RGB color
    glutInitWindowSize(640, 480);                   // Set the initial window size
    glutInitWindowPosition(200, 200);                // Set the initial window position
    glutCreateWindow("Animation");                   // Create the window with the specified title
    init();                                          // Call the init function to initialize OpenGL
    glutDisplayFunc(object1);                        // Set the display callback function
    glutTimerFunc(1000, timer, 0);                    // Set the timer callback function
    glutMainLoop();                                  // Enter the event processing loop
    return 0;
}
