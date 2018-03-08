//
// Created by gil on 05/03/18.
//

#include "../include/pca.h"

void PCA::fit(arma::mat data) {

    Apply(data, data, eigenvalues, eigenvectors);

    explainedVariance = arma::cumsum(eigenvalues);

    // normalise eigenvalues and keep normalising value
    sumEigenvalue = arma::sum(eigenvalues);
    eigenvalues /= sumEigenvalue;

    explainedVarianceRatio = arma::cumsum(eigenvalues);

}

arma::mat PCA::transform(arma::mat data) {

    if (!nDimensions) {

        // need to see how many dimensions to keep if only
        // max variance has been set

        double maxVarianceRatio_ = 0.0;
        nDimensions = 0;

        while (maxVarianceRatio_ < maxVariance) {

            maxVarianceRatio_ += explainedVarianceRatio(*nDimensions);

            (*nDimensions)++;
        }
    }

    return eigenvectors.submat(arma::span::all, arma::span(0, (*nDimensions) - 1));

}