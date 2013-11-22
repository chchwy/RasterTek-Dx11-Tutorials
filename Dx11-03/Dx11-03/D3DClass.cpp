
#include "D3DClass.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")


D3DClass::D3DClass() 
{
}


D3DClass::~D3DClass()
{
}

bool D3DClass::Initialize( int, int, bool, HWND, bool, float, float )
{
    return true;
}

void D3DClass::Shutdown()
{

}

void D3DClass::BeginScene( float, float, float, float )
{

}

void D3DClass::EndScene()
{

}
