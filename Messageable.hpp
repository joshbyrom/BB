#include "Message.hpp"

template<typename T>
class Messageable {
public:
	virtual bool receive_message(Message<int, T> message) = {0};
private:
};
