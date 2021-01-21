//=============================================================================
//
// 処理 [scene2d.cpp]
// Author : 
//
//=============================================================================

//*****************************************************************************
// ファイルインクルード
//*****************************************************************************
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "effect.h"
#include "particle.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************

//=============================================================================
// コンストラクタ関数
//=============================================================================
CScene2d::CScene2d(int nPriority):CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRadius = 0.0f;
	m_fAngle = 0.0f;
	m_fRot = 0.0f;
	m_fLength = 0.0f;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIndex = 0;
	//m_posUpperLeft[MAX_EFFECT] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f) };
	//m_posUpperRight[MAX_EFFECT] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f) };
	//m_posBottomLeft[MAX_EFFECT] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f) };
	//m_posBottomRight[MAX_EFFECT] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f) };
}

//=============================================================================
// デストラクタ関数
//=============================================================================
CScene2d::~CScene2d()
{

}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CScene2d::Init(void)
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

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了関数
//=============================================================================
void CScene2d::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

void CScene2d::Update(void)
{
	VERTEX_2D*pVtx;
	static int nCount = 0;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

#ifdef POLYGONTEST
	if (m_type == TYPE_EFFECT)
	{
		int nIndex = CEffect::GetIndex();
		static int n = 0;

		if (m_nIndex <= nIndex)
		{
			m_nIndex = nIndex;
		}
		else
		{
			if (nIndex == 1)
			{
				n -= 4;
				m_nIndex = nIndex;
			}
			else if (nIndex <= 0)
			{
				m_nIndex = nIndex;
			}
			else
			{
				n -= 6;
			}
		}
		int nCount = 0;

		if (nIndex == 1)
		{
			pVtx[n].pos = m_posUpperLeft[nIndex - 1];
			pVtx[n + 1].pos = m_posUpperRight[nIndex - 1];
			pVtx[n + 2].pos = m_posBottomLeft[nIndex - 1];
			pVtx[n + 3].pos = m_posBottomRight[nIndex - 1];

			pVtx[n].tex = m_uvUpperLeft;
			pVtx[n + 1].tex = m_uvUpperRight;
			pVtx[n + 2].tex = m_uvBottomLeft;
			pVtx[n + 3].tex = m_uvBottomRight;

			pVtx[n].col = m_col;
			pVtx[n + 1].col = m_col;
			pVtx[n + 2].col = m_col;
			pVtx[n + 3].col = m_col;

			n += 4;
		}
		else
		{
			pVtx[n].pos = m_posBottomRight[nIndex - 1];
			pVtx[n + 1].pos = m_posUpperLeft[nIndex];
			pVtx[n + 2].pos = m_posUpperLeft[nIndex];
			pVtx[n + 3].pos = m_posUpperRight[nIndex];
			pVtx[n + 4].pos = m_posBottomLeft[nIndex];
			pVtx[n + 5].pos = m_posBottomRight[nIndex];

			n += 6;

			/*pVtx[0].tex = m_uvUpperLeft;
			pVtx[1].tex = m_uvUpperRight;
			pVtx[2].tex = m_uvBottomLeft;
			pVtx[3].tex = m_uvBottomRight;

			pVtx[0].col = m_col;
			pVtx[1].col = m_col;
			pVtx[2].col = m_col;
			pVtx[3].col = m_col;*/
		}
	}
	else
	{
		pVtx[0].pos = m_posUpperLeft[0];
		pVtx[1].pos = m_posUpperRight[0];
		pVtx[2].pos = m_posBottomLeft[0];
		pVtx[3].pos = m_posBottomRight[0];

		pVtx[0].tex = m_uvUpperLeft;
		pVtx[1].tex = m_uvUpperRight;
		pVtx[2].tex = m_uvBottomLeft;
		pVtx[3].tex = m_uvBottomRight;

		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;
	}
#endif // POLYGONTEST

	/*if (m_type = TYPE_PARTICLE)
	{
		int nIndex = CParticle::GetIndex();

		m_posUpperLeft[nIndex - 1] = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y, 0.0f);
		m_posUpperRight[nIndex - 1] = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y, 0.0f);
		m_posBottomLeft[nIndex - 1] = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y, 0.0f);
		m_posBottomRight[nIndex - 1] = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y, 0.0f);
	}*/

	pVtx[0].pos = m_posUpperLeft[0];
	pVtx[1].pos = m_posUpperRight[0];
	pVtx[2].pos = m_posBottomLeft[0];
	pVtx[3].pos = m_posBottomRight[0];

	pVtx[0].tex = m_uvUpperLeft;
	pVtx[1].tex = m_uvUpperRight;
	pVtx[2].tex = m_uvBottomLeft;
	pVtx[3].tex = m_uvBottomRight;

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	m_pVtxBuff->Unlock();
}

void CScene2d::Draw(void)
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

void CScene2d::SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type, int nPattern)
{
	m_pos = pos;
	m_size = size;
	m_col = col;
	m_type = type;

	m_posUpperLeft[0] = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	m_posUpperRight[0] = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	m_posBottomLeft[0] = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);
	m_posBottomRight[0] = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);

	m_uvUpperLeft = D3DXVECTOR2(0.0f, 0.0f);
	m_uvUpperRight = D3DXVECTOR2(1.0f, 0.0f);
	m_uvBottomLeft = D3DXVECTOR2(0.0f, 1.0f);
	m_uvBottomRight = D3DXVECTOR2(1.0f, 1.0f);

	/*if (m_type = TYPE_PARTICLE)
	{
		int nIndex = CEffect::GetIndex();

		m_posUpperLeft[nIndex - 1] = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y, 0.0f);
		m_posUpperRight[nIndex - 1] = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y, 0.0f);
		m_posBottomLeft[nIndex - 1] = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y, 0.0f);
		m_posBottomRight[nIndex - 1] = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y, 0.0f);
	}
	else*/ if (m_type == TYPE_EFFECT)
	{

#ifdef POLYGONTEST
		int nIndex = CEffect::GetIndex();

		m_posUpperLeft[nIndex - 1] = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y, 0.0f);
		m_posUpperRight[nIndex - 1] = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y, 0.0f);
		m_posBottomLeft[nIndex - 1] = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y, 0.0f);
		m_posBottomRight[nIndex - 1] = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y, 0.0f);

		/*m_nIndex++;*/
#endif // POLYGONTEST
	}
	else if (m_type == TYPE_EXPLOSION)
	{
		m_uvUpperLeft = D3DXVECTOR2(nPattern*0.125, 0.0f);

		m_uvUpperRight = D3DXVECTOR2(nPattern*0.125 + 0.125, 0.0f);

		m_uvBottomLeft = D3DXVECTOR2(nPattern*0.125, 1.0f);

		m_uvBottomRight = D3DXVECTOR2(nPattern*0.125 + 0.125, 1.0f);
	}
	else if (m_type == TYPE_LIFE)
	{
		static float nLifeSize = (float)size.x;

		m_posUpperLeft[0] = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y, 0.0f);
		m_posUpperRight[0] = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y, 0.0f);
		m_posBottomLeft[0] = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y, 0.0f);
		m_posBottomRight[0] = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y, 0.0f);

		if (nPattern == 1)
		{
			m_uvUpperLeft = D3DXVECTOR2(0.0f, 0.0f);
			m_uvUpperRight = D3DXVECTOR2(((float)size.x / (nLifeSize / 100.0f)) / 100.0f, 0.0f);
			m_uvBottomLeft = D3DXVECTOR2(0.0f, 1.0f);
			m_uvBottomRight = D3DXVECTOR2(((float)size.x / (nLifeSize / 100.0f)) / 100.0f, 1.0f);
		}
		else
		{
			m_uvUpperLeft = D3DXVECTOR2(0.0f, 0.0f);
			m_uvUpperRight = D3DXVECTOR2(1.0f, 0.0f);
			m_uvBottomLeft = D3DXVECTOR2(0.0f, 1.0f);
			m_uvBottomRight = D3DXVECTOR2(1.0f, 1.0f);
		}
	}
	else
	{

	}
}

CScene2d *CScene2d::Create(void)
{
	CScene2d *pScene;
	pScene = new CScene2d;
	pScene->Init();
	pScene->SetType(TYPE_SCENE2D);
	return pScene;
}

void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
