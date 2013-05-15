/*! \author Tuomo Rinne
 *  \version 0.1
 *  \date 09/05/2013 
 *  \class Context
 *  \brief Context is the currently selected Graph which also is the only modifyiable object at the time.
 *  Context works as a facade for multiple of classes 
 */


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
		/* \brief  Constructor
		 *
		 * \param _name the name of the graph to go down into
		 */
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
		/* \brief Add a input slot to the graph
		 *
		 * \param _name name of the output
		 * \param _var variable type
		 */
		void addInputSlot(const std::string &_name, const SVariable &_var);
		/* \brief Add a output slot to the graph
		 *
		 * \param _name name of the output
		 * \param _var variable type
		 */
		void addOutputSlot(const std::string &_name,const SVariable &_var);
		/* \brief Add a Node to the graph
		 *
		 * \param _name name of the node
		 */
		void addNode(const std::string &_name);
		/* \brief Write current Node to XML
		 *
		 * \param _location path of the output
		 */
		void writeNode(const std::string _location&);
		/* \brief Print all the DataBase nodes
		 */
		void printDB() const;
	private:

		/* \brief get Slot according to string
		 *
		 * \param _name path of the slot
		 */
		Slot *getSlotFromString(const std::string &_name);
		/* \brief get Node according to string
		 *
		 * \param _name path of the node
		 */
		Node *getNodeFromString(const std::string &_name);

};


#endif
