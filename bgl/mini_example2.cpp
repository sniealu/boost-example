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
			template <class vertex_descriptor>
			void operator() (std::ostream& out, const vertex_descriptor& d) const {
			    out << " [label=\""
				    << boost::get(boost::vertex_bundle, g_)[d]
					<< "\"]";
			}
	}; // vertex_writer
} //namespace detail

template <class GraphT>
void print(const GraphT& g) {
    typedef typename boost::graph_traits<boost::SampleGraph::Graph>::vertex_iterator vert_it_t;
	vert_it_t it, end;
	boost::tie(it,end) = boost::vertices(g);
	typedef boost::graph_traits<boost::SampleGraph::Graph>::vertex_descriptor desc_t;
	for(; it!=end; ++it) {
	    desc_t desc = *it;
		std::cout<<boost::get(boost::vertex_bundle,g)[desc];
	}
}


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
  print(g);
  std::cout<<g; 
  return 0;
}

