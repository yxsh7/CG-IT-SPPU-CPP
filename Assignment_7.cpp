/*
Aim: Generate fractal patterns using i) Bezier ii) Koch Curve
*/

#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

using namespace std;

int x[4], y[4]; // Array to store the x and y coordinates of four points

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set the clear color to white
    glMatrixMode(GL_PROJECTION); // Set the matrix mode to projection
    gluOrtho2D(0, 640, 0, 480); // Define the orthographic projection matrix
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
}

void putpixel(double xt, double yt) {
    glColor3f(1, 0, 0); // Set the color to red
    glBegin(GL_POINTS); // Begin drawing points
        glVertex2d(xt, yt); // Specify the vertex position
    glEnd(); // End drawing points
    glFlush(); // Force execution of OpenGL commands
}

void Algorithm() {
    glColor3f(0, 1, 0); // Set the color to green
    glBegin(GL_LINES); // Begin drawing lines
        glVertex2i(x[0], y[0]); // Specify the first point of the line
        glVertex2i(x[1], y[1]); // Specify the second point of the line
        glVertex2i(x[1], y[1]); // Specify the third point of the line
        glVertex2i(x[2], y[2]); // Specify the fourth point of the line
        glVertex2i(x[2], y[2]); // Specify the fifth point of the line
        glVertex2i(x[3], y[3]); // Specify the sixth point of the line
    glEnd(); // End drawing lines
    glFlush(); // Force execution of OpenGL commands

    double t;
    for (t = 0.0; t < 1.0; t += 0.0005) {
        // Calculate the x and y coordinates of the Bezier curve using cubic interpolation
        double xt = pow(1 - t, 3) * x[0] + 3 * t * pow(1 - t, 2) * x[1] + 3 * pow(t, 2) * (1 - t) * x[2] + pow(t, 3) * x[3];
        double yt = pow(1 - t, 3) * y[0] + 3 * t * pow(1 - t, 2) * y[1] + 3 * pow(t, 2) * (1 - t) * y[2] + pow(t, 3) * y[3];
        putpixel(xt, yt); // Plot the calculated point on the screen
    }
}

int main(int argc, char** argv) {
    cout << "\n \t Enter The Four Points x space y ";
    for (int i = 0; i < 4; i++) {
        cout << "\n \t Enter x and y for " << i << " = ";
        cin >> x[i] >> y[i]; // Read the x and y coordinates from the user
    }

    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set the display mode
    glutInitWindowSize(640, 480); // Set the window size
    glutInitWindowPosition(200, 200); // Set the window position
    glutCreateWindow("Bezier 4 point"); // Create a window with the specified title
    init(); // Call the initialization function
    glutDisplayFunc(Algorithm); // Register the display callback function

    glutMainLoop(); // Enter the event processing loop
    return 0;
}
