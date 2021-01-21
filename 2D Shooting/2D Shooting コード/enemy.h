//=============================================================================
//
// プレーヤー処理 [enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_ENEMY_TEX 3
#define ENEMY_SIZE_WIDTH 100.0f
#define ENEMY_SIZE_HIGHT 100.0f

//*****************************************************************************
// クラス
//*****************************************************************************
class CEnemy : public CScene2d
{
public:
	typedef enum
	{
		ENEMY_TYPE001 = 0,
		ENEMY_TYPE002,
		ENEMY_TYPE003,
		ENEMY_TYPE_MAXINUM
	}ENEMY_TYPE;

	CEnemy(int nPriority = 3);
	~CEnemy();
	HRESULT Init(D3DXVECTOR3 pos, ENEMY_TYPE enemy, int nRate);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy *Create(D3DXVECTOR3 pos, ENEMY_TYPE enemy, int nRate);
	static HRESULT Load(void);
	static void Unload(void);
	void SetState(STATE state) { m_state = state; };
	STATE GetState(void) { return m_state; };
private:
	D3DXVECTOR3 m_pos;  //座標
	int m_nCount;//射撃間隔
	int m_nRate;//射撃間隔
	STATE m_state;
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_ENEMY_POLYGON]; //テクスチャ
	static int m_nId;

};

#endif