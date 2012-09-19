#include <stdio.h>
#include <vector>
#include <UnitTest++/UnitTest++.h>
#include <core/geometry.h>
#include <core/color.h>
#include <project1/common.h>
#include <project1/turtle.h>

std::vector<Point> points = std::vector<Point>();
std::vector<Color> colors = std::vector<Color>();

void Init() {
  // Init GL
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glColor3f(1.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
  glMatrixMode(GL_MODELVIEW);

  // Init Turtle
  Turtle t = Turtle(&points, &colors);
}

// Init Test Number
enum tests {
  VerticalLine,
  TenOFive,
  Square,
  Example1,

  numTest,
};
int testNum;

void DrawVerticalLine() {
  printf("Drawing Vertical Line ...\n");
  // Turtle commands
  Turtle t = Turtle();
  t.reset();
  t.forward(90);

  // Checks
  CHECK_EQUAL(2, points.size());
  CHECK_EQUAL(2, colors.size());
  
  glutPostRedisplay();
}

void DrawTenOFive() {
  printf("Drawing 10 o' 5 ...\n");
  // Turtle commands
  Turtle t = Turtle();
  t.reset();
  t.left(60);
  t.forward(30);
  t.origin();
  t.right(30);
  t.forward(50);

  // Checks
  CHECK_EQUAL(4, points.size());
  CHECK_EQUAL(4, colors.size());

  glutPostRedisplay();
}

void DrawSquare() {
  printf("Drawing a Square ...\n");
  // Turtle commands
  Turtle t = Turtle();
  t.reset();
  t.up();
  t.forward(15);
  t.down();
  t.right(90);
  t.forward(15);
  t.right(90);
  t.forward(30);
  t.right(90);
  t.forward(30);
  t.right(90);
  t.forward(30);
  t.right(90);
  t.forward(15);

  // Checks
  CHECK_EQUAL(10, points.size());
  CHECK_EQUAL(10, colors.size());

  glutPostRedisplay();
}

void DrawExample1() {
  printf("Drawing Example 1 ...\n");

  Turtle t = Turtle();
  t.reset();

  t.forward(30);
  t.right (90);
  t.forward (30);
  t.left (90);

  t.color (1);
  t.forward(30);
  t.right(90);
  t.forward(30);
  t.left(90);

  t.origin();
  t.left(90);

  t.color(2);
  t.forward(30);
  t.left(90);
  t.forward(30);
  t.right(90);

  t.color(3);
  t.forward(30);
  t.left(90);
  t.forward(30);
  t.right(90);
  
  glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'q':
      exit(EXIT_SUCCESS);
      break;
    case 'n':
      testNum = ++testNum % numTest;
      switch (testNum) {
        case VerticalLine:
          DrawVerticalLine();
          break;
        case TenOFive:
          DrawTenOFive();
          break;
        case Square:
          DrawSquare();
          break;
        case Example1:
          DrawExample1();
          break;
      break;
      }
  }
}

void Display()
{
  // Draw previously issued commands
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_LINES);
  for (unsigned i = 0; i < points.size(); i++) {
    glColor3f(colors[i].r, colors[i].g, colors[i].b);
    glVertex2f(points[i].x, points[i].y);
  }
  glEnd();
  glFlush();
  glutPostRedisplay();
}

TEST(Turtle) {
  // Init GLUT
  int argc = 1;
  char* argv[1] = {"project1_test"};
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Turtle graphics");
  glutKeyboardFunc(Keyboard);
  glutDisplayFunc(Display);

  Init();

  // Enter main loop
  glutMainLoop();
}