//=============================================================================
//
// �V�[������ [scene.cpp]
// Author : 
//
//=============================================================================

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �t�@�C���C���N���[�h
//*****************************************************************************

#include "scene.h"
#include "scene2d.h"
#include "renderer.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CScene *CScene::m_pTop;
CScene *CScene::m_pCur;

//=============================================================================
// �R���X�g���N�^�֐�
//=============================================================================
CScene::CScene(int nPriority)
{
	if (m_pTop == NULL || m_pCur == NULL)//continue;
	{
		//�g�b�v��ݒ�
		m_pTop = this;
		//���݂̃|�C���^�̑��
		m_pCur = this;

		//�O�̃|�C���^��ۑ�
		m_pPrev = NULL;
	}
	else
	{
		//�O�̃|�C���^��ۑ�
		m_pPrev = m_pCur;

		//���݂̃|�C���^�̑��
		m_pCur = this;
	}
	m_pNext = NULL;
	m_bDeath = false;
}

//=============================================================================
// �f�X�g���N�^�֐�
//=============================================================================
CScene::~CScene()
{
	if (m_pTop == this)//continue;
	{
		m_pTop = m_pTop->m_pNext;
	}
	else if (m_pCur == this)
	{
		m_pCur = m_pCur->m_pPrev;
	}

	if (m_pNext == NULL)
	{
		m_pNext = m_pNext->m_pNext;
	}
	if (m_pPrev == NULL)
	{
		m_pPrev = m_pPrev->m_pPrev;
	}
}

//=============================================================================
// �I���֐�
//=============================================================================
void CScene::ReleaseAll(void)
{
	CScene *pScene = m_pTop;
	while (1)
	{
		if (pScene != NULL)
		{
			CScene *pSceneNext = pScene->m_pNext;

			//�I������
			pScene->Uninit();
			pScene = pSceneNext;
		}
	}
	while (1)
	{
		while (pScene->m_bDeath == true)
		{
			CScene *pSceneNext = pScene->m_pNext;

			//�I������
			pScene->Death();
			pScene = pSceneNext;
		}
	}
}

void CScene::UpdateAll(void)
{
	CScene *pScene = m_pTop;
	while (pScene)
	{
		CScene *pSceneNext = pScene->m_pNext;
		//�o�͏���
		pScene->Update();
		pScene = pSceneNext;
	}

	pScene = m_pTop;
	while (pScene->m_bDeath == true)
	{
		CScene *pSceneNext = pScene->m_pNext;
		//�o�͏���
		pScene->Death();
		pScene = pSceneNext;
	}
}

void CScene::DrawAll(void)
{
	CScene *pScene = m_pTop;
	while (pScene)
	{
		CScene *pSceneNext = pScene->m_pNext;
		//�o�͏���
		pScene->Draw();
		pScene = pSceneNext;
	}
}

void CScene::Death(void)
{
	CScene *pScene = this;

	if (m_pTop == this)
	{
		m_pTop = m_pNext;
	}
	if (m_pCur == this)
	{
		m_pCur = m_pPrev;
	}

	m_pNext->m_pPrev = m_pPrev;
	m_pPrev->m_pNext = m_pNext;

	delete this;
}

void CScene::Release(void)
{
	/*CScene *pScene = this;

	if (m_pTop == this)
	{
	m_pTop = m_pNext;
	}
	if (m_pCur == this)
	{
	m_pCur = m_pPrev;
	}

	m_pNext->m_pPrev = m_pPrev;
	m_pPrev->m_pNext = m_pNext;*/

	m_bDeath = true;
}