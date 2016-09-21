#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <assert.h>


struct date {
    unsigned short year;
    unsigned short month;
    unsigned short day;
};

date parse_date_time1(const std::string& s) {
    using boost::spirit::qi::_1;
    using boost::spirit::qi::ushort_;
	using boost::spirit::qi::char_;
	using boost::phoenix::ref;
	date res;
	const char* first = s.data();
	const char* const end = first + s.size();
	bool success = boost::spirit::qi::parse(first, end,
	    ushort_[ ref(res.year) = _1 ] >> char('-')
	    >>ushort_[ ref(res.month) = _1 ] >> char('-')
	    >>ushort_[ ref(res.day) = _1 ]
	);
    if (!success || first != end) {
	    throw std::logic_error("Parsing failed");
	}
    return res;
}

int main() {
    date d = parse_date_time1("2012-12-31");
    printf("%d\n",d.year);
	printf("%d\n",d.month);
	printf("%d\n",d.day);
    assert(d.year == 2012);
    assert(d.month == 12);
    assert(d.day == 31);
}
