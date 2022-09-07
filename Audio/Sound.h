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
	// チャンクヘッダ

	struct ChunkHeader
	{
		char id[4]; // チャンク毎のID
		int32_t size;  // チャンクサイズ
	};


	// RIFFヘッダチャンク
	struct RiffHeader
	{
		ChunkHeader chunk;   // "RIFF"
		char type[4]; // "WAVE"
	};


	// FMTチャンク
	struct FormatChunk
	{
		ChunkHeader chunk; // "fmt "
		WAVEFORMATEX fmt; // 波形フォーマット
	};

	// 音声データ
	struct SoundData
	{
		// 波形フォーマット
		WAVEFORMATEX wfex;
		// バッファの先頭アドレス
		BYTE* pBuffer;

		// バッファのサイズ
		unsigned int bufferSize;
	};

public:
	// 初期化処理
	bool Initialize();

	// 終了処理
	void Finalize();

	// WAVE音声読み込み
	void LoadWave(const char* filename);


	// 音声再生
	void PlayWave(const char* filename, bool loopFlag);

	// 音声を止める
	void Stop(const char* filename);


	// 音量の取得
	float GetVolume(const char* filename);

	// 音量の設定
	void SetVolume(const char* filename, float volume);

private:
	// サウンドデータの解放
	void Unload(SoundData* saundoData);

	Sound() = default;
	Sound(const Sound&) = delete;
	~Sound() = default;
	Sound& operator=(const Sound&) = delete;
private: // メンバ変数
	// ディレクトリーパス
	const std::string directoryPath = "Resources/BGM/";
	// xAudioのインスタンス
	ComPtr<IXAudio2> xAudio2;
	// サウンドデータ配列
	std::unordered_map<std::string, SoundData> soundDatas;
	// サウンドボイス配列
	std::unordered_map<std::string, IXAudio2SourceVoice*> pSourceVoices;
};
