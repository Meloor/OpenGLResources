// Test2 pick.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Test2 pick.h"
/*菜单函数**************************************************************/
void render_menu(int value) {
	if (value == 0) {
		render_mode = 0;
		//调用display，从选择模式回到绘制模式后，高亮的虚线需要去掉
		glutPostRedisplay();
		printf("进入绘制模式...\n");
	}
	if (value == 1) {
		render_mode = 1;
		printf("进入选择模式...\n");
	}
}
void draw_menu(int value) {
	if (value == 1) {//线段
		draw_mode = 1;
		click_num = 0;
		printf("绘制线段...\n");
	}
	if (value == 2) {//矩形
		draw_mode = 2;
		click_num = 0;
		printf("绘制矩形...\n");
	}
	if (value == 3) {//三角形
		draw_mode = 3;
		click_num = 0;
		printf("绘制三角形...\n");
	}
}
void fill_menu(int value) {
	if (value == 0) {
		fill_mode = 0;
		glutPostRedisplay();
		printf("进入线框模式...\n");
	}
	if (value == 1) {
		fill_mode = 1;
		glutPostRedisplay();
		printf("进入填充模式...\n");
	}
}
void color_menu(int value) {
	if (value == 0) {
		draw_color = 0;
		printf("绘制白色图元...\n");
	}
	if (value == 1) {
		draw_color = 1;
		printf("绘制红色图元...\n");
	}
	if (value == 2) {
		draw_color = 2;
		printf("绘制绿色图元...\n");
	}
	if (value == 3) {
		draw_color = 3;
		printf("绘制蓝色图元...\n");
	}
}
void mymenu(int value) {
	if (value == 5) {
		printf("清空屏幕...\n");
		glClear(GL_COLOR_BUFFER_BIT);
		//glutSwapBuffers();
		//加了下面两行代码后就能清屏了，这是啥原理	
		glBegin(GL_LINES);
		glEnd();

		obj_num = 0;
		glFlush();
	}
	if (value == 6) {
		exit(0);
	}
}

/*初始化菜单**************************************************************/
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//颜色子菜单
	int color_menu_id = glutCreateMenu(color_menu);
	glutAddMenuEntry("White", 0);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);

	//绘制模式子菜单
	int draw_menu_id = glutCreateMenu(draw_menu);
	glutAddMenuEntry("线段", 1);
	glutAddMenuEntry("矩形", 2);
	glutAddMenuEntry("三角形", 3);

	//渲染模式子菜单
	int render_menu_id = glutCreateMenu(render_menu);
	glutAddMenuEntry("绘制", 0);
	glutAddMenuEntry("选择", 1);

	//填充模式
	int fill_menu_id = glutCreateMenu(fill_menu);
	glutAddMenuEntry("线框", 0);
	glutAddMenuEntry("填充", 1);
	//主菜单
	int id = glutCreateMenu(mymenu);
	glutAddSubMenu("渲染模式", render_menu_id);
	glutAddSubMenu("图形选择", draw_menu_id);
	glutAddSubMenu("填充模式", fill_menu_id);
	glutAddSubMenu("颜色选择", color_menu_id);
	glutAddMenuEntry("清屏", 5);
	glutAddMenuEntry("退出", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}
/*模式切换函数**************************************************************************/
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
/*图元绘制函数**************************************************************************/
void draw_line(int obj_id) {
	//printf("draw_line\n");
	int i = obj_id;
	int x1 = objs[i][0].x;
	int y1 = objs[i][0].y;
	int x2 = objs[i][1].x;
	int y2 = objs[i][1].y;
	//glColor3f(1.0, 0, 0); glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_LINES);
		glVertex2i(x1, window_height - y1);//左上角
		//printf("point:%d %d\n", x1, window_height - y1);
		glVertex2i(x2, window_height - y2);//右下角
	glEnd();
	glFlush();
}
void draw_rect(int obj_id) {
	int i = obj_id;
	int x1 = objs[i][0].x;
	int y1 = objs[i][0].y;
	int x2 = objs[i][1].x;
	int y2 = objs[i][1].y;

	//一行代码绘制矩形
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
		if (mode == GL_SELECT) glLoadName(i);//是不是因为从0开始而0又被用过了才出错的
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
//输出命中信息
void processHits(GLint hits, GLuint buffer[])
{
	printf("hits = %d\n", hits);
	unsigned int i;
	GLint name;	

	//设置高亮模式
	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(4.0f);//设置线宽
	glEnable(GL_LINE_STIPPLE);//启用点划模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//多边形要先换成线框模式
	glLineStipple(3, 0xff00);//点划模式，可建立虚线???

	for (i = 0; i < hits; i++) {
	//每个选中物体有占用名字栈中4个单位，第4个是物体名字值
		name = buffer[3 + i * 4];
		switch (obj_color[name]) {
			case 0:printf("白色"); break;
			case 1:printf("红色"); break;
			case 2:printf("绿色"); break;
			case 3:printf("蓝色"); break;
		}
		switch (obj_type[name]) {
		case 1: {
			draw_line(name);
			glFlush();
			printf("线段"); 
			break;
		}
		case 2: {
			draw_rect(name);
			glFlush();
			printf("矩形"); 
			break;
		}
		case 3: {
			draw_triangle(name);
			glFlush();
			printf("三角形"); 
			break;
		}
		}
		
		printf("\n");
	}
	glDisable(GL_LINE_STIPPLE);//关闭点划模式
	change_fill_mode(fill_mode);//回到设置的填充模式
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		printf("click point(%d,%d)\n", x, y);
		if (render_mode == 0) {
			change_color(draw_color);
			change_fill_mode(fill_mode);
			if (draw_mode == 1) {//线段
				static int x1, y1;			
				click_num++;
				if (click_num == 1)//第一次点击
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

			if (draw_mode == 2) {//矩形
				static int x1, y1;
				click_num++;
				if (click_num == 1)//第一次点击
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
			if (draw_mode == 3) {//三角形
				static int x1, y1, x2, y2;			
				click_num++;
				if (click_num == 1)//第一次点击
				{
					x1 = x;
					y1 = y;
					//printf("点击第一个点\n");
				}
				if (click_num == 2) {
					x2 = x;
					y2 = y;

					glBegin(GL_LINES);
						glVertex2i(x1, window_height - y1);//左上角
						glVertex2i(x2, window_height - y2);//右下角
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
			glPushName(0);//hit为0与这个无关
			glMatrixMode(GL_PROJECTION);
			//push,pop之间的的顺序不能动，也不能放在外面
			glPushMatrix();//保存旧裁剪体
				glLoadIdentity();//加载新裁剪体
				gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y),5.0, 5.0, viewport);
				gluOrtho2D(0.0, (GLfloat)window_width, 0.0, (GLfloat)window_height);
				drawObjects(GL_SELECT);					
			glPopMatrix();//返回旧裁剪体
			glFlush();//这个flush应该是返回后的刷新
			glMatrixMode(GL_MODELVIEW);//观察reshape函数，glLoadIdentity函数时紧跟在glMatrixMode后面的
			glLoadIdentity();//少了这一行代码，hit就一定是0		
			hits = glRenderMode(GL_RENDER);
			processHits(hits, selectBuf);
				
			//glutPostRedisplay();//回调display,这行必须关掉否则hit就一定是0
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

	//下面的代码加上才能正常的使用绘制模式，如果只加了第三行，在从选择模式返回绘制模式后无法正常绘制
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, window_width, 0, window_height);//加了这一行代码后可以绘制出图元，有关作用还需进一步研究
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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//hit为0与这个无关
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(800, 100);
	glutCreateWindow(argv[0]);
	init();

	//这两个函数无论谁先谁后都是先调用的reshape
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	

	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

