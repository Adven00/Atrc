#pragma once

#include <Atrc/Core/Core.h>

AGZ_NS_BEG(Atrc)

struct MDSampleResult
{
    Vec3 H;
    Real pdf;
};

// ΢����ֲ����������в����Լ�����ֵ�������ں�۱���ֲ�����ϵ��
class MicrofacetDistribution
{
public:

    virtual ~MicrofacetDistribution() = default;

    virtual float Eval(const Vec3 &H) const = 0;
};

AGZ_NS_END(Atrc)
