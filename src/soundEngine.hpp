#ifndef __MT4_SOUND_ENGINE__
#define __MT4_SOUND_ENGINE__

	#include<vector>
	#include<string>
	#include <AL/al.h>
	#include <AL/alc.h>
	#include <sndfile.h>
	#include <QTimer>

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

	class SoundEngine : public QObject
	{
		Q_OBJECT

		private :
			QTimer* 	timer;
			ALCdevice* 	device;
			ALCcontext* 	context;
			ALuint 		backgroundSource;

			std::vector<Sound*> sounds;
			std::vector<ALuint> sources;

			int sBackground;

		public :
			SoundEngine(void);
			~SoundEngine(void);

			int getSource(void);
			int loadSound(const std::string& filename);
			void setBackgroundSound(int s);
			void playSound(int source, int sound);

			void silence(void);

		private slots:
			void checkLoop(void);
	};

#endif // __MT4_SOUND_ENGINE__
