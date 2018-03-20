//
// Created by gil on 19/03/18.
//

#include "../include/kmeans.h"

void KMeans::fit(arma::mat data) {

    // mlpack expects a matrix with a datapoint per *COLUMN* (??)
    Cluster(data.t(), n_clusters, centroids);

    std::cout << "Number of clusters: " << n_clusters << std::endl;
    std::cout << "Data: " << std::endl;
    data.print();
    std::cout << "Centroids: " << std::endl;
    centroids.print();

}

arma::uvec KMeans::predict(arma::mat data) {

    auto dists = arma::mat(data.n_rows, centroids.n_rows, arma::fill::zeros);

    for (int j = 0; j < centroids.n_rows; ++j) {

        auto centroidVec = centroids.row(j);

        for (int i = 0; i < data.n_rows; ++i) {

            auto distVec = data.row(i);

            // calculate distance between all rows -> do not take square root as it is not necessary
            // just need to check where distance is lowest -> works with euclidean distance
            // so D = sum((dist[i], centroids[j]) ** 2)
            dists(i, j) = arma::sum(arma::pow((distVec - centroidVec), 2));
        }
    }

    // generate a column vector with minimum distance
    return arma::index_min(dists, 1);
}