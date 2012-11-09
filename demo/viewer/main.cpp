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

Point eye;          // The position of the camera
Point center;       // The center of the camera's view frustum
Vector up;          // The upward orientation of the camera
float fovY = 40.0;  // The field of view in the Y direction

// The co-tangent of fovY, used to calculate distance from eye to center
float distFactor = cos(Radian(fovY)) / sin(Radian(fovY));

Point prevEye;          // Location of eye when arcball is initiated
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

Vector ArcballContact(int x, int y);

void MouseButton(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void Keyboard(unsigned char key, int x, int y);

void ComputeLookAt() {
  printf("Calling ComputeLookAt\n");
  BBox bb = mesh.mesh.ObjectBound();

  // Recompute camera positions
  float diagExtent = Length(bb.pMax - bb.pMin) / 2;
  float dist = diagExtent * distFactor;

  eye = center + Vector(dist, dist, dist);
}

void SetCamera() {
  // TODO call gluLookAt such that mesh fits nicely in viewport.
  // mesh.bb() may be useful.
//   printf("Setting camera\n");
//   printf("Eye: (%f %f %f)\n", eye.x, eye.y, eye.z);
//   printf("Center is: (%f %f %f)\n", center.x, center.y, center.z);
  gluLookAt(eye.x, eye.y, eye.z,
            center.x, center.y, center.z,
            up.x, up.y, up.z);
}

void SetLighting() {
  glShadeModel(GL_SMOOTH);
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
  gluPerspective(fovY, window_aspect, 1, 1500);
}

void SetDrawMode() {
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_LINE);
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

  // TODO set up lighting, material properties and render mesh.
  // Be sure to call glEnable(GL_RESCALE_NORMAL) so your normals
  // remain normalized throughout transformations.

  float scale = 50;
//   glMatrixMode(GL_MODELVIEW);
//   glPushMatrix();
//   glLoadIdentity();
  glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(axis.x*scale, axis.y*scale, axis.z*scale);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(prevContact.x*scale, prevContact.y*scale, prevContact.z*scale);

    glColor3f(1, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(contact.x*scale, contact.y*scale, contact.z*scale);

    glColor3f(0, 1, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(eye.x*scale, eye.y*scale, eye.z*scale);
  glEnd();
//   glPopMatrix();
  
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

/// Called after parsing but before rendering occurs
void Init() {
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  // resize the window
  window_aspect = window_width/static_cast<float>(window_height);

  SetProjection();
  SetDrawMode();

  // Compute the initial position of the camera
  up = Vector(0, 1, 0);
  ComputeLookAt();
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

//   float radius = sqrt(3.0) / 3;
//   printf("Contact vector: %f %f %f\n", cx, cy, cz);
//   Vector ret = Vector(cx * radius, cy * radius, cz * radius);
//   printf("Contact vector length: %f\n", Length(ret));
//   return ret;
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
  //       prevX = x;
  //       prevY = y;
        prevEye = eye;
        prevButton = GLUT_LEFT_BUTTON;

        float top_matrix[4][4];
        float *top_matrix_ptr = &top_matrix[0][0];
        glGetFloatv(GL_MODELVIEW_MATRIX, top_matrix_ptr);

        orientation = Transform(Transpose(Matrix4x4(top_matrix)));
//         glMatrixMode(GL_MODELVIEW);
//         glPushMatrix();
//         glPushMatrix();
        prevContact = ArcballContact(x, y);
//         printf("PrevContact is %f %f %f\n", prevContact.x, prevContact.y, prevContact.z);
    }
  } else {    // On button released:
    if (button == GLUT_LEFT_BUTTON) {           /* left mouse button */
//       arcball = arcball;
//       float top_matrix[16];
//       float *top_matrix_ptr = &top_matrix[0];
//       glGetFloatv(GL_MODELVIEW_MATRIX, top_matrix_ptr);
//       glPopMatrix();
//       glPopMatrix();
//       glLoadMatrixf(top_matrix_ptr);
//       glMultMatrixf(top_matrix_ptr);
//       glPushMatrix();
//       glPushMatrix();
    }
    prevButton = -1;
  }
  glutPostRedisplay();
}

/// Called whenever a mouse button is pressed the mouse is moved
void MouseMotion(int x, int y) {
  // TODO implement arc ball and zoom
  if (prevButton == GLUT_LEFT_BUTTON) {
//     float deltaX = (prevX - x) / static_cast<float>(window_width);
//     float deltaY = (prevY - y) / static_cast<float>(window_height);
//     eye = Rotate(-deltaY, Cross(up, center - eye))(eye);
//     eye = RotateY(2 * deltaX)(eye);
    contact = ArcballContact(x, y);
    axis = Cross(prevContact, contact);

//     float angle = Length(contact - prevContact);
    float angle = Length(contact - Dot(contact, prevContact) * contact);
//     angle *= sensitivity;
//     printf("Contact is %f %f %f\n", contact.x, contact.y, contact.z);
//     printf("Axis: %f %f %f \t Angle: %f\n", axis.x, axis.y, axis.z, angle);
//     eye = Rotate(angle, axis)(prevEye);
    glMatrixMode(GL_MODELVIEW);
//     glPopMatrix();
//     glPushMatrix();
//     glRotatef(Degree(angle), axis.x, axis.y, axis.z) ;
    arcball = orientation * Rotate(angle, axis);
//     glMultTransposeMatrixf(reinterpret_cast<float*>(arcball.Matrix().m));
    glLoadTransposeMatrixf(reinterpret_cast<float*>(arcball.Matrix().m));
//     int depth;
//     glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &depth);
//     printf("Modelview Stack Depth: %d\n", depth);
    
//     glPushMatrix();
//     glPopMatrix();
//     glPushMatrix();

//     prevContact = contact;
//     ComputeLookAt();
//     prevX = x;
//     prevY = y;
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

  Init();

  glutMainLoop();

  return 0;
}
