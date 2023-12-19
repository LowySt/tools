#ifndef LS_INPUT_H
#define LS_INPUT_H

struct keyMap
{
    u8 F1  : 1, F2  : 1, F3  : 1, F4  : 1, F5  : 1, F6  : 1;
    u8 F7  : 1, F8  : 1, F9  : 1, F10 : 1, F11 : 1, F12 : 1;    // 12
    
    u8 A : 1, B : 1, C : 1, D : 1, E : 1, F : 1, G : 1;
    u8 H : 1, I : 1, J : 1, K : 1, L : 1, M : 1, N : 1;
    u8 O : 1, P : 1, Q : 1, R : 1, S : 1, T : 1, U : 1;
    u8 V : 1, W : 1, X : 1, Y : 1, Z : 1;                       // 12 + 26 = 38
    
    // Classic Number Keys
    u8 K0 : 1, K1 : 1, K2 : 1, K3 : 1, K4 : 1;
    u8 K5 : 1, K6 : 1, K7 : 1, K8 : 1, K9 : 1;                  // 38 + 10 = 48
    
    //Numpad Number Keys
    u8 N0 : 1, N1 : 1, N2 : 1, N3 : 1, N4 : 1;
    u8 N5 : 1, N6 : 1, N7 : 1, N8 : 1, N9 : 1;                  // 48 + 10 = 58
    
    u8 Enter : 1, Shift : 1, Control : 1, RAlt : 1;             // 58 +  4 = 62
    
    u8 LArrow : 1, RArrow : 1, UArrow : 1, DArrow : 1;          // 62 +  4 = 66
    
    u8 Backspace : 1, Delete : 1, Home : 1, End : 1;            // 66 +  4 = 70
    
    u8 Escape : 1;                                              // 70 +  1 = 71
    
};

typedef u32(*ClipboardFunc)(void *, u32);

struct KeyboardInput
{
    keyMap currentState = {};
    keyMap prevState    = {};
    
    keyMap repeatState  = {};
    
    b32 hasPrintableKey;
    u32 keyCodepoint;
    
    ClipboardFunc getClipboard;
    ClipboardFunc setClipboard;
};

struct MouseInput
{
    s32 currPosX, currPosY;
    s32 prevPosX, prevPosY;
    
    s32 wheelDelta;
    
    b32 isLeftPressed;
    b32 wasLeftPressed;
    b32 isMiddlePressed;
    b32 wasMiddlePressed;
    b32 isRightPressed;
    b32 wasRightPressed;
    
    b32 isWheelRotated;
};

struct Input
{
    MouseInput Mouse;
    KeyboardInput Keyboard;
};

//Input UserInput = {};

#endif //LS_INPUT_H
