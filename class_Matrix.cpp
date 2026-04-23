#include <bits/stdc++.h>
#include "class_Matrix.h"

#define endl '\n'

using namespace std;

Matrix::Matrix(int n, int m, int** arr): rows_cnt(n), cols_cnt(m) {
    if (n <= 0 || m <= 0)
        abort();
    Node* last = new Node(0, 0, arr[0][0]);
    matrix = last;
    for (int row = 0; row < rows_cnt; ++row) {
        for (int col = 0; col < cols_cnt; ++col){
            if (row == 0 && col == 0)
                continue;
            if (arr[row][col] != 0){
                Node* node = new Node(row, col, arr[row][col]);
                last->nx = node;
                last = node;
            }
        }
    }
}

Matrix::Matrix(int n, int m): rows_cnt(n), cols_cnt(m), matrix(nullptr){};

Matrix::Matrix(Matrix&& other): rows_cnt(other.rows_cnt), cols_cnt(other.cols_cnt), matrix(other.matrix){
    other.rows_cnt = 0;
    other.cols_cnt = 0;
    other.matrix = nullptr;
}

Matrix::Matrix(const Matrix& other): rows_cnt(other.rows_cnt), cols_cnt(other.cols_cnt){
    matrix = nullptr;
    Node* last = nullptr;

    Node* cur = other.matrix;
    while (cur){
        Node* node = new Node(cur->i, cur-> j, cur->val);
        if (!matrix){
            matrix = node;
            last = node;
        } else {
            last->nx = node;
            last = node;
        }
        cur = cur->nx;
    }
    
}

Matrix::Matrix(): rows_cnt(0), cols_cnt(0), matrix(nullptr){
}

Matrix::~Matrix(){
    while (matrix){
        Node* node = matrix;
        matrix = matrix->nx;
        delete node;
    }
}

Matrix& Matrix::operator=(const Matrix& other){
    if (this == &other)
        return *this;

    while (matrix){
        Node* node = matrix;
        matrix = matrix->nx;
        delete node;
    }

    rows_cnt = other.rows_cnt;
    cols_cnt = other.cols_cnt;
    matrix = nullptr;
    Node* last = nullptr;

    Node* cur = other.matrix;
    while (cur){
        Node* node = new Node(cur->i, cur-> j, cur->val);
        if (!matrix){
            matrix = node;
            last = node;
        } else {
            last->nx = node;
            last = node;
        }
        cur = cur->nx;
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

    Node* cur = matrix;
    while (cur){
        if (cur->i == row && cur->j == col)
            return cur->val;
        cur = cur->nx;
    }
    return 0;
}


bool Matrix::Equals(const Matrix& other) const{
    if (rows_cnt != other.rows_cnt || cols_cnt != other.cols_cnt)
        return false;
    Node* cur1 = matrix;
    Node* cur2 = other.matrix;

    while (cur1 && cur2){
        if (cur1->i != cur2->i || cur1->j != cur2->j || cur1->val != cur2->val)
            return false;
        cur1 = cur1->nx;
        cur2 = cur2->nx;
    }
    if (cur1 || cur2)
        return false;
    
    return true;
}

void Matrix::Print() const{

    for (int row = 0; row < rows_cnt; ++row){
        for (int col = 0; col < cols_cnt; ++col)
            cout << GetEl(row, col) << " ";

        cout << endl;
    }
}

void Matrix::ReadMatrix(){

    while (matrix){
        Node* node = matrix;
        matrix = matrix->nx;
        delete node;
    }

    cin >> rows_cnt >> cols_cnt;
    matrix = nullptr;
    Node* last = nullptr;

    for (int i = 0; i < rows_cnt; ++i){
        for (int j = 0; j < cols_cnt; ++j){
            int val;
            cin >> val;
            if (val == 0)
                continue;
            Node* node = new Node(i, j, val);
            if (!matrix){
                matrix = node;
                last = node;
            } else {
                last->nx = node;
                last = node;
            }
        }
    }


}


Matrix Matrix::Add(const Matrix& other) const{
    if (rows_cnt != other.rows_cnt || cols_cnt != other.cols_cnt)
        abort();

    Matrix ans(rows_cnt, cols_cnt);
    Node* last = nullptr;

    Node* cur1 = matrix;
    Node* cur2 = other.matrix;

    while (cur1 || cur2){
        Node* node;
        if (!cur1){
            node = new Node(cur2->i, cur2->j, cur2->val);
            cur2 = cur2->nx;
        } else if (!cur2){
            node = new Node(cur1->i, cur1->j, cur1->val);
            cur1 = cur1->nx;
        } else {
            if (cur1->i*cols_cnt+cur1->j < cur2->i*cols_cnt+cur2->j){
                node = new Node(cur1->i, cur1->j, cur1->val);
                cur1 = cur1->nx;
            } else if (cur1->i*cols_cnt+cur1->j > cur2->i*cols_cnt+cur2->j){
                node = new Node(cur2->i, cur2->j, cur2->val);
                cur2 = cur2->nx;
            } else {
                node = new Node(cur1->i, cur1->j, cur1->val+cur2->val);
                cur1 = cur1->nx;
                cur2 = cur2->nx;
            }
        }

        if (node->val == 0){
            delete node;
            continue;
        }

        if (!ans.matrix){
            ans.matrix = node;
            last = node;
        } else {
            last->nx = node;
            last = node;
        }
    }
    return ans;
}

Matrix Matrix::Mult(const Matrix& other) const{
    if (cols_cnt != other.rows_cnt)
        abort();

    Matrix ans(rows_cnt, other.cols_cnt);
    Node* last = nullptr;
    Node* cur1 = matrix;
    Node* cur2 = other.matrix;
    int i = 0, j = 0, el;
    while (i < rows_cnt){
        if (j == other.cols_cnt){
            ++i;
            j = 0;
        }
        el = 0;
        cur1 = matrix;
        cur2 = other.matrix;
        while (cur1){
            if (cur1->i > i)
                break;
            while (cur2 && (cur2->i < cur1->j || (cur2->i == cur1->j && cur2->j < j))){
                cur2 = cur2->nx;
            }
            if (cur1 && cur2 && cur1->i == i && cur1->j == cur2->i && cur2->j == j)
                el += cur1->val*cur2->val;
            cur1 = cur1->nx;
        }

        if (el){
            Node* node = new Node(i, j, el);
            if (!ans.matrix){
                ans.matrix = node;
                last = node;
            } else {
                last->nx = node;
                last = node;
            }
        }
        ++j;
    }

    return ans;
}

Matrix Matrix::MultByNum(int x) const{
    Matrix ans(GetNumOfRows(), GetNumOfCols());
    if (x == 0){
        return ans;
    }

    Node* last = nullptr;
    Node* cur = matrix;
    while (cur){
        Node* node = new Node(cur->i, cur->j, cur->val*x);
        if (!ans.matrix){
            ans.matrix = node;
            last = node;
        } else {
            last->nx = node;
            last = node;
        }
        cur = cur->nx;
    }

    return ans;
}

Matrix Matrix::Transpose() const{
    Matrix ans(cols_cnt, rows_cnt);
    Node* last = nullptr;
    Node* cur;
    for (int i = 0; i < cols_cnt; ++i){
        cur = matrix;
        while (cur){
            if (cur->j == i){
                Node* node = new Node(cur->j, cur->i, cur->val);
                if (!ans.matrix){
                    ans.matrix = node;
                    last = node;
                } else {
                    last->nx = node;
                    last = node;
                }
            }
            cur = cur->nx;
        }
    }

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

    Matrix mat1(n, m, arr), mat2(2, 2), mat3 = Matrix(2, 3);

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

    cout << "1 == 1 " << mat1.Equals(mat1) << endl;
    cout << "1 == 2 " << mat1.Equals(mat2) << endl;

    Matrix mat_sum, mat_prod, mat_mult_by_n, mat_T;

    mat_sum = mat1.Add(mat2);
    cout << "1+2" << endl; 
    mat_sum.Print();
    cout << endl;
    mat_prod = mat1.Mult(mat3);
    cout << "1*3" << endl; 
    mat_prod.Print();
    cout << endl;
    mat_mult_by_n = mat2.MultByNum(2);
    cout << "2* by 2" << endl; 
    mat_mult_by_n.Print();
    cout << endl;
    mat_T = mat3.Transpose();
    cout << "3.T" << endl; 
    mat_T.Print();

    for (int i = 0; i < n; i++)
        delete[] arr[i];
    delete[] arr;
}
