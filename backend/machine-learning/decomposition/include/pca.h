//
// Created by gil on 05/03/18.
//

#ifndef ABPYTOOLS_QT_PCA_H
#define ABPYTOOLS_QT_PCA_H

#include <mlpack/core.hpp>
#include <mlpack/methods/pca/pca.hpp>
#include <mlpack/core/math/lin_alg.hpp>
#include <boost/optional.hpp>

namespace mlpca = mlpack::pca;

class PCA: public mlpca::PCA {
    // Wrapper around mlpack PCA implementation
    // based on https://github.com/mlpack/mlpack/blob/master/src/mlpack/methods/pca/pca_impl.hpp
    // but with a touch of python's sklearn library

public:
    PCA(int nDimensions_, bool centreData_ = false) {
        nDimensions = nDimensions_;
        centreData = centreData_;
    };

    PCA(double maxVariance_, bool centreData_ = false) {
        maxVariance = maxVariance_;
        centreData = centreData_;
    };

//    PCA();

    ~PCA() = default;

    void fit(const arma::mat &data);
    arma::mat transform();
    arma::mat fit_transform(const arma::mat &data) {
        fit(data);
        return transform();
    }

    // GETTERS
    arma::vec getExplainedVariance() { return  explainedVariance;}
    arma::vec getExplainedVarianceRatio() { return explainedVarianceRatio;}
    arma::vec getEigenvalues() {return eigenvalues;}
    arma::mat getEigenvectors() {return eigenvectors;}
    arma::mat getTransformedData() {return transformedData;}

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
    bool centreData;


    arma::vec explainedVariance;
    arma::vec explainedVarianceRatio;
    double sumEigenvalue;

    arma::vec eigenvalues;
    arma::mat eigenvectors;

    arma::mat transformedData;

};


#endif //ABPYTOOLS_QT_PCA_H
