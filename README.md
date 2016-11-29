Copyright 2016 Mentor Graphics Corporation
All Rights Reserved

THIS WORK CONTAINS TRADE SECRET AND PROPRIETARY
INFORMATION WHICH ARE THE PROPERTY OF MENTOR
GRAPHICS CORPORATION OR ITS LICENSORS AND IS
SUBJECT TO LICENSE TERMS.

# Procedural Specification Interface

The procedural specification interface (PSI) enables a Portable Stimulus Model to be
declared using a procedural programming language. There are two core elements to the 
procedural specification interface: 
* A C++ class library with constructs that enable creation of a PSS model
* A C++ API, targeted at tool vendors, that allows specification and introspection

This collection of source files provides the following:
* Header files for the class library and C++ API. The constructs in these header 
  files are intended to be part of the standard.
* A reference implementation of the class library and C++ API. The constructs 
  in these files are not intended to be part of the standard.
* Examples and tests of the class library and API. 
* Utilities built on top of the APIs. These utilities are not intended to
  be part of the standard.


# Directory Structure

* contrib - The contrib directory contains an implementation of the class library,
            C++ API, and utilities used by the tests
* doc     - The doc directory contains scripts used for generating documentation
* include - The include directory contains header files with the public interface
            to the class library and C++ API.
* schema  - The schema directory contains an XML schema used by the tests to
            validate the procedurally-constructed Portable Stimulus Specification.
* tests   - The tests directory contains test code, scripts, and reference files
            for testing the public header files and contributed implementation.


# Tests
Please see the README.md file, in the tests subdirectory, for more information
on how to run the tests.

# Tools
The following tools are used:
* A C++11-compliant GCC. GCC 5.4.0 was used during development of this code, though other compiler versions may work as well.
* GNU Make. GNU Make 4.2.1 was used during development of this code, though other versions may also work.
* Apache ANT. Apache ANT is used during the (optional) generation of API documentation. 
* Doxygen. Doxygen is used during the (optional) generation of API documentation.


