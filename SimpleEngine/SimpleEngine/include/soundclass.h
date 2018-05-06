///////////////////////////////////////////////////////////////////////////////
// Filename: soundclass.h
///////////////////////////////////////////////////////////////////////////////
#ifndef _SOUNDCLASS_H_
#define _SOUNDCLASS_H_


/////////////
// LINKING //
/////////////
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")


//////////////
// INCLUDES //
//////////////
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>


// Direct Sound �������ڼ����κθ�ʽ�� audio( �������Զ���� audio format ), ֻ������Ҫ���Լ��ṩ audio format ����Ϣ( �ǳ����� )
// �÷�: create a sound buffer with the play back format you would like, �� audio �ļ�������ݶ������ buffer ��, Ȼ��Ϳ��Բ�����
// ԭ��: Direct Sound ʵ�������� primary buffer �� secondary buffer ���� buffer
// primary buffer �����ڲ��ŵ� main sound memory buffer, ���������� default sound card ��
// secondary buffer ֻ�����ǵ� sound ��Ӳ�̼��غ��ŵĵط�, ���������� memory ��
// ��Ϊ���ǿ���ͬʱ���źü�����Ƶ�ļ�( ����໥������ secondary buffer ), ʵ�ʲ���ʱ���� mixing ���� sound into the primary buffer
// Ȼ��� primary buffer ���в���
class SoundClass
{
private:

	// the header of the .wav file
	// The header contains all the information about the audio file so we can use that to create a secondary buffer to accommodate the audio data
	struct WaveHeaderType
	{
		char chunkId[4];				// 4 bytes
		unsigned long chunkSize;		// 4 bytes
		char format[4];					// 4 bytes
		char subChunkId[4];				// 4 bytes
		unsigned long subChunkSize;
		unsigned short audioFormat;		// 2 bytes
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};

public:
	SoundClass();
	SoundClass(const SoundClass&);
	~SoundClass();

	bool Initialize(HWND);
	void Shutdown();

private:
	bool InitializeDirectSound(HWND);
	void ShutdownDirectSound();

	bool LoadWaveFile(char*, IDirectSoundBuffer8**);
	void ShutdownWaveFile(IDirectSoundBuffer8**);

	bool PlayWaveFile();

private:
	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;
	IDirectSoundBuffer8* m_secondaryBuffer1;
};

#endif