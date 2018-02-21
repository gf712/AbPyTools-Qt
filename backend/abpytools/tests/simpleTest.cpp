//
// Created by gil on 19/02/18.
//

#define BOOST_TEST_MODULE AbPyToolsPyCInterface
#include "chain.h"
#include "exception.h"
#include <boost/test/included/unit_test.hpp>

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
    char numbering_scheme[10] = "chothia";

    auto *testObject = new AntibodyChainCPP(sequence, name, numbering_scheme);

    BOOST_TEST(testObject->getName() == name);
    BOOST_TEST(testObj    std::cout << testObject->getChain();
ect->getSequence() == sequence);
    BOOST_TEST(testObject->getNumberingScheme() == numbering_scheme);
}

BOOST_AUTO_TEST_CASE(LoadTest)
{

    char name[5] = "test";
    char sequence[200] = "QVQLQQWGAGLLKPSETLSLTCAVYGGSFSGYYWSWIRQPPGQGAEWIGEINHSGSTNYNPSLKSRVTISVGTSKNQFSLKLSSVTAADTAVYYCARGSTGRFLEWLLYFDYWGQGTLVTVSSGSRSAPTLFPLVSCENSPSDTSSVAVGCLAQDFLPDSITFSWKYKNNSDISSTRGFPSVLR";
    char numbering_scheme[10] = "chothia";
    char chain[6] = "heavy";

    auto *testObject = new AntibodyChainCPP(sequence, name, numbering_scheme);

    testObject->load();

    BOOST_TEST(testObject->getChain() == chain);
}
