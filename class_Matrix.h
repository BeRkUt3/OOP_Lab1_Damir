class Matrix{
private:
    int rows_cnt, cols_cnt;
    int** matrix;

public:
    Matrix(int n, int m, int** arr);
    Matrix(int n, int m);
    Matrix();
    Matrix(const Matrix& other);
    ~Matrix();

    Matrix& operator=(const Matrix& other);

    int GetNumOfRows() const;
    int GetNumOfCols() const;
    int GetEl(int row, int col) const;
    void ReadMatrix();
    void Print() const;

    bool operator==(const Matrix& other) const;

    Matrix Add(const Matrix& other) const;
    Matrix Mult(const Matrix& other) const;
    Matrix MultByNum(int x) const;
    Matrix Transpose() const;
};