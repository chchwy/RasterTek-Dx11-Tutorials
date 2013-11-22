
#include <windows.h>
#include "D3DClass.h"
#include "GraphicsClass.h"


GraphicsClass::GraphicsClass()
: m_pD3D( nullptr )
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize( int screenWidth, int screenHeight, HWND hWnd )
{
    m_pD3D = new D3DClass;
    if ( m_pD3D == NULL )
    {
        return false;
    }

    bool bResult = m_pD3D->Initialize( screenWidth, screenHeight, 
                                       VSYNC_ENABLED,
                                       hWnd,
                                       FULL_SCREEN,
                                       SCREEN_DEPTH,
                                       SCREEN_NEAR );

    if ( bResult == false )
    {
        MessageBox( hWnd, L"Could not initialize Direct3D", L"Error", MB_OK );
        return false;
    }
    return true;
}

bool GraphicsClass::Shutdown()
{
    if ( m_pD3D )
    {
        m_pD3D->Shutdown();
    }
    return true;
}

bool GraphicsClass::Frame()
{
    return Render();
}

bool GraphicsClass::Render()
{
    m_pD3D->BeginScene( 0.5, 0.5, 0.5, 1 );

    m_pD3D->EndScene();
    return true;
}
