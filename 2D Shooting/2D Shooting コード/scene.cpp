//=============================================================================
//
// シーン処理 [scene.cpp]
// Author : 
//
//=============================================================================

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// ファイルインクルード
//*****************************************************************************

#include "scene.h"
#include "scene2d.h"
#include "renderer.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CScene *CScene::m_pTop;
CScene *CScene::m_pCur;

//=============================================================================
// コンストラクタ関数
//=============================================================================
CScene::CScene(int nPriority)
{
	if (m_pTop == NULL || m_pCur == NULL)//continue;
	{
		//トップを設定
		m_pTop = this;
		//現在のポインタの代入
		m_pCur = this;

		//前のポインタを保存
		m_pPrev = NULL;
	}
	else
	{
		//前のポインタを保存
		m_pPrev = m_pCur;

		//現在のポインタの代入
		m_pCur = this;
	}
	m_pNext = NULL;
	m_bDeath = false;
}

//=============================================================================
// デストラクタ関数
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
// 終了関数
//=============================================================================
void CScene::ReleaseAll(void)
{
	CScene *pScene = m_pTop;
	while (1)
	{
		if (pScene != NULL)
		{
			CScene *pSceneNext = pScene->m_pNext;

			//終了処理
			pScene->Uninit();
			pScene = pSceneNext;
		}
	}
	while (1)
	{
		while (pScene->m_bDeath == true)
		{
			CScene *pSceneNext = pScene->m_pNext;

			//終了処理
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
		//出力処理
		pScene->Update();
		pScene = pSceneNext;
	}

	pScene = m_pTop;
	while (pScene->m_bDeath == true)
	{
		CScene *pSceneNext = pScene->m_pNext;
		//出力処理
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
		//出力処理
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