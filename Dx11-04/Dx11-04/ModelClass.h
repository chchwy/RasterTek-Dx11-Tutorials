
#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <d3d11.h>
#include <DirectXMath.h>

using DirectX::XMFLOAT3;
using DirectX::XMFLOAT4;


class ModelClass
{
public:

    struct VertexType 
    {
        XMFLOAT3 position;
        XMFLOAT4 color;
    };

    ModelClass();
    ~ModelClass();

    bool Initialize( ID3D11Device* );
    void Shutdown();
    void Render( ID3D11DeviceContext* );

    int GetIndexCount();
private:
    bool CreateBuffer( ID3D11Device* );
    void ReleaseBuffer() { }
    void RenderBuffer( ID3D11DeviceContext* );

    ID3D11Buffer* m_pVertexBuffer;
    ID3D11Buffer* m_pIndexBuffer;

    int m_vertexCount;
    int m_indexCount;
};

#endif