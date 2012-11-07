#include <time.h>

template<unsigned int TYPE, typename T>
class Message {
public:
	Message(const T& sender, const T& receiver);
	~Message();

	T get_reciever() { return receiver; }
	T get_sender() { return sender; }

	unsigned int get_age() { return ((clock() - creation_clock) * 1000) / CLOCKS_PER_SEC; }
	unsigned int get_type() { return TYPE; }	// essentially type is the message
private:
	T * sender;
	T * receiver;

	clock_t creation_clock;
};

template<unsigned int TYPE, typename T>
Message<TYPE, T>(const T& sender, const T& receiver) 
	: sender(&sender), receiver(&receiver), creation_clock(clock()) {

}