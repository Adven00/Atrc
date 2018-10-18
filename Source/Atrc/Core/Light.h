#pragma once

#include <Atrc/Core/Common.h>

AGZ_NS_BEG(Atrc)

struct LightSampleToResult
{
    Vec3 pos;
    Vec3 nor;
    Spectrum le;
    Real pdf = 0.0;
};

class Light
{
public:

    virtual ~Light() = default;

    // �ڹ�Դ�ϲ���һ��������sp
    virtual LightSampleToResult SampleTo(const SurfacePoint &sp) const = 0;

    // ������Դ�ϵĲ����������pdf
    virtual Real SampleToPDF(const SurfacePoint &sp, const Vec3 &pos) const = 0;

    // λ�ò����Ƿ�ʹ��delta�ֲ�
    virtual bool IsDeltaPosition() const = 0;

    // �Ƿ���delta����Ĺ�Դ���������������
    virtual bool IsDeltaDirection() const = 0;

    // �������ʵ��Ĺ�Դ����ĳr��ʵ�彻��sp������һ����-r.dir��radiance
    virtual Spectrum AreaLe(const SurfacePoint &sp, const Vec3 &wo) const = 0;

    // û��ʵ�壬ƾ�ղ�������Щle������environment map
    virtual Spectrum Le(const Ray &r) const = 0;

    // �����ڶ����Դ�����ѡ��
    virtual Real Power() const = 0;
};

AGZ_NS_END(Atrc)
