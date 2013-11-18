

#include "stdafx.h"
#include <exception>
#include "SystemClass.h"


SystemClass::SystemClass()
{
}


SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	bool result;


	// Initialize the width and height of the screen to zero before sending the variables into the function.
	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	InitializeWindows( screenWidth, screenHeight );

	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass;
	if ( !m_Input )
	{
		return false;
	}

	// Initialize the input object.
	m_Input->Initialize();

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new GraphicsClass;
	if ( !m_Graphics )
	{
		return false;
	}

	// Initialize the graphics object.
	result = m_Graphics->Initialize( screenWidth, screenHeight, m_hwnd );
	if ( !result )
	{
		return false;
	}

	return true;
}

void SystemClass::Run()
{

}

bool SystemClass::Shutdown()
{
	return true;
}

void SystemClass::InitializeWindows( int screenWidth, int screenHeight )
{
	throw std::exception( "The method or operation is not implemented." );
}
