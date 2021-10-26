#include "JInput.h"

DWORD JInput::GetKey(DWORD dwKey)
{
	return m_dwKeyState[dwKey];
}

void   JInput::OnMove(int iX, int iY)
{
    if (m_bDrag)
    {
        m_pDrag.x = iX - m_pDragDown.x;
        m_pDrag.y = iY - m_pDragDown.y;
    }
    m_pDragDown.x = iX;
    m_pDragDown.y = iY;
    //std::string buffer;
    //std::string b = std::to_string(iX);
    //buffer = b + " " + std::to_string(m_pDragDown.x);
    //OutputDebugStringA(buffer.c_str());
    return;
}
void   JInput::OnBegin(int iX, int iY)
{
    m_bDrag = true;
    m_pDragDown.x = iX;
    m_pDragDown.y = iY;
    return;
}
void   JInput::OnEnd()
{
    m_bMove = false;
    m_bDrag = false;
    m_pDrag.x = 0;
    m_pDrag.y = 0;
    return;
}
LRESULT JInput::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int iMouseX = (short)LOWORD(lParam);
    int iMouseY = (short)HIWORD(lParam);
    switch (message)
    {
    case  WM_MOUSEMOVE:
        OnMove(iMouseX, iMouseY);
        return TRUE;
    case WM_LBUTTONDOWN:
        SetCapture(g_hWnd);
        OnBegin(iMouseX, iMouseY);
        return TRUE;
    case WM_LBUTTONUP:
        ReleaseCapture();
        OnEnd();
        return TRUE;
        /*case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:*/
    case WM_MOUSEWHEEL:
    {
        m_iWheel = GET_WHEEL_DELTA_WPARAM(wParam);//120    
        return 0;
    }
    }
    return 0;
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

