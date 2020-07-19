namespace MATSE::MCT {

double transform(double min1, double max1, double min2, double max2,
                 double x1) {
  return (x1 - min1) / (max1 - min1) * (max2 - min2) + min2;
}

} // namespace MATSE::MCT