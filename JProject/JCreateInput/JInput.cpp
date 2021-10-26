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
	//Ŀ���� ��ġ�� �������ִ� ������ ���� 
	GetCursorPos(&m_ptPos);


	//Ŭ���̾�Ʈ ��ǥ
	ScreenToClient(g_hWnd, &m_ptPos);
	
	for (int iKey = 0; iKey < 256; iKey++)
	{
		SHORT sKey = GetAsyncKeyState(iKey);
		if (sKey & 0x8000)
		{
			if (m_dwKeyState[iKey] == KEY_FREE)
			{
				m_dwKeyState[iKey] = KEY_PUSH;
			}
			else
			{
				m_dwKeyState[iKey] = KEY_HOLD;
			}
		}
		else
		{
			//�����ٰ� ���� ��� ���� ���� ���� Ȯ���� Ǫ�ó� Ȧ���� ��� ���ű� ������ ������ �ʱ�ȭ
			if (m_dwKeyState[iKey] == KEY_PUSH
				|| m_dwKeyState[iKey] == KEY_HOLD)
			{
				m_dwKeyState[iKey] = KEY_UP;
			}
			// �� ��Ȳ�� �ƴ϶�� UP���¶�� �� �Ǵ� ���� FREE��� �� �̱� ������ �ʱ�ȭ
			else
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