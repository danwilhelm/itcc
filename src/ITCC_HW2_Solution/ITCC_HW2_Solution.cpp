/******************************************************************************
 *  ITCC_HW2_Solution.cpp	                                                  *
 *  Written by Daniel Wilhelm [danny@wildfiregames.com]  				      *
 ******************************************************************************/

#include <ITCC_Framework.h>

// the (fake) entry point for our application
int Main(ITCC *itcc)
{
	int xRes = 640, yRes = 480;	// height (y) and width (x) of screen
	int isRunning = TRUE;		// the game is running
	
	int paddleWidth  = 10;		// width of each paddle
	int paddleHeight = 40;		// height of each paddle
	int ballHeight   = 10;		// height of square ball
	int ballSpeed	 = 1;		// speed of the ball

	// initial (x,y) positions for the top of each paddle
	// (centered at the far left and right of the screen)
	int xPaddleFromEdge = 10;
	int xPaddleLeft  = xPaddleFromEdge;
	int yPaddleLeft  = yRes / 2 - paddleHeight / 2;
	int xPaddleRight = xRes - paddleWidth - xPaddleFromEdge;
	int yPaddleRight = yRes / 2 - paddleHeight / 2;

	// initial (x,y) position for the ball
	// (centered in the middle of the screen)
	int xBall = xRes / 2 - ballHeight / 2;
	int yBall = yRes / 2 - ballHeight / 2;
	
	// initial velocity of the ball
	// (move toward the bottom right)
	int xBallVel = 1;
	int yBallVel = 1;

	// indices for for loops
	int xIndex = 0, yIndex = 0;

	// colors of certain items
	unsigned long ballColor        = RGB32(255, 255, 255);  // white
	unsigned long paddleLeftColor  = RGB32(255,   0,   0);  // red
	unsigned long paddleRightColor = RGB32(  0, 255,   0);  // green
	unsigned long screenBoundColor = RGB32(  0, 255, 255);  // cyan



	/***********************
	* INITIALIZATION       *
	************************/
	itcc->InitWindowed(xRes, yRes, "HW2 Solution (Pong), by Daniel Wilhelm");
	itcc->MsgBox("Pong Instructions", "Left paddle: A/Z, Right paddle: Up/Down. To exit, press Escape.");


	/************************
	 * MAIN GAME LOOP       *
	 ************************/
	while (   (itcc->Flip())	// Makes back buffer visible
		   && (isRunning))		// While the game is still running
	{

		/////////////////////////////////////
		// RENDER GRAPHICS                 //
		/////////////////////////////////////

		itcc->Clear();   // Clear the background to black
		
		// Draw the ball
		for (xIndex=0; xIndex<ballHeight; xIndex++)
		{
			for (yIndex=0; yIndex<ballHeight; yIndex++)
			{
				itcc->SetPixel(xBall + xIndex, yBall + yIndex, ballColor);
			}
		}


		// Draw the left/right paddles
		for (xIndex=0; xIndex<paddleWidth; xIndex++)
		{
			for (yIndex=0; yIndex<paddleHeight; yIndex++)
			{
				itcc->SetPixel(xPaddleLeft  + xIndex, yPaddleLeft  + yIndex, paddleLeftColor );
				itcc->SetPixel(xPaddleRight + xIndex, yPaddleRight + yIndex, paddleRightColor);
			}
		}


		// Draw the top/bottom screen boundaries as dotted lines
		for (xIndex=0; xIndex<xRes; xIndex+=2)
		{
			itcc->SetPixel(xIndex,      0, screenBoundColor);
			itcc->SetPixel(xIndex, yRes-1, screenBoundColor);
		}



		/////////////////////////////////////
		// GAME LOGIC                      //
		/////////////////////////////////////
		
		// Bounce off the top and bottom wall
		if (yBall <= 0)
		{
			yBallVel = ballSpeed;
		}
		else if (yBall >= yRes - ballHeight)
		{
			yBallVel = -ballSpeed;
		}


		// bounce off the paddles
		// (+/- 1 for x calcs so ball goes in one before being missed)
		if (xBall < xPaddleLeft + paddleWidth - 1)
		{
			// did it hit the paddle?
			if (    (yBall >= yPaddleLeft - ballHeight)
				 && (yBall <= yPaddleLeft + paddleHeight))
			{
				xBallVel = ballSpeed;
			}
			else
			{
				itcc->MsgBox("WINNER!", "Right player wins! Congrats!");
				isRunning = FALSE;
			}
		}
		else if (xBall > xPaddleRight - ballHeight + 1)
		{
			// did it hit the paddle?
			if (   (yBall >= yPaddleRight - ballHeight)
				&& (yBall <= yPaddleRight + paddleHeight))
			{
				xBallVel = -ballSpeed;
			}
			else
			{
				itcc->MsgBox("WINNER!", "Left player wins! Congrats!");
				isRunning = FALSE;
			}
		}

		// ensure the paddles are in-bounds
		if (yPaddleLeft  <= 0)   { yPaddleLeft  = 0;  }
		if (yPaddleRight <= 0)   { yPaddleRight = 0;  }

		if (yPaddleLeft  >= yRes-paddleHeight) { yPaddleLeft  = yRes - paddleHeight; }
		if (yPaddleRight >= yRes-paddleHeight) { yPaddleRight = yRes - paddleHeight; }


		// calculate new ball coordinates
		xBall += xBallVel;
		yBall += yBallVel;


		/////////////////////////////////////
		// KEYBOARD INPUT                  //
		/////////////////////////////////////

		// keys control the paddle position
		if (KEYDOWN('A'))     {  yPaddleLeft--;  }
		if (KEYDOWN('Z'))     {  yPaddleLeft++;  }
		if (KEYDOWN(VK_UP))   {  yPaddleRight--; }
		if (KEYDOWN(VK_DOWN)) {  yPaddleRight++; }
		
		// escape key exists
		if (KEYDOWN(VK_ESCAPE)) {  isRunning = FALSE;  }



		// delay the timing 5 ms/frame so the ball isn't too fast
		Sleep(5);
  	}


	/***********************
	* SHUT DOWN            *
	************************/

	return 0;	// terminated successfully
}



//////////////////////////////////////////////////////////////////////////////
// DO NOT EDIT ANYTHING BELOW THIS POINT!
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
	static ITCC itcc;

	// Initialize the ITCC Windows Framework
	if (itcc.WindowsInit(hInstance, Main) == FALSE)
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