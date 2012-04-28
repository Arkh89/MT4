#include "network.hpp"

	Message::Message(void)
	 : msg(), cursor(0)
	{ }

	Message::Message(const QByteArray& m)
	 : msg(m), cursor(0)
	{ }

	Message::Message(const Message& m)
	 : msg(m.msg), cursor(0)
	{ }

	unsigned int Message::length(void) const
	{
		return msg.length();
	}

	void Message::push(Vect2D& v)
	{
		push(v.getX());
		push(v.getY());
	}

	void Message::push(Segment& v)
	{
		push(v.getX1());
		push(v.getY1());
		push(v.getX2());
		push(v.getY2());
	}

	const QByteArray Message::getArray(void) const
	{
		return msg;
	}

	Vect2D Message::pullVect2D(void)
	{
		Vect2D v;

		v.x() = pull<Vect2D::Type>();
		v.y() = pull<Vect2D::Type>();

		return v;
	}

	Segment Message::pullSegment(void)
	{
		Vect2D v1, v2;

		v1 = pullVect2D();
		v2 = pullVect2D();

		return Segment(v1, v2);
	}

	Client::Client(const QHostAddress& adr, quint16 p)
	 : address(adr), port(p)
	{

	}

	void Client::sendMessage(const std::string& msg, QUdpSocket& socket)
	{
		socket.writeDatagram( msg.c_str(), msg.length(), address, port );
	}

	void Client::sendMessage(const Message& msg, QUdpSocket& socket)
	{
		socket.writeDatagram( msg.getArray(), msg.length(), address, port );
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

	void Server::broadcast(const Message& msg)
	{
		for(std::vector<Client>::iterator it=clients.begin(); it!=clients.end(); it++)
			(*it).sendMessage(msg,socket);
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
				std::cout << "       : " << sender.toString().toUtf8().constData() << " : " << senderPort << std::endl;
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

	void Connection::sendMessage(const Message& msg)
	{
		socket.writeDatagram( msg.getArray(), msg.length(), serverAddress, serverPort);
	}

	unsigned int Connection::getNumMessages(void) const
	{
		return messages.size();
	}

	bool Connection::hasMessages(void) const
	{
		return !messages.empty();
	}

	Connection::MsgIterator Connection::listBegin(void)
	{
		return messages.begin();
	}

	Connection::MsgIterator Connection::listEnd(void)
	{
		return messages.end();
	}

	Message Connection::popFront(void)
	{
		Message m = messages.front();
		messages.pop_front();
		return m;
	}

	Message Connection::popBack(void)
	{
		Message m = messages.back();
		messages.pop_back();
		return m;
	}

	void Connection::clearMessages(void)
	{
		messages.clear();
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

			//std::cout << "Connection : Received reponse from server..." << std::endl;
			//std::cout << "Packet : " << std::string(datagram.constData()) << std::endl;
			//std::cout << "Packet length : " << datagram.length() << std::endl;
			messages.push_back(Message(datagram));
		}
	}

