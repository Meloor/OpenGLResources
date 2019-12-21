/* Rotating cube with color interpolation */
#include "stdafx.h"
#include <stdlib.h>
#include <algorithm>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
/*数据类型定义*********************************************************************/
//枚举变换模式
enum TRANSFORM {
	TARANSLATE = 100,
	ROTATE,
	SCALE
};
/*全局变量*********************************************************************/
//正方体
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
//四面体,很奇怪，只有加上下面的代码正方体才能显示出来
GLfloat vertices2[][3] = { { 1.0,0.0,0.0 },
{ 0.0,0.0,1.0 },
{ 0.0,1.0,0.0 },
{ 0.0,0.0,0.0 } };

GLfloat colors2[][3] = { { 1.0,0.0,0.0 },//点A，红色
{ 0.0,1.0,0.0 },//点B，绿色
{ 0.0,0.0,1.0 },//点C，蓝色
{ 1.0,1.0,0.0 } };//点O，黄色

static GLfloat theta[3] = { 0.0,0.0,0.0 };
static GLint axis = 2;

TRANSFORM transform = TARANSLATE;//默认旋转模式

int display_num = 1;
int win_height;
int win_width;

int dx = 0, dy = 0;
float translate_speed = 1 / 100.0f;//平移系数
float rotate_speed = 1 / 10.0f;//旋转
float scale_speed = 1 / 100.0f;//缩放

float tra[3] = { 0.0,0.0,0.0 };//总平移量
float rot[4] = { 0.0,0.0,0.0,0.0 };//总旋转量
float sca[3] = { 1.0,1.0,1.0 };//总缩放量

							   /*函数声明*********************************************************************/
void display(void);
void rehsape(int w, int h);
void idle();
void mouse(int btn, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void cube();
/*图元绘制函数*********************************************************************/
void cube() {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//平面着色模式,在绘制时，对于每个多边形，只有最后一个颜色值将被使用
	glShadeModel(GL_FLAT);
	//默认的着色模式是平滑类型的，如果每个点的颜色都不同，
	//opengl将用这些顶点的颜色值在每个多边形的表面内部进行插值

	glEnableClientState(GL_COLOR_ARRAY);//启用颜色数组
	glEnableClientState(GL_VERTEX_ARRAY);//启用顶点数组

										 //提供数组信息
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	//存储顶点的索引值
	GLubyte indices[] = { 0,3,2,1,
		2,3,7,6,
		3,0,4,7,
		1,2,6,5,
		4,5,6,7,
		5,4,0,1 };

	//进行一次绘制,使用类型GL_QUADS,每4个连续的顶点绘制一个新的四边形
	//执行该函数时，所有被启用的数组将会被绘制
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_COLOR_ARRAY);//关闭颜色数组
	glDisableClientState(GL_VERTEX_ARRAY);//关闭顶点数组
}
/**************************************************************************************/
void mytransform() {
	/*屏幕坐标系的原点在左上角，转换后的opengl坐标系原点在左下角
	dx>0, x2在右边，是往右滑的
	dy>0, y2在上边，是往上滑的
	*/
	if (transform == TARANSLATE) {
		float x = dx*translate_speed;
		float y = dy*translate_speed;
		tra[0] += x;
		tra[1] += y;
		glTranslatef(tra[0], tra[1], tra[2]);
		printf("平移(%.2f,%.2f)->(%2f,%2.f)\n", x, y, tra[0], tra[1]);
	}
	if (transform == ROTATE) {//旋转的叠加
		float x = dx*rotate_speed;
		float y = dy*rotate_speed;
		float theta = fabs(x)>fabs(y) ? x : y;
		//绕垂直轴旋转,世界坐标的y轴
		if (abs(dx) > abs(dy)) {
			rot[0] = rot[1] = rot[2] = 0;
			rot[1] = 1.0f;
		}//绕水平轴旋转，世界坐标的x轴
		else {
			rot[0] = rot[1] = rot[2] = 0;
			rot[0] = 1.0f;
		}
		glTranslatef(tra[0], tra[1], tra[2]);//平移回原位置
		glRotatef(theta, rot[0], rot[1], rot[2]);//进行旋转
		glTranslatef(-tra[0], -tra[1], -tra[2]);//先平移到原点
	}
	if (transform == SCALE) {
		float d = abs(dx) > abs(dy) ? dx : dy;
		d *= scale_speed;
		if (d > 0) {//放大
			sca[0] = sca[1] = sca[2] *= (1 + d);
			printf("放大%.2f\n", (1 + d));
		}//缩小
		else {
			d = fabs(d);
			sca[0] = sca[1] = sca[2] *= 1 / (1 + d);
			printf("缩小%.2f\n", 1 / (1 + d));
		}
		glScalef(sca[0], sca[1], sca[2]);
	}
}
/* 该函数实现具体的平移、旋转、缩放。根据变换模式进行以下变换：
* 平移，按住鼠标左键，然后拖动，拖动距离决定平移距离。
*		x轴偏移，y轴偏移。
*		只计算偏移大的轴。
* 旋转，按住鼠标左键，然后拖动，拖动距离决定旋转的角度。
*		y轴偏移值绕着水平方向旋转，x轴偏移值绕着垂直方向旋转。
*		只计算偏移大的轴。
* 缩放，按住鼠标左键，然后拖动，拖动距离决定缩放的大小
*		往右上是放大，左下是缩小。
*		只计算偏移大的轴。
*
*/
void mouse(int btn, int state, int x, int y)
{
	static int x1, y1, x2, y2;
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		x1 = x;
		y1 = win_height - y;//转换为opengl坐标
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		x2 = x;
		y2 = win_height - y;//转换为opengl坐标
		dx = x2 - x1;
		dy = y2 - y1;
		glutPostRedisplay();
	}
}
//键盘切换变换模式
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

	if (transform != ROTATE)glPushMatrix();//旋转只能只用矩阵来叠加
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
	glClearColor(0.0, 0.0, 0.0, 0.0);//设置背景色为白色
	glColor3f(1.0, 1.0, 1.0);//设置绘制颜色为黑色
	printf("W:平移 E:旋转 R:缩放\n拖动鼠标进行相应的变换\n(目前旋转还没有做到叠加之前的旋转变换，有点小问题)\n");
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
