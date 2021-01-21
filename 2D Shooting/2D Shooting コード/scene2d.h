//=============================================================================
//
// シーン2D処理 [scene2d.h]
// Author : 
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス
//*****************************************************************************
class CScene2d : public CScene
{
public:
	CScene2d(int nPriority = 3);
	~CScene2d();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type, int nPattern);
	D3DXVECTOR3 GetPosition(void) { return m_pos; };
	D3DXVECTOR2 GetSize(void) { return m_size; };
	static CScene2d *Create(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	virtual void SetState(STATE state) {};
	virtual STATE GetState(void) { return STATE_NONE; };
private:
	LPDIRECT3DTEXTURE9		m_pTexture; //テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //バッファ
	D3DXVECTOR3 m_pos;            //中心座標
	D3DXVECTOR3 m_posUpperLeft[MAX_POLYGON];   //座標0
	D3DXVECTOR3 m_posUpperRight[MAX_POLYGON];  //座標1
	D3DXVECTOR3 m_posBottomLeft[MAX_POLYGON];  //座標2
	D3DXVECTOR3 m_posBottomRight[MAX_POLYGON]; //座標3
	D3DXVECTOR2 m_uvUpperLeft;    //uv座標0
	D3DXVECTOR2 m_uvUpperRight;   //uv座標1
	D3DXVECTOR2 m_uvBottomLeft;   //uv座標2
	D3DXVECTOR2 m_uvBottomRight;  //uv座標3
	D3DXCOLOR m_col;   //色
	TYPE m_type;       //タイプ
	int m_nPattern;    //パターン
	float m_fRadius;   //半径
	float m_fAngle;    //角度
	float m_fRot;      //角度加算
	float m_fLength;   //半径加算
	int m_nIndex;    //パターン
	D3DXVECTOR3 m_size;//サイズ
	CScene2d *m_pScene2D;
};

#endif