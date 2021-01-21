//=============================================================================
//
// エフェクト処理 [particle.h]
// Author : 
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PARTICLE_TEX 1
#define MAX_PARTICLE (128*10)	// エフェクトの最大数
#define MAX_PARTICLE_LIFE 100
#define PLAYER_HIT_TEST 5

//*****************************************************************************
// クラス
//*****************************************************************************
class CParticle : public CScene2d
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_NORMAL,
		TYPE_MAX
	}PARTICLE_TYPE;
	CParticle(int nPriority = 3);
	~CParticle();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fColAlphaValue, float fRadius, int fRadiusValue, int nLife, PARTICLE_TYPE particletype);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CParticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fColAlphaValue, float fRadius, int fRadiusValue, int nLife, PARTICLE_TYPE particletype);
	static HRESULT Load(void);
	static void Unload(void);
	D3DXVECTOR3 SetParticleMove(PARTICLE_TYPE particletype, D3DXVECTOR3 move);
	static int GetIndex(void) { return m_nIndex; };
	void SetState(STATE state) { ; };
	STATE GetState(void) { return STATE_NONE; };
private:
	D3DXVECTOR3 m_move; //移動量
	D3DXVECTOR3 m_pos;  //座標
	D3DXCOLOR m_col; //色
	float m_fRadius;			// 半径
	float m_fRadiusValue;		// 半径変化量
	float m_fColAlphaValue;	// 色変化量
	int m_nLife;//HP
	static int m_nIndex;
	PARTICLE_TYPE m_particletype;//種類
	static LPDIRECT3DTEXTURE9 m_apParticleTexture[MAX_PARTICLE_TEX];//テクスチャ
};

#endif