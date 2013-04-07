#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//provides an API for the actual processing
#include <libxslt/transform.h>
//generic utility functions
#include <libxslt/xsltutils.h>

//defined int libxml/globals.h
extern int xmlLoadExtDtdDefaultValue;

static void usage(const char *name) {
	printf("Usage %s [options] stylesheet [stylesheet ...] file [file ...]\n", name);
	printf("	--out file: send output to file\n");
	printf("	--param name value: pass a (parameter, value) pair\n");
}

int main(int argc, char **argv) {
	//integer is an index used to iterate over the program arguments
	int arg_indx;
	//to collect XSLT parameters
	const char *params[16 + 1];
	int params_indx = 0;
	int stylesheet_indx = 0;
	//index to iterate over files to be processed
	int file_indx = 0;
	int i, j, k;
	//value the program returns to the operating system
	//standard output in most cases
	FILE *output_file = stdout;
	//libxslt stores stylesheets in xsltStylesheet structures
	// xsltStylesheetPtr is a pointer to that
	xsltStylesheetPtr *stylesheets =
		//calloc allocates memory for an array of identical items
		(xsltStylesheetPtr *) calloc(argc, sizeof(xsltStylesheetPtr));
	//cast type to  xmlDocPtr*
	xmlDocPtr *files = (xmlDocPtr *) calloc(argc, sizeof(xmlDocPtr));
	xmlDocPtr doc, res;
	int return_value=0;

		if (argc <= 1) {
			usage(argv[0]);
			return_value=1;
			goto finish;
		}

	/* collect arguments */
	for (arg_indx = 1; arg_indx; arg_indx++) {
		if (argv[arg_indx][0] != '-')
			break;
		if ((!strcmp(argv[arg_indx], "-param")) 
				|| (!strcmp(argv[arg_indx], "--param")))	{
			arg_indx++;
			params[params_indx++] = argv[arg_indx++];
			params[params_indx++] = argv[arg_indx];
			if (params_indx >= 16) {
				fprintf(stderr, "too many params\n");
				return_value = 1;
				goto finish;
			}
		} else if ((!strcmp(argv[arg_indx], "-o"))
				|| (!strcmp(argv[arg_indx], "--out"))) {
			arg_indx++;
			//set output file
			output_file = fopen(argv[arg_indx], "w");
			// unknown argument
		} else {
			fprintf(stderr, "Unknown option %s\n", argv[arg_indx]);
			usage(argv[0]);
			return_value = 1;
			goto finish;
		}
	}
	params[params_indx] = 0;

	// parsing
	/* collect and parse stylesheets and files to be transformed */
	for (; arg_indx < argc; arg_indx++) {
		char *argument = 
			(char *) malloc(sizeof(char) * (strlen(argv[arg_indx]) + 1));
		strcpy(argument, argv[arg_indx]);
		if (strtok(argument, ".")) {
			//strtok split str into tokens
			char * suffix = strtok(0, ".");
			if (suffix && !strcmp(suffix, "xsl")) {
				stylesheets[stylesheet_indx++] =
					//parses the stylesheet
					//xmlChar = typedef of unsigned char
					xsltParseStylesheetFile((const xmlChar *)argv[arg_indx]);;
			} else {
				files[file_indx++] = xmlParseFile(argv[arg_indx]);
			}
		} else {
			files[file_indx++] = xmlParseFile(argv[arg_indx]);
		}
		//deallocates memory
		free(argument);
	}


	//file processing

	for(i = 0; files[i]; i++) {
		doc = files[i];
		res = doc;
		for (j= 0; stylesheets[j]; j++) {
			res = xsltApplyStylesheet(stylesheets[j], doc, params);
			xmlFreeDoc(doc);
			doc = res;
		}
		if (stylesheets[0]) {
			xsltSaveResultToFile(output_file, res, stylesheets[j-1]);
		} else {
			xmlDocDump(output_file, res);
		}
		xmlFreeDoc(res);
	}

	fclose(output_file);

	for(k=0; stylesheets[k]; k++) {
		xsltFreeStylesheet(stylesheets[k]);
	}

	xsltCleanupGlobals();
	xmlCleanupParser();

finish:
	free(stylesheets);
	free(files);
	return (return_value);
}
