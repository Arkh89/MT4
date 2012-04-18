#ifndef __MT4_SOUND_ENGINE__
#define __MT4_SOUND_ENGINE__

        #include<vector>
	#include<string>
	#include <AL/al.h>
	#include <AL/alc.h>
	#include <QTimer>
	#include "vect2D.hpp"
	#include <cstring>

	class Sound
	{
		private :
			ALsizei nbSamples, sampleRate;
			ALenum format;
			ALuint buffer;

			void readData(unsigned short& dest, char* data);
			void readData(unsigned int& dest, char* data);

		public :
			Sound(const std::string& filename);
			~Sound(void);

			ALuint getBuffer(void) const;
	};

	class SoundSource
	{
		private :
			ALuint s;
		protected :
			Vect2D pos;
		public :
			SoundSource(void);
			SoundSource(const Vect2D& p);
			~SoundSource(void);

			bool isPlaying(void);
			void setPosition(const Vect2D& p);
			void play(const Sound& sound);
			void stop(void);
			void setGain(float g);
			// add doppler effect
			// add pitch effect
	};

	class SoundEngine : public QObject
	{
		Q_OBJECT

		private :
			QTimer* 	timer;
			ALCdevice* 	device;
			ALCcontext* 	context;

			SoundSource* background;
			Sound* bSound;

		public :
			SoundEngine(void);
			~SoundEngine(void);

			void setBackgroundSound(const std::string& filename);
			void setListenerPosition(const Vect2D& p);

			std::string getLastError(void);

		private slots:
			void checkLoop(void);
        };

#endif // __MT4_SOUND_ENGINE__
