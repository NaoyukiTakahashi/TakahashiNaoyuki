//*****************************************************************************
// ファイルインクルード
//*****************************************************************************
#include "manager.h"
#include "renderer.h"
#include "explosion.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosion::m_pExplosionTexture = NULL;

CExplosion::CExplosion(int nPriority)
{
}

CExplosion::~CExplosion()
{
}

HRESULT CExplosion::Init(D3DXVECTOR3 pos)
{
	BindTexture(m_pExplosionTexture);

	m_pos = pos;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	CScene2d::Init();
	return S_OK;
}

void CExplosion::Uninit(void)
{
	CScene2d::Uninit();
}

void CExplosion::Update(void)
{
	m_nCounterAnim++;

	SetPolygon(D3DXVECTOR3(m_pos), D3DXVECTOR3(EXPLOTION_SIZE_WIDTH, EXPLOTION_SIZE_HIGHT, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), TYPE_EXPLOSION, m_nPatternAnim);

	if (m_nCounterAnim == EXPLOTION_ANIM_SPEED)
	{
		m_nCounterAnim = 0;

		m_nPatternAnim++;
	}

	CScene2d::Update();

	if (m_pos.x <= 0 || SCREEN_WIDTH <= m_pos.x || m_pos.y <= 0 || SCREEN_HIGHT <= m_pos.y|| m_nPatternAnim > MAX_EXPLOTION_ANIM)
	{
		Uninit();
	}
}

void CExplosion::Draw(void)
{
	CScene2d::Draw();
}

CExplosion * CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pExplosion;
	pExplosion = new CExplosion;
	pExplosion->Init(pos);
	pExplosion->SetType(TYPE_EXPLOSION);
	return pExplosion;
}

HRESULT CExplosion::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "TEX/explosion000.png", &m_pExplosionTexture);

	return S_OK;
}

void CExplosion::Unload(void)
{
	// テクスチャの破棄
	if (m_pExplosionTexture != NULL)
	{
		m_pExplosionTexture->Release();
		m_pExplosionTexture = NULL;
	}
}
