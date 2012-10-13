/*
  CS 354 - Fall 2012
  main.cpp

  This is simple skeleton GLUT code.
*/

#include <src/core/point.h>
#include <src/core/vector.h>
#include <src/core/transform.h>
#include <src/core/bbox.h>

// C++ library includes
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>

#include "./common.h"

#include "./types.h"
#include "./bvh_defs.h"
#include "./joint.h"
#include "./loader.h"
#include "./geom.h"

using namespace std;
using namespace ishi;

// window parameters
int window_width = 800, window_height = 600;
float window_aspect = window_width/static_cast<float>(window_height);

// callback prototypes
void InitGL();
void Display();
void Resize(int width, int height);
void Keyboard(unsigned char key, int x, int y);
void Idle();
void Sleep(int value);

void SetLighting();

// Application initialization
void Init();

#define PI 3.14159265f

SceneGraph sg;            // Main scene graph

Point eye, center, up;    // Camera configuration variables
int waypoint = 1;         // Default camera position (unused)

BBox bbox = BBox(Point(-100, -100, -100), Point(100, 100, 100));
float maxDist;

Transform orbitLeft = RotateY(-0.1f);        // Orbitting left transform

char filename[1000];

bool showAxis = true;       // If true, show axis
bool showBounds = false;    // If true, show bounding box
bool animate = false;       // If true, animate character

float axisLen = 1.0f;

void InitGL() {
  // Perform any necessary GL initialization in this function

  // enable depth testing, and set clear color to white
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  SetLighting();

  Init();

  // resize the window
  Resize(window_width, window_height);
}

void ComputeLookAt() {
  // Recompute world center and bound
  maxDist = Length(bbox.pMax - bbox.pMin);
  center = (bbox.pMax + bbox.pMin)/2.0f;
  axisLen = maxDist*0.05f;
}

void Init() {
  // Compute world bounds
  ComputeLookAt();

  // Compute default camera position
  up = Point(0.0f, 1.0f, 0.0f);
  eye = center + Vector(0.5f*maxDist, 0.75f*maxDist, 1.5f*maxDist);

  sg.SetCurrentFrame(0);
}

void SetLighting() {
  glShadeModel(GL_FLAT);
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
  glDisable(GL_COLOR_MATERIAL);
}

void SetCamera() {
  gluLookAt(eye[0], eye[1], eye[2],
            center[0], center[1], center[2],
            up[0], up[1], up[2]);
}

void SetProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(40.0, window_aspect, 1, 1500);
}

void SetDrawMode() {
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_FILL);
}

void DrawAxis() {
  Point c = (bbox.pMin+bbox.pMax) * 0.5f;
  float L = Length(bbox.pMax-bbox.pMin) * 0.2;

  Vector X(L, 0, 0), Y(0, L, 0), Z(0, 0, L);

  glLineWidth(2.0);

  glBegin(GL_LINES);

  glColor3f(1, 0, 0);
  glVertex3f(c.x, c.y, c.z);
  glVertex3f((c+X).x, (c+X).y, (c+X).z);

  glColor3f(0, 1, 0);
  glVertex3f(c.x, c.y, c.z);
  glVertex3f((c+Y).x, (c+Y).y, (c+Y).z);

  glColor3f(0, 0, 1);
  glVertex3f(c.x, c.y, c.z);
  glVertex3f((c+Z).x, (c+Z).y, (c+Z).z);

  glEnd();
}

void DrawFloor(float W, float H, float w, float h) {
  float a = H/h, b = W/w;
  int M = static_cast<int>(floor(a+0.5f));
  int N = static_cast<int>(floor(b+0.5f));
  int i = 0, j = 0;
  Vec3f u = {w, 0, 0}, v = {0, 0, h}, r = {-(N/2)*w, 0, -(M/2)*h};
  Vec3f p0, p1, p2, p3;
  glEnable(GL_POLYGON_SMOOTH);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
  glBegin(GL_QUADS);
  glColor3f(0.7, 0.7, 0.7);
  for (j = 0; j < N; j++) {
    p0 = r+u*static_cast<float>(j%2);
    for (i = j%2; i < M; i += 2) {
      p1 = p0+u;
      p2 = p1+v;
      p3 = p2-u;

      glVertex3fv(p3.x);
      glVertex3fv(p2.x);
      glVertex3fv(p1.x);
      glVertex3fv(p0.x);

      p0 += u*2.0f;
    }
    r += v;
  }
  glEnd();
}

void DrawRect(const Point &base, const Vector &ext1, const Vector &ext2) {
  Point tmp;
  glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 1);

    glVertex3fv(&(base.x));
    tmp = base + ext1;
    glVertex3fv(&(tmp.x));

    tmp = base + ext1 + ext2;
    glVertex3fv(&(tmp.x));

    tmp = base + ext2;
    glVertex3fv(&(tmp.x));
    glVertex3fv(&(base.x));
  glEnd();
}

void DrawBounds() {
  Point u, v, m1[] = {bbox.pMin, bbox.pMax}, m2[] = {bbox.pMax, bbox.pMin};
  Vector uu, vv;

  for (int k = 0; k < 2; k++) {
    for (int i = 0; i < 3; i++) {
      for (int j = i+1; j < 3; j++) {
        u = m1[k];
        v = m1[k];
        u[i] = m2[k][i];
        v[j] = m2[k][j];
        uu = u - m1[k];
        vv = v - m1[k];
        DrawRect(m1[k], uu, vv);
      }
    }
  }
}

void Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  SetProjection();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  SetLighting();
  SetCamera();
  SetDrawMode();
  //DrawFloor(800, 800, 80, 80);

  // TODO: draw scene graph and animate

  // Render scene graph
  for (unsigned int i = 0; i < sg.roots.size(); i++) {
    sg.roots[i]->Render();
  }

  // If animating:
  if (animate) {
    // increment frame index && update position for all joints
    sg.SetCurrentFrame((sg.GetCurrentFrame()+1) % sg.GetNumFrames());
    // then sleep until the next frame
    glutTimerFunc(sg.GetFrameTime()*10000, Sleep, 0);
  }

  if (showAxis) DrawAxis();
  if (showBounds) DrawBounds();

  glFlush();          // finish the drawing commands
  glutSwapBuffers();  // and update the screen
}

// This reshape function is called whenever the user
// resizes the display window.
void Resize(int width, int height) {
  window_width = width;
  window_height = height;
  float fheight = static_cast<float>(height);
  window_aspect = width / fheight;

  // resize the window
  glViewport(0, 0, window_width, window_height);

  SetProjection();

  // setup basic orthographic projection
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // let glut know to redraw the screen
  glutPostRedisplay();
}

// This function is called whenever the user hits letters or numbers
// on the keyboard.  The 'key' variable has the character the user hit,
// and x and y tell where the mouse was when it was hit.
void Keyboard(unsigned char key, int x, int y) {
  y = window_height - y;

  float sgn = 1.0f;
  Vec3f v;

  switch (key) {
    case '1':
      waypoint = 1;
      eye = center + Vector(0.5f*maxDist, 0.75f*maxDist, 1.5f*maxDist);
      ComputeLookAt();
      break;
    case '2':
      waypoint = 2;
      eye = center + Vector(0, 0.1f*maxDist, 1.5f*maxDist);
      ComputeLookAt();
      break;
    case '3':
      waypoint = 3;
      eye = center + Vector(1.5f*maxDist, 0.1f*maxDist, 0);
      ComputeLookAt();
      break;
    case 'z':
      waypoint = 4;
      eye = center + ((eye - center) * 0.95);
      ComputeLookAt();
      break;
    case 'Z':
      eye = center + ((eye - center) * 1.05);
      ComputeLookAt();
      break;
    case 'j':
      orbitLeft.Apply(&eye);
      ComputeLookAt();
      break;
    case 'k':
      orbitLeft.ApplyInvert(&eye);
      ComputeLookAt();
      break;
    case ' ':
      cout << "Start/stop animation" << endl;
      animate = !animate;
      break;
    case 'a':
      showAxis = !showAxis;
      break;
    case 'b':
      showBounds = !showBounds;
      break;
    case 'q':
    case 27:  // esc
      exit(0);
      break;
  }

  // let glut know to redraw the screen
  glutPostRedisplay();
}

void Sleep(int value) {
  glutPostRedisplay();
}

void Idle() {}

void processCommandLine(int argc, char *argv[]) {
  if (argc>1) {
    snprintf(&(filename[0]), strlen(argv[1])+1, "%s", argv[1]);
    BVHLoader::loadBVH(filename, &sg);
    ComputeLookAt();
  } else {
    printf("Filename argument required.\n");
    exit(0);
  }
}

void showMenu() {
  cout << "------------ menu ------------" << endl;
  cout << "q - quit" << endl;
  cout << "a - show/hide axis" << endl;
  cout << "b - show/hide bounds" << endl;
  cout << "[1-3] - move to waypoint" << endl;
  cout << "z - zoom in" << endl;
  cout << "Z - zoom out" << endl;
  cout << "j - rotate left" << endl;
  cout << "k - rotate right" << endl;
  cout << "[SPACE] - start/stop" << endl;
}

int main(int argc, char *argv[]) {
  // Initialize GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(window_width, window_height);
  glutInitWindowPosition(100, 100);
  // Do not change the name of the window -- it is needed for the screenshot
  glutCreateWindow("Mocap");
  glutDisplayFunc(Display);
  glutReshapeFunc(Resize);
  glutKeyboardFunc(Keyboard);
  glutIdleFunc(Idle);

  processCommandLine(argc, argv);

  showMenu();

  InitGL();

  glutMainLoop();

  return 0;
}
