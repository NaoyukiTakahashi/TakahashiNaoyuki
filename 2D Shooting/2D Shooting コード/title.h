//=============================================================================
//
// タイトル処理 [title.h]
// Author : 
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// ファイルインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TITLE_TEX 3
#define MAX_TITLE_POLYGON 3
#define TITLE_1 "TEX/title000.png"
#define TITLE_2 "TEX/title001.png"
#define TITLE_3 "TEX/title002.png"
#define TITLE_1_SIZE_WIDTH 1920.0f
#define TITLE_1_SIZE_HIGHT 1080.0f
#define TITLE_2_SIZE_WIDTH 1920.0f
#define TITLE_2_SIZE_HIGHT 1080.0f
#define TITLE_3_SIZE_WIDTH 1920.0f
#define TITLE_3_SIZE_HIGHT 1080.0f

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// クラス
//*****************************************************************************
class CTitle :public CScene
{
public:
	CTitle(int nPriority = 1);
	~CTitle();
	static CTitle *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type, int nPattern) {};
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); };
	D3DXVECTOR2 GetSize(void) { return D3DXVECTOR2(0.0f, 0.0f); };
	void SetState(STATE state) {};
	STATE GetState(void) { return STATE_NONE; };
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TITLE_TEX]; //テクスチャ
	CPolygon *m_apPolygon[MAX_TITLE_POLYGON];
};
#endif