#include "frontend.hpp"

namespace kocoasift {

KocoaSIFT::KocoaSIFT()
    : parameters_(
          0, 0, kDefaultNFeatures, kDefaultNOctaves, kDefaultNLayers, kDefaultSigma) {}

KocoaSIFT::~KocoaSIFT() = default;

void KocoaSIFT::configure(
        int image_width, int image_height,
        int nFeatures, int nOctaves, int nLayers, float sigma) {
  parameters_ = KocoaSIFTParameters(image_width, image_height, nFeatures, nOctaves, nLayers, sigma);
}

void KocoaSIFT::initialize()
{
    detect_ = std::make_unique<KocoaSIFTDetector>(&parameters_);
}

void KocoaSIFT::process(cv::Mat& image) {
    if (!detect_) {
        throw std::runtime_error("KocoaSIFTDetector is not initialized. Call initialize() first.");
    }
    detect_->process(image);
  // PLACEHOLDER: SIFT frontend execution is not implemented yet.
}

}  // namespace kocoasift
