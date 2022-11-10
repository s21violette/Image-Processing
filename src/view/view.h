#ifndef VIEW_H
#define VIEW_H

#include <QButtonGroup>
#include <QColorDialog>
#include <QDialog>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QMainWindow>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

#include "../controller/controller.h"
#include "customfilterdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class view;
}
QT_END_NAMESPACE
class view : public QMainWindow {
  Q_OBJECT

  enum LastMethod {
    init = 0,
    toning,
    negative,
    discoloration,
    emboss,
    sharpen,
    boxblur,
    gaussianblur,
    laplacianfilter,
    sobelfilter,
    custom,
    brightness,
    contrast,
    saturation
  };

 public:
  view(QWidget *parent = nullptr);
  ~view();

 private slots:
  void LoadFile();
  void SaveFile();

  void Discoloration();
  void Negative();
  void Toning();

  void Emboss();
  void Sharpen();
  void BoxBlur();
  void GaussianBlur();
  void LaplacianFilter();
  void SobelFilter();
  void Custom();

  void SliderBrightness();
  void on_spinBox_brightness_textChanged(const QString &arg1);
  void on_spinBox_brightness_valueChanged(int arg1);

  void SliderContrast();
  void on_spinBox_contrast_textChanged(const QString &arg1);
  void on_spinBox_contrast_valueChanged(int arg1);

  void SliderSaturation();
  void on_spinBox_saturation_textChanged(const QString &arg1);
  void on_spinBox_saturation_valueChanged(int arg1);

  void on_radioButton_HSL_clicked();
  void on_radioButton_HSV_clicked();

  void on_pushButton_reset_clicked();

  void SetScene(view::LastMethod last);

 private:
  Ui::view *ui_;
  QWidget *widget_;
  QGraphicsScene *scene_start_;
  QGraphicsScene *scene_finish_;
  QButtonGroup *group_;
  QString file_name_;
  QImage img, buf_img_, src_img_;
  LastMethod last_;
  s21::Controller *controller_;
  bool HSV;

  void ChangeBrightness(int brightness);
  void ChangeContrast(double contrast_slider);
  void HSVMethod(double saturation_slider);
  void HSLMethod(double saturation_slider);

  void StartSettings();
  void ConnectSlots();
  bool OpenFile();

  void CheckLastMethod(LastMethod last_method);
};
#endif  // VIEW_H
