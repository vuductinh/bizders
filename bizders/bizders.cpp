//http://www.glprogramming.com/red/chapter12.html

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

const int numGrid = 2;
GLfloat ctrlpoints1[4][3] = {
        { -4.0, -4.0, 0.0}, { -2.0, 4.0, 0.0},
        {2.0, -4.0, 0.0}, {4.0, 4.0, 0.0} };
GLfloat ctrlpoints[4][3] = {
        { -4.0, -4.0, 0.0}, { -2.0, 4.0, 0.0},
        {4.0, 4.0, 0.0}, {2.0, -4.0, 0.0} };
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);

    // Set up grid for evaluator.
    // This only needs to be done when using glEvalMesh1.
    glMapGrid1d(numGrid, 0.0, 1.0);
}


void display(void)
{
    int i;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

#if 1
    glEvalMesh1(GL_LINE, 0, numGrid);
#else
    glBegin(GL_LINE_STRIP);
    for (i = 0; i <= numGrid; i++)
        glEvalCoord1f((GLfloat)i / 30.0);
    glEnd();
#endif

    /* Displays the control points as dots. */
    glPointSize(5.0);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for (i = 0; i < 4; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-5.0, 5.0, -5.0 * (GLfloat)h / (GLfloat)w,
            5.0 * (GLfloat)h / (GLfloat)w, -5.0, 5.0);
    else
        glOrtho(-5.0 * (GLfloat)w / (GLfloat)h,
            5.0 * (GLfloat)w / (GLfloat)h, -5.0, 5.0, -5.0, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}