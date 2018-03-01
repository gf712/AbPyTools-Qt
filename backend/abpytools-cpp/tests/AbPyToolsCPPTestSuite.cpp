//
// Created by gil on 21/02/18.
//

#define BOOST_TEST_MODULE AbPyToolsCInterfaceTestSuite
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "chainCollectionCPP.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(chainCollectionCPPTestSuite)

    BOOST_AUTO_TEST_CASE(chainCollectionEmptyContructor) {

        auto testObject = ChainCollectionCPP();

    }

    BOOST_AUTO_TEST_CASE(chainCollectionTwoChains) {

        char name[5] = "test";
        char sequence[200] = "QVQLQQWGAGLLKPSETLSLTCAVYGGSFSGYYWSWIRQPPGQGAEWIGEINHSGSTNYNPSLKSRVTISVGTSKNQFSLKLSSVTAADTAVYYCARGSTGRFLEWLLYFDYWGQGTLVTVSSGSRSAPTLFPLVSCENSPSDTSSVAVGCLAQDFLPDSITFSWKYKNNSDISSTRGFPSVLR";
        char numbering_scheme[10] = "chothia";
        auto testObject = new AntibodyChainCPP(sequence, name, numbering_scheme);

        auto testChainCollectionObject = new ChainCollectionCPP();

        testChainCollectionObject->append(*testObject);
        testChainCollectionObject->append(*testObject);

        BOOST_TEST(testChainCollectionObject->getNumberOfChains() == 2);
    }

    BOOST_AUTO_TEST_CASE(chainCollectionLoadTwoChains) {

        char name[5] = "test";
        char sequence[200] = "QVQLQQWGAGLLKPSETLSLTCAVYGGSFSGYYWSWIRQPPGQGAEWIGEINHSGSTNYNPSLKSRVTISVGTSKNQFSLKLSSVTAADTAVYYCARGSTGRFLEWLLYFDYWGQGTLVTVSSGSRSAPTLFPLVSCENSPSDTSSVAVGCLAQDFLPDSITFSWKYKNNSDISSTRGFPSVLR";
        char numbering_scheme[10] = "chothia";
        auto testObject = new AntibodyChainCPP(sequence, name, numbering_scheme);
        auto testChainCollectionObject = new ChainCollectionCPP();

        testChainCollectionObject->append(*testObject);
        testChainCollectionObject->append(*testObject);

        testChainCollectionObject->load();

        BOOST_TEST(testChainCollectionObject->getChainType() == "heavy");
        BOOST_TEST(testChainCollectionObject->getNumberOfChains() == 2);

    }


BOOST_AUTO_TEST_SUITE_END()
