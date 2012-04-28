#ifndef __MT4_NETWORK__
#define __MT4_NETWORK__

	#include <iostream>
	#include <vector>
	#include <QHostAddress>
	#include <QUdpSocket>

	class Client
	{
		private :
			QHostAddress address;
			quint16 port;
		public :
			Client(const QHostAddress& adr, quint16 p);

			void sendMessage(const std::string& msg, QUdpSocket& socket);

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

		public :
			Connection(quint16 port, const QHostAddress& serverAdr, quint16 serverP);

			void sendMessage(const std::string& msg);

		public slots :
			void readPendingDatagrams(void);
	};

#endif
