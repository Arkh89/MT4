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

		// Remplissage avec les échantillons lus
		alBufferData(buffer, format, &samples[0], nbSamples * sizeof(ALushort), sampleRate);

		// Vérification des erreurs
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

	SoundEngine::SoundEngine(void)
	 : sBackground(-1)
	{
		device = alcOpenDevice(NULL);
		if(!device)
			throw Exception("SoundEngine::SoundEngine - Unable to open device for OpenAL.", __FILE__, __LINE__);

		context = alcCreateContext(device, NULL);
		if (!context)
			throw Exception("SoundEngine::SoundEngine - Unable to create context for OpenAL.", __FILE__, __LINE__);

		if(!alcMakeContextCurrent(context))
			throw Exception("SoundEngine::SoundEngine - Unable to use OpenAL context.", __FILE__, __LINE__);

		alGenSources(1, &backgroundSource);

		timer = new QTimer;
		timer->setInterval(1000.0);

		QObject::connect(timer, SIGNAL(timeout()),this, SLOT(checkLoop()));

		timer->start();
	}

	SoundEngine::~SoundEngine(void)
	{
		alSourcei(backgroundSource, AL_BUFFER, 0);
		alDeleteSources(1, &backgroundSource);



		for(std::vector<ALuint>::iterator it = sources.begin(); it!=sources.end(); it++)
		{
			alSourcei(*it, AL_BUFFER, 0);
			alDeleteSources(1, &(*it));
		}
		sources.clear();

		for(std::vector<Sound*>::iterator it=sounds.begin(); it!=sounds.end(); it++)
			delete *it;
		sounds.clear();

		alcMakeContextCurrent(NULL);

		alcDestroyContext(context);

		alcCloseDevice(device);
	}

	int SoundEngine::loadSound(const std::string& filename)
	{
		if(!QFile::exists(filename.c_str()))
			throw Exception("SoundEngine::loadSound - Unable to load : " + filename + ". File doesn't exist.", __FILE__, __LINE__);

		sounds.push_back(new Sound(filename));

		return sounds.size()-1;
	}

	int SoundEngine::getSource(void)
	{
		ALuint s;
		alGenSources(1, &s);
		sources.push_back(s);
		return sources.size()-1;
	}

	void SoundEngine::setBackgroundSound(int s)
	{
		sBackground = s;
	}

	void SoundEngine::playSound(int source, int sound)
	{
		ALuint s = sources[source];
		ALint status;

		alGetSourcei(s, AL_SOURCE_STATE, &status);

		if(status!=AL_PLAYING)
		{
			alSourcei(s, AL_BUFFER, sounds[sound]->getBuffer());
			alSourcePlay(s);
		}
	}

	void SoundEngine::checkLoop(void)
	{
		ALint status;
		alGetSourcei(backgroundSource, AL_SOURCE_STATE, &status);

		if(status!=AL_PLAYING && sBackground>=0)
		{
			alSourcei(backgroundSource, AL_BUFFER, sounds[sBackground]->getBuffer());
			alSourcePlay(backgroundSource);
		}
	}
