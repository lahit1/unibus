#include <unibus/req>
#include <unibus/headers>

namespace unibus {


bool Req::buffer(void **buff) {
	if(in.peek() != headers::buffer)
		return false;
	in.ignore();
	int size;
	in >> size;
	char *_buff = new char[size];
	in.read(_buff, size);
	*buff = static_cast<char*>(_buff);
	return true;
}
bool Req::string(std::string *s) {
	if(in.peek() != headers::string)
		return false;
	in.ignore();
	int size;
	in >> size;
	char *buff = new char[size];
	s->assign(buff, size);
	return true;
}

bool Req::json(nlohmann::json *o) {
	if(in.peek() != headers::json)
		return false;
	in.ignore();
	*o = nlohmann::json::parse(in);
	return true;
}

}
