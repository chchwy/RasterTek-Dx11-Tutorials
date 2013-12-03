
#include <cstring>
#include "CameraClass.h"

using namespace DirectX;

CameraClass::CameraClass()
: m_position( 0, 0, 0 )
, m_rotation( 0, 0, 0 )
{
    memset( &m_viewMatrix, 0, sizeof( XMFLOAT4X4 ) );
}


CameraClass::~CameraClass()
{
}

void CameraClass::setPosition( float x, float y, float z)
{
    m_position = XMFLOAT3( x, y, z );
}

void CameraClass::setRotation( float x, float y, float z )
{
    m_rotation = XMFLOAT3( x, y, z );
}

XMFLOAT3 CameraClass::GetPosition()
{
    return m_position;
}

XMFLOAT3 CameraClass::GetRotation()
{
    return m_rotation;
}

void CameraClass::Render()
{
    XMVECTOR up = XMLoadFloat3( &XMFLOAT3( 0, 1, 0 ) );
    XMVECTOR position = XMLoadFloat3( &m_position );
    XMVECTOR lookAt = XMLoadFloat3( &XMFLOAT3( 0, 0, 1 ) );

    float pitch = XMConvertToRadians( m_rotation.x );
    float yaw   = XMConvertToRadians( m_rotation.y );
    float roll  = XMConvertToRadians( m_rotation.z );
    
    XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw( pitch, yaw, roll );

    lookAt = XMVector3TransformCoord( lookAt, rotationMatrix );
    up = XMVector3TransformCoord( up, rotationMatrix );

    lookAt = position + lookAt;

    XMMATRIX viewMatrix = XMMatrixLookAtLH( position, lookAt, up );
    XMStoreFloat4x4( &m_viewMatrix , viewMatrix );
}

void CameraClass::GetViewMatrix( XMMATRIX& viewMatrix )
{
    viewMatrix = XMLoadFloat4x4( &m_viewMatrix );
}
