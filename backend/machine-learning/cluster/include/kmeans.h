//
// Created by gil on 19/03/18.
//

#ifndef ABPYTOOLS_QT_KMEANS_H
#define ABPYTOOLS_QT_KMEANS_H

#include <mlpack/core.hpp>
#include <mlpack/methods/kmeans/kmeans.hpp>
#include "cluster.h"

class KMeans: public cluster, public mlpack::kmeans::KMeans<> {

public:

    KMeans(int n_clusters_=2, int max_iterations=1000) {
        n_clusters = n_clusters_;
        max_iterations = max_iterations;
    }

    void fit(arma::mat);

    arma::mat getCentroids() {return centroids;}
    int getK() {return n_clusters;}
    int getMaxIterations() {return max_iterations;}

private:
    int n_clusters;
    int max_iterations;

};


#endif //ABPYTOOLS_QT_KMEANS_H
