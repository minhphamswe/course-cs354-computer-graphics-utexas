#include <db_GLHelloWorld.h>

void init(void)
{
    glClearColor(0,0,0,0);
    glShadeModel(GL_FLAT);
}

void DrawCube(void)
{
    glLoadIdentity();
    gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
    glBegin(GL_QUADS);

    //face in xy plane
    glColor3f(0.82, 0.41, 0.12);//this the color with which complete cube is drawn. 
    glVertex3f(0,0 ,0 );
    glVertex3f(5, 0, 0);
    glVertex3f(5, 5, 0);
    glVertex3f(0, 5, 0);

    //face in yz plane
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 5);
    glVertex3f(0, 5, 0);
    glVertex3f(0, 5, 5);

    //face in zx plance
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0  );
    glVertex3f(0, 0, 5);
    glVertex3f(5, 0, 5);
    glVertex3f(5, 0, 0);

    //|| to xy plane.
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 5);
    glVertex3f(5, 0, 5);
    glVertex3f(5, 5, 5);
    glVertex3f(0, 5, 5);

    //|| to yz plane
    glColor3f(0.73, 0.58, 0.58);
    glVertex3f(0,0 ,5 );
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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1.5, 20);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);//we initizlilze the glut. functions
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(DrawCube);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
