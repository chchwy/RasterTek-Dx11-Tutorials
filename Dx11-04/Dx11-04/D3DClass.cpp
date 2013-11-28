
#include "DirectXColors.h"
#include "D3DClass.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")


using namespace DirectX;




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

    // Initialize depth buffer
    D3D11_TEXTURE2D_DESC dd;
    memset( &dd, 0, sizeof( D3D11_TEXTURE2D_DESC ) );

    dd.Width = screenWidth;
    dd.Height = screenHeight;
    dd.MipLevels = 1;
    dd.ArraySize = 1;
    dd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dd.SampleDesc.Count = 1;
    dd.SampleDesc.Quality = 0;
    dd.Usage = D3D11_USAGE_DEFAULT;
    dd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    dd.CPUAccessFlags = 0;
    dd.MiscFlags = 0;

    hr = m_pDevice->CreateTexture2D( &dd, 0, &m_pDepthStencilBuffer );
    if ( FAILED( hr ) )
    {
        return false;
    }
    
    CD3D11_DEPTH_STENCIL_DESC dsd;

    dsd.DepthEnable = true;
    dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsd.DepthFunc = D3D11_COMPARISON_LESS;

    dsd.StencilEnable = true;
    dsd.StencilReadMask = 0xFF;
    dsd.StencilWriteMask = 0xFF;
    
    dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    
    dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    
    hr = m_pDevice->CreateDepthStencilState( &dsd, &m_pDepthStencilState );
    if ( FAILED( hr ) )
    {
        return false;
    }
    m_pContext->OMSetDepthStencilState( m_pDepthStencilState, 1 );
    
    // Create depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
    dsvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsvd.Texture2D.MipSlice = 0;

    m_pDevice->CreateDepthStencilView( m_pDepthStencilBuffer, &dsvd, &m_pDepthStencilView );

    // Set Render target
    m_pContext->OMSetRenderTargets( 1, &m_pRenderTargetView, m_pDepthStencilView );

    // Set Rasterizer state
    CD3D11_RASTERIZER_DESC rd( D3D11_DEFAULT );

    hr = m_pDevice->CreateRasterizerState( &rd, &m_pRasterState );
    if ( FAILED( hr ) )
    {
        return false;
    }

    m_pContext->RSSetState( m_pRasterState );

    // Set viewport
    D3D11_VIEWPORT viewPort;
    viewPort.Width = static_cast<float>(screenWidth);
    viewPort.Height = static_cast<float>(screenHeight);
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;

    m_pContext->RSSetViewports( 1, &viewPort );

    float filedOfView = XM_PI / 4.0f;
    float screenAspect = ( float )screenWidth / ( float )screenHeight;
    
    m_projectionMatrix = XMMatrixPerspectiveFovLH( filedOfView, screenAspect, screenNear, screenDepth );
    m_worldMatrix = XMMatrixIdentity();
    m_orthoMatrix = XMMatrixOrthographicLH( screenWidth, screenHeight, screenNear, screenDepth );

    return true;
}

void D3DClass::Shutdown()
{
    if ( m_pSwapChain )
    {
        m_pSwapChain->SetFullscreenState( false, NULL );
    }

    SAFE_RELEASE( m_pRasterState );
    SAFE_RELEASE( m_pDepthStencilView );
    SAFE_RELEASE( m_pDepthStencilState );
    SAFE_RELEASE( m_pDepthStencilBuffer );
    SAFE_RELEASE( m_pRenderTargetView );
    SAFE_RELEASE( m_pDevice );
    SAFE_RELEASE( m_pContext );
    SAFE_RELEASE( m_pSwapChain );

}

void D3DClass::BeginScene( float, float, float, float )
{
    m_pContext->ClearRenderTargetView( m_pRenderTargetView, Colors::Blue );
}

void D3DClass::EndScene()
{
    m_pSwapChain->Present( 1, 0 );
}

void D3DClass::GetProjectionMatrix( XMMATRIX& projectionMatrix )
{
    projectionMatrix = m_projectionMatrix;
}

void D3DClass::GetWorldMatrix( XMMATRIX& worldMatrix )
{
    worldMatrix = m_worldMatrix;
}

void D3DClass::GetOrthoMatrix( XMMATRIX& orthoMatrix )
{
    orthoMatrix = m_orthoMatrix;
}

void D3DClass::GetVideoCardInfo( char*, int& )
{

}
