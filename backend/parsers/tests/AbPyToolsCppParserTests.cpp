//
// Created by gil on 22/02/18.
//

#define BOOST_TEST_MODULE AbPyToolsCppParserTestSuite
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "hydrophobicityParser.h"
#include <iostream>


BOOST_AUTO_TEST_SUITE(AbPyToolsHydrophobicityTests)

    BOOST_AUTO_TEST_CASE(ParseFile) {

        std::string path ="data/abraham.hpb";

        auto testObject = hydrophobicityParser(path);

        std::cout << testObject.getFilepath();

        testObject.parse();

        BOOST_TEST(testObject.getAminoAcidHydrophobicityMap()["ALA"] == 0.440);
        BOOST_TEST(testObject.getAminoAcidHydrophobicityMap().size() == 20);
    }

BOOST_AUTO_TEST_SUITE_END()
