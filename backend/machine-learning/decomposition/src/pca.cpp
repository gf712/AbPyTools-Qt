//
// Created by gil on 05/03/18.
//

#include "../include/pca.h"

void PCA::fit(arma::mat data) {

    // Center the data into a temporary matrix.
    arma::mat centeredData;
    mlpack::math::Center(data, centeredData);

    // tranform data to have variance zero
    arma::vec stdDev = arma::stddev(centeredData, 0, 1);

    // If there are any zeroes, make them very small.
    for (size_t i = 0; i < stdDev.n_elem; ++i)
        if (stdDev[i] == 0)
            stdDev[i] = 1e-50;

    centeredData /= arma::repmat(stdDev, 1, centeredData.n_cols);

    // apply PCA on centered and whitened data
    Apply(centeredData, transformedData, eigenvalues, eigenvectors);

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