// Dx11-01.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Dx11-01.h"
#include "SystemClass.h"

int APIENTRY _tWinMain( _In_ HINSTANCE hInstance,
						_In_opt_ HINSTANCE hPrevInstance,
						_In_ LPTSTR    lpCmdLine,
						_In_ int       nCmdShow )
{
	SystemClass* pSystem;
	bool result;

	// Create the system object.
	pSystem = new SystemClass;
	if ( !pSystem )
	{
		return 0;
	}

	// Initialize and run the system object.
	result = pSystem->Initialize();
	if ( result )
	{
		pSystem->Run();
	}

	// Shutdown and release the system object.
	pSystem->Shutdown();
	delete pSystem;
	pSystem = 0;

	return 0;
}