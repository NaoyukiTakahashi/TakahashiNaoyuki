//=============================================================================
//
// �V�[��2D���� [scene2d.h]
// Author : 
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X
//*****************************************************************************
class CScene2d : public CScene
{
public:
	CScene2d(int nPriority = 3);
	~CScene2d();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type, int nPattern);
	D3DXVECTOR3 GetPosition(void) { return m_pos; };
	D3DXVECTOR2 GetSize(void) { return m_size; };
	static CScene2d *Create(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	virtual void SetState(STATE state) {};
	virtual STATE GetState(void) { return STATE_NONE; };
private:
	LPDIRECT3DTEXTURE9		m_pTexture; //�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //�o�b�t�@
	D3DXVECTOR3 m_pos;            //���S���W
	D3DXVECTOR3 m_posUpperLeft[MAX_POLYGON];   //���W0
	D3DXVECTOR3 m_posUpperRight[MAX_POLYGON];  //���W1
	D3DXVECTOR3 m_posBottomLeft[MAX_POLYGON];  //���W2
	D3DXVECTOR3 m_posBottomRight[MAX_POLYGON]; //���W3
	D3DXVECTOR2 m_uvUpperLeft;    //uv���W0
	D3DXVECTOR2 m_uvUpperRight;   //uv���W1
	D3DXVECTOR2 m_uvBottomLeft;   //uv���W2
	D3DXVECTOR2 m_uvBottomRight;  //uv���W3
	D3DXCOLOR m_col;   //�F
	TYPE m_type;       //�^�C�v
	int m_nPattern;    //�p�^�[��
	float m_fRadius;   //���a
	float m_fAngle;    //�p�x
	float m_fRot;      //�p�x���Z
	float m_fLength;   //���a���Z
	int m_nIndex;    //�p�^�[��
	D3DXVECTOR3 m_size;//�T�C�Y
	CScene2d *m_pScene2D;
};

#endif