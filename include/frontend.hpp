#pragma once
#include "common.hpp"

#include "detect.hpp"
#include "parameters.hpp"

namespace kocoasift {

/// Default parameters for KocoaSIFT
inline constexpr int kDefaultNFeatures = 600;
inline constexpr int kDefaultNOctaves = 4;
inline constexpr int kDefaultNLayers = 3;
inline constexpr float kDefaultSigma = 1.6f;

class KocoaSIFT {
 public:
  KocoaSIFT();
  ~KocoaSIFT();

  void configure(
        int image_width, int image_height,
        int nFeatures = kDefaultNFeatures,
        int nOctaves = kDefaultNOctaves,
        int nLayers = kDefaultNLayers,
        float sigma = kDefaultSigma);

  void initialize();
  void process(cv::Mat& image);
  KocoaSIFTParameters& parameters() { return parameters_; }
  KocoaSIFTDetector& detector() { return *detect_; }

 private:
  KocoaSIFTParameters parameters_;
  std::unique_ptr<KocoaSIFTDetector> detect_;
};

}  // namespace kocoasift
