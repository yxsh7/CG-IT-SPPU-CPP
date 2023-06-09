#include <GL/glut.h>
#include <iostream>
using namespace std;

int r1, r2;
int x1, y1, x2, y2;

void E_way(int x, int y, int tx, int ty)
{
    // Plot the 8 symmetric points of the circle
    glBegin(GL_POINTS);
    glVertex2i(x + tx, y + ty);  // Translate and plot the point
    glVertex2i(y + tx, x + ty);
    glVertex2i(y + tx, -x + ty);
    glVertex2i(x + tx, -y + ty);
    glVertex2i(-x + tx, -y + ty);
    glVertex2i(-y + tx, -x + ty);
    glVertex2i(-y + tx, x + ty);
    glVertex2i(-x + tx, y + ty);
    glEnd();
    glFlush();
}

void B_circle(int r, int tx, int ty)
{
    float d;
    d = 3 - 2 * r;  // Initial decision parameter

    int x, y;
    x = 0;
    y = r;

    do
    {
        E_way(x, y, tx, ty);  // Plot the points in the current circle

        if (d < 0)
        {
            d = d + 4 * x + 6;  // Update decision parameter for inward pixel
        }
        else
        {
            d = d + 4 * (x - y) + 10;  // Update decision parameter for inward and downward pixel
            y = y - 1;  // Decrement y-coordinate for inward and downward movement
        }
        x = x + 1;  // Increment x-coordinate for inward movement

    } while (x < y);  // Repeat until x becomes greater than or equal to y
}

void init()
{
    glClearColor(1, 1, 1, 0);  // Set clear color to white
    glColor3f(1, 0, 0);  // Set drawing color to red
    gluOrtho2D(0, 640, 0, 480);  // Set the 2D orthographic projection
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
}

int main(int argc, char** argv)
{
    cout << "\nEnter Radius 1: ";
    cin >> r1;  // Get the radius of the first circle from the user
    cout << "Enter Center coordinates (x1, y1): ";
    cin >> x1 >> y1;  // Get the center coordinates of the first circle from the user

    cout << "\nEnter Radius 2: ";
    cin >> r2;  // Get the radius of the second circle from the user
    cout << "Enter Center coordinates (x2, y2): ";
    cin >> x2 >> y2;  // Get the center coordinates of the second circle from the user

    glutInit(&argc, argv); // Initialize GLUT library with command line arguments
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set the initial display mode for the window

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Circle");
    init();  // Call the init function

    glutDisplayFunc([]() {
        B_circle(r1, x1, y1);  // Draw the first circle
        B_circle(r2, x2, y2);  // Draw the second circle
    });

    glutMainLoop();  // Enter the event processing loop

    return 0;
}
