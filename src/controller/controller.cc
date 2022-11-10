#include "controller.h"

namespace s21 {

Controller::Controller() { model_ = new Model(); }

Controller::~Controller() { delete model_; }

void Controller::SetToning(QColor toning_color, QImage &img, QImage &buf_img) {
  model_->Toning(toning_color, img, buf_img);
}

void Controller::SetNegative(QImage &img, QImage &buf_img) {
  model_->Negative(img, buf_img);
}

void Controller::SetDiscoloration(QImage &img, QImage &buf_img) {
  model_->Discoloration(img, buf_img);
}

void Controller::SetBrightness(QImage &img, QImage &buf_img, int brightness) {
  model_->Brightness(img, buf_img, brightness);
}

void Controller::SetContrast(QImage &img, QImage &buf_img, double contrast) {
  model_->Contrast(img, buf_img, contrast);
}

void Controller::SetHSV(QImage &img, QImage &buf_img, double saturation) {
  model_->HSV(img, buf_img, saturation);
}

void Controller::SetHSL(QImage &img, QImage &buf_img, double saturation) {
  model_->HSL(img, buf_img, saturation);
}

void Controller::SetEmboss(QImage &img, QImage &buf_img) {
  Matrix<int> filter = EMBOSS;
  model_->Convolution(img, buf_img, filter);
}

void Controller::SetSharpen(QImage &img, QImage &buf_img) {
  Matrix<int> filter = SHARPEN;
  model_->Convolution(img, buf_img, filter);
}

void Controller::SetBoxBlur(QImage &img, QImage &buf_img) {
  Matrix<int> filter = BOXBLUR;
  model_->Convolution(img, buf_img, filter);
}

void Controller::SetGaussianBlur(QImage &img, QImage &buf_img) {
  Matrix<int> filter = GAUSSIANBLUR;
  model_->Convolution(img, buf_img, filter);
}

void Controller::SetLaplacianFilter(QImage &img, QImage &buf_img) {
  Matrix<int> filter = LAPLACIANFILTER;
  model_->Convolution(img, buf_img, filter);
}

void Controller::SetSobelFilter(QImage &img, QImage &buf_img) {
  Matrix<int> filter = SOBELFILTER;
  model_->Convolution(img, buf_img, filter);
}

void Controller::SetCustomFilter(QImage &img, QImage &buf_img,
                                 Matrix<int> &filter) {
  model_->Convolution(img, buf_img, filter);
}

}  // namespace s21
