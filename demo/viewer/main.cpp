#include <src/core/common.h>
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

Point light;
Point eye;          // The position of the camera
Point center;       // The center of the camera's view frustum
Vector up;          // The upward orientation of the camera
float fovY = 40.0;  // The field of view in the Y direction

// The co-tangent of fovY, used to calculate distance from eye to center
float distFactor = cos(Radian(fovY)) / sin(Radian(fovY));

int prevX;              // The X coordinate where the mouse was last clicked
int prevY;              // The Y coordinate where the mouse was last clicked
int prevButton;         // The last mouse button that was clicked

Transform arcball;      // Arcball rotation transform
Transform orientation;  // Orientation of the model

// Arcball parameters
Vector prevContact;     // Previous point of contact to Origin
Vector contact;         // Current point of contact to Origin
Vector axis;            // Axis of rotation
float sensitivity = 1;  // Sensitivity of arcball rotation

GLuint* texture_ids;

// window parameters
int window_width = 800, window_height = 600;
float window_aspect = window_width / static_cast<float>(window_height);

bool scene_lighting;

// Lighting configurations
Point light_position = Point(120.f, 150.f, 120.f);
GLfloat light_ambient[] = {0.3f, 0.3f, 0.3f};
GLfloat light_diffuse[] = {0.6f, 0.6f, 0.6f};
GLfloat light_specular[] = {1.0f, 1.0f, 1.0f};

// Forward declarations of functions
void Init();

void InitCamera();
void InitLighting();

void UpdateCamera();
void UpdateLighting();

void SetProjection();

Vector ArcballContact(int x, int y);

void MouseButton(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void Keyboard(unsigned char key, int x, int y);

void InitCamera() {
  BBox bb = mesh.mesh[0].ObjectBound();

  // Recompute camera positions
  float diagExtent = Length(bb.pMax - bb.pMin) / 2;
  float dist = diagExtent * distFactor;

  eye = center + Vector(dist, dist, dist);
}

/// Called by Init() to set up the calculate the projection matrix
void UpdateCamera() {
  gluLookAt(eye.x, eye.y, eye.z,
            center.x, center.y, center.z,
            up.x, up.y, up.z);
}

/// Called by Display() to update lighting
void UpdateLighting() {
  if (!scene_lighting) {
    light_position = arcball.Invert(eye);
    glLightfv(GL_LIGHT0, GL_POSITION, &light_position.x);
  } else {
//     glLightfv(GL_LIGHT0, GL_POSITION, &light.x);
  }
}

/// Called by Init() to initialize lighting
void InitLighting() {
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
//   glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);

  // Set light configurations for the global light source
//   light = Point(150, 120, 150);
//   light = Point(eye.x, eye.y, eye.z);
  light = Point(0, 0, 150);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

//   glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
//   glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
//   glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
//   glLightfv(GL_LIGHT1, GL_POSITION, &light.x);
}

void SetProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fovY, window_aspect, 1, 1500);
}

void Display() {
//   printf("Display called\n");
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // These have to go together
  SetProjection();
  UpdateCamera();

  UpdateLighting();

  // Render the mesh
  mesh.mesh[0].Render(gl_renderer);

  glFlush();
  glutSwapBuffers();
}

/// Called after parsing but before rendering occurs
void Init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  glEnable(GL_RESCALE_NORMAL);

  // resize the window
  window_aspect = window_width/static_cast<float>(window_height);

  // Compute the initial position of the camera
  up = Vector(0, 1, 0);
  SetProjection();
  InitCamera();

  // Set light positions
  light_position = eye;
  InitLighting();
}

/// Called to obtain the vector of contact on the arcball
Vector ArcballContact(int x, int y) {
  float cx, cy, cz, sq_cz;
  cx = 2 * x / static_cast<float>(window_width) - 1;
  cy = 2 * y / static_cast<float>(window_height) - 1;
  sq_cz = 1.0 - cx*cx - cy*cy;
  if (sq_cz < 0)
    cz = -sqrt(-sq_cz);
  else
    cz = sqrt(sq_cz);

  return orientation.Invert(Normalize(Vector(cx, -cy, cz)));
}

/// Called whenever a mouse button is pressed
void MouseButton(int button, int state, int x, int y) {
  // TODO implement arc ball and zoom

  if (state == GLUT_DOWN) {   // On button pressed:
    if (button == 3) {                          /* mouse scroll up */
      eye = center + ((eye - center) * 0.95);

    } else if (button == 4) {                   /* mouse scroll down */
      eye = center + ((eye - center) * 1.05);

    } else if (button == GLUT_LEFT_BUTTON) {    /* left mouse button */
      // Save button pressed and contact vector
      prevButton = GLUT_LEFT_BUTTON;

      // Save top modelview matrix
      float top_matrix[4][4];
      float *top_matrix_ptr = &top_matrix[0][0];
      glGetFloatv(GL_MODELVIEW_MATRIX, top_matrix_ptr);
      orientation = Transform(Transpose(Matrix4x4(top_matrix)));

      prevContact = ArcballContact(x, y);

    } else if (button == GLUT_RIGHT_BUTTON) {
      prevY = y;
      prevButton = GLUT_RIGHT_BUTTON;
    }
  } else {    // On button released:
//     if (button == GLUT_RIGHT_BUTTON) {           /* left mouse button */
//     }
    prevButton = -1;
  }
  glutPostRedisplay();
}

/// Called whenever a mouse button is pressed the mouse is moved
void MouseMotion(int x, int y) {
  // TODO implement zoom
  if (prevButton == GLUT_LEFT_BUTTON) {
    // Calculate new contact vector
    contact = ArcballContact(x, y);

    // Calculate new rotation transformation matrix
    axis = Cross(prevContact, contact);
    float angle = Length(contact - Dot(contact, prevContact) * contact);
    arcball = orientation * Rotate(angle, axis);

    // Load transformation matrix into modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadTransposeMatrixf(reinterpret_cast<float*>(arcball.Matrix().m));

  } else if (prevButton == GLUT_RIGHT_BUTTON) {
    float zoomFactor = (y - prevY);
    zoomFactor /= static_cast<float>(window_height);
    zoomFactor += 1;
    eye = center + ((eye - center) * zoomFactor);
    prevY = y;
  }
  glutPostRedisplay();
}

/// Called whenever a normal key is pressed
void Keyboard(unsigned char key, int x, int y) {
  if (key == 'q' || key == 27)
    exit(0);
  else if (key == 'l')
    scene_lighting = !scene_lighting;
  else if (key == '+')
    fovY += 10.0;
  else if (key == '-')
    fovY -= 10.0;
  glutPostRedisplay();
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
      ::Material& material = mesh.material(i);
      material.LoadTexture(texture_ids[i]);
    }
  }

  Init();

  glutMainLoop();

  return 0;
}
