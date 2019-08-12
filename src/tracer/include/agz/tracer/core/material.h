#pragma once

#include <agz/tracer/core/intersection.h>
#include <agz/tracer/utility/object.h>

AGZ_TRACER_BEGIN

/**
 * @brief ��ͬ���ͽ��ʷֽ����Ĳ���ģ�ͽӿ�
 *
 * ���� ���� -> ShadingPoint�����˶���
 */
class Material : public obj::Object
{
public:

    using Object::Object;

    /** @brief ��������ʵ��Ľ���ת��Ϊshading point */
    virtual ShadingPoint shade(const EntityIntersection &inct, Arena &arena) const = 0;
};

AGZT_INTERFACE(Material)

AGZ_TRACER_END
