
#include <fstream>
#include "D3Dcompiler.h"
#include "D3DX11async.h"
#include "ColorShaderClass.h"


#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if (x) { x->Release(); x = NULL; }
#endif

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
    return InitializeShader( pDevice, hWnd, L"ColorVertexShader.hlsl", L"ColorPixelShader.hlsl" );
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
                                D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG,
                                0,
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
                                D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG,
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
    
    ID3D11ClassLinkage* pClassLinkage = nullptr;
    pDevice->CreateClassLinkage( &pClassLinkage );

    hr = pDevice->CreatePixelShader( pPixelShaderBuffer->GetBufferPointer(),
                                     pPixelShaderBuffer->GetBufferSize(),
                                     pClassLinkage,
                                     &m_pPixelShader );
    if ( FAILED( hr ) )
    {
        return false;
    }

    D3D11_INPUT_ELEMENT_DESC inputLayouts[] = 
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
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

    D3D11_BUFFER_DESC matrixBufferDesc;
    matrixBufferDesc.ByteWidth = sizeof( MatrixBufferType );
    matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
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

void ColorShaderClass::ShutdownShader()
{
    SAFE_RELEASE( m_pMatrixBuffer );
    SAFE_RELEASE( m_pInputLayout );
    SAFE_RELEASE( m_pVertexShader );
    SAFE_RELEASE( m_pPixelShader );
}

bool ColorShaderClass::SetShaderParameter( ID3D11DeviceContext* pContext, 
                                           XMMATRIX& worldMatrix, 
                                           XMMATRIX& viewMatrix, 
                                           XMMATRIX& projectionMatrix )
{
    HRESULT hr = S_OK;

    worldMatrix = XMMatrixTranspose( worldMatrix );
    viewMatrix = XMMatrixTranspose( viewMatrix );
    projectionMatrix = XMMatrixTranspose( projectionMatrix );

    D3D11_MAPPED_SUBRESOURCE mappedResource;
    hr = pContext->Map( m_pMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource );

    if ( FAILED( hr ) )
    {
        return false;
    }

    MatrixBufferType* pData = ( MatrixBufferType* )mappedResource.pData;
    pData->world = worldMatrix;
    pData->view = viewMatrix;
    pData->projection = projectionMatrix;

    pContext->Unmap( m_pMatrixBuffer, 0 );

    pContext->VSSetConstantBuffers( 0, 1, &m_pMatrixBuffer );

    return true;
}

void ColorShaderClass::RenderShader( ID3D11DeviceContext* pContext, int indexCount )
{
    pContext->IASetInputLayout( m_pInputLayout );

    pContext->VSSetShader( m_pVertexShader, NULL, 0 );
    pContext->PSSetShader( m_pPixelShader, NULL, 0 );

    pContext->DrawIndexed( indexCount, 0, 0 );
}

void ColorShaderClass::OutputShaderErrorMessage( ID3DBlob* pErrorMessage, 
                                                 HWND hWnd , 
                                                 WCHAR* strShaderFilename )
{
    std::ofstream fout;

    // Get a pointer to the error message text buffer.
    char* strCompileErrors = ( char* )( pErrorMessage->GetBufferPointer( ) );

    // Get the length of the message.
    uint32_t bufferSize = pErrorMessage->GetBufferSize();

    // Open a file to write the error message to.
    fout.open( "shader-error.txt" );

    // Write out the error message.
    for ( int i = 0; i < bufferSize; i++ )
    {
        fout << strCompileErrors[ i ];
    }

    // Close the file.
    fout.close();

    // Release the error message.
    pErrorMessage->Release();
    pErrorMessage = 0;

    // Pop a message up on the screen to notify the user to check the text file for compile errors.
    MessageBox( hWnd, L"Error compiling shader.  Check shader-error.txt for message.", strShaderFilename, MB_OK );
}



