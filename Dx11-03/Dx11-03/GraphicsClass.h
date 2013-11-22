
#ifndef GRAPHICS_CLASS_H
#define GRAPHICS_CLASS_H

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
    void Render();
};

#endif 

