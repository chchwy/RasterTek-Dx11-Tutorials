
#include "D3DClass.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")


#define SAFE_RELEASE(x) if(x) { x->Release(); x = NULL; }


D3DClass::D3DClass() :
m_pDevice( nullptr ),
m_pContext( nullptr ),
m_pSwapChain( nullptr ),
m_pRenderTargetView( nullptr ),
m_pDepthStencilBuffer( nullptr ),
m_pDepthStencilState( nullptr ),
m_pDepthStencilView( nullptr ),
m_pRasterState( nullptr )
{

}

D3DClass::~D3DClass()
{
}

bool D3DClass::Initialize( int screenWidth, int screenHeight,
                           bool bVsync,
                           HWND hWnd,
                           bool bFullScreen,
                           float screenDepth,
                           float screenNear )
{

    // Create swap chain, device and device context
    UINT createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;

    D3D_FEATURE_LEVEL myFeatureLevel;

    DXGI_SWAP_CHAIN_DESC sd;
    sd.BufferDesc.Width = screenWidth;
    sd.BufferDesc.Height = screenHeight;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;

    sd.BufferCount  = 1;
    sd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.Windowed     = !bFullScreen;
    sd.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags        = 0;

    HRESULT hr = D3D11CreateDeviceAndSwapChain( NULL,  // Default Adapter
                                                D3D_DRIVER_TYPE_HARDWARE,
                                                NULL,  // No software device
                                                createDeviceFlags,
                                                0, 0,  // Use default feature list
                                                D3D11_SDK_VERSION,
                                                &sd,
                                                &m_pSwapChain, 
                                                &m_pDevice,
                                                &myFeatureLevel,
                                                &m_pContext );

    if ( FAILED( hr ) )
    {
        return false;
    }

    if ( myFeatureLevel != D3D_FEATURE_LEVEL_11_0 )
    {
        return false;
    }

    // Set back buffer and render target
    ID3D11Texture2D* pBackBuffer = NULL;
    m_pSwapChain->GetBuffer( 0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);

    hr = m_pDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_pRenderTargetView );
    if ( FAILED( hr ) )
    {
        return false;
    }
    SAFE_RELEASE( pBackBuffer );

    return true;
}

void D3DClass::Shutdown()
{

}

void D3DClass::BeginScene( float, float, float, float )
{

}

void D3DClass::EndScene()
{

}

void D3DClass::GetProjectionMatrix( XMMATRIX& )
{

}

void D3DClass::GetWorldMatrix( XMMATRIX& )
{

}

void D3DClass::GetOrthoMatrix( XMMATRIX& )
{

}

void D3DClass::GetVideoCardInfo( char*, int& )
{

}
