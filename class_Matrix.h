class Matrix{
private:
    struct Node{
        int i, j, val;
        Node* nx;
        Node(int row, int col, int value){
            i = row;
            j = col;
            val = value;
            nx = nullptr;
        }

    };

    int rows_cnt, cols_cnt;
    Node* matrix;

public:
    Matrix(int n, int m, int** arr);
    Matrix(int n, int m);
    Matrix(Matrix&& other);
    Matrix();
    Matrix(const Matrix& other);
    ~Matrix();

    Matrix& operator=(const Matrix& other);

    int GetNumOfRows() const;
    int GetNumOfCols() const;
    int GetEl(int row, int col) const;
    void ReadMatrix();
    void Print() const;

    bool Equals(const Matrix& other) const;

    Matrix Add(const Matrix& other) const;
    Matrix Mult(const Matrix& other) const;
    Matrix MultByNum(int x) const;
    Matrix Transpose() const;
};
