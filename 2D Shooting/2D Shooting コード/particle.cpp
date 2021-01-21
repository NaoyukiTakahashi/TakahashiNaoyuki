//=============================================================================
//
// エフェクト処理 [particle.cpp]
// Author : 
//
//=============================================================================

//*****************************************************************************
// ファイルインクルード
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
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CParticle::m_apParticleTexture[];
int  CParticle::m_nIndex = 0;

//=============================================================================
// コンストラクタ関数
//=============================================================================
CParticle::CParticle(int nPriority)
{
}

//=============================================================================
// デストラクタ関数
//=============================================================================
CParticle::~CParticle()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fColAlphaValue, float fRadius, int fRadiusValue, int nLife, PARTICLE_TYPE particletype)
{
	BindTexture(m_apParticleTexture[particletype]);
	m_pos = pos;  //座標
	m_move = move; //移動量
	m_col = col; //色
	m_fColAlphaValue = fColAlphaValue;	// 色変化量
	m_fRadius = fRadius;			// 半径
	m_fRadiusValue = fRadiusValue;		// 半径変化量
	m_nLife = nLife;//HP
	m_particletype = particletype;//種類
	m_nIndex++;
	CScene2d::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CParticle::Uninit(void)
{
	m_nIndex--;
	CScene2d::Uninit();
}

//更新
void CParticle::Update(void)
{
	m_col.a -= m_fColAlphaValue;
	m_fRadius += m_fRadiusValue;

	static float fAngle = 0.0f;
	fAngle++;

	m_move.x = ((cosf((2 * D3DX_PI * fAngle* - 90) * D3DX_PI / 180)) * (m_fRadius * 1));
	m_move.y = ((sinf((2 * D3DX_PI * fAngle* - 90) * D3DX_PI / 180))* (m_fRadius * 1));

	//位置更新
	SetPolygon(m_pos + m_move, D3DXVECTOR3(m_fRadius, m_fRadius, 0), m_col, TYPE_PARTICLE, NULL);

	CScene2d::Update();

	m_nLife--;

	if (m_nLife <= 0)
	{
		//	弾の破棄
		Uninit();
	}
}

//描画
void CParticle::Draw(void)
{
	CScene2d::Draw();
}

//生成
CParticle * CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fColAlphaValue, float fRadius, int fRadiusValue, int nLife, PARTICLE_TYPE particletype)
{
	CParticle *pParticle;
	pParticle = new CParticle;
	pParticle->Init(pos, move, col, fColAlphaValue, fRadius, fRadiusValue, nLife, particletype);
	pParticle->SetType(TYPE_PARTICLE);
	return pParticle;
}

//画像ロード
HRESULT CParticle::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "TEX/bullet000.png", &m_apParticleTexture[0]);
	//D3DXCreateTextureFromFile(pDevice, "TEX/particle001.png", &m_apParticleTexture[1]);

	return S_OK;
}

//画像破棄
void CParticle::Unload(void)
{
	// テクスチャの破棄
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