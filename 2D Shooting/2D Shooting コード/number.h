//=============================================================================
//
// �i���o�[���� [number.h]
// Author : 
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X
//*****************************************************************************
class CNumber
{
public:
	CNumber();
	~CNumber();
	void SetNumber(int nNumber);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//�e�N�X�`��
};

#endif