#ifndef _UTIL_H_
#define _UTIL_H_

class Node;
class Graph;
class Slot;

namespace Utilities
{
	Node *findNode(Graph *_g, const std::string &_name);
	Slot *findSlot(Graph *_g, const std::string &_name);
}


#endif




