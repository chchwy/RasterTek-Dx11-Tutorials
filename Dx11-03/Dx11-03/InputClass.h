
#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

enum
{
    KEY_CODE_MAX = 256
};

class InputClass
{
public:
    InputClass();
    ~InputClass();
    bool Initialize();
    bool IsKeyDown( unsigned int nKeyCode );
    void KeyDown( unsigned int nKeyCode );
    void KeyUp( unsigned int nKeyCode );

private:
    bool m_keys[ KEY_CODE_MAX ];
};

#endif


