#ifndef RENDER_H
#define RENDER_H

#include <QImage>
#include <vector>

#include "helpers/matrix.h"

namespace s21 {

enum rgb { red, green, blue };

class Model {
 public:
  Model();
  void Toning(QColor toning_color, QImage &img, QImage &buf_img);
  void Negative(QImage &img, QImage &buf_img);
  void Discoloration(QImage &img, QImage &buf_img);
  void Convolution(QImage &img, QImage &buf_img,
                   s21::Matrix<int> &convolution_kernel);
  void Brightness(QImage &img, QImage &buf_img, int brightness);
  void Contrast(QImage &img, QImage &buf_img, double contrast);
  void HSV(QImage &img, QImage &buf_img, double saturation_delta);
  void HSL(QImage &img, QImage &buf_img, double saturation_delta);

 private:
  double MinColor(double red, double green, double blue);
  double MaxColor(double red, double green, double blue);
  double GetHue(double red, double green, double blue, double delta,
                double cMax);
  void SetRGB(double &red, double &green, double &blue, double hue, double c,
              double x, double m);
};
}  // namespace s21

#endif  // RENDER_H
