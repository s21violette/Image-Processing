#include "matrix.h"
#include <cmath>


namespace s21 {
template <typename T>
Matrix<T>::Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows_ < 0 || cols_ < 0) error_ = true;

  if (!error_) CreateMatrix();
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<T> const &items) 
    : rows_(sqrt(items.size())), cols_(sqrt(items.size())), matrix_(nullptr) {
  if (fmod((items.size()), sqrt(items.size())) != 0) error_ = true;

  if (!error_) {
    CreateMatrix();
    this->InitMatrix(items);
  }
}

template <typename T>
void Matrix<T>::InitMatrix(std::initializer_list<T> const &items) {
  auto it = items.begin();
  for(auto i = 0; i < rows_; i++) {
    std::memmove(matrix_[i], it, sizeof(*it)* cols_);
    for(auto j = 0; j < cols_; j++)
      it++;
  }
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();
  CopyMatrix(other);
}

template <typename T>
Matrix<T>::~Matrix() {
  DeleteMatrix();
}

template <typename T>
void Matrix<T>::CreateMatrix() {
  matrix_ = new T*[rows_];
  for (auto i = 0; i < rows_; i++) matrix_[i] = new T[cols_]();
}

template <typename T>
int Matrix<T>::GetCols() const {
  return cols_;
}

template <typename T>
int Matrix<T>::GetRows() const {
  return rows_;
}

template <typename T>
void Matrix<T>::SetRows(const int rows) {
    if (rows < 1)
        throw std::out_of_range("Error: Wrong rows size");
    if (rows != this->rows_)
        this->ResizeMatrix(rows, this->cols_);
}

template <typename T>
void Matrix<T>::SetCols(const int cols) {
    if (cols < 1)
        throw std::out_of_range("Error: Wrong cols size");
    if (cols != this->cols_)
        this->ResizeMatrix(this->rows_, cols);
}

template <typename T>
void Matrix<T>::ResizeMatrix(int rows, int cols) {
    Matrix<T> new_matrix(rows, cols);
    int min_rows = (rows < this->rows_) ? rows : this->rows_;
    int min_cols = (cols < this->cols_) ? cols : this->cols_;
    for (auto row = 0; row < min_rows; row++)
        std::memcpy(new_matrix.matrix_[row], this->matrix_[row], min_cols * sizeof(double));
    *this = new_matrix;
}

template <typename T>
void Matrix<T>::DeleteMatrix() {
  if (matrix_ != nullptr) {
    for (auto i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
    matrix_ = nullptr;
  }
  cols_ = 0;
  rows_ = 0;
}

template <typename T>
bool Matrix<T>::IsEqualSize(const Matrix& other) {
  return (cols_ == other.cols_ && rows_ == other.rows_);
}

template <typename T>
bool Matrix<T>::IsEqualMatrix(const Matrix& other) {
  bool flag_equal = IsEqualSize(other);
  if (flag_equal) {
    for (int i = 0; i < rows_ && flag_equal; i++)
      if (std::memcmp(matrix_[i], other.matrix_[i],
                      sizeof(*matrix_[i]) * cols_) != 0)
        flag_equal = false;
  }
  return flag_equal;
}

template <typename T>
void Matrix<T>::CopyMatrix(Matrix const& other) {
  if (!IsEqualSize(other)) {
    DeleteMatrix();
    cols_ = other.cols_;
    rows_ = other.rows_;
    CreateMatrix();
  }
  if (matrix_ != nullptr) {
    for (auto i = 0; i < rows_; i++)
      std::memcpy(matrix_[i], other.matrix_[i], sizeof(*matrix_[i]) * cols_);
  }
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
  if (&other != this) CopyMatrix(other);  
  return *this;
}

template <typename T>
T& Matrix<T>::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::range_error("Incorrect matrix size");
  return matrix_[row][col];
}

template <class T>
bool Matrix<T>::operator==(const Matrix& other) {
  return IsEqualMatrix(other);
}

}  // namespace s21

template class s21::Matrix<bool>;
template class s21::Matrix<double>;
template class s21::Matrix<float>;
template class s21::Matrix<int>;
