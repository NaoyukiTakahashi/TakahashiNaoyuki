#include "life.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"

LPDIRECT3DTEXTURE9 CLife::m_apTexture[];
int CLife::m_nLife = MAX_LIFE;
int CLife::m_nEnegy = 0;

CLife::CLife(int nPriority) :CScene(nPriority)
{
	for (int nCount = 0; nCount < MAX_LIFE_POLYGON; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)//continue;
		{
			m_apScene2D[nCount] = NULL;
			break;
		}
	}
}

CLife::~CLife()
{
}

HRESULT CLife::Load(void)
{

	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, LIFE_1, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, ENERGY_1, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, GAUGE_1, &m_apTexture[2]);

	return S_OK;
}

HRESULT CLife::UnLoad(void)
{
	// テクスチャの開放
	for (int nCount = 0; nCount < MAX_LIFE_POLYGON; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}

	return S_OK;
}

HRESULT CLife::Init(void)
{
	for (int nCount = MAX_LIFE_TEX-1; 0 <= nCount; nCount--)
	{
		m_apScene2D[nCount] = CScene2d::Create();

		if (m_apScene2D[nCount] != NULL)
		{
			m_apScene2D[nCount]->BindTexture(m_apTexture[nCount]);
		}
	}

	return S_OK;
}

void CLife::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_LIFE_POLYGON; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			//m_apScene2D[nCount]->Uninit();
			m_apScene2D[nCount] = NULL;
		}
	}
	Release();
}

void CLife::Update(void)
{
	if (m_nLife<=0)
	{
		CManeger::GetFade()->SetFade(CManeger::MODE_RESULT);
	}

	m_apScene2D[0]->SetPolygon(D3DXVECTOR3(50.0f-20.0f, SCREEN_HIGHT, 0.0f), D3DXVECTOR3(40, GAUGE_SIZE_HIGHT / MAX_LIFE * m_nLife, 0), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), TYPE_LIFE, 0);
	m_apScene2D[1]->SetPolygon(D3DXVECTOR3(50.0f+23.5f, SCREEN_HIGHT, 0.0f), D3DXVECTOR3(25, GAUGE_SIZE_HIGHT / MAX_ENERGY * m_nEnegy, 0), D3DXCOLOR(1.0f, 0.6f, 0.0f, 1.0f), TYPE_LIFE, 0);
	m_apScene2D[2]->SetPolygon(D3DXVECTOR3(50.0f, SCREEN_HIGHT, 0.0f), D3DXVECTOR3(GAUGE_SIZE_WIDTH, GAUGE_SIZE_HIGHT+10, 0), D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f), TYPE_LIFE, 0);
}

void CLife::Draw(void)
{
}

void CLife::SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type, int nPattern)
{
}

void CLife::SubLife(int nLife)
{
	if (m_nLife < MAX_LIFE)
	{
		m_nLife += nLife;
	}
	else if (nLife < 0)
	{
		m_nLife += nLife;
	}
	else if(m_nEnegy < MAX_ENERGY)
	{
		if (m_nEnegy + nLife >= MAX_ENERGY)
		{
			nLife -= (m_nEnegy + nLife) % 10;
		}

		SubEnergy(nLife);
	}
	else
	{

	}
}

void CLife::SubEnergy(int nEnergy)
{
	m_nEnegy += nEnergy;
}

CLife * CLife::Create(void)
{
	CLife *pLife;
	pLife = new CLife;
	pLife->Init();
	pLife->SetType(TYPE_LIFE);
	return pLife;
}