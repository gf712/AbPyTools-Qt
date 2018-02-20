//
// Created by gil on 19/02/18.
//

#define BOOST_TEST_MODULE AbPyToolsPyCInterface
#include <boost/test/included/unit_test.hpp>
#include "chain.h"
#include "exception.h"
#include <string>

BOOST_AUTO_TEST_CASE(ModuleImportTest)
{
    try {
        auto *testObject = new AntibodyChainCPP;
    }

    catch (ModuleImportException &e) {
        BOOST_FAIL("Failed to initialise AntibodyChainCPP object!");
    }
}

BOOST_AUTO_TEST_CASE(ChainImportTest)
{
    try {
        auto *testObject = new AntibodyChainCPP;
    }

    catch (ClassImportException &e) {
        BOOST_FAIL("Failed to initialise AntibodyChainCPP object!");
    }
}

BOOST_AUTO_TEST_CASE(NameTest)
{

    char name[5] = "test";
    char sequence[5] = "ABCD";
    char numbering_scheme[10] = "Chothia";

    auto *testObject = new AntibodyChainCPP(sequence, name, numbering_scheme);

    BOOST_TEST(testObject->getName() == name);

}
