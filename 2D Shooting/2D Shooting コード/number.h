//=============================================================================
//
// ナンバー処理 [number.h]
// Author : 
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス
//*****************************************************************************
class CNumber
{
public:
	CNumber();
	~CNumber();
	void SetNumber(int nNumber);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//テクスチャ
};

#endif