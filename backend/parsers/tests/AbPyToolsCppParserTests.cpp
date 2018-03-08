//
// Created by gil on 22/02/18.
//

#define BOOST_TEST_MODULE AbPyToolsCppParserTestSuite
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "hydrophobicityParser.h"
#include "fastaParser.h"
#include <iostream>

BOOST_AUTO_TEST_SUITE(AbPyToolsHydrophobicityTests)

    BOOST_AUTO_TEST_CASE(ParseFile) {

        std::string path ="data/abraham.hpb";

        auto testObject = hydrophobicityParser(path);

        std::cout << testObject.getFilepath();

        testObject.parse();

        BOOST_TEST(testObject.getAminoAcidHydrophobicityMap(3)["ALA"] == 0.440);
        BOOST_TEST(testObject.getAminoAcidHydrophobicityMap(1)["A"] == 0.440);
        BOOST_TEST(testObject.getAminoAcidHydrophobicityMap(3).size() == 20);
        BOOST_TEST(testObject.getAminoAcidHydrophobicityMap(1).size() == 20);
        BOOST_TEST(testObject.getBasename().compare(std::string("abraham")) == 0);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AbPyToolsFASTATests)

    BOOST_AUTO_TEST_CASE(ParseFile) {

        std::string path ="data/test.fasta";

        auto testObject = FastaParser(path);

        std::cout << testObject.getFilepath();

        testObject.parse();

        BOOST_TEST(testObject.getSequences().size() == 2);
        BOOST_TEST(testObject.getNames().size() == 2);
        BOOST_TEST(testObject.getTotalLines() == 2);
    }

BOOST_AUTO_TEST_SUITE_END()
