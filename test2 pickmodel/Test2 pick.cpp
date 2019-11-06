// Test2 pick.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Test2 pick.h"
/*�˵�����**************************************************************/
void render_menu(int value) {
	if (value == 0) {
		render_mode = 0;
		//����display����ѡ��ģʽ�ص�����ģʽ�󣬸�����������Ҫȥ��
		glutPostRedisplay();
		printf("�������ģʽ...\n");
	}
	if (value == 1) {
		render_mode = 1;
		printf("����ѡ��ģʽ...\n");
	}
}
void draw_menu(int value) {
	if (value == 1) {//�߶�
		draw_mode = 1;
		click_num = 0;
		printf("�����߶�...\n");
	}
	if (value == 2) {//����
		draw_mode = 2;
		click_num = 0;
		printf("���ƾ���...\n");
	}
	if (value == 3) {//������
		draw_mode = 3;
		click_num = 0;
		printf("����������...\n");
	}
}
void fill_menu(int value) {
	if (value == 0) {
		fill_mode = 0;
		glutPostRedisplay();
		printf("�����߿�ģʽ...\n");
	}
	if (value == 1) {
		fill_mode = 1;
		glutPostRedisplay();
		printf("�������ģʽ...\n");
	}
}
void color_menu(int value) {
	if (value == 0) {
		draw_color = 0;
		printf("���ư�ɫͼԪ...\n");
	}
	if (value == 1) {
		draw_color = 1;
		printf("���ƺ�ɫͼԪ...\n");
	}
	if (value == 2) {
		draw_color = 2;
		printf("������ɫͼԪ...\n");
	}
	if (value == 3) {
		draw_color = 3;
		printf("������ɫͼԪ...\n");
	}
}
void mymenu(int value) {
	if (value == 5) {
		printf("�����Ļ...\n");
		glClear(GL_COLOR_BUFFER_BIT);
		//glutSwapBuffers();
		//�����������д������������ˣ�����ɶԭ��	
		glBegin(GL_LINES);
		glEnd();

		obj_num = 0;
		glFlush();
	}
	if (value == 6) {
		exit(0);
	}
}

/*��ʼ���˵�**************************************************************/
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//��ɫ�Ӳ˵�
	int color_menu_id = glutCreateMenu(color_menu);
	glutAddMenuEntry("White", 0);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);

	//����ģʽ�Ӳ˵�
	int draw_menu_id = glutCreateMenu(draw_menu);
	glutAddMenuEntry("�߶�", 1);
	glutAddMenuEntry("����", 2);
	glutAddMenuEntry("������", 3);

	//��Ⱦģʽ�Ӳ˵�
	int render_menu_id = glutCreateMenu(render_menu);
	glutAddMenuEntry("����", 0);
	glutAddMenuEntry("ѡ��", 1);

	//���ģʽ
	int fill_menu_id = glutCreateMenu(fill_menu);
	glutAddMenuEntry("�߿�", 0);
	glutAddMenuEntry("���", 1);
	//���˵�
	int id = glutCreateMenu(mymenu);
	glutAddSubMenu("��Ⱦģʽ", render_menu_id);
	glutAddSubMenu("ͼ��ѡ��", draw_menu_id);
	glutAddSubMenu("���ģʽ", fill_menu_id);
	glutAddSubMenu("��ɫѡ��", color_menu_id);
	glutAddMenuEntry("����", 5);
	glutAddMenuEntry("�˳�", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}
/*ģʽ�л�����**************************************************************************/
void change_color(int color_id) {
	if (color_id == 0) {
		glColor3f(1.0, 1.0, 1.0);
	}
	if (color_id == 1) {
		glColor3f(1.0, 0, 0);
	}
	if (color_id == 2) {
		glColor3f(0, 1.0, 0);
	}
	if (color_id == 3) {
		glColor3f(0, 0, 1.0);
	}
}
void change_fill_mode(int render_mode) {
	if (fill_mode == 0)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (fill_mode == 1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
/*ͼԪ���ƺ���**************************************************************************/
void draw_line(int obj_id) {
	//printf("draw_line\n");
	int i = obj_id;
	int x1 = objs[i][0].x;
	int y1 = objs[i][0].y;
	int x2 = objs[i][1].x;
	int y2 = objs[i][1].y;
	//glColor3f(1.0, 0, 0); glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_LINES);
		glVertex2i(x1, window_height - y1);//���Ͻ�
		//printf("point:%d %d\n", x1, window_height - y1);
		glVertex2i(x2, window_height - y2);//���½�
	glEnd();
	glFlush();
}
void draw_rect(int obj_id) {
	int i = obj_id;
	int x1 = objs[i][0].x;
	int y1 = objs[i][0].y;
	int x2 = objs[i][1].x;
	int y2 = objs[i][1].y;

	//һ�д�����ƾ���
	glRecti(x1, window_height - y1, x2, window_height - y2);
}
void draw_triangle(int obj_id) {
	int i = obj_id;
	int x1 = objs[i][0].x;
	int y1 = objs[i][0].y;
	int x2 = objs[i][1].x;
	int y2 = objs[i][1].y;
	int x3 = objs[i][2].x;
	int y3 = objs[i][2].y;

	glBegin(GL_TRIANGLES);
		glVertex2i(x1, window_height - y1);
		glVertex2i(x2, window_height - y2);
		glVertex2i(x3, window_height - y3);
	glEnd();
}
void drawObjects(GLenum mode){
	printf("draw %d objects\n", obj_num);
	for (int i = 0; i < obj_num; i++) {
		if (mode == GL_SELECT) glLoadName(i);//�ǲ�����Ϊ��0��ʼ��0�ֱ��ù��˲ų����
		change_color(obj_color[i]);
		change_fill_mode(fill_mode);
		if (obj_type[i] == 1) {
			draw_line(i);
		}
		if (obj_type[i] == 2) {
			draw_rect(i);
		}
		if (obj_type[i] == 3) {
			draw_triangle(i);
		}
	}
}
/***************************************************************************/
//���������Ϣ
void processHits(GLint hits, GLuint buffer[])
{
	printf("hits = %d\n", hits);
	unsigned int i;
	GLint name;	

	//���ø���ģʽ
	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(4.0f);//�����߿�
	glEnable(GL_LINE_STIPPLE);//���õ㻮ģʽ
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�����Ҫ�Ȼ����߿�ģʽ
	glLineStipple(3, 0xff00);//�㻮ģʽ���ɽ�������???

	for (i = 0; i < hits; i++) {
	//ÿ��ѡ��������ռ������ջ��4����λ����4������������ֵ
		name = buffer[3 + i * 4];
		switch (obj_color[name]) {
			case 0:printf("��ɫ"); break;
			case 1:printf("��ɫ"); break;
			case 2:printf("��ɫ"); break;
			case 3:printf("��ɫ"); break;
		}
		switch (obj_type[name]) {
		case 1: {
			draw_line(name);
			glFlush();
			printf("�߶�"); 
			break;
		}
		case 2: {
			draw_rect(name);
			glFlush();
			printf("����"); 
			break;
		}
		case 3: {
			draw_triangle(name);
			glFlush();
			printf("������"); 
			break;
		}
		}
		
		printf("\n");
	}
	glDisable(GL_LINE_STIPPLE);//�رյ㻮ģʽ
	change_fill_mode(fill_mode);//�ص����õ����ģʽ
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		printf("click point(%d,%d)\n", x, y);
		if (render_mode == 0) {
			change_color(draw_color);
			change_fill_mode(fill_mode);
			if (draw_mode == 1) {//�߶�
				static int x1, y1;			
				click_num++;
				if (click_num == 1)//��һ�ε��
				{
					//printf("click_num:%d\n", click_num);
					x1 = x;
					y1 = y;

				}
				if (click_num == 2)
				{
					//printf("click_num:%d\n", click_num);
					click_num = 0;

					obj_type[obj_num] = draw_mode;
					obj_color[obj_num] = draw_color;
					objs[obj_num][0] = point(x1, y1);
					objs[obj_num][1] = point(x, y);

					draw_line(obj_num);
					glFlush();
					obj_num++;
				}				
			}

			if (draw_mode == 2) {//����
				static int x1, y1;
				click_num++;
				if (click_num == 1)//��һ�ε��
				{
					x1 = x;
					y1 = y;

				}
				if (click_num == 2)
				{
					click_num = 0;

					obj_type[obj_num] = draw_mode;
					obj_color[obj_num] = draw_color;
					objs[obj_num][0] = point(x1, y1);
					objs[obj_num][1] = point(x, y);

					draw_rect(obj_num);
					glFlush();
					obj_num++;	
				}			
			}
			if (draw_mode == 3) {//������
				static int x1, y1, x2, y2;			
				click_num++;
				if (click_num == 1)//��һ�ε��
				{
					x1 = x;
					y1 = y;
					//printf("�����һ����\n");
				}
				if (click_num == 2) {
					x2 = x;
					y2 = y;

					glBegin(GL_LINES);
						glVertex2i(x1, window_height - y1);//���Ͻ�
						glVertex2i(x2, window_height - y2);//���½�
					glEnd();
					glFlush();
				}
				if (click_num == 3)
				{
					click_num = 0;

					obj_type[obj_num] = draw_mode;
					obj_color[obj_num] = draw_color;
					objs[obj_num][0] = point(x1, y1);
					objs[obj_num][1] = point(x2, y2);
					objs[obj_num][2] = point(x, y);

					draw_triangle(obj_num);
					glFlush();
					obj_num++;
				}			
			}
		}

		if (render_mode == 1) {	
			GLuint selectBuf[SIZE];
			GLint hits;
			GLint viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);
			glSelectBuffer(SIZE, selectBuf);
			glRenderMode(GL_SELECT);
			glInitNames();
			glPushName(0);//hitΪ0������޹�
			glMatrixMode(GL_PROJECTION);
			//push,pop֮��ĵ�˳���ܶ���Ҳ���ܷ�������
			glPushMatrix();//����ɲü���
				glLoadIdentity();//�����²ü���
				gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y),5.0, 5.0, viewport);
				gluOrtho2D(0.0, (GLfloat)window_width, 0.0, (GLfloat)window_height);
				drawObjects(GL_SELECT);					
			glPopMatrix();//���ؾɲü���
			glFlush();//���flushӦ���Ƿ��غ��ˢ��
			glMatrixMode(GL_MODELVIEW);//�۲�reshape������glLoadIdentity����ʱ������glMatrixMode�����
			glLoadIdentity();//������һ�д��룬hit��һ����0		
			hits = glRenderMode(GL_RENDER);
			processHits(hits, selectBuf);
				
			//glutPostRedisplay();//�ص�display,���б���ص�����hit��һ����0
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		click_num = 0;
	}
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

void display()
{
	display_times++;
	printf("display times:%d\n", display_times);
	//printf("obj_num:%d\n", obj_num);
	glClear(GL_COLOR_BUFFER_BIT);

	//����Ĵ�����ϲ���������ʹ�û���ģʽ�����ֻ���˵����У��ڴ�ѡ��ģʽ���ػ���ģʽ���޷���������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, window_width, 0, window_height);//������һ�д������Ի��Ƴ�ͼԪ���й����û����һ���о�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	drawObjects(GL_RENDER);
	glFlush();
}

void reshape(int w, int h)
{
	//printf("reshape\n");
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Main Loop */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//hitΪ0������޹�
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(800, 100);
	glutCreateWindow(argv[0]);
	init();

	//��������������˭��˭�����ȵ��õ�reshape
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	

	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

