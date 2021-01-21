#include "input.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//=============================================================================
// コンストラクタ関数
//=============================================================================
CInput::CInput()
{
	m_pDevice=NULL;
}

//=============================================================================
// デストラクタ関数
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CInput::Uninit(void)
{
	if (m_pDevice != NULL)
	{
		//デバイス制御の停止
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice=NULL;
	}
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//更新
void CInput::Update(void)
{

}

//キーボードコンストラクタ
CInputKeyboard::CInputKeyboard()
{
	ZeroMemory(m_aKeyState, sizeof(m_aKeyState));
	ZeroMemory(m_aKeyStateTrigger, sizeof(m_aKeyStateTrigger));
	ZeroMemory(m_aKeyStateRelease, sizeof(m_aKeyStateRelease));
}

//キーボードデストラクタ
CInputKeyboard::~CInputKeyboard()
{
}

//初期化
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	m_pDevice->Acquire();

	return S_OK;
}

//終了
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//更新
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	int nCntkey;

	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{

			m_aKeyStateTrigger[nCntkey] = (m_aKeyState[nCntkey] ^ aKeyState[nCntkey]) & aKeyState[nCntkey];

			m_aKeyStateRelease[nCntkey] = (m_aKeyState[nCntkey] ^ aKeyState[nCntkey]) & ~aKeyState[nCntkey];

			m_aKeyState[nCntkey] = aKeyState[nCntkey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//取得
bool CInputKeyboard::GetKeyPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//取得
bool CInputKeyboard::GetKeyTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//取得
bool CInputKeyboard::GetKeyRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
