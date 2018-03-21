 //
// Created by gil on 21/02/18.
//

#define BOOST_TEST_MODULE AbPyToolsCInterfaceTestSuite
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "connection_check.h"
#include "chainCollectionCPP.h"

namespace tt = boost::test_tools;
namespace utf = boost::unit_test;

tt::assertion_result connection(utf::test_unit_id) {

    bool result = abnumConnection();

    tt::assertion_result ans(result);

    if (!result) ans.message() << "Failed to connect to abnum server!";

    return ans;
}

struct ChainCollectionObjectFixture {

    char name[5] = "test";
    char sequence[200] = "QVQLQQWGAGLLKPSETLSLTCAVYGGSFSGYYWSWIRQPPGQGAEWIGEINHSGSTNYNPSLKSRVTISVGTSKNQFSLKLSSVTAADTAVYYCARGSTGRFLEWLLYFDYWGQGTLVTVSSGSRSAPTLFPLVSCENSPSDTSSVAVGCLAQDFLPDSITFSWKYKNNSDISSTRGFPSVLR";
    char numbering_scheme[10] = "chothia";
    ChainCollectionCPP *testChainCollectionObject;

    ChainCollectionObjectFixture() {

        auto testObject = new AntibodyChainCPP(sequence, name, numbering_scheme);
        testChainCollectionObject = new ChainCollectionCPP(numbering_scheme);

        testChainCollectionObject->append(*testObject);
        testChainCollectionObject->append(*testObject);

    }

    ~ChainCollectionObjectFixture() = default;

};



BOOST_FIXTURE_TEST_SUITE(chainCollectionCPPTestSuite, ChainCollectionObjectFixture)

    BOOST_AUTO_TEST_CASE(chainCollectionEmptyContructor) {

        try {
            ChainCollectionCPP testObject_ = ChainCollectionCPP("chothia");
        }
        catch (...) {
            BOOST_FAIL("Failed to instantiate ChainCollectionCPP");
        }
    }

    BOOST_AUTO_TEST_CASE(chainCollectionTwoChains) {

        BOOST_TEST(testChainCollectionObject->getNumberOfChains() == 2);
    }

    BOOST_AUTO_TEST_CASE(chainCollectionLoadTwoChains, *utf::precondition(connection)) {

        testChainCollectionObject->load();
        BOOST_TEST(testChainCollectionObject->getChainType() == "heavy");

    }

    BOOST_AUTO_TEST_CASE(chainCollectionInvalidNumbering0, *utf::precondition(connection)) {

        auto *tempChainCollection = new ChainCollectionCPP("chothia");

        testChainCollectionObject->append("falseSequence", "TEST");

        std::cout << "testChainCollectionObject->getChainObject(2)->getNumberingScheme(): "
                  << testChainCollectionObject->getAntibodyObject(2)->getNumberingScheme() << std::endl;

        testChainCollectionObject->load(0, tempChainCollection);

        BOOST_TEST(testChainCollectionObject->getChainType() == "heavy");
        BOOST_TEST(testChainCollectionObject->getNumberOfChains() == 3);
        BOOST_TEST(testChainCollectionObject->isPartial() == true);
        BOOST_TEST(testChainCollectionObject->isLoaded() == true);

        BOOST_TEST(tempChainCollection->getChainType() == "heavy");
        BOOST_TEST(tempChainCollection->getNumberOfChains() == 2);
        BOOST_TEST(tempChainCollection->isPartial() == false);
        BOOST_TEST(tempChainCollection->isLoaded() == true);
    }

    BOOST_AUTO_TEST_CASE(chainCollectionInvalidNumbering1, *utf::precondition(connection)) {

        testChainCollectionObject->append("falseSequence", "TEST");
        testChainCollectionObject->load();

        BOOST_TEST(testChainCollectionObject->getChainType() == "heavy");
        BOOST_TEST(testChainCollectionObject->getNumberOfChains() == 2);
        BOOST_TEST(testChainCollectionObject->isPartial() == false);
        BOOST_TEST(testChainCollectionObject->isLoaded() == true);
    }


    BOOST_AUTO_TEST_CASE(chainCollectionGetHydrophobicityMatrix, *utf::precondition(connection)) {

        std::string path ="data/abraham.hpb";
        auto hObject = hydrophobicityParser(path);
        hObject.parse();

        testChainCollectionObject->load();

        testChainCollectionObject->getHydrophobicityValues(hObject, false);

        arma::colvec hSum = arma::sum(testChainCollectionObject->getHydrophobicityValues(hObject), 1);

        BOOST_TEST(hSum(0) == 50.35, tt::tolerance(10e-9));

    }

    BOOST_AUTO_TEST_CASE(chainCollectionHydrophobicityMatrixPCA, *utf::precondition(connection)) {

        std::string path ="data/abraham.hpb";
        auto hObject = hydrophobicityParser(path);
        hObject.parse();

        testChainCollectionObject->load();

        testChainCollectionObject->performPCA(hObject, 2, false);

        arma::vec result = testChainCollectionObject->getPrincipalComponent(1);

        BOOST_TEST(round(result(1)) == 0); // not a great test, but boost test seems to have some bug calculating tolerance with small numbers
    }

BOOST_AUTO_TEST_SUITE_END()
