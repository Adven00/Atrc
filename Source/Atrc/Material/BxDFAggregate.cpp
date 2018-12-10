﻿#include <Atrc/Material/BxDFAggregate.h>

AGZ_NS_BEG(Atrc)

BxDFAggregate::BxDFAggregate(const Vec3 &shdNor, const LocalCoordSystem &geoLocal)
    : BSDF(shdNor, geoLocal), bxdfCnt_(0)
{

}

void BxDFAggregate::AddBxDF(const BxDF *bxdf)
{
    AGZ_ASSERT(bxdfCnt_ < MAX_BXDF_CNT);
    bxdfs_[bxdfCnt_++] = bxdf;
}

Spectrum BxDFAggregate::Eval(const Vec3 &wi, const Vec3 &wo, BxDFType type) const
{
    Vec3 lwi = geometryLocal_.World2Local(wi), lwo = geometryLocal_.World2Local(wo);

    Spectrum ret;
    for(size_t i = 0; i < bxdfCnt_; ++i)
    {
        if(bxdfs_[i]->MatchType(type))
            ret += bxdfs_[i]->Eval(shadingLocal_, lwi, lwo);
    }

    return ret;
}

Option<BSDFSampleWiResult> BxDFAggregate::SampleWi(const Vec3 &wo, BxDFType type) const
{
    // 有多少type对得上的bxdf

    size_t nMatched = 0;
    for(size_t i = 0; i < bxdfCnt_; ++i)
        nMatched += bxdfs_[i]->MatchType(type);
    if(!nMatched)
        return None;

    // 从里面选出一个，用来采样

    const BxDF *bxdf = nullptr;
    auto dstIdx = AGZ::Math::Random::Uniform<size_t>(0, nMatched - 1);
    for(size_t i = 0, j = 0; i < bxdfCnt_; ++i)
    {
        if(bxdfs_[i]->MatchType(type) && j++ == dstIdx)
        {
            bxdf = bxdfs_[i];
            break;
        }
    }

    // 采样该bxdf

    Vec3 lwo = geometryLocal_.World2Local(wo).Normalize();
    auto ret = bxdf->SampleWi(shadingLocal_, lwo);
    if(!ret)
        return None;

    // 如果这是个specular，那么coef和pdf都附带了delta，此时把别的bxdf算进来没有意义
    if(ret->type & BXDF_SPECULAR || nMatched <= 1)
    {
        ret->pdf /= nMatched;
        ret->wi = geometryLocal_.Local2World(ret->wi).Normalize();
        AGZ_ASSERT(IsNormalized(ret->wi));
        return ret;
    }

    // 综合考虑所有类型对得上的bxdf的意见
    for(size_t i = 0; i < bxdfCnt_; ++i)
    {
        if(bxdfs_[i]->MatchType(type) && bxdfs_[i] != bxdf)
        {
            ret->pdf += bxdfs_[i]->SampleWiPDF(shadingLocal_, ret->wi, lwo);
            ret->coef += bxdfs_[i]->Eval(shadingLocal_, ret->wi, lwo);
        }
    }

    ret->pdf /= nMatched;
    ret->wi = geometryLocal_.Local2World(ret->wi).Normalize();
    AGZ_ASSERT(IsNormalized(ret->wi));
    return ret;
}

Real BxDFAggregate::SampleWiPDF(const Vec3 &wi, const Vec3 &wo, BxDFType type) const
{
    Vec3 lwi = geometryLocal_.World2Local(wi).Normalize(), lwo = geometryLocal_.World2Local(wo).Normalize();

    int nMatched = 0; Real ret = 0.0;
    for(size_t i = 0; i < bxdfCnt_; ++i)
    {
        if(bxdfs_[i]->MatchType(type))
        {
            ++nMatched;
            ret += bxdfs_[i]->SampleWiPDF(shadingLocal_, lwi, lwo);
        }
    }

    return nMatched ? ret / nMatched : Real(0);
}

AGZ_NS_END(Atrc)
