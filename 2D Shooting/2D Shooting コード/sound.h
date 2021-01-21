//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���� �ߔ��u
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BGM_1 "Sound/BGM/bgm.wav"
#define BGM_2 "Sound/BGM/game_maoudamashii_1_battle27.wav"
#define BGM_3 "Sound/BGM/bgm002.wav"
#define SE_1 "Sound/SE/se_maoudamashii_system43.wav"
#define SE_2 "Sound/SE/se_maoudamashii_battle15.wav"
#define SE_3 "Sound/SE/se_maoudamashii_retro12.wav"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CSound
{
public:
	// �T�E���h�t�@�C��
	typedef enum
	{
		SOUND_LABEL_BGM_000 = 0,		// BGM0
		SOUND_LABEL_BGM_001,			// BGM1
		SOUND_LABEL_BGM_002,			// BGM2
		SOUND_LABEL_SE_SHOT,		// �e���ˉ�
		SOUND_LABEL_SE_HIT,			// �q�b�g��
		SOUND_LABEL_SE_EXPLOSION,	// ������
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	// �p�����[�^�\���̒�`
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
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
	IXAudio2 * m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice * m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice * m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];// �e���f�ނ̃p�����[�^
};

#endif
