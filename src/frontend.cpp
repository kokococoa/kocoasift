#include "frontend.hpp"

namespace kocoasift {

KocoaSIFT::KocoaSIFT()
    : parameters_(
          kDefaultNFeatures, kDefaultNOctaves, kDefaultNLayers, kDefaultSigma) {}

KocoaSIFT::~KocoaSIFT() = default;

void KocoaSIFT::configure(
    int nFeatures, int nOctaves, int nLayers, float sigma) {
  parameters_ = KocoaSIFTParameters(nFeatures, nOctaves, nLayers, sigma);
}

void KocoaSIFT::initialize()
{
    detect_ = std::make_unique<KocoaSIFTDetector>(&parameters_);
}

void KocoaSIFT::run() {
  // PLACEHOLDER: SIFT frontend execution is not implemented yet.
}

}  // namespace kocoasift
