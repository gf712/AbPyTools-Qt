//
// Created by gil on 21/03/18.
//

#define BOOST_TEST_MODULE PCATestSuite
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "pca.h"

namespace tt = boost::test_tools;

struct PCATestFixture {

    arma::mat data;
    arma::uvec labels;

    PCATestFixture() {

        data <<  0.81053728 << -0.82557431 <<  0.76932462 << arma::endr
             <<  0.61821076 <<  2.24627065 <<  0.32586028 << arma::endr
             << -0.3762968  << -0.29062952 << -0.2960242  << arma::endr
             << -2.02934799 <<  2.22601899 << -1.94059068 << arma::endr
             <<  1.50725044 << -1.30308485 <<  1.40955312 << arma::endr
             <<  1.72100246 <<  0.88807452 <<  1.39389445 << arma::endr
             << -1.1367644  << -1.89570615 << -0.80193412 << arma::endr
             <<  1.76856675 <<  0.80693464 <<  1.44200633 << arma::endr
             << -0.01015517 << -1.20226672 <<  0.10037367 << arma::endr
             <<  0.94077416 <<  1.37069271 <<  0.68165121 << arma::endr
             << -1.36536204 <<  1.39473319 << -1.29630532 << arma::endr
             << -1.24039806 <<  0.57127886 << -1.11453597 << arma::endr
             << -0.87791817 << -1.84005703 << -0.58521706 << arma::endr
             <<  0.15079383 << -0.28660898 <<  0.1551944  << arma::endr
             <<  0.30651184 << -0.47169202 <<  0.30539677 << arma::endr;

        data = data.t();

        labels << 0 << 1 << 0 << 1 << 0 << 1 << 0 << 1 << 0 << 1 << 1 << 1 << 0 << 0 << 0;
    }

    ~PCATestFixture() = default;

};

BOOST_FIXTURE_TEST_SUITE(PCATestSuite, PCATestFixture)

    BOOST_AUTO_TEST_CASE(PCARatio) {

        double ratio_answers[3] = {5.75711670e-01, 4.24288330e-01, 1.01404823e-18};

        auto pca = PCA(2);
        pca.fit(data);
        auto ratio = pca.getExplainedVarianceRatio();

        pca.getExplainedVarianceRatio().print();
        pca.getExplainedVariance().print();

        for (int i = 0; i < 3; ++i) {
            BOOST_TEST(ratio[i] == ratio_answers[i], tt::tolerance(10e-8));
        }
    }

BOOST_AUTO_TEST_SUITE_END()

//array([[ 0.81053728, -0.82557431,  0.76932462],
//       [ 0.61821076,  2.24627065,  0.32586028],
//       [-0.3762968 , -0.29062952, -0.2960242 ],
//       [-2.02934799,  2.22601899, -1.94059068],
//       [ 1.50725044, -1.30308485,  1.40955312],
//       [ 1.72100246,  0.88807452,  1.39389445],
//       [-1.1367644 , -1.89570615, -0.80193412],
//       [ 1.76856675,  0.80693464,  1.44200633],
//       [-0.01015517, -1.20226672,  0.10037367],
//       [ 0.94077416,  1.37069271,  0.68165121],
//       [-1.36536204,  1.39473319, -1.29630532],
//       [-1.24039806,  0.57127886, -1.11453597],
//       [-0.87791817, -1.84005703, -0.58521706],
//       [ 0.15079383, -0.28660898,  0.1551944 ],
//       [ 0.30651184, -0.47169202,  0.30539677]])
//array([0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0]))
