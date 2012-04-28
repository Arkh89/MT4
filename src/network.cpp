#include "network.hpp"

	Client::Client(const QHostAddress& adr, quint16 p)
	 : address(adr), port(p)
	{

	}

	void Client::sendMessage(const std::string& msg, QUdpSocket& socket)
	{
		socket.writeDatagram( msg.c_str(), msg.length(), address, port );
	}

	const QHostAddress& Client::getAdr(void) const
	{
		return address;
	}

	bool Client::isTheSame(const QHostAddress& adr, quint16 p)
	{
		return (adr==address) && (port==p);
	}

	Server::Server(quint16 port)
	 : socket(this)
	{
		socket.bind(port);

		connect(&socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
	}

	std::vector<Client>::iterator Server::getClient(const QHostAddress& adr, quint16 p)
	{
		std::vector<Client>::iterator it;

		for(it=clients.begin(); it!=clients.end(); it++)
		{
			if((*it).isTheSame(adr, p))
				return it;
		}

		return clients.end();
	}

	unsigned int Server::getNumClients(void) const
	{
		return clients.size();
	}

	void Server::broadcast(const std::string& str)
	{
		for(std::vector<Client>::iterator it=clients.begin(); it!=clients.end(); it++)
			(*it).sendMessage(str,socket);
	}

	void Server::readPendingDatagrams(void)
	{
		while(socket.hasPendingDatagrams())
		{
			QByteArray datagram;
			datagram.resize(socket.pendingDatagramSize());
			QHostAddress sender;
			quint16 senderPort;

			socket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

			// Check if the client is known
			std::vector<Client>::iterator it = getClient(sender, senderPort);

			// unknown
			if(it==clients.end())
			{
				std::cout << "Server : Registering a new client..." << std::endl;
				clients.push_back(Client(sender, senderPort));
				// Sending confirmation to client :
				clients.back().sendMessage("Hello Client!", socket);
			}
			else
			{
				std::cout << "Server : Received a paquet from a known client..." << std::endl;
			}
			std::cout << "Packet : " << std::string(datagram.constData()) << std::endl;
		}
	}


	Connection::Connection(quint16 port, const QHostAddress& serverAdr, quint16 serverP)
	 : serverAddress(serverAdr), serverPort(serverP), socket(this)
	{
		socket.bind(port);

		std::cout << "Server is : " << serverAddress.toString().toUtf8().constData() << " port : " << serverP << std::endl;

		connect(&socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
	}

	void Connection::sendMessage(const std::string& msg)
	{
		socket.writeDatagram( msg.c_str(), msg.length(), serverAddress, serverPort);
	}

	void Connection::readPendingDatagrams(void)
	{
		while(socket.hasPendingDatagrams())
		{
			QByteArray datagram;
			datagram.resize(socket.pendingDatagramSize());
			QHostAddress sender;
			quint16 senderPort;

			socket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);


			std::cout << "Connection : Received reponse from server..." << std::endl;
			std::cout << "Packet : " << std::string(datagram.constData()) << std::endl;
		}
	}

