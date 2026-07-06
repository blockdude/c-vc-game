#ifndef VCP_MATH_H
#define VCP_MATH_H

namespace vcp::math
{

using dimension = int;

// =============================
// Vector<N, T>
// =============================

template<dimension N, typename T>
struct Vector
{
    T data[N];

    constexpr T& operator()(dimension i);
    constexpr const T& operator()(dimension i) const;
    constexpr T& operator[](dimension i);
    constexpr const T& operator[](dimension i) const;
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

    constexpr T& operator()(dimension i);
    constexpr const T& operator()(dimension i) const;
    constexpr T& operator[](dimension i);
    constexpr const T& operator[](dimension i) const;
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

    constexpr T& operator()(dimension i);
    constexpr const T& operator()(dimension i) const;
    constexpr T& operator[](dimension i);
    constexpr const T& operator[](dimension i) const;
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

    constexpr T& operator()(dimension i);
    constexpr const T& operator()(dimension i) const;
    constexpr T& operator[](dimension i);
    constexpr const T& operator[](dimension i) const;
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

    constexpr T& operator()(dimension i);
    constexpr const T& operator()(dimension i) const;
    constexpr T& operator[](dimension i);
    constexpr const T& operator[](dimension i) const;
};

// =============================
// Quaternion<T>
// =============================

template<typename T>
struct Quaternion
{
    T x, y, z, w;

    constexpr T& operator()(dimension i);
    constexpr const T& operator()(dimension i) const;
    constexpr T& operator[](dimension i);
    constexpr const T& operator[](dimension i) const;
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

template<dimension N, dimension M, typename T>
struct Matrix
{
    T data[N * M];

    constexpr T& operator()(dimension r, dimension c);
    constexpr const T& operator()(dimension r, dimension c) const;
    constexpr T &operator[](dimension i);
    constexpr const T &operator[](dimension i) const;
};

// =============================
// Geometry primitives (dimension-agnostic)
// =============================

// =============================
// Line<N, T>
// =============================

template<dimension N, typename T>
struct Line
{
    Vector<N, T> a;
    Vector<N, T> b;
};

// =============================
// Triangle<N, T>
// =============================

template<dimension N, typename T>
struct Triangle
{
    Vector<N, T> a;
    Vector<N, T> b;
    Vector<N, T> c;
};

// =============================
// Ray<N, T>
// =============================

template<dimension N, typename T>
struct Ray
{
    Vector<N, T> origin;
    Vector<N, T> direction;
};

// =============================
// Ball<N, T>
// =============================

template<dimension N, typename T>
struct Ball
{
    Vector<N, T> center;
    T r;
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
};

// =============================
// Box<N, T>
// =============================

template<dimension N, typename T>
struct Box
{
    Vector<N, T> position;
    Vector<N, T> size;
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
};

// =============================
// Color<T>
// =============================

template<typename T>
struct Color
{
    T r, g, b, a;
};

// =============================
// AABB<N, T>
// =============================

template<dimension N, typename T>
struct AABB
{
    Vector<N, T> min;
    Vector<N, T> max;
};

// =============================
// OBB<N, T, R>
// =============================

template<dimension N, typename T, typename R = Matrix<N, N, T>>
struct OBB
{
    Vector<N, T> center;
    Vector<N, T> extent;
    R orientation;
};

} // namespace vcp::math

#endif // VCP_MATH_H
