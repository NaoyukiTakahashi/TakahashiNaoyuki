//=============================================================================
//
// �i���o�[���� [number.cpp]
// Author : 
//
//=============================================================================

//*****************************************************************************
// �t�@�C���C���N���[�h
//*****************************************************************************
#include "number.h"
#include "manager.h"
#include "renderer.h"

// �}�N����`
#define	SCORE_POS_X			(SCREEN_WIDTH - (35.0f * 8))	// �X�R�A�̕\����ʒu(�w���W)
#define	SCORE_POS_Y			(20.0f)							// �X�R�A�̕\����ʒu(�x���W)
#define	SCORE_WIDTH			(35.0f)							// �X�R�A�̐����̕�
#define	SCORE_HEIGHT		(70.0f)							// �X�R�A�̐����̍���
#define	SCORE_INTERVAL_X	(35.0f - 3.0f)					// �X�R�A�̐����̕\���Ԋu

//*****************************************************************************
// �ÓI�����o�ϐ��錾
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

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// ���_����ݒ�
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
	// ���_�o�b�t�@�̔j��
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

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
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

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, "TEX/number000.png", &m_pTexture);

	return S_OK;
}

void CNumber::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}