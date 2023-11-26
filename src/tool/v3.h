//
// Created by matthewperiut on 5/7/21.
//

#pragma once

#include <olcPixelGameEngine.h>
#include <cmath>
#include <string>
#include "../utility/settings/Settings.h"

extern Settings settings;

struct v3 {


    float x = 0;
    float y = 0;
    float z = 0;
    v3() : x(0), y(0) {}
    v3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    v3(const v3& v) : x(v.x), y(v.y), z(v.z) {}
    v3& operator=(const v3& v) = default;
    float mag() const { return float(std::sqrt(x * x + y * y + z * z)); }
    float mag2() const { return x * x + y * y + z * z; }
    v3  norm() const { float r = 1 / mag(); return v3(x * r, y * r, z * r); }
    v3  perp() const { return v3(-y, x, z); }
    v3  floor() const { return v3(std::floor(x), std::floor(y), std::floor(z)); }
    v3  ceil() const { return v3(std::ceil(x), std::ceil(y), std::ceil(z)); }
    v3  max(const v3& v) const { return v3(std::max(x, v.x), std::max(y, v.y), std::max(z, v.z)); }
    v3  min(const v3& v) const { return v3(std::min(x, v.x), std::min(y, v.y), std::min(z, v.z)); }
    float dot(const v3& rhs) const { return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z; }
    //float cross(const v3& rhs) const { return this->x * rhs.y - this->y * rhs.x; }
    v3  operator +  (const v3& rhs) const { return v3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z); }
    v3  operator -  (const v3& rhs) const { return v3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z); }
    v3  operator *  (const float& rhs)           const { return v3(this->x * rhs, this->y * rhs, this->z * rhs); }
    v3  operator *  (const v3& rhs) const { return v3(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z); }
    v3  operator /  (const float& rhs)           const { return v3(this->x / rhs, this->y / rhs, this->z / rhs); }
    v3  operator /  (const v3& rhs) const { return v3(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z); }
    v3& operator += (const v3& rhs) { this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; return *this; }
    v3& operator -= (const v3& rhs) { this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; return *this; }
    v3& operator *= (const float& rhs) { this->x *= rhs; this->y *= rhs; this->z *= rhs; return *this; }
    v3& operator /= (const float& rhs) { this->x /= rhs; this->y /= rhs; this->z /= rhs; return *this; }
    v3& operator *= (const v3& rhs) { this->x *= rhs.x; this->y *= rhs.y; this->z *= rhs.z; return *this; }
    v3& operator /= (const v3& rhs) { this->x /= rhs.x; this->y /= rhs.y; this->z /= rhs.z; return *this; }
    v3  operator +  () const { return { +x, +y, +z }; }
    v3  operator -  () const { return { -x, -y, -z }; }
    bool operator == (const v3& rhs) const { return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z); }
    bool operator != (const v3& rhs) const { return (this->x != rhs.x || this->y != rhs.y || this->z == rhs.z); }
    const std::string str() const { return std::string("(" + std::to_string(this->x) + "," + std::to_string(this->y) + "," + std::to_string(this->z) + ")"); }
    friend std::ostream& operator << (std::ostream& os, const v3& rhs) { os << rhs.str(); return os; }
    //operator v3<int32_t>() const { return { static_cast<int32_t>(this->x), static_cast<int32_t>(this->y) }; }
    //operator v3<float>() const { return { static_cast<float>(this->x), static_cast<float>(this->y) }; }
    //operator v3<double>() const { return { static_cast<double>(this->x), static_cast<double>(this->y) }; }
    olc::vf2d toScreen(olc::vf2d offset, bool noStart = false)
    {
        olc::vf2d ScreenPos{ (float(settings.resolution.x)/2+1) + offset.x, (float(settings.resolution.y)/2+18) + offset.y };
        ScreenPos.x += x;
        ScreenPos.y += x / 2;
        ScreenPos.x += z;
        ScreenPos.y -= z / 2;
        ScreenPos.y -= y;
        return ScreenPos;
    }
    olc::vf2d toScreenNoCentering()
    {
        olc::vf2d ScreenPos{ 0, 15 };
        ScreenPos.x += x;
        ScreenPos.y += x / 2;
        ScreenPos.x += z;
        ScreenPos.y -= z / 2;
        ScreenPos.y -= y;
        return ScreenPos;
    }
};
