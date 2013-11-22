
#include <string>
#include "InputClass.h"



InputClass::InputClass()
{
    memset( m_keys, 0, sizeof( m_keys ) );
}

InputClass::~InputClass()
{

}

bool InputClass::Initialize()
{
    return true;
}

bool InputClass::IsKeyDown( unsigned int nKeyCode )
{
    if ( nKeyCode < KEY_CODE_MAX )
    {
        return m_keys[ nKeyCode ];
    }
    return false;
}

void InputClass::KeyDown( unsigned int nKeyCode )
{
    if ( nKeyCode < KEY_CODE_MAX )
    {
        m_keys[ nKeyCode ] = true;
    }
}

void InputClass::KeyUp( unsigned int nKeyCode )
{
    if ( nKeyCode < KEY_CODE_MAX )
    {
        m_keys[ nKeyCode ] = false;
    }
}

