#include <unibus/radixtrie>
#include <unibus/req>
#include <unibus/res>

namespace unibus {

	namespace Radix {

		void N::call(std::istream& in, std::ostream& out) {
			if(worker_func != nullptr) {
				Req req{header, in};
				Res res{out};
				worker_func(req, res);
			}

			for(auto t: targets)
				if(t.first == in.peek())
					t.second->call(in, out);
		}

		void N::use(const std::initializer_list<char> &header, void (*worker_func)(Req& req, Res& res)) {
			std::unordered_map<char, std::shared_ptr<Radix::N>> *par = &targets;
			std::shared_ptr<Radix::N> last_node;
			for(char c: header) {
				last_node = (*par)[c];
				if(last_node == nullptr)
					last_node = (*par)[c] = std::make_shared<Radix::N>();
				par = &last_node->targets;
			}
			last_node->header = header;
			last_node->worker_func = worker_func;
		}
	}

}
