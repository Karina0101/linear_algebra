#include "Matrix.h"
#include "iomanip" 

using namespace std;

Matrix::Matrix(int rows, int cols, double def = 0) {
    mRows = rows;
    mCols = cols;

    list.resize(rows);
    for (int i = 0; i < rows; i++)
    {
        list[i].resize(cols, def);
    }
}

Matrix::Matrix(const Matrix& other)
{
    mRows = other.get_mRows();
    mCols = other.get_mCols();
    list = other.list;
}

unsigned Matrix::get_mRows() const { return mRows; }
unsigned Matrix::get_mCols() const { return mCols; }
double Matrix::get_val(int i, int j) { return list[i][j]; }
void Matrix::set_values(vector<vector<double>> val)
{
    Matrix A(val.size(), val[0].size(), 0);
    A.list = val;
    *(this) = A;
}

Matrix Matrix::operator+(const Matrix& other) {

    Matrix A(mCols, mRows, 0.);
    if (mCols != other.get_mCols() || mRows != other.get_mRows())
    {
        throw length_error("Rows and cols are not equal! Addition is impossible");
    }

    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < mCols; j++)
        {
            A.list[i][j] = this->list[i][j] + other.list[i][j];
        }
    }
    return A;
}

Matrix Matrix::operator-(const Matrix& other) {

    Matrix A(mCols, mRows, 0.);

    if (mCols != other.get_mCols() || mRows != other.get_mRows())
    {
        throw length_error("Rows and cols are not equal! Subtraction is impossible.");
    }


    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < mCols; j++)
        {
            A.list[i][j] = (*this).list[i][j] - other.list[i][j];
        }
    }

    return A;
}

Matrix Matrix::operator*(const Matrix& other) {

    Matrix A(mRows, other.get_mCols(), 0);
    if (mCols != other.get_mRows())
    {
        throw length_error("The number of cols is not equal to the number of rows. Multiplication is impossible.");
    }

    double tmp = 0;
    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < other.get_mCols(); j++)
        {
            tmp = 0.0;
            for (int k = 0; k < mCols; k++)
            {
                tmp += list[i][k] * other.list[k][j];
            }
            A.list[i][j] = tmp;
        }
    }
    return A;
}

Matrix Matrix::operator*(double alpha) {
    Matrix A(mRows, mCols, 0);
    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < mCols; j++)
        {
            A.list[i][j] = alpha * list[i][j];
        }
    }
    return A;
}

Matrix Matrix::adamar(const Matrix& other)
{
    Matrix A(mCols, mRows, 0);

    if (mCols != other.get_mCols() || mRows != other.get_mRows())
    {
        throw length_error("Rows and cols are not equal!");
    }

    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < mCols; j++)
        {
            A.list[i][j] = list[i][j] * other.list[i][j];
        }
    }
    return A;
}

ostream& operator<<(ostream& out, const Matrix& m)
{
    for (int i = 0; i < m.mRows; i++) {
        for (int j = 0; j < m.mCols; j++) {
            out << setw(10) << left << setprecision(2) << m.list[i][j];
        }
        out << endl;
    }
    out << endl;
    return out;
}

istream& operator>>(istream& in, Matrix& m)
{
    for (int i = 0; i < m.mRows; i++) {
        for (int j = 0; j < m.mCols; j++) {
            in >> m.list[i][j];
        }
    }
    return in;
}


/////////////////// lab 2 ////////////

Matrix Matrix::Transpose()
{
    Matrix A(mCols, mRows, 0);

    for (int i = 0; i < mCols; i++) {
        for (int j = 0; j < mRows; j++) {
            A.list[i][j] = list[j][i];
        }
    }
    return A;
}

double Matrix::determinantG()
{
    Matrix A = (*this);
    double znak = 1;
    double determinant = 1;

    if (mRows != mCols) {
        throw length_error("The matrix is not square!");
    }

    for (int i = 0; i < mRows; ++i)
    {
        int keyRow = i;
        int flag = 0;
        double corner_element = A.list[i][i];

        for (int j = i + 1; j < mRows; ++j)
        {
            if (fabs(corner_element) < fabs(A.list[j][i]))
            {
                corner_element = A.list[j][i];
                keyRow = j;
                flag = 1;
            }
        }

        if (corner_element == 0)
        {
            return 0;
        }

        if (flag)
        {
            for (int k = 0; k < mCols - i; k++) {
                swap(A.list[i][k], A.list[keyRow][k]);
            }
            znak *= -1;
        }

        for (int r = i + 1; r < mRows; r++)
        {
            for (int c = i + 1; c < mCols; c++)
            {
                A.list[r][c] -= A.list[r][i] / corner_element * A.list[i][c];
            }
        }
        determinant *= corner_element;
    }

    return determinant * znak;
}

double Matrix::trace() {

    double tr = 0;

    if (mRows != mCols) {
        throw length_error("The matrix is not square!");
    }
    for (int i = 0; i < mCols; i++) {
        tr += list[i][i];
    }

    return tr;
}

double Matrix::scalar(const Matrix& other) {

    double scal = 0;
    if (mCols == other.get_mCols() == 1) {
        for (int i = 0; i < mRows; i++) {
            scal += list[i][0] * other.list[i][0];
        }
    }

    else {
        for (int i = 0; i < mCols; i++) {
            scal += list[0][i] * other.list[0][i];
        }
    }
    return scal;
}

double Matrix::normVector() {
    return sqrt((*this).scalar(*this));
}

double Matrix::maxNormVector() {
    double max_el = abs(list[0][0]);
    for (int i = 0; i < mRows; ++i) {
        for (int j = 0; j < mCols; ++j) {
            if (max_el < fabs(list[i][j])) max_el = fabs(list[i][j]);
        }
    }
    return max_el;
}

double Matrix::frobeniusNorm() {
    double sum = 0.0;
    for (int i = 0; i < mRows; i++) {
        for (int j = 0; j < mCols; j++) {
            sum += pow(list[i][j], 2);
        }
    }

    return sqrt(sum);
}

///////////////// lab 3 ///////////

double Matrix::angleVectors(Matrix& other) {
    double angle;
    angle = (*this).scalar(other) / ((*this).normVector() * other.normVector());
    return angle;
}

int Matrix::Rang()
{
    int i, j, k;
    double corner_element;
    Matrix A = (*this);
    double eps = 1E-10;
    int corner_row = 0;

    i = 0; j = 0;
    while (i < mRows && j < mCols) {

        corner_element = 0.0;
        for (k = i; k < mRows; ++k) {
            if (fabs(A.list[k][j]) > corner_element) {
                corner_row = k;
                corner_element = fabs(A.list[k][j]);
            }
        }

        if (corner_element < eps) {
            for (k = i; k < mRows; ++k) {
                A.list[k][j] = 0.0;
            }
            ++j;
            continue;
        }

        if (corner_row != i) {
            for (k = j; k < mCols; ++k) {
                A.list[i][k] *= -1;
                swap(A.list[i][k], A.list[corner_row][k]);
            }
        }

        for (k = i + 1; k < mRows; ++k) {
            for (int col = j + 1; col < mCols; ++col) {
                A.list[k][col] -= (A.list[k][j] / A.list[i][j]) * A.list[i][col];
                A.list[k][j] = 0.0;
            }
        }
        ++i; ++j;
    }
    return i;
}


Matrix Matrix::Reverse() {

    Matrix A = (*this);
    double det = (*this).determinantG();
    double a = 1 / det;
    int znak = 1;
    if (det == 0) {
        throw invalid_argument("The inverse matrix does not exist!");
    }

    Matrix minor(A.get_mRows(), A.get_mCols(), 0);
    for (int i = 0; i < mRows; i++) {
        for (int j = 0; j < mCols; j++) {
            minor.list[i][j] = (A.excludeLine(i, j)).determinantG();
        }
    }

    Matrix revers(A.get_mRows(), A.get_mCols(), 0);
    for (int i = 0; i < mRows; i++) {
        for (int j = 0; j < mCols; j++) {
            revers.list[i][j] = znak * minor.list[j][i] * a;
            znak *= -1;
        }
    }

    return revers;
}


Matrix Matrix::excludeLine(int row, int col) {

    Matrix A(mRows - 1, mCols - 1, 0);
    for (int i = 0, Ai = 0; i < mRows; i++) {
        if (i == row) continue;
        for (int j = 0, Aj = 0; j < mCols; j++) {
            if (j == col) continue;
            A.list[Ai][Aj] = list[i][j];
            Aj++;
        }
        Ai++;
    }
    return A;
}


///////////////// lab 4 ///////////
Matrix Matrix::read_bFile(string fileName, int rows, int cols)
{
    fstream in(fileName, ios::in | ios::binary);
    while (in.is_open()) {
        Matrix A(rows, cols, 0.0);
        vector<vector<double>> mat;
        for (int i = 0; i < rows; i++)
        {
            vector<double> row;
            row.resize(cols);
            in.read(reinterpret_cast<char*>(row.data()), cols * sizeof(double));
            mat.push_back(row);
        }
        in.close();
        A.list = mat;
        return A;
    }
    cout << "File opening error!" << endl;
}

void Matrix::write_bFile(string fileName)
{
    fstream in(fileName, ios::out | ios::binary);
    if (in.is_open()) {
        for (int i = 0; i < mRows; ++i) {
            vector<double> row = list[i];
            in.write(reinterpret_cast<char*>(row.data()), mCols * sizeof(double));
        }
        in.close();
    }
    else cout << "Failed to write to file!" << endl;
}


