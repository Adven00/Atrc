#include <Atrc/Material/BxDFAggregate.h>

AGZ_NS_BEG(Atrc)

BxDFAggregate::BxDFAggregate(const LocalCoordSystem &shdLocal, const LocalCoordSystem &geoLocal)
    : BSDF(shdLocal, geoLocal), bxdfCnt_(0)
{

}

void BxDFAggregate::AddBxDF(BxDF *bxdf)
{
    AGZ_ASSERT(bxdfCnt_ < MAX_BXDF_CNT);
    bxdfs_[bxdfCnt_++] = bxdf;
}

Spectrum BxDFAggregate::Eval(const Vec3 &wi, const Vec3 &wo, BxDFType type) const
{
    Vec3 lwi = shadingLocal_.World2Local(wi), lwo = shadingLocal_.World2Local(wo);

    Spectrum ret;
    for(size_t i = 0; i < bxdfCnt_; ++i)
    {
        if(bxdfs_[i]->MatchType(type))
            ret += bxdfs_[i]->Eval(lwi, lwo);
    }

    return ret;
}

Option<BSDFSampleWiResult> BxDFAggregate::SampleWi(const Vec3 &wo, BxDFType type) const
{
    // �ж���type�Ե��ϵ�bxdf

    size_t nMatched = 0;
    for(size_t i = 0; i < bxdfCnt_; ++i)
        nMatched += bxdfs_[i]->MatchType(type);
    if(!nMatched)
        return None;

    // ������ѡ��һ������������

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

    // ������bxdf

    Vec3 lwo = shadingLocal_.World2Local(wo);
    auto ret = bxdf->SampleWi(lwo);
    if(!ret)
        return None;

    // ������Ǹ�specular����ôcoef��pdf��������delta����ʱ�ѱ��bxdf�����û������
    if(ret->type & BXDF_SPECULAR || nMatched <= 1)
    {
        ret->pdf /= nMatched;
        ret->wi = shadingLocal_.Local2World(ret->wi);
        return ret;
    }

    // �ۺϿ����������ͶԵ��ϵ�bxdf�����
    for(size_t i = 0; i < bxdfCnt_; ++i)
    {
        if(bxdfs_[i]->MatchType(type) && bxdfs_[i] != bxdf)
        {
            ret->pdf += bxdfs_[i]->SampleWiPDF(ret->wi, lwo);
            ret->coef += bxdfs_[i]->Eval(ret->wi, lwo);
        }
    }

    ret->pdf /= nMatched;
    ret->wi = shadingLocal_.Local2World(ret->wi);
    return ret;
}

Real BxDFAggregate::SampleWiPDF(const Vec3 &wi, const Vec3 &wo, BxDFType type) const
{
    Vec3 lwi = shadingLocal_.World2Local(wi), lwo = shadingLocal_.World2Local(wo);

    int nMatched = 0; Real ret = 0.0;
    for(size_t i = 0; i < bxdfCnt_; ++i)
    {
        if(bxdfs_[i]->MatchType(type))
        {
            ++nMatched;
            ret += bxdfs_[i]->SampleWiPDF(lwi, lwo);
        }
    }

    return nMatched ? ret / nMatched : 0.0;
}

AGZ_NS_END(Atrc)
