// test1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define _USE_MATH_DEFINES
#include "math.h"
/*
*  simple.c
*  This program draws a white rectangle on a black background.
*/


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/
#endif

void display(void){
	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);//这句是什么意思
	/* draw unit square polygon */
	glEnable(GL_POLYGON_STIPPLE);
	//glPolygonStipple();
	glBegin(GL_POLYGON);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	/* flush GL buffers */
	glFlush();
}
void display_point(void) {
	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);
	/* draw unit square polygon */
	glPointSize(4.0f);//设置点的大小
	glBegin(GL_POINTS);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	/* flush GL buffers */
	glFlush();
}
//绘制线段，顶点两两一对
void display_line(void) {
	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);
	/* draw unit square polygon */
	glLineWidth(4.0f);//设置线宽
	glEnable(GL_LINE_STIPPLE);//启用点划模式
	glLineStipple(3,0xff00);//点划模式，可建立虚线???
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);	
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	/* flush GL buffers */
	glFlush();
}
void display_line_strip(void) {
	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);
	/* draw unit square polygon */
	glBegin(GL_LINE_STRIP);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	/* flush GL buffers */
	glFlush();
}
void display_line_loop(void) {
	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);
	/* draw unit square polygon */
	glBegin(GL_LINE_LOOP);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	/* flush GL buffers */
	glFlush();
}
/*6种填充图元*******************************************************************/
void display_triangles(void) {
	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);
	/* draw unit square polygon */
	glBegin(GL_TRIANGLES);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	/* flush GL buffers */
	glFlush();
}
//渐变条带
void display_triangle_strip(void) {
	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);
	/* draw unit square polygon */
	glShadeModel(GL_FLAT);//块模式，颜色为三角形最后一个点的颜色
	glShadeModel(GL_FLAT); //GL_SMOOTH为默认，是平滑模式（渐变效果）
	glBegin(GL_TRIANGLE_STRIP);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-0.5, -0.5);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(-0.5, 0.5);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.5, 0.5);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(0.5, 1.0);
	glEnd();
	/* flush GL buffers */
	glFlush();
}
void display_triangle_fan(void) {
	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);
	/* draw unit square polygon */
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//设置线框模式还有GL_FILL填充模式
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	/* flush GL buffers */
	glFlush();
}
void display_quads(void) {
	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);
	/* draw unit square polygon */
	glBegin(GL_QUADS);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	/* flush GL buffers */
	glFlush();
}
void display_quad_strip(void) {
	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);
	/* draw unit square polygon */
	glBegin(GL_QUAD_STRIP);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	/* flush GL buffers */
	glFlush();
}
void  display_rect(void) {
	//glRect<sifd>(0.0f, 0.0f, 10.0f, 10.0f);
}
/*绘制一个逼近的圆************************************************************/
void display_circle(void) {
	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);
	/* draw unit square polygon */
	const int max_v = 8;
	float x[max_v];
	float y[max_v];
	float r = 0.5f;

	float alpha = 2*M_PI / max_v;
	for (int i = 0; i < max_v; i++) {
		y[i] = r*sin(alpha*i);
		x[i] = r*cos(alpha*i);
		printf("%d(%.2lf,%.2lf)\n", i, x[i], y[i]);
	}
	
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glLineWidth(10.0f);
	glBegin(GL_POLYGON);
	
	//glBegin(GL_LINE_LOOP);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3b(1.0, 0.0, 0.0);
	glVertex2f(x[0], y[0]);
	glVertex2f(x[1], y[1]);
	glVertex2f(-0.5f, 0.0f);
	glVertex2f(0.5f,0.0f);
	//for (int i = 0; i < max_v; i++) {
	//	glVertex2f(x[i], y[i]);
	//}	
	glEnd();
	/* flush GL buffers */
	glFlush();
}

void display_circle2(void){
	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);//这句是什么意思
	const int max_v = 100;
	float x[max_v];
	float y[max_v];
	float r = 0.5f;

	float alpha = 2*M_PI / max_v;
	for (int i = 0; i < max_v; i++) {
		y[i] = r*sin(alpha*i);
		x[i] = r*cos(alpha*i);
		printf("%d(%.2lf,%.2lf)\n", i, x[i], y[i]);
	}
	/* draw unit square polygon */
	//glPolygonStipple();
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_POLYGON);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	for (int i = 0; i < max_v; i++) {
		glVertex2f(x[i], y[i]);
	}	
	glEnd();
	/* flush GL buffers */
	glFlush();
}
void init()
{

	/* set clear color to black */

	/* 	glClearColor (0.0, 0.0, 0.0, 0.0); */
	/* set fill  color to white */

	/* 	glColor3f(1.0, 1.0, 1.0); */

	/* set up standard orthogonal view with clipping */
	/* box as cube of side 2 centered at origin */
	/* This is default view and these statement could be removed */

	/* glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  */
}

int main(int argc, char** argv)
{

	/* Initialize mode and open a window in upper left corner of screen */
	/* Window title is name of program (arg[0]) */

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("simple");
	//glutDisplayFunc(display_point);
	//glutDisplayFunc(display_line);
	//glutDisplayFunc(display_line_strip);
	glutDisplayFunc(display_line_loop);
	//glutDisplayFunc(display_triangles);
	//glutDisplayFunc(display_triangle_strip);
	//glutDisplayFunc(display_triangle_fan);
	//glutDisplayFunc(display_quads);
	 //glutDisplayFunc(display_quad_strip);
	 //glutDisplayFunc(display_circle2);
	//init();
	glutMainLoop();

}

