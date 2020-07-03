
#include <windows.h> 
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>


float snake[100][2];
int direction = 0;
int count = 1;
float foodx=5, foody=0;
boolean end = false;

void myinit()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 20, 0, 20);
	glMatrixMode(GL_MODELVIEW);
	snake[0][0] = 0.0;
	snake[0][1] = 0.0;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(foodx, foody);
	glVertex2f(foodx + 1, foody);
	glVertex2f(foodx + 1, foody + 1);
	glVertex2f(foodx, foody + 1);
	glEnd();

	
	glColor3f(0.0f, 1.0f, 0.0f);
	for (int i = 0; i < count; i++) {
		glBegin(GL_QUADS);
		glVertex2f(snake[i][0],snake[i][1]);
		glVertex2f(snake[i][0] + 0.9, snake[i][1]);
		glVertex2f(snake[i][0] + 0.9, snake[i][1] + 0.9);
		glVertex2f(snake[i][0], snake[i][1] + 0.9);
		glEnd();
	}

	
	glFlush();
}

void timer(int i) {
	
	if (snake[0][0] == foodx && snake[0][1] == foody) {
		count++;
		foodx = rand() % 20;
		foody = rand() % 20;
	}
	
	for (int i = count - 1; i > 0; i--) {
			snake[i][0] = snake[i - 1][0];
			snake[i][1] = snake[i - 1][1];
		}

	if (direction == 0){
	if (snake[i][0] > 19)
		snake[i][0] = -1;
	snake[i][0] = snake[i][0] + 1; }
	
	if (direction == 3) {
		if (snake[i][0] < 0)
			snake[i][0] = 20;
		snake[i][0] = snake[i][0] -1;
	}

	else if (direction == 1) {
		if (snake[i][1] > 19)
			snake[i][1] = -1;
		snake[i][1] = snake[i][1] + 1;
	}
	if (direction == 2) {
		if (snake[i][1] < 0)
			snake[i][1] = 20;
		snake[i][1] = snake[i][1] - 1;
	}
		
	glutPostRedisplay();

	for (int i = 1; i < count; i++) {
		if (snake[0][0] == snake[i][0] & snake[0][1] == snake[i][1])
			end = true;
	}

	if (end == false || count==50) {
		glutTimerFunc(100, timer, 0);
	}
}

void arrow(int key, int a, int b) {
	if (key == GLUT_KEY_RIGHT)
		direction = 0;
	else if (key == GLUT_KEY_UP)
		direction = 1;
	else if (key == GLUT_KEY_DOWN)
		direction = 2;
	else if (key == GLUT_KEY_LEFT)
		direction = 3;
	
}

void keys(unsigned char key, int a, int b) {
	if (key == 'a') {
		count++;
	}
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutCreateWindow("TEST");
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	myinit();
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(500, 500);
	glutDisplayFunc(display);
	glutTimerFunc(1000, timer, 0);
	glutSpecialFunc(arrow);
	glutKeyboardFunc(keys);
	glutMainLoop();           
		return 0;
}
