#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


void Display();
void Resize(int w, int h);
void Keyboard(unsigned char c, int x, int y);
void Idle();

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Atom");
  
  glutDisplayFunc(Display);
  glutReshapeFunc(Resize);
  glutKeyboardFunc(Keyboard);
  glutIdleFunc(Idle);
}