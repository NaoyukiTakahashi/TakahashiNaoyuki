#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "input.h"
#include "fade.h"

LPDIRECT3DTEXTURE9 CTitle::m_apTexture[] = {};

CTitle::CTitle(int nPriority)
{
	memset(m_apTexture, 0, sizeof(m_apTexture));
}

CTitle::~CTitle()
{
}

CTitle * CTitle::Create(void)
{
	CTitle *pTitle;
	pTitle = new CTitle;
	pTitle->Init();
	return pTitle;
}

HRESULT CTitle::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TITLE_1, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TITLE_2, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TITLE_3, &m_apTexture[2]);

	for (int nCount = 0; nCount < MAX_TITLE_POLYGON; nCount++)
	{
		m_apPolygon[nCount] = CPolygon::Create();

		if (m_apPolygon[nCount] != NULL)
		{
			m_apPolygon[nCount]->BindTexture(m_apTexture[nCount]);
		}
	}

	return S_OK;
}

void CTitle::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_TITLE_TEX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
	for (int nCount = 0; nCount < MAX_TITLE_TEX; nCount++)
	{
		if (m_apPolygon[nCount] != NULL)
		{
			m_apPolygon[nCount]->Uninit();
			delete m_apPolygon[nCount];
			m_apPolygon[nCount] = NULL;
		}
	}
	Release();
}

void CTitle::Update(void)
{
	m_apPolygon[0]->SetPolygon(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2, 0), D3DXVECTOR3(TITLE_1_SIZE_WIDTH, TITLE_1_SIZE_HIGHT, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apPolygon[1]->SetPolygon(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2, 0), D3DXVECTOR3(TITLE_2_SIZE_WIDTH, TITLE_2_SIZE_HIGHT, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apPolygon[2]->SetPolygon(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2, 0), D3DXVECTOR3(TITLE_3_SIZE_WIDTH, TITLE_3_SIZE_HIGHT, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	//キー取得
	if (CManeger::GetInputKeyboard()->GetKeyPress(DIK_RETURN)&& CManeger::GetMode() == CManeger::MODE_TITLE)
	{
		CManeger::GetFade()->SetFade(CManeger::MODE_GAME);
		//CManeger::SetMode(CManeger::MODE_GAME);
	}
}

void CTitle::Draw(void)
{
	if (m_apPolygon != NULL)
	{
		for (int nCount = 0; nCount < MAX_TITLE_POLYGON; nCount++)
		{
			m_apPolygon[nCount]->Draw();
		}
	}
}