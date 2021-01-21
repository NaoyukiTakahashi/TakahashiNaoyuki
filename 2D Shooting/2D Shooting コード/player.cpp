#define _CRT_SECURE_NO_WARNINGS

//インクルードファイル
#include "player.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "renderer.h"
#include "sound.h"
#include "score.h"
#include "barrier.h"
#include "fade.h"
#include "game.h"  
#include "life.h"
#include "particle.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pPlayerTexture = NULL;

//=============================================================================
// コンストラクタ関数
//=============================================================================
CPlayer::CPlayer(int nPriority)
{
}

//=============================================================================
// デストラクタ関数
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CPlayer::Init(void)
{
	BindTexture(m_pPlayerTexture);

	CScene2d::Init();

	m_state = STATE_NORMAL;

	SetPolygon(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_WIDTH-100.0f, 0.0f) , D3DXVECTOR3(PLAYER_SIZE_WIDTH, PLAYER_SIZE_HIGHT, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), TYPE_PLAYER, NULL);

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2d::Uninit();
}

//更新
void CPlayer::Update(void)
{

	PLAY_MODE mode = CPlayer::PLAY;

	static int nInputStoring[MAX_STORING_FRAME][MAX_CONCURRENT_ENTRY_KEY] = { NULL };
	int nConcurrentEntryKeyCount = 0;
	static int nFrameCount = 0;
	static int nCountState = 0;
	static int nCountBrrier = 0;
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 size = D3DXVECTOR3(PLAYER_SIZE_WIDTH, PLAYER_SIZE_HIGHT, 0);
	D3DXCOLOR col;
	static D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//キー取得
	CInputKeyboard *pKey;
	pKey = CManeger::GetInputKeyboard();

	if (mode == CPlayer::PLAY)
	{

		if (pKey->GetKeyTrigger(DIK_BACK))
		{
			m_state = STATE_DETH;
		}

		if (m_state != STATE_DETH)
		{

			if (m_state == STATE_NORMAL)
			{
				col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				if (nCountBrrier <= 0)
				{
					col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
					nCountBrrier = 0;
					if (pKey->GetKeyPress(DIK_SPACE))
					{
						for (int nCount = 0; nCount < 10; nCount++)
						{
							CParticle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.8f), 0.01f, 20, 1, 20, CParticle::TYPE_NORMAL);
						}
						nInputStoring[nFrameCount][nConcurrentEntryKeyCount] = DIK_SPACE;
						nConcurrentEntryKeyCount++;
						CManeger::GetSound()->Play(CSound::SOUND_LABEL_SE_SHOT);
						CBarrier::Create(pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), TYPE_BULLET_P, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150);
						nCountBrrier = 150;
					}
				}
				if (pKey->GetKeyPress(DIK_P))
				{
					CGame::GetLife()->SubLife(10);
				}
				if (pKey->GetKeyTrigger(DIK_V) && CGame::GetLife()->GetEnergy() >= 10)
				{
					nInputStoring[nFrameCount][nConcurrentEntryKeyCount] = DIK_V;
					nConcurrentEntryKeyCount++;
					CGame::GetLife()->SubEnergy(-1);
					CManeger::GetSound()->Play(CSound::SOUND_LABEL_SE_SHOT);
					CBullet::Create(pos, D3DXVECTOR3(0.0f, -20.0f, 0.0f), TYPE_BULLET_P, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(500.0f, 100.0f, 0.0f), 100, CBullet::BULLET_TYPE::TYPE_WAVE);
				}
				else if (pKey->GetKeyTrigger(DIK_V) && CGame::GetLife()->GetEnergy() > 0)
				{
					nInputStoring[nFrameCount][nConcurrentEntryKeyCount] = DIK_V;
					nConcurrentEntryKeyCount++;
					CGame::GetLife()->SubEnergy(-1);
					CManeger::GetSound()->Play(CSound::SOUND_LABEL_SE_SHOT);
					CBullet::Create(pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), TYPE_BULLET_P, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), D3DXVECTOR3(50.0f,50.0f,0.0f), MAX_BULLET_LIFE, CBullet::BULLET_TYPE::TYPE_NORMAL);
				}
				nCountBrrier--;
			}
			else
			{
				col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);
				nCountState++;
			}

			if (nCountState >= 50)
			{
				nCountState = 0;
				m_state = STATE_NORMAL;
			}

			if (pKey->GetKeyPress(DIK_A))
			{
				nInputStoring[nFrameCount][nConcurrentEntryKeyCount] = DIK_A;
				nConcurrentEntryKeyCount++;
				if (pKey->GetKeyPress(DIK_W))
				{
					nInputStoring[nFrameCount][nConcurrentEntryKeyCount] = DIK_W;
					nConcurrentEntryKeyCount++;
					move.x -= PLAYER_MOVE*cos(45);
					move.y -= PLAYER_MOVE*sin(45);

				}
				else if (pKey->GetKeyPress(DIK_S))
				{
					nInputStoring[nFrameCount][nConcurrentEntryKeyCount] = DIK_S;
					nConcurrentEntryKeyCount++;
					move.x -= PLAYER_MOVE*cos(45);
					move.y += PLAYER_MOVE*sin(45);
				}
				else
				{
					move.x -= PLAYER_MOVE;
				}
			}
			else if (pKey->GetKeyPress(DIK_D))
			{
				nInputStoring[nFrameCount][nConcurrentEntryKeyCount] = DIK_D;
				nConcurrentEntryKeyCount++;
				if (pKey->GetKeyPress(DIK_W))
				{
					nInputStoring[nFrameCount][nConcurrentEntryKeyCount] = DIK_W;
					nConcurrentEntryKeyCount++;
					move.x += PLAYER_MOVE*cos(45);
					move.y -= PLAYER_MOVE*sin(45);

				}
				else if (pKey->GetKeyPress(DIK_S))
				{
					nInputStoring[nFrameCount][nConcurrentEntryKeyCount] = DIK_S;
					nConcurrentEntryKeyCount++;
					move.x += PLAYER_MOVE*cos(45);
					move.y += PLAYER_MOVE*sin(45);
				}
				else
				{
					move.x += PLAYER_MOVE;
				}
			}
			else if (pKey->GetKeyPress(DIK_W))
			{
				nInputStoring[nFrameCount][nConcurrentEntryKeyCount] = DIK_W;
				nConcurrentEntryKeyCount++;
				move.y -= PLAYER_MOVE;
			}
			else if (pKey->GetKeyPress(DIK_S))
			{
				nInputStoring[nFrameCount][nConcurrentEntryKeyCount] = DIK_S;
				nConcurrentEntryKeyCount++;
				move.y += PLAYER_MOVE;
			}

			if (pos.x <= 0 + size.x / 4)
			{
				pos.x = SCREEN_WIDTH - 1 - size.x / 4;
			}
			else if (pos.x >= SCREEN_WIDTH - size.x / 4)
			{
				pos.x = 0 + 1 + size.x / 4;
			}
			else if (pos.y <= 0 + size.y / 4)
			{
				pos.y = 0 + size.y / 4;
			}
			else if (pos.y >= SCREEN_HIGHT - size.y / 4)
			{
				pos.y = SCREEN_HIGHT - size.y / 4;
			}
			else
			{

			}

			move += (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - move) * RATE_MOVE;

			pos = pos + move;

			//位置更新
			SetPolygon(pos, size, col, TYPE_PLAYER, NULL);
		}
		else
		{
			CManeger::GetFade()->SetFade(CManeger::MODE_RESULT);
			//CManeger::SetMode(CManeger::MODE_RESULT);
			return;
		}

		nFrameCount++;

		if (nFrameCount >= MAX_STORING_FRAME)
		{
			PlayerActivitySave(nInputStoring);
			nFrameCount = 0;
		}
	}
	else
	{
		UpdateRePlay();
	}

	CScene2d::Update();
}

void CPlayer::UpdateRePlay(void)
{
	static int nLoadStoring[MAX_STORING_FRAME][MAX_CONCURRENT_ENTRY_KEY] = { NULL };
	static int nFrameCount = 0;
	int nConcurrentEntryKeyCount = 0;
	static int nCountState = 0;
	static int nCountBrrier = 0;
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 size = D3DXVECTOR3(PLAYER_SIZE_WIDTH, PLAYER_SIZE_HIGHT, 0);
	D3DXCOLOR col;
	static D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (0 == nFrameCount%120)
	{
		FileLoad(nLoadStoring);
	}

	if (nLoadStoring[nFrameCount][nConcurrentEntryKeyCount] == DIK_BACK)
	{
		m_state = STATE_DETH;
		nConcurrentEntryKeyCount++;
	}

	if (m_state != STATE_DETH)
	{

		if (m_state == STATE_NORMAL)
		{
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			if (nCountBrrier <= 0)
			{
				col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				nCountBrrier = 0;
				if (nLoadStoring[nFrameCount][nConcurrentEntryKeyCount] == DIK_SPACE)
				{
					nConcurrentEntryKeyCount++;
					CManeger::GetSound()->Play(CSound::SOUND_LABEL_SE_SHOT);
					CBarrier::Create(pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), TYPE_BULLET_P, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150);
					nCountBrrier = 150;
				}
			}
			if (nLoadStoring[nFrameCount][nConcurrentEntryKeyCount] == DIK_V && CGame::GetLife()->GetEnergy() > 0)
			{
				nConcurrentEntryKeyCount++;
				CGame::GetLife()->SubEnergy(-1);
				CManeger::GetSound()->Play(CSound::SOUND_LABEL_SE_SHOT);
				CBullet::Create(pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), TYPE_BULLET_P, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), MAX_BULLET_LIFE, CBullet::BULLET_TYPE::TYPE_NORMAL);
			}
			nCountBrrier--;
		}
		else
		{
			col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);
			nCountState++;
		}

		if (nCountState >= 50)
		{
			nCountState = 0;
			m_state = STATE_NORMAL;
		}

		if (nLoadStoring[nFrameCount][nConcurrentEntryKeyCount] == DIK_A)
		{
			nConcurrentEntryKeyCount++;
			if (nLoadStoring[nFrameCount][nConcurrentEntryKeyCount] == DIK_W)
			{
				nConcurrentEntryKeyCount++;
				move.x -= PLAYER_MOVE*cos(45);
				move.y -= PLAYER_MOVE*sin(45);

			}
			else if (nLoadStoring[nFrameCount][nConcurrentEntryKeyCount] == DIK_S)
			{
				nConcurrentEntryKeyCount++;
				move.x -= PLAYER_MOVE*cos(45);
				move.y += PLAYER_MOVE*sin(45);
			}
			else
			{
				move.x -= PLAYER_MOVE;
			}
		}
		else if (nLoadStoring[nFrameCount][nConcurrentEntryKeyCount] == DIK_D)
		{
			nConcurrentEntryKeyCount++;
			if (nLoadStoring[nFrameCount][nConcurrentEntryKeyCount] == DIK_W)
			{
				nConcurrentEntryKeyCount++;
				move.x += PLAYER_MOVE*cos(45);
				move.y -= PLAYER_MOVE*sin(45);

			}
			else if (nLoadStoring[nFrameCount][nConcurrentEntryKeyCount] == DIK_S)
			{
				nConcurrentEntryKeyCount++;
				move.x += PLAYER_MOVE*cos(45);
				move.y += PLAYER_MOVE*sin(45);
			}
			else
			{
				move.x += PLAYER_MOVE;
			}
		}
		else if (nLoadStoring[nFrameCount][nConcurrentEntryKeyCount] == DIK_W)
		{
			nConcurrentEntryKeyCount++;
			move.y -= PLAYER_MOVE;
		}
		else if (nLoadStoring[nFrameCount][nConcurrentEntryKeyCount] == DIK_S)
		{
			nConcurrentEntryKeyCount++;
			move.y += PLAYER_MOVE;
		}

		if (pos.x <= 0 + size.x / 4)
		{
			pos.x = SCREEN_WIDTH - 1 - size.x / 4;
		}
		else if (pos.x >= SCREEN_WIDTH - size.x / 4)
		{
			pos.x = 0 + 1 + size.x / 4;
		}
		else if (pos.y <= 0 + size.y / 4)
		{
			pos.y = 0 + size.y / 4;
		}
		else if (pos.y >= SCREEN_HIGHT - size.y / 4)
		{
			pos.y = SCREEN_HIGHT - size.y / 4;
		}
		else
		{

		}

		move += (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - move) * RATE_MOVE;

		pos = pos + move;

		//位置更新
		SetPolygon(pos, size, col, TYPE_PLAYER, NULL);
	}
	else
	{
		CManeger::GetFade()->SetFade(CManeger::MODE_RESULT);
		return;
	}

	nFrameCount++;

	if (nFrameCount >= MAX_STORING_FRAME)
	{
		FileLoad(nLoadStoring);
		nFrameCount = 0;
	}
}

//描画
void CPlayer::Draw(void)
{
	CScene2d::Draw();
}

//生成
CPlayer * CPlayer::Create(void)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;
	pPlayer->Init();
	pPlayer->SetType(TYPE_PLAYER);
	return pPlayer;
}

//画像ロード
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "TEX/player000.png", &m_pPlayerTexture);

	return S_OK;
}

//画像破棄
void CPlayer::Unload(void)
{
	// テクスチャの破棄
	if (m_pPlayerTexture != NULL)
	{
		m_pPlayerTexture->Release();
		m_pPlayerTexture = NULL;
	}
}

void CPlayer::PlayerActivitySave(int nNumSave[MAX_STORING_FRAME][MAX_CONCURRENT_ENTRY_KEY])
{
	static int nFrame = 0;
	char cfileName[64];
	sprintf(cfileName, "PlayerActivity/%d.txt", nFrame);

	//ファイルを開く
	FILE *pFile = fopen(cfileName, "w");

	if (pFile != NULL)//ファイルが開けたとき
	{
		for (int nCountFrame = 0; nCountFrame < MAX_STORING_FRAME; nCountFrame++)
		{
			fprintf(pFile, "-1,\n");
			fprintf(pFile, "%d,\n", MAX_STORING_FRAME * nFrame + nCountFrame + 1);

			for (int nCountEntryKey = 0; nCountEntryKey < MAX_CONCURRENT_ENTRY_KEY; nCountEntryKey++)
			{
				if (nNumSave[nCountFrame][nCountEntryKey] != 0)
				{
					fprintf(pFile, "-2,\n");
					fprintf(pFile, "%d,\n", nNumSave[nCountFrame][nCountEntryKey]);
				}
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else//ファイルが開けなかったとき
	{
	}
	nFrame++;
}

/*データロード関数*/
void CPlayer::FileLoad(int pnNumLoad[MAX_STORING_FRAME][MAX_CONCURRENT_ENTRY_KEY])
{
	static int nFrame = 0;
	int nCountEntryKey = 0;
	int nDiscriminant = 0;
	char cfileName[64];
	sprintf(cfileName, "PlayerActivity/%d.txt", nFrame);

	//ファイルを開く
	FILE *pFile = fopen(cfileName, "r");

	if (pFile != NULL)//ファイルが開けたとき
	{
		//フレーム数分
		for (int nCountFrame = 0; nCountFrame < MAX_STORING_FRAME; nCountFrame)
		{
			if (fscanf(pFile, "%d%[^,]", &nDiscriminant) < 1)//要素数が足りない場合
			{
				if (nDiscriminant == -1)
				{
					if (fscanf(pFile, "%d", &pnNumLoad[MAX_STORING_FRAME]) < 1)//要素数が足りない場合
					{
						nCountFrame++;
						nCountEntryKey = 0;
					}
				}
				else
				{
					if (fscanf(pFile, "%d", &pnNumLoad[MAX_STORING_FRAME][nCountEntryKey]) < 1)//要素数が足りない場合
					{
						nCountEntryKey++;
					}
				}
			}

		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else//ファイルが開けなかったとき
	{
	}
	nFrame++;
}