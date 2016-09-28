/*
 * pssxml2xml.cpp
 *
 *  Created on: Sep 13, 2016
 *      Author: ballance
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "PSSXmlValidator.h"
#include "PSIFileUtils.h"
#include "PSI2XML.h"
#include "XML2PSI.h"
#include "api_impl/ModelImpl.h"

using namespace psi;
using namespace psi::apps;

int main(int argc, char **argv) {
	const char *outfile = 0;
	const char *file = 0;

	// First, process arguments
	for (int i=1; i<argc; i++) {
		if (argv[i][0] == '-') {
			if (!strcmp(argv[i], "-o")) {
				i++;
				outfile = argv[i];
			} else {
				fprintf(stdout, "Error: unknown option %s\n", argv[i]);
				exit(1);
			}
		} else {
			// non-option
			if (!file) {
				file = argv[i];
			} else {
				fprintf(stdout, "Error: multiple file specified (%s)\n", argv[i]);
				exit(1);
			}
		}
	}

	if (!file) {
		fprintf(stdout, "Error: no input file specified\n");
		exit(1);
	}

	if (!outfile) {
		fprintf(stdout, "Error: no output file specified\n");
		exit(1);
	}

	fprintf(stdout, "==> pssxml2xml::validate\n");
	fflush(stdout);
	// First, validate the file
	PSSXmlValidator *validator = new PSSXmlValidator();
	FILE *in = fopen(file, "r");
	if (!in) {
		fprintf(stdout, "Error: failed to open input file %s\n", file);
		exit(1);
	}
	std::string in_c = PSIFileUtils::read(in);

	fclose(in);

	if (!validator->validate(in_c, file)) {
		fprintf(stdout, "Error: validation of %s failed\n", file);
		exit(1);
	}
	delete validator;

	fprintf(stdout, "<== pssxml2xml::validate\n");
	fflush(stdout);

	// Run XML2PSI
	ModelImpl *model = new ModelImpl();
	XML2PSI *xml2psi = new XML2PSI();
	xml2psi->process(in_c, model);

	fprintf(stdout, "==> pssxml2xml::psi2xml\n");
	fflush(stdout);
	PSI2XML *psi2xml = new PSI2XML();
	std::string out_c = psi2xml->traverse(model);

	fprintf(stdout, "<== pssxml2xml::psi2xml\n");
	fflush(stdout);

	FILE *out;

	// Finally, write-back the output
	if (!strcmp(outfile, "-")) {
		out = stdout;
	} else {
		out = fopen(outfile, "w");

		if (!out) {
			fprintf(stdout, "Error: failed to open output file %s\n", outfile);
			exit(1);
		}
	}

	fwrite(out_c.c_str(), 1, out_c.size(), out);

	// Only close if we're not directing to stdout
	if (strcmp(outfile, "-") != 0) {
		fclose(out);
	}

	delete xml2psi;
	delete psi2xml;
	delete model;

	fprintf(stdout, "<== pssxml2xml\n");
	fflush(stdout);
	return 0;
}



