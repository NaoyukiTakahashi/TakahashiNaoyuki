//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 高橋 那伯志
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BGM_1 "Sound/BGM/bgm.wav"
#define BGM_2 "Sound/BGM/game_maoudamashii_1_battle27.wav"
#define BGM_3 "Sound/BGM/bgm002.wav"
#define SE_1 "Sound/SE/se_maoudamashii_system43.wav"
#define SE_2 "Sound/SE/se_maoudamashii_battle15.wav"
#define SE_3 "Sound/SE/se_maoudamashii_retro12.wav"

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CSound
{
public:
	// サウンドファイル
	typedef enum
	{
		SOUND_LABEL_BGM_000 = 0,		// BGM0
		SOUND_LABEL_BGM_001,			// BGM1
		SOUND_LABEL_BGM_002,			// BGM2
		SOUND_LABEL_SE_SHOT,		// 弾発射音
		SOUND_LABEL_SE_HIT,			// ヒット音
		SOUND_LABEL_SE_EXPLOSION,	// 爆発音
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	// パラメータ構造体定義
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;

	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT Play(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	IXAudio2 * m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice * m_pMasteringVoice;			// マスターボイス
	IXAudio2SourceVoice * m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];// 各音素材のパラメータ
};

#endif
