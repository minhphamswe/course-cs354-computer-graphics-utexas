/**
 * @file gl_cube.cpp
 * This demo shows basic capabilities of OpenGL and GLUT.
 *
 * It is used to show that OpenGL is available on the system.
 */

#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define DELTA 10
#define RDELTA 5

static int vpx;    // X coordinate of the lower left corner of viewport
static int vpy;    // Y coordinate of the lower left corner of viewport
static unsigned int vpw;    // width of the viewport
static unsigned int vph;    // height of the viewport

static float rx;  // cube rotation around the x axis
static float ry;  // cube rotation around the y axis

static bool depth;  // true if depth-testing is enabled
static bool cull;   // true if hidden-face culling is enabled
static bool wire;   // true if backfaces are drawn in wireframe

void init(void)
{
  glClearColor(0,0,0,0);    // Set clearing color
  glShadeModel(GL_FLAT);    // Set shading model

  // Set up camera
  glLoadIdentity();
  gluLookAt(20, 20, 20, 0, 0, 0, 0, 1, 0);
  //gluLookAt(-5, -5, -5, 0, 0, 0, 0, -1, 0);

  // Print instruction
  std::cout << "=================================================\n";
  std::cout << "|| Instructions: \n";
  std::cout << "|| \n";
  std::cout << "|| - Playing with the viewport \n";
  std::cout << "||   * Press +/- keys to expand/shrink the viewport\n";
  std::cout << "||   * Press WASD keys to move the viewport\n";
  std::cout << "|| - Playing with the cube \n";
  std::cout << "||   * Press arrow keys to rotate the cube\n";
  std::cout << "|| - Playing with the rendering method\n";
  std::cout << "||   * Right click to open the Effects menu\n";
  std::cout << "=================================================\n";
}

/// Called whenever a menu is brought up
void ProcessMenu(int value) {
  if (value == 1) depth = !depth;
  if (value == 2) cull = !cull;
  if (value == 3) wire = !wire;
  glutPostRedisplay();
}

void DrawCube(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  // Save model transformation
  glPushMatrix();

  // Rotate into position to draw the cube
  glRotatef(rx, 1.f, 0.f, 0.f);   // rotate around x
  glRotatef(ry, 0.f, 1.f, 0.f);   // rotate around y

  // Turn culling on if flag is set
  if (cull) glEnable(GL_CULL_FACE);
  else      glDisable(GL_CULL_FACE);

  // Enable depth testing if flag is set
  if (depth) glEnable(GL_DEPTH_TEST);
  else      glDisable(GL_DEPTH_TEST);

  // Draw back side as a polygon only, if flag is set
  if (wire) glPolygonMode(GL_BACK,GL_LINE);
  else      glPolygonMode(GL_BACK,GL_FILL);

  // Draw the cube
  glBegin(GL_QUADS);

    //face in xy plane
    glColor3f(1, 0, 0);   // red
    glVertex3f(-5, -5, -5);
    glVertex3f(-5, 5, -5);
    glVertex3f(5, 5, -5);
    glVertex3f(5, -5, -5);


    //face in yz plane
    glColor3f(0, 1, 0);  // green
    glVertex3f(-5, -5, -5);
    glVertex3f(-5, -5, 5);
    glVertex3f(-5, 5, 5);
    glVertex3f(-5, 5, -5);

    //face in zx plance
    glColor3f(0, 0, 1);  // blue
    glVertex3f(-5, -5, -5);
    glVertex3f(5, -5, -5);
    glVertex3f(5, -5, 5);
    glVertex3f(-5, -5, 5);

    //|| to xy plane.
    glColor3f(1, 1, 0);  // yellow
    glVertex3f(-5, -5, 5);
    glVertex3f(5, -5, 5);
    glVertex3f(5, 5, 5);
    glVertex3f(-5, 5, 5);

    //|| to yz plane
    glColor3f(1, 0, 1);   // pink
    glVertex3f(5, -5, -5);
    glVertex3f(5, 5, -5);
    glVertex3f(5, 5, 5);
    glVertex3f(5, -5, 5);

    //|| to zx plane
    glColor3f(0, 1, 1);   // cyan
    glVertex3f(-5, 5, -5);
    glVertex3f(-5, 5, 5);
    glVertex3f(5, 5, 5);
    glVertex3f(5, 5, -5);

  glEnd();

  // Restore model transformation
  glPopMatrix();

  glFlush();
}

/// Called whenever the window is resized
void reshape(int w,int h){
  vpw = w;
  vph = h;
  glViewport(vpx, vpy, vpw, vph);

  // Reset the coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //glOrtho(-10, 10, -10, 10, 1.5, 20);     // Orthographic view
  glFrustum(-1, 1, -1, 1, 1.5, 50);     // Perspective view

  glMatrixMode(GL_MODELVIEW);
  //glLoadIdentity();   // will reset the camera -> can't see anything

  glutPostRedisplay();
}

/// Called whenever a normal key is pressed on the keyboard
void Keyboard(unsigned char key, int x, int y) {
  // Move the viewport
  if (key == 'a' || key == 'A') vpx -= DELTA;
  if (key == 'd' || key == 'D') vpx += DELTA;
  if (key == 's' || key == 'S') vpy -= DELTA;
  if (key == 'w' || key == 'W') vpy += DELTA;

  // Shrink/expand the viewport
  if (key == '+') { vph += DELTA; vpw += DELTA; }
  if (key == '-') { vph -= DELTA; vpw -= DELTA; }

  glViewport(vpx, vpy, vpw, vph);
  glutPostRedisplay();
}

/// Called whenever a special key is pressed on the keyboard
void KeyboardSpec(int key, int x, int y) {
  // Increment rotation
  if (key == GLUT_KEY_LEFT)  rx -= RDELTA;
  if (key == GLUT_KEY_RIGHT) rx += RDELTA;
  if (key == GLUT_KEY_DOWN)  ry -= RDELTA;
  if (key == GLUT_KEY_UP)    ry += RDELTA;

  glutPostRedisplay();
} 

int main(int argc, char** argv){
  // Initialilze glut functions
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);

  // Register callback functions
  glutDisplayFunc(DrawCube);       // function to call every frame
  glutReshapeFunc(reshape);        // function to call when window is resized
  glutKeyboardFunc(Keyboard);      // function to call when normal key is pressed
  glutSpecialFunc(KeyboardSpec);   // function to call when speial key is pressed

  // Register menu
  glutCreateMenu(ProcessMenu);
  glutAddMenuEntry("Toggle depth test",1);
  glutAddMenuEntry("Toggle cull backface",2);
  glutAddMenuEntry("Toggle outline back",3);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  // Set clear color
  init();

  // Enter main loop
  glutMainLoop();
  return 0;
}
