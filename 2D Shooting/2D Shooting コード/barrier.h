//=============================================================================
//
// バリア処理 [barrier.h]
// Author : 
//
//=============================================================================
#ifndef _BARRIER_H_
#define _BARRIER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BARRIER_SIZE_WIDTH 10.0f
#define BARRIER_SIZE_HIGHT 10.0f
#define MAX_BULLET_LIFE 50
#define HITTEST 75

//*****************************************************************************
// クラス
//*****************************************************************************
class CBarrier : public CScene2d
{
public:
	CBarrier(int nPriority = 3);
	~CBarrier();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type, D3DXCOLOR col, int nSize);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBarrier *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type, D3DXCOLOR col, int nSize);
	static HRESULT Load(void);
	static void Unload(void);
	void SetState(STATE state) { m_state = state; };
	STATE GetState(void) { return m_state; };
private:
	D3DXVECTOR3 m_move; //移動量
	D3DXVECTOR3 m_pos;  //座標
	D3DXCOLOR m_col; //色
	TYPE m_type;//種類
	STATE m_state;
	int m_nSize;
	static LPDIRECT3DTEXTURE9 m_pBarrierTexture;//テクスチャ
};

#endif