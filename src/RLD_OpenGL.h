#ifndef RLD_OPENGL
#define RLD_OPENGL
#include "g_Include.h"
void glPrint(int x, int y, const char *fmt, ...);
void glPrintBig(int x, int y, const char *fmt, ...);
void glPrintUnderline(int x, int y, const char *fmt, ...);
void DrawBox(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);
void DrawRectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
void DrawWatermark(const char* watermark,bool randcol, GLfloat R, GLfloat G, GLfloat B);
void HookGL();
#endif