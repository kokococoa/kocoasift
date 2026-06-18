#include "parameters.hpp"

namespace kocoasift {

KocoaSIFTParameters::KocoaSIFTParameters() = default;

KocoaSIFTParameters::KocoaSIFTParameters(
    int nFeatures, int nOctaves, int nLayers, float sigma)
    : nFeatures_(nFeatures),
      nOctaves_(nOctaves),
      nLayers_(nLayers),
      sigma_(sigma) {}

KocoaSIFTParameters::~KocoaSIFTParameters() = default;

int KocoaSIFTParameters::nFeatures() const { return nFeatures_; }

int KocoaSIFTParameters::nOctaves() const { return nOctaves_; }

int KocoaSIFTParameters::nLayers() const { return nLayers_; }

float KocoaSIFTParameters::sigma() const { return sigma_; }

}  // namespace kocoasift
