//=============================================================================
//
// バレット処理 [bullet.cpp]
// Author : 
//
//=============================================================================

//*****************************************************************************
// ファイルインクルード
//*****************************************************************************
#include "bullet.h"
#include "manager.h"
#include "input.h"
#include "scene2d.h"
#include "renderer.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "game.h"
#include "effect.h"
#include "particle.h"
#include "boss.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_apBulletTexture[];

//=============================================================================
// コンストラクタ関数
//=============================================================================
CBullet::CBullet(int nPriority) :CScene2d(nPriority)
{
}

//=============================================================================
// デストラクタ関数
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type, D3DXCOLOR col, D3DXVECTOR3 size, int nLife, BULLET_TYPE bullettype)
{
	if (bullettype == TYPE_WAVE)
	{
		BindTexture(m_apBulletTexture[1]);
	}
	else
	{
		BindTexture(m_apBulletTexture[0]);
	}

	m_pos = pos;
	m_type = type;
	m_col = col;
	m_size = size;
	m_nLife = nLife;
	m_bullettype = bullettype;
	if (m_bullettype != TYPE_TARGET)
	{
		m_move = move;
	}
	else
	{
		m_move = SetBulletMove(m_bullettype, move);
	}
	CScene2d::Init();
	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2d::Uninit();
}

//更新
void CBullet::Update(void)
{
	D3DXVECTOR3 posEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//位置更新
	if (m_bullettype != TYPE_TARGET)
	{
		SetPolygon(D3DXVECTOR3(m_pos += SetBulletMove(m_bullettype, m_move)), D3DXVECTOR3(m_size.x, m_size.y, 0), m_col, m_type, NULL);
	}
	else 
	{
		SetPolygon(D3DXVECTOR3(m_pos += m_move), D3DXVECTOR3(m_size.x, m_size.y, 0), m_col, m_type, NULL);
	}

	CScene2d::Update();

	m_nLife--;

	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			//CScene *pScene = GetScene(nCntPriority,nCntScene);
			//if (pScene != NULL)
			//{
			//	TYPE type = pScene->GetObjType();
			//	STATE state = pScene->GetScene(nCntPriority,nCntScene)->GetState();

			//	if (type == TYPE_ENEMY)
			//	{
			//		posEnemy = pScene->GetPosition();

			//		if (m_type == TYPE_BULLET_P)
			//		{
			//			CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 0.05f, 10, 2, 30, CEffect::TYPE_NORMAL);
			//			//当たり判定
			//			if (posEnemy.x - ENEMY_SIZE_WIDTH / 2 <= m_pos.x + m_size.x / 2 && m_pos.x - m_size.x / 2 <= posEnemy.x + ENEMY_SIZE_WIDTH / 2 &&
			//				posEnemy.y - ENEMY_SIZE_HIGHT / 2 <= m_pos.y + m_size.y / 2 && m_pos.y - m_size.y / 2 <= posEnemy.y + ENEMY_SIZE_HIGHT / 2)//弾と敵が重なった
			//			{
			//				//	敵の破棄
			//				pScene->Uninit();

			//				if (m_bullettype == TYPE_WAVE)
			//				{

			//				}
			//				else
			//				{
			//					m_nLife = 0;
			//				}

			//				CScore::addScore(100);

			//				break;
			//			}
			//			else
			//			{

			//			}
			//		}
			//		else
			//		{

			//		}
			//	}
			//	else if (type == TYPE_BOSS)
			//	{
			//		posEnemy = pScene->GetPosition();

			//		if (m_type == TYPE_BULLET_P)
			//		{
			//			CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 0.05f, 10, 2, 30, CEffect::TYPE_NORMAL);
			//			//当たり判定
			//			if (posEnemy.x - ENEMY_SIZE_WIDTH / 2 <= m_pos.x + m_size.x / 2 && m_pos.x - m_size.x / 2 <= posEnemy.x + ENEMY_SIZE_WIDTH / 2 &&
			//				posEnemy.y - ENEMY_SIZE_HIGHT / 2 <= m_pos.y + m_size.y / 2 && m_pos.y - m_size.y / 2 <= posEnemy.y + ENEMY_SIZE_HIGHT / 2)//弾と敵が重なった
			//			{
			//				if (pScene->GetScene(nCntPriority, nCntScene)->GetState() == STATE_NORMAL)
			//				{
			//						pScene->GetScene(nCntPriority, nCntScene)->SetState(STATE_HIT);
			//				}

			//				if (pScene->GetScene(nCntPriority, nCntScene)->GetState() == STATE_DETH)
			//				{
			//					//	敵の破棄
			//					pScene->Uninit();
			//				}

			//				if (m_bullettype == TYPE_WAVE)
			//				{

			//				}
			//				else
			//				{
			//					m_nLife = 0;
			//				}

			//				CScore::addScore(100);

			//				break;
			//			}
			//			else
			//			{

			//			}
			//		}
			//		else
			//		{

			//		}
			//	}
			//	else if (type == TYPE_PLAYER)
			//	{
			//		posPlayer = pScene->GetPosition();

			//		if (m_type == TYPE_BULLET_E)
			//		{
			//			//当たり判定
			//			if (posPlayer.x + PLAYER_HIT_TEST - ENEMY_SIZE_WIDTH / 2 <= m_pos.x - PLAYER_HIT_TEST + m_size.x / 2 && m_pos.x + PLAYER_HIT_TEST - m_size.x / 2 <= posPlayer.x - PLAYER_HIT_TEST + ENEMY_SIZE_WIDTH / 2 &&
			//				posPlayer.y + PLAYER_HIT_TEST - ENEMY_SIZE_HIGHT / 2 <= m_pos.y - PLAYER_HIT_TEST + m_size.y / 2 && m_pos.y + PLAYER_HIT_TEST - m_size.y / 2 <= posPlayer.y - PLAYER_HIT_TEST + ENEMY_SIZE_HIGHT / 2)//弾と敵が重なった
			//			{
			//				if (state == STATE_NORMAL)
			//				{
			//					CGame::GetLife()->SubLife(-1);
			//					pScene->GetScene(nCntPriority,nCntScene)->SetState(STATE_HIT);

			//					if (CGame::GetLife()->GetLife() <= 0)
			//					{
			//						//自機の破棄
			//						pScene->Uninit();
			//					}

			//				}
			//				else
			//				{

			//				}

			//				m_nLife = 0;

			//				break;
			//			}
			//		}
			//		else
			//		{

			//		}
			//	}
			//	else
			//	{

			//	}
			//}
		}
	}

	if (m_nLife <= 0 || m_pos.x <= 0.0f || SCREEN_WIDTH <= m_pos.x || m_pos.y <= 0.0f || SCREEN_HIGHT <= m_pos.y)
	{
		CExplosion::Create(m_pos);
		//	弾の破棄
		Uninit();
	}
}

//描画
void CBullet::Draw(void)
{
	CScene2d::Draw();
}

//生成
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type, D3DXCOLOR col, D3DXVECTOR3 size, int nLife, BULLET_TYPE bullettype)
{
	CBullet *pBullet;
	pBullet = new CBullet;
	pBullet->Init(pos, move, type, col, size, nLife, bullettype);
	pBullet->SetType(type);

	return pBullet;
}

//画像ロード
HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "TEX/bullet000.png", &m_apBulletTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "TEX/bullet001.png", &m_apBulletTexture[1]);

	return S_OK;
}

//画像破棄
void CBullet::Unload(void)
{
	// テクスチャの破棄
	for (int nCount = 0; nCount < MAX_BULLET_TEX; nCount++)
	{
		if (m_apBulletTexture[nCount] != NULL)
		{
			m_apBulletTexture[nCount]->Release();
			m_apBulletTexture[nCount] = NULL;
		}
	}
}

D3DXVECTOR3 CBullet::SetBulletMove(BULLET_TYPE bullettype,D3DXVECTOR3 move)
{
	float fDistance = 0.0f;
	static float fComparison = 0.0f;
	float fDistance_x = 0.0f;
	float fDistance_y = 0.0f;
	float fAngle = 0.0f;
	int nCount = 0;
	D3DXVECTOR3 nMove;
	D3DXVECTOR3 bulletmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posEnemy = D3DXVECTOR3(0.0f,0.0f,0.0f);
	static D3DXVECTOR3 NearposEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (bullettype)
	{
	case TYPE_NORMAL:
		bulletmove = move;
		break;
	case TYPE_TARGET:
		for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
		{
			for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				/*CScene *pScene = GetScene(nCntPriority, nCntScene);
				if (pScene != NULL)
				{
					TYPE type = pScene->GetObjType();
					STATE state = pScene->GetScene(nCntPriority, nCntScene)->GetState();
					if (type == TYPE_PLAYER)
					{
						posPlayer = pScene->GetPosition();
						fDistance_x = posPlayer.x - m_pos.x;
						fDistance_y = posPlayer.y - m_pos.y;
					}
				}*/
			}
		}
		fAngle = atan2f(fDistance_y, fDistance_x);
		bulletmove = D3DXVECTOR3(cosf(fAngle) * move.x, sinf(fAngle) * move.y, 0.0f);
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
					if (type == TYPE_BOSS)
					{
						posEnemy = pScene->GetPosition();
						fDistance_x = posEnemy.x - m_pos.x;
						fDistance_y = posEnemy.y - m_pos.y;
						fDistance = sqrtf(fDistance_x * fDistance_x + fDistance_y * fDistance_y);
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
		bulletmove = D3DXVECTOR3(cosf(fAngle) * -move.x, sinf(fAngle) * -move.y, 0.0f);
		break;
	case TYPE_WAVE:
		bulletmove = move;
		break;
	default:
		break;
	}
	return bulletmove;
}
