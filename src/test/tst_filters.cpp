#include "test.h"

TEST_F(PhotoLab, emboss) {
    QImage image_result = QImage("../../datasets/emboss.bmp");
    s21::Matrix<int> filter = EMBOSS;

    model_->Convolution(image_base, image_standart, filter);
    for(int i = 0; i < image_standart.size().height(); i++) {
        for(int j = 0; j < image_standart.size().width(); j++) {
            EXPECT_EQ(image_standart.pixelColor(i, j).red(), image_result.pixelColor(i, j).red());
            EXPECT_EQ(image_standart.pixelColor(i, j).green(), image_result.pixelColor(i, j).green());
            EXPECT_EQ(image_standart.pixelColor(i, j).blue(), image_result.pixelColor(i, j).blue());
        }
    }
}

TEST_F(PhotoLab, sharpen) {
    QImage image_result = QImage("../../datasets/sharpen.bmp");
    s21::Matrix<int> filter = SHARPEN;

    model_->Convolution(image_base, image_standart, filter);
    for(int i = 0; i < image_standart.size().height(); i++) {
        for(int j = 0; j < image_standart.size().width(); j++) {
            EXPECT_EQ(image_standart.pixelColor(i, j).red(), image_result.pixelColor(i, j).red());
            EXPECT_EQ(image_standart.pixelColor(i, j).green(), image_result.pixelColor(i, j).green());
            EXPECT_EQ(image_standart.pixelColor(i, j).blue(), image_result.pixelColor(i, j).blue());
        }
    }
}

TEST_F(PhotoLab, boxblur) {
    QImage image_result = QImage("../../datasets/boxbluer.bmp");
    s21::Matrix<int> filter = BOXBLUR;

    model_->Convolution(image_base, image_standart, filter);
    for(int i = 0; i < image_standart.size().height(); i++) {
        for(int j = 0; j < image_standart.size().width(); j++) {
            EXPECT_EQ(image_standart.pixelColor(i, j).red(), image_result.pixelColor(i, j).red());
            EXPECT_EQ(image_standart.pixelColor(i, j).green(), image_result.pixelColor(i, j).green());
            EXPECT_EQ(image_standart.pixelColor(i, j).blue(), image_result.pixelColor(i, j).blue());
        }
    }
}

TEST_F(PhotoLab, gaussian) {
    QImage image_result = QImage("../../datasets/gaussian.bmp");
    s21::Matrix<int> filter = GAUSSIANBLUR;

    model_->Convolution(image_base, image_standart, filter);
    for(int i = 0; i < image_standart.size().height(); i++) {
        for(int j = 0; j < image_standart.size().width(); j++) {
            EXPECT_EQ(image_standart.pixelColor(i, j).red(), image_result.pixelColor(i, j).red());
            EXPECT_EQ(image_standart.pixelColor(i, j).green(), image_result.pixelColor(i, j).green());
            EXPECT_EQ(image_standart.pixelColor(i, j).blue(), image_result.pixelColor(i, j).blue());
        }
    }
}

TEST_F(PhotoLab, laplacia) {
    QImage image_result = QImage("../../datasets/laplassa.bmp");
    s21::Matrix<int> filter = LAPLACIANFILTER;

    model_->Convolution(image_base, image_standart, filter);
    for(int i = 0; i < image_standart.size().height(); i++) {
        for(int j = 0; j < image_standart.size().width(); j++) {
            EXPECT_EQ(image_standart.pixelColor(i, j).red(), image_result.pixelColor(i, j).red());
            EXPECT_EQ(image_standart.pixelColor(i, j).green(), image_result.pixelColor(i, j).green());
            EXPECT_EQ(image_standart.pixelColor(i, j).blue(), image_result.pixelColor(i, j).blue());
        }
    }
}

TEST_F(PhotoLab, sobel) {
    QImage image_result = QImage("../../datasets/sobel.bmp");
    s21::Matrix<int> filter = SOBELFILTER;

    model_->Convolution(image_base, image_standart, filter);
    for(int i = 0; i < image_standart.size().height(); i++) {
        for(int j = 0; j < image_standart.size().width(); j++) {
            EXPECT_EQ(image_standart.pixelColor(i, j).red(), image_result.pixelColor(i, j).red());
            EXPECT_EQ(image_standart.pixelColor(i, j).green(), image_result.pixelColor(i, j).green());
            EXPECT_EQ(image_standart.pixelColor(i, j).blue(), image_result.pixelColor(i, j).blue());
        }
    }
}

TEST_F(PhotoLab, custom) {
    QImage image_result = QImage("../../datasets/custom.bmp");
    s21::Matrix<int> filter = CUSTOM;

    model_->Convolution(image_base, image_standart, filter);
    for(int i = 0; i < image_standart.size().height(); i++) {
        for(int j = 0; j < image_standart.size().width(); j++) {
            EXPECT_EQ(image_standart.pixelColor(i, j).red(), image_result.pixelColor(i, j).red());
            EXPECT_EQ(image_standart.pixelColor(i, j).green(), image_result.pixelColor(i, j).green());
            EXPECT_EQ(image_standart.pixelColor(i, j).blue(), image_result.pixelColor(i, j).blue());
        }
    }
}

TEST_F(PhotoLab, discoloration) {
    QImage image_result = QImage("../../datasets/discoloration.bmp");

    model_->Discoloration(image_base, image_standart);
    for(int i = 0; i < image_standart.size().height(); i++) {
        for(int j = 0; j < image_standart.size().width(); j++) {
            EXPECT_EQ(image_standart.pixelColor(i, j).red(), image_result.pixelColor(i, j).red());
            EXPECT_EQ(image_standart.pixelColor(i, j).green(), image_result.pixelColor(i, j).green());
            EXPECT_EQ(image_standart.pixelColor(i, j).blue(), image_result.pixelColor(i, j).blue());
        }
    }
}

TEST_F(PhotoLab, negative) {
    QImage image_result = QImage("../../datasets/negative.bmp");

    model_->Negative(image_base, image_standart);
    for(int i = 0; i < image_standart.size().height(); i++) {
        for(int j = 0; j < image_standart.size().width(); j++) {
            EXPECT_EQ(image_standart.pixelColor(i, j).red(), image_result.pixelColor(i, j).red());
            EXPECT_EQ(image_standart.pixelColor(i, j).green(), image_result.pixelColor(i, j).green());
            EXPECT_EQ(image_standart.pixelColor(i, j).blue(), image_result.pixelColor(i, j).blue());
        }
    }
}

TEST_F(PhotoLab, toning) {
    QImage image_result = QImage("../../datasets/red-toning.bmp");

    model_->Toning(QColor(Qt::red), image_base, image_standart);
    for(int i = 0; i < image_standart.size().height(); i++) {
        for(int j = 0; j < image_standart.size().width(); j++) {
            EXPECT_EQ(image_standart.pixelColor(i, j).red(), image_result.pixelColor(i, j).red());
            EXPECT_EQ(image_standart.pixelColor(i, j).green(), image_result.pixelColor(i, j).green());
            EXPECT_EQ(image_standart.pixelColor(i, j).blue(), image_result.pixelColor(i, j).blue());
        }
    }
}

TEST_F(PhotoLab, brightness) {
    QImage image_result = QImage("../../datasets/brightness-max.bmp");

    model_->Brightness(image_base, image_standart, 255);
    for(int i = 0; i < image_standart.size().height(); i++) {
        for(int j = 0; j < image_standart.size().width(); j++) {
            EXPECT_EQ(image_standart.pixelColor(i, j).red(), image_result.pixelColor(i, j).red());
            EXPECT_EQ(image_standart.pixelColor(i, j).green(), image_result.pixelColor(i, j).green());
            EXPECT_EQ(image_standart.pixelColor(i, j).blue(), image_result.pixelColor(i, j).blue());
        }
    }
}

TEST_F(PhotoLab, contrast) {
    QImage image_result = QImage("../../datasets/contrast-max.bmp");

    model_->Contrast(image_base, image_standart, 255);
    for(int i = 0; i < image_standart.size().height(); i++) {
        for(int j = 0; j < image_standart.size().width(); j++) {
            EXPECT_EQ(image_standart.pixelColor(i, j).red(), image_result.pixelColor(i, j).red());
            EXPECT_EQ(image_standart.pixelColor(i, j).green(), image_result.pixelColor(i, j).green());
            EXPECT_EQ(image_standart.pixelColor(i, j).blue(), image_result.pixelColor(i, j).blue());
        }
    }
}

TEST_F(PhotoLab, saturationHSL) {
    QImage image_result = QImage("../../datasets/saturation-max.bmp");

    model_->HSL(image_base, image_standart, 255);
    for(int i = 0; i < image_standart.size().height(); i++) {
        for(int j = 0; j < image_standart.size().width(); j++) {
            EXPECT_EQ(image_standart.pixelColor(i, j).red(), image_result.pixelColor(i, j).red());
            EXPECT_EQ(image_standart.pixelColor(i, j).green(), image_result.pixelColor(i, j).green());
            EXPECT_EQ(image_standart.pixelColor(i, j).blue(), image_result.pixelColor(i, j).blue());
        }
    }
}

TEST_F(PhotoLab, saturationHSV) {
    QImage image_result = QImage("../../datasets/hsv-min.bmp");

    model_->HSV(image_base, image_standart, -255);
    for(int i = 0; i < image_standart.size().height(); i++) {
        for(int j = 0; j < image_standart.size().width(); j++) {
            EXPECT_EQ(image_standart.pixelColor(i, j).red(), image_result.pixelColor(i, j).red());
            EXPECT_EQ(image_standart.pixelColor(i, j).green(), image_result.pixelColor(i, j).green());
            EXPECT_EQ(image_standart.pixelColor(i, j).blue(), image_result.pixelColor(i, j).blue());
        }
    }
}
