
#include "D3Dcompiler.h"
#include "D3DX11async.h"
#include "ColorShaderClass.h"


ColorShaderClass::ColorShaderClass()
: m_pVertexShader( NULL )
, m_pPixelShader( NULL )
, m_pMatrixBuffer( NULL )
, m_pInputLayout( NULL )
{

}


ColorShaderClass::~ColorShaderClass()
{
}

bool ColorShaderClass::Initialize( ID3D11Device* pDevice, HWND hWnd )
{
    return InitializeShader( pDevice, hWnd, L"color.vs", L"color.ps" );
}

void ColorShaderClass::Shutdown()
{
    ShutdownShader();
}


bool ColorShaderClass::Render( ID3D11DeviceContext* pContext, 
                               int indexCount,
                               XMMATRIX& worldMatrix, 
                               XMMATRIX& viewMatrix, 
                               XMMATRIX& projectionMatrix )
{
    bool bOK = SetShaderParameter( pContext, worldMatrix, viewMatrix, projectionMatrix );

    if ( !bOK )
    {
        return false;
    }

    RenderShader( pContext, indexCount );

    return true;
}

bool ColorShaderClass::InitializeShader( ID3D11Device* pDevice,
                                         HWND hWnd,
                                         WCHAR* strVertexShaderFilename,
                                         WCHAR* strPixelShaderFilename )
{
    HRESULT hr = S_OK;

    ID3DBlob* pVertexShaderBuffer = NULL;
    ID3DBlob* pPixelShaderBuffer = NULL;
    ID3DBlob* pErrorMessage = NULL;

    hr = D3DX11CompileFromFile( strVertexShaderFilename,
                                NULL,
                                NULL,
                                "ColorVertexShader",
                                "vs_5_0",
                                D3DCOMPILE_ENABLE_STRICTNESS, 0,
                                NULL,
                                &pVertexShaderBuffer,
                                &pErrorMessage,
                                NULL );

    if ( FAILED( hr ) )
    {
        if ( pErrorMessage != NULL )
        {
            OutputShaderErrorMessage( pErrorMessage, hWnd, strVertexShaderFilename );
        }
        else
        {
            // No error message, then it simply cannot find the shader file itself.
            MessageBox( hWnd, strVertexShaderFilename, L"Missing Shader File.", MB_OK );
        }
        return false;
    }


    hr = D3DX11CompileFromFile( strPixelShaderFilename, NULL, NULL,
                                "ColorPixelShader",
                                "ps_5_0",
                                D3DCOMPILE_ENABLE_STRICTNESS,
                                0, NULL,
                                &pPixelShaderBuffer,
                                &pErrorMessage,
                                NULL );

    if ( FAILED( hr ) )
    {
        if ( pErrorMessage != NULL )
        {
            OutputShaderErrorMessage( pErrorMessage, hWnd, strPixelShaderFilename );
        }
        else
        {
            // No error message, then it simply cannot find the shader file itself.
            MessageBox( hWnd, strPixelShaderFilename, L"Missing Shader File.", MB_OK );
        }
        return false;
    }

    hr = pDevice->CreateVertexShader( pVertexShaderBuffer->GetBufferPointer(),
                                      pVertexShaderBuffer->GetBufferSize(),
                                      NULL,
                                      &m_pVertexShader );
    if ( FAILED( hr ) )
    {
        return false;
    }

    hr = pDevice->CreatePixelShader( pPixelShaderBuffer->GetBufferPointer(),
                                     pPixelShaderBuffer->GetBufferSize(),
                                     NULL,
                                     &m_pPixelShader );
    if ( FAILED( hr ) )
    {
        return false;
    }

    D3D11_INPUT_ELEMENT_DESC inputLayouts[] = 
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR"   , 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    hr = pDevice->CreateInputLayout( inputLayouts, 2, 
                                     pVertexShaderBuffer->GetBufferPointer(),
                                     pVertexShaderBuffer->GetBufferSize(), 
                                     &m_pInputLayout );
    if ( FAILED( hr ) )
    {
        return false;
    }

    pVertexShaderBuffer->Release();
    pPixelShaderBuffer->Release();

    CD3D11_BUFFER_DESC matrixBufferDesc;
    matrixBufferDesc.ByteWidth = sizeof( MatrixBufferType );
    matrixBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    matrixBufferDesc.MiscFlags = 0;
    matrixBufferDesc.StructureByteStride = 0;

    hr = pDevice->CreateBuffer( &matrixBufferDesc, NULL, &m_pMatrixBuffer );

    if ( FAILED( hr ) )
    {
        return false;
    }

    return true;
}

bool ColorShaderClass::SetShaderParameter( ID3D11DeviceContext*, XMMATRIX&, XMMATRIX&, XMMATRIX& )
{
    return false;
}

void ColorShaderClass::RenderShader( ID3D11DeviceContext*, int )
{

}

