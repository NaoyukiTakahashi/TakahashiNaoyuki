//=============================================================================
//
// �v���[���[���� [player.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2d.h"
#include <mutex>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_SIZE_WIDTH 100.0f
#define PLAYER_SIZE_HIGHT 100.0f
#define PLAYER_MOVE (10.0f)
#define PLAYER_LIFE (10)
#define RATE_MOVE (0.5f)
#define MAX_STORING_FRAME (120)
#define MAX_CONCURRENT_ENTRY_KEY 109

//*****************************************************************************
// �N���X
//*****************************************************************************
class CPlayer : public CScene2d
{
public:
	typedef enum
	{
		PLAY = 0,
		REPLAY
	}PLAY_MODE;

	CPlayer(int nPriority = 4);
	~CPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void UpdateRePlay(void);
	void Draw(void);
	static CPlayer *Create(void);
	static HRESULT Load(void);
	static void Unload(void);
	void SetState(STATE state) { m_state = state; };
	STATE GetState(void) { return m_state; };
private:
	STATE m_state;
	static LPDIRECT3DTEXTURE9 m_pPlayerTexture; //�e�N�X�`��
	static void PlayerActivitySave(int nNumSave[MAX_STORING_FRAME][MAX_CONCURRENT_ENTRY_KEY]);
	static void FileLoad(int pnNumLoad[MAX_STORING_FRAME][MAX_CONCURRENT_ENTRY_KEY]);
};

#endif