#ifndef TEST_H
#define TEST_H

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>  //  прямая зависимость от того, где лежит библиотека на компе (в файле *.pri)

#include "../model/model.h"

#define EMBOSS \
  { -2, -1, 0, -1, 1, 1, 0, 1, 2 }
#define SHARPEN \
  { -1, -1, -1, -1, 9, -1, -1, -1, -1 }
#define BOXBLUR \
  { 1, 1, 1, 1, 1, 1, 1, 1, 1 }
#define GAUSSIANBLUR \
  { 1, 2, 1, 2, 4, 2, 1, 2, 1 }
#define LAPLACIANFILTER \
  { -1, -1, -1, -1, 8, -1, -1, -1, -1 }
#define SOBELFILTER \
  { 1, 0, -1, 2, 0, -2, 1, 0, -1 }
#define CUSTOM \
  { 1, 1, 1, 0, 0, 0, -1, -1, -1 }

class PhotoLab : public testing::Test {
 protected:
  QImage image_base;
  QImage image_standart;
  s21::Model* model_;

  void SetUp() {
    image_base = QImage("../../datasets/test-home.bmp");
    image_standart = QImage("../../datasets/test-home.bmp");
    model_ = new s21::Model();
  }
  void TearDown() { delete model_; }
};

#endif  // TEST_H
