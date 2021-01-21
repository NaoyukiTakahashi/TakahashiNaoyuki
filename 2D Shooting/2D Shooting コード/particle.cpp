//=============================================================================
//
// �G�t�F�N�g���� [particle.cpp]
// Author : 
//
//=============================================================================

//*****************************************************************************
// �t�@�C���C���N���[�h
//*****************************************************************************
#include "particle.h"
#include "manager.h"
#include "input.h"
#include "scene2d.h"
#include "renderer.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "game.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CParticle::m_apParticleTexture[];
int  CParticle::m_nIndex = 0;

//=============================================================================
// �R���X�g���N�^�֐�
//=============================================================================
CParticle::CParticle(int nPriority)
{
}

//=============================================================================
// �f�X�g���N�^�֐�
//=============================================================================
CParticle::~CParticle()
{
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fColAlphaValue, float fRadius, int fRadiusValue, int nLife, PARTICLE_TYPE particletype)
{
	BindTexture(m_apParticleTexture[particletype]);
	m_pos = pos;  //���W
	m_move = move; //�ړ���
	m_col = col; //�F
	m_fColAlphaValue = fColAlphaValue;	// �F�ω���
	m_fRadius = fRadius;			// ���a
	m_fRadiusValue = fRadiusValue;		// ���a�ω���
	m_nLife = nLife;//HP
	m_particletype = particletype;//���
	m_nIndex++;
	CScene2d::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CParticle::Uninit(void)
{
	m_nIndex--;
	CScene2d::Uninit();
}

//�X�V
void CParticle::Update(void)
{
	m_col.a -= m_fColAlphaValue;
	m_fRadius += m_fRadiusValue;

	static float fAngle = 0.0f;
	fAngle++;

	m_move.x = ((cosf((2 * D3DX_PI * fAngle* - 90) * D3DX_PI / 180)) * (m_fRadius * 1));
	m_move.y = ((sinf((2 * D3DX_PI * fAngle* - 90) * D3DX_PI / 180))* (m_fRadius * 1));

	//�ʒu�X�V
	SetPolygon(m_pos + m_move, D3DXVECTOR3(m_fRadius, m_fRadius, 0), m_col, TYPE_PARTICLE, NULL);

	CScene2d::Update();

	m_nLife--;

	if (m_nLife <= 0)
	{
		//	�e�̔j��
		Uninit();
	}
}

//�`��
void CParticle::Draw(void)
{
	CScene2d::Draw();
}

//����
CParticle * CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fColAlphaValue, float fRadius, int fRadiusValue, int nLife, PARTICLE_TYPE particletype)
{
	CParticle *pParticle;
	pParticle = new CParticle;
	pParticle->Init(pos, move, col, fColAlphaValue, fRadius, fRadiusValue, nLife, particletype);
	pParticle->SetType(TYPE_PARTICLE);
	return pParticle;
}

//�摜���[�h
HRESULT CParticle::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "TEX/bullet000.png", &m_apParticleTexture[0]);
	//D3DXCreateTextureFromFile(pDevice, "TEX/particle001.png", &m_apParticleTexture[1]);

	return S_OK;
}

//�摜�j��
void CParticle::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCount = 0; nCount < MAX_PARTICLE_TEX; nCount++)
	{
		if (m_apParticleTexture[nCount] != NULL)
		{
			m_apParticleTexture[nCount]->Release();
			m_apParticleTexture[nCount] = NULL;
		}
	}
}

D3DXVECTOR3 CParticle::SetParticleMove(PARTICLE_TYPE particletype, D3DXVECTOR3 move)
{
	float fDistance = 0.0f;
	static float fComparison = 0.0f;
	float fDistance_x = 0.0f;
	float fDistance_y = 0.0f;
	float fAngle = 0.0f;
	int nCount = 0;
	D3DXVECTOR3 nMove;
	D3DXVECTOR3 particlemove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	static D3DXVECTOR3 NearposEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (particletype)
	{
	case TYPE_NORMAL:
		m_pos.x = ((cosf(2 * D3DX_PI * fAngle*0.001 * nCount)) * (1 * 1));
		m_pos.y = ((sinf(2 * D3DX_PI * fAngle*0.001 * nCount)) * (1 * 1));
		break;
	default:
		break;
	}
	return particlemove;
}

//static float fAngle = 0.0f;
//static float fRadius = 1.0f;
//
//fAngle++;
//
//for (int nCount = 0; nCount < MAX_PARTICLE_POLYGON; nCount++)
//{
//	m_pos.x = ((cosf(2 * D3DX_PI * fAngle*0.001 * nCount)) * (fRadius * 1));
//	m_pos.y = ((sinf(2 * D3DX_PI * fAngle*0.001 * nCount)) * (fRadius * 1));
//
//	m_apScene2D[nCount]->SetPolygon(m_pos, D3DXVECTOR3(10, 10, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), TYPE_PARTICLE, 0);
//}