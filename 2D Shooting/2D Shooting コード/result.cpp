#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "input.h"
#include "fade.h"

LPDIRECT3DTEXTURE9 CResult::m_apTexture[] = {};

CResult::CResult()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));
}

CResult::~CResult()
{
}

CResult * CResult::Create(void)
{
	CResult *pResult;
	pResult = new CResult;
	pResult->Init();
	return pResult;
}

HRESULT CResult::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, RESULT_1, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, RESULT_2, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, RESULT_3, &m_apTexture[2]);

	for (int nCount = 0; nCount < MAX_RESULT_POLYGON; nCount++)
	{
		m_apPolygon[nCount] = CPolygon::Create();

		if (m_apPolygon[nCount] != NULL)
		{
			m_apPolygon[nCount]->BindTexture(m_apTexture[nCount]);
		}
	}
	return S_OK;
}

void CResult::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_RESULT_TEX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
	for (int nCount = 0; nCount < MAX_RESULT_TEX; nCount++)
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

void CResult::Update(void)
{
	m_apPolygon[0]->SetPolygon(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2, 0), D3DXVECTOR3(RESULT_1_SIZE_WIDTH, RESULT_1_SIZE_HIGHT, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apPolygon[1]->SetPolygon(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2, 0), D3DXVECTOR3(RESULT_2_SIZE_WIDTH, RESULT_2_SIZE_HIGHT, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apPolygon[2]->SetPolygon(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2, 0), D3DXVECTOR3(RESULT_3_SIZE_WIDTH, RESULT_3_SIZE_HIGHT, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//if (CManeger::GetInputKeyboard()->GetKeyPress(DIK_RETURN) && CManeger::GetMode() == CManeger::MODE_RESULT)
	//{
	//	CManeger::GetFade()->SetFade(CManeger::MODE_TITLE);
	//	//CManeger::SetMode(CManeger::MODE_TITLE);
	//}
}

void CResult::Draw(void)
{
	if (m_apPolygon != NULL)
	{
		for (int nCount = 0; nCount < MAX_RESULT_POLYGON; nCount++)
		{
			m_apPolygon[nCount]->Draw();
		}
	}
}