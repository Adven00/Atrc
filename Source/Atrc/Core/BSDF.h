#pragma once

#include <Atrc/Core/Common.h>
#include <Atrc/Core/SurfacePoint.h>

AGZ_NS_BEG(Atrc)

enum BxDFType
{
    BXDF_NONE     = 0,

    BXDF_DIFFUSE  = 1 << 0,
    BXDF_GLOSSY   = 1 << 1,
    BXDF_SPECULAR = 1 << 2,

    BXDF_REFLECTION   = 1 << 3,
    BXDF_TRANSMISSION = 1 << 4,

    BXDF_ALL = BXDF_DIFFUSE | BXDF_GLOSSY | BXDF_SPECULAR |
               BXDF_REFLECTION | BXDF_TRANSMISSION
};

struct BSDFSampleWiResult
{
    Vec3 wi;
    Real pdf = 0.0;
    Spectrum coef;
    BxDFType type = BXDF_NONE;
};

class BSDF
{
protected:

    LocalCoordSystem shadingLocal_;
    LocalCoordSystem geometryLocal_;

public:

    BSDF(const LocalCoordSystem &shadingLocal, const LocalCoordSystem &geometryLocal)
        : shadingLocal_(shadingLocal), geometryLocal_(geometryLocal)
    {
        
    }

    virtual ~BSDF() = default;

    virtual Spectrum Eval(const Vec3 &wi, const Vec3 &wo) const = 0;

    // ����wo����wi����type���͵Ĳ���
    virtual Option<BSDFSampleWiResult> SampleWi(const Vec3 &wo, BxDFType type) const = 0;

    // ����ĳwi��������ʱSampleWi�Ĳ������������pdf
    virtual Real SampleWiPDF(const Vec3 &wi, const Vec3 &wo, BxDFType type) const = 0;
};

AGZ_NS_END(Atrc)
