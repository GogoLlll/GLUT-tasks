#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

static GLfloat rotationAngle = 0.0f;
static GLfloat armAngle = 0.0f;
static GLfloat legAngle = 0.0f;
static bool movingForward = true; 
float hatY = 0.0f;
bool hatGoingUp = true; 

void drawLimb(GLfloat length) {
    glPushMatrix();
    glScalef(0.2, length, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawJoint(GLfloat radius) {
    glutSolidSphere(radius, 20, 20);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    glRotatef(rotationAngle, 0.0, 1.0, 0.0);

    // Туловище
    glPushMatrix();
    glTranslatef(0.0, 1.49, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glColor3f(0.7, 0.5, 0.3);
    GLUquadric* quadric = gluNewQuadric();
    gluCylinder(quadric, 0.3, 0.3, 1.2, 20, 20);
    glPopMatrix();

    // Бантик
    glPushMatrix();
    glTranslatef(0.0, 1.39, 0.30);

    // Шар (середина бантика)
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    gluSphere(quadric, 0.1, 20, 20);
    glPopMatrix();

    // Левый конус
    glPushMatrix();
    glTranslatef(-0.03, 0.0, 0.0);
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f); 
    gluCylinder(quadric, 0.0, 0.1, 0.2, 20, 1); 
    glPopMatrix();

    // Правый конус
    glPushMatrix();
    glTranslatef(0.03, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0); 
    glColor3f(1.0f, 0.0f, 0.0f); 
    gluCylinder(quadric, 0.0, 0.1, 0.2, 20, 1); 
    glPopMatrix();

    glPopMatrix();

    // Голова
    glColor3f(0.8, 0.6, 0.5);
    glPushMatrix();
    glTranslatef(0.0, 1.75, 0.0);
    drawJoint(0.3);
    glPopMatrix();

    // Левая рука (верхняя часть)
    glColor3f(0.5, 0.3, 0.1);
    glPushMatrix();
    glTranslatef(-0.4, 1.2, 0.0);
    glRotatef(armAngle, 1.0, 0.0, 0.0);
    drawLimb(0.6);

    // Локтевой сустав
    glTranslatef(0.0, -0.4, 0.0);
    drawJoint(0.15);

    // Левая рука (нижняя часть)
    glTranslatef(0.0, -0.3, 0.1);
    glRotatef(-45.0, 1.0, 0.0, 0.0); 
    drawLimb(0.6);
    glPopMatrix();

    // Правая рука (верхняя часть)
    glColor3f(0.5, 0.3, 0.1);
    glPushMatrix();
    glTranslatef(0.4, 1.2, 0.0);
    glRotatef(-armAngle, 1.0, 0.0, 0.0);
    drawLimb(0.6);

    // Локтевой сустав
    glTranslatef(0.0, -0.4, 0.0);
    drawJoint(0.15);

    // Правая рука (нижняя часть)
    glTranslatef(0.0, -0.3, 0.1);
    glRotatef(-45.0, 1.0, 0.0, 0.0); 
    drawLimb(0.6);
    glPopMatrix();

    // Левая нога (верхняя часть)
    glColor3f(0.3, 0.2, 0.1);
    glPushMatrix();
    glTranslatef(-0.2, 0.0, 0.0);
    glRotatef(legAngle, 1.0, 0.0, 0.0); 
    drawLimb(0.7);

    // Колено
    glTranslatef(0.0, -0.5, 0.0);
    drawJoint(0.15);

    // Левая нога (нижняя часть)
    glTranslatef(0.0, -0.3, 0.1);
    glRotatef(-55.0, 1.0, 0.0, 0.0); 
    drawLimb(0.7);
    glPopMatrix();

    // Правая нога (верхняя часть)
    glColor3f(0.3, 0.2, 0.1);
    glPushMatrix();
    glTranslatef(0.2, 0.0, 0.0);
    glRotatef(-legAngle, 1.0, 0.0, 0.0); 
    drawLimb(0.7);

    // Колено
    glTranslatef(0.0, -0.5, 0.0);
    drawJoint(0.15);

    // Правая нога (нижняя часть)
    glTranslatef(0.0, -0.3, 0.1);
    glRotatef(-55.0, 1.0, 0.0, 0.0);
    drawLimb(0.7);
    glPopMatrix();

    // Шляпа (треугольная шляпа в виде конуса)
    glPushMatrix();
    glTranslatef(0.0, 1.9 + hatY, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f); 
    glutSolidCone(0.3, 0.5, 20, 10); 
    glPopMatrix();

    // Нос (маленький красный шар)
    glPushMatrix();
    glTranslatef(0.0, 1.7, 0.2);
    glColor3f(1.0f, 0.0f, 0.0f); 
    glutSolidSphere(0.1, 20, 20); 
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

void timer(int v) {
    if (movingForward) {
        armAngle += 2.0f;
        legAngle += 2.0f;
        if (armAngle > 30.0f) { 
            movingForward = false;
        }
    }
    else {
        armAngle -= 2.0f;
        legAngle -= 2.0f;
        if (armAngle < -30.0f) { 
            movingForward = true;
        }
    }

    if (hatGoingUp) {
        hatY += 0.005f;
        if (hatY > 0.1f) { 
            hatGoingUp = false;
        }
    }
    else {
        hatY -= 0.005f;
        if (hatY < 0.0f) {
            hatGoingUp = true;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, v);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'r' || key == 'R') {
        rotationAngle += 10.0f;
        if (rotationAngle >= 360.0f) {
            rotationAngle -= 360.0f;
        }
        glutPostRedisplay();
    }
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1, 0.1, 0.2, 1.0);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 1.5, 5.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Walking Animation like doctor Livsey");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000 / 60, timer, 0);
    glutMainLoop();
    return 0;
}
