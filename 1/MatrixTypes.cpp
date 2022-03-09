#include "MatrixTypes.h"



IdentityMatrix::IdentityMatrix(int dim) : Matrix(dim, dim, 0) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (i == j) list[i][j] = 1;
            else list[i][j] = 0;
        }
    }
}


UpperMatrix::UpperMatrix(int dim, vector<vector<double>>& init) : Matrix(dim, dim, 0) {

    if (mRows != init.size() && mCols != init[0].size()) {
        throw length_error("Rows and cols are not equal!");
    }

    int count = dim, flag = 0;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < count--; j++, count--) {
            if (init[i][j] != 0) {
                if (flag == 0) {
                    cout << ("This is not upper matrix! The values will be changed.");
                    flag = 1;
                }
                init[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            list[i][j] = init[i][j];
        }
    }
}


LowerMatrix::LowerMatrix(int dim, vector<vector<double>>& init) : Matrix(dim, dim, 0) {

    if (mRows != init.size() || mCols != init[0].size()) {
        throw length_error("Rows and cols are not equal!");
    }
    int flag = 0;
    int count = 0;
    for (int i = 0; i < dim; i++, count++) {
        for (int j = 0; j < count; j++) {
            if (flag == 0) {
                cout << ("This is not upper matrix! The values will be changed.");
                flag = 1;
            }
            init[i][j] = 0;
        }
    }

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            list[i][j] = init[i][j];
        }
    }
}


SymmetricMatrix::SymmetricMatrix(int dim, vector<vector<double>>& init) : Matrix(dim, dim, 0) {

    if (mRows != init.size() || mCols != init[0].size()) {
        throw length_error("Rows and cols are not equal!");
    }

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (init[i][j] != init[j][i]) {
                throw invalid_argument("This is not symmetric matrix!");
            }
        }
    }

    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            list[i][j] = init[i][j];
        }
    }
}


DiagonalMatrix::DiagonalMatrix(int dim, vector<double>& init) : Matrix(dim, dim, 0) {

    if (mRows != init.size()) {
        throw length_error("Rows and cols are not equal!");
    }

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (i == j) list[i][j] = init[i];
            else list[i][j] = 0;
        }
    }
}