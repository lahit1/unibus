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

	void T::use(std::initializer_list<char> header, void (*worker_func)(Req req, Res res)) {
		std::unordered_map<char, std::shared_ptr<Radix::N>> *par = &rad_root.targets;
		std::shared_ptr<Radix::N> last_node;
		for(char c: header) {
			last_node = (*par)[c];
			if(last_node == nullptr)
				last_node = (*par)[c] = std::make_shared<Radix::N>();
			par = &last_node->targets;
		}
		last_node->worker_func = worker_func;
	}
}
