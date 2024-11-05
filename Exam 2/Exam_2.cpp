#include <GL/glut.h>
#include <cmath>

GLfloat rotationAngle = 0.0f;

void drawCylinder(GLfloat radius, GLfloat height) {
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);

    // Цилиндр
    gluCylinder(quadric, radius, radius, height, 30, 30);
    gluDeleteQuadric(quadric);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glRotatef(-20.0, 1.0, 0.0, 0.0);
    glRotatef(rotationAngle, 0.0, 1.0, 0.0);

    // Куб
    glPushMatrix();
    glTranslatef(0.0, -0.5, 0.0); 
    GLfloat brown[] = { 0.54, 0.27, 0.07, 1.0 }; 
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
    glutSolidCube(1.0); 
    glPopMatrix();

    // Конус
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0); 
    glRotatef(-90.0, 1.0, 0.0, 0.0); 
    GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 }; 
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
    glutSolidCone(0.6, 1.0, 30, 30); 
    glPopMatrix();

    // Шар
    glPushMatrix();
    glTranslatef(1.5, 0.5, 0.0); 
    GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 }; 
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
    glutSolidSphere(0.5, 30, 30); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5, 0.5, 0.0); 
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0.0);

    // Вертикальные линии
    for (int i = 0; i <= 360; i += 10) { 
        for (int j = -90; j <= 90; j += 20) { 
            GLfloat x_start = cos(i * M_PI / 180.0) * cos(j * M_PI / 180.0);
            GLfloat y_start = sin(j * M_PI / 180.0);
            GLfloat z_start = sin(i * M_PI / 180.0) * cos(j * M_PI / 180.0);
            GLfloat x_end = cos(i * M_PI / 180.0) * cos((j + 20) * M_PI / 180.0);
            GLfloat y_end = sin((j + 20) * M_PI / 180.0);
            GLfloat z_end = sin(i * M_PI / 180.0) * cos((j + 20) * M_PI / 180.0);
            glVertex3f(x_start, y_start, z_start); 
            glVertex3f(x_end, y_end, z_end);
        }
    }

    // Горизонтальные линии
    for (int j = -90; j <= 90; j += 10) {
        for (int i = 0; i <= 360; i += 20) { 
            GLfloat x_start = cos(i * M_PI / 180.0) * cos(j * M_PI / 180.0);
            GLfloat y_start = sin(j * M_PI / 180.0);
            GLfloat z_start = sin(i * M_PI / 180.0) * cos(j * M_PI / 180.0);
            GLfloat x_end = cos((i + 20) * M_PI / 180.0) * cos(j * M_PI / 180.0);
            GLfloat y_end = sin(j * M_PI / 180.0);
            GLfloat z_end = sin((i + 20) * M_PI / 180.0) * cos(j * M_PI / 180.0);
            glVertex3f(x_start, y_start, z_start); 
            glVertex3f(x_end, y_end, z_end); 
        }
    }
    glEnd();
    glPopMatrix();

    // Цилиндр
    glPushMatrix();
    glTranslatef(-2.0, -0.5, 0.0); 
    GLfloat blue[] = { 0.0, 0.0, 1.0, 1.0 }; 
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
    drawCylinder(0.3, 1.5); 
    glPopMatrix();

    glPopMatrix();
    glFlush();
}

void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    GLfloat aspect = GLfloat(w) / GLfloat(h);
    glLoadIdentity();
    if (w <= h) {
        glOrtho(-2.5, 2.5, -2.5 / aspect, 2.5 / aspect, -10.0, 10.0);
    }
    else {
        glOrtho(-2.5 * aspect, 2.5 * aspect, -2.5, 2.5, -10.0, 10.0);
    }
}

void handleKeys(unsigned char key, int x, int y) {
    if (key == 'r') {
        rotationAngle += 10.0f; 
        if (rotationAngle >= 360.0f) {
            rotationAngle -= 360.0f; 
        }
        glutPostRedisplay(); 
    }
}

void init() {
    GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat direction[] = { 1.0, 1.0, 1.0, 0.0 };

    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);

    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_POSITION, direction);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 600);
    glutCreateWindow("House with Cone Roof, Sphere with Lines, and Cylinder");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeys); 
    init();
    glutMainLoop();
}
