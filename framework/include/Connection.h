/*! \author Tuomo Rinne
 *  \version 0.1
 *  \date 29/04/2013 Initialisation 
 *  \class Connection
 *  \brief  Connection connects two slots together
 */
#ifndef _CONNECTION_H_
#define _CONNECTION_H_

class Slot;

class Connection
{
	private:
		Slot *m_lhs;
		Slot *m_rhs;

	public:
		Connection(Slot *_lhs, Slot *_rhs);
};

#endif