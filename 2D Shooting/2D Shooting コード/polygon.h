//=============================================================================
//
// �|���S������ [polygon.h]
// Author : 
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X
//*****************************************************************************
class CPolygon
{
public:
	CPolygon();
	~CPolygon();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	static CPolygon *Create();
private:
	LPDIRECT3DTEXTURE9		m_pTexture; //�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //�o�b�t�@
	D3DXVECTOR3 m_pos; //���W
	D3DXVECTOR3 m_size;       //�T�C�Y
	D3DXCOLOR m_col;
};

#endif