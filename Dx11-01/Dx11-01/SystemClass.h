
#ifndef SYSTEM_CLASS_H
#define SYSTEM_CLASS_H

#include <windows.h>

#define WIN32_LEAN_AND_MEAN

class InputClass 
{
public:
	bool Initialize() { return true;  }
	bool IsKeyDown( int nKeyCode ) { return false; }
	void KeyDown( unsigned int nKeyCode ) {}
	void KeyUp( unsigned int nKeyCode ) {}
};

class GraphicsClass
{
public:
	bool Initialize( int, int, HWND ) { return true; }
	bool Shutdown() { return true; }

	bool Frame() { return true; }
};


class SystemClass
{
public:
	SystemClass();
	~SystemClass();
	bool Initialize();
	void Run();
	bool Shutdown();
	
	LRESULT CALLBACK MessageHandler( HWND, UINT, WPARAM, LPARAM );

private:
	void InitializeWindows( int& screenWidth, int& screenHeight );
	void ShutdownWindows();
	bool Frame();

	InputClass* m_Input;
	GraphicsClass* m_Graphics;

	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
};

#endif