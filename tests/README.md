
# Running Tests

## Setup environment

% cd api_tests
% . ../simscripts/set_env.sh

Note: A recent GCC that supports C++-11 must be present in the path

## Run a single test

% runtest.pl -test tests/concept_walkthrough.f

## Run the test suite

% runtest.pl -testlist testlists/alltests.f

