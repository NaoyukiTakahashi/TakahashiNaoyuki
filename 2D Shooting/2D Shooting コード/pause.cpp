#include "main.h"
#include "pause.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "input.h"

LPDIRECT3DTEXTURE9 CPause::m_apTexture[];

CPause::CPause()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));
	m_pause = PAUSE_OFF;					// フェード状態
	m_colorPause = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);			// フェード色
}

CPause::~CPause()
{
}

CPause * CPause::Create(void)
{
	CPause *pFade;
	pFade = new CPause;
	pFade->Init();
	return pFade;
}

void CPause::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();
	m_pause = PAUSE_OFF;
	m_colorPause = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);// 黒い画面（不透明）_modeNext);
	
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, PAUSE_1, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_2, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, PAUSE_3, &m_apTexture[2]);

	for (int nCount = 0; nCount < MAX_PAUSE_POLYGON; nCount++)
	{
		m_apPolygon[nCount] = CPolygon::Create();

		if (m_apPolygon[nCount] != NULL)
		{
			m_apPolygon[nCount]->BindTexture(m_apTexture[nCount]);
		}
	}
}

void CPause::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_PAUSE_TEX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
	for (int nCount = 0; nCount < MAX_PAUSE_POLYGON; nCount++)
	{
		if (m_apPolygon[nCount] != NULL)
		{
			m_apPolygon[nCount]->Uninit();
			delete m_apPolygon[nCount];
			m_apPolygon[nCount] = NULL;
		}
	}
}

void CPause::Update(void)
{
	if (CManeger::GetInputKeyboard()->GetKeyTrigger(DIK_TAB))
	{
		m_pause = PAUSE_OFF;
	}
	else
	{
		m_apPolygon[0]->SetPolygon(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2, 0), D3DXVECTOR3(PAUSE_1_SIZE_WIDTH, PAUSE_1_SIZE_HIGHT, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apPolygon[1]->SetPolygon(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2, 0), D3DXVECTOR3(PAUSE_2_SIZE_WIDTH, PAUSE_2_SIZE_HIGHT, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
		m_apPolygon[2]->SetPolygon(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2, 0), D3DXVECTOR3(PAUSE_3_SIZE_WIDTH, PAUSE_3_SIZE_HIGHT, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));
	}
}

void CPause::Draw(void)
{
	if (m_apPolygon != NULL)
	{
		for (int nCount = 0; nCount < MAX_PAUSE_POLYGON; nCount++)
		{
			m_apPolygon[nCount]->Draw();
		}
	}
}
