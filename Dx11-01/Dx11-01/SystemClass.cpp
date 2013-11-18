

#include "stdafx.h"
#include <exception>
#include "SystemClass.h"


SystemClass::SystemClass() :
	m_Input( nullptr ),
	m_Graphics( nullptr )
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
	MSG msg;
	
	// Initialize the message structure.
	ZeroMemory( &msg, sizeof( MSG ) );

	// Loop until there is a quit message from the window or the user.
	bool done = false;
	bool result = false;

	while ( !done )
	{
		// Handle the windows messages.
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		// If windows signals to end the application then exit out.
		if ( msg.message == WM_QUIT )
		{
			done = true;
		}
		else
		{
			// Otherwise do the frame processing.
			result = Frame();
			if ( !result )
			{
				done = true;
			}
		}
	}
}

bool SystemClass::Shutdown()
{
	// Release the graphics object.
	if ( m_Graphics )
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// Release the input object.
	if ( m_Input )
	{
		delete m_Input;
		m_Input = 0;
	}

	// Shutdown the window.
	ShutdownWindows();

	return true;
}

void SystemClass::InitializeWindows( int screenWidth, int screenHeight )
{

}

void SystemClass::ShutdownWindows()
{

}

bool SystemClass::Frame()
{
	bool result;

	// Check if the user pressed escape and wants to exit the application.
	if ( m_Input->IsKeyDown( VK_ESCAPE ) )
	{
		return false;
	}

	// Do the frame processing for the graphics object.
	result = m_Graphics->Frame();
	if ( !result )
	{
		return false;
	}

	return true;
}
