#ifndef CONNECTION_INTERFACE_H
#define CONNECTION_INTERFACE_H

#include  <string>

namespace qffixlib {

	class ConnectionInterface {
	public:
		virtual ~ConnectionInterface() {};

		virtual void onConnected() = 0;
		virtual void onDisconnected() = 0;
		virtual void onMessage(char, int, const char*, std::size_t) = 0;

		virtual bool isConnected() = 0;
	};

}

#endif //CONNECTION_INTERFACE_H
