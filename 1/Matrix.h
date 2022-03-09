#pragma once
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <tuple>
#include <numeric>
#include <stdexcept>

using namespace std;

class Matrix {

protected:
    int mRows;
    int mCols;
    vector<vector<double>> list;

public:
    Matrix(int, int, double);
    Matrix(const Matrix&);
    unsigned get_mRows() const;
    unsigned get_mCols() const;
    double get_val(int i, int j);
    void set_values(vector<vector<double>> val);
    Matrix operator+(const Matrix&);
    Matrix operator-(const Matrix&);
    Matrix operator*(const Matrix&);
    Matrix operator*(double);
    Matrix adamar(const Matrix& other);
    friend ostream& operator<<(ostream& out, const Matrix& m);
    friend istream& operator>>(istream& in, Matrix& m);


    //lab2
    double determinantG();
    double trace();
    double scalar(const Matrix& other);
    double normVector();
    double maxNormVector();
    double frobeniusNorm();


    //lab3
    double angleVectors(Matrix& other);
    Matrix Transpose();
    Matrix excludeLine(int row, int col);
    int Rang();
    Matrix Reverse();

    //Lab4
    Matrix read_bFile(string fileName, int rows, int cols);
    void write_bFile(string fileName);
};


