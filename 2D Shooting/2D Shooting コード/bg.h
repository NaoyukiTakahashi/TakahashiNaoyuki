//=============================================================================
//
// プレーヤー処理 [bg.h]
// Author : 
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BG_TEX 3
#define MAX_BG_POLYGON 3
#define BG_1 "TEX/bg100.png"
#define BG_2 "TEX/bg101.png"
#define BG_3 "TEX/bg102.png"
#define BG_SIZE_WIDTH 1920.0f
#define BG_SIZE_HIGHT 1080.0f

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス
//*****************************************************************************
class CBg : public CScene
{
public:
	CBg(int nPriority = 9);
	~CBg();
	static HRESULT Load(void);
	static HRESULT UnLoad(void);
	static CBg *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type, int nPattern) {};
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(0.0f,0.0f,0.0f); };
	D3DXVECTOR2 GetSize(void) { return D3DXVECTOR2(0.0f, 0.0f); };
	void SetState(STATE state) {};
	STATE GetState(void) { return STATE_NONE; };
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG_TEX]; //テクスチャ
	CScene2d *m_apScene2D[MAX_BG_TEX];
};

#endif