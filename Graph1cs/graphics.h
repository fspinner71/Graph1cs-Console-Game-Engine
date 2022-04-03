#include <iostream>
#include <Windows.h>
#include <cwchar>
#include <string>
#include <stdlib.h>

HANDLE buffer;

COORD globalsize;

CHAR_INFO *clearchars = new CHAR_INFO[globalsize.X * globalsize.Y];

struct keypress
{
    bool A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO, LCTRL, ESC, TAB, RCTRL, SHIFT, ENTER, BACK, SPACE, LEFT, RIGHT, UP, DOWN, ML, MR;
};
struct rect
{
    COORD position, size;
    WORD property = 0;
    CHAR_INFO *info = new CHAR_INFO[globalsize.X * globalsize.Y];

    void construct()
    {
        for (int i = 0; i < globalsize.X * globalsize.Y; ++i)
        {
            info[i].Attributes = property;
            info[i].Char.AsciiChar = '1';
        }
    }
};

void clear()
{
    COORD totalsize;
    totalsize.X = globalsize.X;
    totalsize.Y = globalsize.Y;
    SMALL_RECT used;
    used.Bottom = globalsize.Y;
    used.Top = 0;
    used.Left = 0;
    used.Right = globalsize.X;
    WriteConsoleOutput(buffer, clearchars, totalsize, {0, 0}, &used);
}

void init(COORD size, COORD font, std::string name)
{
    TCHAR *temp = new TCHAR[name.size()];
    temp[name.size()] = 0;
    std::copy(name.begin(), name.end(), temp);
    SetConsoleTitle(temp);
    buffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(buffer);
    SMALL_RECT winrect = {0,0};
    winrect.Right = size.X * font.X;
    winrect.Bottom = size.Y * font.Y;
    MoveWindow(GetConsoleWindow(),winrect.Left, winrect.Top, winrect.Right,winrect.Bottom,true);
    CONSOLE_SCREEN_BUFFER_INFO binfo;
    GetConsoleScreenBufferInfo(buffer, &binfo);
    globalsize.X = binfo.dwSize.X;
    globalsize.Y = binfo.dwSize.Y;
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    cfi.dwFontSize.X = font.X;
    cfi.dwFontSize.Y = font.Y;
    cfi.nFont = 0;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Comic Sans");
    SetCurrentConsoleFontEx(buffer,true, &cfi);
    for (int i = 0; i < (globalsize.X * globalsize.Y); ++i)
    {
        clearchars[i].Attributes = 0;
        clearchars[i].Char.AsciiChar = ' ';
    }
    delete[] temp;
}

void draw(rect obj)
{
    COORD totalsize;
    totalsize.X = obj.size.X + obj.position.X;
    totalsize.Y = obj.size.Y + obj.position.Y;
    SMALL_RECT used;
    used.Bottom = totalsize.Y;
    used.Top = obj.position.Y;
    used.Left = obj.position.X;
    used.Right = totalsize.X;
    WriteConsoleOutput(buffer, obj.info, totalsize, obj.position, &used);
}
void pollkeypresses(keypress &keys)
{
    keys.A = !(GetKeyState(0x41) >= 0);
    keys.B = !(GetKeyState(0x42) >= 0);
    keys.C = !(GetKeyState(0x43) >= 0);
    keys.D = !(GetKeyState(0x44) >= 0);
    keys.E = !(GetKeyState(0x45) >= 0);
    keys.F = !(GetKeyState(0x46) >= 0);
    keys.G = !(GetKeyState(0x47) >= 0);
    keys.H = !(GetKeyState(0x48) >= 0);
    keys.I = !(GetKeyState(0x49) >= 0);
    keys.J = !(GetKeyState(0x4A) >= 0);
    keys.K = !(GetKeyState(0x4B) >= 0);
    keys.L = !(GetKeyState(0x4C) >= 0);
    keys.M = !(GetKeyState(0x4D) >= 0);
    keys.N = !(GetKeyState(0x4E) >= 0);
    keys.O = !(GetKeyState(0x4F) >= 0);
    keys.P = !(GetKeyState(0x50) >= 0);
    keys.Q = !(GetKeyState(0x51) >= 0);
    keys.R = !(GetKeyState(0x52) >= 0);
    keys.S = !(GetKeyState(0x53) >= 0);
    keys.T = !(GetKeyState(0x54) >= 0);
    keys.U = !(GetKeyState(0x55) >= 0);
    keys.V = !(GetKeyState(0x56) >= 0);
    keys.W = !(GetKeyState(0x57) >= 0);
    keys.X = !(GetKeyState(0x58) >= 0);
    keys.Y = !(GetKeyState(0x59) >= 0);
    keys.Z = !(GetKeyState(0x5A) >= 0);
    keys.ONE = !(GetKeyState(0x31) >= 0);
    keys.TWO = !(GetKeyState(0x32) >= 0);
    keys.THREE = !(GetKeyState(0x33) >= 0);
    keys.FOUR = !(GetKeyState(0x34) >= 0);
    keys.FIVE = !(GetKeyState(0x35) >= 0);
    keys.SIX = !(GetKeyState(0x36) >= 0);
    keys.SEVEN = !(GetKeyState(0x37) >= 0);
    keys.EIGHT = !(GetKeyState(0x38) >= 0);
    keys.NINE = !(GetKeyState(0x39) >= 0);
    keys.ZERO = !(GetKeyState(0x30) >= 0);
    keys.SHIFT = !(GetKeyState(VK_SHIFT) >= 0);
    keys.LCTRL = !(GetKeyState(VK_LCONTROL) >= 0);
    keys.RCTRL = !(GetKeyState(VK_RCONTROL) >= 0);
    keys.TAB = !(GetKeyState(VK_TAB) >= 0);
    keys.ENTER = !(GetKeyState(VK_RETURN) >= 0);
    keys.ESC = !(GetKeyState(VK_ESCAPE) >= 0);
    keys.BACK = !(GetKeyState(VK_BACK) >= 0);
    keys.SPACE = !(GetKeyState(VK_SPACE) >= 0);
    keys.LEFT = !(GetKeyState(VK_LEFT) >= 0);
    keys.RIGHT = !(GetKeyState(VK_RIGHT) >= 0);
    keys.UP = !(GetKeyState(VK_UP) >= 0);
    keys.DOWN = !(GetKeyState(VK_DOWN) >= 0);
    keys.ML = !(GetKeyState(VK_LBUTTON) >= 0);
    keys.MR = !(GetKeyState(VK_RBUTTON) >= 0);
}
