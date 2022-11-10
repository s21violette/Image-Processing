#include "customfilterdialog.h"

CustomFilterDialog::CustomFilterDialog(QWidget *parent) : QDialog(parent) {
  this->setWindowTitle("Enter the filter kernel");
  this->setMaximumSize(520, 550);
  this->setMinimumSize(520, 550);
  QBoxLayout *common_layout = new QVBoxLayout;
  QBoxLayout *size_layout = new QHBoxLayout;

  QLabel *size_label = new QLabel("Size");
  size_layout->addWidget(size_label);

  QSpinBox *size_spin = new QSpinBox();
  size_spin->setRange(3, 15);
  size_spin->setValue(3);
  size_spin->setSingleStep(2);
  size_spin->setMaximumSize(60, 20);
  size_layout->addWidget(size_spin);
  connect(size_spin, SIGNAL(valueChanged(int)), this, SLOT(ResizeMatrix(int)));

  common_layout->addLayout(size_layout);

  QBoxLayout *table = new QHBoxLayout;
  matrix = new QTableWidget(3, 3);

  for (int i = 0; i < 3; i++) {
    matrix->setColumnWidth(i, 30);
    for (int j = 0; j < 3; j++)
      matrix->setItem(i, j, new QTableWidgetItem("0"));
  }

  table->addWidget(matrix);
  common_layout->addLayout(table);

  QPushButton *button = new QPushButton("OK");
  connect(button, SIGNAL(clicked()), SLOT(CloseDialog()));
  common_layout->addWidget(button);

  setLayout(common_layout);
}

CustomFilterDialog::~CustomFilterDialog() {}

void CustomFilterDialog::ResizeMatrix(int size) {
  int start_size = matrix->columnCount();
  size = (size % 2 == 0) ? size + 1 : size;

  matrix->setColumnCount(size);
  matrix->setRowCount(size);
  if (size > start_size) {
    for (int i = 0; i < matrix->columnCount(); i++) {
      matrix->setColumnWidth(i, 30);
      for (int j = 0; j < matrix->columnCount(); j++) {
        if (i < start_size && j < start_size) continue;
        matrix->setItem(i, j, new QTableWidgetItem("0"));
      }
    }
  }
}

void CustomFilterDialog::CloseDialog() { close(); }

s21::Matrix<int> *CustomFilterDialog::GetFilter() {
  s21::Matrix<int> *filter_ =
      new s21::Matrix<int>(matrix->columnCount(), matrix->columnCount());
  for (int i = 0; i < filter_->GetCols(); i++) {
    for (int j = 0; j < filter_->GetRows(); j++) {
      filter_->operator()(i, j) = CheckValue(matrix->item(i, j)->text());
    }
  }
  return filter_;
}

int CustomFilterDialog::CheckValue(QString cell) {
  bool flag = !cell.isEmpty();
  for (int i = 0; flag && i < cell.size(); i++)
    if (!cell[i].isDigit() && cell[i] != '-' &&
        (cell[i] == '-' && cell.size() == 1))
      flag = false;
  return flag ? cell.toInt() : 0;
}
