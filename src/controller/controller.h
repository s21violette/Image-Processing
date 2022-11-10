#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"

namespace s21 {

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
  { 1, 0, -1, 2, 0, -2, 1, 0, -1 }  // left
#define SOBELFILTERRIGHT \
  { -1, 0, 1, -2, 0, 2, -1, 0, 1 }  // right

class Controller {
 public:
  Controller();
  ~Controller();
  void SetToning(QColor toning_color, QImage &img, QImage &buf_img);
  void SetNegative(QImage &img, QImage &buf_img);
  void SetDiscoloration(QImage &img, QImage &buf_img);
  void SetEmboss(QImage &img, QImage &buf_img);
  void SetSharpen(QImage &img, QImage &buf_img);
  void SetBoxBlur(QImage &img, QImage &buf_img);
  void SetGaussianBlur(QImage &img, QImage &buf_img);
  void SetLaplacianFilter(QImage &img, QImage &buf_img);
  void SetSobelFilter(QImage &img, QImage &buf_img);
  void SetCustomFilter(QImage &img, QImage &buf_img, Matrix<int> &filter);
  void SetBrightness(QImage &img, QImage &buf_img, int brightness);
  void SetContrast(QImage &img, QImage &buf_img, double contrast);
  void SetHSV(QImage &img, QImage &buf_img, double saturation);
  void SetHSL(QImage &img, QImage &buf_img, double saturation);

 private:
  Model *model_;
};

}  // namespace s21
#endif  // CONTROLLER_H
