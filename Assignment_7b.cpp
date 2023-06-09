#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

using namespace std;

double x, y, len, angle; // Variables to store starting point, length, and angle
int it; // Variable for the number of iterations

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set the clear color to white
    glMatrixMode(GL_PROJECTION); // Set the matrix mode to projection
    gluOrtho2D(0, 640, 0, 480); // Define the orthographic projection matrix
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
}

void line1(int x1, int y11, int x2, int y2) {
    glColor3f(0, 1, 0); // Set the color to green
    glBegin(GL_LINES); // Begin drawing lines
        glVertex2i(x1, y11); // Specify the first point of the line
        glVertex2i(x2, y2); // Specify the second point of the line
    glEnd(); // End drawing lines
    glFlush(); // Force execution of OpenGL commands
}

void k_curve(double x, double y, double len, double angle, int it) {
    if (it > 0) {
        len /= 3; // Divide the length by 3 for each iteration
        k_curve(x, y, len, angle, (it - 1)); // Recursive call for the first segment of the curve
        x += (len * cosl(angle * (M_PI) / 180)); // Update the x-coordinate based on the length and angle
        y += (len * sinl(angle * (M_PI) / 180)); // Update the y-coordinate based on the length and angle
        k_curve(x, y, len, angle + 60, (it - 1)); // Recursive call for the second segment of the curve
        x += (len * cosl((angle + 60) * (M_PI) / 180)); // Update the x-coordinate based on the length and angle
        y += (len * sinl((angle + 60) * (M_PI) / 180)); // Update the y-coordinate based on the length and angle
        k_curve(x, y, len, angle - 60, (it - 1)); // Recursive call for the third segment of the curve
        x += (len * cosl((angle - 60) * (M_PI) / 180)); // Update the x-coordinate based on the length and angle
        y += (len * sinl((angle - 60) * (M_PI) / 180)); // Update the y-coordinate based on the length and angle
        k_curve(x, y, len, angle, (it - 1)); // Recursive call for the fourth segment of the curve
    } else {
        line1(x, y, (int)(x + len * cosl(angle * (M_PI) / 180) + 0.5), (int)(y + len * sinl(angle * (M_PI) / 180) + 0.5));
        // Draw a line segment for the final iteration
    }
}

void Algorithm() {
    k_curve(x, y, len, angle, it); // Call the k_curve function to draw the Koch curve
}

int main(int argc, char** argv) {
    cout << "\n Enter Starting Point x space y ";
    cin >> x >> y;

    cout << "\n Length of line and angle of line";
    cin >> len >> angle;

    cout << "\n No. of iterations ";
    cin >> it;

    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set the display mode
    glutInitWindowSize(640, 480); // Set the window size
    glutInitWindowPosition(200, 200); // Set the window position
    glutCreateWindow("Koch"); // Create a window with the specified title
    init(); // Call the initialization function
    glutDisplayFunc(Algorithm); // Register the display callback function

    glutMainLoop(); // Enter the event processing loop
    return 0;
}
