#include <Atrc/Material/Normal.h>

AGZ_NS_BEG(Atrc)

BxDFType NormalBRDF::GetType() const
{
    return BXDF_NONE;
}

Spectrum NormalBRDF::Eval(const Vec3r &wi, const Vec3r &wo) const
{
    return SPECTRUM::BLACK;
}

Option<BxDFSample> NormalBRDF::Sample(const Vec3r &wi, BxDFType type) const
{
    return None;
}

Spectrum NormalBRDF::AmbientRadiance(const Intersection &inct) const
{
    return 0.5f * (inct.nor.Map([](Real r) {return static_cast<float>(r); }) + Spectrum(1.0f));
}

RC<BxDF> NormalMaterial::GetBxDF(const Intersection &inct, const Vec2r &matParam) const
{
    return NewRC<NormalBRDF>();
}

AGZ_NS_END(Atrc)