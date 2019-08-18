#pragma once

#include <agz/tracer_utility/math.h>

AGZ_TRACER_BEGIN

class BSDF;
class Entity;
class Geometry;
class Material;
class Medium;

/**
 * @brief ����������ϵ�һ��
 */
struct SurfacePoint
{
    Vec3 pos;
    Vec2 uv;
    Coord geometry_coord;
    Coord user_coord;
};

/**
 * @brief �����е�һ��
 */
struct MediumPoint
{
    Vec3 pos;
};

struct GeometryIntersection : SurfacePoint
{
    real t = -1;
    Vec3 wr;
};

/**
 * @brief ������ʵ�����Ľ���
 */
struct EntityIntersection : GeometryIntersection
{
    const Entity *entity     = nullptr;
    const Material *material = nullptr;
    const Medium *medium_in  = nullptr;
    const Medium *medium_out = nullptr;

    const Medium *wr_medium() const noexcept
    {
        return dot(wr, geometry_coord.z) >= 0 ? medium_out : medium_in;
    }

    const Medium *inv_wr_medium() const noexcept
    {
        return dot(wr, geometry_coord.z) >= 0 ? medium_in : medium_out;
    }
};

/**
 * @brief �����ڽ����е�ɢ���
 */
struct MediumIntersection : MediumPoint
{
    const Medium *medium = nullptr;
    real t = -1;
    Vec3 wr;

    bool invalid() const noexcept
    {
        return !wr;
    }
};

struct ShadingPoint
{
    const BSDF *bsdf = nullptr;
};

AGZ_TRACER_END
