#include "Graph.h"
#include "Node.h"
#include "DataBase.h"
#include "Exporter.h"
#include "NodeFactory.h"
#include <boost/python.hpp>


std::ostream &operator<<(std::ostream &os, const Node &_n)
{
	os << _n.getName();
	return os;
}

std::ostream &operator<<(std::ostream &os, const BaseSlot &_s)
{
	if(_s.isInput())
		os << _s.getName() << " INPUT";
	else
		os << _s.getName() << " OUTPUT";
	return os;
}

struct convert_node_ptr
{
	static PyObject* convert(Node * const &_n)
	{
		return boost::python::incref(boost::python::object(*_n).ptr());
	}
};
struct convert_slot_ptr
{
	static PyObject* convert(BaseSlot * const &_s)
	{
		return boost::python::incref(boost::python::object(*_s).ptr());
	}
};

BOOST_PYTHON_MODULE(nodetype)
{
	using namespace boost::python;

	enum_<nodeType>("NodeType")
		.value("GRAPH", nodeType::GRAPH)
		.value("EXPRESSION", nodeType::EXPRESSION)
		.value("STATE", nodeType::STATE)
		.export_values()
		;
}

DataBase *pointer (DataBase& p)
{
	return &p;
}

BOOST_PYTHON_MODULE(Framework)
{
	using namespace boost::python;

	class_<NodeFactory>("NodeFactory")
		.def("createNode", &NodeFactory::createNode,
				return_value_policy<reference_existing_object>())
		.def("getDB", &NodeFactory::getDB,
				return_value_policy<reference_existing_object>())
		;
	class_<DataBase>("DataBase")
		.def("getNode", &DataBase::get,
				return_value_policy<reference_existing_object>())
		//.def("__iter__", range(&Container<Node>::begin, &Container<Node>::end));
		.def("__iter__", iterator<DataBase>())
		;
	class_<Node>("Node", no_init)
		.def(self_ns::str(self))
		.def("__iter__", iterator<Node>())
		.def("write", &Node::write)
	;
	class_<Graph, bases<Node>>("Graph", no_init)
		.def(init<DataBase*>())
		.def("connectNodes", &Graph::connectNodes)
		.def("addNode", &Graph::addNode)
		;
	class_<BaseSlot>("Slot", no_init)
		.def(self_ns::str(self))
		;
	class_<XMLExporter>("Exporter")
		.def("writeNode", &XMLExporter::writeNode)
		;
	to_python_converter<Node *, convert_node_ptr>();
	to_python_converter<BaseSlot *, convert_slot_ptr>();

	initnodetype();
}

