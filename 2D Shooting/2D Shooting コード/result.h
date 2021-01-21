//=============================================================================
//
// リザルト処理 [result.h]
// Author : 
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
// ファイルインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_RESULT_TEX 3
#define MAX_RESULT_POLYGON 3
#define RESULT_1 "TEX/result001.png"
#define RESULT_2 "TEX/result002.png"
#define RESULT_3 "TEX/result003.png"
#define RESULT_1_SIZE_WIDTH 1920.0f
#define RESULT_1_SIZE_HIGHT 1080.0f
#define RESULT_2_SIZE_WIDTH 1920.0f
#define RESULT_2_SIZE_HIGHT 1080.0f
#define RESULT_3_SIZE_WIDTH 1920.0f
#define RESULT_3_SIZE_HIGHT 1080.0f

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// クラス
//*****************************************************************************
class CResult :public CScene
{
public:
	CResult();
	~CResult();
	static CResult *Create(void);
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
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_RESULT_TEX]; //テクスチャ
	CPolygon *m_apPolygon[MAX_RESULT_POLYGON];
};
#endif