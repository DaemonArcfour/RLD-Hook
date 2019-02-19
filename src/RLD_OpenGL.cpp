#include "RLD_OpenGL.h"

HDC				hDC;
HFONT			hOldFont;
HFONT			hFont;
UINT			FontBase, FontBaseUnderline, FontBaseBig;
bool                     bFontsBuild = 0;
typedef void (APIENTRY *glBegin_t)(GLenum);
typedef void (APIENTRY *glEnd_t)(void);
typedef void (APIENTRY *glClear_t)(GLbitfield);
typedef void (APIENTRY *glVertex3fv_t)(const GLfloat *v);
typedef void (APIENTRY *glVertex3f_t)(GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRY *glEnable_t)(GLenum);
typedef void (APIENTRY *glDisable_t)(GLenum);
typedef bool (WINAPI *SwapBuffers_t)(HDC);
glBegin_t pglBegin = NULL;
glDisable_t pglDisable = NULL;
glEnd_t pglEnd = NULL;
glClear_t pglClear = NULL;
glVertex3fv_t pglVertex3fv = NULL;
glVertex3f_t pglVertex3f = NULL;
glEnable_t pglEnable = NULL;
SwapBuffers_t pSwapBuffers = NULL;
bool notStrip = false;
// ----------------------------------------------------------------------
void APIENTRY Hooked_glBegin(GLenum mode)
{
	if (gRLD_CVars.rld_autoshoot) {
		autoshoot();
	}
	if (gRLD_CVars.rld_wallhack)
	{
		if (mode == GL_TRIANGLE_STRIP) {
			glDisable(GL_DEPTH_TEST);
			notStrip = true;
		}
		else {
			notStrip = false;
			glEnable(GL_DEPTH_TEST);
		}
	}

	if (pglBegin)
		(*pglBegin)(mode);

}
bool contextCreated = false;
GLvoid initContext() {
	contextCreated = true;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 640, 480, 0.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 1.0);
}
bool WINAPI Hooked_SwapBuffers(HDC hdc) {
	HGLRC oldContext = wglGetCurrentContext();
	static HGLRC thisContext = NULL;
	
	
	if (!contextCreated) {
		thisContext = wglCreateContext(hdc);
		wglMakeCurrent(hdc, thisContext);
		initContext();
	}
	else {
		wglMakeCurrent(hdc, thisContext);
	}
	__int32 *PlayerStruct = (__int32*)0x11F09B8;
	__int32 *PPlayer = &PlayerStruct[0];
	DrawWatermark("RLD Hook v1.666 by Daemon",true, 0.0f, 0.65f, 0.75f);
	//int speed = sqrt((int)(PPlayer[219] >> 16)*(int)(PPlayer[219] >> 16) + (int)(PPlayer[220] >> 16)*(int)(PPlayer[220] >> 16));
	//DrawWatermark(std::to_string(speed).c_str(), true, 0.0f, 0.65f, 0.75f);
	//DrawBox((int)(PPlayer[216] >> 16), (int)(PPlayer[217] >> 16), (int)(PPlayer[218] >> 16), 90, 90);
	wglMakeCurrent(hdc, oldContext);
	return (*pSwapBuffers)(hdc);
}
void APIENTRY Hooked_glEnd(void)
{
	(*pglEnd)();
}

void APIENTRY Hooked_glVertex3fv(GLfloat *v)
{
	(*pglVertex3fv)(v);
}


void APIENTRY Hooked_glVertex3f(GLfloat x, GLfloat y, GLfloat z)
{
	(*pglVertex3f)(x, y, z);
}

void APIENTRY Hooked_glClear(GLbitfield mask)
{
	(*pglClear)(mask);
}

void APIENTRY Hooked_glEnable(GLenum cap)
{
	if (gRLD_CVars.rld_wallhack == true && cap == GL_DEPTH_TEST && notStrip == true)
		return;
	(*pglEnable)(cap);
	
}

void APIENTRY Hooked_glDisable(GLenum cap)
{
	(*pglDisable)(cap);
}
void *DetourFunc(BYTE *src, const BYTE *dst, const int len)
{
	BYTE *jmp = (BYTE*)malloc(len + 5);
	DWORD dwback;
	VirtualProtect(src, len, PAGE_READWRITE, &dwback);
	memcpy(jmp, src, len);
	jmp += len;
	jmp[0] = 0xE9;
	*(DWORD*)(jmp + 1) = (DWORD)(src + len - jmp) - 5;
	src[0] = 0xE9;
	*(DWORD*)(src + 1) = (DWORD)(dst - src) - 5;
	VirtualProtect(src, len, dwback, &dwback);
	return (jmp - len);
}
void HookGL()
{
	HMODULE hOpenGL = GetModuleHandle("opengl32.dll");
	HMODULE hGDI = GetModuleHandle("gdi32.dll");
	pglVertex3fv = (glVertex3fv_t)DetourFunc((LPBYTE)GetProcAddress(hOpenGL, "glVertex3fv"), (LPBYTE)&Hooked_glVertex3fv, 6);
	pglVertex3f = (glVertex3f_t)DetourFunc((LPBYTE)GetProcAddress(hOpenGL, "glVertex3f"), (LPBYTE)&Hooked_glVertex3f, 6);
	pglBegin = (glBegin_t)DetourFunc((LPBYTE)GetProcAddress(hOpenGL, "glBegin"), (LPBYTE)&Hooked_glBegin, 6);
	pglEnd = (glEnd_t)DetourFunc((LPBYTE)GetProcAddress(hOpenGL, "glEnd"), (LPBYTE)&Hooked_glEnd, 6);
	pglClear = (glClear_t)DetourFunc((LPBYTE)GetProcAddress(hOpenGL, "glClear"), (LPBYTE)&Hooked_glClear, 7);
	pglEnable = (glEnable_t)DetourFunc((LPBYTE)GetProcAddress(hOpenGL, "glEnable"), (LPBYTE)&Hooked_glEnable, 6);
	pglDisable = (glEnable_t)DetourFunc((LPBYTE)GetProcAddress(hOpenGL, "glDisable"), (LPBYTE)&Hooked_glDisable, 6);
	pSwapBuffers = (SwapBuffers_t)DetourFunc((LPBYTE)GetProcAddress(hGDI, "SwapBuffers"), (LPBYTE)&Hooked_SwapBuffers, 6);
}


void BuildFonts()
{
	hDC = wglGetCurrentDC();

	FontBase = glGenLists(96);
	hFont = CreateFont(-12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "System"); //"Lucida Console");					
	hOldFont = (HFONT)SelectObject(hDC, hFont);
	wglUseFontBitmaps(hDC, 32, 96, FontBase);
	SelectObject(hDC, hOldFont);
	DeleteObject(hFont);

	FontBaseUnderline = glGenLists(96);
	hFont = CreateFont(-10, 0, 0, 0, FW_NORMAL, FALSE, TRUE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "System");
	hOldFont = (HFONT)SelectObject(hDC, hFont);
	wglUseFontBitmaps(hDC, 32, 96, FontBaseUnderline);
	SelectObject(hDC, hOldFont);
	DeleteObject(hFont);

	FontBaseBig = glGenLists(96);
	hFont = CreateFont(-14, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "System");
	hOldFont = (HFONT)SelectObject(hDC, hFont);
	wglUseFontBitmaps(hDC, 32, 96, FontBaseBig);
	SelectObject(hDC, hOldFont);
	DeleteObject(hFont);

	bFontsBuild = true;
}

// ----------------------------------------------------------------------

void glPrint(int x, int y, const char *fmt, ...)
{
	if (!bFontsBuild) BuildFonts();

	if (fmt == NULL)	return;

	glRasterPos2i(x, y);

	char		text[256];
	va_list		ap;

	va_start(ap, fmt);
	vsprintf(text, fmt, ap);
	va_end(ap);

	glPushAttrib(GL_LIST_BIT);
	glListBase(FontBase - 32);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}

// ----------------------------------------------------------------------

void glPrintUnderline(int x, int y, const char *fmt, ...)
{
	if (!bFontsBuild) BuildFonts();

	if (fmt == NULL)	return;

	glRasterPos2i(x, y);

	char		text[256];
	va_list		ap;

	va_start(ap, fmt);
	vsprintf(text, fmt, ap);
	va_end(ap);

	glPushAttrib(GL_LIST_BIT);
	glListBase(FontBaseUnderline - 32);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}

// ----------------------------------------------------------------------

void glPrintBig(int x, int y, const char *fmt, ...)
{
	if (!bFontsBuild) BuildFonts();

	if (fmt == NULL)	return;

	glRasterPos2i(x, y);

	char		text[256];
	va_list		ap;

	va_start(ap, fmt);
	vsprintf(text, fmt, ap);
	va_end(ap);
	glPushAttrib(GL_LIST_BIT);
	glColor3f(0, 160, 255);
	glListBase(FontBaseBig - 32);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}

void DrawBox(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height)
{
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x + width, y, z);
	glVertex3f(x + width, y + height, z);
	glVertex3f(x, y + height, z);
	glEnd();
}

void DrawRectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	glVertex2f(x, y);
	glVertex2f(x+width, y);
	glVertex2f(x+width, y+height);
	glVertex2f(x, y+height);
	glVertex2f(x, y);
	glEnd();
}
void DrawWatermark(const char* watermark, bool randcol, GLfloat R, GLfloat G, GLfloat B) {
//	DrawRectangle(400, 3, 97, 10);
	glPushAttrib(GL_CURRENT_BIT);
	if (randcol) {
		R = (rand() % 1000 + 1) / 100;
		G = (rand() % 1000 + 1) / 100;
		B = (rand() % 1000 + 1) / 100;
	}
	glColor3f(R, G, B);
	glPrintBig(400, 9, watermark);
	glPopAttrib();

}
