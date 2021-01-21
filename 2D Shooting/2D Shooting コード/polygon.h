//=============================================================================
//
// ポリゴン処理 [polygon.h]
// Author : 
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス
//*****************************************************************************
class CPolygon
{
public:
	CPolygon();
	~CPolygon();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	static CPolygon *Create();
private:
	LPDIRECT3DTEXTURE9		m_pTexture; //テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //バッファ
	D3DXVECTOR3 m_pos; //座標
	D3DXVECTOR3 m_size;       //サイズ
	D3DXCOLOR m_col;
};

#endif