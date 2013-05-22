#include "Node.h"
#include "Graph.h"
#include "Util.h"
#include <boost/tokenizer.hpp>

Node *Utilities::findNode(Graph *_g, const std::string &_name)
{
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(".");
	tokenizer tok(_name, sep);
	tokenizer::iterator beg = tok.begin();
	tokenizer::iterator beg1 = beg;

	int i = 0;
	//this solution could be done a bit better
	for(; beg != tok.end(); beg++)
	{
		i++;
	}
	if(i==2)
	{
		std::string node = *beg1;
		std::string id   = *++beg1;
		int i = std::stoi(id);
		Node *n = _g->getNode(node, i);
		std::cout<<"found node "<<n->getName()<<'\n';
		return n;
	}
	else
	{
		std::cout<<"Node path is wrong\n";
		return new Node;
	}
}


Slot *Utilities::findSlot(Graph *_g, const std::string &_name)
{
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(".");
	tokenizer tok(_name, sep);
	tokenizer::iterator beg = tok.begin();
	tokenizer::iterator beg1 = beg;

	int i = 0;
	//this solution could be done a bit better
	for(; beg != tok.end(); beg++)
	{
		i++;
	}
	//the slot has to be either graphs or some of its slots
	//the graph requires one token , where the node slot path requires 3
	if(i == 1)
	{
		//when the context is inside the node the desired node is the opposite slot
		std::string slotname = *beg1;
		return _g->get(slotname);
	}
	else if(i == 3)
	{
		std::string node = *beg1;
		std::string id   = *++beg1;
		std::string slot = *++beg1;
		int i = std::stoi(id);
		Node *n = _g->getNode(node, i);
		if(n->getName()=="empty")
		{
			if(_g->getName() == node && _g->getID() == id)
			{
				std::cout<<"Graph itself "<<node<<"\n";
				return _g->get(slot);
			}
			std::cout<<"Couldn't find "<<node<<"\n";
			return new Slot;
		}
		return n->get(slot);
	}
	else
	{
		std::cout<<"Slot path is wrong\n";
		return new Slot;
	}
}
