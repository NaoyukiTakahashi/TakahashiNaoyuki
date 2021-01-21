//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author : 
//
//=============================================================================

//*****************************************************************************
// �t�@�C���C���N���[�h
//*****************************************************************************
#include "effect.h"
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
LPDIRECT3DTEXTURE9 CEffect::m_apEffectTexture[];
int  CEffect::m_nIndex = 0;

//=============================================================================
// �R���X�g���N�^�֐�
//=============================================================================
CEffect::CEffect(int nPriority) :CScene2d(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^�֐�
//=============================================================================
CEffect::~CEffect()
{
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fColAlphaValue, float fRadius, int fRadiusValue, int nLife, EFFECT_TYPE effecttype)
{
	BindTexture(m_apEffectTexture[effecttype]);
	m_pos = pos;  //���W
	m_move = move; //�ړ���
	m_col = col; //�F
	m_fColAlphaValue = fColAlphaValue;	// �F�ω���
	m_fRadius = fRadius;			// ���a
	m_fRadiusValue = fRadiusValue;		// ���a�ω���
	m_nLife = nLife;//HP
	m_effecttype = effecttype;//���
	m_nIndex++;
	CScene2d::Init();
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CEffect::Uninit(void)
{
	m_nIndex--;
	CScene2d::Uninit();
}

//�X�V
void CEffect::Update(void)
{
	m_col.a -= m_fColAlphaValue;
	m_fRadius -= m_fRadiusValue;

	//�ʒu�X�V
	SetPolygon(m_pos, D3DXVECTOR3(m_fRadius, m_fRadius, 0), m_col, TYPE_NONE,NULL);

	CScene2d::Update();

	m_nLife--;

	if (m_nLife <= 0)
	{
		//	�e�̔j��
		Uninit();
	}
}

//�`��
void CEffect::Draw(void)
{
	CScene2d::Draw();
}

//����
CEffect * CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fColAlphaValue, float fRadius, int fRadiusValue, int nLife, EFFECT_TYPE effecttype)
{
	CEffect *pEffect;
	pEffect = new CEffect;
	pEffect->Init(pos, move, col, fColAlphaValue, fRadius, fRadiusValue, nLife, effecttype);
	pEffect->SetType(TYPE_EFFECT);
	return pEffect;
}

//�摜���[�h
HRESULT CEffect::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "TEX/bullet000.png", &m_apEffectTexture[0]);
	//D3DXCreateTextureFromFile(pDevice, "TEX/effect001.png", &m_apEffectTexture[1]);

	return S_OK;
}

//�摜�j��
void CEffect::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCount = 0; nCount < MAX_EFFECT_TEX; nCount++)
	{
		if (m_apEffectTexture[nCount] != NULL)
		{
			m_apEffectTexture[nCount]->Release();
			m_apEffectTexture[nCount] = NULL;
		}
	}
}

D3DXVECTOR3 CEffect::SetEffectMove(EFFECT_TYPE effecttype, D3DXVECTOR3 move)
{
	float fDistance = 0.0f;
	static float fComparison = 0.0f;
	float fDistance_x = 0.0f;
	float fDistance_y = 0.0f;
	float fAngle = 0.0f;
	int nCount = 0;
	D3DXVECTOR3 nMove;
	D3DXVECTOR3 effectmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	static D3DXVECTOR3 NearposEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (effecttype)
	{
	case TYPE_NORMAL:
		effectmove = move;
		break;
	case TYPE_HOMING:
		for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				/*CScene *pScene = GetScene(nCntPriority, nCntScene);
				if (pScene != NULL)
				{
					TYPE type = pScene->GetObjType();
					STATE state = pScene->GetScene(nCntPriority, nCntScene)->GetState();

					if (type == TYPE_ENEMY)
					{
						posEnemy = pScene->GetPosition();
						fDistance_x = posEnemy.x - m_pos.x;
						fDistance_y = posEnemy.y - m_pos.y;
						fDistance = sqrtf(fDistance_x * fDistance_x + fDistance_y * fDistance_y);
						int hoge = 0;
						if (nCount == 0)
						{
							fComparison = fDistance;
							NearposEnemy = posEnemy;
						}
						else if (nCount >= 1 && fDistance < fComparison)
						{
							fComparison = fDistance;
							NearposEnemy = posEnemy;
						}
						else
						{
						}
						nCount++;
					}
				}*/
			}
		}
		fDistance_x = NearposEnemy.x - m_pos.x;
		fDistance_y = NearposEnemy.y - m_pos.y;
		fAngle = atan2f(fDistance_y, fDistance_x);
		effectmove = D3DXVECTOR3(cosf(fAngle) * -move.x, sinf(fAngle) * -move.y, 0.0f);
		break;
	default:
		break;
	}
	return effectmove;
}
