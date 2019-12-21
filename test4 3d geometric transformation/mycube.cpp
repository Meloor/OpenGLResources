/* Rotating cube with color interpolation */
#include "stdafx.h"
#include <stdlib.h>
#include <algorithm>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
/*�������Ͷ���*********************************************************************/
//ö�ٱ任ģʽ
enum TRANSFORM {
	TARANSLATE = 100,
	ROTATE,
	SCALE
};
/*ȫ�ֱ���*********************************************************************/
//������
GLfloat vertices[][3] = { { -1.0,-1.0,-1.0 },
{ 1.0,-1.0,-1.0 },
{ 1.0,1.0,-1.0 },
{ -1.0,1.0,-1.0 },
{ -1.0,-1.0,1.0 },
{ 1.0,-1.0,1.0 },
{ 1.0,1.0,1.0 },
{ -1.0,1.0,1.0 } };

GLfloat colors[][3] = { { 1.0,0.0,0.0 },
{ 0.0,1.0,0.0 },
{ 0.0,0.0,1.0 },
{ 1.0,1.0,0.0 },
{ 0.0,1.0,1.0 },
{ 1.0,0.0,1.0 } };
//������,����֣�ֻ�м�������Ĵ��������������ʾ����
GLfloat vertices2[][3] = { { 1.0,0.0,0.0 },
{ 0.0,0.0,1.0 },
{ 0.0,1.0,0.0 },
{ 0.0,0.0,0.0 } };

GLfloat colors2[][3] = { { 1.0,0.0,0.0 },//��A����ɫ
{ 0.0,1.0,0.0 },//��B����ɫ
{ 0.0,0.0,1.0 },//��C����ɫ
{ 1.0,1.0,0.0 } };//��O����ɫ

static GLfloat theta[3] = { 0.0,0.0,0.0 };
static GLint axis = 2;

TRANSFORM transform = TARANSLATE;//Ĭ����תģʽ

int display_num = 1;
int win_height;
int win_width;

int dx = 0, dy = 0;
float translate_speed = 1 / 100.0f;//ƽ��ϵ��
float rotate_speed = 1 / 10.0f;//��ת
float scale_speed = 1 / 100.0f;//����

float tra[3] = { 0.0,0.0,0.0 };//��ƽ����
float rot[4] = { 0.0,0.0,0.0,0.0 };//����ת��
float sca[3] = { 1.0,1.0,1.0 };//��������

							   /*��������*********************************************************************/
void display(void);
void rehsape(int w, int h);
void idle();
void mouse(int btn, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void cube();
/*ͼԪ���ƺ���*********************************************************************/
void cube() {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//ƽ����ɫģʽ,�ڻ���ʱ������ÿ������Σ�ֻ�����һ����ɫֵ����ʹ��
	glShadeModel(GL_FLAT);
	//Ĭ�ϵ���ɫģʽ��ƽ�����͵ģ����ÿ�������ɫ����ͬ��
	//opengl������Щ�������ɫֵ��ÿ������εı����ڲ����в�ֵ

	glEnableClientState(GL_COLOR_ARRAY);//������ɫ����
	glEnableClientState(GL_VERTEX_ARRAY);//���ö�������

										 //�ṩ������Ϣ
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	//�洢���������ֵ
	GLubyte indices[] = { 0,3,2,1,
		2,3,7,6,
		3,0,4,7,
		1,2,6,5,
		4,5,6,7,
		5,4,0,1 };

	//����һ�λ���,ʹ������GL_QUADS,ÿ4�������Ķ������һ���µ��ı���
	//ִ�иú���ʱ�����б����õ����齫�ᱻ����
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_COLOR_ARRAY);//�ر���ɫ����
	glDisableClientState(GL_VERTEX_ARRAY);//�رն�������
}
/**************************************************************************************/
void mytransform() {
	/*��Ļ����ϵ��ԭ�������Ͻǣ�ת�����opengl����ϵԭ�������½�
	dx>0, x2���ұߣ������һ���
	dy>0, y2���ϱߣ������ϻ���
	*/
	if (transform == TARANSLATE) {
		float x = dx*translate_speed;
		float y = dy*translate_speed;
		tra[0] += x;
		tra[1] += y;
		glTranslatef(tra[0], tra[1], tra[2]);
		printf("ƽ��(%.2f,%.2f)->(%2f,%2.f)\n", x, y, tra[0], tra[1]);
	}
	if (transform == ROTATE) {//��ת�ĵ���
		float x = dx*rotate_speed;
		float y = dy*rotate_speed;
		float theta = fabs(x)>fabs(y) ? x : y;
		//�ƴ�ֱ����ת,���������y��
		if (abs(dx) > abs(dy)) {
			rot[0] = rot[1] = rot[2] = 0;
			rot[1] = 1.0f;
		}//��ˮƽ����ת�����������x��
		else {
			rot[0] = rot[1] = rot[2] = 0;
			rot[0] = 1.0f;
		}
		glTranslatef(tra[0], tra[1], tra[2]);//ƽ�ƻ�ԭλ��
		glRotatef(theta, rot[0], rot[1], rot[2]);//������ת
		glTranslatef(-tra[0], -tra[1], -tra[2]);//��ƽ�Ƶ�ԭ��
	}
	if (transform == SCALE) {
		float d = abs(dx) > abs(dy) ? dx : dy;
		d *= scale_speed;
		if (d > 0) {//�Ŵ�
			sca[0] = sca[1] = sca[2] *= (1 + d);
			printf("�Ŵ�%.2f\n", (1 + d));
		}//��С
		else {
			d = fabs(d);
			sca[0] = sca[1] = sca[2] *= 1 / (1 + d);
			printf("��С%.2f\n", 1 / (1 + d));
		}
		glScalef(sca[0], sca[1], sca[2]);
	}
}
/* �ú���ʵ�־����ƽ�ơ���ת�����š����ݱ任ģʽ�������±任��
* ƽ�ƣ���ס��������Ȼ���϶����϶��������ƽ�ƾ��롣
*		x��ƫ�ƣ�y��ƫ�ơ�
*		ֻ����ƫ�ƴ���ᡣ
* ��ת����ס��������Ȼ���϶����϶����������ת�ĽǶȡ�
*		y��ƫ��ֵ����ˮƽ������ת��x��ƫ��ֵ���Ŵ�ֱ������ת��
*		ֻ����ƫ�ƴ���ᡣ
* ���ţ���ס��������Ȼ���϶����϶�����������ŵĴ�С
*		�������ǷŴ���������С��
*		ֻ����ƫ�ƴ���ᡣ
*
*/
void mouse(int btn, int state, int x, int y)
{
	static int x1, y1, x2, y2;
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		x1 = x;
		y1 = win_height - y;//ת��Ϊopengl����
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		x2 = x;
		y2 = win_height - y;//ת��Ϊopengl����
		dx = x2 - x1;
		dy = y2 - y1;
		glutPostRedisplay();
	}
}
//�����л��任ģʽ
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
	case 'W': {
		transform = TARANSLATE;
		printf("translate mode\n");
		break;
	}
	case 'e':
	case 'E': {
		transform = ROTATE;
		printf("rotate mode\n");
		break;
	}
	case 'r':
	case 'R': {
		transform = SCALE;
		printf("scale mode\n");
		break;
	}
	case 27:
		exit(0);
		break;
	}
}
void display(void)
{
	printf("display %d times\n", display_num++);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (transform != ROTATE)glPushMatrix();//��תֻ��ֻ�þ���������
	mytransform();
	cube();
	if (transform != ROTATE)glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void idle()
{
	/* Idle callback, spin cube 2 degrees about selected axis */
	theta[axis] += 0.02;
	if (theta[axis] > 360.0) theta[axis] -= 360.0;
	/* display(); */
	glutPostRedisplay();
}
void rehsape(int w, int h)
{
	win_height = h;
	win_width = w;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
			2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat)w / (GLfloat)h,
			2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
	//GLfloat aspect = (float)w / (float)h;
	//gluPerspective(60.0f, aspect, 0.5f, 15.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);//���ñ���ɫΪ��ɫ
	glColor3f(1.0, 1.0, 1.0);//���û�����ɫΪ��ɫ
	printf("W:ƽ�� E:��ת R:����\n�϶���������Ӧ�ı任\n(Ŀǰ��ת��û����������֮ǰ����ת�任���е�С����)\n");
	if (transform == TARANSLATE)printf("translate mode\n");
	if (transform == ROTATE)printf("rotate mode\n");
	if (transform == SCALE)printf("scale mode\n");
}
void main(int argc, char **argv)
{
	glutInit(&argc, argv);

	/* need both double buffering and z buffer */

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(600, 200);
	glutCreateWindow("Test4");
	glutReshapeFunc(rehsape);
	glutDisplayFunc(display);
	//glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	init();
	glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */
	glutMainLoop();
}
