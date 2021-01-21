#include "input.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//=============================================================================
// �R���X�g���N�^�֐�
//=============================================================================
CInput::CInput()
{
	m_pDevice=NULL;
}

//=============================================================================
// �f�X�g���N�^�֐�
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// �������֐�
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
// �I���֐�
//=============================================================================
void CInput::Uninit(void)
{
	if (m_pDevice != NULL)
	{
		//�f�o�C�X����̒�~
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

//�X�V
void CInput::Update(void)
{

}

//�L�[�{�[�h�R���X�g���N�^
CInputKeyboard::CInputKeyboard()
{
	ZeroMemory(m_aKeyState, sizeof(m_aKeyState));
	ZeroMemory(m_aKeyStateTrigger, sizeof(m_aKeyStateTrigger));
	ZeroMemory(m_aKeyStateRelease, sizeof(m_aKeyStateRelease));
}

//�L�[�{�[�h�f�X�g���N�^
CInputKeyboard::~CInputKeyboard()
{
}

//������
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	m_pDevice->Acquire();

	return S_OK;
}

//�I��
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//�X�V
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

//�擾
bool CInputKeyboard::GetKeyPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//�擾
bool CInputKeyboard::GetKeyTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//�擾
bool CInputKeyboard::GetKeyRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
