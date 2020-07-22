#include <cstdio>
#include <iostream>

#include "Data.hpp"
#include "Model.hpp"

using namespace MATSE::MCT;

const std::array points{TracePoint{5, 37, false},   TracePoint{5, 37, true},
                        TracePoint{124, 37, true},  TracePoint{124, 88, true},
                        TracePoint{5, 88, true},    TracePoint{5, 37, false},
                        TracePoint{11, 61, true},   TracePoint{18, 44, true},
                        TracePoint{24, 61, false},  TracePoint{13, 56, true},
                        TracePoint{22, 56, false},  TracePoint{29, 61, true},
                        TracePoint{29, 44, false},  TracePoint{42, 58, true},
                        TracePoint{40, 61, true},   TracePoint{36, 61, true},
                        TracePoint{33, 58, true},   TracePoint{33, 52, true},
                        TracePoint{36, 49, true},   TracePoint{40, 49, true},
                        TracePoint{42, 52, true},   TracePoint{42, 55, true},
                        TracePoint{33, 55, false},  TracePoint{46, 61, true},
                        TracePoint{54, 49, false},  TracePoint{46, 49, true},
                        TracePoint{54, 61, false},  TracePoint{59, 52, true},
                        TracePoint{61, 49, true},   TracePoint{65, 49, true},
                        TracePoint{67, 51, true},   TracePoint{67, 61, false},
                        TracePoint{67, 58, true},   TracePoint{63, 61, true},
                        TracePoint{60, 61, true},   TracePoint{58, 59, true},
                        TracePoint{58, 57, true},   TracePoint{61, 54, true},
                        TracePoint{67, 54, false},  TracePoint{72, 49, true},
                        TracePoint{72, 61, false},  TracePoint{72, 52, true},
                        TracePoint{75, 49, true},   TracePoint{78, 49, true},
                        TracePoint{80, 51, true},   TracePoint{80, 61, false},
                        TracePoint{94, 52, true},   TracePoint{90, 49, true},
                        TracePoint{87, 49, true},   TracePoint{84, 52, true},
                        TracePoint{84, 57, true},   TracePoint{87, 61, true},
                        TracePoint{90, 61, true},   TracePoint{94, 58, false},
                        TracePoint{94, 61, true},   TracePoint{94, 44, false},
                        TracePoint{107, 58, true},  TracePoint{105, 61, true},
                        TracePoint{101, 61, true},  TracePoint{98, 58, true},
                        TracePoint{98, 52, true},   TracePoint{101, 49, true},
                        TracePoint{105, 49, true},  TracePoint{107, 52, true},
                        TracePoint{107, 55, true},  TracePoint{98, 55, false},
                        TracePoint{112, 49, true},  TracePoint{112, 61, false},
                        TracePoint{112, 52, true},  TracePoint{116, 49, true},
                        TracePoint{118, 49, false}, TracePoint{34, 67, true},
                        TracePoint{45, 67, true},   TracePoint{33, 84, true},
                        TracePoint{45, 84, false},  TracePoint{49, 84, true},
                        TracePoint{49, 72, false},  TracePoint{49, 69, true},
                        TracePoint{48, 68, true},   TracePoint{49, 67, true},
                        TracePoint{50, 68, true},   TracePoint{49, 69, false},
                        TracePoint{54, 75, true},   TracePoint{58, 72, true},
                        TracePoint{61, 72, true},   TracePoint{64, 75, true},
                        TracePoint{64, 80, true},   TracePoint{61, 84, true},
                        TracePoint{58, 84, true},   TracePoint{54, 81, false},
                        TracePoint{54, 84, true},   TracePoint{54, 67, false},
                        TracePoint{76, 81, true},   TracePoint{74, 84, true},
                        TracePoint{70, 84, true},   TracePoint{67, 81, true},
                        TracePoint{67, 75, true},   TracePoint{70, 72, true},
                        TracePoint{74, 72, true},   TracePoint{76, 75, true},
                        TracePoint{76, 78, true},   TracePoint{67, 78, false},
                        TracePoint{81, 72, true},   TracePoint{81, 84, false},
                        TracePoint{81, 75, true},   TracePoint{85, 72, true},
                        TracePoint{87, 72, false},  TracePoint{93, 69, true},
                        TracePoint{93, 83, true},   TracePoint{94, 84, true},
                        TracePoint{96, 84, true},   TracePoint{97, 83, false},
                        TracePoint{90, 72, true},   TracePoint{96, 72, false}};

// const std::array points{
//     TracePoint{0, 0, false},  TracePoint{0, 0, true},
//     TracePoint{127, 0, true}, TracePoint{127, 127, true},
//     TracePoint{0, 127, true}, TracePoint{0, 0, true},
// };

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
  TracePoint lastPoint = points[0];
  for (const auto &point : points) {
    auto p_model = transformToModel({(double)point.x, (double)point.y});
    model.move(p_model.x, p_model.y);
    // printf("%.2f,%.2f,%d\n", p_model.x, p_model.y, model.isInDrawingArea());
    while (!model.hasReachedTarget()) {
      model.timeStep();
      auto x = model.getCurrentX();
      auto y = model.getCurrentY();
      auto p_lcd = transformToLCD({x, y});
      // if (!model.isInDrawingArea()) {
      //   printf("OUT OF AREA!\n");
      // }
      // printf("%.2f,%.2f,%d\n", x, y, lastPoint.pressed);
      if (lastPoint.pressed) {
        // printf("%d,%d,%d\n", p_lcd.x, p_lcd.y, lastPoint.pressed);
        printf("%.2f,%.2f\n", x, -y);
      }
      // printf("%d,%d %d,%d\n", model.getMotor1Step(), model.getMotor1Dir(),
      //        model.getMotor2Step(), model.getMotor2Dir());
    }
    lastPoint = point;
  }

  return 0;
}