#include "XSLTprocessor.h"

#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include <stdio.h>

void XSLTprocessor::applyStylesheetToXML(const std::string &_stylesheet, const std::string &_file, const std::string &_output)
{
	FILE * pfile;

	pfile = fopen(_output.c_str(), "w");
	if (pfile == NULL) perror ("Error opening file");
	else
	{
		xsltStylesheetPtr stylesheet;
		xmlDocPtr xml, res;

		stylesheet = xsltParseStylesheetFile((const xmlChar *)_stylesheet.c_str());
		xml = xmlParseFile(_file.c_str());

		res = xsltApplyStylesheet(stylesheet, xml, 0);

		xsltSaveResultToFile(pfile, res, stylesheet);

		fclose (pfile);
	}

}
