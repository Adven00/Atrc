#pragma once

#include <Atrc/Core/Common.h>

AGZ_NS_BEG(Atrc)

struct LocalCoordSystem
{
    Vec3 ex, ey, ez;

    Vec3 Local2World(const Vec3 &v) const
    {
        return v.x * ex + v.y * ey + v.z * ez;
    }

    Vec3 World2Local(const Vec3 &v) const
    {
        return Vec3(Dot(ex, v), Dot(ey, v), Dot(ez, v));
    }

    static LocalCoordSystem FromEz(const Vec3 &ez)
    {
        Vec3 ex;
        if(ApproxEq(Abs(Dot(ez, Vec3::UNIT_X())), 1.0, 0.1))
            ex = Cross(ez, Vec3::UNIT_Y()).Normalize();
        else
            ex = Cross(ez, Vec3::UNIT_X()).Normalize();
        return { ex, Cross(ez, ex), ez };
    }
};

struct SurfacePoint
{
    // �ཻ���ߵ�tֵ
    Real t = 0.0;

    // ����λ��
    Vec3 pos;

    // �ཻ���ߵķ�����
    Vec3 wo;

    // ����uv���꣬���ཻ������Ĺ������ʾ���
    Vec2 geoUV;

    // �û��Զ���uv���꣬��������ӳ���
    Vec2 usrUV;

    // ���ξֲ�����ϵ������ez���Ǳ��淨��
    LocalCoordSystem geoLocal;

    // �ཻʵ��
    const Entity *entity = nullptr;
    
    // ������ʵ�����ж��壬��������triangle bvh�е�face id��
    uint32_t flag0       = 0;
};

struct ShadingPoint
{
    // ��ɫ�ֲ�����ϵ���󲿷�ʱ����geoLocalһ������bump mapping�ȼ�����Ӱ��
    LocalCoordSystem shdLocal;

    BSDF *bsdf;
};

AGZ_NS_END(Atrc)
