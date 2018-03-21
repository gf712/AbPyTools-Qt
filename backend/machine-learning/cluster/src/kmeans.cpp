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