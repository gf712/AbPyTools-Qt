//
// Created by gil on 05/03/18.
//

#include "../include/pca.h"

void PCA::fit(arma::mat data) {

    Apply(data, transformedData, eigenvalues, eigenvectors);

    std::cout << "MLPACK PCA: \n";
    std::cout << "Data cols: " << data.n_cols << "\n";
    std::cout << "Data rows: " << data.n_rows << "\n";

    std::cout << "EigVec cols: " << eigenvectors.n_cols << "\n";
    std::cout << "EigVec rows: " << eigenvectors.n_rows << "\n";

    explainedVariance = arma::cumsum(eigenvalues);

    // normalise eigenvalues and keep normalising value
    sumEigenvalue = arma::sum(eigenvalues);
    eigenvalues /= sumEigenvalue;

    explainedVarianceRatio = arma::cumsum(eigenvalues);

}

arma::mat PCA::transform() {

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

    return transformedData.submat(arma::span::all, arma::span(0, (*nDimensions) - 1));

}