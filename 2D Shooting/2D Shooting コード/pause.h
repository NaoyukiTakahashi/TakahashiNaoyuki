//=============================================================================
//
// ポーズ処理 [pause.h]
// Author : 
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_


//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include"main.h"
#include"manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PAUSE_TEX 3
#define MAX_PAUSE_POLYGON 3
#define PAUSE_1 "TEX/pause000.png"
#define PAUSE_2 "TEX/pause001.png"
#define PAUSE_3 "TEX/pause002.png"
#define PAUSE_1_SIZE_WIDTH 1920.0f
#define PAUSE_1_SIZE_HIGHT 1080.0f
#define PAUSE_2_SIZE_WIDTH 1920.0f
#define PAUSE_2_SIZE_HIGHT 1080.0f
#define PAUSE_3_SIZE_WIDTH 1920.0f
#define PAUSE_3_SIZE_HIGHT 1080.0f

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// クラス
//*****************************************************************************
class CPause
{
public:
	// フェードの状態
	typedef enum
	{
		PAUSE_OFF = 0,	// ポーズoff
		PAUSE_ON,		// ポーズon
	} PAUSE;
	CPause();
	~CPause();
	static CPause *Create(void);
	void SetPause(void) { m_pause = PAUSE_ON; };
	PAUSE GetPause(void) { return m_pause; };
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void Init(void);

	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_PAUSE_TEX]; //テクスチャ
	PAUSE m_pause;				// ポーズ状態
	D3DXCOLOR m_colorPause;		// ポーズ色
	CPolygon *m_apPolygon[MAX_PAUSE_POLYGON];
};

#endif