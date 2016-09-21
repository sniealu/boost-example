#include <boost/graph/adjacency_list.hpp>
#include <boost/utility/string_ref.hpp>
#include <boost/graph/graphviz.hpp>
#include <string>

typedef std::string vertex_t;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, vertex_t> graph_type;
static const std::size_t vertex_count = 5;

typedef boost::graph_traits<graph_type>::vertex_descriptor descriptor_t;

template <class GraphT>
void find_and_print(const GraphT& g, boost::string_ref name) {
    typedef typename boost::graph_traits<graph_type>::vertex_iterator vert_it_t;
	vert_it_t it, end;
	boost::tie(it,end) = boost::vertices(g);
	typedef boost::graph_traits<graph_type>::vertex_descriptor desc_t;
	for(; it!=end; ++it) {
	    desc_t desc = *it;
		if(boost::get(boost::vertex_bundle,g)[desc] == name.data()) {
		    break;
		}
	}
	assert( it != end);
	std::cout << name << '\n';
} // find_and_print 

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


std::ostream& operator<<(std::ostream& out, const graph_type& g) {
    detail::vertex_writer<graph_type> vw(g);
	boost::write_graphviz(out, g, vw);
	return out;
}



int main()
{
    graph_type graph;
	graph.m_vertices.reserve(vertex_count);

	descriptor_t cpp = boost::add_vertex(vertex_t("C++"), graph);
	descriptor_t stl = boost::add_vertex(vertex_t("stl"), graph);
	descriptor_t boost = boost::add_vertex(vertex_t("boost"), graph);
	descriptor_t guru = boost::add_vertex(vertex_t("guru"), graph);
	descriptor_t ansic = boost::add_vertex(vertex_t("ansic"), graph);

	boost::add_edge(cpp, stl, graph);
	boost::add_edge(stl, boost, graph);
	boost::add_edge(boost, guru, graph);
	boost::add_edge(ansic, guru, graph);

    find_and_print(graph,"C++");
	std::cout<<graph;
    return 0;
}
