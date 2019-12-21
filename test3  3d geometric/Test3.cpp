#pragma once
//① 直接使用针对单个顶点、单一数据源的API函数；
//② 使用数组；
//③ 使用顶点数组。

/* draws the wire frame glut cube */
#include "stdafx.h"
#include "Test3.h"

//直接使用针对单个顶点、单一数据源的API函数
void tetrahedron() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glShadeModel(GL_FLAT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);//红
	glVertex3f(O.x, O.y, O.z);
	glVertex3f(C.x, C.y, C.z);
	glVertex3f(A.x, A.y, A.z);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);//绿
	glBegin(GL_POLYGON);
	glVertex3f(O.x, O.y, O.z);
	glVertex3f(B.x, B.y, B.z);
	glVertex3f(C.x, C.y, C.z);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);//蓝
	glBegin(GL_POLYGON);
	glVertex3f(O.x, O.y, O.z);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(B.x, B.y, B.z);
	glEnd();

	glColor3f(1.0f, 1.0f, 0.0f);//黄
	glBegin(GL_POLYGON);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(C.x, C.y, C.z);
	glVertex3f(B.x, B.y, B.z);
	glEnd();

}
void triangle(int a, int b, int c) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glEnd();
}
void tetrahedron2() {
	glColor3fv(colors[0]);
	triangle(3, 2, 0);
	glColor3fv(colors[1]);
	triangle(3, 1, 2);
	glColor3fv(colors[2]);
	triangle(3, 0, 1);
	glColor3fv(colors[3]);
	triangle(0, 1, 2);
}
void tetrahedron3() {
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
	GLubyte indices[] = { 2,0,3,//CAO黄,把最前面的顶点放到后面不改变顶点环绕方向
						3,1,2,//OBC蓝
						3,0,1,//OAB绿
						1,2,0 };//BCA红

	//将每个面进行独立的绘制，这样较方法二而言，一个面只绘制了一次，总共绘制了4次
	//for (int i = 0; i < 4;i++)
	//	glDrawElements(GL_POLYGON, 3, GL_UNSIGNED_BYTE, indices+i*3);

	//进行一次绘制,使用类型GL_TRIANGLES,每3个连续的顶点绘制一个新的三角形
	//执行该函数时，所有被启用的数组将会被绘制
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_COLOR_ARRAY);//关闭颜色数组
	glDisableClientState(GL_VERTEX_ARRAY);//关闭顶点数组
}
void rotate() {


}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//从不同方向观察
	//gluLookAt(0.0, 0.0,2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//正z轴,预期颜色：红
	//gluLookAt(0.0, 0.0, -2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//负z轴,预期颜色：黄
	//gluLookAt(2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//正x轴,预期颜色：红
	//gluLookAt(-2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//负x轴,预期颜色：蓝
	//gluLookAt(2.0, -2.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//能看到绿

	//绘制四面体
	gluLookAt(1.0, 1.5, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//tetrahedron();
	//tetrahedron2();
	//tetrahedron3();

	//绘制犹他壶
	glColor3f(1.0, 0.0, 0.0);
	glutWireTeapot(1);
	//glutSolidTeapot(1);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	//设置视口
	//glViewport(0, 0, w, h);
	//glViewport(0, 0, w / 2, h / 2);//该视口位于窗口的左下角
	//glViewport(w / 2, 0, w / 2, h / 2);//该视口位于窗口的右下角
	//glViewport(w / 4, h / 4, w / 2, h / 2);
	//glViewport(100, 50, 300, 300);
	float W = 300, H = 300;
	glViewport(w / 2 - W / 2, h / 2 - H / 2, W, H);// ，其中常数W < w, H < h。

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//使用透视投影
	GLfloat aspect = (float)w / (float)h;
	gluPerspective(60.0f, aspect, 0.5f, 15.0f); 

	glMatrixMode(GL_MODELVIEW);//是因为没有切换回模型视图矩阵。导致颜色显示不在预期效果
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);//设置背景色为白色
	glColor3f(0.0, 0.0, 0.0);//设置绘制颜色为黑色
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Test");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	init();
	glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */
	glutMainLoop();
}


