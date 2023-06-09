/*
Implement DDA and Bresenham line drawing algorithm to draw:
i) Simple Line
ii) Dotted Line
iii) Dashed Line
Using mouse interface Divide the screen in four quadrants with center as (0, 0). The line should work for all the slopes positive as well as negative.
*/

#include<iostream>
#include<GL/glut.h>
using namespace std;

int Algo, type;  // Variables to store the algorithm and line type

void Init()
{
    glClearColor(0,0,0,0);  // Set the clear color to black
    glColor3f(0,1,0);  // Set the drawing color to green
    gluOrtho2D(0,640,0,480);  // Set the orthographic view to map window coordinates to screen coordinates
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
}

// Function to determine the sign of a number
int sign(float a)
{
    if(a == 0) {
        return 0;
    }
    if(a > 0) {
        return 1;
    }
    return -1;
}

// Function to draw a line using Bresenham's algorithm
void B_Line(int x_1, int y_1, int x_2, int y_2, int t)
{
    float dy, dx, m, P;
    dy = y_2 - y_1;  // Calculate the change in y-coordinate
    dx = x_2 - x_1;  // Calculate the change in x-coordinate
    m = dy/dx;  // Calculate the slope of the line

    P = 2 * dy - dx;  // Calculate the decision parameter

    int x = x_1, y = y_1;  // Set the initial point of the line

    cout << "\n x1 = " << x << " y1 = " << y;
    if(m < 1) {
        int cnt = 1;
        for(int i = 0; i <= dx; i++) {
            if(t == 1) {
                glBegin(GL_POINTS);
                glVertex2i(x, y);  // Plot the pixel at (x, y)
                glEnd();
            }
            if(t == 2) {
                if(i % 2 == 0) {
                    glBegin(GL_POINTS);
                    glVertex2i(x, y);  // Plot the pixel at (x, y) for every alternate point
                    glEnd();
                }
            }
            if(t == 3) {
                if(cnt <= 10) {
                    glBegin(GL_POINTS);
                    glVertex2i(x, y);  // Plot the pixel at (x, y) for the dashed line pattern
                    glEnd();
                }
                cnt++;
                if(cnt == 15) {
                    cnt = 1;
                }
            }

            if(P < 0) {
                x = x + 1;
                y = y;
                P = P + 2 * dy;
            }
            else {
                x = x + 1;
                y = y + 1;
                P = P + 2 * dy - 2 * dx;
            }
        }
    }
    else {
        int cnt = 1;
        for(int i = 0; i <= dy; i++) {
            if(t == 1) {
                glBegin(GL_POINTS);
                glVertex2i(x, y);  // Plot the pixel at (x, y)
                glEnd();
            }
            if(t == 2) {
                if(i % 2 == 0) {
                    glBegin(GL_POINTS);
                    glVertex2i(x, y);  // Plot the pixel at (x, y) for every alternate point
                    glEnd();
                }
            }
            if(t == 3) {
                if(cnt <= 10) {
                    glBegin(GL_POINTS);
                    glVertex2i(x, y);  // Plot the pixel at (x, y) for the dashed line pattern
                    glEnd();
                }
                cnt++;
                if(cnt == 15) {
                    cnt = 1;
                }
            }

            if(P < 0) {
                x = x;
                y = y + 1;
                P = P + 2 * dx;
            }
            else {
                x = x + 1;
                y = y + 1;
                P = P + 2 * dx - 2 * dy;
            }
        }
    }
    cout << "\n xlast = " << x << " ylast = " << y;
    glFlush();
}

// Function to draw a line using DDA algorithm
void DDA_LINE(int x_1, int y_1, int x_2, int y_2, int t)
{
    float dx, dy, length;
    dx = x_2 - x_1;  // Calculate the change in x-coordinate
    dy = y_2 - y_1;  // Calculate the change in y-coordinate

    if(abs(dx) >= abs(dy)) {
        length = abs(dx);
    }
    else {
        length = abs(dy);
    }

    float xin, yin;
    xin = dx / length;
    yin = dy / length;

    float x, y;

    x = x_1 + 0.5 * sign(xin);  // Set the initial x-coordinate of the line
    y = y_1 + 0.5 * sign(yin);  // Set the initial y-coordinate of the line

    int i = 0;
    int cnt = 1;
    while(i <= length) {
        if(t == 1) {
            glBegin(GL_POINTS);
            glVertex2i(x, y);  // Plot the pixel at (x, y)
            glEnd();
        }
        if(t == 2) {
            if(i % 2 == 0) {
                glBegin(GL_POINTS);
                glVertex2i(x, y);  // Plot the pixel at (x, y) for every alternate point
                glEnd();
            }
        }
        if(t == 3) {
            if(cnt <= 10) {
                glBegin(GL_POINTS);
                glVertex2i(x, y);  // Plot the pixel at (x, y) for the dashed line pattern
                glEnd();
            }
            cnt++;
            if(cnt == 15) {
                cnt = 1;
            }
        }

        x = x + xin;
        y = y + yin;
        i++;
    }

    glFlush();
}

void display()
{
    DDA_LINE(0, 240, 640, 240, 1);  // Call DDA_LINE function to draw a line
    B_Line(320, 0, 320, 640, 1);  // Call B_Line function to draw a line

    glFlush();
}

void mymouse(int b, int s, int x, int y)
{
    static int x_s, y_s, x_e, y_e, pt = 0;
    if(b == GLUT_LEFT_BUTTON && s == GLUT_DOWN) {
        if(pt == 0) {
            x_s = x;
            y_s = 480 - y;
            pt++;

            glBegin(GL_POINTS);
            glVertex2i(x_s, y_s);  // Plot the starting point of the line
            glEnd();
        }
        else {
            x_e = x;
            y_e = 480 - y;
            cout << "\n x_1_click " << x_s << " y_1_click " << y_s;
            cout << "\n x_2_click " << x_e << " y_2_click " << y_e << "\n";
            glBegin(GL_POINTS);
            glVertex2i(x_e, y_e);  // Plot the ending point of the line
            glEnd();

            if(Algo == 1) {
                DDA_LINE(x_s, y_s, x_e, y_e, type);  // Call DDA_LINE function to draw a line based on selected algorithm and line type
            }
            if(Algo == 2) {
                B_Line(x_s, y_s, x_e, y_e, type);  // Call B_Line function to draw a line based on selected algorithm and line type
            }
        }
    }
    else if(b == GLUT_RIGHT_BUTTON && s == GLUT_DOWN) {
        pt = 0;  // Reset the point counter
    }
    glFlush();
}

int main(int argc, char **argv)
{
    cout << "\n Select the Algorithm \n 1. DDA \n 2. Bresenham's \n";
    cin >> Algo;  // Get the algorithm choice from the user
    cout << "Select the Line Type \n 1. Simple Line \n 2. Dotted Line\n 3. Dashed Line \n";
    cin >> type;  // Get the line type from the user

    if((Algo == 1 || Algo == 2) && (type == 1 || type == 2 || type == 3)) {
        // Continue with the program if valid algorithm and line type are selected
    }
    else {
        cout << "\n Option entered is wrong \n";
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("DDA-Line");
    Init();
    glutDisplayFunc(display);
    glutMouseFunc(mymouse);

    glutMainLoop();
    return 0;
}
