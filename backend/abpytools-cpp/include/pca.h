//
// Created by gil on 05/03/18.
//

#ifndef ABPYTOOLS_QT_PCA_H
#define ABPYTOOLS_QT_PCA_H


#include <mlpack/core.hpp>
#include <mlpack/methods/pca/pca.hpp>
#include <boost/optional.hpp>

namespace mlpca = mlpack::pca;

class PCA {
    // Wrapper around mlpack PCA implementation
    // based on methods/pca/pca_impl.hpp
    // but with a touch of python's sklearn library

public:
    PCA(int nDimensions_) {
        nDimensions = nDimensions_;
    };

    PCA(double maxVariance_) {
        maxVariance = maxVariance_;
    };

    ~PCA();

    void fit(arma::mat data);
    arma::mat transform(arma::mat data);
    arma::mat fit_transform(arma::mat data) {
        fit(data);
        return transform(data);
    }

    // GETTERS
    arma::vec getExplainedVariance() { return  explainedVariance;}
    arma::vec getExplainedVarianceRatio() { return explainedVarianceRatio;}
    arma::vec getEigenvalues();
    arma::mat getEigenvectors();

    int getNDimensions() {
        // return 0 if nDimensions is not defined
        return nDimensions ? *nDimensions: 0;
    };

    double getMaxVariance() {
        // return 0.0 if maxVariance is not defined
        return maxVariance ? *maxVariance: 0.0;
    }

    // SETTERS
    void setNDimensions(int nDimensions_) {nDimensions = nDimensions_;}
    void setMaxVariance(double maxVariance_) {maxVariance = maxVariance_;}

private:
    boost::optional<int> nDimensions;
    boost::optional<double> maxVariance;

    arma::vec explainedVariance;
    arma::vec explainedVarianceRatio;
    double sumEigenvalue;

    arma::vec eigenvalues;
    arma::mat eigenvectors;

    mlpca::PCA pcaObject;

};


#endif //ABPYTOOLS_QT_PCA_H
