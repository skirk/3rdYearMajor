#include "Graph.h"
#include "Node.h"
#include "DataBase.h"
#include "Context.h"
#include "Exporter.h"
#include "NodeFactory.h"
#include "XSLTprocessor.h"
#include <memory>
#include <boost/python.hpp>


std::ostream &operator<<(std::ostream &os, const Node &_n)
{
	os << _n.getName();
	return os;
}

std::ostream &operator<<(std::ostream &os, const Slot &_s)
{
	std::cout<<_s.isInput()<<'\n';
	if(_s.isInput())
		//os << _s.getName() << " INPUT";
		os << _s.getName()<<" "<<static_cast<int>(_s.getType()) << " INPUT";
	else
		os << _s.getName()<<" "<<static_cast<int>(_s.getType()) << " OUTPUT";
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
	static PyObject* convert(Slot * const &_s)
	{
		return boost::python::incref(boost::python::object(*_s).ptr());
	}
};

BOOST_PYTHON_MODULE(nodetype)
{
	using namespace boost::python;

	enum_<nodeType>("NodeType")
		.value("GRAPH", nodeType::GRAPH)
		.value("OPERATOR", nodeType::OPERATOR)
		.value("FUNCTION", nodeType::FUNCTION)
		.value("STATE", nodeType::STATE)
		.export_values()
		;
}

BOOST_PYTHON_MODULE(slotvariable)
{
	using namespace boost::python;

	enum_<SVariable>("SlotVariable")
		.value("BOOLEAN", SVariable::BOOLEAN)
		.value("INT", SVariable::INT)
		.value("FLOAT", SVariable::FLOAT)
		.value("VEC3", SVariable::VEC3)
		.value("VEC4", SVariable::VEC4)
		.value("MAT3", SVariable::MAT3)
		.value("MAT4", SVariable::MAT4)
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

	class_<DataBase>("DataBase")
		//.def("__iter__", range(&Container<Node>::begin, &Container<Node>::end));
		.def("__iter__", iterator<DataBase>())
		;
	class_<Node, boost::noncopyable>("Node", no_init)
		//.def(self_ns::str(self))
		//.def("__iter__", iterator<Node>())
		;
	class_<Graph, bases<Node>, boost::noncopyable>("Graph", no_init)
		//.def(init<DataBase*>())
		//.def("connectSlots", &Graph::connectSlots)
		//.def("removeConnection", &Graph::removeConnection)
		//.def("addNode", &Graph::addNode)
		//.def("addInputSlot", &Graph::addInputSlot)
		//.def("addOutputSlot", &Graph::addOutputSlot)
		;
	class_<Slot, boost::noncopyable>("Slot", no_init)
		.def(self_ns::str(self))
		;
	class_<Context>("Context")
		.def("connectSlots", &Context::connectSlots)
		.def("disconnectSlots", &Context::disconnectSlots)
		.def("addInputSlot", &Context::addInputSlot)
		.def("addOutputSlot", &Context::addOutputSlot)
		.def("goUpALevel", &Context::goUpALevel)
		.def("goDownALevel", &Context::goDownALevel)
		.def("addNode", &Context::addNode)
		.def("writeNode", &Context::writeCurrentNode)
		.def("writeShader", &Context::writeShader)
		.def("printDB", &Context::printDB)
		.def("changeConstValue", &Context::changeConstValue)
		;


	class_<XSLTprocessor>("processor")
		.def("process", &XSLTprocessor::applyStylesheetToXML)
		;
	to_python_converter<Node *, convert_node_ptr>();
	to_python_converter<Slot *, convert_slot_ptr>();

	initnodetype();
	initslotvariable();
}

