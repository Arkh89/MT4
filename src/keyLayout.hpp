#ifndef __MT4_KEYLAYOUT__
#define __MT4_KEYLAYOUT__

	#include <QKeyEvent>
	#include <QWidget>

	enum KeyAction
	{
		KeyUp,
		KeyDown,
		KeyLeft,
		KeyRight,
		KeySpace,
		KeyEscape,
		KeyReturn,
		KeyPlus,
		KeyMinus,
		// Add new keys before this line
		NumKey,
		NoAction
	};

	class KeyLayout : public QWidget
	{
		Q_OBJECT

		private :
			Qt::Key	keyAssociation[NumKey];
			bool 	keyPressed[NumKey],
				keyJustPressed[NumKey],
				keyJustReleased[NumKey];

			KeyAction corresponding(const Qt::Key& k) const;
		public :
			KeyLayout(QWidget* w);
			~KeyLayout(void);

			bool pressed(const KeyAction& a) const;
			bool justPressed(const KeyAction& a);
			bool justReleased(const KeyAction& a);

		public slots :
			void keyPress(QKeyEvent* event);
			void keyRelease(QKeyEvent* event);
	};

#endif
