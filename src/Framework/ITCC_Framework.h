/****************************************************************************
*  ITCC_Framework.h, Version 1.0                                            *
*  Copyright (C) 2004 by Daniel Wilhelm                                     *
*  Written by Daniel Wilhelm <danny@wildfiregames.com>                      *
*                                                                           *
*  The code contained in this file is prohibited from being used            *
*  for commercial purposes of an academic instituiton or otherwise. No      *
*  duplication or distribution of this source file is allowed without       *
*  the author's consent.                                                    *
*****************************************************************************/
#pragma once

#include <windows.h>
#include <stdio.h>

///////////////////////////////
// DLL Code                   /
///////////////////////////////
#ifdef BUILD_GFXLIB
	#include <ddraw.h>				// DirectDraw
	
	#pragma comment (lib, "ddraw.lib")
#endif

///////////////////////////////
// Definitions                /
///////////////////////////////

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

#define ITCC_MSGBOX(msg)		MessageBox (NULL, msg, "Info", MB_OK)
#define ITCC_MSGBOX_WARN(msg)	MessageBox (NULL, msg, "Warning", MB_ICONWARNING | MB_OK)

#define ITCC_WINDOWED	1
#define ITCC_FULLSCREEN	2
#define ITCC_PRIMARY	4

#define MAX_LOADSTRING	100		// string limit for loading from a resource

#define RGB16a(r,g,b)	(((b) >> 3) + (((g) >> 3) << 5) + (((r) >> 3) << 10))
#define RGB16b(r,g,b)	(((b) >> 3) + (((g) >> 3) << 6) + (((r) >> 3) << 11))
#define RGB32(r,g,b)	(((r) << 16) + ((g) << 8) + (b))

///////////////////////////////
// Function Declarations      /
///////////////////////////////

class ITCC
{
#ifdef BUILD_GFXLIB
private:
	HWND m_hWnd;							// the rendering window
	HINSTANCE m_hInst;						// current instance
	CHAR m_szTitle2[MAX_LOADSTRING];			// the title bar text
	CHAR m_szWindowClass[MAX_LOADSTRING];	// the main window class name
	CHAR m_szTitle[MAX_LOADSTRING];

	LPDIRECTDRAW7			m_lpdd7;		// dd interface
	LPDIRECTDRAWSURFACE7	m_lpddsprimary; // dd primary surface
	LPDIRECTDRAWSURFACE7	m_lpddsback;	// dd backbuffer
	LPDIRECTDRAWSURFACE7	m_lpddsSurface;	// dd surface rendered to
	LPDIRECTDRAWCLIPPER		m_lpddclipper;	// dd for clipping a surface

	int		m_gfxFlags;			// current rendering mode flags
	HANDLE	m_AppActive;		// whether the app is active
	BOOL	m_AppClose;			// whether the app was asked to close
	HANDLE	m_pgdcThread;		// rendering thread

	DWORD m_xRes;
	DWORD m_yRes;
	DWORD m_bpp; 
	DWORD m_pitch;
	char *m_vidbuf;

	int (*m_MainPtr)(ITCC *);

	BOOL InitInstance(HINSTANCE, BOOL);
	ATOM MyRegisterClass(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	static DWORD WINAPI MainLoop(LPVOID lpParameter);
	void Init(void);

	void CloseApp(void);
	HANDLE GetThread(void);
	HANDLE AppActive(void);

	static ITCC *m_itcc;
#endif
public:
	// Constructor/deconstructor
	ITCC();
	~ITCC();

	// Framework essentials
	void *InitFullScreen(DWORD xRes, DWORD yRes, DWORD bpp, char *appTitle = "", int flags = 0);
	void *InitWindowed(DWORD xRes, DWORD yRes, char *appTitle = "", int flags = 0);
	void *SetVideoMode(DWORD *xRes, DWORD *yRes, DWORD *bpp, DWORD *pitch, int flags);
	void *Flip(void);
	void Exit(void);
	void CleanUp(void);

	// Graphics functions (to be replaced later)
	void Clear(void);
	void SetPixel(int x, int y, DWORD color);
	void Text(char *msg, int x, int y, COLORREF color);
	void MsgBox(char *title, char *msg);

	// Misc functions (DO NOT CALL)
	int WindowsInit(HINSTANCE hInstance, int (*MainPtr)(ITCC *));
	static ITCC *Get_ITCC(void);
};