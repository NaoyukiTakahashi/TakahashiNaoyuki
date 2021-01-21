//=============================================================================
//
// �|�[�Y���� [pause.h]
// Author : 
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_


//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include"main.h"
#include"manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PAUSE_TEX 3
#define MAX_PAUSE_POLYGON 3
#define PAUSE_1 "TEX/pause000.png"
#define PAUSE_2 "TEX/pause001.png"
#define PAUSE_3 "TEX/pause002.png"
#define PAUSE_1_SIZE_WIDTH 1920.0f
#define PAUSE_1_SIZE_HIGHT 1080.0f
#define PAUSE_2_SIZE_WIDTH 1920.0f
#define PAUSE_2_SIZE_HIGHT 1080.0f
#define PAUSE_3_SIZE_WIDTH 1920.0f
#define PAUSE_3_SIZE_HIGHT 1080.0f

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// �N���X
//*****************************************************************************
class CPause
{
public:
	// �t�F�[�h�̏��
	typedef enum
	{
		PAUSE_OFF = 0,	// �|�[�Yoff
		PAUSE_ON,		// �|�[�Yon
	} PAUSE;
	CPause();
	~CPause();
	static CPause *Create(void);
	void SetPause(void) { m_pause = PAUSE_ON; };
	PAUSE GetPause(void) { return m_pause; };
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Init(void);

	// �����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_PAUSE_TEX]; //�e�N�X�`��
	PAUSE m_pause;				// �|�[�Y���
	D3DXCOLOR m_colorPause;		// �|�[�Y�F
	CPolygon *m_apPolygon[MAX_PAUSE_POLYGON];
};

#endif