#ifndef __MT4_NETWORK__
#define __MT4_NETWORK__

	#include <iostream>
	#include <vector>
	#include <QHostAddress>
	#include <QUdpSocket>
	#include "vect2D.hpp"
	#include "segment.hpp"

	class Message
	{
		private :
			QByteArray msg;
			int cursor;
		public :
			Message(void);
			Message(const QByteArray& m);
			Message(const Message& m);

			unsigned int length(void) const;

			template<typename T>
			void push(const T& a)
			{
				msg.append(static_cast<const char*>(static_cast<const void*>(&a)), sizeof(T));
			}
			void push(Vect2D& v);
			void push(Segment& v);

			void resetCursor(void);

			template<typename T>
			T pull(void)
			{
				if(cursor+sizeof(T)>length())
					throw Exception("Message::pull - Requesting element outside of bounds.", __FILE__, __LINE__);
				T v;
				memcpy(static_cast<void*>(&v),msg.constData()+cursor,sizeof(T));
				cursor += sizeof(T);
				return v;
			}

			Vect2D pullVect2D(void);
			Segment pullSegment(void);

			const QByteArray getArray(void) const;
	};

	class Client
	{
		private :
			QHostAddress address;
			quint16 port;
		public :
			Client(const QHostAddress& adr, quint16 p);

			void sendMessage(const std::string& msg, QUdpSocket& socket);
			void sendMessage(const Message& msg, QUdpSocket& socket);

			const QHostAddress& getAdr(void) const;
			bool isTheSame(const QHostAddress& adr, quint16 p);
	};

	class Server : public QObject
	{
		Q_OBJECT

		private :
			std::vector<Client> clients;
			QUdpSocket socket;

			std::vector<Client>::iterator getClient(const QHostAddress& adr, quint16 p);

		public :
			Server(quint16 port);

			unsigned int getNumClients(void) const;
			void broadcast(const std::string& str);
			void broadcast(const Message& msg);

		public slots :
			void readPendingDatagrams(void);
	};

	class Connection : public QObject
	{
		Q_OBJECT

		private :
			QUdpSocket socket;
			QHostAddress serverAddress;
			quint16 serverPort;
			std::list<Message> messages;

		public :
			typedef std::list<Message>::iterator MsgIterator;
			Connection(quint16 port, const QHostAddress& serverAdr, quint16 serverP);

			void sendMessage(const std::string& msg);
			void sendMessage(const Message& msg);

			unsigned int getNumMessages(void) const;
			bool hasMessages(void) const;
			MsgIterator listBegin(void);
			MsgIterator listEnd(void);
			Message popFront(void);
			Message popBack(void);
			void clearMessages(void);

		public slots :
			void readPendingDatagrams(void);
	};

#endif
