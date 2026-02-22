#include <unibus/unibus>

namespace unibus {

	std::shared_ptr<T> T::mk() {
		return std::shared_ptr<T>(new T());
	}

	std::shared_ptr<T> T::mk(std::shared_ptr<std::istream> in, std::shared_ptr<std::ostream> out) {
		std::shared_ptr<T> p(new T());
		p->in = in;
		p->out = out;

		return p;
	}

	void T::use(const std::initializer_list<char> &header, bool (*worker_func)(Req& req, Res& res)) {
		std::string headerStr(header.begin(), header.end());
		rad_root.insert(headerStr, worker_func);
	}
}
