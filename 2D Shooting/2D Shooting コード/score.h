//=============================================================================
//
// �X�R�A���� [score.h]
// Author : 
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SCORE 8

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//*****************************************************************************
// �N���X
//*****************************************************************************
class CScore : public CScene
{
public:
	CScore(int nPriority = 2);
	~CScore();
	void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type, int nPattern) {};
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(0.0f,0.0f,0.0f); };
	D3DXVECTOR2 GetSize(void) { return D3DXVECTOR2(0.0f, 0.0f); };
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetScore(int nScore) { m_nScore = nScore; };
	static void addScore(int nValue) { m_nScore += nValue; };
	static int GetScore(void) { return m_nScore; };
	static CScore*Create(void);
	void SetState(STATE state) {};
	STATE GetState(void) { return STATE_NONE; };
private:
	static int m_nScore;
	static CNumber *m_apNumber[MAX_SCORE];//�f�[�^�ۑ��p
};

#endif