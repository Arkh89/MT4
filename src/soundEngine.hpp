#ifndef __MT4_SOUND_ENGINE__
#define __MT4_SOUND_ENGINE__

	#include<vector>
	#include<string>
	#include <AL/al.h>
	#include <AL/alc.h>
	#include <sndfile.h>
	#include <QTimer>
	#include "vect2D.hpp"

	class Sound
	{
		private :
			ALsizei nbSamples, sampleRate;
			std::vector<ALshort> samples;
			ALenum format;
			ALuint buffer;

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
			//ALuint 		backgroundSource;

			//std::vector<Sound*> sounds;
			//std::vector<ALuint> sources;

			//int sBackground;
			SoundSource* background;
			Sound* bSound;

		public :
			SoundEngine(void);
			~SoundEngine(void);

			//int getSource(void);
			//int loadSound(const std::string& filename);
			void setBackgroundSound(const std::string& filename);
			//void playSound(int source, int sound);

			//void silence(void);
			std::string getLastError(void);

		private slots:
			void checkLoop(void);
	};

#endif // __MT4_SOUND_ENGINE__
