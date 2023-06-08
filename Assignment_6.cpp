/*
Implement following 2D transformations on the object with respect to axis :
i) Scaling
ii) Rotation about arbitrary point
iii) Reflection
*/

// Include Libraries 
#include <iostream>
using namespace std;

#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include <vector>

// Variable Declaration

int edge; // Number of edges in the polygon
vector<int> xpoint; // Vector to store x-coordinates of polygon vertices
vector<int> ypoint; // Vector to store y-coordinates of polygon vertices

int ch; // Choice variable for selecting transformation type

double round(double d)
{
    return floor(d + 0.5); // Function to round a double value to the nearest integer
} 

// Func Declaration

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // SET THE COLOR TO WHITE
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480); // Set up a 2D orthographic viewing region
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
}

// 1. Scaling 
void scale() 
{
    glColor3f(1.0, 0, 0); // SET THE COLOR TO RED
    glBegin(GL_POLYGON); // Begin drawing a polygon
    for (int i = 0; i < edge; i++) 
    {
        glVertex2i(xpoint[i] - 320, ypoint[i] - 240); // Define the vertices of the polygon
    }
    glEnd(); // End drawing the polygon
    glFlush(); // Flush the drawing commands

    cout << "\n\tIn Scaling, the whole screen is the first quadrant.\n";
    int sx, sy;
    cout << "\tEnter sx, sy:\n";
    cin >> sx >> sy;

    // Scale the points
    for (int i = 0; i < edge; i++)
    {
        xpoint[i] = (xpoint[i] - 320) * sx; // Scale the x-coordinate of each vertex
        ypoint[i] = (ypoint[i] - 240) * sy; // Scale the y-coordinate of each vertex
    }

    glColor3f(0, 0, 1.0); // SET THE COLOR TO BLUE
    glBegin(GL_POLYGON); // Begin drawing a polygon
    for (int i = 0; i < edge; i++) 
    {
        glVertex2i(xpoint[i], ypoint[i]); // Define the scaled vertices of the polygon
    }
    glEnd(); // End drawing the polygon
    glFlush(); // Flush the drawing commands
}

// 2. Rotation about arbitrary Point
void rotation() 
{
    int cx, cy;
    cout << "\nEnter Ar point x, y: ";
    cin >> cx >> cy;

    cx = cx + 320;
    cy = cy + 240;
    glColor3f(0.0, 1.0, 0.0); // SET THE COLOR TO GREEN
    glBegin(GL_POINTS); // Begin drawing points
    glVertex2i(cx, cy); // Draw the rotation center point
    glEnd(); // End drawing points
    glFlush(); // Flush the drawing commands

    double theta;
    cout << "\nEnter theta: ";
    cin >> theta;
    theta = theta * 3.14 / 180; // Convert degrees to radians

    glColor3f(0, 0, 1.0); // SET THE COLOR TO BLUE
    glBegin(GL_POLYGON); // Begin drawing a polygon
    for (int i = 0; i < edge; i++)
    {
        glVertex2i(
            round(((xpoint[i] - cx) * cos(theta)) - ((ypoint[i] - cy) * sin(theta))) + cx,
            round(((xpoint[i] - cx) * sin(theta)) + ((ypoint[i] - cy) * cos(theta))) + cy
        ); // Apply rotation transformation to each vertex and define the rotated vertices
    }
    glEnd(); // End drawing the polygon
    glFlush(); // Flush the drawing commands
}

// 3. Reflection 
void reflection() 
{
    char reflection;
    cout << "Enter Reflection Axis (x or y):\n";
    cin >> reflection;

    if (reflection == 'x' || reflection == 'X') 
    {
        glColor3f(0.0, 0.0, 1.0); // SET THE COLOR TO BLUE
        glBegin(GL_POLYGON); // Begin drawing a polygon
        for (int i = 0; i < edge; i++)
        {
            glVertex2i(xpoint[i], (ypoint[i] * -1) + 480); // Reflect the vertices across the x-axis
        }
        glEnd(); // End drawing the polygon
        glFlush(); // Flush the drawing commands
    }
    else if (reflection == 'y' || reflection == 'Y')
    {
        glColor3f(0.0, 0.0, 1.0); // SET THE COLOR TO BLUE
        glBegin(GL_POLYGON); // Begin drawing a polygon
        for (int i = 0; i < edge; i++)
        {
            glVertex2i((xpoint[i] * -1) + 640, ypoint[i]); // Reflect the vertices across the y-axis
        }
        glEnd(); // End drawing the polygon
        glFlush(); // Flush the drawing commands
    }
}

void Draw()
{
    if (ch == 2 || ch == 3) 
    {
        glColor3f(1.0, 0, 0); // SET THE COLOR TO RED
        glBegin(GL_LINES); // Begin drawing lines
        glVertex2i(0, 240); // Draw the x-axis
        glVertex2i(640, 240);
        glEnd(); // End drawing lines

        glColor3f(1.0, 0, 0); // SET THE COLOR TO RED
        glBegin(GL_LINES); // Begin drawing lines
        glVertex2i(320, 0); // Draw the y-axis
        glVertex2i(320, 480);
        glEnd(); // End drawing lines
        glFlush(); // Flush the drawing commands

        glColor3f(1.0, 0, 0); // SET THE COLOR TO RED
        glBegin(GL_POLYGON); // Begin drawing a polygon
        for (int i = 0; i < edge; i++)
        {
            glVertex2i(xpoint[i], ypoint[i]); // Draw the original polygon
        }
        glEnd(); // End drawing the polygon
        glFlush(); // Flush the drawing commands
    }

    if (ch == 1) 
    {
        scale(); // Call the scaling function
    }
    else if (ch == 2)
    {
        rotation(); // Call the rotation function
    }
    else if (ch == 3) 
    {
        reflection(); // Call the reflection function
    }
}

// MAIN FUNCTION
int main(int argc, char** argv)
{
    // MENU DRIVEN PROGRAM
    cout << "\n Following are the 2D transformations on the object with respect to axis: \nEnter 1 for Scaling\nEnter 2 for Rotation about arbitrary point\nEnter 3 for Reflection\nYour Choice:";
    cin >> ch;
    if (ch == 1 || ch == 2 || ch == 3)
    {
        cout << "Enter the number of edges: ";
        cin >> edge;

        int xpointnew, ypointnew;
        cout << "Enter " << edge << " points of the polygon:\n";
        for (int i = 0; i < edge; i++)
        {
            cout << "Enter Point " << i << ": ";
            cin >> xpointnew >> ypointnew;

            xpoint.push_back(xpointnew + 320); // Store the x-coordinate of each vertex with respect to the origin
            ypoint.push_back(ypointnew + 240); // Store the y-coordinate of each vertex with respect to the origin
        }

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(640, 480);
        glutInitWindowPosition(200, 200);
        glutCreateWindow("2D");
        init(); // Initialize the OpenGL settings
        glutDisplayFunc(Draw); // Set the display callback function

        glutMainLoop(); // Enter the event processing loop
        return 0;
    }
    else             // WRONG CHOICE ERROR HANDLING 
    {
        cout << "\nCheck input and run again.\n";
        return 0;
    }
}

/*

1. The necessary libraries are included at the beginning of thhese librarathematical calculations and graphics rendering.

2. Next, some global variables are declared:
   - `edge`: Stores the number of edges in the polygon.
   - `xpoint` and `ypoint`: Vectors to store the x and y coordinates of the polygon vertices.
   - `ch`: Choice variable for selecting the type of transformation.

3. The `round()` function is defined, which is used to round a double value to the nearest integer.

4. The `init()` function is defined. It sets up the OpenGL settings, such as the clear color and the orthographic projection.

5. The `scale()` function implements the scaling transformation. It takes user input for scaling factors `sx` and `sy`. The polygon is initially drawn in red color. Then, the x and y coordinates of each vertex are scaled using the input factors. Finally, the scaled polygon is drawn in blue color.

6. The `rotation()` function implements the rotation transformation. It takes user input for the rotation center point (`cx`, `cy`) and the rotation angle `theta` in degrees. The rotation center is displayed in green color. The polygon is initially drawn in red color. The rotation is applied to each vertex using the rotation formulas, and the rotated polygon is drawn in blue color.

7. The `reflection()` function implements the reflection transformation. It takes user input for the reflection axis (`x` or `y`). If the axis is 'x', the vertices are reflected across the x-axis, and if it is 'y', the vertices are reflected across the y-axis. The reflected polygon is drawn in blue color.

8. The `Draw()` function is responsible for drawing the initial polygon and calling the appropriate transformation function based on the user's choice (`ch`). If `ch` is 1, it calls the `scale()` function; if `ch` is 2, it calls the `rotation()` function; if `ch` is 3, it calls the `reflection()` function. It also draws the x and y axes in red color.

9. In the `main()` function, the user is prompted to enter their choice for the transformation type (`ch`). If the choice is valid (1, 2, or 3), the user is prompted to enter the number of edges of the polygon and the coordinates of the vertices. The necessary OpenGL settings are initialized, and the `Draw()` function is set as the display callback function. Finally, the main event loop (`glutMainLoop()`) is entered to handle user interactions and rendering.

*/