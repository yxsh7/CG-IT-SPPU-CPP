/*
SI32 Yash Kamthe
Drawing a Circle using Bresenham's Algorithm.
*/

#include <GL/glut.h>
#include <iostream>
using namespace std;

int r;

void E_way(int x, int y)
 {
    // Plot the 8 symmetric points of the circle
    glBegin(GL_POINTS);
    glVertex2i(x + 320, y + 240);  // Translate and plot the point
    glVertex2i(y + 320, x + 240);
    glVertex2i(y + 320, -x + 240);
    glVertex2i(x + 320, -y + 240);
    glVertex2i(-x + 320, -y + 240);
    glVertex2i(-y + 320, -x + 240);
    glVertex2i(-y + 320, x + 240);
    glVertex2i(-x + 320, y + 240);
    glEnd();
    glFlush();
}

void B_circle()
 {
    float d;
    d = 3 - 2 * r;  // Initial decision parameter

    int x, y;
    x = 0;
    y = r;

    do
    {
        E_way(x, y);  // Plot the points in the current circle

        if (d < 0)
        {
            d = d + 4 * x + 6;  // Update decision parameter for inward pixel
        } else 
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

int main(int argc, char **argv) 
{
    cout << "\n Enter Radius: ";
    cin >> r;  // Get the radius of the circle from the user

    glutInit(&argc, argv); // Initialize GLUT library with command line arguments
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set the initial display mode for the window

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Circle");
    init();  // Call the init function
    glutDisplayFunc(B_circle);  // Set the display callback function

    glutMainLoop();  // Enter the event processing loop

    return 0;
}

/*
1. The code is for drawing a circle using Bresenham's algorithm. Bresenham's algorithm is an efficient method for approximating a circle using only integer operations, avoiding the need for expensive floating-point calculations.

2. The `E_way` function is responsible for plotting the eight symmetric points of the circle. These points are obtained by applying translations and reflections to a single point.

3. The `B_circle` function implements Bresenham's algorithm for drawing the circle. It starts with an initial decision parameter `d` and iteratively updates it based on the current position on the circle. The algorithm uses the decision parameter to determine the next pixel to be plotted. The function calls `E_way` to plot the points in the current circle.

4. The `init` function initializes the OpenGL environment. It sets the clear color to white (`glClearColor`), the drawing color to red (`glColor3f`), and defines the 2D orthographic projection (`gluOrtho2D`). It also clears the color buffer (`glClear`) to prepare for drawing.

5. In the `main` function, the user is prompted to enter the radius of the circle. The GLUT library is initialized (`glutInit`) with the command-line arguments. The display mode is set to use a single buffer and RGB color mode (`glutInitDisplayMode`).

6. Window position and size are set using `glutInitWindowPosition` and `glutInitWindowSize`. Then, a window with the title "Circle" is created using `glutCreateWindow`. The `init` function is called to perform OpenGL initialization.

7. The `glutDisplayFunc` function is used to specify the callback function (`B_circle`) to be called for rendering the window contents.

8. Finally, `glutMainLoop` enters the event processing loop, where it continuously checks for and handles events, such as keyboard and mouse input, until the program is terminated.

The result is a window displaying a circle with the specified radius using Bresenham's algorithm.
*/
