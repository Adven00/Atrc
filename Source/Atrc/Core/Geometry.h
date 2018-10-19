#pragma once

#include <Atrc/Core/Common.h>

#include <Atrc/Core/AABB.h>
#include <Atrc/Core/Ray.h>
#include <Atrc/Core/SurfacePoint.h>
#include <Atrc/Core/Transform.h>

AGZ_NS_BEG(Atrc)

struct GeometrySampleResult
{
    Vec3 pos;
    Vec3 nor;
    Real pdf = 0.0;
};

class Geometry
{
protected:

    Transform local2World_;

public:

    explicit Geometry(const Transform &local2World)
        : local2World_(local2World)
    {
        
    }

    virtual ~Geometry() = default;

    virtual bool HasIntersection(const Ray &r) const;

    // ��䣺t��pos��wo��geoUV��usrUV��geoLocal����flag0��
    virtual bool FindIntersection(const Ray &r, SurfacePoint *sp) const = 0;

    // ��World�����ϵı����
    virtual Real SurfaceArea() const = 0;

    // �ֲ�bound
    virtual AABB LocalBound() const = 0;

    // ����bound
    virtual AABB WorldBound() const;

    // �ڱ����ϲ���
    virtual GeometrySampleResult Sample() const = 0;

    // �����������������������ܶ�
    virtual Real SamplePDF(const Vec3 &pos) const = 0;

    // ��dstΪ��Ŀ��㡱�ڱ����Ͻ��в���
    virtual GeometrySampleResult Sample(const Vec3 &dst) const;

    // ��һ��������pdf
    virtual Real SamplePDF(const Vec3 &pos, const Vec3 &dst) const;
};

AGZ_NS_END(Atrc)
