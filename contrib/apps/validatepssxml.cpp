/*
 * validatepssxml.cpp
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
	const char *file = 0;

	// First, process arguments
	for (int i=1; i<argc; i++) {
		if (argv[i][0] == '-') {
			{
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

	return 0;
}



