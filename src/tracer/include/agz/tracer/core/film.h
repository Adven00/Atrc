﻿#pragma once

#include <mutex>

#include <agz/tracer/core/gbuffer.h>
#include <agz/tracer_utility/math.h>
#include <agz/tracer_utility/object.h>
#include <agz/utility/texture.h>

AGZ_TRACER_BEGIN

using ImageBuffer = texture::texture2d_t<Spectrum>;

/**
 * @brief 一块完整film上的一块矩形区域，和原film的存储是分离的
 */
class FilmGrid : public misc::uncopyable_t
{
public:

    virtual ~FilmGrid() = default;

    /** @brief 有效采样区域的x坐标最小值，以像素为单位 */
    virtual int sample_x_beg() const noexcept = 0;

    /** @brief 有效采样区域的x坐标最大值+1 */
    virtual int sample_x_end() const noexcept = 0;

    /** @brief 有效采样区域的y坐标最小值 */
    virtual int sample_y_beg() const noexcept = 0;

    /** @brief 有效采样区域的y坐标最大值+1 */
    virtual int sample_y_end() const noexcept = 0;

    /** @brief 添加一个采样点，用重建滤波器更新内部存储的像素和权重数据 */
    virtual void add_sample(const Vec2 &pos, const Spectrum &value, const GBufferPixel &gpixel, real w = 1) = 0;
};

class Film : public obj::Object
{
public:

    using Object::Object;

    virtual void merge_grid(FilmGrid &&grid) = 0;

    virtual void add_grid(FilmGrid &&grid, const Spectrum &weight = Spectrum(1)) = 0;

    /**
     * @brief 生成一块新grid
     * 
     * 参数单位为像素，需满足：
     * - 0 <= x_beg <= x_end <= w_
     * - 0 <= y_beg <= y_end <= h_
     */
    virtual std::unique_ptr<FilmGrid> new_grid(int x_beg, int x_end, int y_beg, int y_end) const = 0;

    /**
     * @brief 返回最终图像
     */
    virtual ImageBuffer image() const = 0;

    /**
     * @brief 返回GBuffer，其中的成员可以为空，表示该film不支持记录此项信息
     */
    virtual GBuffer gbuffer() const = 0;

    /**
     * @brief 图像分辨率
     */
    virtual Vec2i resolution() const noexcept = 0;

    virtual void map_spectrum(std::function<Spectrum(const Spectrum&)> func) = 0;

    virtual void map_weight(std::function<real(real)> func) = 0;

    virtual void end() = 0;
};

AGZT_INTERFACE(Film)

AGZ_TRACER_END