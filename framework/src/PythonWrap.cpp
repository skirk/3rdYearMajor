#include "NodeNetwork.h"
#include "Node.h"
#include "DataBase.h"
#include "NodeFactory.h"
#include <boost/python.hpp>


std::ostream &operator<<(std::ostream &os, const Node &_n)
{
	os << _n.getName();
	return os;
}

struct convert_node_ptr
{
	static PyObject* convert(Node * const &_n)
	{
		return boost::python::incref(boost::python::object(*_n).ptr());
	}
};


BOOST_PYTHON_MODULE(Framework)
{
	using namespace boost::python;

	
	class_<NodeFactory>("NodeFactory")
		.def("getDB", &NodeFactory::getDB,
				return_value_policy<reference_existing_object>())
		;
	class_<DataBase>("DataBase")
		.def("getNode", &DataBase::getNode,
				return_value_policy<reference_existing_object>())
		.def("__iter__", range(&DataBase::begin, &DataBase::end));
	;
	class_<Node>("Node", no_init)
		.def(self_ns::str(self))
		;
	class_<NodeNetwork, bases<Node>>("NodeNetwork", no_init)
		.def(init<DataBase*>())
		//.def("connectNodes", &NodeNetwork::connectNodes)
		//.def("addNode", &NodeNetwork::addNode)
		;
	to_python_converter<Node *, convert_node_ptr>();
}

