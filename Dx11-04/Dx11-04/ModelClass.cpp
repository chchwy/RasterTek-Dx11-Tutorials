#include <stdint.h>
#include "ModelClass.h"


ModelClass::ModelClass()
: m_pVertexBuffer( nullptr )
, m_pIndexBuffer( nullptr )
, m_vertexCount( 0 )
, m_indexCount( 0 )
{
}


ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize( ID3D11Device* pDevice )
{
    return CreateBuffer( pDevice );
}

void ModelClass::Shutdown()
{
    ReleaseBuffer();
}

void ModelClass::Render( ID3D11DeviceContext* pContext )
{
    RenderBuffer( pContext );
}

int ModelClass::GetIndexCount()
{
    return m_indexCount;
}

bool ModelClass::CreateBuffer( ID3D11Device* pDevice )
{
    m_indexCount = 3;
    m_vertexCount = 3;

    VertexType* pVertex = new VertexType[ m_vertexCount ];
    
    pVertex[ 0 ].position = XMFLOAT3( -1, -1, 0 );
    pVertex[ 0 ].color = XMFLOAT4( 0, 1, 0, 0 );
    pVertex[ 1 ].position = XMFLOAT3( 0, 1, 0 );
    pVertex[ 1 ].color = XMFLOAT4( 1, 0, 0, 0 );
    pVertex[ 2 ].position = XMFLOAT3( 1, -1, 0 );
    pVertex[ 2 ].color = XMFLOAT4( 0, 0, 1, 0 );

    D3D11_BUFFER_DESC vertexBufferDesc;
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof( VertexType ) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA vertexData;
    vertexData.pSysMem = pVertex;
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;

    HRESULT hr = pDevice->CreateBuffer( &vertexBufferDesc, &vertexData, &m_pVertexBuffer );
    if ( FAILED( hr ) )
    {
        delete[] pVertex;
        return false;
    }

    uint32_t* pIndices = new uint32_t[ m_indexCount ];
    pIndices[ 0 ] = 0;
    pIndices[ 1 ] = 1;
    pIndices[ 2 ] = 2;

    D3D11_BUFFER_DESC indexBufferDesc;
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof( uint32_t ) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA indexData;
    indexData.pSysMem = pIndices;
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;

    hr = pDevice->CreateBuffer( &indexBufferDesc, &indexData, &m_pIndexBuffer );
    if ( FAILED( hr ) )
    {
        delete[] pIndices;
        return false;
    }

    delete[] pVertex;
    delete[] pIndices;

    return true;
}

void ModelClass::RenderBuffer( ID3D11DeviceContext* pContext )
{
    uint32_t stride = sizeof( VertexType );
    uint32_t offset = 0;

    pContext->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &stride, &offset );
    pContext->IASetIndexBuffer( m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0 );

    pContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
}
