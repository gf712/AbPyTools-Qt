//
// Created by gil on 19/02/18.
//

#define BOOST_TEST_MODULE My Test 1
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(first_test)
{
    int i = 1;
    BOOST_TEST(i);
    BOOST_TEST(i == 2);
}
