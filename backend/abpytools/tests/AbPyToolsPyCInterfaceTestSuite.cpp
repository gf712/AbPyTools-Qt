//
// Created by gil on 21/02/18.
//

#define BOOST_TEST_MODULE AbPyToolsCInterfaceTestSuite
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include "chain.h"
#include "exception.h"
#include <algorithm>

namespace tt = boost::test_tools;

struct ChainObjectFixture {

    AntibodyChainCPP* testObject;
    char name[5] = "test";
    char sequence[200] = "QVQLQQWGAGLLKPSETLSLTCAVYGGSFSGYYWSWIRQPPGQGAEWIGEINHSGSTNYNPSLKSRVTISVGTSKNQFSLKLSSVTAADTAVYYCARGSTGRFLEWLLYFDYWGQGTLVTVSSGSRSAPTLFPLVSCENSPSDTSSVAVGCLAQDFLPDSITFSWKYKNNSDISSTRGFPSVLR";
    char numbering_scheme[10] = "chothia";

    ChainObjectFixture() {

        testObject = new AntibodyChainCPP(sequence, name, numbering_scheme);
    }

    ~ChainObjectFixture() = default;

};

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

BOOST_FIXTURE_TEST_SUITE(AbPyToolsPyCInterface, ChainObjectFixture)

    BOOST_AUTO_TEST_CASE(NameTest) {

        BOOST_TEST(testObject->getName() == name);
        BOOST_TEST(testObject->getSequence() == sequence);
        BOOST_TEST(testObject->getNumberingScheme() == numbering_scheme);

    }


    BOOST_AUTO_TEST_CASE(LoadTest) {

        char chain[6] = "heavy";

        testObject->load();

        BOOST_TEST(testObject->getChain() == chain);

    }

    BOOST_AUTO_TEST_CASE(ChargeTest) {

        char chain[6] = "heavy";
        char database[10] = "Wikipedia";

        vector<double> charges = testObject->getAminoAcidCharges(true, 7.4, database);

        double sumOfCharges = std::accumulate(charges.begin(), charges.end(), 0.0);

        BOOST_TEST(charges.size() == 158);
        BOOST_TEST(sumOfCharges == 1.7497642167513601, tt::tolerance(10e-9));

    }

BOOST_AUTO_TEST_SUITE_END()
