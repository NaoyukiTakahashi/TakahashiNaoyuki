#include "main.h"
#include "fade.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "input.h"

CFade::CFade()
{
	m_fade = FADE_NONE;					// フェード状態
	m_modeNext = CManeger::MODE_NONE;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);			// フェード色
}

CFade::~CFade()
{
}

CFade * CFade::Create(void)
{
	CFade *pFade;
	pFade = new CFade;
	pFade->Init();
	return pFade;
}

void CFade::SetFade(CManeger::MODE modeNext)
{
	if (m_fade == FADE_NONE)
	{
		m_fade = FADE_OUT;
		m_modeNext = modeNext;
		m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}

void CFade::Init()
{

	m_fade = FADE_IN;
	m_modeNext = CManeger::MODE_TITLE;
	m_colorFade = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);// 黒い画面（不透明）
	CManeger::SetMode(m_modeNext);
	m_pPolygon = CPolygon::Create();
}

void CFade::Uninit(void)
{
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Uninit();
		delete m_pPolygon;
		m_pPolygon = NULL;
	}
}

void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{// フェード処理中
		if (m_fade == FADE_IN)
		{// フェードイン処理
			m_colorFade.a -= FADE_RATE;// α値を減算して後ろの画面を浮き上がらせる
			if (m_colorFade.a <= 0.0f)
			{
				// フェード処理終了
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{// フェードアウト処理
			m_colorFade.a += FADE_RATE;// α値を加算して後ろの画面を消していく
			if (m_colorFade.a >= 1.0f)
			{
				// フェードイン処理に切り替え
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;

				// モードを設定
				CManeger::SetMode(m_modeNext);
			}
		}
	}
	m_pPolygon->SetPolygon(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HIGHT, 0), m_colorFade);
}

void CFade::Draw(void)
{
	m_pPolygon->Draw();
}
