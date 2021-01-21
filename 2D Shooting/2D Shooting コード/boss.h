//=============================================================================
//
// プレーヤー処理 [boss.h]
// Author : 
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BOSS_TEX 6
#define BOSS_SIZE_WIDTH 100.0f
#define BOSS_BODY000_SIZE_HIGHT 250.0f
#define BOSS_BODY001_SIZE_HIGHT 220.0f
#define BOSS_BODY002_SIZE_HIGHT 200.0f
#define BOSS_TYPE000_SIZE_HIGHT 100.0f
#define BOSS_TYPE001_SIZE_HIGHT 100.0f
#define BOSS_TYPE002_SIZE_HIGHT 100.0f
#define BOSS_TYPE000_LIFE 2
#define BOSS_TYPE001_LIFE 2
#define BOSS_TYPE002_LIFE 2
#define BOSS_SIZE_HIGHT - 70.0f

//*****************************************************************************
// クラス
//*****************************************************************************
class CBoss : public CScene2d
{
public:
	typedef enum
	{
		BOSS_BODY000 = 0,
		BOSS_BODY001,
		BOSS_BODY002,
		BOSS_TYPE000,
		BOSS_TYPE001,
		BOSS_TYPE002,
		BOSS_TYPE_MAXINUM
	}BOSS_TYPE;

	typedef enum
	{
		STAGE_NONE = 0,
		STAGE000,
		STAGE001,
		STAGE002,
		STAGE_MAXINUM
	}STAGE_TYPE;

	CBoss(int nPriority = 6);
	~CBoss();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, BOSS_TYPE boss, int nRate);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void StageNext(void);
	static CBoss *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, BOSS_TYPE boss, int nRate);
	static HRESULT Load(void);
	static void Unload(void);
	void SetState(STATE state);
	STATE GetState(void) { return m_state; };
private:
	D3DXVECTOR3 m_pos;  //座標
	D3DXVECTOR3 m_move; //移動
	D3DXVECTOR3 m_size;
	D3DXCOLOR m_col;
	STATE m_state;
	static bool m_bUse;
	int m_nRate;//射撃間隔
	BOSS_TYPE m_bossType;
	int m_nLife;
	int m_nTypeIndex;
	int m_nTypeIndex2;
	static STAGE_TYPE m_stageType;
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BOSS_TEX]; //テクスチャ
	static int m_nId;
};

#endif