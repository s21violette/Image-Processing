#include "view.h"

#include "ui_view.h"

view::view(QWidget *parent) : QMainWindow(parent), ui_(new Ui::view) {
  ui_->setupUi(this);
  widget_ = new QWidget();
  widget_->setLayout(ui_->verticalLayout);
  setCentralWidget(widget_);
  StartSettings();
  ConnectSlots();
  controller_ = new s21::Controller();
}

view::~view() {
  delete scene_start_;
  delete scene_finish_;
  delete controller_;
  delete group_;
  delete widget_;
  delete ui_;
}

void view::LoadFile() {
  if (OpenFile()) {
    scene_start_->clear();
    scene_finish_->clear();
    ui_->horizontalSlider->setValue(0);
    ui_->horizontalSlider_2->setValue(0);
    ui_->horizontalSlider_3->setValue(0);
    QPixmap image;
    image.load(file_name_);
    scene_start_->addPixmap(image);
    scene_start_->setSceneRect(image.rect());
    scene_finish_->addPixmap(image);
    scene_finish_->setSceneRect(image.rect());

    img = QImage(file_name_);
    buf_img_ = src_img_ = img;
  }
}

bool view::OpenFile() {
  file_name_ = QFileDialog::getOpenFileName(
      this, tr("Open file"), QCoreApplication::applicationDirPath(),
      tr("*.bmp"));
  return (file_name_ != nullptr);
}

void view::SaveFile() {
  file_name_ = QFileDialog::getSaveFileName(this, tr("Save file"), "",
                                            tr("image (*.bmp)"));
  QImage image(scene_finish_->width(), scene_finish_->height(),
               QImage::Format_ARGB32_Premultiplied);
  QPainter painter(&image);
  scene_finish_->render(&painter);
  image.save(file_name_);
}

void view::SetScene(LastMethod last) {
  QPixmap temp = QPixmap::fromImage(buf_img_);
  scene_finish_->clear();
  scene_finish_->addPixmap(temp);
  scene_finish_->setSceneRect(temp.rect());
  last_ = last;
}

void view::Discoloration() {
  CheckLastMethod(LastMethod::discoloration);
  controller_->SetDiscoloration(img, buf_img_);
  SetScene(LastMethod::discoloration);
}

void view::Negative() {
  CheckLastMethod(LastMethod::negative);
  controller_->SetNegative(img, buf_img_);
  SetScene(LastMethod::negative);
}

void view::Toning() {
  QColor toning_color = QColorDialog::getColor();
  if (!toning_color.isValid()) return;
  CheckLastMethod(LastMethod::toning);
  controller_->SetToning(toning_color, img, buf_img_);
  SetScene(LastMethod::toning);
}

void view::Emboss() {
  CheckLastMethod(LastMethod::emboss);
  controller_->SetEmboss(img, buf_img_);
  SetScene(LastMethod::emboss);
}

void view::Sharpen() {
  CheckLastMethod(LastMethod::sharpen);
  controller_->SetSharpen(img, buf_img_);
  SetScene(LastMethod::sharpen);
}

void view::BoxBlur() {
  CheckLastMethod(LastMethod::boxblur);
  controller_->SetBoxBlur(img, buf_img_);
  SetScene(LastMethod::boxblur);
}

void view::GaussianBlur() {
  CheckLastMethod(LastMethod::gaussianblur);
  controller_->SetGaussianBlur(img, buf_img_);
  SetScene(LastMethod::gaussianblur);
}

void view::LaplacianFilter() {
  CheckLastMethod(LastMethod::laplacianfilter);
  controller_->SetLaplacianFilter(img, buf_img_);
  SetScene(LastMethod::laplacianfilter);
}

void view::SobelFilter() {
  CheckLastMethod(LastMethod::sobelfilter);
  controller_->SetSobelFilter(img, buf_img_);
  SetScene(LastMethod::sobelfilter);
}

void view::Custom() {
  CheckLastMethod(LastMethod::custom);
  CustomFilterDialog dlg(this);
  dlg.exec();
  s21::Matrix<int> custom_filter = *dlg.GetFilter();
  controller_->SetCustomFilter(img, buf_img_, custom_filter);
  SetScene(LastMethod::custom);
}

void view::ChangeBrightness(int brightness) {
  CheckLastMethod(LastMethod::brightness);
  controller_->SetBrightness(img, buf_img_, brightness);
  SetScene(LastMethod::brightness);
}

void view::ChangeContrast(double contrast_slider) {
  if (img.isNull()) return;
  CheckLastMethod(LastMethod::contrast);
  controller_->SetContrast(img, buf_img_, contrast_slider);
  SetScene(LastMethod::contrast);
}

void view::HSLMethod(double saturation_slider) {
  if (img.isNull()) return;
  CheckLastMethod(LastMethod::saturation);
  controller_->SetHSL(img, buf_img_, saturation_slider);
  SetScene(LastMethod::saturation);
}

void view::HSVMethod(double saturation_slider) {
  if (img.isNull()) return;
  CheckLastMethod(LastMethod::saturation);
  controller_->SetHSV(img, buf_img_, saturation_slider);
  SetScene(LastMethod::saturation);
}

void view::CheckLastMethod(LastMethod last_method) {
  if (last_ != last_method) {
    img = buf_img_;
  }
}

void view::SliderSaturation() {
  if (HSV == true) {
    HSVMethod(ui_->horizontalSlider_3->value());
  } else {
    HSLMethod(ui_->horizontalSlider_3->value());
  }
}

void view::on_spinBox_saturation_textChanged(const QString &arg1) {
  if (HSV == true) {
    HSVMethod(ui_->spinBox_saturation->value());
  } else {
    HSLMethod(ui_->spinBox_saturation->value());
  }
}

void view::on_spinBox_saturation_valueChanged(int arg1) {
  if (HSV == true) {
    HSVMethod(arg1);
  } else {
    HSLMethod(arg1);
  }
}

void view::on_radioButton_HSL_clicked() { HSV = false; }

void view::on_radioButton_HSV_clicked() { HSV = true; }

void view::on_pushButton_reset_clicked() {
  img = buf_img_ = src_img_;
  SetScene(LastMethod::init);
  ui_->horizontalSlider->setValue(0);
  ui_->horizontalSlider_2->setValue(0);
  ui_->horizontalSlider_3->setValue(0);
  ui_->spinBox_brightness->setValue(0);
  ui_->spinBox_contrast->setValue(0);
  ui_->spinBox_saturation->setValue(0);
}

void view::SliderBrightness() {
  int brightness = ui_->horizontalSlider->value();
  ChangeBrightness(brightness);
}

void view::on_spinBox_brightness_textChanged(const QString &arg1) {
  int brightness = ui_->spinBox_brightness->value();
  ChangeBrightness(brightness);
}

void view::on_spinBox_brightness_valueChanged(int arg1) {
  ChangeBrightness(arg1);
}

void view::SliderContrast() {
  ChangeContrast(ui_->horizontalSlider_2->value());
}

void view::on_spinBox_contrast_textChanged(const QString &arg1) {
  ChangeContrast(ui_->spinBox_contrast->value());
}

void view::on_spinBox_contrast_valueChanged(int arg1) { ChangeContrast(arg1); }

void view::StartSettings() {
  scene_start_ = new QGraphicsScene();
  scene_finish_ = new QGraphicsScene();

  ui_->radioButton_HSL->setChecked(true);
  group_ = new QButtonGroup();
  group_->addButton(ui_->radioButton_HSL);
  group_->addButton(ui_->radioButton_HSV);
  HSV = false;
  last_ = LastMethod::init;

  ui_->startView->setScene(scene_start_);
  ui_->finishView->setScene(scene_finish_);
}

void view::ConnectSlots() {
  connect(ui_->actionOpen, SIGNAL(triggered(bool)), this, SLOT(LoadFile()));
  connect(ui_->actionSave, SIGNAL(triggered(bool)), this, SLOT(SaveFile()));

  connect(ui_->actionDiscoloration, SIGNAL(triggered(bool)), this,
          SLOT(Discoloration()));
  connect(ui_->actionNegative, SIGNAL(triggered(bool)), this, SLOT(Negative()));
  connect(ui_->actionToning, SIGNAL(triggered(bool)), this, SLOT(Toning()));

  connect(ui_->actionEmboss, SIGNAL(triggered(bool)), this, SLOT(Emboss()));
  connect(ui_->actionSharpen, SIGNAL(triggered(bool)), this, SLOT(Sharpen()));
  connect(ui_->actionBox_blur, SIGNAL(triggered(bool)), this, SLOT(BoxBlur()));
  connect(ui_->actionGaussian_blur, SIGNAL(triggered(bool)), this,
          SLOT(GaussianBlur()));
  connect(ui_->actionLaplacian_filter, SIGNAL(triggered(bool)), this,
          SLOT(LaplacianFilter()));
  connect(ui_->actionSobel_filter, SIGNAL(triggered(bool)), this,
          SLOT(SobelFilter()));
  connect(ui_->actionCustom_filter, SIGNAL(triggered(bool)), this,
          SLOT(Custom()));

  connect(ui_->horizontalSlider, SIGNAL(valueChanged(int)), this,
          SLOT(SliderBrightness()));
  connect(ui_->horizontalSlider_2, SIGNAL(valueChanged(int)), this,
          SLOT(SliderContrast()));
  connect(ui_->horizontalSlider_3, SIGNAL(valueChanged(int)), this,
          SLOT(SliderSaturation()));
}
