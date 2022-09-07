#pragma once

#include <Windows.h>
#include <xaudio2.h>
#include <wrl.h>
#include <unordered_map>
#include <string>


class Sound
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	static Sound* GetInstance();

public:
	// �`�����N�w�b�_

	struct ChunkHeader
	{
		char id[4]; // �`�����N����ID
		int32_t size;  // �`�����N�T�C�Y
	};


	// RIFF�w�b�_�`�����N
	struct RiffHeader
	{
		ChunkHeader chunk;   // "RIFF"
		char type[4]; // "WAVE"
	};


	// FMT�`�����N
	struct FormatChunk
	{
		ChunkHeader chunk; // "fmt "
		WAVEFORMATEX fmt; // �g�`�t�H�[�}�b�g
	};

	// �����f�[�^
	struct SoundData
	{
		// �g�`�t�H�[�}�b�g
		WAVEFORMATEX wfex;
		// �o�b�t�@�̐擪�A�h���X
		BYTE* pBuffer;

		// �o�b�t�@�̃T�C�Y
		unsigned int bufferSize;
	};

public:
	// ����������
	bool Initialize();

	// �I������
	void Finalize();

	// WAVE�����ǂݍ���
	void LoadWave(const char* filename);


	// �����Đ�
	void PlayWave(const char* filename, bool loopFlag);

	// �������~�߂�
	void Stop(const char* filename);


	// ���ʂ̎擾
	float GetVolume(const char* filename);

	// ���ʂ̐ݒ�
	void SetVolume(const char* filename, float volume);

private:
	// �T�E���h�f�[�^�̉��
	void Unload(SoundData* saundoData);

	Sound() = default;
	Sound(const Sound&) = delete;
	~Sound() = default;
	Sound& operator=(const Sound&) = delete;
private: // �����o�ϐ�
	// �f�B���N�g���[�p�X
	const std::string directoryPath = "Resources/BGM/";
	// xAudio�̃C���X�^���X
	ComPtr<IXAudio2> xAudio2;
	// �T�E���h�f�[�^�z��
	std::unordered_map<std::string, SoundData> soundDatas;
	// �T�E���h�{�C�X�z��
	std::unordered_map<std::string, IXAudio2SourceVoice*> pSourceVoices;
};
