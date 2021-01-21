//=============================================================================
//
// �V�[������ [scene.h]
// Author : 
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

#define MAX_PRIORITY 10
#define MAX_ENEMY_POLYGON 3
#define MAX_BOSS_POLYGON 9

//*****************************************************************************
// �N���X
//*****************************************************************************
class CScene
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_BULLET_P,
		TYPE_BULLET_E,
		TYPE_BARRIER,
		TYPE_ENEMY,
		TYPE_EXPLOSION,
		TYPE_BG,
		TYPE_UI,
		TYPE_LIFE,
		TYPE_EFFECT,
		TYPE_SCENE2D,
		TYPE_PARTICLE,
		TYPE_BOSS,
		TYPE_BOSSBODY,
		TYPE_MAXINUM
	}TYPE;

	typedef enum
	{
		STATE_NONE = 0,
		STATE_NORMAL,
		STATE_HIT,
		STATE_INVINCIBLE,
		STATE_DETH,
		STATE_MAX
	}STATE;

	CScene(int nPriority = 3);
	virtual~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type, int nPattern) = 0;
	virtual D3DXVECTOR3 GetPosition(void) = 0;
	virtual D3DXVECTOR2 GetSize(void) = 0;
	virtual void SetState(STATE state) = 0;
	virtual STATE GetState(void) = 0;
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	void SetType(TYPE type) { m_nType = type; };
	void Death(void);
protected:
	void Release(void);
private:
	static CScene *m_pTop;//�擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CScene *m_pCur;//���݂̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pPrev; //�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pNext; //���̃I�u�W�F�N�g�ւ̃|�C���^
	TYPE m_nType;//�^�C�v
	bool m_bDeath;
};

#endif