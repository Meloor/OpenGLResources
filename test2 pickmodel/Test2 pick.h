#pragma once

#include <stdlib.h>
#include <stdio.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define SIZE 512
/*******************************************************/
struct point {
	int x;
	int y;
	point(int x_ = 0, int y_ = 0) {
		x = x_;
		y = y_;
	}
};
int window_width = 500, window_height = 500; // globals for viewport height and width
int draw_mode = 1;
int click_num = 0;
int draw_color = 0;
int render_mode = 0;
int fill_mode = 0;
int obj_num = 0;
int obj_type[500];//存图形对象的类型
int obj_color[500];//图形对象的颜色
point objs[500][3];//存点
int display_times = 0;
/*****************************************************/
void init();
void drawObjects(GLenum mode);
void display();
void processHits(GLint hits, GLuint buffer[]);
void mouse(int button, int state, int x, int y);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void draw_menu(int value);
void render_menu(int value);
void color_menu(int value);
void mymenu(int value);
void fill_menu(int value);
void change_color(int color_id);
void change_fill_mode(int render_mode);
void draw_line(int obj_id);
void draw_rect(int obj_id);
void draw_triangle(int obj_id);

