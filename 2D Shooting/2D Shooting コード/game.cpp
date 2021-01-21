//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : 
//
//=============================================================================

//*****************************************************************************
// ファイルインクルード
//*****************************************************************************
#include "game.h"
#include "bullet.h"
#include "bg.h"
#include "enemy.h"
#include "number.h"
#include "score.h"
#include "life.h"
#include "barrier.h"
#include "player.h"
#include "explosion.h"
#include "player.h"
#include "pause.h"
#include "input.h"
#include "effect.h"
#include "boss.h"
#include "sound.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CPlayer *CGame::m_pPlayer = NULL;
CEnemy *CGame::m_apEnemy[];//エネミー情報保持
CBoss *CGame::m_apBoss[];//ボスエネミー情報保持
CScore *CGame::m_pScore = NULL;
CLife *CGame::m_pLife = NULL;
CBg *CGame::m_pBg = NULL;
CGame::MODE_TYPE CGame::m_mode = CGame::MODE_NONE;
CBoss *CGame::m_pBossLife = NULL;

CGame::CGame()
{
	memset(m_apEnemy, 0, sizeof(m_apEnemy));
	memset(m_apBoss, 0, sizeof(m_apBoss));
}

CGame::~CGame()
{
}

CGame * CGame::Create(void)
{
	CGame *pGame;
	pGame = new CGame;
	pGame->Init();
	return pGame;
}

HRESULT CGame::Init(void)
{
	CManeger::GetSound()->Play(CSound::SOUND_LABEL_BGM_000);
	CBg::Load();
	CPlayer::Load();
	CEnemy::Load();
	CBoss::Load();
	CBullet::Load();
	CBarrier::Load();
	CExplosion::Load();
	CNumber::Load();
	CLife::Load();
	CEffect::Load();

	m_pPlayer = CPlayer::Create();

	m_pScore = CScore::Create();

	m_pLife = CLife::Create();

	m_pBg = CBg::Create();

	SetMode(MODE_ENEMY);

	return S_OK;
}

void CGame::Uninit(void)
{
	CManeger::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_000);
	CBg::UnLoad();
	CPlayer::Unload();
	CEnemy::Unload();
	CBoss::Unload();
	CBullet::Unload();
	CBarrier::Unload();
	CExplosion::Unload();
	CNumber::Unload();
	CLife::UnLoad();
	CEffect::Unload();

	Release();
}

void CGame::Update(void)
{
	//キー取得
	if (CManeger::GetInputKeyboard()->GetKeyTrigger(DIK_TAB))
	{
		CManeger::GetPause()->SetPause();
	}
}

void CGame::Draw(void)
{
}

void CGame::SetMode(MODE_TYPE mode)
{
	m_mode = mode;

	switch (mode)
	{
	case MODE_NONE:
		break;
	case MODE_TUTORIAL:
		break;
	case MODE_ENEMY:
		m_apEnemy[0] = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 400, 50.0f, 0.0f), CEnemy::ENEMY_TYPE001, 150);
		m_apEnemy[1] = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), CEnemy::ENEMY_TYPE002, 100);
		m_apEnemy[2] = CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 400, 50.0f, 0.0f), CEnemy::ENEMY_TYPE003, 50);
		break;
	case MODE_BOSS:
		m_apBoss[0] = CBoss::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -BOSS_BODY000_SIZE_HIGHT / 2 - BOSS_BODY001_SIZE_HIGHT / 2 - BOSS_BODY002_SIZE_HIGHT, 0.0f), D3DXVECTOR3(300.0f, 250.0f, 0.0f), CBoss::BOSS_BODY002, 150);
		m_apBoss[1] = CBoss::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -BOSS_BODY001_SIZE_HIGHT / 2 - BOSS_BODY002_SIZE_HIGHT + 45, 0.0f), D3DXVECTOR3(250.0f, 220.0f, 0.0f), CBoss::BOSS_BODY001, 150);
		m_apBoss[2] = CBoss::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -BOSS_BODY002_SIZE_HIGHT / 2, 0.0f), D3DXVECTOR3(200.0f, 200.0f, 0.0f), CBoss::BOSS_BODY000, 150);
		m_apBoss[3] = CBoss::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -BOSS_BODY002_SIZE_HIGHT / 2, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), CBoss::BOSS_TYPE001, 150);
		m_apBoss[4] = CBoss::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 50, -BOSS_BODY001_SIZE_HIGHT / 2 - BOSS_BODY002_SIZE_HIGHT + 45, 0.0f), D3DXVECTOR3(75.0f, 75.0f, 0.0f), CBoss::BOSS_TYPE002, 150);
		m_apBoss[5] = CBoss::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 50, -BOSS_BODY001_SIZE_HIGHT / 2 - BOSS_BODY002_SIZE_HIGHT + 45, 0.0f), D3DXVECTOR3(75.0f, 75.0f, 0.0f), CBoss::BOSS_TYPE002, 150);
		m_apBoss[6] = CBoss::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100, -BOSS_BODY000_SIZE_HIGHT / 2 - BOSS_BODY001_SIZE_HIGHT / 2 - BOSS_BODY002_SIZE_HIGHT, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CBoss::BOSS_TYPE001, 150);
		m_apBoss[7] = CBoss::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -BOSS_BODY000_SIZE_HIGHT / 2 - BOSS_BODY001_SIZE_HIGHT / 2 - BOSS_BODY002_SIZE_HIGHT, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CBoss::BOSS_TYPE000, 150);
		m_apBoss[8] = CBoss::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 100, -BOSS_BODY000_SIZE_HIGHT / 2 - BOSS_BODY001_SIZE_HIGHT / 2 - BOSS_BODY002_SIZE_HIGHT, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CBoss::BOSS_TYPE001, 150);
		break;
	case MODE_MAXINUM:
		break;
	default:
		break;
	}
}