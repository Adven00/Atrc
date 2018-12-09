#pragma once

#include <Atrc/Material/BxDF/BxDF.h>

AGZ_NS_BEG(Atrc)

// ��֧��shading normal��geometry normal�ֱ���
class DiffuseBRDF : public BxDF
{
    Spectrum color_;

public:

    explicit DiffuseBRDF(const Spectrum &color);

    Spectrum Eval(const LocalCoordSystem &localShdCoord, const Vec3 &wi, const Vec3 &wo) const override;

    Option<BxDFSampleWiResult> SampleWi(const LocalCoordSystem &localShdCoord, const Vec3 &wo) const override;

    Real SampleWiPDF(const LocalCoordSystem &localShdCoord, const Vec3 &wi, const Vec3 &wo) const override;
};

AGZ_NS_END(Atrc)
