//
// Created by Gil Ferreira Hoben on 27/02/18.
//

#define BOOST_TEST_MODULE AbPyToolsGUIestSuite
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "chainGroups.h"

struct ChainGroup1Fixture {

    std::string name = "test";
    std::string sequence = "QVQLQQWGAGLLKPSETLSLTCAVYGGSFSGYYWSWIRQPPGQGAEWIGEINHSGSTNYNPSLKSRVTISVGTSKNQFSLKLSSVTAADTAVYYCARGSTGRFLEWLLYFDYWGQGTLVTVSSGSRSAPTLFPLVSCENSPSDTSSVAVGCLAQDFLPDSITFSWKYKNNSDISSTRGFPSVLR";
    std::string numbering_scheme = "chothia";
    ChainGroups *ChainGroupObject;

    ChainGroup1Fixture() {

        ChainGroupObject = new ChainGroups();

        ChainGroupObject->addGroup("Group1", numbering_scheme);

        ChainGroupObject->addChain("Group1", name, sequence);
        ChainGroupObject->addChain("Group1", "unnumberedSequence", "TEST");
    }

    ~ChainGroup1Fixture() = default;

};

BOOST_FIXTURE_TEST_SUITE(ChainGroupTestSuite, ChainGroup1Fixture)


    BOOST_AUTO_TEST_CASE(chainGroupNumberOfChains) {

        BOOST_TEST(ChainGroupObject->getNumberOfSequences("Group1") == 2);
    }

    BOOST_AUTO_TEST_CASE(chainGroupInvalidNumbering0) {

        ChainGroupObject->applyNumbering(0);

        BOOST_TEST(ChainGroupObject->getNumberOfSequences("Group1") == 2);
        BOOST_TEST(ChainGroupObject->getNumberOfSequences("Group1_numbered") == 1);

    }

    BOOST_AUTO_TEST_CASE(chainGroupInvalidNumbering1) {

        ChainGroupObject->applyNumbering(1);

        BOOST_TEST(ChainGroupObject->getNumberOfSequences("Group1") == 1);

    }

BOOST_AUTO_TEST_SUITE_END()
