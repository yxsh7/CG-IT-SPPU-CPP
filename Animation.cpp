#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

using namespace std;

int x = 0;      // Variable to track the x-coordinate of the object
int flag = 0;   // Variable to control the direction of movement

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Set clear color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);        // Set the 2D orthographic projection
}

void object1()
{
    glClear(GL_COLOR_BUFFER_BIT);      // Clear the color buffer
    
    glColor3f(1, 0, 0);                 // Set drawing color to red
    glBegin(GL_POLYGON);                // Start drawing a polygon
        glVertex2i(x, 220);             // Define the vertices of the polygon
        glVertex2i(x + 40, 220);
        glVertex2i(x + 40, 260);
        glVertex2i(x, 260);
    glEnd();                            // End drawing the polygon
    
    glutSwapBuffers();                  // Swap the front and back buffers to display the object
}

void timer(int)
{
    glutPostRedisplay();                // Mark the current window as needing to be redisplayed
    glutTimerFunc(1000 / 60, timer, 0); // Set a timer callback to trigger every 1/60th of a second
    
    if (flag == 0)
    {
        x = x + 3;                      // Move the object to the right
    }
    if (flag == 1)
    {
        x = x - 3;                      // Move the object to the left
    }
    if (x == 600) 
    {
        flag = 1;                       // Reverse direction when reaching the right boundary
    }
    if (x == 0) 
    {
        flag = 0;                       // Reverse direction when reaching the left boundary
    }
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

/*
- The code includes necessary header files and libraries, such as `<iostream>`, `<math.h>`, `<time.h>`, and `<GL/glut.h>`.
- The code defines two variables: `x` and `flag`. `x` is used to track the x-coordinate of the object, and `flag` is used to control the direction of movement.
- The `init` function is responsible for initializing the OpenGL environment. It sets the clear color to white using `glClearColor` and sets the 2D orthographic projection using `gluOrtho2D`. The specified range for the projection is from (0, 0) to (640, 480).
- The `object1` function is the display callback function. It clears the color buffer using `glClear` to prepare for drawing the object. It sets the drawing color to red using `glColor3f`. Then, it defines a polygon using `glBegin(GL_POLYGON)` and specifies the vertices of the polygon using `glVertex2i`. The `x` variable is used to determine the x-coordinate of the vertices, while the y-coordinate values remain constant. Finally, it ends the drawing of the polygon using `glEnd`. After drawing the object, it calls `glutSwapBuffers` to swap the front and back buffers and display the object on the screen.
- The `timer` function is a callback function that is triggered repeatedly based on a timer. Inside this function, `glutPostRedisplay` is called to mark the current window as needing to be redrawn. It sets a timer callback using `glutTimerFunc` to call the `timer` function again after a specified time interval (1/60th of a second in this case). Then, it checks the value of the `flag` variable to determine the direction of movement. If `flag` is 0, it increments `x` by 3, moving the object to the right. If `flag` is 1, it decrements `x` by 3, moving the object to the left. Additionally, it checks if `x` has reached the right boundary (600) or the left boundary (0) to reverse the direction of movement by updating the `flag` variable accordingly.
- In the `main` function, GLUT is initialized using `glutInit`. It specifies the display mode to use double buffering and RGB color using `glutInitDisplayMode`. It sets the initial window size using `glutInitWindowSize` and the initial window position using `glutInitWindowPosition`. Then, it creates the window with the specified title using `glutCreateWindow`. The `init` function is called to initialize the OpenGL environment. The `object1` function is set as the display callback function using `glutDisplayFunc`. The `timer` function is set as the timer callback function using `glutTimerFunc`. Finally, the event processing loop is entered using `glutMainLoop`, where GLUT handles events and calls the appropriate callback functions.
*/