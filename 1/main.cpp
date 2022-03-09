#include "Matrix.h"
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;


int main() {

    Matrix A(2, 2, 0);
    Matrix B1(3, 1, 2.0);
    Matrix B2(3, 1, 1.0);
    Matrix C(3, 3, 5.0);
    Matrix C2(3, 3, 5.0);


    vector<vector<double>> list1 = { {1, 5}, {2, 8} };
    vector<vector<double>> list2 = { {1, 3, 4}, {2, 5, -8}, {7, 1, 4} };
    vector<vector<double>> list3 = { {1}, {-2}, {-3} };
    vector<vector<double>> list4 = { {2, 3, 6}, {-1, 2, -8}, {0, 4, -4} };

    A.set_values(list1);
    C.set_values(list2);
    B2.set_values(list3);
    //  cout << A;
    //  cin >> A;
    cout << C;
    cout << B2;
    //  cout << (A * B1) << endl;
    //  cout << (A + C) << endl;
    //  cout << (A - C) << endl;
    //  cout << A * 2 << endl;

    cout << "Trace: " << C.trace() << endl;
    cout << "Determinant: " << C.determinantG() << endl;
    cout << "Adamar product: \n" << C.adamar(C2) << endl;
    cout << "Scalar product of vectors: " << B1.scalar(B2) << endl;
    cout << "The norm of the vector: " << B2.normVector() << endl;
    cout << "The max norm of the vector: " << B2.maxNormVector() << endl;
    cout << "The norm of the matrix: " << B2.frobeniusNorm() << endl;
    cout << "Angle between vectors: " << B1.angleVectors(B2) << endl;

    cout << "Matrix Rank: " << C.Rang() << endl;
    cout << "Inverse matrix: \n" << C.Reverse() * C << endl;
    cout << "Transposed matrix: \n" << B2.Transpose() << endl;
    A.write_bFile("bfile1");
    // Matrix V = V.read_bFile("bfile1", 2, 2);
    // cout << V;

    return 0;
}
