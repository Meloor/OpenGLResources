/* Rotating cube with texture */

//#include "stdafx.h"
#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*ȫ�ֱ���*****************************************************************************/
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

/*������ر���*********************************************************************************/
GLfloat light0_pos[4] = { 0.90, 0.90, 2.25, 0.0 };//���ĸ�����Ϊ0��ʾ�����Թ�Դ

typedef struct materialStruct {//�������Խṹ��
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} materialStruct;

typedef struct lightingStruct {//��Դ���Խṹ��
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
} lightingStruct;

//�������ֲ���
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

//�������ֹ�Դ
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

//����������(��ɫ)���㣬������ҪΪÿ����ָ��һ������
GLfloat normals[][3] = { { 0.0,0.0,-1.0 },{ 0.0,1.0,0.0 },
{ -1.0,0.0,0.0 },{ 1.0,0.0,0.0 },{ 0.0,0.0,1.0 },
{ 0.0,-1.0,0.0 } };

/*����*****************************************************************************/
void polygon(int a, int b, int c, int d)
{
	/* draw a polygon via list of vertices */
	glShadeModel(GL_FLAT);
	glBegin(GL_POLYGON);
		glColor4fv(colors[a]);//������ɫ
		// �����øö�����������겢��ֱ���´ε���  glTexCoord*()ǰ����ǰ�������걣�ֲ��䡣	
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

void spinCube()//ÿ֡����
{

	/* Idle callback, spin cube 2 degrees about selected axis */

	theta[axis] += 0.02;
	if (theta[axis] > 360.0) theta[axis] -= 360.0;
	/* display(); */
	glutPostRedisplay();//����display����
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
		{	//������8��1000
			c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
			image[i][j][0] = (GLubyte)c;
			image[i][j][1] = (GLubyte)c;
			image[i][j][2] = (GLubyte)c;
		}
	}

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);//���ö�ά����

	/*��ά�����塪������������ͼ�����ݴӴ������ڴ�д�뵽�����ڴ���
	void glTexImage2D(GLenum target,GL_TEXTURE_2D
					GLint level,�༶��������Mipmap����ϸ�ڲ��
					GLint  iformat,����ͼ��������Ԫ���ڲ���ʽ����ȡֵΪ GL_RGB��GL_RGBA����iformat��format���Բ�ͬ��
					GLsizei width, 
					GLsizei height,
					GLint border,����ͼ��ĳߴ�ͱ߽���
					GLenum format,pixels��������������ظ�ʽ����ȡGL_RGB�� GL_RGBA���μ�glDrawPixels()
					GLenum type,pixel������������������ͣ��μ�glDrawPixels()
					const GLvoid *pixels);ͼ�����ݵ��������飬�μ�glDrawPixels()��
	*/
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//�����������
	//���Ƿ�ʽ
	/*��������£���������ĸ�����λ��[0, 1]��
	�����glTexCoord*()�и��������������������[0, 1]  ��Χ��
		��ô������ӳ������н�ʹ���ظ�ģʽ��  GL_REPEAT������λģʽ
		��GL_CLAMP���Դ�����  [0,1]��Χ��ֵ��
	�ظ�ģʽ��GL_REPEAT���£����������s��t��r�������ظ�
		�������ֵΪ����ֱ��ʹ��С�����֣�����ֵΪ������ȡ������Ӻ�Ϊ������С������
	��λģʽ��GL_CLAMP���£����Գ���[0, 1]��Χ��ֵ������ λ����
		����������ֵΪ������ǿ��ȡΪ0����������ֵ����1
		����ǿ��ȡΪ1��*/
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);//��λģʽ
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);//��λģʽ
	//�˲���ʽ
	/*һ����˵������ͼ��Ϊ�����λ� �����Ρ�����ʵ�ʵ�����ӳ���У�
		����ӳ�䵽һ����� �λ������ϲ��任����Ļ����ʱ������ͼ
		�еĸ������� ��Ԫ����׼ȷ����Ļ�еĸ�������һһ��Ӧ��*/
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//����Ԫ�ķŴ�
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//����Ԫ����С

	/*����************************************************************************************/
	glEnable(GL_LIGHTING);//��������ģʽ
	glEnable(GL_LIGHT0);//������Դ0

	currentMaterials = &brassMaterials;//����Ĭ�ϲ���

											//���ò��ʶԹ�ķ�������
	glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);//������
	glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);//������
	glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);//���淴��
	glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);//�Զ�ϵ���������ļ��г̶�

	currentLighting = &whiteLighting;//����Ĭ�Ϲ�Դ

									 //���ù�Դ����
	glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);//������
	glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);//������
	glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);//���淴��
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);//���ù�Դλ��
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
