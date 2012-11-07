#include <src/core/point.h>
#include <src/core/vector.h>
#include <src/core/transform.h>
#include <src/rendering/GLRenderer.h>

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "./common.h"
#include "./bb.h"
#include "./mesh.h"
#include "./io.h"
#include "./texture.h"

using namespace std;
using namespace ishi;

Mesh mesh;

GLRenderer gl_renderer = GLRenderer();  // The Renderer we are using

Point eye;        // The position of the camera
Point center;     // The center of the camera's view frustum
Vector up;        // The upward orientation of the camera

Transform t;

int prevX;        // The X coordinate where the mouse was last clicked
int prevY;        // The Y coordinate where the mouse was last clicked
int prevButton;   // The last mouse button that was clicked

bool showAxis = true;   // If true, draw the main axes at origin

GLuint* texture_ids;

// window parameters
int window_width = 800, window_height = 600;
float window_aspect = window_width / static_cast<float>(window_height);

bool scene_lighting;

// Lighting configurations
GLfloat light_position[] = {0.f, 50.f, 0.f};
GLfloat light_ambient[] = {0.25, 0.25, 0.25};
GLfloat light_diffuse[] = {0.25, 0.25, 0.25};
GLfloat light_specular[] = {1.f, 1.f, 1.f};

// Material configurations
GLfloat mat_ambient[] = {0.5, 0.5, 0.5};
GLfloat mat_diffuse[] = {0.5, 0.5, 0.5};
GLfloat mat_specular[] = {1.f, 1.f, 1.f};
GLfloat mat_shininess[] = {100.f};

// Forward declarations of functions
void Init();

void ComputeLookAt();
void SetCamera();
void SetDrawMode();
void SetLighting();
void SetProjection();

void MouseButton(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void Keyboard(unsigned char key, int x, int y);

void ComputeLookAt() {
  BBox bb = mesh.mesh.WorldBound();

  // Recompute camera positions
//   center = (bb.pMax + bb.pMin) / 2;
}

void SetCamera() {
  // TODO call gluLookAt such that mesh fits nicely in viewport.
  // mesh.bb() may be useful.
  printf("Setting camera\n");
  printf("Eye: (%f %f %f)\n", eye.x, eye.y, eye.z);
  printf("Center is: (%f %f %f)\n", center.x, center.y, center.z);
  gluLookAt(eye.x, eye.y, eye.z,
            center.x, center.y, center.z,
            up.x, up.y, up.z);
}

void SetLighting() {
  glShadeModel(GL_FLAT);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);

  // Set light configurations for the global light source
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  // Set material lighting configurations
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void SetProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, window_aspect, 1, 1500);
}

void SetDrawMode() {
  glPolygonMode(GL_FRONT, GL_LINE);
  glPolygonMode(GL_BACK, GL_FILL);
}

/// Called by Display to draw the floor. Draw a checkerboard floor.
void DrawFloor() {
  // Save the modelling transform state
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  // Set modelling transform state to origin
  glLoadIdentity();

  int numSquares = 20;  // number of squares on each side
  int squareSize = 10;  // length of the side of each square

  // Draw the floor
  glBegin(GL_QUADS);
  for (int i = -numSquares/2; i < numSquares/2; i++) {
    for (int j = -numSquares/2; j < numSquares/2; j++) {
      // select color
      if ((i + j) % 2 == 0)
        glColor3f(0.f, 0.f, 0.f);   // black
      else
        glColor3f(1.f, 1.f, 1.f);   // white

      glVertex3f(i * squareSize, 0, j * squareSize);
      glVertex3f(i * squareSize, 0, (j+1) * squareSize);
      glVertex3f((i+1) * squareSize, 0, (j+1) * squareSize);
      glVertex3f((i+1) * squareSize, 0, j * squareSize);
    }
  }
  glEnd();

  // Restore the modelling transform state
  glPopMatrix();
}

void Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  SetProjection();

//   glMatrixMode(GL_MODELVIEW);
//   glLoadIdentity();

  SetLighting();
  SetCamera();
  SetDrawMode();

  // TODO set up lighting, material properties and render mesh.
  // Be sure to call glEnable(GL_RESCALE_NORMAL) so your normals
  // remain normalized throughout transformations.

  if (showAxis) DrawAxis();
//   DrawFloor();

  // Render the mesh
  mesh.mesh.accept(gl_renderer);

  glFlush();
  glutSwapBuffers();
}

void PrintMatrix(GLfloat* m) {
  cout.precision(2);
  int w = 6;
  for (int i = 0; i < 4; ++i) {
    cout << setprecision(2) << setw(w) << m[i] << " "
         << setprecision(2) << setw(w) << m[i+4] << " "
         << setprecision(2) << setw(w) << m[i+8] << " "
         << setprecision(2) << setw(w) << m[i+12] << " "
         << endl;
  }
  cout << endl;
}

void PrintMatrix(GLint matrix) {
  GLfloat m[16];
  glGetFloatv(matrix, m);
  PrintMatrix(m);
}

void PrintMatrix() {
  PrintMatrix(GL_MODELVIEW_MATRIX);
}

void LoadMatrix(GLfloat* m) {
  // transpose to column-major
  for (int i = 0; i < 4; ++i) {
    for (int j = i; j < 4; ++j) {
      swap(m[i*4+j], m[j*4+i]);
    }
  }
  glLoadMatrixf(m);
}

void MultMatrix(GLfloat* m) {
  // transpose to column-major
  for (int i = 0; i < 4; ++i) {
    for (int j = i; j < 4; ++j) {
      swap(m[i*4+j], m[j*4+i]);
    }
  }
  glMultMatrixf(m);
}

/// Called before any parsing or rendering occurs
void Init() {
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  // resize the window
  window_aspect = window_width/static_cast<float>(window_height);

  // Compute the initial position of the camera
  eye = Point(2, 2, 5);
  up = Vector(0, 1, 0);
  center = Point();

  SetProjection();
}

void DrawAxis() {
  const Vec3f c = {{0, 0, 0}};
  const float L = 1;
  const Vec3f X = {{L, 0, 0}}, Y = {{0, L, 0}}, Z = {{0, 0, L}};

  // Disable lighting
  glDisable(GL_LIGHTING);
  glLineWidth(4);

  glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3fv(c.x);
    glVertex3fv((c+X).x);
    glColor3f(0, 1, 0);
    glVertex3fv(c.x);
    glVertex3fv((c+Y).x);
    glColor3f(0, 0, 1);
    glVertex3fv(c.x);
    glVertex3fv((c+Z).x);
  glEnd();

  // Re-enable lighting
  glEnable(GL_LIGHTING);
}

/// Called whenever a mouse button is pressed
void MouseButton(int button, int state, int x, int y) {
  // TODO implement arc ball and zoom
  if (button == 3) /* mouse wheel up */ {
    if (state == GLUT_DOWN) {
      eye = center + ((eye - center) * 0.95);
      ComputeLookAt();
    }
  } else if (button == 4) /* mouse wheel down */ {
    if (state == GLUT_DOWN) {
      eye = center + ((eye - center) * 1.05);
      ComputeLookAt();
    }
  } else if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      prevX = x;
      prevY = y;
      prevButton = GLUT_LEFT_BUTTON;
    } else if (state == GLUT_UP) {
      prevButton = -1;
    }
  }
  glutPostRedisplay();
}

/// Called whenever a mouse button is pressed the mouse is moved
void MouseMotion(int x, int y) {
  // TODO implement arc ball and zoom
  if (prevButton == GLUT_LEFT_BUTTON) {
    float deltaX = (prevX - x) / static_cast<float>(window_width);
    float deltaY = (prevY - y) / static_cast<float>(window_height);
    eye = Rotate(-deltaY, Cross(up, center - eye))(eye);
    eye = RotateY(2 * deltaX)(eye);
    ComputeLookAt();
    prevX = x;
    prevY = y;
  }
  glutPostRedisplay();
}

/// Called whenever a normal key is pressed
void Keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'q':
    case 27:  // esc
      exit(0);
      break;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << endl;
    cout << "Usage: ./viewer (filename.obj | -s) [-l]" << endl;
    cout << endl;
    cout << "To load data/test.obj: ./viewer data/test.obj" << endl;
    cout << "To load a custom scene: ./viewer -s" << endl;
    cout << endl;
    return 0;
  }

  // Initialize GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(window_width, window_height);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Object viewer");
  glutMouseFunc(MouseButton);
  glutMotionFunc(MouseMotion);
  glutKeyboardFunc(Keyboard);
  glutDisplayFunc(Display);

  Init();

  if (string(argv[1]) == "-s") {
    cout << "Create scene" << endl;
  } else {
    string filename(argv[1]);
    cout << filename << endl;

    // Detect whether to fix the light source(s) to the camera or the world
    scene_lighting = false;
    if (argc > 2 && string(argv[2]) == "-l") {
      scene_lighting = true;
    }

    // Parse the obj file, compute the normals, read the textures

    ParseObj(filename, mesh);
    mesh.compute_normals();

    texture_ids = new GLuint[mesh.num_materials()];
    glGenTextures(mesh.num_materials(), texture_ids);

    for (int i = 0; i < mesh.num_materials(); ++i) {
      Material& material = mesh.material(i);
      material.LoadTexture(texture_ids[i]);
    }
  }

  glutMainLoop();

  return 0;
}
