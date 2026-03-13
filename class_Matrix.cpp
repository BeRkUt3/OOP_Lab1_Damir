#include <bits/stdc++.h>
#include "class_Matrix.h"

#define endl '\n'

using namespace std;

Matrix::Matrix(int n, int m, int** arr) {
    rows_cnt = n;
    cols_cnt = m;
    matrix = new int*[rows_cnt];
    for (int row = 0; row < rows_cnt; ++row) {
        matrix[row] = new int[cols_cnt];
        for (int col = 0; col < cols_cnt; ++col)
            if (arr[row][col] != NULL)
                matrix[row][col] = arr[row][col];
            else
                abort();
    }
}

Matrix::Matrix(int n, int m) {
    rows_cnt = n;
    cols_cnt = m;
    matrix = new int*[rows_cnt];
    for (int i = 0; i < rows_cnt; ++i) {
        matrix[i] = new int[cols_cnt]{0};
    }
}

Matrix::Matrix(const Matrix& other){
    rows_cnt = other.rows_cnt;
    cols_cnt = other.cols_cnt;
    matrix = new int*[rows_cnt];

    for (int row = 0; row < rows_cnt; ++row){
        matrix[row] = new int[cols_cnt];

        for (int col = 0; col < cols_cnt; ++col)
            matrix[row][col] = other.matrix[row][col];
    }
}

Matrix::Matrix(){
    rows_cnt = 0;
    cols_cnt = 0;
    matrix = nullptr;
}

Matrix::~Matrix(){
    for (int i = 0; i <rows_cnt; ++i)
        delete[] matrix[i];

    delete[] matrix;
}

Matrix& Matrix::operator=(const Matrix& other){
    if (this == &other)
        return *this;

    for (int i = 0; i < rows_cnt; ++i)
        delete[] matrix[i];
    delete[] matrix;

    rows_cnt = other.rows_cnt;
    cols_cnt = other.cols_cnt;
    matrix = new int*[rows_cnt];

    for (int row = 0; row < rows_cnt; ++row){
        matrix[row] = new int[cols_cnt];

        for (int col = 0; col < cols_cnt; ++col)
            matrix[row][col] = other.matrix[row][col];
    }

    return *this;
}

int Matrix::GetNumOfRows() const{
    return rows_cnt;
}

int Matrix::GetNumOfCols() const{
    return cols_cnt;
}

int Matrix::GetEl(int row, int col) const{
    if (!(0 <= row && row < rows_cnt) || !(0 <= col && col < cols_cnt))
        abort();

    return matrix[row][col];
}

bool Matrix::operator==(const Matrix& other) const{
    if (rows_cnt != other.rows_cnt || cols_cnt != other.cols_cnt)
        return false;
    for (int row = 0; row < rows_cnt; ++row)
        for (int col = 0; col < cols_cnt; ++col)
            if (matrix[row][col] != other.matrix[row][col])
                return false;



    return true;
}

void Matrix::Print() const{

    for (int row = 0; row < rows_cnt; ++row){
        for (int col = 0; col < cols_cnt; ++col)
            cout << matrix[row][col] << " ";

        cout << endl;
    }
}

void Matrix::ReadMatrix(){
    for (int row = 0; row < rows_cnt; ++row)
        for (int col = 0; col < cols_cnt; ++col)
            cin >> matrix[row][col];


}


Matrix Matrix::Add(const Matrix& other) const{
    if (rows_cnt != other.rows_cnt || cols_cnt != other.cols_cnt)
        abort();

    Matrix ans(rows_cnt, cols_cnt);

    for (int row = 0; row < rows_cnt; ++row)
        for (int col = 0; col < cols_cnt; ++col)
            ans.matrix[row][col] = matrix[row][col] + other.matrix[row][col];

    return ans;
}

Matrix Matrix::Mult(const Matrix& other) const{
    if (cols_cnt != other.rows_cnt)
        abort();

    Matrix ans(rows_cnt, other.cols_cnt);

    for (int row = 0; row < rows_cnt; ++row){
        for (int col = 0; col < other.cols_cnt; ++col){
            int el = 0;
            for (int i = 0; i < cols_cnt; ++i)
                el += matrix[row][i] * other.matrix[i][col];

            ans.matrix[row][col] = el;
        }
    }

    return ans;
}

Matrix Matrix::MultByNum(int x) const{
    Matrix ans(rows_cnt, cols_cnt);

    for (int row = 0; row < rows_cnt; ++row)
        for (int col = 0; col < cols_cnt; ++col)
            ans.matrix[row][col] = matrix[row][col] * x;

    return ans;
}

Matrix Matrix::Transpose() const{
    Matrix ans(cols_cnt, rows_cnt);

    for (int row = 0; row < rows_cnt; ++row)
        for (int col = 0; col < cols_cnt; ++col)
            ans.matrix[col][row] = matrix[row][col];

    return ans;
}


int main(){
    int n = 2, m = 2;

    int** arr = new int*[n];
    for (int i = 0; i < n; i++){
        arr[i] = new int[m];
    }
    arr[0][0] = 1;
    arr[0][1] = 4;
    arr[1][0] = 6;
    arr[1][1] = 3;

    Matrix mat1(n, m, arr), mat2(2, 2), mat3(2, 3);

    mat2.ReadMatrix();
    mat3.ReadMatrix();

    cout << "1" << endl; 
    mat1.Print();
    cout << endl;
    cout << "2" << endl; 
    mat2.Print();
    cout << endl;
    cout << "3" << endl; 
    mat3.Print();
    cout << endl;

    cout << "Rows: " << mat1.GetNumOfRows() << endl;
    cout << "Cosl: " << mat1.GetNumOfCols() << endl;
    cout << "Element at [0,0]: " << mat1.GetEl(0, 0) << endl;

    Matrix mat_sum, mat_prod, mat_mult_by_n, mat_T;

    mat_sum = mat1.Add(mat2);
    mat_prod = mat1.Mult(mat3);
    mat_mult_by_n = mat2.MultByNum(2);
    mat_T = mat3.Transpose();

    cout << "1+2" << endl; 
    mat_sum.Print();
    cout << endl;
    cout << "1*3" << endl; 
    mat_prod.Print();
    cout << endl;
    cout << "2* by 2" << endl; 
    mat_mult_by_n.Print();
    cout << endl;
    cout << "3.T" << endl; 
    mat_T.Print();

}