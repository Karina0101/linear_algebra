#pragma once
#include "Matrix.h"


class IdentityMatrix : public Matrix {
public:
    IdentityMatrix(int dim);
};

class UpperMatrix : public Matrix {
public:
    UpperMatrix(int dim, vector<vector<double>>& init);
};

class LowerMatrix : public Matrix {
public:
    LowerMatrix(int dim, vector<vector<double>>& init);
};

class SymmetricMatrix : public Matrix {
public:
    SymmetricMatrix(int dim, vector<vector<double>>& init);
};

class DiagonalMatrix : public Matrix {
public:
    DiagonalMatrix(int dim, vector<double>& init);
};
