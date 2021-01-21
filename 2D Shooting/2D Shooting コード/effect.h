//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author : 
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_EFFECT_TEX 1
#define MAX_EFFECT (128*10)	// �G�t�F�N�g�̍ő吔
#define MAX_EFFECT_LIFE 100
#define PLAYER_HIT_TEST 5

//*****************************************************************************
// �N���X
//*****************************************************************************
class CEffect : public CScene2d
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,
		TYPE_HOMING,
		TYPE_MAX
	}EFFECT_TYPE;
	CEffect(int nPriority = 6);
	~CEffect();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fColAlphaValue, float fRadius, int fRadiusValue, int nLife, EFFECT_TYPE effecttype);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col, float fColAlphaValue, float fRadius,int fRadiusValue, int nLife, EFFECT_TYPE effecttype);
	static HRESULT Load(void);
	static void Unload(void);
	D3DXVECTOR3 SetEffectMove(EFFECT_TYPE effecttype, D3DXVECTOR3 move);
	static int GetIndex(void) { return m_nIndex; };
	void SetState(STATE state) { ; };
	STATE GetState(void) { return STATE_NONE; };
private:
	D3DXVECTOR3 m_move; //�ړ���
	D3DXVECTOR3 m_pos;  //���W
	D3DXCOLOR m_col; //�F
	float m_fRadius;			// ���a
	float m_fRadiusValue;		// ���a�ω���
	float m_fColAlphaValue;	// �F�ω���
	int m_nLife;//HP
	static int m_nIndex;
	EFFECT_TYPE m_effecttype;//���
	static LPDIRECT3DTEXTURE9 m_apEffectTexture[MAX_EFFECT_TEX];//�e�N�X�`��
};

#endif