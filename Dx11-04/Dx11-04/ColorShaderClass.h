
#ifndef COLOR_SHADER_H
#define COLOR_SHADER_H

//#include <D3DX11.h>
#include <d3d11.h>
#include <DirectXMath.h>

using DirectX::XMMATRIX;



class ColorShaderClass
{
    struct MatrixBufferType
    {
        XMMATRIX world;
        XMMATRIX view;
        XMMATRIX projection;
    };

public:
    ColorShaderClass();
    ~ColorShaderClass();

    bool Initialize( ID3D11Device*, HWND );
    void Shutdown();
    bool Render( ID3D11DeviceContext*, int, XMMATRIX&, XMMATRIX&, XMMATRIX& );

private:
    bool InitializeShader( ID3D11Device*, HWND, WCHAR*, WCHAR* );
    void ShutdownShader();
    void OutputShaderErrorMessage( ID3DBlob*, HWND, WCHAR* ) { }

    bool SetShaderParameter( ID3D11DeviceContext*, XMMATRIX&, XMMATRIX&, XMMATRIX& );
    void RenderShader( ID3D11DeviceContext*, int );

    ID3D11VertexShader* m_pVertexShader;
    ID3D11PixelShader* m_pPixelShader;
    ID3D11InputLayout* m_pInputLayout;
    ID3D11Buffer* m_pMatrixBuffer;
};

#endif