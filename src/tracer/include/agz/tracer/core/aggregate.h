#pragma once

#include <agz/tracer/core/intersection.h>
#include <agz/tracer_utility/object.h>

AGZ_TRACER_BEGIN

class Entity;

/**
 * @brief ʵ��ۺϽӿڣ���ʾ���һ��ʵ��ʵ�ֵ��󽻼������ݽṹ
 */
class Aggregate : public obj::Object
{
public:

    using Object::Object;

    /**
     * @brief ������̬�������ݽṹ
     * 
     * ���������ʵ��󡢿�ʼ��Ⱦǰ����
     */
    virtual void build(const Entity *const*entities, size_t entity_count) = 0;

    virtual bool has_intersection(const Ray &r) const noexcept = 0;

    virtual bool closest_intersection(const Ray &r, EntityIntersection *inct) const noexcept = 0;

    virtual AABB world_bound() const noexcept = 0;
};

AGZT_INTERFACE(Aggregate)

AGZ_TRACER_END
