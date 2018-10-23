#pragma once

#include <Atrc/Core/Common.h>

AGZ_NS_BEG(Atrc)

struct LightSampleToResult
{
    Vec3 pos;
    Vec3 wi;
    Spectrum radiance;
    Real pdf = 0.0;
};

class Light
{
public:

    virtual ~Light() = default;

    // Ԥ�������Ի�ñ�Ҫ����Ϣ������������ȡ������С�Խ��в�����
    // ȱʡɶҲ����
    virtual void PreprocessScene(const Scene &scene);

    // �ڹ�Դ�ϲ���һ��������sp��ԭ���ϰ�����AreaLe��NonareaLe������
    virtual LightSampleToResult SampleLi(const SurfacePoint &sp) const = 0;

    // ������Դ�ϵĲ����������pdf
    // posOnLightָ��pos�Ƿ��ڹ�Դʵ���ϣ�ǰ�߶�ӦAreaLe�����߶�ӦNonareaLe
    virtual Real SampleLiPDF(const Vec3 &pos, const Vec3 &dst, bool posOnLight = true) const = 0;

    // λ�ò����Ƿ�ʹ��delta�ֲ�
    virtual bool IsDeltaPosition() const = 0;

    // �Ƿ���delta����Ĺ�Դ���������������
    virtual bool IsDeltaDirection() const = 0;

    virtual bool IsDelta() const;

    // �������ʵ��Ĺ�Դ����ĳr��ʵ�彻��sp������һ����-r.dir��radiance
    virtual Spectrum AreaLe(const SurfacePoint &sp) const = 0;

    // û��ʵ�壬��-r.dir����ƾ�ղ�������Щle������skylight��
    virtual Spectrum NonareaLe(const Ray &r) const = 0;

    // �����ڶ����Դ�����ѡ��
    virtual Spectrum Power() const = 0;
};

class GeometricLight : public Light
{
protected:

    const Geometry *geometry_;

public:

    explicit GeometricLight(const Geometry *geometry)
        : geometry_(geometry)
    {
        AGZ_ASSERT(geometry);
    }

    const Geometry *GetGeometry() const
    {
        return geometry_;
    }
};

AGZ_NS_END(Atrc)
