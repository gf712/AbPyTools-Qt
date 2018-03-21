//
// Created by gil on 21/03/18.
//

#ifndef ABPYTOOLS_QT_CLUSTER_H
#define ABPYTOOLS_QT_CLUSTER_H

#include <armadillo>

class cluster {

public:
    cluster() {};

    arma::urowvec predict(arma::mat);

protected:
    arma::mat centroids;

};


#endif //ABPYTOOLS_QT_CLUSTER_H
