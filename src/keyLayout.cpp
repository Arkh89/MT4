#include <iostream>
#include "keyLayout.hpp"

	KeyLayout::KeyLayout(QWidget* w)
	 : QWidget(w)
	{
		for(int i=0; i<NumKey; i++)
		{
			keyPressed[i]		= false;
			keyJustPressed[i]	= false;
			keyJustReleased[i]	= false;
		}

		keyAssociation[static_cast<int>(KeyUp)]		= Qt::Key_Up;
		keyAssociation[static_cast<int>(KeyDown)]	= Qt::Key_Down;
		keyAssociation[static_cast<int>(KeyLeft)]	= Qt::Key_Left;
		keyAssociation[static_cast<int>(KeyRight)]	= Qt::Key_Right;
		keyAssociation[static_cast<int>(KeySpace)]	= Qt::Key_Space;
		keyAssociation[static_cast<int>(KeyEscape)]	= Qt::Key_Escape;
		keyAssociation[static_cast<int>(KeyReturn)]	= Qt::Key_Return;
		keyAssociation[static_cast<int>(KeyPlus)]	= Qt::Key_Plus;
		keyAssociation[static_cast<int>(KeyMinus)]	= Qt::Key_Minus;
	}

	KeyLayout::~KeyLayout(void)
	{ }

	KeyAction KeyLayout::corresponding(const Qt::Key& k) const
	{
		for(int i=0; i<NumKey; i++)
			if(keyAssociation[i]==k)
				return static_cast<KeyAction>(i);

		return NoAction;
	}

	bool KeyLayout::pressed(const KeyAction& a) const
	{
		return keyPressed[static_cast<int>(a)];
	}

	bool KeyLayout::justPressed(const KeyAction& a)
	{
		if(keyJustPressed[static_cast<int>(a)])
		{
			keyJustPressed[static_cast<int>(a)] = false;
			return true;
		}
		else
			return false;
	}

	bool KeyLayout::justReleased(const KeyAction& a)
	{
		if(keyJustReleased[static_cast<int>(a)])
		{
			keyJustReleased[static_cast<int>(a)] = false;
			return true;
		}
		else
			return false;
	}

	void KeyLayout::keyPress(QKeyEvent* event)
	{
		if(!event->isAutoRepeat())
		{
			KeyAction a = corresponding(static_cast<Qt::Key>(event->key()));

			std::cout << "Event : Key pressed" << std::endl;

			if(a!=NoAction)
			{
				keyPressed[static_cast<int>(a)] = true;
				keyJustPressed[static_cast<int>(a)] = true;
				keyJustReleased[static_cast<int>(a)] = false;
			}
			else
				std::cerr << "Warning : Key not assiociated" << std::endl;
		}
	}

	void KeyLayout::keyRelease(QKeyEvent* event)
	{
		if(!event->isAutoRepeat())
		{
			KeyAction a = corresponding(static_cast<Qt::Key>(event->key()));

			std::cout << "Event : Key released" << std::endl;

			if(a!=NoAction)
			{
				keyPressed[static_cast<int>(a)] = false;
				keyJustPressed[static_cast<int>(a)] = false;
				keyJustReleased[static_cast<int>(a)] = true;
			}
			else
				std::cerr << "Warning : Key not assiociated" << std::endl;
		}
	}
