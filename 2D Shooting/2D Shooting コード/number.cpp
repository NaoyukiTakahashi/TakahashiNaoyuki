//=============================================================================
//
// ナンバー処理 [number.cpp]
// Author : 
//
//=============================================================================

//*****************************************************************************
// ファイルインクルード
//*****************************************************************************
#include "number.h"
#include "manager.h"
#include "renderer.h"

// マクロ定義
#define	SCORE_POS_X			(SCREEN_WIDTH - (35.0f * 8))	// スコアの表示基準位置(Ｘ座標)
#define	SCORE_POS_Y			(20.0f)							// スコアの表示基準位置(Ｙ座標)
#define	SCORE_WIDTH			(35.0f)							// スコアの数字の幅
#define	SCORE_HEIGHT		(70.0f)							// スコアの数字の高さ
#define	SCORE_INTERVAL_X	(35.0f - 3.0f)					// スコアの数字の表示間隔

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

CNumber::CNumber()
{
	m_pVtxBuff = NULL;
}

CNumber::~CNumber()
{
}

void CNumber::SetNumber(int nNumber)
{
	VERTEX_2D*pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + nNumber / 10.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + nNumber / 10.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + nNumber / 10.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + nNumber / 10.0f, 1.0f);

	m_pVtxBuff->Unlock();
}

HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	VERTEX_2D*pVtx;

	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// 頂点情報を設定
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y - size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x / 2, pos.y + size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x / 2, pos.y + size.y / 2, 0.0f);

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	m_pVtxBuff->Unlock();

	//SetNumber(0);
	//Draw();

	return S_OK;
}

void CNumber::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

void CNumber::Update(void)
{
}

void CNumber::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

CNumber * CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CNumber *pNumber;
	pNumber = new CNumber;
	pNumber->Init(pos, size);
	return pNumber;
}

HRESULT CNumber::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "TEX/number000.png", &m_pTexture);

	return S_OK;
}

void CNumber::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}