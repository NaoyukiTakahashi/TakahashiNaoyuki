//=============================================================================
//
// ライフ処理 [life.h]
// Author : 
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LIFE_TEX 3
#define MAX_LIFE_POLYGON 3
#define MAX_LIFE 5
#define MAX_ENERGY 10
#define LIFE_1 "TEX/life000.png"
#define ENERGY_1 "TEX/energy000.png"
#define GAUGE_1 "TEX/gauge000.png"
#define GAUGE_SIZE_WIDTH 100
#define GAUGE_SIZE_HIGHT 800.0f

//*****************************************************************************
// クラス
//*****************************************************************************
class CLife : public CScene
{
public:
	CLife(int nPriority = 2);
	~CLife();
	static HRESULT Load(void);
	static HRESULT UnLoad(void);
	static CLife *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type, int nPattern);
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); };
	D3DXVECTOR2 GetSize(void) { return D3DXVECTOR2(0.0f, 0.0f); };
	int GetLife(void) { return m_nLife; };
	void SubLife(int nLife);
	int GetEnergy(void) { return m_nEnegy; };
	void SubEnergy(int nEnergy);
	void SetState(STATE state) {};
	STATE GetState(void) { return STATE_NONE; };
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_LIFE_TEX]; //テクスチャ
	CScene2d *m_apScene2D[MAX_LIFE_POLYGON];
	static int m_nLife;
	static int m_nEnegy;
};

#endif