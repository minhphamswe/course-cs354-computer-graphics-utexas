#include <math.h>
#include <iostream>
#include <vector>

#include "./common.h"
#include "./command.h"

using namespace std;

// Command vector
vector<Command> commands;

// Cursor states
bool draw;      /// True if the pen is down (drawing)
float x, y;     /// Location of the cursor
float o;        /// Orientation of the cursor (in radian)

/// Return the radian measurment of an angle measured in degrees
float rad(double degree) {
  
}

void Init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glColor3f(1.0, 0.0, 0.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // TODO: Change this call so that the drawing methods work on a canvas
  // that is 200x200 units with the origin (0, 0) at the center of the
  // canvas.
  gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
  glMatrixMode(GL_MODELVIEW);

  // Initialize values for the cursor
  draw = true;
  x = 0;
  y = 0;
  o = rad(90);
}

void Interpret(const vector<Command>& commands) {
  // TODO: Interpret each command one-by-one.
  // TODO: Remove output statements as you implement them.
  for (int i = 0; i < commands.size(); ++i) {
    const Command& c = commands[i];

    // pre-action debug info
    cout << "Pre Action: " << endl;
    cout << "(x, y): (" << x << ", " << y << ")" << endl;
    cout << "o: " << o << endl;

    switch (c.name()) {
    case FORWARD:
      cout << "forward " << c.arg() << endl;
      x = x + cos(o) * c.arg();
      y = y + sin(o) * c.arg();
      if (draw) {
        glVertex2f(x, y);
      }
      break;
    case RIGHT:
      cout << "right " << c.arg() << endl;
      o = o - rad(c.arg());
      break;
    case LEFT:
      cout << "left " << c.arg() << endl;
      o = o + rad(c.arg());
      break;
    case PEN_UP:
      cout << "pen up" << endl;
      draw = false;
      break;
    case PEN_DOWN:
      cout << "pen down" << endl;
      draw = true;
      break;
    case COLOR:
      cout << "color " << c.arg() << endl;
      if (c.arg() == 0)
        glColor3f(0.f, 0.f, 0.f);
      if (c.arg() == 1)
        glColor3f(1.f, 0.f, 0.f);
      if (c.arg() == 2)
        glColor3f(0.f, 1.f, 0.f);
      if (c.arg() == 3)
        glColor3f(0.f, 0.f, 1.f);
      break;
    case ORIGIN:
      cout << "origin" << endl;
      x = 0;
      y = 0;
      o = rad(90);
      break;
    }
    // post-action debug info
    cout << "Post Action: " << endl;
    cout << "(x, y): (" << x << ", " << y << ")" << endl;
    cout << "o: " << o << endl;
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
  glClear(GL_COLOR_BUFFER_BIT);
  // TODO: Change to draw according to turtle commands given
  // Draw a red triangle.
  glBegin(GL_LINE_STRIP);
  // glVertex2f(x, y);
  Interpret(commands);
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
  commands = Parse(argv[1]);
  glutMainLoop();
}
