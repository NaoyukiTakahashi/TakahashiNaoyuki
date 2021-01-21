#include "main.h"
#include "fade.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "input.h"

CFade::CFade()
{
	m_fade = FADE_NONE;					// �t�F�[�h���
	m_modeNext = CManeger::MODE_NONE;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);			// �t�F�[�h�F
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
	m_colorFade = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);// ������ʁi�s�����j
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
	{// �t�F�[�h������
		if (m_fade == FADE_IN)
		{// �t�F�[�h�C������
			m_colorFade.a -= FADE_RATE;// ���l�����Z���Č��̉�ʂ𕂂��オ�点��
			if (m_colorFade.a <= 0.0f)
			{
				// �t�F�[�h�����I��
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{// �t�F�[�h�A�E�g����
			m_colorFade.a += FADE_RATE;// ���l�����Z���Č��̉�ʂ������Ă���
			if (m_colorFade.a >= 1.0f)
			{
				// �t�F�[�h�C�������ɐ؂�ւ�
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;

				// ���[�h��ݒ�
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
