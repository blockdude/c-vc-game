#ifndef VCP_MATH_H
#define VCP_MATH_H

#include <cmath>
#include <type_traits>
#include "vcp/traits.h"

namespace vcp::math
{

// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// 
//  _______   _____ ___ ___ 
// |_   _\ \ / / _ \ __/ __|
//   | |  \ V /|  _/ _|\__ \
//   |_|   |_| |_| |___|___/
// 
//   All types live below.
//   https://patorjk.com/software/taag/#p=display&f=Small&t=TYPES&x=none&v=4&h=4&w=80&we=false
// 
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================

// =============================
// Dimension
// =============================

using Dimension = int;

// =============================
// Constants
// =============================

template<typename T>
struct Constant
{
    static constexpr T EULER = T(2.71828182845904523536028747135266249);
    static constexpr T PI = T(3.14159265358979323846264338327950288);
    static constexpr T HALF_PI = PI / T(2);
    static constexpr T TAU = PI * T(2);
    static constexpr T EPSILON = T(0.0001);
};

// =============================
// Vector<N, T>
// =============================

template<Dimension N, typename T, typename A = std::allocator<T>>
struct Vector
{
    T data[N];

    using Scalar = T;
    static constexpr Dimension size = N;
    static constexpr Dimension dimension = N;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T, typename A>
struct Vector<1, T, A>
{
    union
    {
        T x;
        T u;
        T w;
        T r;
    };

    using Scalar = T;
    static constexpr Dimension size = 1;
    static constexpr Dimension dimension = 1;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T, typename A>
struct Vector<2, T, A>
{
    union
    {
        struct { T x, y; };
        struct { T u, v; };
        struct { T w, h; };
        struct { T r, g; };
    };

    using Scalar = T;
    static constexpr Dimension size = 2;
    static constexpr Dimension dimension = 2;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T, typename A>
struct Vector<3, T, A>
{
    union
    {
        struct { T x, y, z; };
        struct { T u, v, w; };
        struct { T r, g, b; };
    };

    using Scalar = T;
    static constexpr Dimension size = 3;
    static constexpr Dimension dimension = 3;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T, typename A>
struct Vector<4, T, A>
{
    union
    {
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
        struct { T s, t, p, q; };
    };

    using Scalar = T;
    static constexpr Dimension size = 4;
    static constexpr Dimension dimension = 4;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
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

template<Dimension N, Dimension M, typename T, typename A = std::allocator<T>>
struct Matrix
{
    T data[N * M];

    using Scalar = T;
    static constexpr Dimension rows = N;
    static constexpr Dimension cols = M;
    static constexpr Dimension size = N * M;
    constexpr T &operator()(Dimension r, Dimension c);
    constexpr const T &operator()(Dimension r, Dimension c) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// Basis<K, E>
// =============================

template<Dimension K, typename E, typename A = std::allocator<E>>
struct Basis
{
    E v[K];

    constexpr E &operator()(Dimension i);
    constexpr const E &operator()(Dimension i) const;
    constexpr E &operator[](Dimension i);
    constexpr const E &operator[](Dimension i) const;
};

// =============================
// Quaternion<T>
// =============================

template<typename T>
struct Quaternion
{
    T x, y, z, w;

    using Scalar = T;
    static constexpr Dimension size = 4;
    static constexpr Dimension dimension = 3;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// Rotor<N, T>
// =============================

template<Dimension N, typename T>
struct Rotor
{
    T data[N * (N - 1) / 2 + 1];

    using Scalar = T;
    static constexpr Dimension size = N * (N - 1) / 2 + 1;
    static constexpr Dimension dimension = N;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T>
struct Rotor<2, T>
{
    union
    {
        struct { T s, b; };
        struct { T a, b; };
        struct { T w, z; };
    };

    using Scalar = T;
    static constexpr Dimension size = 2;
    static constexpr Dimension dimension = 2;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T>
struct Rotor<3, T>
{
    union
    {
        struct { T s, xy, xz, yz; };
        struct { T a, b, c, d; };
        struct { T w, x, y, z; };
    };

    using Scalar = T;
    static constexpr Dimension size = 4;
    static constexpr Dimension dimension = 3;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// Motor<N, T>
// =============================

template<Dimension N, typename T>
struct Motor
{
    Rotor<N, T> real;
    Rotor<N, T> dual;

    using Scalar = T;
    static constexpr Dimension size = Rotor<N, T>::size * 2;
    static constexpr Dimension dimension = N;
    constexpr T &operator()(Dimension i);
    constexpr const T &operator()(Dimension i) const;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
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
// Line<N, T>
// =============================

template<Dimension N, typename T, typename A = std::allocator<T>>
struct Line
{
    Vector<N, T, A> a;
    Vector<N, T, A> b;

    using Scalar = T;
    static constexpr Dimension size = N * 2;
    static constexpr Dimension dimension = N;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// Triangle<N, T>
// =============================

template<Dimension N, typename T, typename A = std::allocator<T>>
struct Triangle
{
    Vector<N, T, A> a;
    Vector<N, T, A> b;
    Vector<N, T, A> c;

    using Scalar = T;
    static constexpr Dimension size = N * 3;
    static constexpr Dimension dimension = N;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// Ray<N, T>
// =============================

template<Dimension N, typename T, typename A = std::allocator<T>>
struct Ray
{
    Vector<N, T, A> origin;
    Vector<N, T, A> direction;

    using Scalar = T;
    static constexpr Dimension size = N * 2;
    static constexpr Dimension dimension = N;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// Hit<N, T>
// =============================

template<Dimension N, typename T, typename A = std::allocator<T>>
struct Hit
{
    T t;
    Vector<N, T, A> normal;

    using Scalar = T;
    static constexpr Dimension size = N + 1;
    static constexpr Dimension dimension = N;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;

    constexpr bool hit() const;
    constexpr Vector<N, T, A> point(Ray<N, T, A> ray) const;
};

// =============================
// Ball<N, T>
// =============================

template<Dimension N, typename T, typename A = std::allocator<T>>
struct Ball
{
    Vector<N, T, A> center;
    T r;

    using Scalar = T;
    static constexpr Dimension size = N + 1;
    static constexpr Dimension dimension = N;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T, typename A>
struct Ball<1, T, A>
{
    union
    {
        T x;
        Vector<1, T, A> center;
    };

    T r;

    using Scalar = T;
    static constexpr Dimension size = 2;
    static constexpr Dimension dimension = 1;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T, typename A>
struct Ball<2, T, A>
{
    union
    {
        struct
        {
            T x, y;
        };

        Vector<2, T, A> center;
    };

    T r;

    using Scalar = T;
    static constexpr Dimension size = 3;
    static constexpr Dimension dimension = 2;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T, typename A>
struct Ball<3, T, A>
{
    union
    {
        struct
        {
            T x, y, z;
        };

        Vector<3, T, A> center;
    };

    T r;

    using Scalar = T;
    static constexpr Dimension size = 4;
    static constexpr Dimension dimension = 3;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// Box<N, T>
// =============================

template<Dimension N, typename T, typename A = std::allocator<T>>
struct Box
{
    Vector<N, T, A> position;
    Vector<N, T, A> extent;

    using Scalar = T;
    static constexpr Dimension size = N * 2;
    static constexpr Dimension dimension = N;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T, typename A>
struct Box<1, T, A>
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
            Vector<1, T, A> position;
            Vector<1, T, A> extent;
        };
    };

    using Scalar = T;
    static constexpr Dimension size = 2;
    static constexpr Dimension dimension = 1;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T, typename A>
struct Box<2, T, A>
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
            Vector<2, T, A> position;
            Vector<2, T, A> extent;
        };
    };

    using Scalar = T;
    static constexpr Dimension size = 4;
    static constexpr Dimension dimension = 2;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

template<typename T, typename A>
struct Box<3, T, A>
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
            Vector<3, T, A> position;
            Vector<3, T, A> extent;
        };
    };

    using Scalar = T;
    static constexpr Dimension size = 6;
    static constexpr Dimension dimension = 3;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// AABB<N, T>
// =============================

template<Dimension N, typename T, typename A = std::allocator<T>>
struct AABB
{
    Vector<N, T, A> min;
    Vector<N, T, A> max;

    using Scalar = T;
    static constexpr Dimension size = N * 2;
    static constexpr Dimension dimension = N;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// OBB<N, T, R>
// =============================

template<Dimension N, typename T, typename A = std::allocator<T>, typename R = Matrix<N, N, T, A>>
struct OBB
{
    Vector<N, T, A> center;
    Vector<N, T, A> extent;
    R orientation;

    using Scalar = T;
    static constexpr Dimension size = N * 2 + R::size;
    static constexpr Dimension dimension = N;
    constexpr T &operator[](Dimension i);
    constexpr const T &operator[](Dimension i) const;
};

// =============================
// Color<T>
// =============================

template<typename T>
struct Color
{
    T r, g, b, a;

    using Scalar = T;
    static constexpr Dimension size = 4;
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
    static constexpr Vector<3, T> BT601 = { T(0.2990), T(0.5870), T(0.1140) };
    // BT.709 — HDTV, sRGB (the universal default)
    static constexpr Vector<3, T> BT709 = { T(0.2126), T(0.7152), T(0.0722) };
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
    template<typename T> static auto curve(T exp);
    // True sRGB encode (linear → sRGB)
    template<typename T> static auto encode_sRGB();
    // True sRGB decode (sRGB → linear)
    template<typename T> static auto decode_sRGB();
    // BT.1886 encode (linear → display)
    template<typename T> static auto encode_BT1886();
    // BT.1886 decode (display → linear)
    template<typename T> static auto decode_BT1886();
};

// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// 
//  ___ _  _ _____ ___ ___ ___ _   ___ ___ 
// |_ _| \| |_   _| __| _ \ __/_\ / __| __|
//  | || .` | | | | _||   / _/ _ \ (__| _| 
// |___|_|\_| |_| |___|_|_\_/_/ \_\___|___|
// 
//   All function protoypes/interface lives below.
//   https://patorjk.com/software/taag/#p=display&f=Small&t=INTERFACE&x=none&v=4&h=4&w=80&we=false
// 
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================

// =============================
// Scalar utilities
// =============================

template<typename T> constexpr T min(T a, T b);
template<typename T> constexpr T max(T a, T b);
template<typename T> constexpr T clamp(T v, T lo, T hi);
template<typename T> constexpr T sign(T v);
template<typename T> constexpr T abs(T v);
template<typename T> constexpr T lerp(T a, T b, T t);
template<typename T> constexpr T normalize(T v, T lo, T hi);
template<typename T> constexpr T radians(T degrees);
template<typename T> constexpr T degrees(T radians);
template<typename T> constexpr T saturate(T v);
template<typename T> constexpr T closest_offset(T from, T to, T period);
template<typename T> constexpr T smoothstep(T edge0, T edge1, T x);

template<typename T> constexpr T truncate(T x);
template<typename T> constexpr T floor(T x);
template<typename T> constexpr T ceil(T x);
template<typename T> constexpr T round(T x);

template<typename T> constexpr T truncated_modulo(T a, T b);
template<typename T> constexpr T modulo(T a, T b);

template<typename T> constexpr T sqrt(T x);
template<typename T> constexpr T sin(T x);
template<typename T> constexpr T cos(T x);
template<typename T> constexpr T tan(T x);
template<typename T> constexpr T atan(T x);
template<typename T> constexpr T atan2(T y, T x);
template<typename T> constexpr T asin(T x);
template<typename T> constexpr T acos(T x);

// =============================
// General
// =============================

template<typename V> constexpr V make();
template<typename V> constexpr V filled(typename V::Scalar value);
template<typename V> constexpr V one();
template<typename V> constexpr V zero();
template<typename V> constexpr V identity();
template<typename V> constexpr V diagonal(typename V::Scalar value);

// =============================
// Vector math
// =============================

template<Dimension N, typename T> constexpr Vector<N, T> make(const Vector<N, T> &pattern);
template<Dimension N, typename T> constexpr Vector<N, T> filled(const Vector<N, T> &pattern, T value);
template<Dimension N, typename T> constexpr Vector<N, T> one(const Vector<N, T> &pattern);
template<Dimension N, typename T> constexpr Vector<N, T> zero(const Vector<N, T> &pattern);
template<Dimension N, typename T> constexpr Vector<N, T> cardinal(Dimension i);
template<Dimension N, typename T> constexpr Vector<N, T> cardinal(const Vector<N, T> &pattern, Dimension i);
template<Dimension N, Dimension M, typename T> constexpr Vector<N, T> resize(Vector<M, T> v, T fill = T{});
template<typename T, Dimension N, Dimension... Ns> constexpr Vector<(N + ... + Ns), T> concat(Vector<N, T> a, Vector<Ns, T>... rest);
template<Dimension N, typename T, typename... Scalars> constexpr Vector<N + 1 + sizeof...(Scalars), T> concat(Vector<N, T> v, T s, Scalars... rest);
template<Dimension N, typename T> constexpr Vector<N + 1, T> concat(T s, Vector<N, T> v);
template<typename T, typename... Scalars> constexpr Vector<1 + sizeof...(Scalars), T> concat(T first, Scalars... rest);

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
template<Dimension N, typename T> constexpr bool equals(Vector<N, T> a, Vector<N, T> b, T epsilon = Constant<T>::EPSILON);
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
// Matrix
// =============================

template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> make(const Matrix<N, M, T> &pattern);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> filled(const Matrix<N, M, T> &pattern, T value);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> zero(const Matrix<N, M, T> &pattern);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> one(const Matrix<N, M, T> &pattern);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> identity(const Matrix<N, M, T> &pattern);
template<Dimension N, Dimension M, typename T> constexpr Matrix<N, M, T> diagonal(const Matrix<N, M, T> &pattern, T value);
template<Dimension N, Dimension R, Dimension C, typename T> constexpr Matrix<N, N, T> resize(Matrix<R, C, T> m, T fill = T{});
template<Dimension N, Dimension M, Dimension R, Dimension C, typename T> constexpr Matrix<N, M, T> resize(Matrix<R, C, T> m, T fill = T{});
template<Dimension RA, Dimension CA, Dimension RB, Dimension CB, typename T> constexpr Matrix<max(RA, RB), max(CA, CB), T> embed(Matrix<RA, CA, T> a, Matrix<RB, CB, T> b);

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
// Quaternion
// =============================

template<typename T> constexpr Quaternion<T> make(const Quaternion<T> &pattern);
template<typename T> constexpr Quaternion<T> filled(const Quaternion<T> &pattern, T value);
template<typename T> constexpr Quaternion<T> identity(const Quaternion<T> &pattern);

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
template<typename T> constexpr bool equals(Quaternion<T> a, Quaternion<T> b, T epsilon = Constant<T>::EPSILON);

// =============================
// Geometry
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
template<typename S1, typename S2> constexpr Vector<S1::dimension, typename S1::Scalar> separation(S1 a, S2 b);
template<Dimension N, typename T, typename S1, typename S2> constexpr Vector<N, T> separation(S1 a, S2 b);

/// Ray-shape intersection. Returns the first hit, or `t = -1` if no hit.
template<Dimension N, typename T> constexpr Hit<N, T> intersection(Ray<N, T> ray, Ball<N, T> shape);
template<Dimension N, typename T> constexpr Hit<N, T> intersection(Ray<N, T> ray, AABB<N, T> shape);
template<Dimension N, typename T> constexpr Hit<N, T> intersection(Ray<N, T> ray, Box<N, T> shape);
template<Dimension N, typename T> constexpr Hit<N, T> intersection(Ray<N, T> ray, Triangle<N, T> shape);
template<Dimension N, typename T, typename R> constexpr Hit<N, T> intersection(Ray<N, T> ray, OBB<N, T, R> shape);

/// Generic ray-shape intersection via GJK Ray Cast for any convex shape with ADL `support()`.
template<typename S, Dimension N, typename T> constexpr Hit<N, T> intersection(Ray<N, T> ray, S shape);

/// Support function — farthest point of a convex shape in a given direction.
///
/// Used by GJK/EPA for generic convex-convex collision detection.
template<Dimension N, typename T> constexpr Vector<N, T> support(Ball<N, T> shape, Vector<N, T> dir);
template<Dimension N, typename T> constexpr Vector<N, T> support(AABB<N, T> shape, Vector<N, T> dir);
template<Dimension N, typename T> constexpr Vector<N, T> support(Box<N, T> shape, Vector<N, T> dir);
template<Dimension N, typename T> constexpr Vector<N, T> support(Triangle<N, T> shape, Vector<N, T> dir);
template<Dimension N, typename T, typename R> constexpr Vector<N, T> support(OBB<N, T, R> shape, Vector<N, T> dir);

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

// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// 
//  ___ __  __ ___ _    ___ __  __ ___ _  _ _____ _ _____ ___ ___  _  _ 
// |_ _|  \/  | _ \ |  | __|  \/  | __| \| |_   _/_\_   _|_ _/ _ \| \| |
//  | || |\/| |  _/ |__| _|| |\/| | _|| .` | | |/ _ \| |  | | (_) | .` |
// |___|_|  |_|_| |____|___|_|  |_|___|_|\_| |_/_/ \_\_| |___\___/|_|\_|
// 
//   All function bodies live below.
//   https://patorjk.com/software/taag/#p=display&f=Small&t=IMPLEMENTATION&x=none&v=4&h=4&w=80&we=false
// 
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================

// =============================
// Vector<N, T>
// =============================

template<Dimension N, typename T, typename A>
constexpr T &Vector<N, T, A>::operator()(Dimension i)
{
    return this->data[i];
}

template<Dimension N, typename T, typename A>
constexpr const T &Vector<N, T, A>::operator()(Dimension i) const
{
    return this->data[i];
}

template<Dimension N, typename T, typename A>
constexpr T &Vector<N, T, A>::operator[](Dimension i)
{
    return this->data[i];
}

template<Dimension N, typename T, typename A>
constexpr const T &Vector<N, T, A>::operator[](Dimension i) const
{
    return this->data[i];
}

// =============================
// Vector<1, T>
// =============================

template<typename T, typename A>
constexpr T &Vector<1, T, A>::operator()(Dimension i)
{
    return this->x;
}

template<typename T, typename A>
constexpr const T &Vector<1, T, A>::operator()(Dimension i) const
{
    return this->x;
}

template<typename T, typename A>
constexpr T &Vector<1, T, A>::operator[](Dimension i)
{
    return this->x;
}

template<typename T, typename A>
constexpr const T &Vector<1, T, A>::operator[](Dimension i) const
{
    return this->x;
}

// =============================
// Vector<2, T>
// =============================

template<typename T, typename A>
constexpr T &Vector<2, T, A>::operator()(Dimension i)
{
    switch (i)
    {
    case 0: return this->x;
    case 1: return this->y;
    }
    return this->x;
}

template<typename T, typename A>
constexpr const T &Vector<2, T, A>::operator()(Dimension i) const
{
    switch (i)
    {
    case 0: return this->x;
    case 1: return this->y;
    }
    return this->x;
}

template<typename T, typename A>
constexpr T &Vector<2, T, A>::operator[](Dimension i)
{
    switch (i)
    {
    case 0: return this->x;
    case 1: return this->y;
    }
    return this->x;
}

template<typename T, typename A>
constexpr const T &Vector<2, T, A>::operator[](Dimension i) const
{
    switch (i)
    {
    case 0: return this->x;
    case 1: return this->y;
    }
    return this->x;
}

// =============================
// Vector<3, T>
// =============================

template<typename T, typename A>
constexpr T &Vector<3, T, A>::operator()(Dimension i)
{
    switch (i)
    {
    case 0: return this->x;
    case 1: return this->y;
    case 2: return this->z;
    }
    return this->x;
}

template<typename T, typename A>
constexpr const T &Vector<3, T, A>::operator()(Dimension i) const
{
    switch (i)
    {
    case 0: return this->x;
    case 1: return this->y;
    case 2: return this->z;
    }
    return this->x;
}

template<typename T, typename A>
constexpr T &Vector<3, T, A>::operator[](Dimension i)
{
    switch (i)
    {
    case 0: return this->x;
    case 1: return this->y;
    case 2: return this->z;
    }
    return this->x;
}

template<typename T, typename A>
constexpr const T &Vector<3, T, A>::operator[](Dimension i) const
{
    switch (i)
    {
    case 0: return this->x;
    case 1: return this->y;
    case 2: return this->z;
    }
    return this->x;
}

// =============================
// Vector<4, T>
// =============================

template<typename T, typename A>
constexpr T &Vector<4, T, A>::operator()(Dimension i)
{
    switch (i)
    {
    case 0: return this->x;
    case 1: return this->y;
    case 2: return this->z;
    case 3: return this->w;
    }
    return this->x;
}

template<typename T, typename A>
constexpr const T &Vector<4, T, A>::operator()(Dimension i) const
{
    switch (i)
    {
    case 0: return this->x;
    case 1: return this->y;
    case 2: return this->z;
    case 3: return this->w;
    }
    return this->x;
}

template<typename T, typename A>
constexpr T &Vector<4, T, A>::operator[](Dimension i)
{
    switch (i)
    {
    case 0: return this->x;
    case 1: return this->y;
    case 2: return this->z;
    case 3: return this->w;
    }
    return this->x;
}

template<typename T, typename A>
constexpr const T &Vector<4, T, A>::operator[](Dimension i) const
{
    switch (i)
    {
    case 0: return this->x;
    case 1: return this->y;
    case 2: return this->z;
    case 3: return this->w;
    }
    return this->x;
}

// =============================
// Matrix<N, M, T>
// =============================

template<Dimension N, Dimension M, typename T, typename A>
constexpr T &Matrix<N, M, T, A>::operator()(Dimension r, Dimension c)
{
    return this->data[r + c * N];
}

template<Dimension N, Dimension M, typename T, typename A>
constexpr const T &Matrix<N, M, T, A>::operator()(Dimension r, Dimension c) const
{
    return this->data[r + c * N];
}

template<Dimension N, Dimension M, typename T, typename A>
constexpr T &Matrix<N, M, T, A>::operator[](Dimension i)
{
    return this->data[i];
}

template<Dimension N, Dimension M, typename T, typename A>
constexpr const T &Matrix<N, M, T, A>::operator[](Dimension i) const
{
    return this->data[i];
}

// =============================
// Basis<K, E>
// =============================

template<Dimension K, typename E, typename A>
constexpr E &Basis<K, E, A>::operator()(Dimension i)
{
    return this->v[i];
}

template<Dimension K, typename E, typename A>
constexpr const E &Basis<K, E, A>::operator()(Dimension i) const
{
    return this->v[i];
}

template<Dimension K, typename E, typename A>
constexpr E &Basis<K, E, A>::operator[](Dimension i)
{
    return this->v[i];
}

template<Dimension K, typename E, typename A>
constexpr const E &Basis<K, E, A>::operator[](Dimension i) const
{
    return this->v[i];
}

// =============================
// Quaternion<T>
// =============================

template<typename T>
constexpr T &Quaternion<T>::operator()(Dimension i)
{
    switch (i)
    {
    case 0: return this->x;
    case 1: return this->y;
    case 2: return this->z;
    case 3: return this->w;
    }
    return this->x;
}

template<typename T>
constexpr const T &Quaternion<T>::operator()(Dimension i) const
{
    switch (i)
    {
    case 0: return this->x;
    case 1: return this->y;
    case 2: return this->z;
    case 3: return this->w;
    }
    return this->x;
}

template<typename T>
constexpr T &Quaternion<T>::operator[](Dimension i)
{
    switch (i)
    {
    case 0: return this->x;
    case 1: return this->y;
    case 2: return this->z;
    case 3: return this->w;
    }
    return this->x;
}

template<typename T>
constexpr const T &Quaternion<T>::operator[](Dimension i) const
{
    switch (i)
    {
    case 0: return this->x;
    case 1: return this->y;
    case 2: return this->z;
    case 3: return this->w;
    }
    return this->x;
}

// =============================
// Rotor<N, T>
// =============================

template<Dimension N, typename T>
constexpr T &Rotor<N, T>::operator()(Dimension i)
{
    return this->data[i];
}

template<Dimension N, typename T>
constexpr const T &Rotor<N, T>::operator()(Dimension i) const
{
    return this->data[i];
}

template<Dimension N, typename T>
constexpr T &Rotor<N, T>::operator[](Dimension i)
{
    return this->data[i];
}

template<Dimension N, typename T>
constexpr const T &Rotor<N, T>::operator[](Dimension i) const
{
    return this->data[i];
}

// =============================
// Rotor<2, T>
// =============================

template<typename T>
constexpr T &Rotor<2, T>::operator()(Dimension i)
{
    switch (i)
    {
    case 0: return this->s;
    case 1: return this->b;
    }
    return this->s;
}

template<typename T>
constexpr const T &Rotor<2, T>::operator()(Dimension i) const
{
    switch (i)
    {
    case 0: return this->s;
    case 1: return this->b;
    }
    return this->s;
}

template<typename T>
constexpr T &Rotor<2, T>::operator[](Dimension i)
{
    switch (i)
    {
    case 0: return this->s;
    case 1: return this->b;
    }
    return this->s;
}

template<typename T>
constexpr const T &Rotor<2, T>::operator[](Dimension i) const
{
    switch (i)
    {
    case 0: return this->s;
    case 1: return this->b;
    }
    return this->s;
}

// =============================
// Rotor<3, T>
// =============================

template<typename T>
constexpr T &Rotor<3, T>::operator()(Dimension i)
{
    switch (i)
    {
    case 0: return this->s;
    case 1: return this->xy;
    case 2: return this->xz;
    case 3: return this->yz;
    }
    return this->s;
}

template<typename T>
constexpr const T &Rotor<3, T>::operator()(Dimension i) const
{
    switch (i)
    {
    case 0: return this->s;
    case 1: return this->xy;
    case 2: return this->xz;
    case 3: return this->yz;
    }
    return this->s;
}

template<typename T>
constexpr T &Rotor<3, T>::operator[](Dimension i)
{
    switch (i)
    {
    case 0: return this->s;
    case 1: return this->xy;
    case 2: return this->xz;
    case 3: return this->yz;
    }
    return this->s;
}

template<typename T>
constexpr const T &Rotor<3, T>::operator[](Dimension i) const
{
    switch (i)
    {
    case 0: return this->s;
    case 1: return this->xy;
    case 2: return this->xz;
    case 3: return this->yz;
    }
    return this->s;
}

// =============================
// Motor<N, T>
// =============================

template<Dimension N, typename T>
constexpr T &Motor<N, T>::operator()(Dimension i)
{
    if (i < Rotor<N, T>::size)
        return this->real(i);
    return this->dual(i - Rotor<N, T>::size);
}

template<Dimension N, typename T>
constexpr const T &Motor<N, T>::operator()(Dimension i) const
{
    if (i < Rotor<N, T>::size)
        return this->real(i);
    return this->dual(i - Rotor<N, T>::size);
}

template<Dimension N, typename T>
constexpr T &Motor<N, T>::operator[](Dimension i)
{
    if (i < Rotor<N, T>::size)
        return this->real[i];
    return this->dual[i - Rotor<N, T>::size];
}

template<Dimension N, typename T>
constexpr const T &Motor<N, T>::operator[](Dimension i) const
{
    if (i < Rotor<N, T>::size)
        return this->real[i];
    return this->dual[i - Rotor<N, T>::size];
}

// =============================
// Cardinal<N, T>
// =============================

template<Dimension N, typename T>
constexpr Vector<N, T> Cardinal<N, T>::get(Dimension i)
{
    Vector<N, T> v{};
    v(i) = T(1);
    return v;
}

template<typename T>
constexpr Vector<1, T> Cardinal<1, T>::get(Dimension i)
{
    switch (i)
    {
    case 0: return Cardinal::X;
    }
    return {};
}

template<typename T>
constexpr Vector<2, T> Cardinal<2, T>::get(Dimension i)
{
    switch (i)
    {
    case 0: return Cardinal::X;
    case 1: return Cardinal::Y;
    }
    return {};
}

template<typename T>
constexpr Vector<3, T> Cardinal<3, T>::get(Dimension i)
{
    switch (i)
    {
    case 0: return Cardinal::X;
    case 1: return Cardinal::Y;
    case 2: return Cardinal::Z;
    }
    return {};
}

template<typename T>
constexpr Vector<4, T> Cardinal<4, T>::get(Dimension i)
{
    switch (i)
    {
    case 0: return Cardinal::X;
    case 1: return Cardinal::Y;
    case 2: return Cardinal::Z;
    case 3: return Cardinal::W;
    }
    return {};
}

// =============================
// Line<N, T>
// =============================

template<Dimension N, typename T, typename A>
constexpr T &Line<N, T, A>::operator[](Dimension i)
{
    if (i < N) return this->a[i];
    return this->b[i - N];
}

template<Dimension N, typename T, typename A>
constexpr const T &Line<N, T, A>::operator[](Dimension i) const
{
    if (i < N) return this->a[i];
    return this->b[i - N];
}

// =============================
// Triangle<N, T>
// =============================

template<Dimension N, typename T, typename A>
constexpr T &Triangle<N, T, A>::operator[](Dimension i)
{
    if (i < N) return this->a[i];
    if (i < N * 2) return this->b[i - N];
    return this->c[i - N * 2];
}

template<Dimension N, typename T, typename A>
constexpr const T &Triangle<N, T, A>::operator[](Dimension i) const
{
    if (i < N) return this->a[i];
    if (i < N * 2) return this->b[i - N];
    return this->c[i - N * 2];
}

// =============================
// Ray<N, T>
// =============================

template<Dimension N, typename T, typename A>
constexpr T &Ray<N, T, A>::operator[](Dimension i)
{
    if (i < N) return this->origin[i];
    return this->direction[i - N];
}

template<Dimension N, typename T, typename A>
constexpr const T &Ray<N, T, A>::operator[](Dimension i) const
{
    if (i < N) return this->origin[i];
    return this->direction[i - N];
}

// =============================
// Hit<N, T>
// =============================

template<Dimension N, typename T, typename A>
constexpr T &Hit<N, T, A>::operator[](Dimension i)
{
    if (i == 0) return this->t;
    return this->normal[i - 1];
}

template<Dimension N, typename T, typename A>
constexpr const T &Hit<N, T, A>::operator[](Dimension i) const
{
    if (i == 0) return this->t;
    return this->normal[i - 1];
}

template<Dimension N, typename T, typename A>
constexpr bool Hit<N, T, A>::hit() const
{
    return this->t >= T(0);
}

template<Dimension N, typename T, typename A>
constexpr Vector<N, T, A> Hit<N, T, A>::point(Ray<N, T, A> ray) const
{
    return ray.origin + ray.direction * this->t;
}

// =============================
// Ball<N, T>
// =============================

template<Dimension N, typename T, typename A>
constexpr T &Ball<N, T, A>::operator[](Dimension i)
{
    if (i < N) return this->center[i];
    return this->r;
}

template<Dimension N, typename T, typename A>
constexpr const T &Ball<N, T, A>::operator[](Dimension i) const
{
    if (i < N) return this->center[i];
    return this->r;
}

template<typename T, typename A>
constexpr T &Ball<1, T, A>::operator[](Dimension i)
{
    if (i < 1) return this->center[i];
    return this->r;
}

template<typename T, typename A>
constexpr const T &Ball<1, T, A>::operator[](Dimension i) const
{
    if (i < 1) return this->center[i];
    return this->r;
}

template<typename T, typename A>
constexpr T &Ball<2, T, A>::operator[](Dimension i)
{
    if (i < 2) return this->center[i];
    return this->r;
}

template<typename T, typename A>
constexpr const T &Ball<2, T, A>::operator[](Dimension i) const
{
    if (i < 2) return this->center[i];
    return this->r;
}

template<typename T, typename A>
constexpr T &Ball<3, T, A>::operator[](Dimension i)
{
    if (i < 3) return this->center[i];
    return this->r;
}

template<typename T, typename A>
constexpr const T &Ball<3, T, A>::operator[](Dimension i) const
{
    if (i < 3) return this->center[i];
    return this->r;
}

// =============================
// Box<N, T>
// =============================

template<Dimension N, typename T, typename A>
constexpr T &Box<N, T, A>::operator[](Dimension i)
{
    if (i < N) return this->position[i];
    return this->extent[i - N];
}

template<Dimension N, typename T, typename A>
constexpr const T &Box<N, T, A>::operator[](Dimension i) const
{
    if (i < N) return this->position[i];
    return this->extent[i - N];
}

template<typename T, typename A>
constexpr T &Box<1, T, A>::operator[](Dimension i)
{
    if (i < 1) return this->position[i];
    return this->extent[i - 1];
}

template<typename T, typename A>
constexpr const T &Box<1, T, A>::operator[](Dimension i) const
{
    if (i < 1) return this->position[i];
    return this->extent[i - 1];
}

template<typename T, typename A>
constexpr T &Box<2, T, A>::operator[](Dimension i)
{
    if (i < 2) return this->position[i];
    return this->extent[i - 2];
}

template<typename T, typename A>
constexpr const T &Box<2, T, A>::operator[](Dimension i) const
{
    if (i < 2) return this->position[i];
    return this->extent[i - 2];
}

template<typename T, typename A>
constexpr T &Box<3, T, A>::operator[](Dimension i)
{
    if (i < 3) return this->position[i];
    return this->extent[i - 3];
}

template<typename T, typename A>
constexpr const T &Box<3, T, A>::operator[](Dimension i) const
{
    if (i < 3) return this->position[i];
    return this->extent[i - 3];
}

// =============================
// AABB<N, T>
// =============================

template<Dimension N, typename T, typename A>
constexpr T &AABB<N, T, A>::operator[](Dimension i)
{
    if (i < N) return this->min[i];
    return this->max[i - N];
}

template<Dimension N, typename T, typename A>
constexpr const T &AABB<N, T, A>::operator[](Dimension i) const
{
    if (i < N) return this->min[i];
    return this->max[i - N];
}

// =============================
// OBB<N, T, R>
// =============================

template<Dimension N, typename T, typename A, typename R>
constexpr T &OBB<N, T, A, R>::operator[](Dimension i)
{
    if (i < N) return this->center[i];
    if (i < N * 2) return this->extent[i - N];
    return this->orientation[i - N * 2];
}

template<Dimension N, typename T, typename A, typename R>
constexpr const T &OBB<N, T, A, R>::operator[](Dimension i) const
{
    if (i < N) return this->center[i];
    if (i < N * 2) return this->extent[i - N];
    return this->orientation[i - N * 2];
}

// =============================
// Color<T>
// =============================

template<typename T>
constexpr T &Color<T>::operator()(Dimension i)
{
    switch (i)
    {
    case 0: return this->r;
    case 1: return this->g;
    case 2: return this->b;
    case 3: return this->a;
    }
    return this->r;
}

template<typename T>
constexpr const T &Color<T>::operator()(Dimension i) const
{
    switch (i)
    {
    case 0: return this->r;
    case 1: return this->g;
    case 2: return this->b;
    case 3: return this->a;
    }
    return this->r;
}

template<typename T>
constexpr T &Color<T>::operator[](Dimension i)
{
    switch (i)
    {
    case 0: return this->r;
    case 1: return this->g;
    case 2: return this->b;
    case 3: return this->a;
    }
    return this->r;
}

template<typename T>
constexpr const T &Color<T>::operator[](Dimension i) const
{
    switch (i)
    {
    case 0: return this->r;
    case 1: return this->g;
    case 2: return this->b;
    case 3: return this->a;
    }
    return this->r;
}

// =============================
// Gamma
// =============================

template<typename T>
auto Gamma::curve(T exp)
{
    return [exp](T x) { return std::pow(x, exp); };
}

template<typename T>
auto Gamma::encode_sRGB()
{
    return [](T x) -> T
    {
        return x <= T(0.0031308) ? x * T(12.92)
            : T(1.055) * std::pow(x, T(1.0) / T(2.4)) - T(0.055);
    };
}

template<typename T>
auto Gamma::decode_sRGB()
{
    return [](T x) -> T
    {
        return x <= T(0.04045) ? x / T(12.92)
            : std::pow((x + T(0.055)) / T(1.055), T(2.4));
    };
}

template<typename T>
auto Gamma::encode_BT1886()
{
    return [](T x) { return std::pow(x, T(1.0) / T(2.4)); };
}

template<typename T>
auto Gamma::decode_BT1886()
{
    return [](T x) { return std::pow(x, T(2.4)); };
}

// =============================
// Scalar utilities
// =============================

template<typename T>
constexpr T min(T a, T b)
{
    return a < b ? a : b;
}

template<typename T>
constexpr T max(T a, T b)
{
    return a < b ? b : a;
}

template<typename T>
constexpr T clamp(T v, T lo, T hi)
{
    return v < lo ? lo : hi < v ? hi : v;
}

template<typename T>
constexpr T sign(T v)
{
    return v > T(0) ? T(1) : v < T(0) ? T(-1) : T(0);
}

template<typename T>
constexpr T abs(T v)
{
    return v == T(0) ? T(0) : v < T(0) ? -v : v;
}

template<typename T>
constexpr T lerp(T a, T b, T t)
{
    return a + (b - a) * t;
}

template<typename T>
constexpr T normalize(T v, T lo, T hi)
{
    return (v - lo) / (hi - lo);
}

template<typename T>
constexpr T radians(T degrees)
{
    return degrees * Constant<T>::PI / T(180);
}

template<typename T>
constexpr T degrees(T radians)
{
    return radians * T(180) / Constant<T>::PI;
}

template<typename T>
constexpr T saturate(T v)
{
    return v < T(0) ? T(0) : v > T(1) ? T(1) : v;
}

template<typename T>
constexpr T closest_offset(T from, T to, T period)
{
    T h = period / T(2);
    T r = modulo(to - from, period);
    return r > h ? r - period : r;
}

template<typename T>
constexpr T smoothstep(T edge0, T edge1, T x)
{
    T t = saturate((x - edge0) / (edge1 - edge0));
    return t * t * (T(3) - T(2) * t);
}

template<typename T>
constexpr T truncate(T x)
{
    constexpr auto fallback = [](T v) -> T
    {
        if (v >= T(0))
        {
            T r = T(0);
            T p = T(1);
            while (p * T(2) <= v) p = p * T(2);
            while (p >= T(1))
            {
                if (r + p <= v) r = r + p;
                p = p / T(2);
            }
            return r;
        }
        else
        {
            T n = T(0);
            T p = T(1);
            while (p * T(2) <= -v) p = p * T(2);
            while (p >= T(1))
            {
                if (n - p >= v) n = n - p;
                p = p / T(2);
            }
            return n;
        }
    };

    if constexpr (std::is_integral_v<T>)
    {
        return x;
    }
    else if constexpr (requires { std::trunc(x); })
    {
        if consteval
        {
            if constexpr (vcp::is_constexpr([] { return std::trunc(T(1)); }))
            {
                return std::trunc(x);
            }
            else
            {
                if (x != x) return x;
                if (x == T(1) / T(0)) return x;
                if (x == -T(1) / T(0)) return x;
                return fallback(x);
            }
        }
        else
        {
            return std::trunc(x);
        }
    }
    else
    {
        return fallback(x);
    }
}

template<typename T>
constexpr T floor(T x)
{
    if constexpr (std::is_integral_v<T>)
    {
        return x;
    }
    else if constexpr (requires { std::floor(x); })
    {
        if consteval
        {
            if constexpr (vcp::is_constexpr([] { return std::floor(T(1)); }))
            {
                return std::floor(x);
            }
            else
            {
                if (x != x) return x;
                if (x == T(1) / T(0)) return x;
                if (x == -T(1) / T(0)) return x;
                T t = truncate(x);
                return t > x ? t - T(1) : t;
            }
        }
        else
        {
            return std::floor(x);
        }
    }
    else
    {
        T t = truncate(x);
        return t > x ? t - T(1) : t;
    }
}

template<typename T>
constexpr T ceil(T x)
{
    if constexpr (std::is_integral_v<T>)
    {
        return x;
    }
    else if constexpr (requires { std::ceil(x); })
    {
        if consteval
        {
            if constexpr (vcp::is_constexpr([] { return std::ceil(T(1)); }))
            {
                return std::ceil(x);
            }
            else
            {
                if (x != x) return x;
                if (x == T(1) / T(0)) return x;
                if (x == -T(1) / T(0)) return x;
                T t = truncate(x);
                return t < x ? t + T(1) : t;
            }
        }
        else
        {
            return std::ceil(x);
        }
    }
    else
    {
        T t = truncate(x);
        return t < x ? t + T(1) : t;
    }
}

template<typename T>
constexpr T round(T x)
{
    if constexpr (std::is_integral_v<T>)
    {
        return x;
    }
    else if constexpr (requires { std::round(x); })
    {
        if consteval
        {
            if constexpr (vcp::is_constexpr([] { return std::round(T(1)); }))
            {
                return std::round(x);
            }
            else
            {
                if (x != x) return x;
                if (x == T(1) / T(0)) return x;
                if (x == -T(1) / T(0)) return x;
                T t = truncate(x);
                if (x > T(0)) return x - t >= T(0.5) ? t + T(1) : t;
                return t - x >= T(0.5) ? t - T(1) : t;
            }
        }
        else
        {
            return std::round(x);
        }
    }
    else
    {
        T t = truncate(x);
        if (x > T(0)) return x - t >= T(0.5) ? t + T(1) : t;
        return t - x >= T(0.5) ? t - T(1) : t;
    }
}

template<typename T>
constexpr T truncated_modulo(T a, T b)
{
    if constexpr (std::is_integral_v<T>)
    {
        return a % b;
    }
    else if constexpr (requires { std::fmod(a, b); })
    {
        if consteval
        {
            if constexpr (vcp::is_constexpr([] { return std::fmod(T(1), T(2)); }))
            {
                return std::fmod(a, b);
            }
            else
            {
                return a - truncate(a / b) * b;
            }
        }
        else
        {
            return std::fmod(a, b);
        }
    }
    else
    {
        return a - truncate(a / b) * b;
    }
}

template<typename T>
constexpr T modulo(T a, T b)
{
    T r = truncated_modulo(a, b);
    return r < T(0) ? r + b : r;
}

// =============================
// Transcendental
// =============================

template<typename T>
constexpr T sqrt(T x)
{
    constexpr auto fallback = [](T x) -> T
    {
        T guess = x;
        for (int i = 0; i < 64; i++)
        {
            T next = (guess + x / guess) / T(2);
            if (next == guess) break;
            guess = next;
        }
        return guess;
    };

    if constexpr (std::is_integral_v<T>)
    {
        if consteval
        {
            if (x <= T(0)) return T(0);
            return fallback(x);
        }
        else
        {
            return static_cast<T>(std::sqrt(static_cast<double>(x)));
        }
    }
    else if constexpr (requires { std::sqrt(x); })
    {
        if consteval
        {
            if constexpr (vcp::is_constexpr([] { return std::sqrt(T(1)); }))
            {
                return std::sqrt(x);
            }
            else
            {
                if (x != x) return x;
                if (x == T(1) / T(0)) return x;
                if (x < T(0) || x == -T(1) / T(0)) return T(0) / T(0);
                if (x == T(0)) return T(0);
                return fallback(x);
            }
        }
        else
        {
            return std::sqrt(x);
        }
    }
    else
    {
        if (x <= T(0)) return T(0);
        return fallback(x);
    }
}

template<typename T>
constexpr T sin(T x)
{
    constexpr auto sin_poly = [](T r) -> T
    {
        T r2 = r * r;
        return r * (T(1)
            + r2 * (T(-1) / T(6)
            + r2 * (T(1) / T(120)
            + r2 * (T(-1) / T(5040)
            + r2 * (T(1) / T(362880)
            + r2 * (T(-1) / T(39916800)
            + r2 * (T(1) / T(6227020800))))))));
    };

    constexpr auto cos_poly = [](T r) -> T
    {
        T r2 = r * r;
        return T(1)
            + r2 * (T(-1) / T(2)
            + r2 * (T(1) / T(24)
            + r2 * (T(-1) / T(720)
            + r2 * (T(1) / T(40320)
            + r2 * (T(-1) / T(3628800)
            + r2 * (T(1) / T(479001600)))))));
    };

    constexpr auto fallback = [](T x) -> T
    {
        constexpr T PI = Constant<T>::PI;
        constexpr T HALF_PI = Constant<T>::HALF_PI;
        constexpr T TWO_PI = Constant<T>::TAU;

        x = modulo(x + PI, TWO_PI) - PI;

        T q = round(x / HALF_PI);
        T r = x - q * HALF_PI;

        T qi = modulo(truncate(q), T(4));

        if (qi == T(0)) return  sin_poly(r);
        if (qi == T(1)) return  cos_poly(r);
        if (qi == T(2)) return -sin_poly(r);
        return -cos_poly(r);
    };

    if constexpr (std::is_integral_v<T>)
    {
        if consteval
        {
            if constexpr (vcp::is_constexpr([] { return std::sin(double(1)); }))
            {
                return static_cast<T>(round(std::sin(static_cast<double>(x))));
            }
            else
            {
                return static_cast<T>(round(fallback(static_cast<double>(x))));
            }
        }
        else
        {
            return static_cast<T>(std::round(std::sin(static_cast<double>(x))));
        }
    }
    else if constexpr (requires { std::sin(x); })
    {
        if consteval
        {
            if constexpr (vcp::is_constexpr([] { return std::sin(T(1)); }))
            {
                return std::sin(x);
            }
            else
            {
                return fallback(x);
            }
        }
        else
        {
            return std::sin(x);
        }
    }
    else
    {
        return fallback(x);
    }
}

template<typename T>
constexpr T cos(T x)
{
    constexpr auto sin_poly = [](T r) -> T
    {
        T r2 = r * r;
        return r * (T(1)
            + r2 * (T(-1) / T(6)
            + r2 * (T(1) / T(120)
            + r2 * (T(-1) / T(5040)
            + r2 * (T(1) / T(362880)
            + r2 * (T(-1) / T(39916800)
            + r2 * (T(1) / T(6227020800))))))));
    };

    constexpr auto cos_poly = [](T r) -> T
    {
        T r2 = r * r;
        return T(1)
            + r2 * (T(-1) / T(2)
            + r2 * (T(1) / T(24)
            + r2 * (T(-1) / T(720)
            + r2 * (T(1) / T(40320)
            + r2 * (T(-1) / T(3628800)
            + r2 * (T(1) / T(479001600)))))));
    };

    constexpr auto fallback = [](T x) -> T
    {
        constexpr T PI = Constant<T>::PI;
        constexpr T HALF_PI = Constant<T>::HALF_PI;
        constexpr T TWO_PI = Constant<T>::TAU;

        x = modulo(x + PI, TWO_PI) - PI;

        T q = round(x / HALF_PI);
        T r = x - q * HALF_PI;

        T qi = modulo(truncate(q), T(4));

        if (qi == T(0)) return  cos_poly(r);
        if (qi == T(1)) return -sin_poly(r);
        if (qi == T(2)) return -cos_poly(r);
        return  sin_poly(r);
    };

    if constexpr (std::is_integral_v<T>)
    {
        if consteval
        {
            if constexpr (vcp::is_constexpr([] { return std::cos(double(1)); }))
            {
                return static_cast<T>(round(std::cos(static_cast<double>(x))));
            }
            else
            {
                return static_cast<T>(round(fallback(static_cast<double>(x))));
            }
        }
        else
        {
            return static_cast<T>(std::round(std::cos(static_cast<double>(x))));
        }
    }
    else if constexpr (requires { std::cos(x); })
    {
        if consteval
        {
            if constexpr (vcp::is_constexpr([] { return std::cos(T(1)); }))
            {
                return std::cos(x);
            }
            else
            {
                return fallback(x);
            }
        }
        else
        {
            return std::cos(x);
        }
    }
    else
    {
        return fallback(x);
    }
}

template<typename T>
constexpr T tan(T x)
{
    constexpr auto fallback = [](T x) -> T
    {
        constexpr T PI = Constant<T>::PI;
        constexpr T HALF_PI = Constant<T>::HALF_PI;
        constexpr T TWO_PI = Constant<T>::TAU;

        x = modulo(x + PI, TWO_PI) - PI;

        T q = round(x / HALF_PI);
        T r = x - q * HALF_PI;

        T qi = modulo(truncate(q), T(4));

        T s = sin(r);
        T c = cos(r);

        if (qi == T(1) || qi == T(3))
        {
            if (s == T(0)) return T(1) / T(0);
            return -c / s;
        }

        return s / c;
    };

    if constexpr (std::is_integral_v<T>)
    {
        if consteval
        {
            if constexpr (vcp::is_constexpr([] { return std::tan(double(1)); }))
            {
                return static_cast<T>(round(std::tan(static_cast<double>(x))));
            }
            else
            {
                return static_cast<T>(round(fallback(static_cast<double>(x))));
            }
        }
        else
        {
            return static_cast<T>(std::round(std::tan(static_cast<double>(x))));
        }
    }
    else if constexpr (requires { std::tan(x); })
    {
        if consteval
        {
            if constexpr (vcp::is_constexpr([] { return std::tan(T(1)); }))
            {
                return std::tan(x);
            }
            else
            {
                return fallback(x);
            }
        }
        else
        {
            return std::tan(x);
        }
    }
    else
    {
        return fallback(x);
    }
}

} // namespace vcp::math

#endif // VCP_MATH_H