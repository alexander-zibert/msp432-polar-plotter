#ifndef MATSE_MCT_IMAGES_HPP
#define MATSE_MCT_IMAGES_HPP

#include "Data.hpp"

using namespace MATSE::MCT;

void addAlexanderZibert() {
  PlotPoints plotPoints;
  const std::array points{
      TracePoint{5, 37, false},   TracePoint{5, 37, true},
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
  for (const auto &p : points) {
    plotPoints.addPoint(p);
  }
  GalleryData::addImage(plotPoints);
}

void addFrame() {
  PlotPoints plotPoints;
  const std::array points{
      TracePoint{0, 0, false},  TracePoint{0, 0, true},
      TracePoint{127, 0, true}, TracePoint{127, 127, true},
      TracePoint{0, 127, true}, TracePoint{0, 0, true},
  };
  for (const auto &p : points) {
    plotPoints.addPoint(p);
  }
  GalleryData::addImage(plotPoints);
}

void addAachen() {
  PlotPoints plotPoints;
  const std::array points{TracePoint{2, 64, false},  TracePoint{2, 64, true},
                          TracePoint{3, 64, true},   TracePoint{3, 53, true},
                          TracePoint{4, 50, true},   TracePoint{6, 53, true},
                          TracePoint{6, 57, true},   TracePoint{8, 57, true},
                          TracePoint{11, 58, true},  TracePoint{11, 40, true},
                          TracePoint{13, 38, true},  TracePoint{14, 40, true},
                          TracePoint{14, 35, true},  TracePoint{16, 30, true},
                          TracePoint{18, 36, true},  TracePoint{17, 37, true},
                          TracePoint{17, 43, true},  TracePoint{19, 41, true},
                          TracePoint{37, 41, true},  TracePoint{40, 44, true},
                          TracePoint{41, 42, true},  TracePoint{41, 36, true},
                          TracePoint{40, 36, true},  TracePoint{42, 30, true},
                          TracePoint{45, 37, true},  TracePoint{44, 37, true},
                          TracePoint{44, 42, true},  TracePoint{48, 48, true},
                          TracePoint{48, 52, true},  TracePoint{50, 57, true},
                          TracePoint{51, 54, true},  TracePoint{54, 54, true},
                          TracePoint{57, 56, true},  TracePoint{57, 57, true},
                          TracePoint{59, 57, true},  TracePoint{59, 56, true},
                          TracePoint{61, 56, true},  TracePoint{64, 60, true},
                          TracePoint{65, 57, true},  TracePoint{72, 57, true},
                          TracePoint{73, 59, true},  TracePoint{74, 57, true},
                          TracePoint{76, 55, true},  TracePoint{78, 54, true},
                          TracePoint{78, 50, true},  TracePoint{79, 49, true},
                          TracePoint{79, 46, true},  TracePoint{80, 40, true},
                          TracePoint{81, 46, true},  TracePoint{81, 49, true},
                          TracePoint{82, 50, true},  TracePoint{82, 54, true},
                          TracePoint{85, 55, true},  TracePoint{87, 57, true},
                          TracePoint{89, 57, true},  TracePoint{89, 51, true},
                          TracePoint{93, 51, true},  TracePoint{93, 45, true},
                          TracePoint{97, 41, true},  TracePoint{104, 41, true},
                          TracePoint{108, 46, true}, TracePoint{109, 46, true},
                          TracePoint{109, 44, true}, TracePoint{111, 41, true},
                          TracePoint{112, 41, true}, TracePoint{112, 39, true},
                          TracePoint{113, 37, true}, TracePoint{114, 39, true},
                          TracePoint{114, 41, true}, TracePoint{115, 41, true},
                          TracePoint{117, 44, true}, TracePoint{117, 47, true},
                          TracePoint{119, 47, true}, TracePoint{119, 40, true},
                          TracePoint{121, 29, true}, TracePoint{124, 40, true},
                          TracePoint{124, 60, true}, TracePoint{125, 60, true}};
  for (const auto &p : points) {
    plotPoints.addPoint(p);
  }
  GalleryData::addImage(plotPoints);
}

void addSmiley() {
  PlotPoints plotPoints;
  const std::array points{
      TracePoint{108, 64, 1}, TracePoint{108, 58, 1}, TracePoint{107, 53, 1},
      TracePoint{105, 47, 1}, TracePoint{102, 42, 1}, TracePoint{99, 38, 1},
      TracePoint{96, 33, 1},  TracePoint{92, 29, 1},  TracePoint{87, 26, 1},
      TracePoint{82, 23, 1},  TracePoint{77, 21, 1},  TracePoint{71, 20, 1},
      TracePoint{66, 19, 1},  TracePoint{60, 19, 1},  TracePoint{55, 20, 1},
      TracePoint{49, 21, 1},  TracePoint{44, 23, 1},  TracePoint{39, 26, 1},
      TracePoint{34, 29, 1},  TracePoint{30, 33, 1},  TracePoint{27, 38, 1},
      TracePoint{24, 42, 1},  TracePoint{21, 47, 1},  TracePoint{19, 53, 1},
      TracePoint{18, 58, 1},  TracePoint{18, 64, 1},  TracePoint{18, 70, 1},
      TracePoint{19, 75, 1},  TracePoint{21, 81, 1},  TracePoint{24, 86, 1},
      TracePoint{27, 90, 1},  TracePoint{30, 95, 1},  TracePoint{34, 99, 1},
      TracePoint{39, 102, 1}, TracePoint{44, 105, 1}, TracePoint{49, 107, 1},
      TracePoint{55, 108, 1}, TracePoint{60, 109, 1}, TracePoint{66, 109, 1},
      TracePoint{71, 108, 1}, TracePoint{77, 107, 1}, TracePoint{82, 105, 1},
      TracePoint{87, 102, 1}, TracePoint{92, 99, 1},  TracePoint{96, 95, 1},
      TracePoint{99, 90, 1},  TracePoint{102, 86, 1}, TracePoint{105, 81, 1},
      TracePoint{107, 75, 1}, TracePoint{108, 70, 1}, TracePoint{108, 64, 0},
      TracePoint{68, 64, 1},  TracePoint{68, 62, 1},  TracePoint{67, 61, 1},
      TracePoint{66, 60, 1},  TracePoint{65, 59, 1},  TracePoint{63, 59, 1},
      TracePoint{61, 59, 1},  TracePoint{60, 60, 1},  TracePoint{59, 61, 1},
      TracePoint{58, 62, 1},  TracePoint{58, 64, 1},  TracePoint{58, 66, 1},
      TracePoint{59, 67, 1},  TracePoint{60, 68, 1},  TracePoint{61, 69, 1},
      TracePoint{63, 69, 1},  TracePoint{65, 69, 1},  TracePoint{66, 68, 1},
      TracePoint{67, 67, 1},  TracePoint{68, 66, 1},  TracePoint{68, 64, 0},
      TracePoint{78, 64, 1},  TracePoint{77, 59, 1},  TracePoint{75, 55, 1},
      TracePoint{72, 52, 1},  TracePoint{68, 50, 1},  TracePoint{63, 49, 1},
      TracePoint{58, 50, 1},  TracePoint{54, 52, 1},  TracePoint{51, 55, 1},
      TracePoint{49, 59, 1},  TracePoint{48, 64, 1},  TracePoint{49, 69, 1},
      TracePoint{51, 73, 1},  TracePoint{54, 76, 1},  TracePoint{58, 78, 1},
      TracePoint{63, 79, 1},  TracePoint{68, 78, 1},  TracePoint{72, 76, 1},
      TracePoint{75, 73, 1},  TracePoint{77, 69, 1},  TracePoint{78, 64, 0},
      TracePoint{55, 37, 1},  TracePoint{55, 34, 1},  TracePoint{53, 31, 1},
      TracePoint{51, 29, 1},  TracePoint{48, 27, 1},  TracePoint{45, 27, 1},
      TracePoint{42, 27, 1},  TracePoint{39, 29, 1},  TracePoint{37, 31, 1},
      TracePoint{35, 34, 1},  TracePoint{35, 37, 1},  TracePoint{35, 40, 1},
      TracePoint{37, 43, 1},  TracePoint{39, 45, 1},  TracePoint{42, 47, 1},
      TracePoint{45, 47, 1},  TracePoint{48, 47, 1},  TracePoint{51, 45, 1},
      TracePoint{53, 43, 1},  TracePoint{55, 40, 1},  TracePoint{55, 37, 0},
      TracePoint{91, 37, 1},  TracePoint{91, 34, 1},  TracePoint{89, 31, 1},
      TracePoint{87, 29, 1},  TracePoint{84, 27, 1},  TracePoint{81, 27, 1},
      TracePoint{78, 27, 1},  TracePoint{75, 29, 1},  TracePoint{73, 31, 1},
      TracePoint{71, 34, 1},  TracePoint{71, 37, 1},  TracePoint{71, 40, 1},
      TracePoint{73, 43, 1},  TracePoint{75, 45, 1},  TracePoint{78, 47, 1},
      TracePoint{81, 47, 1},  TracePoint{84, 47, 1},  TracePoint{87, 45, 1},
      TracePoint{89, 43, 1},  TracePoint{91, 40, 1},  TracePoint{91, 37, 0},
      TracePoint{50, 37, 1},  TracePoint{50, 35, 1},  TracePoint{49, 34, 1},
      TracePoint{48, 33, 1},  TracePoint{47, 32, 1},  TracePoint{45, 32, 1},
      TracePoint{43, 32, 1},  TracePoint{42, 33, 1},  TracePoint{41, 34, 1},
      TracePoint{40, 35, 1},  TracePoint{40, 37, 1},  TracePoint{40, 39, 1},
      TracePoint{41, 40, 1},  TracePoint{42, 41, 1},  TracePoint{43, 42, 1},
      TracePoint{45, 42, 1},  TracePoint{47, 42, 1},  TracePoint{48, 41, 1},
      TracePoint{49, 40, 1},  TracePoint{50, 39, 1},  TracePoint{50, 37, 0},
      TracePoint{86, 37, 1},  TracePoint{86, 35, 1},  TracePoint{85, 34, 1},
      TracePoint{84, 33, 1},  TracePoint{83, 32, 1},  TracePoint{81, 32, 1},
      TracePoint{79, 32, 1},  TracePoint{78, 33, 1},  TracePoint{77, 34, 1},
      TracePoint{76, 35, 1},  TracePoint{76, 37, 1},  TracePoint{76, 39, 1},
      TracePoint{77, 40, 1},  TracePoint{78, 41, 1},  TracePoint{79, 42, 1},
      TracePoint{81, 42, 1},  TracePoint{83, 42, 1},  TracePoint{84, 41, 1},
      TracePoint{85, 40, 1},  TracePoint{86, 39, 1},  TracePoint{86, 37, 0},
      TracePoint{89, 78, 1},  TracePoint{87, 82, 1},  TracePoint{85, 85, 1},
      TracePoint{82, 87, 1},  TracePoint{79, 89, 1},  TracePoint{76, 91, 1},
      TracePoint{72, 93, 1},  TracePoint{69, 93, 1},  TracePoint{65, 94, 1},
      TracePoint{61, 94, 1},  TracePoint{57, 93, 1},  TracePoint{54, 93, 1},
      TracePoint{50, 91, 1},  TracePoint{47, 89, 1},  TracePoint{44, 87, 1},
      TracePoint{41, 85, 0},
  };
  for (const auto &p : points) {
    plotPoints.addPoint(p);
  }
  GalleryData::addImage(plotPoints);
}

void addPolarPlotter() {
  PlotPoints plotPoints;
  const std::array points{
      TracePoint{52, 42, 1},  TracePoint{93, 42, 1},  TracePoint{99, 43, 1},
      TracePoint{104, 46, 1}, TracePoint{109, 51, 1}, TracePoint{111, 55, 1},
      TracePoint{111, 67, 1}, TracePoint{108, 72, 1}, TracePoint{101, 79, 1},
      TracePoint{98, 80, 1},  TracePoint{90, 82, 1},  TracePoint{74, 82, 1},
      TracePoint{72, 84, 1},  TracePoint{72, 100, 1}, TracePoint{75, 103, 1},
      TracePoint{83, 103, 1}, TracePoint{84, 104, 1}, TracePoint{84, 110, 1},
      TracePoint{83, 111, 1}, TracePoint{52, 111, 1}, TracePoint{51, 110, 1},
      TracePoint{51, 104, 1}, TracePoint{52, 103, 1}, TracePoint{60, 103, 1},
      TracePoint{63, 100, 1}, TracePoint{63, 52, 1},  TracePoint{61, 50, 1},
      TracePoint{52, 50, 1},  TracePoint{50, 48, 1},  TracePoint{50, 44, 1},
      TracePoint{52, 42, 0},  TracePoint{75, 50, 1},  TracePoint{93, 50, 1},
      TracePoint{98, 53, 1},  TracePoint{100, 55, 1}, TracePoint{101, 58, 1},
      TracePoint{101, 66, 1}, TracePoint{99, 69, 1},  TracePoint{96, 72, 1},
      TracePoint{91, 73, 1},  TracePoint{83, 74, 1},  TracePoint{75, 74, 1},
      TracePoint{73, 72, 1},  TracePoint{73, 52, 1},  TracePoint{75, 50, 0},
      TracePoint{15, 19, 1},  TracePoint{56, 19, 1},  TracePoint{62, 20, 1},
      TracePoint{67, 23, 1},  TracePoint{72, 28, 1},  TracePoint{74, 32, 1},
      TracePoint{74, 42, 0},  TracePoint{63, 56, 1},  TracePoint{61, 57, 1},
      TracePoint{53, 59, 1},  TracePoint{37, 59, 1},  TracePoint{35, 61, 1},
      TracePoint{35, 77, 1},  TracePoint{38, 80, 1},  TracePoint{46, 80, 1},
      TracePoint{47, 81, 1},  TracePoint{47, 87, 1},  TracePoint{46, 88, 1},
      TracePoint{15, 88, 1},  TracePoint{14, 87, 1},  TracePoint{14, 81, 1},
      TracePoint{15, 80, 1},  TracePoint{23, 80, 1},  TracePoint{26, 77, 1},
      TracePoint{26, 29, 1},  TracePoint{24, 27, 1},  TracePoint{15, 27, 1},
      TracePoint{13, 25, 1},  TracePoint{13, 21, 1},  TracePoint{15, 19, 0},
      TracePoint{38, 27, 1},  TracePoint{56, 27, 1},  TracePoint{61, 30, 1},
      TracePoint{63, 32, 1},  TracePoint{64, 35, 1},  TracePoint{64, 42, 0},
      TracePoint{51, 50, 1},  TracePoint{46, 51, 1},  TracePoint{38, 51, 1},
      TracePoint{36, 49, 1},  TracePoint{36, 29, 1},  TracePoint{38, 27, 0},
  };
  for (const auto &p : points) {
    plotPoints.addPoint(p);
  }
  GalleryData::addImage(plotPoints);
}

#endif