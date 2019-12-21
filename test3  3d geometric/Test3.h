#pragma once
#include "stdafx.h"
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>         /* glut.h includes gl.h and glu.h */
#endif
/*结构体定义*********************************************************/
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
/*函数声明*********************************************************/
void tetrahedron();//直接使用针对单个顶点、单一数据源的API函数
void triangle(int a,int b,int c);
void tetrahedron2();//使用数组
void tetrahedron3();//使用顶点数组
void display();
void reshape(int w, int h);
void init();
/*全局变量********************************************************/
//下面四个点用于方法一
point A = point(1, 0, 0);
point B = point(0, 0, 1);
point C = point(0, 1, 0);
point O = point(0, 0, 0);
//下面这两个数组用于方法二、三
GLfloat vertices[][3] = { { 1.0,0.0,0.0 },
						{ 0.0,0.0,1.0 },
						{ 0.0,1.0,0.0 },
						{ 0.0,0.0,0.0 } };

GLfloat colors[][3] = { { 1.0,0.0,0.0 },//点A，红色
						{ 0.0,1.0,0.0 },//点B，绿色
						{ 0.0,0.0,1.0 },//点C，蓝色
						{ 1.0,1.0,0.0 } };//点O，黄色




