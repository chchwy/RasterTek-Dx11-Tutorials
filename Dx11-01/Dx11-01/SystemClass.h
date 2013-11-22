
#ifndef SYSTEM_CLASS_H
#define SYSTEM_CLASS_H

#include <windows.h>
#include "InputClass.h"
#include "GraphicsClass.h"

#define WIN32_LEAN_AND_MEAN


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