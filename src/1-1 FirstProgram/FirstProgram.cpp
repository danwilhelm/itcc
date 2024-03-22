/******************************************************************************
 *  FirstProgam.cpp, Version 1.0	                                          *
 *  Written by Daniel Wilhelm <danny@wildfiregames.com>                       *
 *                                                                            *
 * TODO:							                                          *
 * (1) Modify the text printed so that it displays a different message.       *
 * (2) Add some more line breaks before the "press any key" message.          *
 * (3) Comment out the 'using namespace std;' line, then try to compile the   *
 *     file. Note the errors, then add 'std::' immediately in front of 'cout' *
 *     and try recompiling. Note the errors, then add 'std::' immediately in  *
 *	   front of 'endl' and rebuild the project. Forgetting to add the         *
 *	   'using namespace std' line or 'std::'s is a common source of errors    *
 *	   for new C++ programmers!                                               *
 *                                                                            *
 * HINT: See the first lecture slides for how this program works!             *
 ******************************************************************************/

#include <iostream>
#include <conio.h>

using namespace std;

// Application point of entry
int main(void)
{
	cout << "Hello, world!" << endl;
	getch();

	return 0;	// terminated normally
}

