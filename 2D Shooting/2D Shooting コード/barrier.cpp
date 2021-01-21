//=============================================================================
//
// バレット処理 [barrier.cpp]
// Author : 
//
//=============================================================================

//*****************************************************************************
// ファイルインクルード
//*****************************************************************************
#include "barrier.h"
#include "manager.h"
#include "input.h"
#include "scene2d.h"
#include "renderer.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "bullet.h"
#include "game.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBarrier::m_pBarrierTexture = NULL;

//=============================================================================
// コンストラクタ関数
//=============================================================================
CBarrier::CBarrier(int nPriority) :CScene2d(nPriority)
{
}

//=============================================================================
// デストラクタ関数
//=============================================================================
CBarrier::~CBarrier()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CBarrier::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type, D3DXCOLOR col, int nSize)
{
	BindTexture(m_pBarrierTexture);
	m_move = move;
	m_pos = pos;
	m_type = type;
	m_col = col;
	m_nSize = nSize;
	CScene2d::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CBarrier::Uninit(void)
{
	CScene2d::Uninit();
}

//更新
void CBarrier::Update(void)
{
	D3DXVECTOR3 posEnemyBullet;
	D3DXVECTOR2 EnemyBulletSize;
	D3DXVECTOR3 posPlayer;
	static int nCount = 0;

	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			/*CScene *pScene = GetScene(nCntPriority, nCntScene);
			if (pScene != NULL)
			{
				TYPE type = pScene->GetObjType();

				if (type == TYPE_PLAYER)
				{
					posPlayer = pScene->GetPosition();
				}
			}*/
		}
	}
	//CScene *pScene2 = GetScene(5, 2);
	//TYPE type2 = pScene2->GetObjType();
	//D3DXVECTOR3 posEnemyBullet2 = pScene2->GetPosition();
	//D3DXVECTOR2 EnemyBulletSize2 = pScene2->GetSize();

	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			//CScene *pScene = GetScene(nCntPriority, nCntScene);
			//if (pScene != NULL)
			//{
			//	TYPE type = pScene->GetObjType();

			//	if (type == TYPE_BULLET_E)
			//	{
			//		posEnemyBullet = pScene->GetPosition();

			//		float fDistance_x = posEnemyBullet.x - posPlayer.x;
			//		float fDistance_y = posEnemyBullet.y - posPlayer.y;
			//		float fDistance = sqrt(fDistance_x * fDistance_x + fDistance_y * fDistance_y);

			//		if (fDistance <= m_nSize - 70 && nCount < 15)
			//		{
			//			//	敵の弾の破棄
			//			pScene->Uninit();
			//			CGame::GetLife()->SubLife(1);
			//			CBullet::Create(posPlayer, D3DXVECTOR3(-10.0f, -10.0f, 0.0f), TYPE_BULLET_P, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), D3DXVECTOR3(50.0f,50.0f,0.0f), 50, CBullet::TYPE_HOMING);
			//			CScore::addScore(100);

			//		}
			//		else if(fDistance <= m_nSize - 70)
			//		{
			//			pScene->Uninit();
			//			CExplosion::Create(posEnemyBullet);
			//		}
			//	}
			//	else
			//	{

			//	}
			//}
		}
	}

	if (nCount >= 100)
	{
		//位置更新
		SetPolygon(D3DXVECTOR3(posPlayer), D3DXVECTOR3(m_nSize, m_nSize, 0), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), m_type, NULL);

		nCount = 0;

		CScene2d::Update();
		Uninit();
	}
	else if (nCount >= 80)
	{
		//位置更新
		SetPolygon(D3DXVECTOR3(posPlayer), D3DXVECTOR3(m_nSize, m_nSize, 0), D3DXCOLOR(m_col.r, 0.0f, 0.0f, 1.0f), m_type, NULL);

		CScene2d::Update();
		nCount++;
	}
	else if (nCount >= 15)
	{
		//位置更新
		SetPolygon(D3DXVECTOR3(posPlayer), D3DXVECTOR3(m_nSize, m_nSize, 0), D3DXCOLOR(1.0f, 1.0f, 0.0f, m_col.a - ((float)nCount / 150.0f)), m_type, NULL);

		CScene2d::Update();
		nCount++;
	}
	else
	{
		//位置更新
		SetPolygon(D3DXVECTOR3(posPlayer), D3DXVECTOR3(m_nSize, m_nSize, 0), D3DXCOLOR(0.3f, 1.0f, 0.0f, 1.0f), m_type, NULL);

		CScene2d::Update();
		nCount++;
	}
}

//描画
void CBarrier::Draw(void)
{
	CScene2d::Draw();
}

//生成
CBarrier * CBarrier::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type, D3DXCOLOR col, int nSize)
{
	CBarrier *pBarrier;
	pBarrier = new CBarrier;
	pBarrier->Init(pos, move, type, col, nSize);
	pBarrier->SetType(TYPE_BARRIER);
	return pBarrier;
}

//画像ロード
HRESULT CBarrier::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "TEX/barrier.png", &m_pBarrierTexture);

	return S_OK;
}

//画像破棄
void CBarrier::Unload(void)
{
	// テクスチャの破棄
	if (m_pBarrierTexture != NULL)
	{
		m_pBarrierTexture->Release();
		m_pBarrierTexture = NULL;
	}
}
