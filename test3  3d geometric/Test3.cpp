#pragma once
//�� ֱ��ʹ����Ե������㡢��һ����Դ��API������
//�� ʹ�����飻
//�� ʹ�ö������顣

/* draws the wire frame glut cube */
#include "stdafx.h"
#include "Test3.h"

//ֱ��ʹ����Ե������㡢��һ����Դ��API����
void tetrahedron() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glShadeModel(GL_FLAT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);//��
	glVertex3f(O.x, O.y, O.z);
	glVertex3f(C.x, C.y, C.z);
	glVertex3f(A.x, A.y, A.z);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);//��
	glBegin(GL_POLYGON);
	glVertex3f(O.x, O.y, O.z);
	glVertex3f(B.x, B.y, B.z);
	glVertex3f(C.x, C.y, C.z);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);//��
	glBegin(GL_POLYGON);
	glVertex3f(O.x, O.y, O.z);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(B.x, B.y, B.z);
	glEnd();

	glColor3f(1.0f, 1.0f, 0.0f);//��
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
	GLubyte indices[] = { 2,0,3,//CAO��,����ǰ��Ķ���ŵ����治�ı䶥�㻷�Ʒ���
						3,1,2,//OBC��
						3,0,1,//OAB��
						1,2,0 };//BCA��

	//��ÿ������ж����Ļ��ƣ������Ϸ��������ԣ�һ����ֻ������һ�Σ��ܹ�������4��
	//for (int i = 0; i < 4;i++)
	//	glDrawElements(GL_POLYGON, 3, GL_UNSIGNED_BYTE, indices+i*3);

	//����һ�λ���,ʹ������GL_TRIANGLES,ÿ3�������Ķ������һ���µ�������
	//ִ�иú���ʱ�����б����õ����齫�ᱻ����
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_COLOR_ARRAY);//�ر���ɫ����
	glDisableClientState(GL_VERTEX_ARRAY);//�رն�������
}
void rotate() {


}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//�Ӳ�ͬ����۲�
	//gluLookAt(0.0, 0.0,2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//��z��,Ԥ����ɫ����
	//gluLookAt(0.0, 0.0, -2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//��z��,Ԥ����ɫ����
	//gluLookAt(2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//��x��,Ԥ����ɫ����
	//gluLookAt(-2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//��x��,Ԥ����ɫ����
	//gluLookAt(2.0, -2.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//�ܿ�����

	//����������
	gluLookAt(1.0, 1.5, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//tetrahedron();
	//tetrahedron2();
	//tetrahedron3();

	//����������
	glColor3f(1.0, 0.0, 0.0);
	glutWireTeapot(1);
	//glutSolidTeapot(1);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	//�����ӿ�
	//glViewport(0, 0, w, h);
	//glViewport(0, 0, w / 2, h / 2);//���ӿ�λ�ڴ��ڵ����½�
	//glViewport(w / 2, 0, w / 2, h / 2);//���ӿ�λ�ڴ��ڵ����½�
	//glViewport(w / 4, h / 4, w / 2, h / 2);
	//glViewport(100, 50, 300, 300);
	float W = 300, H = 300;
	glViewport(w / 2 - W / 2, h / 2 - H / 2, W, H);// �����г���W < w, H < h��

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//ʹ��͸��ͶӰ
	GLfloat aspect = (float)w / (float)h;
	gluPerspective(60.0f, aspect, 0.5f, 15.0f); 

	glMatrixMode(GL_MODELVIEW);//����Ϊû���л���ģ����ͼ���󡣵�����ɫ��ʾ����Ԥ��Ч��
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);//���ñ���ɫΪ��ɫ
	glColor3f(0.0, 0.0, 0.0);//���û�����ɫΪ��ɫ
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


