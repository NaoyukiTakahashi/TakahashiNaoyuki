//=============================================================================
//
// バレット処理 [bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BULLET_TEX 2
#define BULLET_SIZE_WIDTH 10.0f
#define BULLET_SIZE_HIGHT 10.0f
#define MAX_BULLET_LIFE 100
#define PLAYER_HIT_TEST 5

//*****************************************************************************
// クラス
//*****************************************************************************
class CBullet : public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_NORMAL,
		TYPE_TARGET,
		TYPE_HOMING,
		TYPE_WAVE,
		STATE_MAX
	}BULLET_TYPE;

	CBullet(int nPriority = 5);
	~CBullet();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type, D3DXCOLOR col, D3DXVECTOR3 size, int nLife, BULLET_TYPE bullettype);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type, D3DXCOLOR col, D3DXVECTOR3 size, int nLife, BULLET_TYPE bullettype);
	static HRESULT Load(void);
	static void Unload(void);
	void SetLife(int nLife) { m_nLife = nLife; };
	void SetState(STATE state) { m_state = state; };
	STATE GetState(void) { return m_state; };
private:
	D3DXVECTOR3 SetBulletMove(BULLET_TYPE bullettype, D3DXVECTOR3 move);
	D3DXVECTOR3 m_move; //移動量
	D3DXVECTOR3 m_pos;  //座標
	D3DXCOLOR m_col; //色
	TYPE m_type;//種類
	STATE m_state;
	D3DXVECTOR3 m_size;
	int m_nLife;//HP
	BULLET_TYPE m_bullettype;//種類
	static LPDIRECT3DTEXTURE9 m_apBulletTexture[MAX_BULLET_TEX];//テクスチャ
};

#endif