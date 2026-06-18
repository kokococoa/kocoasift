#include "parameters.hpp"

namespace kocoasift {

KocoaSIFTParameters::KocoaSIFTParameters() = default;

KocoaSIFTParameters::KocoaSIFTParameters(
    int image_width, int image_height, int nFeatures, int nOctaves, int nLayers, float sigma)
    : image_width_(image_width),
      image_height_(image_height),
      nFeatures_(nFeatures),
      nOctaves_(nOctaves),
      nLayers_(nLayers),
      sigma_(sigma) {}

KocoaSIFTParameters::~KocoaSIFTParameters() = default;

int KocoaSIFTParameters::imageWidth() const { return image_width_; }

int KocoaSIFTParameters::imageHeight() const { return image_height_; }

int KocoaSIFTParameters::nFeatures() const { return nFeatures_; }

int KocoaSIFTParameters::nOctaves() const { return nOctaves_; }

int KocoaSIFTParameters::nLayers() const { return nLayers_; }

float KocoaSIFTParameters::sigma() const { return sigma_; }

}  // namespace kocoasift
