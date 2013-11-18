
#ifndef SYSTEM_CLASS_H
#define SYSTEM_CLASS_H

#include <windows.h>

#define WIN32_LEAN_AND_MEAN

class InputClass 
{
public:
	bool Initialize() { return true;  }
};

class GraphicsClass
{
public:
	bool Initialize( int, int, HWND ) { return true; }
};


class SystemClass
{
public:
	SystemClass();
	~SystemClass();
	bool Initialize();
	void Run();
	bool Shutdown();

private:
	void InitializeWindows( int screenWidth, int screenHeight );

	InputClass* m_Input;
	GraphicsClass* m_Graphics;

	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
};

#endif