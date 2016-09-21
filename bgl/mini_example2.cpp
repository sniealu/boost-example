#include "successive_shortest_path_nonnegative_weights.hpp"
#include "find_flow_cost.hpp"

#include "min_cost_max_flow_utils.hpp"
#include <boost/graph/graphviz.hpp>


namespace detail {
    template <class GraphT>
	class vertex_writer {
	    const GraphT& g_;
		public:
		    explicit vertex_writer(const GraphT& g) : g_(g) {}
			template <class VertexDescriptorT>
			void operator() (std::ostream& out, const VertexDescriptorT& d) const {
			    out << " [label=\""
				    << boost::get(boost::vertex_bundle, g_)[d]
					<< "\"]";
			}
	}; // vertex_writer
} //namespace detail


std::ostream& operator<<(std::ostream& out, const boost::SampleGraph::Graph& g) {
    detail::vertex_writer<boost::SampleGraph::Graph> vw(g);
	boost::write_graphviz(out, g, vw);
	return out;
}


int main() {
  boost::SampleGraph::vertex_descriptor s,t;
  boost::SampleGraph::Graph g; 
  boost::SampleGraph::getSampleGraph(g, s, t);

  boost::successive_shortest_path_nonnegative_weights(g, s, t);

  int cost =  boost::find_flow_cost(g);
  assert(cost == 29);
  std::cout<<g; 
  return 0;
}

