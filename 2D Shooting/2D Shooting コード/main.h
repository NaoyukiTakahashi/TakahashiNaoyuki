//=============================================================================
//
// メイン処理 [main.h]
// Author : 
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//#define DIRECTINPUT_VERSION 0x0800
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "dinput.h"	
#include <windows.h>
#include "d3dx9.h"
#include <xaudio2.h>

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment (lib, "dinput8.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"winmm.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define SCREEN_WIDTH	(1920)
#define SCREEN_HIGHT	(1080)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define NUM_VERTEX	(4)
#define NUM_POLYGON	(2)
#define MAX_POLYGON (128*10)//Polygon最大数

#define _DEBUG
#undef _DEBUG

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;//場所
	float rhw;
	D3DCOLOR col;//色
	D3DXVECTOR2 tex;//UV座標
}VERTEX_2D;

#ifdef _DEBUG
int GetFPS(void);
#endif

#endif