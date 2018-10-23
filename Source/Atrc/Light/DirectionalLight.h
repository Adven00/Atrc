#pragma once

#include <Atrc/Core/Core.h>

AGZ_NS_BEG(Atrc)

class DirectionalLight : public Light
{
    Vec3 dir_;
    Spectrum radiance_;
    
    Vec3 worldCentre_;
    Real worldRadius_;

public:

    DirectionalLight(const Vec3 &dir, const Spectrum &radiance);

    void PreprocessScene(const Scene &scene) override;

    // �ڹ�Դ�ϲ���һ��������sp��ԭ���ϰ�����AreaLe��NonareaLe������
    LightSampleToResult SampleLi(const SurfacePoint &sp) const override;

    // ������Դ�ϵĲ����������pdf
    // posOnLightָ��pos�Ƿ��ڹ�Դʵ���ϣ�ǰ�߶�ӦAreaLe�����߶�ӦNonareaLe
    Real SampleLiPDF(const Vec3 &pos, const Vec3 &dst, bool posOnLight) const override;

    // λ�ò����Ƿ�ʹ��delta�ֲ�
    bool IsDeltaPosition() const override;

    // �Ƿ���delta����Ĺ�Դ���������������
    bool IsDeltaDirection() const override;

    bool IsDelta() const override;

    // �������ʵ��Ĺ�Դ����ĳr��ʵ�彻��sp������һ����-r.dir��radiance
    Spectrum AreaLe(const SurfacePoint &sp) const override;

    // û��ʵ�壬��-r.dir����ƾ�ղ�������Щle������skylight��
    Spectrum NonareaLe(const Ray &r) const override;

    // �����ڶ����Դ�����ѡ��
    Spectrum Power() const override;
};

AGZ_NS_END(Atrc)
