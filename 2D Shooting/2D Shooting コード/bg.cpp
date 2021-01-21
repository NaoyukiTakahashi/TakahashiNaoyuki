#include "bg.h"
#include "manager.h"
#include "renderer.h"

LPDIRECT3DTEXTURE9 CBg::m_apTexture[] = {};

CBg::CBg(int nPriority)
{
	for (int nCount = 0; nCount < MAX_BG_POLYGON; nCount++)
	{
		if (m_apScene2D[nCount] == NULL)//continue;
		{
			m_apScene2D[nCount] = NULL;
			break;
		}
	}
}

CBg::~CBg()
{
}

HRESULT CBg::Load(void)
{

	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, BG_1, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, BG_2, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, BG_3, &m_apTexture[2]);

	return S_OK;
}

HRESULT CBg::UnLoad(void)
{
	// テクスチャの開放
	for (int nCount = 0; nCount < MAX_BG_TEX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
	return S_OK;
}

HRESULT CBg::Init(void)
{
	for (int nCount = 0; nCount < MAX_BG_POLYGON; nCount++)
	{
		m_apScene2D[nCount] = CScene2d::Create();

		if (m_apScene2D[nCount] != NULL)
		{
			m_apScene2D[nCount]->BindTexture(m_apTexture[nCount]);
		}
	}

	return S_OK;
}

void CBg::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_BG_POLYGON; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			m_apScene2D[nCount]->Uninit();
			m_apScene2D[nCount] = NULL;
		}
	}
	Release();
}

void CBg::Update(void)
{
	m_apScene2D[0]->SetPolygon(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2, 0),D3DXVECTOR3(BG_SIZE_WIDTH, BG_SIZE_HIGHT, 0),D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), TYPE_BG, 0);
	m_apScene2D[1]->SetPolygon(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2, 0), D3DXVECTOR3(BG_SIZE_WIDTH, BG_SIZE_HIGHT, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), TYPE_BG, 0);
	m_apScene2D[2]->SetPolygon(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2, 0), D3DXVECTOR3(BG_SIZE_WIDTH, BG_SIZE_HIGHT, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), TYPE_BG, 0);
}

void CBg::Draw(void)
{
}

CBg * CBg::Create(void)
{
	CBg *pBg;
	pBg = new CBg;
	pBg->Init();
	pBg->SetType(TYPE_BG);
	return pBg;
}