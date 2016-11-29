/*
 * validatepssxml.cpp
 *
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
 *
 * Licensed under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in
 *  compliance with the License.  You may obtain a copy of
 *  the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
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



