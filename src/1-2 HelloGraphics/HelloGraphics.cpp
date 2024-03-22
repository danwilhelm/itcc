/******************************************************************************
 *  HelloGraphics.cpp, Version 1.0	                                          *
 *  Written by Daniel Wilhelm <danny@wildfiregames.com>                       *
 *                                                                            *
 * TODO:	               						                              *
 *  (1) Change the text displayed and its position                            *
 *  (2) Change the size of the window                                         *
 *  (3) Try commenting out the itcc->Clear() command. What happens?           *
 *                                                                            *
 * **IMPORTANT NOTE** Some known bugs exist that allow graphics to be         *
 * rendered at inappropriate places on the desktop. These bugs are currently  *
 * being worked out. Please report any other bugs to my address above.        *
 ******************************************************************************/

#include "../Framework/ITCC_Framework.h"
#pragma comment(lib, "../Framework/ITCC_Framework.lib")

// the (fake) entry point for our application
int Main(ITCC *itcc)
{
	itcc->InitWindowed(640, 480);

	/************************
	 * MAIN GRAPHICS LOOP   *
	 ************************/
	while (itcc->Flip() != NULL)
	{
		itcc->Clear();
		itcc->Text ("Hello World!", 0, 0, RGB(255,0,0));
  	}

	return 0;	// terminated successfully
}





//////////////////////////////////////////////////////////////////////////////
// DO NOT EDIT BELOW THIS POINT
//////////////////////////////////////////////////////////////////////////////

/*****************************************************************************
/ WinMain (app entry point)
/     hInstance: The ID of this instance of the application
/ hPrevInstance: The last instance of this application (always NULL)
/     lpCmdLine: Command line parameters passed
/      nCmdShow: How this window should be displayed
/
/ Returns: Exit code (sent to the OS) - 0 if successful exit
/ Remarks: 
/   
/*****************************************************************************/
int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPTSTR    lpCmdLine,
					 int       nCmdShow)
{
	MSG msg;
	ITCC itcc(Main);

	// Initialize the ITCC Windows Framework
	if (itcc.WindowsInit(hInstance, TRUE) == FALSE)
	{
		ITCC_MSGBOX_WARN("Window did not correctly initialize!");
		return 0;
	}

	// Main message loop
	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}

	return (int) msg.wParam;
}