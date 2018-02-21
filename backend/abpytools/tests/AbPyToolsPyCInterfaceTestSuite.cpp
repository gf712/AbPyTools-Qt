//
// Created by gil on 21/02/18.
//

#define BOOST_TEST_MODULE AbPyToolsCInterfaceTestSuite
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include "chain.h"
#include "exception.h"

BOOST_AUTO_TEST_SUITE(AbPyToolsImportTests)

    BOOST_AUTO_TEST_CASE(ModuleImportTest) {

        try {
            auto *testObject = new AntibodyChainCPP;
            BOOST_TEST(true);
        }
        catch (ModuleImportException &e) {
            BOOST_FAIL("Failed to initialise AntibodyChainCPP object!");
        }
    }

    BOOST_AUTO_TEST_CASE(ChainImportTest) {

        try {
            auto *testObject = new AntibodyChainCPP;
            BOOST_TEST(true);
        }

        catch (ClassImportException &e) {
            BOOST_FAIL("Failed to initialise AntibodyChainCPP object!");
        }
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AbPyToolsPyCInterface)

    BOOST_AUTO_TEST_CASE(NameTest) {

        char name[5] = "test";
        char sequence[5] = "ABCD";
        char numbering_scheme[10] = "chothia";

        auto *testObject = new AntibodyChainCPP(sequence, name, numbering_scheme);

        BOOST_TEST(testObject->getName() == name);
        BOOST_TEST(testObject->getSequence() == sequence);
        BOOST_TEST(testObject->getNumberingScheme() == numbering_scheme);

    }


    BOOST_AUTO_TEST_CASE(LoadTest) {

        char name[5] = "test";
        char sequence[200] = "QVQLQQWGAGLLKPSETLSLTCAVYGGSFSGYYWSWIRQPPGQGAEWIGEINHSGSTNYNPSLKSRVTISVGTSKNQFSLKLSSVTAADTAVYYCARGSTGRFLEWLLYFDYWGQGTLVTVSSGSRSAPTLFPLVSCENSPSDTSSVAVGCLAQDFLPDSITFSWKYKNNSDISSTRGFPSVLR";
        char numbering_scheme[10] = "chothia";
        char chain[6] = "heavy";

        auto *testObject = new AntibodyChainCPP(sequence, name, numbering_scheme);

        testObject->load();

        BOOST_TEST(testObject->getChain() == chain);

    }

BOOST_AUTO_TEST_SUITE_END()
