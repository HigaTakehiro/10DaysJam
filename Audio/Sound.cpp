#include "Sound.h"
#include <fstream>
#include <cassert>

#pragma comment(lib,"xaudio2.lib")

Sound* Sound::GetInstance()
{
	static Sound instance;

	return &instance;
}

bool Sound::Initialize()
{
	HRESULT result;

	IXAudio2MasteringVoice* masterVoice;

	// XAudio�G���W���̃C���X�^���X�𐶐�
	result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if FAILED(result) {
		assert(0);
		return false;
	}

	// �}�X�^�[�{�C�X�𐶐�
	result = xAudio2->CreateMasteringVoice(&masterVoice);
	if FAILED(result) {
		assert(0);
		return false;
	}

	return true;
}

void Sound::Finalize()
{
	// xAudio�I������
	xAudio2.Reset();
	// �T�E���h�f�[�^���
	for (std::unordered_map<std::string, SoundData>::iterator it = soundDatas.begin();
		it != soundDatas.end(); it++) {
		Unload(&it->second);
	}
	soundDatas.clear();
	pSourceVoices.clear();
}

void Sound::LoadWave(const char* filename)
{
	if (soundDatas.find(filename) != soundDatas.end()) {
		// �d���ǂݍ��݂Ȃ̂ŁA��������������
		return;
	}

	// �t�@�C�����̓X�g���[���̃C���X�^���X
	std::ifstream file;
	// .wav�t�@�C�����o�C�i�����[�h�ŊJ��
	file.open(directoryPath + filename, std::ios_base::binary);
	// �t�@�C���I�[�v�����s�����o����
	assert(file.is_open());

	// RIFF�w�b�_�[�̓ǂݍ���
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	// �t�@�C����RIFF���`�F�b�N
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}
	// �^�C�v��WAVE���`�F�b�N
	if (strncmp(riff.type, "WAVE", 4) != 0) {
		assert(0);
	}

	// Format�`�����N�̓ǂݍ���
	FormatChunk format = {};
	// �`�����N�w�b�_�[�̊m�F
	file.read((char*)&format, sizeof(ChunkHeader));
	if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
		assert(0);
	}
	// �`�����N�{�̂̓ǂݍ���
	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);

	// Data�`�����N�̓ǂݍ���
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));
	// JUNK�`�����N�����o�����ꍇ
	if (strncmp(data.id, "JUNK ", 4) == 0) {
		// �ǂݎ��ʒu��JUNK�`�����N�̏I���܂Ői�߂�
		file.seekg(data.size, std::ios_base::cur);
		// �ēǂݍ���
		file.read((char*)&data, sizeof(data));
	}

	if (strncmp(data.id, "data ", 4) != 0) {
		assert(0);
	}

	// Data�`�����N�̃f�[�^���i�g�`�f�[�^�j�̓ǂݍ���
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);

	// Wave�t�@�C�������
	file.close();

	// �z��ɂ��܂��ׂ̉����f�[�^
	SoundData soundData = {};

	soundData.wfex = format.fmt;
	soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	soundData.bufferSize = data.size;

	// �t�@�C�����œo�^
	soundDatas.emplace(filename, soundData);

	HRESULT result;

	// �g�`�t�H�[�}�b�g������SourceVoice�̐���
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundDatas[filename].wfex);
	assert(SUCCEEDED(result));

	// �t�@�C�����œo�^
	pSourceVoices.emplace(filename, pSourceVoice);
}

void Sound::Unload(SoundData* soundData)
{
	// �o�b�t�@�����������
	delete[] soundData->pBuffer;

	soundData->pBuffer = 0;
	soundData->bufferSize = 0;
	soundData->wfex = {};
}

void Sound::PlayWave(const char* filename, bool loopFlag)
{
	HRESULT result;

	// �Đ�����g�`�f�[�^�̐ݒ�
	XAUDIO2_BUFFER buf{};

	buf.pAudioData = soundDatas[filename].pBuffer;
	buf.AudioBytes = soundDatas[filename].bufferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;
	//  buf.PlayBegin = 0;
	if (loopFlag) {
		buf.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	// �g�`�f�[�^�̍Đ�
	result = pSourceVoices[filename]->FlushSourceBuffers(); //�ŏ�����Đ�����
	result = pSourceVoices[filename]->SubmitSourceBuffer(&buf);
	result = pSourceVoices[filename]->Start();
}

void Sound::Stop(const char* filename)
{
	pSourceVoices[filename]->Stop();
}

float Sound::GetVolume(const char* filename)
{
	float volume;
	pSourceVoices[filename]->GetVolume(&volume);
	return volume;
}

void Sound::SetVolume(const char* filename, float volume)
{
	pSourceVoices[filename]->SetVolume(volume);
}
