 //
// Created by gil on 21/02/18.
//

#define BOOST_TEST_MODULE AbPyToolsCInterfaceTestSuite
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "chainCollectionCPP.h"

namespace tt = boost::test_tools;


struct ChainCollectionObjectFixture {

    char name[5] = "test";
    char sequence[200] = "QVQLQQWGAGLLKPSETLSLTCAVYGGSFSGYYWSWIRQPPGQGAEWIGEINHSGSTNYNPSLKSRVTISVGTSKNQFSLKLSSVTAADTAVYYCARGSTGRFLEWLLYFDYWGQGTLVTVSSGSRSAPTLFPLVSCENSPSDTSSVAVGCLAQDFLPDSITFSWKYKNNSDISSTRGFPSVLR";
    char numbering_scheme[10] = "chothia";
    ChainCollectionCPP *testChainCollectionObject;

    ChainCollectionObjectFixture() {

        auto testObject = new AntibodyChainCPP(sequence, name, numbering_scheme);
        testChainCollectionObject = new ChainCollectionCPP();

        testChainCollectionObject->append(*testObject);
        testChainCollectionObject->append(*testObject);

    }

    ~ChainCollectionObjectFixture() = default;

};


BOOST_FIXTURE_TEST_SUITE(chainCollectionCPPTestSuite, ChainCollectionObjectFixture)

    BOOST_AUTO_TEST_CASE(chainCollectionEmptyContructor) {

        try {
            ChainCollectionCPP testObject_ = ChainCollectionCPP();
        }
        catch (...) {
            BOOST_FAIL("Failed to instantiate ChainCollectionCPP");
        }
    }

    BOOST_AUTO_TEST_CASE(chainCollectionTwoChains) {

        BOOST_TEST(testChainCollectionObject->getNumberOfChains() == 2);
    }

    BOOST_AUTO_TEST_CASE(chainCollectionLoadTwoChains) {

        testChainCollectionObject->load();
        BOOST_TEST(testChainCollectionObject->getChainType() == "heavy");

    }

    BOOST_AUTO_TEST_CASE(chainCollectionGetHydrophobicityMatrix) {

        std::string path ="data/abraham.hpb";
        auto hObject = hydrophobicityParser(path);
        hObject.parse();

        testChainCollectionObject->load();

        testChainCollectionObject->getHydrophobicityValues(hObject, false);

        arma::colvec hSum = arma::sum(testChainCollectionObject->getHydrophobicityValues(hObject), 1);

        BOOST_TEST(hSum(0) == 50.35, tt::tolerance(10e-9));

    }

    BOOST_AUTO_TEST_CASE(chainCollectionHydrophobicityMatrixPCA) {

        std::string path ="data/abraham.hpb";
        auto hObject = hydrophobicityParser(path);
        hObject.parse();

        testChainCollectionObject->load();

        testChainCollectionObject->performPCA(hObject, 2, false);

        arma::vec result = testChainCollectionObject->getPrincipalComponent(1);

        BOOST_TEST(result(1) == 0.70710678, tt::tolerance(10e-9));
    }

BOOST_AUTO_TEST_SUITE_END()
