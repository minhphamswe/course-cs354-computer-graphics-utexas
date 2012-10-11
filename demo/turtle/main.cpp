#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <vector>

#include "./command.h"

#include "./common.h"
#include "./turtle.h"

using namespace std;

// Command vector
vector<Command> commands;

// Turtle trace vectors
vector<Point> points;
vector<Color> colors;

void Init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glColor3f(1.0, 0.0, 0.0);
  glDisable(GL_BLEND);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // TODO: Change this call so that the drawing methods work on a canvas
  // that is 200x200 units with the origin (0, 0) at the center of the
  // canvas.
  gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
  glMatrixMode(GL_MODELVIEW);

  // Initialize the turtle with trace vectors
  Turtle(&points, &colors);
}

void Interpret(const vector<Command>& commands) {
  // TODO: Interpret each command one-by-one.
  // TODO: Remove output statements as you implement them.
  // Get the turtle
  Turtle t = Turtle();

  for (int i = 0; i < commands.size(); ++i) {
    const Command& c = commands[i];

    switch (c.name()) {
    case FORWARD:
      // Command Turtle to go forward
      t.forward(c.arg());
      break;
    case RIGHT:
      // Command Turtle to turn right
      t.right(c.arg());
      break;
    case LEFT:
      // Command Turtle to turn left
      t.left(c.arg());
      break;
    case PEN_UP:
      // Command Turtle to lift pen up
      t.up();
      break;
    case PEN_DOWN:
      // Command Turtle to put pen down
      t.down();
      break;
    case COLOR:
      // Command Turtle to change pen color
      t.color(c.arg());
      break;
    case ORIGIN:
      // Command Turtle to return to origin
      t.origin();
      break;
    }
  }
}

void Keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'q':
      exit(EXIT_SUCCESS);
      break;
  }
}

void Display() {
  int i;
  glClear(GL_COLOR_BUFFER_BIT);
  // TODO: Change to draw according to turtle commands given
  // Draw a red triangle.
  glBegin(GL_LINES);
  for (int i = 0; i < points.size(); i++) {
    glColor3f(colors[i].r, colors[i].g, colors[i].b);  // change color first
    glVertex2f(points[i].x, points[i].y);              // draw point in color
  }
  glEnd();

  glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  // DO NOT change the window title.  It is necessary for the screen capture.
  glutCreateWindow("Turtle graphics");
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  Init();

  if (argc < 2) {
    cout << "Usage: turtle filename" << endl;
    exit(1);
  }
  // Parse and execute drawing Turtle commands (Turtle will drop traces)
  commands = Parse(argv[1]);
  Interpret(commands);

  // Enter the main drawing loop
  glutMainLoop();
}
