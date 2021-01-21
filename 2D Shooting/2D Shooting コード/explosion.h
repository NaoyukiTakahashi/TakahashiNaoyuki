//=============================================================================
//
// 爆発処理 [explosion.h]
// Author : 
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_EXPLOTION_ANIM 8
#define EXPLOTION_ANIM_SPEED 5
#define EXPLOTION_SIZE_WIDTH 50.0f
#define EXPLOTION_SIZE_HIGHT 50.0f

//*****************************************************************************
// クラス
//*****************************************************************************
class CExplosion : public CScene2d
{
public:
	CExplosion(int nPriority = 4);
	~CExplosion();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CExplosion *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	int GetLife(void) { return 0; };
	void SetState(STATE state) { m_state = state; };
	STATE GetState(void) { return m_state; };
private:
	D3DXVECTOR3 m_pos;  //座標
	int m_nCounterAnim;
	int m_nPatternAnim;
	STATE m_state;
	static LPDIRECT3DTEXTURE9 m_pExplosionTexture;//テクスチャ
};

#endif