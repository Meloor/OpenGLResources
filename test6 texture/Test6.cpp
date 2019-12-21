/* Rotating cube with texture */

//#include "stdafx.h"
#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*全局变量*****************************************************************************/
GLfloat vertices[][3] = { { -1.0,-1.0,-1.0 },{ 1.0,-1.0,-1.0 },
{ 1.0,1.0,-1.0 },{ -1.0,1.0,-1.0 },{ -1.0,-1.0,1.0 },
{ 1.0,-1.0,1.0 },{ 1.0,1.0,1.0 },{ -1.0,1.0,1.0 } };

GLfloat colors[][4] = { { 0.0,0.0,0.0,0.5 },{ 1.0,0.0,0.0,0.5 },
{ 1.0,1.0,0.0,0.5 },{ 0.0,1.0,0.0,0.5 },{ 0.0,0.0,1.0,0.5 },
{ 1.0,0.0,1.0,0.5 },{ 1.0,1.0,1.0,0.5 },{ 0.0,1.0,1.0,0.5 } };

//GLfloat colors[][4] = { { 0.0,0.0,0.0,1 },{ 1.0,0.0,0.0,1 },
//{ 1.0,1.0,0.0,1 },{ 0.0,1.0,0.0,1 },{ 0.0,0.0,1.0,1 },
//{ 1.0,0.0,1.0,1 },{ 1.0,1.0,1.0,1 },{ 0.0,1.0,1.0,1 } };

GLubyte image[64][64][3];

static GLfloat theta[] = { 0.0,0.0,0.0 };
static GLint axis = 2;

/*光照相关变量*********************************************************************************/
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

//GLfloat vertices[][3] = { { -1.0,-1.0,-1.0 },{ 1.0,-1.0,-1.0 },
//{ 1.0,1.0,-1.0 },{ -1.0,1.0,-1.0 },{ -1.0,-1.0,1.0 },
//{ 1.0,-1.0,1.0 },{ 1.0,1.0,1.0 },{ -1.0,1.0,1.0 } };

//对于明暗度(着色)计算，我们需要为每个面指定一个法线
GLfloat normals[][3] = { { 0.0,0.0,-1.0 },{ 0.0,1.0,0.0 },
{ -1.0,0.0,0.0 },{ 1.0,0.0,0.0 },{ 0.0,0.0,1.0 },
{ 0.0,-1.0,0.0 } };

/*函数*****************************************************************************/
void polygon(int a, int b, int c, int d)
{
	/* draw a polygon via list of vertices */
	glShadeModel(GL_FLAT);
	glBegin(GL_POLYGON);
		glColor4fv(colors[a]);//设置颜色
		// 来设置该顶点的纹理坐标并且直到下次调用  glTexCoord*()前，当前纹理坐标保持不变。	
		glTexCoord2f(0.0, 0.0);
		glVertex3fv(vertices[a]);

		glColor4fv(colors[b]);
		glTexCoord2f(0.0, 1.0);
		glVertex3fv(vertices[b]);

		glColor4fv(colors[c]);
		glTexCoord2f(1.0, 1.0);
		glVertex3fv(vertices[c]);

		glColor4fv(colors[d]);
		glTexCoord2f(1.0, 0.0);
		glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube(void)
{

	/* map vertices to faces */
	glNormal3fv(normals[0]);
	polygon(0, 3, 2, 1);
	glNormal3fv(normals[1]);
	polygon(2, 3, 7, 6);
	glNormal3fv(normals[2]);
	polygon(3, 0, 4, 7);
	glNormal3fv(normals[3]);
	polygon(1, 2, 6, 5);
	glNormal3fv(normals[4]);
	polygon(4, 5, 6, 7);
	glNormal3fv(normals[5]);
	polygon(5, 4, 0, 1);

}



void display(void)
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

void spinCube()//每帧调用
{

	/* Idle callback, spin cube 2 degrees about selected axis */

	theta[axis] += 0.02;
	if (theta[axis] > 360.0) theta[axis] -= 360.0;
	/* display(); */
	glutPostRedisplay();//调用display函数
}

void mouse(int btn, int state, int x, int y)
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

void key(unsigned char k, int x, int y)
{
	if (k == '1') glutIdleFunc(spinCube);
	if (k == '2') glutIdleFunc(NULL);
}
void init() {
	int i, j, c;
	for (i = 0; i<64; i++)
	{
		for (j = 0; j<64; j++)
		{	//二进制8：1000
			c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
			image[i][j][0] = (GLubyte)c;
			image[i][j][1] = (GLubyte)c;
			image[i][j][2] = (GLubyte)c;
		}
	}

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);//启用二维纹理

	/*二维纹理定义——创建纹理并将图像数据从处理器内存写入到纹理内存中
	void glTexImage2D(GLenum target,GL_TEXTURE_2D
					GLint level,多级渐进纹理（Mipmap）的细节层次
					GLint  iformat,纹理图像中纹理单元的内部格式，常取值为 GL_RGB或GL_RGBA，但iformat和format可以不同。
					GLsizei width, 
					GLsizei height,
					GLint border,纹理图像的尺寸和边界宽度
					GLenum format,pixels中像素数组的像素格式，常取GL_RGB或 GL_RGBA，参见glDrawPixels()
					GLenum type,pixel中像素数组的数据类型，参见glDrawPixels()
					const GLvoid *pixels);图像数据的像素数组，参见glDrawPixels()。
	*/
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//设置纹理参数
	//覆盖方式
	/*正常情况下，纹理坐标的各分量位于[0, 1]。
	如果在glTexCoord*()中给出的纹理坐标分量超出[0, 1]  范围，
		那么在纹理映射过程中将使用重复模式（  GL_REPEAT）或箝位模式
		（GL_CLAMP）以处理超出  [0,1]范围的值。
	重复模式（GL_REPEAT）下，纹理可以在s，t，r方向上重复
		，即如果值为正，直接使用小数部分，若该值为负，则取与其相加和为正的最小整数。
	箝位模式（GL_CLAMP）下，将对超出[0, 1]范围的值进行箝 位处理，
		即纹理坐标值为负，则强制取为0；纹理坐标值超出1
		，则强制取为1。*/
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);//箝位模式
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);//箝位模式
	//滤波方式
	/*一般来说，纹理图像为正方形或 长方形。但在实际的纹理映射中，
		当它映射到一个多边 形或曲面上并变换到屏幕坐标时，纹理图
		中的各个纹理 单元很难准确与屏幕中的各个像素一一对应。*/
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//纹理单元的放大
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//纹理单元的缩小

	/*光照************************************************************************************/
	glEnable(GL_LIGHTING);//开启光照模式
	glEnable(GL_LIGHT0);//开启光源0

	currentMaterials = &brassMaterials;//设置默认材质

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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("colorcube");

	/* need both double buffering and z buffer */

	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(spinCube);
	glutMouseFunc(mouse);
	glutKeyboardFunc(key);

	init();
	glutMainLoop();
}
