#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "explosion.h"
#include "game.h"

LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[] = {};
int CEnemy::m_nId = 0;

CEnemy::CEnemy(int nPriority)
{

}

CEnemy::~CEnemy()
{
}

HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "TEX/enemy000.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "TEX/enemy001.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "TEX/enemy002.png", &m_apTexture[2]);

	return S_OK;
}

void CEnemy::Unload(void)
{
	for (int nCount = 0; nCount < MAX_ENEMY_TEX; nCount++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

HRESULT CEnemy::Init(D3DXVECTOR3 pos, ENEMY_TYPE enemy, int nRate)
{
	CScene2d::Init();

	m_pos = pos;
	m_nRate = nRate;

	BindTexture(m_apTexture[enemy]);

	m_nId++;

	return S_OK;
}

void CEnemy::Uninit(void)
{
	m_nId--;

	if (m_nId <= 0)
	{
		CGame::SetMode(CGame::MODE_BOSS);
	}
	CScene2d::Uninit();
}

void CEnemy::Update(void)
{
	m_nCount++;

	if (m_nCount >= m_nRate)
	{
		CBullet::Create(m_pos, D3DXVECTOR3(0.0f, 10.0f, 0.0f), TYPE_BULLET_E, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(10.0f,10.0f,0.0f), MAX_BULLET_LIFE, CBullet::BULLET_TYPE::TYPE_NORMAL);

		m_nCount = 0;
	}

	//位置更新
	SetPolygon(m_pos, D3DXVECTOR3(ENEMY_SIZE_WIDTH, ENEMY_SIZE_HIGHT, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), TYPE_ENEMY, NULL);

	CScene2d::Update();
}

void CEnemy::Draw(void)
{
	CScene2d::Draw();
}

CEnemy * CEnemy::Create(D3DXVECTOR3 pos, ENEMY_TYPE enemy, int nRate)
{
	CEnemy *pEnemy;
	pEnemy = new CEnemy;
	pEnemy->Init(pos, enemy, nRate);
	pEnemy->SetType(TYPE_ENEMY);
	return pEnemy;
}
