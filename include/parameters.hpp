#pragma once

#include "common.hpp"

namespace kocoasift {

class KocoaSIFTParameters {
 public:
  KocoaSIFTParameters();
  KocoaSIFTParameters(int nFeatures, int nOctaves, int nLayers, float sigma);
  ~KocoaSIFTParameters();

  int nFeatures() const;
  int nOctaves() const;
  int nLayers() const;
  float sigma() const;

 private:
  int nFeatures_;
  int nOctaves_;
  int nLayers_;
  float sigma_;
};

}  // namespace kocoasift
