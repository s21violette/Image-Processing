#include "model.h"

namespace s21 {

Model::Model() {}

static int FindDiv(s21::Matrix<int> &convolution_kernel) {
  int div = 0;
  for (int i = 0; i < convolution_kernel.GetRows(); i++)
    for (int j = 0; j < convolution_kernel.GetCols(); j++)
      div += convolution_kernel.operator()(i, j);
  return (div != 0) ? div : 1;
}

static void setColor(QImage &buf_img, s21::rgb color, int value, int i, int j) {
  if (color == s21::rgb::red)
    buf_img.setPixelColor(i, j,
                          QColor(value, buf_img.pixelColor(i, j).green(),
                                 buf_img.pixelColor(i, j).blue()));
  else if (color == s21::rgb::green)
    buf_img.setPixelColor(i, j,
                          QColor(buf_img.pixelColor(i, j).red(), value,
                                 buf_img.pixelColor(i, j).blue()));
  else
    buf_img.setPixelColor(i, j,
                          QColor(buf_img.pixelColor(i, j).red(),
                                 buf_img.pixelColor(i, j).green(), value));
}

static int getColor(QImage &img, s21::rgb color, int i, int j, int kernel) {
  int result = 0;
  if (color == s21::rgb::red)
    result = img.pixelColor(i, j).red() * kernel;
  else if (color == s21::rgb::green)
    result = img.pixelColor(i, j).green() * kernel;
  else
    result = img.pixelColor(i, j).blue() * kernel;
  return result;
}

static void DoConvuletion(QImage &img, QImage &buf_img, s21::rgb color,
                          s21::Matrix<int> &kernel, int div) {
  for (int i = 0; i < img.size().height(); i++) {
    for (int j = 0; j < img.size().width(); j++) {
      int color_res = 0;
      for (int n = -(kernel.GetRows() / 2) + i, x = 0;
           n <= (kernel.GetRows() / 2) + i; n++, x++) {
        for (int m = -(kernel.GetCols() / 2) + j, y = 0;
             m <= (kernel.GetCols() / 2) + j; m++, y++) {
          if ((n < 0 && m < 0) ||
              (n >= img.size().height() && m >= img.size().width()) ||
              (n < 0 && m >= img.size().width()) ||
              (n >= img.size().height() && m < 0))
            color_res += getColor(img, color, i, j, kernel(x, y));
          else if (n < 0 || n >= img.size().height())
            color_res += getColor(img, color, i, m, kernel(x, y));
          else if (m < 0 || m >= img.size().width())
            color_res += getColor(img, color, n, j, kernel(x, y));
          else
            color_res += getColor(img, color, n, m, kernel(x, y));
        }
      }
      color_res = color_res * (1. / (double)div);
      color_res = (color_res < 0) ? 0 : (color_res > 255) ? 255 : color_res;
      setColor(buf_img, color, color_res, i, j);
    }
  }
}

void Model::Convolution(QImage &img, QImage &buf_img,
                        s21::Matrix<int> &convolution_kernel) {
  int div = FindDiv(convolution_kernel);
  DoConvuletion(img, buf_img, rgb::red, convolution_kernel, div);
  DoConvuletion(img, buf_img, rgb::green, convolution_kernel, div);
  DoConvuletion(img, buf_img, rgb::blue, convolution_kernel, div);
}

void Model::Discoloration(QImage &img, QImage &buf_img) {
  for (int i = 0; i < img.size().width(); i++) {
    for (int j = 0; j < img.size().height(); j++) {
      double middle =
          (img.pixelColor(i, j).red() + img.pixelColor(i, j).green() +
           img.pixelColor(i, j).blue()) /
          3;
      buf_img.setPixelColor(i, j, QColor(middle, middle, middle));
    }
  }
}

void Model::Negative(QImage &img, QImage &buf_img) {
  for (int i = 0; i < img.size().width(); i++) {
    for (int j = 0; j < img.size().height(); j++) {
      buf_img.setPixelColor(i, j,
                            QColor(255 - img.pixelColor(i, j).red(),
                                   255 - img.pixelColor(i, j).green(),
                                   255 - img.pixelColor(i, j).blue()));
    }
  }
}

void Model::Toning(QColor toning_color, QImage &img, QImage &buf_img) {
  std::vector<int> rgb = {toning_color.red(), toning_color.green(),
                          toning_color.blue()};
  std::vector<double> koef;
  for (int i = 0; i < 3; i++) {
    double temp;
    if (rgb[i] - *std::min_element(rgb.begin(), rgb.end()) < 30 ||
        std::accumulate(rgb.begin(), rgb.end(), 0) / 3 == rgb[i])
      temp = 1;
    else if (rgb[i] - *std::max_element(rgb.begin(), rgb.end()) > -30)
      temp = 2.5;
    else
      temp = 1.5;
    koef.push_back(temp);
  }

  for (int i = 0; i < img.size().width(); i++) {
    for (int j = 0; j < img.size().height(); j++) {
      double middle =
          (img.pixelColor(i, j).red() + img.pixelColor(i, j).green() +
           img.pixelColor(i, j).blue()) /
          3;
      for (int i = 0; i < 3; i++) {
        rgb[i] = middle * koef[i];
        rgb[i] = rgb[i] > 255 ? 255 : rgb[i];
      }
      buf_img.setPixelColor(i, j, QColor(rgb[0], rgb[1], rgb[2]));
    }
  }
}

void Model::Brightness(QImage &img, QImage &buf_img, int brightness) {
  for (int i = 0; i < img.size().width(); i++) {
    for (int j = 0; j < img.size().height(); j++) {
      int red = img.pixelColor(i, j).red() + brightness;
      int green = img.pixelColor(i, j).green() + brightness;
      int blue = img.pixelColor(i, j).blue() + brightness;

      QColor tmp;
      tmp.setRed(red > 255 ? 255 : red < 0 ? 0 : red);
      tmp.setGreen(green > 255 ? 255 : green < 0 ? 0 : green);
      tmp.setBlue(blue > 255 ? 255 : blue < 0 ? 0 : blue);
      tmp.setAlpha(img.pixelColor(i, j).alpha());

      buf_img.setPixelColor(i, j, tmp);
    }
  }
}

void Model::Contrast(QImage &img, QImage &buf_img, double contrast) {
  for (int i = 0; i < img.width(); i++) {
    for (int j = 0; j < img.height(); j++) {
      int red = img.pixelColor(i, j).red();
      int green = img.pixelColor(i, j).green();
      int blue = img.pixelColor(i, j).blue();

      double factor = (259 * (contrast + 255)) / (255 * (259 - contrast));
      double red1 = factor * (red - 128) + 128;
      red1 = red1 > 255 ? 255 : red1 < 0 ? 0 : red1;
      double green1 = factor * (green - 128) + 128;
      green1 = green1 > 255 ? 255 : green1 < 0 ? 0 : green1;
      double blue1 = factor * (blue - 128) + 128;
      blue1 = blue1 > 255 ? 255 : blue1 < 0 ? 0 : blue1;

      QColor tmp;
      tmp.setRed(red1);
      tmp.setGreen(green1);
      tmp.setBlue(blue1);
      tmp.setAlpha(img.pixelColor(i, j).alpha());

      buf_img.setPixelColor(i, j, tmp);
    }
  }
}

void Model::HSL(QImage &img, QImage &buf_img, double saturation_delta) {
  saturation_delta /= 255.0;
  for (int i = 0; i < img.width(); i++) {
    for (int j = 0; j < img.height(); j++) {
      double red = img.pixelColor(i, j).red() / 255.0;
      double green = img.pixelColor(i, j).green() / 255.0;
      double blue = img.pixelColor(i, j).blue() / 255.0;

      double cMax = MaxColor(red, green, blue);
      double cMin = MinColor(red, green, blue);
      double delta = (cMax - cMin);

      double hue = GetHue(red, green, blue, delta, cMax);
      double saturation = 0.0;
      double lightness = (cMax + cMin) / 2;
      if (delta != 0.0) {
        saturation = delta / (1 - abs(2 * lightness - 1));
      }

      saturation += saturation_delta;
      double c = (1 - abs(2 * lightness - 1)) * saturation;
      double x = c * (1 - abs(fmod(hue / 60.0, 2) - 1));
      double m = lightness - (c / 2.0);
      SetRGB(red, green, blue, hue, c, x, m);

      QColor tmp;
      tmp.setRed(red > 255 ? 255 : red < 0 ? 0 : red);
      tmp.setGreen(green > 255 ? 255 : green < 0 ? 0 : green);
      tmp.setBlue(blue > 255 ? 255 : blue < 0 ? 0 : blue);
      tmp.setAlpha(img.pixelColor(i, j).alpha());

      buf_img.setPixelColor(i, j, tmp);
    }
  }
}

void Model::HSV(QImage &img, QImage &buf_img, double saturation_delta) {
  saturation_delta /= 255.0;
  for (int i = 0; i < img.width(); i++) {
    for (int j = 0; j < img.height(); j++) {
      double red = img.pixelColor(i, j).red() / 255.0;
      double green = img.pixelColor(i, j).green() / 255.0;
      double blue = img.pixelColor(i, j).blue() / 255.0;

      double cMax = MaxColor(red, green, blue);
      double cMin = MinColor(red, green, blue);
      double delta = (cMax - cMin);

      double hue = GetHue(red, green, blue, delta, cMax);
      double saturation = 0.0;
      double value = cMax;
      if (cMax != 0.0) {
        saturation = delta / cMax;
      }

      saturation += saturation_delta;
      double c = value * saturation;
      double x = c * (1 - abs(fmod(hue / 60.0, 2.0) - 1.0));
      double m = value - c;
      SetRGB(red, green, blue, hue, c, x, m);

      QColor tmp;
      tmp.setRed(red > 255 ? 255 : red < 0 ? 0 : red);
      tmp.setGreen(green > 255 ? 255 : green < 0 ? 0 : green);
      tmp.setBlue(blue > 255 ? 255 : blue < 0 ? 0 : blue);
      tmp.setAlpha(img.pixelColor(i, j).alpha());

      buf_img.setPixelColor(i, j, tmp);
    }
  }
}

double Model::MinColor(double red, double green, double blue) {
  if (blue < red && blue < green)
    return blue;
  else if (green < red && green < blue)
    return green;
  else
    return red;
}

double Model::MaxColor(double red, double green, double blue) {
  if (blue > red && blue > green)
    return blue;
  else if (green > red && green > blue)
    return green;
  else
    return red;
}

double Model::GetHue(double red, double green, double blue, double delta,
                     double cMax) {
  double hue;
  if (delta == 0.0) {
    hue = 0.0;
  } else if (cMax == red) {
    hue = 60.0 * fmod(((green - blue) / delta), 6.0);
  } else if (cMax == green) {
    hue = 60.0 * (((blue - red) / delta) + 2.0);
  } else {
    hue = 60.0 * (((red - green) / delta) + 4.0);
  }
  return hue;
}

void Model::SetRGB(double &red, double &green, double &blue, double hue,
                   double c, double x, double m) {
  if (hue < 60.0) {
    red = c;
    green = x;
    blue = 0.0;
  } else if (hue < 120.0) {
    red = x;
    green = c;
    blue = 0.0;
  } else if (hue < 180.0) {
    red = 0.0;
    green = c;
    blue = x;
  } else if (hue < 240.0) {
    red = 0.0;
    green = x;
    blue = c;
  } else if (hue < 300.0) {
    red = x;
    green = 0.0;
    blue = c;
  } else if (hue < 360.0) {
    red = c;
    green = 0.0;
    blue = x;
  }
  red = (red + m) * 255.0;
  green = (green + m) * 255.0;
  blue = (blue + m) * 255.0;
}

}  // namespace s21
