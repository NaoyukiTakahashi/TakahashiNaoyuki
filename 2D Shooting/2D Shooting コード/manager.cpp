//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : 
//
//=============================================================================

//*****************************************************************************
// ファイルインクルード
//*****************************************************************************
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "input.h"
#include "sound.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "pause.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CRenderer *CManeger::m_pRenderer = NULL;
CInputKeyboard *CManeger::m_pInputKeyboard = NULL;
CSound *CManeger::m_pSound = NULL;
CTitle *CManeger::m_pTitle = NULL;
CGame *CManeger::m_pGame = NULL;
CResult *CManeger::m_pResult = NULL;
CFade *CManeger::m_pFade;
CPause *CManeger::m_pPause;
CManeger::MODE CManeger::m_mode = CManeger::MODE_NONE;
//CPlayer *CManeger::m_pPlayer = NULL;
//CEnemy *CManeger::m_apEnemy[];//エネミー情報保持
//CScore *CManeger::m_pScore = NULL;

//=============================================================================
// コンストラクタ関数
//=============================================================================
CManeger::CManeger()
{
}

//=============================================================================
// デストラクタ関数
//=============================================================================
CManeger::~CManeger()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CManeger::Init(HINSTANCE hInstance, HWND hWnd, bool bWhindow)
{
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		m_pSound->InitSound(hWnd);
	}

	m_pRenderer = new CRenderer;
	if (m_pRenderer != NULL)
	{
		if (FAILED(m_pRenderer->Init(hWnd, bWhindow)))
		{
			return -1;
		}
	}

	m_pInputKeyboard = new CInputKeyboard;
	if (m_pInputKeyboard != NULL)
	{
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	m_pFade = CFade::Create();
	m_pPause = CPause::Create();

	//CManeger::SetMode(CManeger::MODE_TITLE);

	/*m_pScore = new CScore;
	if (m_pScore != NULL)
	{
		if (FAILED(m_pScore->Init()))
		{
			return E_FAIL;
		}
	}

	CBg::Load();
	CPlayer::Load();
	CEnemy::Load();
	CBullet::Load();
	CBarrier::Load();
	CExplosion::Load();
	CNumber::Load();
	CLife::Load();

	CBg::Create();
	CLife::Create();

	if (m_pPlayer == NULL)
	{
		m_pPlayer = CPlayer::Create();
	}

	m_apEnemy[0] = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2-200, 50.0f, 0.0f), CEnemy::ENEMY_TYPE001,150);
	m_apEnemy[1] = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), CEnemy::ENEMY_TYPE002,100);
	m_apEnemy[2] = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2+200, 50.0f, 0.0f), CEnemy::ENEMY_TYPE003,50);*/

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CManeger::Uninit(void)
{
	CScene::ReleaseAll();


	/*CBg::UnLoad();
	CPlayer::Unload();
	CEnemy::Unload();
	CBullet::Unload();
	CBarrier::Unload();
	CExplosion::Unload();
	CNumber::Unload();
	CLife::UnLoad();

	if (m_pScore != NULL)
	{
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = NULL;
	}*/

	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	if (m_pSound != NULL)
	{
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = NULL;
	}

	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}

	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = NULL;
	}
}

//更新
void CManeger::Update(void)
{
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}
	if (m_pPause->GetPause() == CPause::PAUSE_OFF)
	{
		if (m_pRenderer != NULL)
		{
			m_pRenderer->Update();
		}
	}
	else
	{
		if (m_pPause != NULL)
		{
			m_pPause->Update();
		}
	}
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}
}

//描画
void CManeger::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();// 描画処理
	}
}

void CManeger::SetMode(MODE mode)
{
	m_mode = mode;
	CScene::ReleaseAll();
	m_pTitle = NULL;
	m_pGame = NULL;
	m_pResult = NULL;

	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = CTitle::Create();
		break;
	case MODE_GAME:
		m_pGame = CGame::Create();
		break;
	case MODE_RESULT:
		m_pResult = CResult::Create();
		break;
	default:
		break;
	}
}