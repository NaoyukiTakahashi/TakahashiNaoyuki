//=============================================================================
//
// �v���[���[���� [enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENEMY_TEX 3
#define ENEMY_SIZE_WIDTH 100.0f
#define ENEMY_SIZE_HIGHT 100.0f

//*****************************************************************************
// �N���X
//*****************************************************************************
class CEnemy : public CScene2d
{
public:
	typedef enum
	{
		ENEMY_TYPE001 = 0,
		ENEMY_TYPE002,
		ENEMY_TYPE003,
		ENEMY_TYPE_MAXINUM
	}ENEMY_TYPE;

	CEnemy(int nPriority = 3);
	~CEnemy();
	HRESULT Init(D3DXVECTOR3 pos, ENEMY_TYPE enemy, int nRate);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy *Create(D3DXVECTOR3 pos, ENEMY_TYPE enemy, int nRate);
	static HRESULT Load(void);
	static void Unload(void);
	void SetState(STATE state) { m_state = state; };
	STATE GetState(void) { return m_state; };
private:
	D3DXVECTOR3 m_pos;  //���W
	int m_nCount;//�ˌ��Ԋu
	int m_nRate;//�ˌ��Ԋu
	STATE m_state;
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_ENEMY_POLYGON]; //�e�N�X�`��
	static int m_nId;

};

#endif