//=============================================================================
//
// �G�t�F�N�g���� [particle.h]
// Author : 
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PARTICLE_TEX 1
#define MAX_PARTICLE (128*10)	// �G�t�F�N�g�̍ő吔
#define MAX_PARTICLE_LIFE 100
#define PLAYER_HIT_TEST 5

//*****************************************************************************
// �N���X
//*****************************************************************************
class CParticle : public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_NORMAL,
		TYPE_MAX
	}PARTICLE_TYPE;
	CParticle(int nPriority = 3);
	~CParticle();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fColAlphaValue, float fRadius, int fRadiusValue, int nLife, PARTICLE_TYPE particletype);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CParticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fColAlphaValue, float fRadius, int fRadiusValue, int nLife, PARTICLE_TYPE particletype);
	static HRESULT Load(void);
	static void Unload(void);
	D3DXVECTOR3 SetParticleMove(PARTICLE_TYPE particletype, D3DXVECTOR3 move);
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
	PARTICLE_TYPE m_particletype;//���
	static LPDIRECT3DTEXTURE9 m_apParticleTexture[MAX_PARTICLE_TEX];//�e�N�X�`��
};

#endif