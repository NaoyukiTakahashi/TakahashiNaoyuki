//=============================================================================
//
// �}�l�[�W���[���� [maneger.h]
// Author : 
//
//=============================================================================
#ifndef _MANEGER_H_
#define _MANEGER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define MAX_ENEMY_POLYGON 3

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;
class CScene;
class CInputKeyboard;
class CSound;
class CTitle;
class CGame;
class CResult;
class CFade;
class CPause;

//*****************************************************************************
// �N���X
//*****************************************************************************
class CManeger
{
public:
	typedef enum
	{
		MODE_NONE = 0,
		MODE_TITLE,
		MODE_GAME,
		MODE_RESULT,
		MODE_END,
	}MODE;
	CManeger();
	~CManeger();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWhindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRenderer *GetRenderer(void) { return m_pRenderer; };
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; };
	static CSound *GetSound(void) { return m_pSound; };
	static CFade *GetFade(void) { return m_pFade; };
	static CPause *GetPause(void) { return m_pPause; };
	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; };
private:
	static CTitle *m_pTitle;
	static CGame *m_pGame;
	static CResult *m_pResult;
	static MODE m_mode;
	static CFade *m_pFade;
	static CPause *m_pPause;
	static CRenderer *m_pRenderer;//�����_���[���ێ�
	static CInputKeyboard *m_pInputKeyboard;//�L�[�{�[�h���ێ�
	static CSound *m_pSound;//�T�E���h���ێ�
};
#endif