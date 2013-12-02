
#include <windows.h>
#include <string>
#include <sstream>
#include "D3DClass.h"
#include "GraphicsClass.h"


GraphicsClass::GraphicsClass()
: m_pD3D( NULL )
, m_pColorShader( NULL )
, m_pModel( NULL )
, m_pCamera( NULL )
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

    m_pCamera = new CameraClass();
    m_pCamera->setPosition( 0, 0, -10 );

    m_pModel = new ModelClass();
    bResult = m_pModel->Initialize( m_pD3D->GetDevice() );

    if ( bResult == false )
    {
        MessageBox( hWnd, L"Could not initialize model.", L"ERROR", MB_OK );
        return false;
    }

    m_pColorShader = new ColorShaderClass();
    bResult = m_pColorShader->Initialize( m_pD3D->GetDevice(), hWnd );

    if ( bResult == false )
    {
        MessageBox( hWnd, L"Could not initialize the color shader.", L"ERROR", MB_OK );
        return false;
    }

    std::wostringstream sout;

    sout << "GraphicsClass init with (" << screenWidth << ", " << screenHeight << ").\n";
    OutputDebugString( sout.str().c_str() );

    return true;
}

bool GraphicsClass::Shutdown()
{
    if ( m_pColorShader )
    {
        m_pColorShader->Shutdown();
        delete m_pColorShader;
    }

    if ( m_pModel )
    {
        m_pModel->Shutdown();
        delete m_pModel;
    }

    if ( m_pCamera )
    {
        delete m_pCamera;
    }

    if ( m_pD3D )
    {
        m_pD3D->Shutdown();
        delete m_pD3D;
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

    XMMATRIX viewMatrix;
    XMMATRIX projectionMatrix;
    XMMATRIX worldMatrix;

    // Clear the buffers to begin the scene.
    m_pD3D->BeginScene( 0.0f, 0.0f, 0.0f, 1.0f );

    // Generate the view matrix based on the camera's position.
    m_pCamera->Render();

    // Get the world, view, and projection matrices from the camera and d3d objects.
    m_pCamera->GetViewMatrix( viewMatrix );
    m_pD3D->GetWorldMatrix( worldMatrix );
    m_pD3D->GetProjectionMatrix( projectionMatrix );

    // Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
    m_pModel->Render( m_pD3D->GetDeviceContext() );

    // Render the model using the color shader.
    bool bResult = m_pColorShader->Render( m_pD3D->GetDeviceContext(), 
                                           m_pModel->GetIndexCount(),
                                           worldMatrix, viewMatrix, projectionMatrix );
    if ( !bResult )
    {
        return false;
    }

    m_pD3D->EndScene();

    return true;
}
