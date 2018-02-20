//
// Created by gil on 19/02/18.
//

#define BOOST_TEST_MODULE My Test 1
#include <boost/test/included/unit_test.hpp>
#include "chain.h"
#include "exception.h"

BOOST_AUTO_TEST_CASE(first_test)
{
    try {
        auto *testObject = new AntibodyChainCPP;
    }

    catch (ModuleImportException &e) {
        BOOST_FAIL("Failed to initialise AntibodyChainCPP object!");
    }
}
