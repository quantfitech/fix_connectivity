#ifndef CONNECTION_INTERFACE_H
#define CONNECTION_INTERFACE_H

#include  <string>
#include "fix_chars.hpp"


namespace qffixlib {

	class ConnectionInterface {
	public:
		virtual ~ConnectionInterface() {};

		virtual void onConnected() = 0;
		virtual void onDisconnected() = 0;
		virtual void onMessage(const MsgChars&, int, const char*, std::size_t) = 0;
	};

}

#endif //CONNECTION_INTERFACE_H
