#include "soundEngine.hpp"
#include "exception.hpp"
#include <QFile>
#include <fstream>

        Sound::Sound(const std::string& filename)
	{
		//See https://ccrma.stanford.edu/courses/422/projects/WaveFormat/ for more informations
		
		int length, offset;
		char* fileBuffer;
		std::fstream file;
		file.open(filename.c_str(), std::fstream::in | std::fstream::binary);

		if(!file.is_open())
			throw Exception("Sound::Sound - Unable to load file : " + filename + ".", __FILE__, __LINE__);

		// get length of file:
		file.seekg (0, std::ios::end);
		length = file.tellg();
		file.seekg (0, std::ios::beg);

		// allocate memory:
		fileBuffer = new char [length];

		// read data as a block:
		file.read (fileBuffer,length);

		file.close();

		unsigned short	audioFormat, audioChannels, bitsPerSample;
		unsigned int 	chunkSize, subChunk1Size, subChunk2Size, sampleRate, dataSize;


		std::cout << "Loading 		: " << filename << std::endl;
		std::cout << "	Chunk name 	: " << std::string(fileBuffer,4) << std::endl;
		readData(chunkSize,fileBuffer+4);
		std::cout << "	Chunk size 	: " << chunkSize << std::endl;
		std::cout << "	Format	 	: " << std::string(fileBuffer+8,4) << std::endl;
		std::cout << "	Subchunk ID 	: " << std::string(fileBuffer+12,4) << std::endl;
		readData(subChunk1Size,fileBuffer+16);
		std::cout << "	Sub Chunk size 	: " << subChunk1Size << std::endl;
		readData(audioFormat, fileBuffer+20);
		readData(audioChannels, fileBuffer+22);
		readData(sampleRate, fileBuffer+24);
		readData(bitsPerSample, fileBuffer+34);
		std::cout << "	Audio format 	: " << audioFormat << std::endl;
		std::cout << "	Audio channels 	: " << audioChannels << std::endl;
		std::cout << "	Sample rate 	: " << sampleRate << std::endl;
		std::cout << "	Bits per Sample	: " << bitsPerSample << std::endl;

		offset = 0;
		while(std::string(fileBuffer+36+offset,4)!="data")
		{
			offset++;
			if(36+offset>=length)
				throw Exception("Sound::Sound - Unable to find starting of DATA chunk for sound file : " + filename + ".", __FILE__, __LINE__);
		}

		std::cout << "	Data offset	: " << offset << std::endl;
		std::cout << "	Subchunk ID 	: " << std::string(fileBuffer+36+offset,4) << std::endl;
		readData(subChunk2Size,fileBuffer+40+offset);
		std::cout << "	Sub Chunk size 	: " << subChunk2Size << std::endl;

		if(bitsPerSample==8 && audioChannels==1)
			format = AL_FORMAT_MONO8;
		else if(bitsPerSample==8 && audioChannels==2)
			format = AL_FORMAT_STEREO8;
		else if(bitsPerSample==16 && audioChannels==1)
			format = AL_FORMAT_MONO16;
		else if(bitsPerSample==16 && audioChannels==2)
			format = AL_FORMAT_STEREO16;
		else
		{
			delete[] fileBuffer;
			throw Exception("Sound::Sound - Unable to find audio format corresponding to bitsPerSample=" + to_string(bitsPerSample) + "bits and channels=" + to_string(audioChannels) + ".", __FILE__, __LINE__);
		}

		readData(dataSize,fileBuffer+40+offset);

		unsigned char* data = new unsigned char[dataSize];
		memcpy(data, fileBuffer+44, dataSize);

		alGenBuffers(1, &buffer);

		this->nbSamples		= dataSize;
		this->sampleRate	= sampleRate;

		alBufferData(buffer, format, data, dataSize, sampleRate);

		delete[] fileBuffer;
		delete[] data;

		if(alGetError()!=AL_NO_ERROR)
			throw Exception("Sound::Sound - Unable to read file : " + filename + ". An OpenAL error occured.", __FILE__, __LINE__);
			
		std::cout << "	File loaded successfully" << std::endl;
	}

	Sound::~Sound(void)
	{
		alDeleteBuffers(1, &buffer);
	}

	void Sound::readData(unsigned short& dest, char* data)
	{
		memcpy(&dest, data, sizeof(unsigned short));
	}

	void Sound::readData(unsigned int& dest, char* data)
	{
		memcpy(&dest, data, sizeof(unsigned int));
	}

	ALuint Sound::getBuffer(void) const
	{
		return buffer;
	}

	SoundSource::SoundSource(void)
	 : pos()
	{
		alGenSources(1, &s);
		alSourcei(s, AL_BUFFER, 0);
	}

	SoundSource::SoundSource(const Vect2D& p)
	 : pos(p)
	{
		alGenSources(1, &s);
		alSourcei(s, AL_BUFFER, 0);
		setPosition(p);
	}

	SoundSource::~SoundSource(void)
	{
		stop();
		alDeleteSources(1, &s);
	}

	bool SoundSource::isPlaying(void)
	{
		ALint status;
		alGetSourcei(s, AL_SOURCE_STATE, &status);
		return status==AL_PLAYING;
	}

	void SoundSource::setPosition(const Vect2D& p)
	{
		pos = p;
		alSource3f(s,AL_POSITION,pos.getX(),pos.getY(),0.0);
	}

	void SoundSource::play(const Sound& sound)
	{
		if(!isPlaying())
		{
			alSourcei(s, AL_BUFFER, sound.getBuffer());
			alSourcePlay(s);
		}
	}

	void SoundSource::stop(void)
	{
		alSourcei(s, AL_BUFFER, 0);
	}

	void SoundSource::setGain(float g)
	{
		alSourcef(s,AL_GAIN,g);
	}

	SoundEngine::SoundEngine(void)
	 : bSound(NULL), background(NULL)
	{
		device = alcOpenDevice(NULL);
		if(!device)
			throw Exception("SoundEngine::SoundEngine - Unable to open device for OpenAL.", __FILE__, __LINE__);

		context = alcCreateContext(device, NULL);
		if (!context)
			throw Exception("SoundEngine::SoundEngine - Unable to create context for OpenAL.", __FILE__, __LINE__);

		if(!alcMakeContextCurrent(context))
			throw Exception("SoundEngine::SoundEngine - Unable to use OpenAL context.", __FILE__, __LINE__);

		background = new SoundSource;

		timer = new QTimer;
		timer->setInterval(1000.0);

		QObject::connect(timer, SIGNAL(timeout()),this, SLOT(checkLoop()));

		timer->start();
	}

	SoundEngine::~SoundEngine(void)
	{
		background->stop();
		delete background;
		delete bSound;

		alcMakeContextCurrent(NULL);

		alcDestroyContext(context);

		alcCloseDevice(device);
	}

	void SoundEngine::setBackgroundSound(const std::string& filename)
	{
		delete bSound;
		bSound = new Sound(filename);
		background->stop();
		checkLoop();
	}

	void SoundEngine::setListenerPosition(const Vect2D& p)
	{
		background->setPosition(p);
		alListener3f(AL_POSITION,p.getX(),p.getY(),0.0);
	}

	void SoundEngine::checkLoop(void)
	{
		if(!background->isPlaying() && bSound!=NULL)
		{
			std::cout << "Playing background..." << std::endl;
			background->play(*bSound);
			getLastError();
		}
	}

	std::string SoundEngine::getLastError(void)
	{
		ALenum err= alGetError();

		switch(err)
		{
			case AL_NO_ERROR: 		return "OpenAL : There is no current error.";
			case AL_INVALID_NAME:		return "OpenAL : Invalid name parameter.";
			case AL_INVALID_ENUM:		return "OpenAL : Invalid parameter.";
			case AL_INVALID_VALUE:		return "OpenAL : Invalid enum parameter value.";
			case AL_INVALID_OPERATION :	return "OpenAL : Illegal call.";
			case AL_OUT_OF_MEMORY :		return "OpenAL : Unable to allocate memory.";
			default :			return "OpenAL : Unknown OpenAL error.";
		}
        }
