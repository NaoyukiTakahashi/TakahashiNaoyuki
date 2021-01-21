//=============================================================================
//
// �o���A���� [barrier.h]
// Author : 
//
//=============================================================================
#ifndef _BARRIER_H_
#define _BARRIER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BARRIER_SIZE_WIDTH 10.0f
#define BARRIER_SIZE_HIGHT 10.0f
#define MAX_BULLET_LIFE 50
#define HITTEST 75

//*****************************************************************************
// �N���X
//*****************************************************************************
class CBarrier : public CScene2d
{
public:
	CBarrier(int nPriority = 3);
	~CBarrier();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type, D3DXCOLOR col, int nSize);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBarrier *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type, D3DXCOLOR col, int nSize);
	static HRESULT Load(void);
	static void Unload(void);
	void SetState(STATE state) { m_state = state; };
	STATE GetState(void) { return m_state; };
private:
	D3DXVECTOR3 m_move; //�ړ���
	D3DXVECTOR3 m_pos;  //���W
	D3DXCOLOR m_col; //�F
	TYPE m_type;//���
	STATE m_state;
	int m_nSize;
	static LPDIRECT3DTEXTURE9 m_pBarrierTexture;//�e�N�X�`��
};

#endif