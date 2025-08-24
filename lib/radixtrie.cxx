#include <unibus/radixtrie>
#include <unibus/req>
#include <unibus/res>

namespace unibus {

	namespace Radix {

		bool N::call(std::istream& in, std::ostream& out) {
			if(worker_func != nullptr) {
				Req req{header, in};
				Res res{out};
				if(!worker_func(req, res)) return false;
			}

			for(auto t: targets)
				if(t.first == in.peek())
					if(!t.second->call(in, out))
						return false;
			return true;
		}

		void N::use(const std::initializer_list<char> &header, bool (*worker_func)(Req& req, Res& res)) {
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
