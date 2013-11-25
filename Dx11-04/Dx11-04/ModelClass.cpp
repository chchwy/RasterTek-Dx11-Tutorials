#include "stdafx.h"
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

    return true;
}

void ModelClass::RenderBuffer( ID3D11DeviceContext* )
{

}
