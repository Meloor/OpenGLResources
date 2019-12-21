/* Rotating cube with shading */
#include "stdafx.h"
#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLfloat light0_pos[4] = { 0.90, 0.90, 2.25, 0.0 };//第四个参数为0表示方向性光源

typedef struct materialStruct {//材质属性结构体
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} materialStruct;

typedef struct lightingStruct {//光源属性结构体
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
} lightingStruct;

//定义三种材质
materialStruct colorCubeMaterials = {
	{ 0.2, 0.2, 0.2, 1.0 },
	{ 0.8, 0.8, 0.8, 1.0 },
	{ 0.0, 0.0, 0.0, 1.0 },
	1.0
};

materialStruct brassMaterials = {
	{ 0.33, 0.22, 0.03, 1.0 },
	{ 0.78, 0.57, 0.11, 1.0 },
	{ 0.99, 0.91, 0.81, 1.0 },
	27.8
};

materialStruct redPlasticMaterials = {
	{ 0.3, 0.0, 0.0, 1.0 },
	{ 0.6, 0.0, 0.0, 1.0 },
	{ 0.8, 0.6, 0.6, 1.0 },
	32.0
};

materialStruct whiteShinyMaterials = {
	{ 1.0, 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 },
	100.0
};

//定义两种光源
lightingStruct whiteLighting = {
	{ 0.0, 0.0, 0.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0, 1.0 }
};

lightingStruct coloredLighting = {
	{ 0.2, 0.0, 0.0, 1.0 },
	{ 0.0, 1.0, 0.0, 1.0 },
	{ 0.0, 0.0, 1.0, 1.0 }
};


materialStruct *currentMaterials;
lightingStruct *currentLighting;

GLfloat vertices[][3] = { { -1.0,-1.0,-1.0 },{ 1.0,-1.0,-1.0 },
{ 1.0,1.0,-1.0 },{ -1.0,1.0,-1.0 },{ -1.0,-1.0,1.0 },
{ 1.0,-1.0,1.0 },{ 1.0,1.0,1.0 },{ -1.0,1.0,1.0 } };

//对于明暗度(着色)计算，我们需要为每个面指定一个法线
GLfloat normals[][3] = { { 0.0,0.0,-1.0 },{ 0.0,1.0,0.0 },
{ -1.0,0.0,0.0 },{ 1.0,0.0,0.0 },{ 0.0,0.0,1.0 },
{ 0.0,-1.0,0.0 } };

void polygon(int a, int b, int c, int d)
{
	/* draw a polygon via list of vertices */
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}
//由于法线也被视作一种几何图元，所以也将受到模型-视图矩阵的影响，而且将随立方体一起旋转,
void colorcube(void)
{
	/* map vertices to faces */
	glNormal3fv(normals[0]);
	polygon(0, 3, 2, 1);
	glNormal3fv(normals[1]);
	polygon(2, 3, 7, 6);
	glNormal3fv(normals[2]);
	polygon(0, 4, 7, 3);
	glNormal3fv(normals[3]);
	polygon(1, 2, 6, 5);
	glNormal3fv(normals[4]);
	polygon(4, 5, 6, 7);
	glNormal3fv(normals[5]);
	polygon(0, 1, 5, 4);
}

static GLfloat theta[] = { 0.0,0.0,0.0 };
static GLint axis = 2;

void display(void)//根据旋转参数动态的渲染cube
{
	/* display callback, clear frame buffer and z buffer,
	rotate cube and draw, swap buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	colorcube();
	glutSwapBuffers();
}

void spinCube()//旋转轴
{
	/* Idle callback, spin cube 2 degrees about selected axis */
	theta[axis] += 0.02;
	if (theta[axis] > 360.0) theta[axis] -= 360.0;
	/* display(); */
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)//更换旋转轴
{
	/* mouse callback, selects an axis about which to rotate */
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
			2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat)w / (GLfloat)h,
			2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void key(unsigned char k, int x, int y)//键盘切换材质和光源属性
{
	switch (k)
	{
	case '1':
		glutIdleFunc(NULL);//空闲回调函数设置为空
		break;
	case '2':
		glutIdleFunc(spinCube);//设置空闲回调函数
		break;
	case '3':
		currentMaterials = &redPlasticMaterials;//红色材质
		break;
	case '4':
		currentMaterials = &colorCubeMaterials;//彩色材质
		break;
	case '5':
		currentMaterials = &brassMaterials;//黄铜材质
		break;
	case '6':
		currentLighting = &whiteLighting;//白光
		break;
	case '7':
		currentLighting = &coloredLighting;//有颜色的光
		break;
	case 'q':
		exit(0);
		break;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
	glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);

	glutPostRedisplay();
}

void init()
{
	glEnable(GL_LIGHTING);//开启光照模式
	glEnable(GL_LIGHT0);//开启光源0

	currentMaterials = &redPlasticMaterials;//设置默认材质

											//设置材质对光的反射属性
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);//环境光
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);//漫反射
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);//镜面反射
	glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);//辉度系数，反射光的集中程度

	currentLighting = &whiteLighting;//设置默认光源

									 //设置光源属性
	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);//环境光
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);//漫反射
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);//镜面反射
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);//设置光源位置
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);

	/* need both double buffering and z buffer */

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("colorcube");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutIdleFunc(spinCube);
	glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */
	init();
	glutMainLoop();
}
