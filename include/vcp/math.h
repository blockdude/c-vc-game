#ifndef VCP_MATH_H
#define VCP_MATH_H

#include <cmath>

namespace vcp::math
{

using Dimension = int;

// =============================
// Constants
// =============================

template<typename T> constexpr T EULER   = T(2.71828182845904523536028747135266249);
template<typename T> constexpr T PI      = T(3.14159265358979323846264338327950288);
template<typename T> constexpr T PI_2    = PI<T> / T(2);
template<typename T> constexpr T TAU     = PI<T> * T(2);
template<typename T> constexpr T EPSILON = T(0.0001);

// =============================
// Vector<N, T>
// =============================

template<Dimension N, typename T>
struct Vector
{
    T data[N];

    static constexpr Dimension size = N;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;

    static constexpr Vector filled(T value);
    static constexpr Vector one();
    static constexpr Vector zero();
};

template<typename T>
struct Vector<1, T>
{
    union
    {
        T x;
        T u;
        T w;
        T r;
    };

    static constexpr Dimension size = 1;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;

    static constexpr Vector filled(T value);
    static constexpr Vector one();
    static constexpr Vector zero();
};

template<typename T>
struct Vector<2, T>
{
    union
    {
        struct { T x, y; };
        struct { T u, v; };
        struct { T w, h; };
        struct { T r, g; };
    };

    static constexpr Dimension size = 2;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;

    static constexpr Vector filled(T value);
    static constexpr Vector one();
    static constexpr Vector zero();
};

template<typename T>
struct Vector<3, T>
{
    union
    {
        struct { T x, y, z; };
        struct { T u, v, w; };
        struct { T r, g, b; };
    };

    static constexpr Dimension size = 3;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;

    static constexpr Vector filled(T value);
    static constexpr Vector one();
    static constexpr Vector zero();
};

template<typename T>
struct Vector<4, T>
{
    union
    {
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
        struct { T s, t, p, q; };
    };

    static constexpr Dimension size = 4;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;

    static constexpr Vector filled(T value);
    static constexpr Vector one();
    static constexpr Vector zero();
};

// =============================
// Quaternion<T>
// =============================

template<typename T>
struct Quaternion
{
    T x, y, z, w;

    static constexpr Dimension size = 4;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;

    static constexpr Quaternion identity();
    static constexpr Quaternion filled(T value);
};

// =============================
// Matrix<N, M, T>
// =============================

/*
 * Layout is column-major. Access via:
 *     m(r, c) — (row, col),  returns data[r + c * N]
 *     m[i]    — linear,       returns data[i]
 *
 * GPU-ready: data is contiguous in column-major order.
 */

template<Dimension N, Dimension M, typename T>
struct Matrix
{
    T data[N * M];

    static constexpr Dimension rows = N;
    static constexpr Dimension cols = M;
    constexpr T &operator()(Dimension r, Dimension c);
    constexpr const T &operator()(Dimension r, Dimension c) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;

    static constexpr Matrix identity();
    static constexpr Matrix diagonal(T value);
    static constexpr Matrix filled(T value);
    static constexpr Matrix zero();
    static constexpr Matrix one();
};

// =============================
// Basis<K, E>
// =============================

template<Dimension K, typename E>
struct Basis
{
    E v[K];

    constexpr E &operator()(Dimension i);
    constexpr const E &operator()(Dimension i) const;
    constexpr E &operator[](Dimension i);
    constexpr const E &operator[](Dimension i) const;
};

// =============================
// EulerOrder<T>
// =============================

template<typename T>
struct EulerOrder
{
    Vector<3, T> a0, a1, a2;
};

// =============================
// Cardinal<N, T>
// =============================

template<Dimension N, typename T>
struct Cardinal
{
    static constexpr Vector<N, T> get(Dimension i);
    static constexpr Vector<N, T> X = get(0);
    static constexpr Vector<N, T> Y = get(1);
    static constexpr Vector<N, T> Z = get(2);
    static constexpr Vector<N, T> W = get(3);
};

template<typename T>
struct Cardinal<1, T>
{
    static constexpr Vector<1, T> get(Dimension i);
    static constexpr Vector<1, T> X = { T(1) };
};

template<typename T>
struct Cardinal<2, T>
{
    static constexpr Vector<2, T> get(Dimension i);
    static constexpr Vector<2, T> X = { T(1), T(0) };
    static constexpr Vector<2, T> Y = { T(0), T(1) };
};

template<typename T>
struct Cardinal<3, T>
{
    static constexpr Vector<3, T> get(Dimension i);
    static constexpr Vector<3, T> X = { T(1), T(0), T(0) };
    static constexpr Vector<3, T> Y = { T(0), T(1), T(0) };
    static constexpr Vector<3, T> Z = { T(0), T(0), T(1) };
    static constexpr EulerOrder<T> ZYX = { Z, Y, X };
    static constexpr EulerOrder<T> XYZ = { X, Y, Z };
    static constexpr EulerOrder<T> XZY = { X, Z, Y };
    static constexpr EulerOrder<T> YXZ = { Y, X, Z };
    static constexpr EulerOrder<T> YZX = { Y, Z, X };
    static constexpr EulerOrder<T> ZXY = { Z, X, Y };
};

template<typename T>
struct Cardinal<4, T>
{
    static constexpr Vector<4, T> get(Dimension i);
    static constexpr Vector<4, T> X = { T(1), T(0), T(0), T(0) };
    static constexpr Vector<4, T> Y = { T(0), T(1), T(0), T(0) };
    static constexpr Vector<4, T> Z = { T(0), T(0), T(1), T(0) };
    static constexpr Vector<4, T> W = { T(0), T(0), T(0), T(1) };
};

// =============================
// Color<T>
// =============================

template<typename T>
struct Color
{
    T r, g, b, a;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

enum class BlendMode
{
    OVER,
    ADD,
    MULTIPLY,
    SCREEN,
    PREMUL,
    SUBTRACT,
    DIFFERENCE,
    DARKEN,
    LIGHTEN,
    DIVIDE,
    EXCLUSION,
    OVERLAY,
    HARD_LIGHT,
    SOFT_LIGHT,
    COLOR_DODGE,
    COLOR_BURN,
    LINEAR_DODGE,
    LINEAR_BURN,
    HUE,
    SATURATION,
    COLOR,
    LUMINOSITY
};

template<typename T>
struct Luminance
{
    // BT.601 — Standard-definition TV (NTSC)
    static constexpr Vector<3, T> BT601  = { T(0.2990), T(0.5870), T(0.1140) };

    // BT.709 — HDTV, sRGB (the universal default)
    static constexpr Vector<3, T> BT709  = { T(0.2126), T(0.7152), T(0.0722) };

    // BT.2020 — UHD, wide gamut
    static constexpr Vector<3, T> BT2020 = { T(0.2627), T(0.6780), T(0.0593) };

    // ACEScg — Linear ACES workspace (film/VFX, used by Unreal & HDRP)
    static constexpr Vector<3, T> ACEScg = { T(0.2723), T(0.7181), T(0.0095) };

    // SMPTE 240M — Early HDTV standard
    static constexpr Vector<3, T> SMPTE240M = { T(0.2120), T(0.7010), T(0.0870) };
};

struct Gamma
{
    // Generic gamma curve — gamma(c, Gamma::curve(2.2f))
    template<typename T>
    static auto curve(T exp)
    {
        return [exp](T x) { return std::pow(x, exp); };
    }

    // True sRGB encode (linear → sRGB)
    template<typename T>
    static auto encode_sRGB()
    {
        return [](T x) -> T
        {
            return x <= T(0.0031308) ? x * T(12.92)
                 : T(1.055) * std::pow(x, T(1.0) / T(2.4)) - T(0.055);
        };
    }

    // True sRGB decode (sRGB → linear)
    template<typename T>
    static auto decode_sRGB()
    {
        return [](T x) -> T
        {
            return x <= T(0.04045) ? x / T(12.92)
                 : std::pow((x + T(0.055)) / T(1.055), T(2.4));
        };
    }

    // BT.1886 encode (linear → display)
    template<typename T>
    static auto encode_BT1886()
    {
        return [](T x) { return std::pow(x, T(1.0) / T(2.4)); };
    }

    // BT.1886 decode (display → linear)
    template<typename T>
    static auto decode_BT1886()
    {
        return [](T x) { return std::pow(x, T(2.4)); };
    }
};

// =============================
// Line<N, T>
// =============================

template<Dimension N, typename T>
struct Line
{
    Vector<N, T> a;
    Vector<N, T> b;

    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// Triangle<N, T>
// =============================

template<Dimension N, typename T>
struct Triangle
{
    Vector<N, T> a;
    Vector<N, T> b;
    Vector<N, T> c;

    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// Ray<N, T>
// =============================

template<Dimension N, typename T>
struct Ray
{
    Vector<N, T> origin;
    Vector<N, T> direction;

    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// Ball<N, T>
// =============================

template<Dimension N, typename T>
struct Ball
{
    Vector<N, T> center;
    T r;

    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T>
struct Ball<1, T>
{
    union
    {
        T x;
        Vector<1, T> center;
    };

    T r;

    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T>
struct Ball<2, T>
{
    union
    {
        struct
        {
            T x, y;
        };

        Vector<2, T> center;
    };

    T r;

    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T>
struct Ball<3, T>
{
    union
    {
        struct
        {
            T x, y, z;
        };

        Vector<3, T> center;
    };

    T r;

    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// Box<N, T>
// =============================

template<Dimension N, typename T>
struct Box
{
    Vector<N, T> position;
    Vector<N, T> size;

    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T>
struct Box<1, T>
{
    union
    {
        struct
        {
            T x;
            T w;
        };

        struct
        {
            Vector<1, T> position;
            Vector<1, T> size;
        };
    };

    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T>
struct Box<2, T>
{
    union
    {
        struct
        {
            T x, y;
            T w, h;
        };

        struct
        {
            Vector<2, T> position;
            Vector<2, T> size;
        };
    };

    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T>
struct Box<3, T>
{
    union
    {
        struct
        {
            T x, y, z;
            T w, h, d;
        };

        struct
        {
            Vector<3, T> position;
            Vector<3, T> size;
        };
    };

    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// AABB<N, T>
// =============================

template<Dimension N, typename T>
struct AABB
{
    Vector<N, T> min;
    Vector<N, T> max;

    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// OBB<N, T, R>
// =============================

template<Dimension N, typename T, typename R = Matrix<N, N, T>>
struct OBB
{
    Vector<N, T> center;
    Vector<N, T> extent;
    R orientation;

    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// Scalar utilities
// =============================

template<typename T> constexpr T min(T a, T b);
template<typename T> constexpr T max(T a, T b);
template<typename T> constexpr T clamp(T v, T lo, T hi);
template<typename T> constexpr T sign(T v);
template<typename T> constexpr T abs(T v);
template<typename T> constexpr T lerp(T a, T b, T t);
template<typename T> constexpr T normalize(T v, T min, T max);
template<typename T> constexpr T radians(T degrees);
template<typename T> constexpr T degrees(T radians);
template<typename T> constexpr T saturate(T v);
template<typename T> constexpr T modulo(T a, T b);
template<typename T> constexpr T truncated_modulo(T a, T b);
template<typename T> constexpr T closest_offset(T from, T to, T period);
template<typename T> constexpr T smoothstep(T edge0, T edge1, T x);

// =============================
// Vector math
// =============================

template<Dimension N, typename T> constexpr Vector<N, T> add(Vector<N, T> a, Vector<N, T> b);
template<Dimension N, typename T> constexpr Vector<N, T> add(Vector<N, T> v, T s);
template<Dimension N, typename T> constexpr Vector<N, T> add(T s, Vector<N, T> v);
template<Dimension N, typename T> constexpr Vector<N, T> sub(Vector<N, T> a, Vector<N, T> b);
template<Dimension N, typename T> constexpr Vector<N, T> sub(Vector<N, T> v, T s);
template<Dimension N, typename T> constexpr Vector<N, T> sub(T s, Vector<N, T> v);
template<Dimension N, typename T> constexpr Vector<N, T> mul(Vector<N, T> a, Vector<N, T> b);
template<Dimension N, typename T> constexpr Vector<N, T> mul(Vector<N, T> v, T s);
template<Dimension N, typename T> constexpr Vector<N, T> mul(T s, Vector<N, T> v);
template<Dimension N, typename T> constexpr Vector<N, T> div(Vector<N, T> a, Vector<N, T> b);
template<Dimension N, typename T> constexpr Vector<N, T> div(Vector<N, T> v, T s);
template<Dimension N, typename T> constexpr Vector<N, T> div(T s, Vector<N, T> v);
template<Dimension N, typename T> constexpr Vector<N, T> negate(Vector<N, T> v);
template<Dimension N, typename T> constexpr Vector<N, T> lerp(Vector<N, T> a, Vector<N, T> b, T t);
template<Dimension N, typename T> constexpr Vector<N, T> reflect(Vector<N, T> v, Vector<N, T> normal);
template<Dimension N, typename T> constexpr Vector<N, T> move_towards(Vector<N, T> from, Vector<N, T> to, T delta);
template<Dimension N, typename T> constexpr Vector<N, T> invert(Vector<N, T> v);
template<Dimension N, typename T> constexpr Vector<N, T> clamp_length(Vector<N, T> v, T lo, T hi);
template<Dimension N, typename T> constexpr Vector<N, T> min(Vector<N, T> a, Vector<N, T> b);
template<Dimension N, typename T> constexpr Vector<N, T> max(Vector<N, T> a, Vector<N, T> b);
template<Dimension N, typename T> constexpr Vector<N, T> clamp(Vector<N, T> v, Vector<N, T> lo, Vector<N, T> hi);
template<Dimension N, typename T> constexpr Vector<N, T> clamp(Vector<N, T> v, T lo, T hi);
template<Dimension N, typename T> constexpr T length(Vector<N, T> v);
template<Dimension N, typename T> constexpr T length_squared(Vector<N, T> v);
template<Dimension N, typename T> constexpr T dot(Vector<N, T> a, Vector<N, T> b);
template<Dimension N, typename T> constexpr T distance(Vector<N, T> a, Vector<N, T> b);
template<Dimension N, typename T> constexpr T distance_squared(Vector<N, T> a, Vector<N, T> b);
template<Dimension N, typename T> constexpr T angle(Vector<N, T> a, Vector<N, T> b);
template<Dimension N, typename T> constexpr bool equals(Vector<N, T> a, Vector<N, T> b, T epsilon = EPSILON<T>);
template<Dimension N, typename T> constexpr Vector<N, T> normalize(Vector<N, T> v);
template<Dimension N, typename T> constexpr Vector<N, T> rotate(Vector<N, T> vec, T angle, Vector<N, T> u, Vector<N, T> v);
template<Dimension N, typename T> constexpr Vector<N, T> rotate(Vector<N, T> v, Vector<N, T> from, Vector<N, T> to);
template<Dimension N, typename T> constexpr Vector<N, T> project(Vector<N, T> v, Vector<N, T> axis);
template<Dimension N, typename T> constexpr Vector<N, T> reject(Vector<N, T> v, Vector<N, T> axis);
template<Dimension N, typename T> constexpr Vector<N, T> center(Vector<N, T> a, Vector<N, T> b);
template<Dimension N, typename T> constexpr Vector<N, T> orthogonal(Vector<N, T> v);
template<Dimension N, typename T> constexpr Vector<N, T> abs(Vector<N, T> v);
template<Dimension N, typename T> constexpr Vector<N, T> sign(Vector<N, T> v);
template<Dimension N, typename T> constexpr Vector<N, T> saturate(Vector<N, T> v);
template<Dimension N, typename T> constexpr Vector<N, T> safe_normalize(Vector<N, T> v);
template<Dimension N, typename T> constexpr Vector<N, T> refract(Vector<N, T> v, Vector<N, T> normal, T eta);
template<Dimension N, typename T> constexpr Vector<N, T> modulo(Vector<N, T> v, T d);
template<Dimension N, typename T> constexpr Vector<N, T> modulo(Vector<N, T> a, Vector<N, T> b);
template<Dimension N, typename T> constexpr Vector<N, T> truncated_modulo(Vector<N, T> v, T d);
template<Dimension N, typename T> constexpr Vector<N, T> truncated_modulo(Vector<N, T> a, Vector<N, T> b);
template<Dimension N, typename T> constexpr Vector<N, T> closest_offset(Vector<N, T> from, Vector<N, T> to, T period);
template<Dimension N, typename T> constexpr Vector<N, T> closest_offset(Vector<N, T> from, Vector<N, T> to, Vector<N, T> period);
template<Dimension N, typename T> constexpr Vector<N, T> smoothstep(Vector<N, T> edge0, Vector<N, T> edge1, Vector<N, T> x);
template<Dimension N, Dimension M, typename T> constexpr Vector<N, T> resize(Vector<M, T> v, T fill = T{});
template<Dimension N, typename T = float> constexpr Vector<N, T> cardinal(Dimension i);
template<typename T, Dimension N, Dimension... Ns> constexpr Vector<(N + ... + Ns), T> concat(Vector<N, T> a, Vector<Ns, T>... rest);
template<Dimension N, typename T, typename... Scalars> constexpr Vector<N + 1 + sizeof...(Scalars), T> concat(Vector<N, T> v, T s, Scalars... rest);
template<Dimension N, typename T> constexpr Vector<N + 1, T> concat(T s, Vector<N, T> v);
template<typename T, typename... Scalars> constexpr Vector<1 + sizeof...(Scalars), T> concat(T first, Scalars... rest);

// =============================
// Vec2-specific
// =============================

template<typename T> constexpr T cross(Vector<2, T> a, Vector<2, T> b);
template<typename T> constexpr Vector<2, T> orthogonal(Vector<2, T> v);
template<typename T> constexpr Vector<2, T> orthogonal_cw(Vector<2, T> v);
template<typename T> constexpr Vector<2, T> rotate(Vector<2, T> v, T angle);
template<typename T> constexpr T line_angle(Vector<2, T> a, Vector<2, T> b);
template<typename T> constexpr Vector<2, T> transform(Matrix<4, 4, T> m, Vector<2, T> v, T w = T(1));
template<typename T> constexpr Vector<2, T> transform(Vector<2, T> v, Matrix<4, 4, T> m, T w = T(1));
template<typename T> constexpr Vector<2, T> transform(Matrix<3, 3, T> m, Vector<2, T> v, T z = T(1));
template<typename T> constexpr Vector<2, T> transform(Vector<2, T> v, Matrix<3, 3, T> m, T z = T(1));

// =============================
// Vec3-specific
// =============================

template<typename T> constexpr Vector<3, T> cross(Vector<3, T> a, Vector<3, T> b);
template<typename T> constexpr Vector<3, T> rotate(Vector<3, T> v, Quaternion<T> q);
template<typename T> constexpr Vector<3, T> rotate(Vector<3, T> v, T angle, Vector<3, T> axis);
template<typename T> constexpr Vector<3, T> rotate(Vector<3, T> v, T pitch, T yaw, T roll, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Vector<3, T> rotate(Vector<3, T> v, Vector<3, T> euler, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Vector<3, T> euler(Quaternion<T> q, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Vector<3, T> euler(Matrix<3, 3, T> m, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Vector<3, T> euler(Matrix<4, 4, T> m, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Vector<3, T> euler(T angle, Vector<3, T> axis, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Vector<3, T> euler(Vector<3, T> from, Vector<3, T> to, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Vector<3, T> euler(T pitch, T yaw, T roll);
template<typename T> constexpr Vector<3, T> transform(Matrix<4, 4, T> m, Vector<3, T> v, T w = T(1));
template<typename T> constexpr Vector<3, T> transform(Vector<3, T> v, Matrix<4, 4, T> m, T w = T(1));

// =============================
// Vec4-specific
// =============================

template<typename T> constexpr Vector<4, T> rotate(Vector<4, T> v, Quaternion<T> q);
template<typename T> constexpr Vector<3, T> perspective_divide(Vector<4, T> v);

// =============================
// Quaternion
// =============================

template<typename T> constexpr Quaternion<T> add(Quaternion<T> a, Quaternion<T> b);
template<typename T> constexpr Quaternion<T> add(Quaternion<T> q, T s);
template<typename T> constexpr Quaternion<T> add(T s, Quaternion<T> q);
template<typename T> constexpr Quaternion<T> sub(Quaternion<T> a, Quaternion<T> b);
template<typename T> constexpr Quaternion<T> sub(Quaternion<T> q, T s);
template<typename T> constexpr Quaternion<T> sub(T s, Quaternion<T> q);
template<typename T> constexpr Quaternion<T> mul(Quaternion<T> a, Quaternion<T> b);
template<typename T> constexpr Quaternion<T> mul(Quaternion<T> q, T s);
template<typename T> constexpr Quaternion<T> mul(T s, Quaternion<T> q);
template<typename T> constexpr Vector<3, T> mul(Quaternion<T> q, Vector<3, T> v);
template<typename T> constexpr Vector<4, T> mul(Quaternion<T> q, Vector<4, T> v);
template<typename T> constexpr Quaternion<T> project(Quaternion<T> a, Quaternion<T> b);
template<typename T> constexpr Quaternion<T> reject(Quaternion<T> a, Quaternion<T> b);
template<typename T> constexpr Quaternion<T> div(Quaternion<T> q, T s);
template<typename T> constexpr Quaternion<T> div(T s, Quaternion<T> q);
template<typename T> constexpr T length(Quaternion<T> q);
template<typename T> constexpr T angle(Quaternion<T> q);
template<typename T> constexpr Quaternion<T> conjugate(Quaternion<T> q);
template<typename T> constexpr Quaternion<T> negate(Quaternion<T> q);
template<typename T> constexpr Quaternion<T> normalize(Quaternion<T> q);
template<typename T> constexpr Quaternion<T> invert(Quaternion<T> q);
template<typename T> constexpr Quaternion<T> lerp(Quaternion<T> a, Quaternion<T> b, T t);
template<typename T> constexpr Quaternion<T> nlerp(Quaternion<T> a, Quaternion<T> b, T t);
template<typename T> constexpr Quaternion<T> slerp(Quaternion<T> a, Quaternion<T> b, T t, T epsilon);
template<typename T> constexpr Quaternion<T> exp_map(Vector<3, T> v);
template<typename T> constexpr Vector<3, T> log_map(Quaternion<T> q);
template<typename T> constexpr T dot(Quaternion<T> a, Quaternion<T> b);
template<typename T> constexpr T project_angle(Quaternion<T> q, Vector<3, T> axis);        // rotation angle around axis
template<typename T> constexpr T reject_angle(Quaternion<T> q, Vector<3, T> axis);    // rotation angle perpendicular to axis
template<typename T> constexpr Quaternion<T> project(Quaternion<T> q, Vector<3, T> axis);
template<typename T> constexpr Quaternion<T> reject(Quaternion<T> q, Vector<3, T> axis);
template<typename T> constexpr Quaternion<T> quaternion(Vector<4, T> v);
template<typename T> constexpr Quaternion<T> orientation(T pitch, T yaw, T roll, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Quaternion<T> orientation(Vector<3, T> euler, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Quaternion<T> orientation(T angle, Vector<3, T> axis);
template<typename T> constexpr Quaternion<T> orientation(Matrix<4, 4, T> m);
template<typename T> constexpr Quaternion<T> orientation(Matrix<3, 3, T> m);
template<typename T> constexpr Quaternion<T> orientation(Vector<3, T> from, Vector<3, T> to);
template<typename T> constexpr Quaternion<T> orient(Quaternion<T> q, T pitch, T yaw, T roll, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Quaternion<T> orient(T pitch, T yaw, T roll, Quaternion<T> q, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Quaternion<T> orient(Quaternion<T> q, Vector<3, T> euler, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Quaternion<T> orient(Vector<3, T> euler, Quaternion<T> q, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Quaternion<T> orient(Quaternion<T> q, T angle, Vector<3, T> axis);
template<typename T> constexpr Quaternion<T> orient(T angle, Vector<3, T> axis, Quaternion<T> q);
template<typename T> constexpr Quaternion<T> orient(Quaternion<T> q, Matrix<4, 4, T> m);
template<typename T> constexpr Quaternion<T> orient(Matrix<4, 4, T> m, Quaternion<T> q);
template<typename T> constexpr bool equals(Quaternion<T> a, Quaternion<T> b, T epsilon = EPSILON<T>);

// =============================
// Matrix
// =============================

template<Dimension N, Dimension K, Dimension M, typename T> constexpr Matrix<N, M, T> mul(Matrix<N, K, T> a, Matrix<K, M, T> b);
template<Dimension N, Dimension M, typename T> constexpr Vector<N, T> mul(Matrix<N, M, T> m, Vector<M, T> v);
template<Dimension N, Dimension M, typename T> constexpr Vector<M, T> mul(Vector<N, T> v, Matrix<N, M, T> m);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> mul(Matrix<N, M, T> m, T s);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> mul(T s, Matrix<N, M, T> m);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> add(Matrix<N, M, T> a, Matrix<N, M, T> b);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> add(Matrix<N, M, T> m, T s);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> add(T s, Matrix<N, M, T> m);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> sub(Matrix<N, M, T> a, Matrix<N, M, T> b);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> sub(Matrix<N, M, T> m, T s);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> sub(T s, Matrix<N, M, T> m);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> div(Matrix<N, M, T> m, T s);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> div(T s, Matrix<N, M, T> m);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> abs(Matrix<N, M, T> m);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> sign(Matrix<N, M, T> m);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> saturate(Matrix<N, M, T> m);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> modulo(Matrix<N, M, T> m, T d);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> modulo(Matrix<N, M, T> a, Matrix<N, M, T> b);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> truncated_modulo(Matrix<N, M, T> m, T d);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> truncated_modulo(Matrix<N, M, T> a, Matrix<N, M, T> b);
template<Dimension N, typename T> constexpr T determinant(Matrix<N, N, T> m);
template<Dimension N, typename T> constexpr T trace(Matrix<N, N, T> m);
template<Dimension N, Dimension M, typename T> constexpr Matrix<M, N, T> transpose(Matrix<N, M, T> m);
template<Dimension N, typename T> constexpr Matrix<N, N, T> invert(Matrix<N, N, T> m);
template<Dimension N, Dimension R, Dimension C, typename T> constexpr Matrix<N, N, T> resize(Matrix<R, C, T> m, T fill = T{});
template<Dimension N, Dimension M, Dimension R, Dimension C, typename T> constexpr Matrix<N, M, T> resize(Matrix<R, C, T> m, T fill = T{});
template<Dimension RA, Dimension CA, Dimension RB, Dimension CB, typename T> constexpr Matrix<max(RA, RB), max(CA, CB), T> embed(Matrix<RA, CA, T> a, Matrix<RB, CB, T> b);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> outer_product(Vector<N, T> a, Vector<M, T> b);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> project(Matrix<N, M, T> a, Matrix<N, M, T> b);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> reject(Matrix<N, M, T> a, Matrix<N, M, T> b);
template<Dimension N, typename T> constexpr void svd(Matrix<N, N, T> m, Matrix<N, N, T> &u, Vector<N, T> &sigma, Matrix<N, N, T> &v);
template<Dimension N, typename T> constexpr Vector<N / 2, T> principal_angles(Matrix<N, N, T> m);
template<Dimension N, typename T> constexpr T project_angle(Matrix<N, N, T> m, Vector<N, T> u, Vector<N, T> v);
template<Dimension N, typename T> constexpr T reject_angle(Matrix<N, N, T> m, Vector<N, T> u, Vector<N, T> v);

// =============================
// Matrix 2x2
// =============================

// Returns the principal rotation angle of a 2x2 rotation matrix
template<typename T> constexpr T angle(Matrix<2, 2, T> m);

// =============================
// Matrix 3x3
// =============================

// Creates a 3x3 skew-symmetric cross product matrix from a 3D vector
template<typename T> constexpr Matrix<3, 3, T> skew(Vector<3, T> v);
// Returns the principal rotation angle of a 3x3 rotation matrix
template<typename T> constexpr T angle(Matrix<3, 3, T> m);
// Returns the rotation angle parallel/perpendicular to a given axis
template<typename T> constexpr T project_angle(Matrix<3, 3, T> m, Vector<3, T> axis);
template<typename T> constexpr T reject_angle(Matrix<3, 3, T> m, Vector<3, T> axis);

// =============================
// Matrix 4x4
// =============================

template<typename T> constexpr Matrix<4, 4, T> perspective(T fovy, T aspect, T near, T far);
template<typename T> constexpr Matrix<4, 4, T> orthographic(T left, T right, T bottom, T top, T near, T far);
template<typename T> constexpr Matrix<4, 4, T> frustum(T left, T right, T bottom, T top, T near, T far);
template<typename T> constexpr Matrix<4, 4, T> lookat(Vector<3, T> eye, Vector<3, T> target, Vector<3, T> up);
template<typename T> constexpr T project_angle(Matrix<4, 4, T> m, Vector<3, T> axis);
template<typename T> constexpr T reject_angle(Matrix<4, 4, T> m, Vector<3, T> axis);

// =============================
// Affine transforms
// =============================

// Create
template<Dimension N, typename T> constexpr Matrix<N + 1, N + 1, T> translation(Vector<N, T> v);
template<Dimension N, typename T> constexpr Matrix<N + 1, N + 1, T> scaling(Vector<N, T> v);
template<Dimension N, typename T> constexpr Matrix<N + 1, N + 1, T> rotation(T angle, Vector<N, T> u, Vector<N, T> v);
template<Dimension N, typename T> constexpr Matrix<N + 1, N + 1, T> rotation(Vector<N, T> from, Vector<N, T> to);
template<Dimension N, typename T> constexpr Matrix<N, N, T> linear_rotation(T angle, Vector<N, T> u, Vector<N, T> v);
template<Dimension N, typename T> constexpr Matrix<N, N, T> linear_rotation(Vector<N, T> from, Vector<N, T> to);
template<typename T> constexpr Matrix<2, 2, T> linear_rotation(T angle);
template<typename T> constexpr Matrix<3, 3, T> linear_rotation(Quaternion<T> q);
template<typename T> constexpr Matrix<3, 3, T> linear_rotation(T angle, Vector<3, T> axis);
template<typename T> constexpr Matrix<3, 3, T> linear_rotation(T pitch, T yaw, T roll, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Matrix<3, 3, T> linear_rotation(Vector<3, T> euler, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Matrix<3, 3, T> rotation(T angle);
template<typename T> constexpr Matrix<4, 4, T> rotation(T angle, Vector<3, T> axis);
template<typename T> constexpr Matrix<4, 4, T> rotation(Quaternion<T> q);
template<typename T> constexpr Matrix<4, 4, T> rotation(T pitch, T yaw, T roll, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Matrix<4, 4, T> rotation(Vector<3, T> euler, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Matrix<4, 4, T> rotation_x(T angle);
template<typename T> constexpr Matrix<4, 4, T> rotation_y(T angle);
template<typename T> constexpr Matrix<4, 4, T> rotation_z(T angle);

// Extract
template<Dimension N, typename T> constexpr Matrix<N, N, T> translation(Matrix<N, N, T> m);
template<Dimension N, typename T> constexpr Matrix<N, N, T> scaling(Matrix<N, N, T> m);
template<Dimension N, typename T> constexpr Matrix<N, N, T> rotation(Matrix<N, N, T> m);
template<Dimension N, typename T> constexpr Matrix<N - 1, N - 1, T> linear_rotation(Matrix<N, N, T> m);
template<Dimension N, typename T> constexpr Vector<N - 1, T> displacement(Matrix<N, N, T> m);
template<Dimension N, typename T> constexpr Vector<N - 1, T> scaling_factors(Matrix<N, N, T> m);

// Decompose
template<Dimension N, typename T> constexpr void decompose(Matrix<N, N, T> m, Matrix<N, N, T> &translation, Matrix<N, N, T> &rotation, Matrix<N, N, T> &scale);
template<Dimension N, typename T> constexpr void decompose(Matrix<N, N, T> m, Matrix<N, N, T> &translation, Matrix<N - 1, N - 1, T> &rotation, Matrix<N, N, T> &scale);
template<Dimension N, typename T> constexpr void decompose(Matrix<N, N, T> m, Vector<N - 1, T> &translation, Matrix<N - 1, N - 1, T> &rotation, Vector<N - 1, T> &scale);
template<Dimension N, typename T> constexpr void decompose(Matrix<N, N, T> m, Vector<N - 1, T> &translation, Matrix<N, N, T> &rotation, Vector<N - 1, T> &scale);
template<typename T> constexpr void decompose(Matrix<4, 4, T> m, Vector<3, T> &translation, Quaternion<T> &rotation, Vector<3, T> &scale);
template<typename T> constexpr void decompose(Matrix<4, 4, T> m, Vector<3, T> &translation, Vector<3, T> &rotation, Vector<3, T> &scale);

// Apply
template<Dimension N, typename T> constexpr Matrix<N + 1, N + 1, T> translate(Matrix<N + 1, N + 1, T> m, Vector<N, T> v);
template<Dimension N, typename T> constexpr Matrix<N + 1, N + 1, T> scale(Matrix<N + 1, N + 1, T> m, Vector<N, T> v);
template<Dimension N, typename T> constexpr Matrix<N + 1, N + 1, T> rotate(Matrix<N + 1, N + 1, T> m, T angle, Vector<N, T> u, Vector<N, T> v);
template<Dimension N, typename T> constexpr Matrix<N + 1, N + 1, T> rotate(Matrix<N + 1, N + 1, T> m, Vector<N, T> from, Vector<N, T> to);
template<Dimension N, typename T> constexpr Matrix<N, N, T> linear_rotate(Matrix<N, N, T> m, T angle, Vector<N, T> u, Vector<N, T> v);
template<Dimension N, typename T> constexpr Matrix<N, N, T> linear_rotate(Matrix<N, N, T> m, Vector<N, T> from, Vector<N, T> to);
template<typename T> constexpr Matrix<2, 2, T> linear_rotate(Matrix<2, 2, T> m, T angle);
template<typename T> constexpr Matrix<3, 3, T> linear_rotate(Matrix<3, 3, T> m, Quaternion<T> q);
template<typename T> constexpr Matrix<3, 3, T> linear_rotate(Matrix<3, 3, T> m, T angle, Vector<3, T> axis);
template<typename T> constexpr Matrix<3, 3, T> linear_rotate(Matrix<3, 3, T> m, T pitch, T yaw, T roll, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Matrix<3, 3, T> linear_rotate(Matrix<3, 3, T> m, Vector<3, T> euler, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Matrix<3, 3, T> rotate(Matrix<3, 3, T> m, T angle);
template<typename T> constexpr Matrix<4, 4, T> rotate(Matrix<4, 4, T> m, T angle, Vector<3, T> axis);
template<typename T> constexpr Matrix<4, 4, T> rotate(Matrix<4, 4, T> m, Quaternion<T> q);
template<typename T> constexpr Matrix<4, 4, T> rotate(Matrix<4, 4, T> m, T pitch, T yaw, T roll, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Matrix<4, 4, T> rotate(Matrix<4, 4, T> m, Vector<3, T> euler, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Matrix<4, 4, T> rotate_x(Matrix<4, 4, T> m, T angle);
template<typename T> constexpr Matrix<4, 4, T> rotate_y(Matrix<4, 4, T> m, T angle);
template<typename T> constexpr Matrix<4, 4, T> rotate_z(Matrix<4, 4, T> m, T angle);

// Pre Apply
template<Dimension N, typename T> constexpr Matrix<N + 1, N + 1, T> translate(Vector<N, T> v, Matrix<N + 1, N + 1, T> m);
template<Dimension N, typename T> constexpr Matrix<N + 1, N + 1, T> scale(Vector<N, T> v, Matrix<N + 1, N + 1, T> m);
template<Dimension N, typename T> constexpr Matrix<N + 1, N + 1, T> rotate(T angle, Vector<N, T> u, Vector<N, T> v, Matrix<N + 1, N + 1, T> m);
template<Dimension N, typename T> constexpr Matrix<N + 1, N + 1, T> rotate(Vector<N, T> from, Vector<N, T> to, Matrix<N + 1, N + 1, T> m);
template<Dimension N, typename T> constexpr Matrix<N, N, T> linear_rotate(T angle, Vector<N, T> u, Vector<N, T> v, Matrix<N, N, T> m);
template<Dimension N, typename T> constexpr Matrix<N, N, T> linear_rotate(Vector<N, T> from, Vector<N, T> to, Matrix<N, N, T> m);
template<typename T> constexpr Matrix<2, 2, T> linear_rotate(T angle, Matrix<2, 2, T> m);
template<typename T> constexpr Matrix<3, 3, T> linear_rotate(Quaternion<T> q, Matrix<3, 3, T> m);
template<typename T> constexpr Matrix<3, 3, T> linear_rotate(T angle, Vector<3, T> axis, Matrix<3, 3, T> m);
template<typename T> constexpr Matrix<3, 3, T> linear_rotate(T pitch, T yaw, T roll, Matrix<3, 3, T> m, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Matrix<3, 3, T> linear_rotate(Vector<3, T> euler, Matrix<3, 3, T> m, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Matrix<3, 3, T> rotate(T angle, Matrix<3, 3, T> m);
template<typename T> constexpr Matrix<4, 4, T> rotate(T angle, Vector<3, T> axis, Matrix<4, 4, T> m);
template<typename T> constexpr Matrix<4, 4, T> rotate(Quaternion<T> q, Matrix<4, 4, T> m);
template<typename T> constexpr Matrix<4, 4, T> rotate(T pitch, T yaw, T roll, Matrix<4, 4, T> m, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Matrix<4, 4, T> rotate(Vector<3, T> euler, Matrix<4, 4, T> m, EulerOrder<T> order = Cardinal<3, T>::ZYX);
template<typename T> constexpr Matrix<4, 4, T> rotate_x(T angle, Matrix<4, 4, T> m);
template<typename T> constexpr Matrix<4, 4, T> rotate_y(T angle, Matrix<4, 4, T> m);
template<typename T> constexpr Matrix<4, 4, T> rotate_z(T angle, Matrix<4, 4, T> m);

// =============================
// Basis math
// =============================

template<Dimension K, Dimension N, typename T> constexpr Basis<K, Vector<N, T>> orthonormalize(Basis<K, Vector<N, T>> b);
template<Dimension K, Dimension N, typename T> constexpr Vector<K, T> project(Vector<N, T> v, Basis<K, Vector<N, T>> b);
template<Dimension K, Dimension N, typename T> constexpr Vector<N, T> reject(Vector<N, T> v, Basis<K, Vector<N, T>> b);
template<Dimension K, Dimension N, typename T> constexpr Matrix<N, K, T> matrix(Basis<K, Vector<N, T>> b);

// =============================
// Color math
// =============================

// Perceptual extraction
template<typename T> constexpr T hue(Color<T> c);
template<typename T> constexpr T saturation(Color<T> c);
template<typename T> constexpr T brightness(Color<T> c);
template<typename T> constexpr T lightness(Color<T> c);
template<typename T> constexpr T luminance(Color<T> c, Vector<3, T> weights = Luminance<T>::BT709);

// Gamma
template<typename T> constexpr Color<T> gamma(Color<T> c, T exp);
template<typename T, typename F> constexpr Color<T> gamma(Color<T> c, F fn);

// Modifiers
template<typename T> constexpr Color<T> invert(Color<T> c);
template<typename T> constexpr Color<T> grayscale(Color<T> c);
template<typename T> constexpr Color<T> tint(Color<T> a, Color<T> b);
template<typename T> constexpr Color<T> lerp(Color<T> a, Color<T> b, T t);
template<typename T> constexpr Color<T> blend(Color<T> src, Color<T> dst, BlendMode mode);

// =============================
// Collision
// =============================

/// Returns the per-axis signed separation vector between two shapes.
///
/// Each component of the result is:
///   positive  — shapes are separated along that axis (gap)
///   zero      — shapes are exactly touching along that axis
///   negative  — shapes are overlapping along that axis (penetration)
///
/// To resolve overlap, add the result to the first shape's position.
/// The result subsumes the minimum translation vector (MTV):
/// when any component is negative, the result IS the MTV.
template<Dimension N, typename T> constexpr Vector<N, T> separation(Ball<N, T> a, Ball<N, T> b);
template<Dimension N, typename T> constexpr Vector<N, T> separation(AABB<N, T> a, AABB<N, T> b);
template<Dimension N, typename T> constexpr Vector<N, T> separation(Ball<N, T> a, AABB<N, T> b);
template<Dimension N, typename T> constexpr Vector<N, T> separation(AABB<N, T> a, Ball<N, T> b);
template<Dimension N, typename T> constexpr Vector<N, T> separation(Box<N, T> a, Box<N, T> b);

/// Generic GJK+EPA separation for any convex shapes with ADL `support()`.
/// Per-pair overloads above are preferred when available.
template<typename S1, typename S2> constexpr Vector<S1::dimension, typename S1::scalar> separation(S1 a, S2 b);

/// Support function — farthest point of a convex shape in a given direction.
///
/// Used by GJK/EPA for generic convex-convex collision detection.
template<Dimension N, typename T> constexpr Vector<N, T> support(Ball<N, T> shape, Vector<N, T> dir);
template<Dimension N, typename T> constexpr Vector<N, T> support(AABB<N, T> shape, Vector<N, T> dir);
template<Dimension N, typename T> constexpr Vector<N, T> support(Box<N, T> shape, Vector<N, T> dir);
template<Dimension N, typename T> constexpr Vector<N, T> support(Triangle<N, T> shape, Vector<N, T> dir);
template<Dimension N, typename T, typename R> constexpr Vector<N, T> support(OBB<N, T, R> shape, Vector<N, T> dir);

} // namespace vcp::math



#endif // VCP_MATH_H
