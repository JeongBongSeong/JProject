#include "JInput.h"

DWORD JInput::GetKey(DWORD dwKey)
{
    return m_dwKeyState[dwKey];
}

bool JInput::Init()
{
    ZeroMemory(&m_dwKeyState, sizeof(DWORD) * 256);
    return true;
}

bool JInput::Frame()
{
    // 화면 좌표
    GetCursorPos(&m_ptPos);

    // 클라이언트 좌표
    ScreenToClient(g_hWnd,&m_ptPos);

    for (int iKey = 0; iKey < 256; iKey++)
    {
        SHORT sKey = GetAsyncKeyState(iKey);
        if (sKey & 0x8000)
            //눌렸을 경우 최상위 비트는 1
        {
            if (m_dwKeyState[iKey] == KEY_FREE)
                //이벤트 발생 시 값이 0일경우 2로변경
            {
                m_dwKeyState[iKey] = KEY_PUSH;
            }
            else
                //이벤트 발생 시 값이 0이 아닐경우 3으로변경
            {
                m_dwKeyState[iKey] = KEY_HOLD;
            }
        }
        else
            //해당 키가 눌러져 있지 않을 경우 키의 상태를 확인후 변경
        {
            if (m_dwKeyState[iKey] == KEY_PUSH ||
                m_dwKeyState[iKey] == KEY_HOLD)
                //이벤트 발생 시 2 또는 3일 경우 1값으로 변경
            {
                m_dwKeyState[iKey] = KEY_UP;
            }
            else
                //해당 키가 2 또는 3 상태가 아닐 경우 0으로 초기화
            {
                m_dwKeyState[iKey] = KEY_FREE;
            }
        }
    }

    return true;
}

bool JInput::Render()
{
    return true;
}

bool JInput::Release()
{
    return true;
}

JInput::JInput()
{
}
JInput::~JInput()
{
}
