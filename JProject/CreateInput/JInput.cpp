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
    // ȭ�� ��ǥ
    GetCursorPos(&m_ptPos);

    // Ŭ���̾�Ʈ ��ǥ
    ScreenToClient(g_hWnd,&m_ptPos);

    for (int iKey = 0; iKey < 256; iKey++)
    {
        SHORT sKey = GetAsyncKeyState(iKey);
        if (sKey & 0x8000)
            //������ ��� �ֻ��� ��Ʈ�� 1
        {
            if (m_dwKeyState[iKey] == KEY_FREE)
                //�̺�Ʈ �߻� �� ���� 0�ϰ�� 2�κ���
            {
                m_dwKeyState[iKey] = KEY_PUSH;
            }
            else
                //�̺�Ʈ �߻� �� ���� 0�� �ƴҰ�� 3���κ���
            {
                m_dwKeyState[iKey] = KEY_HOLD;
            }
        }
        else
            //�ش� Ű�� ������ ���� ���� ��� Ű�� ���¸� Ȯ���� ����
        {
            if (m_dwKeyState[iKey] == KEY_PUSH ||
                m_dwKeyState[iKey] == KEY_HOLD)
                //�̺�Ʈ �߻� �� 2 �Ǵ� 3�� ��� 1������ ����
            {
                m_dwKeyState[iKey] = KEY_UP;
            }
            else
                //�ش� Ű�� 2 �Ǵ� 3 ���°� �ƴ� ��� 0���� �ʱ�ȭ
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
