#pragma once

#include <agz/tracer_utility/math.h>
#include <agz/tracer_utility/object.h>

AGZ_TRACER_BEGIN

/**
 * @brief ͼ���ؽ��˲���
 * 
 * �μ� http://alvyray.com/Memos/CG/Microsoft/6_pixel.pdf
 */
class FilmFilter : public obj::Object
{
public:

    using Object::Object;

    /**
     * @brief �����Ч�뾶����pixelΪ��λ
     */
    virtual real radius() const noexcept = 0;

    /**
     * @brief ���˲���ֵ
     */
    virtual real eval(real x, real y) const noexcept = 0;
};

AGZT_INTERFACE(FilmFilter)

AGZ_TRACER_END
