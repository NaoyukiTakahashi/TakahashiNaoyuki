//=============================================================================
//
// ���� [polygon.cpp]
// Author : 
//
//=============================================================================

//*****************************************************************************
// �t�@�C���C���N���[�h
//*****************************************************************************
#include "polygon.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^�֐�
//=============================================================================
CPolygon::CPolygon()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^�֐�
//=============================================================================
CPolygon::~CPolygon()
{

}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CPolygon::Init()
{
	VERTEX_2D*pVtx;

	LPDIRECT3DDEVICE9 pDevice = CManeger::GetRenderer()->GetDevice();

	m_pTexture = NULL; //�e�N�X�`��
	m_pVtxBuff = NULL; //�o�b�t�@
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);; //���W
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;       //�T�C�Y
	m_col = D3DCOLOR_RGBA(255, 255, 255, 255);;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// ���_����ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CPolygon::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

void CPolygon::Update(void)
{
	VERTEX_2D*pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	m_pVtxBuff->Unlock();
}

void CPolygon::Draw(void)
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

void CPolygon::SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col)
{
	m_pos = pos;
	m_size = size;
	m_col = col;
	
	Update();
}

CPolygon *CPolygon::Create()
{
	CPolygon *pScene;
	pScene = new CPolygon;
	pScene->Init();
	return pScene;
}

void CPolygon::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
