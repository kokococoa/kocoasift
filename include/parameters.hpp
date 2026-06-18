#pragma once

#include "common.hpp"

namespace kocoasift {

class KocoaSIFTParameters {
 public:
  KocoaSIFTParameters();
  KocoaSIFTParameters(int image_width, int image_height, int nFeatures, int nOctaves, int nLayers, float sigma);
  ~KocoaSIFTParameters();

  int nFeatures() const;
  int nOctaves() const;
  int nLayers() const;
  float sigma() const;
  int imageWidth() const;
  int imageHeight() const;

 private:
  int nFeatures_;
  int nOctaves_;
  int nLayers_;
  float sigma_;
  int image_width_;
  int image_height_;
};

}  // namespace kocoasift
