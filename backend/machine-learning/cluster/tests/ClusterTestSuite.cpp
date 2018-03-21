//
// Created by gil on 20/03/18.
//

#define BOOST_TEST_MODULE ClusterTestSuite
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "kmeans.h"

namespace tt = boost::test_tools;


struct ClusterTestFixture {

    arma::mat data;
    arma::uvec labels;

    ClusterTestFixture() {
        data << -8.78346921 <<  5.04982015  << arma::endr
             <<  5.65540601 << -9.54434396  << arma::endr
             <<  5.20142846 << -8.02833731  << arma::endr
             << -9.38914263 <<  6.01661793  << arma::endr
             <<  6.69599896 << -11.59248801 << arma::endr
             <<  5.58710613 << -8.31880506  << arma::endr
             << -7.21040978 <<  4.29978953  << arma::endr
             << -8.54476321 <<  2.98571676  << arma::endr
             << -9.43919909 <<  3.05837214  << arma::endr
             <<  7.51514861 << -9.80296322  << arma::endr;

        data = data.t();
        labels << 0 << 1 << 1 << 0 << 1 << 1 << 0 << 0 << 0 << 1;
    }

    ~ClusterTestFixture() = default;

};


BOOST_FIXTURE_TEST_SUITE(ClusterTestSuite, ClusterTestFixture)

    BOOST_AUTO_TEST_CASE(KMeansLabel) {

        // create kmeans object
        auto k = KMeans();

        // fit to data
        k.fit(data);

        // predict cluster labels from centroids obtained after calling fit
        auto test_labels = k.predict(data);

        // test point by point
        for (int i = 0; i < 10; ++i) {
            BOOST_TEST(labels[i] == test_labels[i]);
        }
    }

    BOOST_AUTO_TEST_CASE(KMeansCentroids) {

        auto k = KMeans();
        k.fit(data);

        k.getCentroids().print();

        BOOST_TEST(k.getCentroids()(0,0) == -8.6734, tt::tolerance(10e-6));
        BOOST_TEST(k.getCentroids()(1,0) ==  4.2821, tt::tolerance(10e-6));
        BOOST_TEST(k.getCentroids()(0,1) ==  6.1310, tt::tolerance(10e-6));
        BOOST_TEST(k.getCentroids()(1,1) == -9.4574, tt::tolerance(10e-6));
    }

BOOST_AUTO_TEST_SUITE_END()

//
//array([[ -8.78346921,   5.04982015],
//       [  5.65540601,  -9.54434396],
//       [  5.20142846,  -8.02833731],
//       [ -9.38914263,   6.01661793],
//       [  6.69599896, -11.59248801],
//       [  5.58710613,  -8.31880506],
//       [ -7.21040978,   4.29978953],
//       [ -8.54476321,   2.98571676],
//       [ -9.43919909,   3.05837214],
//       [  7.51514861,  -9.80296322]]),
// array([0, 1, 1, 0, 1, 1, 0, 0, 0, 1])
