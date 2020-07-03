#ifndef MATSE_MCT_DRAW_INTERFACE_HPP
#define MATSE_MCT_DRAW_INTERFACE_HPP

namespace MATSE::MCT {
class DrawInterface {
public:
  virtual void print(const char *) = 0;
};
} // namespace MATSE::MCT

#endif