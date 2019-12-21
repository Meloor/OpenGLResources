#pragma once
#include "stdafx.h"
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>         /* glut.h includes gl.h and glu.h */
#endif
/*�ṹ�嶨��*********************************************************/
struct point {
	float x;
	float y;
	float z;
	point(float _x = 0, float _y = 0, float _z = 0) {
		x = _x;
		y = _y;
		z = _z;
	}
};
/*��������*********************************************************/
void tetrahedron();//ֱ��ʹ����Ե������㡢��һ����Դ��API����
void triangle(int a,int b,int c);
void tetrahedron2();//ʹ������
void tetrahedron3();//ʹ�ö�������
void display();
void reshape(int w, int h);
void init();
/*ȫ�ֱ���********************************************************/
//�����ĸ������ڷ���һ
point A = point(1, 0, 0);
point B = point(0, 0, 1);
point C = point(0, 1, 0);
point O = point(0, 0, 0);
//�����������������ڷ���������
GLfloat vertices[][3] = { { 1.0,0.0,0.0 },
						{ 0.0,0.0,1.0 },
						{ 0.0,1.0,0.0 },
						{ 0.0,0.0,0.0 } };

GLfloat colors[][3] = { { 1.0,0.0,0.0 },//��A����ɫ
						{ 0.0,1.0,0.0 },//��B����ɫ
						{ 0.0,0.0,1.0 },//��C����ɫ
						{ 1.0,1.0,0.0 } };//��O����ɫ




