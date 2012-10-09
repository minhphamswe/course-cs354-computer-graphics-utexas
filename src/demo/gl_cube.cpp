#include <demo/gl_cube.h>

void init(void)
{
    glClearColor(0,0,0,0);
    glShadeModel(GL_FLAT);
    glClear(GL_COLOR_BUFFER_BIT);
}

void DrawCube(void)
{
    glLoadIdentity();
    gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
    glBegin(GL_QUADS);

    //face in xy plane
    //glColor3f(0.82, 0.41, 0.12);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(5, 0, 0);
    glVertex3f(5, 5, 0);
    glVertex3f(0, 5, 0);

    //face in yz plane
    glColor3f(1, 0, 0);  // red
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 5);
    glVertex3f(0, 5, 0);
    glVertex3f(0, 5, 5);

    //face in zx plance
    glColor3f(0, 1, 0);  // green
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 5);
    glVertex3f(5, 0, 5);
    glVertex3f(5, 0, 0);

    //|| to xy plane.
    glColor3f(0, 0, 1);  // blue
    glVertex3f(0, 0, 5);
    glVertex3f(5, 0, 5);
    glVertex3f(5, 5, 5);
    glVertex3f(0, 5, 5);

    //|| to yz plane
    glColor3f(0.73, 0.58, 0.58);
    glVertex3f(0, 0 ,5);
    glVertex3f(5, 0, 5);
    glVertex3f(5, 5, 5);
    glVertex3f(0, 5, 5);

    //|| to zx plane
    glVertex3f(0.58, 0, 0.82);
    glVertex3f(0, 5, 0  );
    glVertex3f(0, 5, 5);
    glVertex3f(5, 5, 5);
    glVertex3f(5, 5, 0);
    glEnd();
    glFlush();
}


void reshape(int w,int h){
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1.5, 20);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    // Initialilze glut functions
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    // Register callback functions
    glutDisplayFunc(DrawCube);
    glutReshapeFunc(reshape);

    // Set clear color
    init();

    // Enter main loop
    glutMainLoop();
    return 0;
}
