#ifndef CUSTOMFILTERDIALOG_H
#define CUSTOMFILTERDIALOG_H

#include <QBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
#include <QWidget>

#include "../model/helpers/matrix.h"

class CustomFilterDialog : public QDialog {
  Q_OBJECT
 public:
  CustomFilterDialog(QWidget *parent = nullptr);
  ~CustomFilterDialog();

  s21::Matrix<int> *GetFilter();

 private:
  QTableWidget *matrix;

  int CheckValue(QString cell);

 private slots:
  void ResizeMatrix(int size);
  void CloseDialog();
};

#endif  // CUSTOMFILTERDIALOG_H
