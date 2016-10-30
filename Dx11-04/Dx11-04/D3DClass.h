
#ifndef D3D_CLASS_H
#define D3D_CLASS_H

#include <windows.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <DirectXMath.h>

using DirectX::XMMATRIX;

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if(x) { x->Release(); x = NULL; }
#endif


class D3DClass
{
public:
    D3DClass();
    ~D3DClass();

    bool Initialize( int screenWidth, int screenHeight, 
                     bool bVsync, HWND hWnd, bool bFullScreen, 
                     float screenDepth, float screenNear );
    void Shutdown();
    void BeginScene( float, float, float, float );
    void EndScene();

    ID3D11Device* GetDevice() { return m_pDevice; }
    ID3D11DeviceContext* GetDeviceContext() { return m_pContext; }

    void GetProjectionMatrix( XMMATRIX& );
    void GetWorldMatrix( XMMATRIX& );
    void GetOrthoMatrix( XMMATRIX& );

    void GetVideoCardInfo( char*, int& );

private:
    ID3D11Device*        m_pDevice = nullptr;
    ID3D11DeviceContext* m_pContext = nullptr;
    IDXGISwapChain*      m_pSwapChain = nullptr;

    ID3D11RenderTargetView*  m_pRenderTargetView = nullptr;
    ID3D11Texture2D*         m_pDepthStencilBuffer = nullptr;
    ID3D11DepthStencilState* m_pDepthStencilState = nullptr;
    ID3D11DepthStencilView*  m_pDepthStencilView = nullptr;
    ID3D11RasterizerState*   m_pRasterState = nullptr;

    XMMATRIX m_projectionMatrix;
    XMMATRIX m_worldMatrix;
    XMMATRIX m_orthoMatrix;
};

#endif

