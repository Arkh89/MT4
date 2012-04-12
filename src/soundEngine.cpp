#include "soundEngine.hpp"
#include "exception.hpp"
#include <QFile>

	Sound::Sound(const std::string& filename)
	{
		SF_INFO fileInfos;
		SNDFILE* file = sf_open(filename.c_str(), SFM_READ, &fileInfos);
		if(!file)
			throw Exception("Sound::Sound - Unable to read file : " + filename + ".", __FILE__, __LINE__);

		nbSamples  = static_cast<ALsizei>(fileInfos.channels * fileInfos.frames);
		sampleRate = static_cast<ALsizei>(fileInfos.samplerate);

		samples.resize(nbSamples);

		if(sf_read_short(file, &samples[0], nbSamples) < nbSamples)
			throw Exception("Sound::Sound - Unable to read file : " + filename + ". Samples failure.", __FILE__, __LINE__);

		switch (fileInfos.channels)
		{
			case 1 :  format = AL_FORMAT_MONO16;   break;
			case 2 :  format = AL_FORMAT_STEREO16; break;
			default :
				throw Exception("Sound::Sound - Unable to read file : " + filename + ". Incompatible format.", __FILE__, __LINE__);
		}

		sf_close(file);

		alGenBuffers(1, &buffer);

		alBufferData(buffer, format, &samples[0], nbSamples * sizeof(ALushort), sampleRate);

		if(alGetError()!=AL_NO_ERROR)
			throw Exception("Sound::Sound - Unable to read file : " + filename + ". An OpenAL error occured.", __FILE__, __LINE__);

	}

	Sound::~Sound(void)
	{
		samples.clear();
		alDeleteBuffers(1, &buffer);
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
		alSource3f(s,AL_POSITION,pos.x,pos.y,0.0);
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
		checkLoop();
	}

	void SoundEngine::checkLoop(void)
	{
		if(!background->isPlaying() && bSound!=NULL)
		{
			std::cout << "Playing background..." << std::endl;
			background->play(*bSound);
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
