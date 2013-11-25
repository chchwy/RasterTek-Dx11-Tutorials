
//
// Dx11-04
//

#include <tchar.h>
#include "SystemClass.h"

int APIENTRY _tWinMain( _In_ HINSTANCE hInstance,
                        _In_opt_ HINSTANCE hPrevInstance,
                        _In_ LPTSTR    lpCmdLine,
                        _In_ int       nCmdShow )
{
    // Create the system object.
    SystemClass* pSystem = new SystemClass;
    if ( !pSystem )
    {
        return 0;
    }

    // Initialize and run the system object.
    bool bResult = pSystem->Initialize();
    if ( bResult )
    {
        pSystem->Run();
    }

    // Shutdown and release the system object.
    pSystem->Shutdown();
    delete pSystem;
    pSystem = 0;

    return 0;
}