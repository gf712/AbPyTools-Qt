//
// Created by gil on 19/03/18.
//

#include "../include/kmeans.h"

void KMeans::fit(arma::mat data) {

    Cluster(data, n_clusters, centroids);
    std::cout << "Number of clusters: " << n_clusters << std::endl;
    std::cout << "Data: " << std::endl;
    data.print();
    std::cout << "Centroids: " << std::endl;
    centroids.print();

}

arma::urowvec KMeans::predict(arma::mat data) {

    auto dists = arma::mat(centroids.n_rows, data.n_cols, arma::fill::zeros);

    for (int j = 0; j < centroids.n_cols; ++j) {

        arma::vec centroidVec = centroids.col(j);

        std::cout << "Vector: " << std::endl;
        centroidVec.print();

        for (int i = 0; i < data.n_cols; ++i) {

            arma::vec distVec = data.col(i);

            // calculate distance between all rows -> do not take square root as it is not necessary
            // just need to check where distance is lowest -> works with euclidean distance
            // so D = sum((dist[i], centroids[j]) ** 2)
            dists(j, i) = arma::sum(arma::pow((distVec - centroidVec), 2));
        }
    }

    // generate a row vector with minimum distance
    return arma::index_min(dists, 0);
}