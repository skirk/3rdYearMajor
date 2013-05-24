/*! \author Tuomo Rinne
 *  \version 0.1
 *  \date 05/05/2013 
 *  \class XSLTprocessor
 *  \brief XSLTprocessor processes the xml into a other forms depending on the stylesheets given
 */

#ifndef _XSLTPROCESSOR_H_
#define _XSLTPROCESSOR_H_

#include <string>

class XSLTprocessor
{
	public:
		
		/*! \brief Apply a stylesheet to XML document
		 *
		 * \param _stylesheet the stylesheet to apply
		 * \param _file the target XML file
		 * \param _output file to save the output
		 */
		void applyStylesheetToXML(
				const std::string &_stylesheet,
				const std::string &_file,
				const std::string &_output
				);
};

#endif
