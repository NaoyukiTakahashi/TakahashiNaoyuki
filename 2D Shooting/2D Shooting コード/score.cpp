#include "score.h"
#include "number.h"

CNumber *CScore::m_apNumber[MAX_SCORE];//データ保存用
int CScore::m_nScore=0;

CScore::CScore(int nPriority) :CScene(nPriority)
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
}

CScore::~CScore()
{
}

HRESULT CScore::Init(void)
{
	for (int nCntPlace = 0; nCntPlace < MAX_SCORE; nCntPlace++)
	{
		m_apNumber[nCntPlace] = CNumber::Create(D3DXVECTOR3(SCREEN_WIDTH - MAX_SCORE * 50 + nCntPlace*50, 50, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	}

	return S_OK;
}

void CScore::Uninit(void)
{
	for (int nCntPlace = 0; nCntPlace < MAX_SCORE; nCntPlace++)
	{
		if (m_apNumber[nCntPlace] != NULL)
		{
			m_apNumber[nCntPlace]->Uninit();
			m_apNumber[nCntPlace] = NULL;
		}
	}
	Release();
}

void CScore::Update(void)
{
	for (int nCntPlace = 0; nCntPlace < MAX_SCORE; nCntPlace++)
	{
		m_apNumber[nCntPlace]->Update();

		m_apNumber[nCntPlace]->SetNumber((m_nScore % (int)(powf(10.0f, (float)(MAX_SCORE - nCntPlace)))) / (int)(powf(10.0f, (float)(MAX_SCORE - nCntPlace - 1))));
	}
}

void CScore::Draw(void)
{
	for (int nCntPlace = 0; nCntPlace < MAX_SCORE; nCntPlace++)
	{
		m_apNumber[nCntPlace]->Draw();
	}
}

CScore * CScore::Create(void)
{
	CScore *pScore;
	pScore = new CScore;
	pScore->Init();
	pScore->SetType(TYPE_UI);
	return pScore;
}