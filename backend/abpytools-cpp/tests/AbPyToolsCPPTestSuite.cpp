//
// Created by gil on 21/02/18.
//

#define BOOST_TEST_MODULE AbPyToolsCInterfaceTestSuite
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "chainCollectionCPP.h"

using namespace std;
namespace tt = boost::test_tools;

//struct ChainObjectFixture {
//
//    AntibodyChainCPP* testObject;
//    char name[5] = "test";
//    char sequence[200] = "QVQLQQWGAGLLKPSETLSLTCAVYGGSFSGYYWSWIRQPPGQGAEWIGEINHSGSTNYNPSLKSRVTISVGTSKNQFSLKLSSVTAADTAVYYCARGSTGRFLEWLLYFDYWGQGTLVTVSSGSRSAPTLFPLVSCENSPSDTSSVAVGCLAQDFLPDSITFSWKYKNNSDISSTRGFPSVLR";
//    char numbering_scheme[10] = "chothia";
//
//    ChainObjectFixture() {
//
//        testObject = new AntibodyChainCPP(sequence, name, numbering_scheme);
//    }
//
//    ~ChainObjectFixture() = default;
//
//};

BOOST_AUTO_TEST_SUITE(chainCollectionCPPTestSuite)

    BOOST_AUTO_TEST_CASE(chainCollectionEmptyContructor) {

        auto testObject = ChainCollectionCPP();

    }


BOOST_AUTO_TEST_SUITE_END()
