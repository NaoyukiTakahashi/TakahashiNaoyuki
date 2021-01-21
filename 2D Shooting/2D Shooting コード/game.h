//=============================================================================
//
// �Q�[������ [game.h]
// Author : 
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
class CEnemy;
class CBoss;
class CScore;
class CLife;
class CBg;

class CGame :public CScene
{
public:

	typedef enum
	{
		MODE_NONE = 0,
		MODE_TUTORIAL,
		MODE_ENEMY,
		MODE_BOSS,
		MODE_MAXINUM
	}MODE_TYPE;

	CGame();
	~CGame();
	static CGame *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type, int nPattern) {};
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); };
	D3DXVECTOR2 GetSize(void) { return D3DXVECTOR2(0.0f, 0.0f); };
	void SetState(STATE state) {};
	STATE GetState(void) { return STATE_NONE; };
	static CLife *GetLife(void) { return m_pLife; };
	static CBoss *GetBossLife(void) { return m_pBossLife; };
	static CPlayer *GetPlayer(void) { return m_pPlayer; };
	static CEnemy *GetEnemy(void) { return *m_apEnemy; };
	static CBoss *GetBoss(void) { return *m_apBoss; };
	static void SetMode(MODE_TYPE mode);
	static MODE_TYPE GetMode(void) { return m_mode; };

private:
	static MODE_TYPE m_mode;
	static CPlayer *m_pPlayer;//�v���C���[���ێ�
	static CEnemy *m_apEnemy[MAX_ENEMY_POLYGON];//�G�l�~�[���ێ�
	static CBoss *m_apBoss[MAX_BOSS_POLYGON];//�{�X�G�l�~�[���ێ�
	static CScore *m_pScore;//�X�R�A���ێ�
	static CLife *m_pLife;//���C�t���ێ�
	static CBoss *m_pBossLife;//���C�t���ێ�
	static CBg *m_pBg;//�w�i���ێ�
};
#endif