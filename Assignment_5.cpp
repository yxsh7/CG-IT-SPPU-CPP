/*
Implement Cohen Sutherland polygon clipping method to clip the polygon with respect the view-port and window. Use mouse click, keyboard interface
*/
// CHECK

#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

using namespace std;

int wxmin = 200, wxmax = 500, wymax = 350, wymin = 100;
int points[10][2];  // Array to store the polygon points
int edge;  // Number of edges in the polygon

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Draw() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2, 0.2, 1);
    glBegin(GL_POLYGON);
    for (int i = 0; i < edge; i++) {
        glVertex2i(points[i][0], points[i][1]);
    }
    glEnd();
    glFlush();

    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(200, 100);
    glVertex2i(500, 100);
    glVertex2i(500, 350);
    glVertex2i(200, 350);
    glEnd();
    glFlush();
}

int BottomClipping(int e) {
    float m = 0;
    int x = 0, k = 0;
    int t[10][2];

    for (int i = 0; i < e; i++) {
        if (points[i][1] < wymin) {
            if (points[i + 1][1] < wymin) {
                // Points below the bottom clipping boundary, no intersection
            } else if (points[i + 1][1] > wymin) {
                // Intersection occurs between points[i] and points[i+1]
                float x1, x2;
                float y1, y2;
                x1 = points[i][0];
                y1 = points[i][1];
                x2 = points[i + 1][0];
                y2 = points[i + 1][1];
                x = ((1 / ((y2 - y1) / (x2 - x1))) * (wymin - y1)) + x1;  // Calculate intersection x-coordinate
                t[k][0] = x;
                t[k][1] = wymin;
                k++;
            }
        } else if (points[i][1] > wymin) {
            if (points[i + 1][1] > wymin) {
                // Points above the bottom clipping boundary, no intersection
            } else if (points[i + 1][1] < wymin) {
                // Intersection occurs between points[i] and points[i+1]
                float x1, x2;
                float y1, y2;
                x1 = points[i][0];
                y1 = points[i][1];
                x2 = points[i + 1][0];
                y2 = points[i + 1][1];

                x = ((1 / ((y2 - y1) / (x2 - x1))) * (wymin - y1)) + x1;  // Calculate intersection x-coordinate

                t[k][0] = x1;
                t[k][1] = y1;
                k++;
                t[k][0] = x;
                t[k][1] = wymin;
                k++;
            }
        }
    }
    for (int i = 0; i < k; i++) {
        points[i][0] = t[i][0];
        points[i][1] = t[i][1];
    }
    return k;
}

int TopClipping(int e) {
    float m = 0;
    int x = 0, k = 0;
    int t[10][2];

    for (int i = 0; i < e; i++) {
        if (points[i][1] > wymax) {
            if (points[i + 1][1] > wymax) {
                // Points above the top clipping boundary, no intersection
            } else if (points[i + 1][1] < wymax) {
                // Intersection occurs between points[i] and points[i+1]
                float x1, x2;
                float y1, y2;
                x1 = points[i][0];
                y1 = points[i][1];
                x2 = points[i + 1][0];
                y2 = points[i + 1][1];

                x = ((1 / ((y2 - y1) / (x2 - x1))) * (wymax - y1)) + x1;  // Calculate intersection x-coordinate

                t[k][0] = x1;
                t[k][1] = y1;
                k++;
                t[k][0] = x;
                t[k][1] = wymax;
                k++;
            }
        } else if (points[i][1] < wymax) {
            if (points[i + 1][1] < wymax) {
                // Points below the top clipping boundary, no intersection
            } else if (points[i + 1][1] > wymax) {
                // Intersection occurs between points[i] and points[i+1]
                float x1, x2;
                float y1, y2;
                x1 = points[i][0];
                y1 = points[i][1];
                x2 = points[i + 1][0];
                y2 = points[i + 1][1];

                x = ((1 / ((y2 - y1) / (x2 - x1))) * (wymax - y1)) + x1;  // Calculate intersection x-coordinate

                t[k][0] = x;
                t[k][1] = wymax;
                k++;
            }
        }
    }
    for (int i = 0; i < k; i++) {
        points[i][0] = t[i][0];
        points[i][1] = t[i][1];
    }
    return k;
}

int LeftClipping(int e) {
    float m = 0;
    int x = 0, k = 0;
    int t[10][2];

    for (int i = 0; i < e; i++) {
        if (points[i][0] < wxmin) {
            if (points[i + 1][0] < wxmin) {
                // Points to the left of the left clipping boundary, no intersection
            } else if (points[i + 1][0] > wxmin) {
                // Intersection occurs between points[i] and points[i+1]
                float x1, x2;
                float y1, y2;
                x1 = points[i][0];
                y1 = points[i][1];
                x2 = points[i + 1][0];
                y2 = points[i + 1][1];

                m = (y2 - y1) / (x2 - x1);  // Calculate slope of the line segment

                x = wxmin;
                t[k][0] = x;
                t[k][1] = (m * (x - x1)) + y1;  // Calculate intersection y-coordinate
                k++;
            }
        } else if (points[i][0] > wxmin) {
            if (points[i + 1][0] > wxmin) {
                // Points to the right of the left clipping boundary, no intersection
            } else if (points[i + 1][0] < wxmin) {
                // Intersection occurs between points[i] and points[i+1]
                float x1, x2;
                float y1, y2;
                x1 = points[i][0];
                y1 = points[i][1];
                x2 = points[i + 1][0];
                y2 = points[i + 1][1];

                m = (y2 - y1) / (x2 - x1);  // Calculate slope of the line segment

                x = wxmin;
                t[k][0] = x;
                t[k][1] = (m * (x - x1)) + y1;  // Calculate intersection y-coordinate
                k++;
                t[k][0] = x2;
                t[k][1] = y2;
                k++;
            }
        }
    }
    for (int i = 0; i < k; i++) {
        points[i][0] = t[i][0];
        points[i][1] = t[i][1];
    }
    return k;
}

int RightClipping(int e) {
    float m = 0;
    int x = 0, k = 0;
    int t[10][2];

    for (int i = 0; i < e; i++) {
        if (points[i][0] > wxmax) {
            if (points[i + 1][0] > wxmax) {
                // Points to the right of the right clipping boundary, no intersection
            } else if (points[i + 1][0] < wxmax) {
                // Intersection occurs between points[i] and points[i+1]
                float x1, x2;
                float y1, y2;
                x1 = points[i][0];
                y1 = points[i][1];
                x2 = points[i + 1][0];
                y2 = points[i + 1][1];

                m = (y2 - y1) / (x2 - x1);  // Calculate slope of the line segment

                x = wxmax;
                t[k][0] = x;
                t[k][1] = (m * (x - x1)) + y1;  // Calculate intersection y-coordinate
                k++;
            }
        } else if (points[i][0] < wxmax) {
            if (points[i + 1][0] < wxmax) {
                // Points to the left of the right clipping boundary, no intersection
            } else if (points[i + 1][0] > wxmax) {
                // Intersection occurs between points[i] and points[i+1]
                float x1, x2;
                float y1, y2;
                x1 = points[i][0];
                y1 = points[i][1];
                x2 = points[i + 1][0];
                y2 = points[i + 1][1];

                m = (y2 - y1) / (x2 - x1);  // Calculate slope of the line segment

                x = wxmax;
                t[k][0] = x;
                t[k][1] = (m * (x - x1)) + y1;  // Calculate intersection y-coordinate
                k++;
                t[k][0] = x2;
                t[k][1] = y2;
                k++;
            }
        }
    }
    for (int i = 0; i < k; i++) {
        points[i][0] = t[i][0];
        points[i][1] = t[i][1];
    }
    return k;
}

void display() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    Draw();

    int count = edge;
    count = LeftClipping(count);
    count = RightClipping(count);
    count = TopClipping(count);
    count = BottomClipping(count);

    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < count; i++) {
        glVertex2i(points[i][0], points[i][1]);
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    cout << "Enter the number of edges of the polygon: ";
    cin >> edge;

    for (int i = 0; i < edge; i++) {
        cout << "Enter the x-coordinate of vertex " << i + 1 << ": ";
        cin >> points[i][0];
        cout << "Enter the y-coordinate of vertex " << i + 1 << ": ";
        cin >> points[i][1];
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Polygon Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

