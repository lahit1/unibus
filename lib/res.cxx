#include <unibus/res>

namespace unibus {

bool Res::buffer(const void **buff, int size) {
	out << static_cast<char>(headers::buffer);
	out << size;
	out << *buff;
	return true;
}

bool Res::string(const std::string *s) {
	out << static_cast<char>(headers::buffer);
	out << s->size();
	out << s->c_str();
	return true;
}

bool Res::json(const nlohmann::json *o) {
	out << static_cast<char>(headers::buffer);
	out << *o;
	return true;
}

}
