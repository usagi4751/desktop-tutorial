//=============================================================================
//
// �T�E���h���� [sound.cpp]
// Author : �ؓc�C���l
//
//=============================================================================
#include "sound.h"


/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

/*------------------------------------------------------------------------------
   �\���̂̒�`
------------------------------------------------------------------------------*/
struct SoundData {
	std::string m_Kinds;						// ��ޖ�
	IXAudio2SourceVoice* m_apSourceVoice;		// �\�[�X�{�C�X
	BYTE* m_apDataAudio;						// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio;							// �I�[�f�B�I�f�[�^�T�C�Y
	UINT64 m_Smaple;
	UINT32 m_LoopCount;
	float m_CurrentVolume;
};

/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
------------------------------------------------------------------------------*/
static IXAudio2 *g_pXAudio2 = NULL;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
static IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
std::unordered_map<std::string, std::string> g_SoundPathList;
std::unordered_map<int, SoundData> g_SoundDataList;
std::unordered_map<std::string, SoundData> g_ShareSoundDataList;
float g_WorldVolume;
float g_BGMVolume;
float g_SEVolume;

/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
bool InitSound(HWND hWnd)
{
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();

		return false;
	}
	
	// �}�X�^�[�{�C�X�̐���
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if(g_pXAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return false;
	}

	//�T�E���h�̓o�^
	RegisterSound();
	//�e�{�����[���̏�����
	g_WorldVolume = 0.5f;
	g_BGMVolume = 0.1f;
	g_SEVolume = 0.5f;

	return true;
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitSound(void)
{
	// �S�ẴT�E���h���~����
	for (auto& data:g_SoundDataList)
	{
		if (data.second.m_apSourceVoice) {
			// �ꎞ��~
			data.second.m_apSourceVoice->Stop(0);

			// �I�[�f�B�I�o�b�t�@�̍폜
			data.second.m_apSourceVoice->FlushSourceBuffers();

			// �\�[�X�{�C�X�̔j��
			data.second.m_apSourceVoice->DestroyVoice();
			data.second.m_apSourceVoice = NULL;

			// �I�[�f�B�I�f�[�^�̊J��
			free(data.second.m_apDataAudio);
			data.second.m_apDataAudio = NULL;
		}
	}
	for (auto& data : g_ShareSoundDataList)
	{
		if (data.second.m_apSourceVoice) {
			// �ꎞ��~
			data.second.m_apSourceVoice->Stop(0);

			// �I�[�f�B�I�o�b�t�@�̍폜
			data.second.m_apSourceVoice->FlushSourceBuffers();

			// �\�[�X�{�C�X�̔j��
			data.second.m_apSourceVoice->DestroyVoice();
			data.second.m_apSourceVoice = NULL;

			// �I�[�f�B�I�f�[�^�̊J��
			free(data.second.m_apDataAudio);
			data.second.m_apDataAudio = NULL;
		}
	}
	g_SoundDataList.clear();
	g_ShareSoundDataList.clear();
	g_SoundPathList.clear();
	// �}�X�^�[�{�C�X�̔j��
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COM���C�u�����̏I������
	CoUninitialize();
}

/*------------------------------------------------------------------------------
   �T�E���h�t�@�C���̓ǂݍ���
------------------------------------------------------------------------------*/
int LoadSound(std::string name)
{
	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̃N���A
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// �T�E���h�f�[�^�t�@�C���̐���
	hFile = CreateFile(g_SoundPathList.at(name).c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return -1;
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		MessageBox(NULL, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return -1;
	}

	HRESULT hr;

	// WAVE�t�@�C���̃`�F�b�N
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return -1;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return -1;
	}
	if (dwFiletype != 'EVAW')
	{
		MessageBox(NULL, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
		return -1;
	}

	// �t�H�[�}�b�g�`�F�b�N
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return -1;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return -1;
	}

	// �I�[�f�B�I�f�[�^�ǂݍ���
	SoundData data;
	hr = CheckChunk(hFile, 'atad', &data.m_aSizeAudio, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return -1;
	}
	data.m_apDataAudio = (BYTE*)malloc(data.m_aSizeAudio);
	hr = ReadChunkData(hFile, data.m_apDataAudio, data.m_aSizeAudio, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return -1;
	}

	// �\�[�X�{�C�X�̐���
	hr = g_pXAudio2->CreateSourceVoice(&data.m_apSourceVoice, &(wfx.Format));
	if (FAILED(hr))
	{
		MessageBox(NULL, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
		return -1;
	}


	int index = (int)g_SoundDataList.size();
	for (int i = 0; i < g_SoundDataList.size(); i++)
	{
		if (!g_SoundDataList.count(i)) {
			index = i;
			break;
		}
	}

	//�T�E���h�̎�ސݒ�
	auto chara = g_SoundPathList.at(name)[5];
	if (chara == 'B')
		data.m_Kinds = BGM;
	else
		data.m_Kinds = SE;

	//�T�E���h�f�[�^�̊i�[
	g_SoundDataList[index] = data;


	return index;
}

/*------------------------------------------------------------------------------
   �T�E���h�t�@�C���̓ǂݍ���
------------------------------------------------------------------------------*/
bool LoadShareSound(std::string name)
{
	//���ɋ��L����Ă���T�E���h�̕Ԃ�l
	if (g_ShareSoundDataList.count(name)) {
		return false;
	}


	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̃N���A
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// �T�E���h�f�[�^�t�@�C���̐���
	hFile = CreateFile(g_SoundPathList.at(name).c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return false;
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		MessageBox(NULL, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return false;
	}

	HRESULT hr;

	// WAVE�t�@�C���̃`�F�b�N
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return false;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return false;
	}
	if (dwFiletype != 'EVAW')
	{
		MessageBox(NULL, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
		return false;
	}

	// �t�H�[�}�b�g�`�F�b�N
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return false;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return false;
	}

	// �I�[�f�B�I�f�[�^�ǂݍ���
	SoundData data;
	hr = CheckChunk(hFile, 'atad', &data.m_aSizeAudio, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return false;
	}
	data.m_apDataAudio = (BYTE*)malloc(data.m_aSizeAudio);
	hr = ReadChunkData(hFile, data.m_apDataAudio, data.m_aSizeAudio, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return false;
	}

	// �\�[�X�{�C�X�̐���
	hr = g_pXAudio2->CreateSourceVoice(&data.m_apSourceVoice, &(wfx.Format));
	if (FAILED(hr))
	{
		MessageBox(NULL, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
		return false;
	}

	//�T�E���h�̎�ސݒ�
	auto chara = g_SoundPathList.at(name)[5];
	if (chara == 'B')
		data.m_Kinds = BGM;
	else
		data.m_Kinds = SE;

	//�T�E���h�f�[�^�̊i�[
	g_ShareSoundDataList[name] = data;

	return true;
}

/*------------------------------------------------------------------------------
   �����̍Đ�
------------------------------------------------------------------------------*/
void PlaySound(int index, int loopCount, float vol)
{
	// �����ɖ�����
	if (!g_SoundDataList.count(index))
		return;

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_SoundDataList.at(index).m_aSizeAudio;
	buffer.pAudioData = g_SoundDataList.at(index).m_apDataAudio;
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	if (loopCount < 0)
		loopCount = XAUDIO2_LOOP_INFINITE;
	buffer.LoopCount  = loopCount;

	// ��Ԏ擾
	g_SoundDataList.at(index).m_apSourceVoice->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_SoundDataList.at(index).m_apSourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_SoundDataList.at(index).m_apSourceVoice->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_SoundDataList.at(index).m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// ���[�v�J�E���g�̓o�^
	g_SoundDataList.at(index).m_LoopCount = loopCount;

	// �{�����[���̐ݒ�
	SetVolume(index, vol);

	// �Đ�
	g_SoundDataList.at(index).m_apSourceVoice->Start(0);
}

/*------------------------------------------------------------------------------
   �����̍Đ�
------------------------------------------------------------------------------*/
void PlaySound(int index, int loopCount, float vol, UINT32 sample)
{
	// �����ɖ�����
	if (!g_SoundDataList.count(index))
		return;

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_SoundDataList.at(index).m_aSizeAudio;
	buffer.pAudioData = g_SoundDataList.at(index).m_apDataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	if (loopCount < 0)
		loopCount = XAUDIO2_LOOP_INFINITE;
	buffer.PlayBegin = sample;
	buffer.LoopCount = loopCount;

	// ��Ԏ擾
	g_SoundDataList.at(index).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_SoundDataList.at(index).m_apSourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_SoundDataList.at(index).m_apSourceVoice->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_SoundDataList.at(index).m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// ���[�v�J�E���g�̓o�^
	g_SoundDataList.at(index).m_LoopCount = loopCount;

	//�{�����[���̐ݒ�
	SetVolume(index, vol);

	// �Đ�
	g_SoundDataList.at(index).m_apSourceVoice->Start(0);
}

/*------------------------------------------------------------------------------
   ���L�����̍Đ�
------------------------------------------------------------------------------*/
void PlaySound(std::string name, int loopCount, float vol)
{
	// �����ɖ�����
	if (!g_ShareSoundDataList.count(name))
		return;

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_ShareSoundDataList.at(name).m_aSizeAudio;
	buffer.pAudioData = g_ShareSoundDataList.at(name).m_apDataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	if (loopCount < 0)
		loopCount = XAUDIO2_LOOP_INFINITE;
	buffer.LoopCount = loopCount;

	// ��Ԏ擾
	g_ShareSoundDataList.at(name).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_ShareSoundDataList.at(name).m_apSourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_ShareSoundDataList.at(name).m_apSourceVoice->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_ShareSoundDataList.at(name).m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// ���[�v�J�E���g�̓o�^
	g_ShareSoundDataList.at(name).m_LoopCount = loopCount;

	//�{�����[���̐ݒ�
	SetVolume(name, vol);

	// �Đ�
	g_ShareSoundDataList.at(name).m_apSourceVoice->Start(0);
}

/*------------------------------------------------------------------------------
   ���L�����̍Đ�
------------------------------------------------------------------------------*/
void PlaySound(std::string name, float vol)
{
	// �����ɖ�����
	if (!g_ShareSoundDataList.count(name))
		return;

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_ShareSoundDataList.at(name).m_aSizeAudio;
	buffer.pAudioData = g_ShareSoundDataList.at(name).m_apDataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = 0;

	// ��Ԏ擾
	g_ShareSoundDataList.at(name).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_ShareSoundDataList.at(name).m_apSourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_ShareSoundDataList.at(name).m_apSourceVoice->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_ShareSoundDataList.at(name).m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// ���[�v�J�E���g�̓o�^
	g_ShareSoundDataList.at(name).m_LoopCount = 0;

	//�{�����[���̐ݒ�
	SetVolume(name, vol);

	// �Đ�
	g_ShareSoundDataList.at(name).m_apSourceVoice->Start(0);
}

/*------------------------------------------------------------------------------
   �����̍ĊJ
------------------------------------------------------------------------------*/
void ResumeSound(int index)
{
	// �����ɖ�����
	if (!g_SoundDataList.count(index))
		return;

	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_SoundDataList.at(index).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		return;
	}

	XAUDIO2_BUFFER buffer;
	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_SoundDataList.at(index).m_aSizeAudio;
	buffer.pAudioData = g_SoundDataList.at(index).m_apDataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.PlayBegin = g_SoundDataList.at(index).m_Smaple;
	buffer.LoopCount = g_SoundDataList.at(index).m_LoopCount;

	// �I�[�f�B�I�o�b�t�@�̍폜
	g_SoundDataList.at(index).m_apSourceVoice->FlushSourceBuffers();

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_SoundDataList.at(index).m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// �Đ�
	g_SoundDataList.at(index).m_apSourceVoice->Start(0);
}

/*------------------------------------------------------------------------------
   ���L�����̍ĊJ
------------------------------------------------------------------------------*/
void ResumeSound(std::string name)
{
	// �����ɖ�����
	if (!g_ShareSoundDataList.count(name))
		return;

	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_ShareSoundDataList.at(name).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		return;
	}

	XAUDIO2_BUFFER buffer;
	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_ShareSoundDataList.at(name).m_aSizeAudio;
	buffer.pAudioData = g_ShareSoundDataList.at(name).m_apDataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.PlayBegin = g_ShareSoundDataList.at(name).m_Smaple;
	buffer.LoopCount = g_ShareSoundDataList.at(name).m_LoopCount;

	// �I�[�f�B�I�o�b�t�@�̍폜
	g_ShareSoundDataList.at(name).m_apSourceVoice->FlushSourceBuffers();

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_ShareSoundDataList.at(name).m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// �Đ�
	g_ShareSoundDataList.at(name).m_apSourceVoice->Start(0);
}

/*------------------------------------------------------------------------------
   �����̈ꎞ��~
------------------------------------------------------------------------------*/
void PuaseSound(int index)
{
	// �����ɖ�����
	if (!g_SoundDataList.count(index))
		return;

	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_SoundDataList.at(index).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_SoundDataList.at(index).m_apSourceVoice->Stop(0);

		// �T���v���̎擾
		g_SoundDataList.at(index).m_Smaple = xa2state.SamplesPlayed;

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_SoundDataList.at(index).m_apSourceVoice->FlushSourceBuffers();
	}
}

/*------------------------------------------------------------------------------
   ���L�����̈ꎞ��~
------------------------------------------------------------------------------*/
void PuaseSound(std::string name)
{
	// �����ɖ�����
	if (!g_ShareSoundDataList.count(name))
		return;

	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_ShareSoundDataList.at(name).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_ShareSoundDataList.at(name).m_apSourceVoice->Stop(0);

		// �T���v���̎擾
		g_ShareSoundDataList.at(name).m_Smaple = xa2state.SamplesPlayed;

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_ShareSoundDataList.at(name).m_apSourceVoice->FlushSourceBuffers();
	}
}

/*------------------------------------------------------------------------------
   ����Ă��邷�ׂẲ����ꎞ��~
------------------------------------------------------------------------------*/
void PuaseSoundAll(void)
{
	XAUDIO2_VOICE_STATE xa2state;

	for (auto& data : g_SoundDataList)
	{
		// ��Ԏ擾
		data.second.m_apSourceVoice->GetState(&xa2state);
		if (xa2state.BuffersQueued != 0) {// �Đ���
			// �ꎞ��~
			data.second.m_apSourceVoice->Stop(0);

			// �T���v���̎擾
			data.second.m_Smaple = xa2state.SamplesPlayed;

			// �I�[�f�B�I�o�b�t�@�̍폜
			data.second.m_apSourceVoice->FlushSourceBuffers();
		}
		// �������[�̃��Z�b�g
		ZeroMemory(&xa2state, sizeof(XAUDIO2_VOICE_STATE));
	}
}

/*------------------------------------------------------------------------------
   �����̒�~
------------------------------------------------------------------------------*/
void StopSound(int index)
{
	// �����ɖ�����
	if (!g_SoundDataList.count(index))
		return;

	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_SoundDataList.at(index).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_SoundDataList.at(index).m_apSourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_SoundDataList.at(index).m_apSourceVoice->FlushSourceBuffers();

	}

	// �\�[�X�{�C�X�̔j��
	g_SoundDataList.at(index).m_apSourceVoice->DestroyVoice();
	g_SoundDataList.at(index).m_apSourceVoice = NULL;

	// �I�[�f�B�I�f�[�^�̊J��
	free(g_SoundDataList.at(index).m_apDataAudio);
	g_SoundDataList.at(index).m_apDataAudio = NULL;


	//�T�E���h���X�g�̈ꕔ�폜
	g_SoundDataList.erase(g_SoundDataList.find(index));
}

/*------------------------------------------------------------------------------
   ���L�����̒�~
------------------------------------------------------------------------------*/
void StopSound(std::string name)
{
	// �����ɖ�����
	if (!g_ShareSoundDataList.count(name))
		return;

	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_ShareSoundDataList.at(name).m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_ShareSoundDataList.at(name).m_apSourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_ShareSoundDataList.at(name).m_apSourceVoice->FlushSourceBuffers();
	}

	// �\�[�X�{�C�X�̔j��
	g_ShareSoundDataList.at(name).m_apSourceVoice->DestroyVoice();
	g_ShareSoundDataList.at(name).m_apSourceVoice = NULL;

	// �I�[�f�B�I�f�[�^�̊J��
	free(g_ShareSoundDataList.at(name).m_apDataAudio);
	g_ShareSoundDataList.at(name).m_apDataAudio = NULL;

	//�T�E���h���X�g�̈ꕔ�폜
	g_ShareSoundDataList.erase(g_ShareSoundDataList.find(name));
}

/*------------------------------------------------------------------------------
   �ǂݍ���ł��邷�ׂẲ������~
------------------------------------------------------------------------------*/
void StopSoundAll(void)
{
	XAUDIO2_VOICE_STATE xa2state;

	// �ꎞ��~
	for (auto& data:g_SoundDataList)
	{
		// �ꎞ��~
		data.second.m_apSourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		data.second.m_apSourceVoice->FlushSourceBuffers();

		// �\�[�X�{�C�X�̔j��
		data.second.m_apSourceVoice->DestroyVoice();
		data.second.m_apSourceVoice = NULL;

		// �I�[�f�B�I�f�[�^�̊J��
		free(data.second.m_apDataAudio);
		data.second.m_apDataAudio = NULL;

		// �������[�̃��Z�b�g
		ZeroMemory(&xa2state, sizeof(XAUDIO2_VOICE_STATE));
	}

	//�T�E���h���X�g�̑S����
	g_SoundDataList.clear();
}

/*------------------------------------------------------------------------------
	���ʐݒ�
------------------------------------------------------------------------------ */
void SetVolume(int index, float vol)
{
	//�����l�̉��
	if (!g_SoundDataList.count(index)||vol > 1 || vol < 0)
		return;

	//�{�����[���̐ݒ�
	g_SoundDataList.at(index).m_Kinds == BGM ?
		g_SoundDataList.at(index).m_apSourceVoice->SetVolume(vol * g_BGMVolume * g_WorldVolume) :
		g_SoundDataList.at(index).m_apSourceVoice->SetVolume(vol * g_SEVolume * g_WorldVolume);

	g_SoundDataList.at(index).m_CurrentVolume = vol;
}

/*------------------------------------------------------------------------------
	�S�Ẳ����̉��ʐݒ�
------------------------------------------------------------------------------ */
void SetVolumeAll(float world)
{
	//�����l�̉��
	if (world > 1 || world < 0)
		return;

	//�{�����[���̐ݒ�
	g_WorldVolume = world;
	for (auto& data:g_SoundDataList)
	{
		data.second.m_Kinds == BGM ?
			data.second.m_apSourceVoice->SetVolume(data.second.m_CurrentVolume * g_BGMVolume * g_WorldVolume) :
			data.second.m_apSourceVoice->SetVolume(data.second.m_CurrentVolume * g_SEVolume * g_WorldVolume);
			
	}
	for (auto& data : g_ShareSoundDataList)
	{
		data.second.m_Kinds == BGM ?
			data.second.m_apSourceVoice->SetVolume(data.second.m_CurrentVolume * g_BGMVolume * g_WorldVolume) :
			data.second.m_apSourceVoice->SetVolume(data.second.m_CurrentVolume * g_SEVolume * g_WorldVolume);

	}
}

/*------------------------------------------------------------------------------
	��ނ��Ƃ̉����̉��ʐݒ�
------------------------------------------------------------------------------ */
void SetVolumeKinds(std::string kinds, float vol)
{
	//�����l�̉��
	if (vol > 1 || vol < 0)
		return;

	kinds == BGM?g_BGMVolume = vol : g_SEVolume = vol;
	for (auto& data : g_SoundDataList)
	{
		if (data.second.m_Kinds == kinds) {
			data.second.m_apSourceVoice->SetVolume(data.second.m_CurrentVolume * vol * g_WorldVolume);
		}
	}
	for (auto& data : g_ShareSoundDataList)
	{
		if (data.second.m_Kinds == kinds) {
			data.second.m_apSourceVoice->SetVolume(data.second.m_CurrentVolume * vol * g_WorldVolume);
		}

	}
}

/*------------------------------------------------------------------------------
	���L�����̉��ʐݒ�
------------------------------------------------------------------------------ */
void SetVolume(std::string name, float vol)
{
	//�����l�̉��
	if (!g_ShareSoundDataList.count(name) || vol > 1 || vol < 0)
		return;

	//�{�����[���̐ݒ�
	g_ShareSoundDataList.at(name).m_Kinds == BGM ?
		g_ShareSoundDataList.at(name).m_apSourceVoice->SetVolume(vol * g_BGMVolume * g_WorldVolume) :
		g_ShareSoundDataList.at(name).m_apSourceVoice->SetVolume(vol * g_SEVolume * g_WorldVolume);

	g_ShareSoundDataList.at(name).m_CurrentVolume = vol;
}

/*------------------------------------------------------------------------------
   WAVE�t�H�[�}�b�g�̃`�F�b�N
------------------------------------------------------------------------------*/
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

/*------------------------------------------------------------------------------
   WAVE�t�H�[�}�b�g�̓ǂݍ���
------------------------------------------------------------------------------*/
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

/*------------------------------------------------------------------------------
   �T�E���h�p�X���̓o�^
------------------------------------------------------------------------------*/
void RegisterSound(void)
{
	g_SoundPathList["machine"] = "data/SE/se_machine_noise.wav.wav";
	g_SoundPathList["scorpion"] = "data/SE/sasori.wav";
	g_SoundPathList["spider"] = "data/SE/spider_cry.wav";
	g_SoundPathList["use_card"] = "data/SE/attacksound.wav";
	g_SoundPathList["fier"] = "data/SE/fier.wav";
	g_SoundPathList["water"] = "data/SE/water.wav";
	g_SoundPathList["wind"] = "data/SE/wind.wav";
	g_SoundPathList["heal"] = "data/SE/heal.wav";
	g_SoundPathList["run"] = "data/SE/running-1-6846.wav";
	g_SoundPathList["wark"] = "data/SE/concrete-footsteps-6752.wav";
	g_SoundPathList["patrolenemy"] = "data/SE/se_machine_noise.wav";
	g_SoundPathList["enemybullet1"] = "data/SE/bulletenemy1.wav";
	g_SoundPathList["enemybullet2"] = "data/SE/bulletenemy2.wav";
	g_SoundPathList["bottun1"] = "data/SE/bottun1.wav";
	g_SoundPathList["bottun2"] = "data/SE/bottun2.wav";
	g_SoundPathList["bottun3"] = "data/SE/bottun3.wav";
	g_SoundPathList["bossbullet1"] = "data/SE/bossbullet1.wav";
	g_SoundPathList["bossbullet2"] = "data/SE/bossbullet2.wav";
	g_SoundPathList["paper"] = "data/SE/handle-paper-foley-2-172689.wav";
	g_SoundPathList["boss2_attack1"] = "data/SE/boss2_attack1.wav";
	g_SoundPathList["boss2_attack2"] = "data/SE/boss2_attack2.wav";

	g_SoundPathList["menu"] = "data/BGM/menubgm.wav";
	g_SoundPathList["sgatebgm"] = "data/BGM/sgatebgm.wav";
}

/*------------------------------------------------------------------------------
   ���[���h�{�����[���̎擾
------------------------------------------------------------------------------*/
float GetWolrdSound()
{
	return g_WorldVolume;
}

/*------------------------------------------------------------------------------
   ���ʉ��{�����[���̎擾
------------------------------------------------------------------------------*/
float GetSESound()
{
	return g_SEVolume;
}

/*------------------------------------------------------------------------------
   BGM�{�����[���̎擾
------------------------------------------------------------------------------*/
float GetBGMSound()
{
	return g_BGMVolume;
}

#ifdef _DEBUG
/*------------------------------------------------------------------------------
	�T�E���h�f�[�^�T�C�Y�̎擾
------------------------------------------------------------------------------*/
const int DataSize(void)
{
	int size = g_SoundDataList.size() + g_ShareSoundDataList.size();
	return size;
}
#endif // _DEBUG
