//=============================================================================
//
// ���C������ [main.h]
// Author : 
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//#define DIRECTINPUT_VERSION 0x0800
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "dinput.h"	
#include <windows.h>
#include "d3dx9.h"
#include <xaudio2.h>

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment (lib, "dinput8.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"winmm.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define SCREEN_WIDTH	(1920)
#define SCREEN_HIGHT	(1080)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define NUM_VERTEX	(4)
#define NUM_POLYGON	(2)
#define MAX_POLYGON (128*10)//Polygon�ő吔

#define _DEBUG
#undef _DEBUG

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;//�ꏊ
	float rhw;
	D3DCOLOR col;//�F
	D3DXVECTOR2 tex;//UV���W
}VERTEX_2D;

#ifdef _DEBUG
int GetFPS(void);
#endif

#endif