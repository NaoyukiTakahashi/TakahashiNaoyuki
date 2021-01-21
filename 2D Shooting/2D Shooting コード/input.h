//=============================================================================
//
// �C���v�b�g���� [input.h]
// Author : 
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX	(256)

//*****************************************************************************
// �N���X
//*****************************************************************************
class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;
protected:
	static LPDIRECTINPUT8 m_pInput; //���͏��
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetKeyPress(int nKey);
	bool GetKeyTrigger(int nKey);
	bool GetKeyRelease(int nKey);
private:
	BYTE m_aKeyState[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[���
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X���
};
#endif