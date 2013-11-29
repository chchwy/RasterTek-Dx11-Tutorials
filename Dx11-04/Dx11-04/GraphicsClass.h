
#ifndef GRAPHICS_CLASS_H
#define GRAPHICS_CLASS_H

#include "CameraClass.h"
#include "ModelClass.h"
#include "ColorShaderClass.h"
#include "D3DClass.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


class GraphicsClass
{
public:
    GraphicsClass();
    ~GraphicsClass();

    bool Initialize( int, int, HWND );
    bool Shutdown();

    bool Frame();

private:
    bool Render();

    D3DClass* m_pD3D;
    CameraClass* m_pCamera;
    ModelClass* m_pModel;
    ColorShaderClass* m_pColorShader;
};

#endif 

