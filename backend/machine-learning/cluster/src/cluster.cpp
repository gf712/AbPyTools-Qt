//
// Created by gil on 21/03/18.
//

#include "../include/cluster.h"

arma::urowvec cluster::predict(arma::mat data) {

    // generic cluster label predictor using euclidean (L2 norm)

    auto dists = arma::mat(centroids.n_cols, data.n_cols, arma::fill::zeros);

    dists.print();

    for (int j = 0; j < centroids.n_cols; ++j) {

        arma::colvec centroidVec = centroids.col(j);

        std::cout << "Vector: " << std::endl;
        centroidVec.print();

        for (int i = 0; i < data.n_cols; ++i) {

            arma::colvec distVec = data.col(i);

            // calculate distance between all rows -> do not take square root as it is not necessary
            // just need to check where distance is lowest -> works with euclidean distance
            // so D = sum((dist[i], centroids[j]) ** 2)
            dists(j, i) = arma::sum(arma::pow((distVec - centroidVec), 2));
        }
    }

    // generate a row vector with minimum distance
    return arma::index_min(dists, 0);
}