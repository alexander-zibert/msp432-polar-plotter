#include <cstdio>
#include <iostream>

#include "Data.hpp"
#include "Model.hpp"

using namespace MATSE::MCT;

double transform(double min1, double max1, double min2, double max2,
                 double x1) {
  return (x1 - min1) / (max1 - min1) * (max2 - min2) + min2;
}

struct Point2D {
  double x;
  double y;
};

constexpr double margin = Model::margin;
constexpr double x_max = Model::x_max;
constexpr double y_max = Model::y_max;

Point2D transformToModel(Point2D p) {
  return {transform(0, 127, margin + 1, x_max - margin - 1, p.x),
          transform(0, 127, margin + 1, y_max - margin - 1, p.y)};
}

Point transformToLCD(Point2D p) {
  return {(uint8_t)transform(margin + 1, x_max - margin - 1, 0, 127, p.x),
          (uint8_t)transform(margin + 1, y_max - margin - 1, 0, 127, p.y)};
}

int main() {
  Model model{};
  int numSteps = 2000;
  for (int step1 = -numSteps; step1 < numSteps; step1 += 1) {
    for (int step2 = -numSteps; step2 < numSteps; step2 += 1) {
      model.currentStep1 = step1;
      model.currentStep2 = step2;
      if (model.isInDrawingArea()) {
        printf("%.6f,%.6f,1\n", model.getCurrentX(), model.getCurrentY());
      }
    }
  }
  //   for (int x = 120; x < 378; x += 1) {
  //     for (int y = 130; y < 347; y += 1) {
  //       const auto p_model = transformToModel({(double)x, (double)y});
  //       model.move(p_model.x, p_model.y);
  //       while (!model.hasReachedTarget()) {
  //         model.timeStep();
  //         auto cur_x = model.getCurrentX();
  //         auto cur_y = model.getCurrentY();
  //         printf("%.2f,%.2f,1\n", cur_x, cur_y);
  //       }
  //     }
  //   }

  return 0;
}