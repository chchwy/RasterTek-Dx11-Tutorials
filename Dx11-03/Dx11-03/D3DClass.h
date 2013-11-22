
#ifndef D3D_CLASS_H
#define D3D_CLASS_H

#include <windows.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>


class D3DClass
{
public:
    D3DClass();
    ~D3DClass();

    bool Initialize( int, int, bool, HWND, bool, float, float );
    void Shutdown();
    void BeginScene( float, float, float, float );
    void EndScene();
};

#endif

