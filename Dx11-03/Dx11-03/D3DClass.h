
#ifndef D3D_CLASS_H
#define D3D_CLASS_H

#include <windows.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <DirectXMath.h>

using DirectX::XMMATRIX;


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
    ID3D11Device*        m_pDevice;
    ID3D11DeviceContext* m_pContext;
    IDXGISwapChain*      m_pSwapChain;

    ID3D11RenderTargetView*  m_pRenderTargetView;
    ID3D11Texture2D*         m_pDepthStencilBuffer;
    ID3D11DepthStencilState* m_pDepthStencilState;
    ID3D11DepthStencilView*  m_pDepthStencilView;
    ID3D11RasterizerState*   m_pRasterState;

    XMMATRIX m_projectionMatrix;
    XMMATRIX m_worldMatrix;
    XMMATRIX m_orthoMatrix;
};

#endif

