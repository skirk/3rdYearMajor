#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include <string>
#include "Enum.h"

class Slot;
class Graph;

class Context 
{
	private:
		Graph *m_current;
	public:
		Context();
		void goDownALevel(Graph*);
		void goUpALevel();
		/* \brief Connect two slots together
		 *
		 * \param _lhs left hand side Slot
		 * \param _rhs right hand side Slot
		 */
		void connectSlots(const std::string &_lhs, const std::string &_rhs);
		void disconnectSlots(const std::string &_input);

		void addInputSlot(const std::string &_name, const SVariable &_var);
		/* \brief Add a output slot to the graph
		 *
		 */
		void addOutputSlot(const std::string &_name,const SVariable &_var);
		void addNode(const std::string &_name);
		void writeNode(const std::string&);
	private:
		Slot *getSlotFromString(const std::string &_name);
		bool castAndConnect(Slot *input, Slot *output);

};


#endif
