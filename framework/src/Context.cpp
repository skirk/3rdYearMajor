#include "Context.h"
#include "Util.h"
#include "Slot.h"
#include "Graph.h"
#include "NodeFactory.h"
#include "DataBase.h"
#include "Exporter.h"
#include "EnumParser.h"

#include <iostream>
#include <cstdlib>
#include <boost/tokenizer.hpp>

Context::Context()
{
	m_current = new Graph();
	m_current->setName("root");
	m_current->setParent(NULL);

	NodeFactory &fact = NodeFactory::getInstance();
	fact.InitDB();
}

void Context::connectSlots(const std::string &_lhs, const std::string &_rhs)
{

	Slot *lhs = Utilities::findSlot(m_current, _lhs);
	if(lhs->getName()=="empty")
	{
		std::cout<<"path "<<_lhs<<" is invalid or slot doesn't exist"<<'\n';
		return;
	}
	Slot *rhs = Utilities::findSlot(m_current, _rhs);
	if(rhs->getName()=="empty")
	{
		std::cout<<"path "<<_rhs<<" is invalid or slot doesn't exist"<<'\n';
		return;
	}
	//could do with better solution
	bool b_lhs, b_rhs;
	b_lhs = lhs->isInput();
	b_rhs = rhs->isInput();
	std::cout<<b_lhs<<b_rhs<<'\n';
	//check whether the context is the current node, if so reverse the slot 
	if( lhs->getParent() == m_current )
	{
		std::cout<<"lhs parent node match\n";
		b_lhs = !b_lhs;
	}
	if( rhs->getParent() == m_current )
	{
		std::cout<<"rhs parent node match\n";
		b_rhs = !b_rhs;
	}

	std::cout<<b_lhs<<b_rhs<<'\n';
	if( b_lhs ^ b_rhs )
	{
		if(b_lhs)
		{
			lhs->linkToSlot(rhs);
			return;
		}
		else if (b_rhs)
		{
			rhs->linkToSlot(lhs);
			return;
		}
	}
	else
	{
		std::cout<<"connection invalid\n";
		return;
	}
	std::cout<<"connection not formed\n";
}

void Context::disconnectSlots(const std::string &_inputSlot)
{
	Slot *input = Utilities::findSlot(m_current, _inputSlot);
	input->removeLink();
}

void Context::addInputSlot(const std::string &_name, const SVariable &_var)
{
	Slot* s = new Slot(m_current, _name.c_str(), Stype::INPUT, _var);
	if(m_current->getParent() == NULL)
	{
		m_globalinputs.push_back(s);
	}
	m_current->add(s);
}
void Context::addOutputSlot(const std::string &_name,  const SVariable &_var)
{
	Slot* s = new Slot(m_current, _name.c_str(), Stype::OUTPUT, _var);
	if(m_current->getParent() == NULL)
	{
		m_globaloutputs.push_back(s);
	}
	m_current->add(s);
}

void Context::addNode(const std::string &_name)
{
	NodeFactory &fact = NodeFactory::getInstance();
	Node *n =fact.createNode(_name, nodeType::GRAPH)->clone();
	n->setParent(m_current);
	m_current->addNode(n);
	if(n->getType() == nodeType::STATE)
	{
		std::cout<<"added to uniform inputs"<<'\n';
		m_uniforminputs.push_back(*n->begin());
	}
	if(n->getType() == nodeType::CONSTANT)
	{
		std::cout<<"inserting stuff\n";
		std::cout<<n<<'\n';
		for(Node::iterator it = n->begin(); it != n->end(); it++)
		{
			std::cout<<(*it)->getParent()<<'\n';

		}
		m_constants.insert(std::pair<Node*, std::string>(n, ""));
	}
}

void Context::writeCurrentNode(const std::string &_file)
{
	XMLExporter exp(&m_constants);
	exp.open(_file, "nodes");
	exp.write(m_current);
	exp.close();
}

void Context::writeShader(const std::string &_file)
{
	while(m_current->getParent() != NULL)
	{
		goUpALevel();
	}
	XMLExporter exp(&m_constants);
	exp.open(_file, "shader");
	exp.writeHeader(m_globalinputs, "import");
	exp.writeHeader(m_globaloutputs, "export");
	exp.writeHeader(m_uniforminputs, "uniforms");
	exp.write(m_current);
	exp.close();
}


void Context::goUpALevel()
{ 
	Graph *g = dynamic_cast<Graph*>(m_current->getParent());
	if(g == NULL)
	{
		std::cout<<"failed to go up\n";
		return;
	}
	m_current=g;
}

void Context::goDownALevel(const std::string &_name)
{
	Graph *g = dynamic_cast<Graph*>(Utilities::findNode(m_current, _name));
	std::cout<<"the downers name "<<g->getName()<<'\n';
	if(g->getName() == "empty")
	{
		std::cout<<"failed to go down\n";
		return;
	}
	std::cout<<"going down\n";
	m_current=g;
}

void Context::printDB() const
{
	NodeFactory &fact = NodeFactory::getInstance();
	DataBase *db = fact.getDB();
	Container<Node>::iterator it = db->begin();
	for(; it != db->end(); it++){
		std::cout<<(*it)->getName()<<'\n';
	}

}

void Context::changeConstValue(const std::string &_node, const std::string &_value)
{
	Node *n = Utilities::findNode(m_current, _node);
	ConstantMap::iterator it;
	it = m_constants.find(n);
	(*it).second = _value;
}

void Context::listCurrent()
{
	Graph::nodeiterator it = m_current->NodeBegin();
	Container<Slot>::iterator sit = m_current->begin();
	EnumParser<Stype> p;
	std::cout<<"Slots of the current context"<<'\n';
	for(; sit != m_current->end(); sit++){
		std::cout<<"\t"<<"slot: "<<(*sit)->getName()<<" type "<<p.lookupEnum((*sit)->getType())<<'\n';
	}
	std::cout<<"Nodes of the current context"<<'\n';
	for(; it != m_current->NodeEnd(); it++){
		std::cout<<'\t'<<"Name "<<(*it)->getName()<<" ID "<<(*it)->getID()<<'\n';
		for(sit=(*it)->begin(); sit != (*it)->end(); sit++){
			std::cout<<"\t\t"<<"slot: "<<(*sit)->getName()<<", type "<<p.lookupEnum((*sit)->getType())<<'\n';
		}
	}
}
