#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include <string>
#include <vector>
#include "Enum.h"

class Slot;
class Node;
class Graph;

typedef std::vector<Node*> HeaderStruct;

class Context 
{
	private:
		Graph *m_current;

		//! \brief the values coming into the from openGL or previous shader stage
		HeaderStruct m_globalinputs;
		//! \brief the values going outside of the shader
		HeaderStruct m_globaloutputs;
	public:
		Context();

		/* \brief Change context to the specified graph
		 *
		 * \param _name the name of the graph to go down into
		 */
		void goDownALevel(const std::string &_name);

		/* \brief Change context to the parent of the current node
		 *
		 * Go to the parent graph of the current context
		 */
		void goUpALevel();
		/* \brief Connect two slots together
		 *
		 * \param _lhs left hand side Slot
		 * \param _rhs right hand side Slot
		 */
		void connectSlots(const std::string &_lhs, const std::string &_rhs);
		/* \brief Disconnect slot
		 *
		 * \param _input name of the input to remove connection from
		 */
		void disconnectSlots(const std::string &_input);

		void addInputSlot(const std::string &_name, const SVariable &_var);
		/* \brief Add a output slot to the graph
		 *
		 */
		void addOutputSlot(const std::string &_name,const SVariable &_var);
		void addNode(const std::string &_name);
		void writeNode(const std::string&);
		Graph *getCurrent() const;
		void printDB() const;
		HeaderStruct *getGlobalInputs();
		HeaderStruct *getGlobalOutputs();
	private:

		Slot *getSlotFromString(const std::string &_name);
		Node *getNodeFromString(const std::string &_name);
		bool castAndConnect(Slot *input, Slot *output);

};


#endif
