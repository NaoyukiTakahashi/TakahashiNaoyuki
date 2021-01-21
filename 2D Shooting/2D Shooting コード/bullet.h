//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_BULLET_TEX 2
#define BULLET_SIZE_WIDTH 10.0f
#define BULLET_SIZE_HIGHT 10.0f
#define MAX_BULLET_LIFE 100
#define PLAYER_HIT_TEST 5

//*****************************************************************************
// �N���X
//*****************************************************************************
class CBullet : public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_NORMAL,
		TYPE_TARGET,
		TYPE_HOMING,
		TYPE_WAVE,
		STATE_MAX
	}BULLET_TYPE;

	CBullet(int nPriority = 5);
	~CBullet();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type, D3DXCOLOR col, D3DXVECTOR3 size, int nLife, BULLET_TYPE bullettype);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type, D3DXCOLOR col, D3DXVECTOR3 size, int nLife, BULLET_TYPE bullettype);
	static HRESULT Load(void);
	static void Unload(void);
	void SetLife(int nLife) { m_nLife = nLife; };
	void SetState(STATE state) { m_state = state; };
	STATE GetState(void) { return m_state; };
private:
	D3DXVECTOR3 SetBulletMove(BULLET_TYPE bullettype, D3DXVECTOR3 move);
	D3DXVECTOR3 m_move; //�ړ���
	D3DXVECTOR3 m_pos;  //���W
	D3DXCOLOR m_col; //�F
	TYPE m_type;//���
	STATE m_state;
	D3DXVECTOR3 m_size;
	int m_nLife;//HP
	BULLET_TYPE m_bullettype;//���
	static LPDIRECT3DTEXTURE9 m_apBulletTexture[MAX_BULLET_TEX];//�e�N�X�`��
};

#endif