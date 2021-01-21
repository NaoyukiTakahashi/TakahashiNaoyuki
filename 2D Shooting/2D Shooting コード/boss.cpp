#include "boss.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "explosion.h"
#include "fade.h"

LPDIRECT3DTEXTURE9 CBoss::m_apTexture[] = {};
int CBoss::m_nId = 0;
bool CBoss::m_bUse = false;
CBoss::STAGE_TYPE CBoss::m_stageType = CBoss::STAGE_NONE;

CBoss::CBoss(int nPriority) :CScene2d(nPriority)
{

}

CBoss::~CBoss()
{
}

HRESULT CBoss::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "TEX/body000.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "TEX/body001.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "TEX/body002.png", &m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "TEX/boss001.png", &m_apTexture[3]);
	D3DXCreateTextureFromFile(pDevice, "TEX/boss002.png", &m_apTexture[4]);
	D3DXCreateTextureFromFile(pDevice, "TEX/boss003.png", &m_apTexture[5]);

	return S_OK;
}

void CBoss::Unload(void)
{
	for (int nCount = 0; nCount < MAX_BOSS_TEX; nCount++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

void CBoss::SetState(STATE state)
{
	m_state = state;

	if (m_state == STATE_HIT)
	{
		m_nLife += -1;

		if (m_nLife <= 0)
		{
			m_state = STATE_DETH;
			if (m_stageType == STAGE000)
			{
				m_stageType = STAGE001;
			}
			else if (m_stageType == STAGE001)
			{
				m_stageType = STAGE002;
			}
			if (m_bossType == BOSS_TYPE000)
			{
				CManeger::GetFade()->SetFade(CManeger::MODE_RESULT);
			}
		}
		else
		{
			m_state = STATE_INVINCIBLE;
			m_col = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
		}
	}
}

HRESULT CBoss::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, BOSS_TYPE boss, int nRate)
{
	CScene2d::Init();

	static int nCount = 0;

	static int nCount2 = 0;

	m_bUse = true;

	m_pos = pos;
	m_size = size;
	m_nRate = nRate;

	m_bossType = boss;

	m_state = STATE_NONE;

	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	BindTexture(m_apTexture[boss]);

	m_nId++;

	m_nLife = 0;

	switch (m_bossType)
	{
	case CBoss::BOSS_BODY000:
		break;
	case CBoss::BOSS_BODY001:
		break;
	case CBoss::BOSS_BODY002:
		break;
	case CBoss::BOSS_TYPE000:
		m_nLife = BOSS_TYPE000_LIFE;
		break;
	case CBoss::BOSS_TYPE001:
		m_nTypeIndex = nCount++;
		m_nLife = BOSS_TYPE001_LIFE;
		break;
	case CBoss::BOSS_TYPE002:
		m_nTypeIndex2 = nCount2++;
		m_nLife = BOSS_TYPE002_LIFE;
		break;
	case CBoss::BOSS_TYPE_MAXINUM:
		break;
	default:
		break;
	}

	return S_OK;
}

void CBoss::Uninit(void)
{
	if (m_state == STATE_DETH)
	{
		m_bUse = false;
	}
	CScene2d::Uninit();
}

void CBoss::Update(void)
{
	static int nCount = 0;
	static int nCount2 = 0;//射撃間隔
	static int nCount3 = 0;//射撃間隔
	static int nCount4 = 0;//射撃間隔

	static bool bUse3 = false;

	switch (m_stageType)
	{
	case CBoss::STAGE_NONE:
		StageNext();
		break;
	case CBoss::STAGE000:
		nCount2++;
		if (m_bossType == BOSS_TYPE001)
		{
			if (0 == nCount2 %10 && nCount2 <=280)
			{
				CBullet::Create(D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y + 40.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), TYPE_BULLET_E, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 500, CBullet::BULLET_TYPE::TYPE_TARGET);
				CBullet::Create(D3DXVECTOR3(m_pos.x - 20.0f, m_pos.y + 40.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), TYPE_BULLET_E, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 500, CBullet::BULLET_TYPE::TYPE_TARGET);
			}
			if (nCount2 >= 500)
			{
				nCount2 = 0;
			}
		}
		if (m_state == STATE_INVINCIBLE)
		{
			nCount++;

			if (nCount >= 50)
			{
				nCount = 0;
				m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				m_state = STATE_NORMAL;
			}
		}
			break;
	case CBoss::STAGE001:
		if (m_bossType == BOSS_BODY001 || m_bossType == BOSS_TYPE002)
		{
			if (m_pos.y <= 180.0f && m_state == STATE_NONE)
			{
				m_move.y = 2;
				m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			}
			else
			{
				m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				m_move.y = 0;
				static bool bUse = false;

				if (m_bossType == BOSS_TYPE002)
				{
					if (bUse == false)
					{
						m_state = STATE_NORMAL;
						bUse = true;
					}
					nCount2++;
					nCount3++;
					if (0 == nCount2 % 20 && nCount2 <= 280 && m_nTypeIndex2 == 0)
					{
						CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 40.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), TYPE_BULLET_E, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), 500, CBullet::BULLET_TYPE::TYPE_TARGET);
					}
					if (0 == nCount3 % 20 && nCount3 <= 280 && m_nTypeIndex2 == 1)
					{
						CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 40.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), TYPE_BULLET_E, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), 500, CBullet::BULLET_TYPE::TYPE_TARGET);
					}

				}
			}
			if (nCount2 >= 500)
			{
				nCount2 = 0;
			}
			if (nCount3 >= 500)
			{
				nCount3 = 0;
			}
		}
		if (m_state == STATE_INVINCIBLE)
		{
			nCount++;
			if (nCount >= 50)
			{
				nCount = 0;
				m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				m_state = STATE_NORMAL;
			}
		}
		if (m_bossType == BOSS_BODY002 || m_bossType == BOSS_TYPE000 || (m_bossType == BOSS_TYPE001&&m_nTypeIndex != 0))
		{
			if (m_pos.y <= -0.0f)
			{
				m_move.y = 2;
				m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			}
			else
			{
				m_move.y = 0;
			}
		}
		if (m_bossType == BOSS_BODY000)
		{
			if (m_pos.y <= 350.0f)
			{
				m_move.y = 2;
				m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			}
			else
			{
				m_move.y = 0;
			}
		}
		break;
	case CBoss::STAGE002:
		if (m_bossType == BOSS_TYPE001&&m_nTypeIndex == 1)
		{
			if (m_pos.y <= 100.0f && m_state == STATE_NONE)
			{
				m_move.y = 2;
				m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			}
			else
			{
				m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				m_move.y = 0;
				static bool bUse1 = false;
				if (bUse1 == false)
				{
					m_state = STATE_NORMAL;
					bUse1 = true;
				}
				if (m_bossType == BOSS_TYPE001&&m_nTypeIndex == 1)
				{
					nCount2++;
					if (0 == nCount2 % 10 && nCount2 <= 280)
					{
						CBullet::Create(D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y + 40.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), TYPE_BULLET_E, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 500, CBullet::BULLET_TYPE::TYPE_TARGET);
						CBullet::Create(D3DXVECTOR3(m_pos.x - 20.0f, m_pos.y + 40.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), TYPE_BULLET_E, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 500, CBullet::BULLET_TYPE::TYPE_TARGET);
					}
					if (nCount2 >= 500)
					{
						nCount2 = 0;
					}
				}
			}
		}
		if (m_bossType == BOSS_TYPE001&&m_nTypeIndex == 2)
		{
			if (m_pos.y <= 100.0f && m_state == STATE_NONE)
			{
				m_move.y = 2;
				m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			}
			else
			{
				m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				m_move.y = 0;
				static bool bUse2 = false;
				if (bUse2 == false)
				{
					m_state = STATE_NORMAL;
					bUse2 = true;
				}
				if (m_bossType == BOSS_TYPE001&&m_nTypeIndex == 2)
				{
					nCount2++;
					if (0 == nCount2 % 10 && nCount2 <= 280)
					{
						CBullet::Create(D3DXVECTOR3(m_pos.x + 20.0f, m_pos.y + 40.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), TYPE_BULLET_E, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 500, CBullet::BULLET_TYPE::TYPE_TARGET);
						CBullet::Create(D3DXVECTOR3(m_pos.x - 20.0f, m_pos.y + 40.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), TYPE_BULLET_E, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 500, CBullet::BULLET_TYPE::TYPE_TARGET);
					}
					if (nCount2 >= 500)
					{
						nCount2 = 0;
					}
				}
			}
		}
		if (m_bossType == BOSS_BODY001 || m_bossType == BOSS_TYPE002)
		{
			m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			if (m_bossType == BOSS_TYPE002)
			{
				m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
				m_pos.y = 2000.0f;
			}
			if (m_pos.y <= 280.0f)
			{
				m_move.y = 2;
				m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			}
			else
			{
				m_move.y = 0;
			}
		}
		if (m_state == STATE_INVINCIBLE)
		{
			nCount++;
			if (nCount >= 50)
			{
				nCount = 0;
				m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				m_state = STATE_NORMAL;
			}
		}
		if (m_bossType == BOSS_BODY002 || m_bossType == BOSS_TYPE000)
		{
			if (m_pos.y <= 100.0f)
			{
				m_move.y = 2;
				m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			}
			else
			{
				m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				m_move.y = 0;
				if (m_bossType == BOSS_TYPE000&&m_state == STATE_NONE)
				{
					if (bUse3 == false)
					{
						m_state = STATE_NORMAL;
						bUse3 = true;
					}
				}
				if (m_bossType == BOSS_TYPE000)
				{
					nCount4++;
					if (0 == nCount4 % 25 && nCount4 <= 280)
					{
						CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 40.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), TYPE_BULLET_E, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f), 500, CBullet::BULLET_TYPE::TYPE_TARGET);
					}
					if (nCount4 >= 500)
					{
						nCount4 = 0;
					}
				}
			}
		}
		if (m_bossType == BOSS_BODY000)
		{
			if (m_pos.y <= 450.0f)
			{
				m_move.y = 2;
				m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			}
			else
			{
				m_move.y = 0;
			}
		}

		break;
	case CBoss::STAGE_MAXINUM:
		break;
	default:
		break;
	}

	if (m_bossType == BOSS_BODY000)
	{
		SetPolygon(m_pos, m_size, m_col, TYPE_BOSS, NULL);
	}

	m_pos = m_pos + m_move;

	//位置更新
	SetPolygon(m_pos, m_size, m_col, TYPE_BOSS, NULL);

	CScene2d::Update();
}

void CBoss::Draw(void)
{
	CScene2d::Draw();
}

void CBoss::StageNext(void)
{
	switch (m_stageType)
	{
	case CBoss::STAGE_NONE:
		if (m_bossType == BOSS_BODY001 || m_bossType == BOSS_TYPE002)
		{
			if (m_pos.y <= -20.0f)
			{
				m_move.y = 2;
				m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			}
			else
			{
				m_move.y = 0;
			}
		}
		if (m_bossType == BOSS_BODY002 || m_bossType == BOSS_TYPE000 || (m_bossType == BOSS_TYPE001&&m_nTypeIndex != 0))
		{
			if (m_pos.y <=  -200.0f)
			{
				m_move.y = 2;
				m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			}
			else
			{
				m_move.y = 0;
			}
		}
		if (m_bossType == BOSS_BODY000 || (m_bossType == BOSS_TYPE001&&m_nTypeIndex==0))
		{
			if (m_pos.y <= 150.0f)
			{
				m_move.y = 2;
				m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			}
			else
			{
				m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				m_move.y = 0;
				if (m_bossType == BOSS_TYPE001&&m_move.y == 0)
				{
					m_stageType = STAGE000;
					m_state = STATE_NORMAL;
				}
			}
		}
		break;
	case CBoss::STAGE000:
		if (m_bossType == BOSS_BODY001 || m_bossType == BOSS_TYPE002)
		{
			if (m_pos.y <= -20.0f)
			{
				m_move.y = 2;
				m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			}
			else
			{
				m_move.y = 0;
			}
		}
		if (m_bossType == BOSS_BODY002 || m_bossType == BOSS_TYPE000 || (m_bossType == BOSS_TYPE001&&m_nTypeIndex != 0))
		{
			if (m_pos.y <= -200.0f)
			{
				m_move.y = 2;
				m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			}
			else
			{
				m_move.y = 0;
			}
		}
		if (m_bossType == BOSS_BODY000)
		{
			m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			//if (m_pos.y <= 150.0f)
			//{
			//	m_move.y = 2;
			//	m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			//}
			//else
			//{
			//	m_col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			//	m_move.y = 0;
			//	if (m_bossType == BOSS_TYPE001&&m_move.y == 0)
			//	{
			//		m_stageType = STAGE000;
			//		m_state = STATE_NORMAL;
			//	}
			//}
		}
		m_stageType = STAGE001;
		break;
	case CBoss::STAGE001:
		m_stageType = STAGE002;
		break;
	case CBoss::STAGE002:
		m_stageType = STAGE_MAXINUM;
		break;
	case CBoss::STAGE_MAXINUM:
		m_stageType = STAGE000;
		break;
	default:
		break;
	}
}

CBoss * CBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, BOSS_TYPE boss, int nRate)
{
	CBoss *pBoss;
	pBoss = new CBoss;
	pBoss->Init(pos, size, boss, nRate);
	if (boss== BOSS_BODY000 || boss == BOSS_BODY001 || boss == BOSS_BODY002)
	{
		pBoss->SetType(TYPE_BOSSBODY);
	}
	else
	{
		pBoss->SetType(TYPE_BOSS);
	}
	return pBoss;
}
