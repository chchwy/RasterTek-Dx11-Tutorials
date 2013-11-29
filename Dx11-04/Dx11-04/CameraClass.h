#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <DirectXMath.h>

using DirectX::XMFLOAT3;
using DirectX::XMMATRIX;
using DirectX::XMFLOAT4X4;

class CameraClass
{
public:
    CameraClass();
    ~CameraClass();

    void setPosition( float, float, float );
    void setRotation( float, float, float );

    XMFLOAT3 GetPosition();
    XMFLOAT3 GetRotation();

    void Render();
    void GetViewMatrix( XMMATRIX& );

private:
    XMFLOAT3 m_position;
    XMFLOAT3 m_rotation;

    XMFLOAT4X4 m_viewMatrix;
};

#endif

