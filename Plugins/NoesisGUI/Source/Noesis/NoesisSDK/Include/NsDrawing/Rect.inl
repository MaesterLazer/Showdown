////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Error.h>
#include <NsCore/Math.h>
#include <NsDrawing/Size.h>
#include <NsDrawing/Point.h>
#include <NsMath/AABBox.h>


namespace Noesis
{

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Rect::Rect(float left, float top, float right, float bottom): x(left), y(top),
    width(right - left), height(bottom - top)
{
    NS_ASSERT(left <= right);
    NS_ASSERT(top <= bottom);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Rect::Rect(const Size& size): x(0.0f), y(0.0f), width(size.width), height(size.height)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Rect::Rect(const Point& location, const Size& size): x(location.x), y(location.y),
    width(size.width), height(size.height)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Rect::Rect(const Recti& rect): x(float(rect.x)), y(float(rect.y)), width(float(rect.width)),
    height(float(rect.height))
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool Rect::operator==(const Rect& rect) const
{
    return x == rect.x && y == rect.y && width == rect.width && height == rect.height;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool Rect::operator!=(const Rect& rect) const
{
    return !(*this == rect);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Point Rect::GetLocation() const
{
    return Point(x, y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Rect::SetLocation(const Point& location)
{
    x = location.x;
    y = location.y;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Size Rect::GetSize() const
{
    return Size(width, height);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Rect::SetSize(const Size& size)
{
    width = size.width;
    height = size.height;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline float Rect::GetLeft() const
{
    return x;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline float Rect::GetRight() const
{
    return IsInfinity(width) ? FLT_INF : x + width;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline float Rect::GetTop() const
{
    return y;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline float Rect::GetBottom() const
{
    return IsInfinity(height) ? FLT_INF : y + height;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Point Rect::GetTopLeft() const
{
    return Point(x, y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Point Rect::GetTopRight() const
{
    return Point(GetRight(), y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Point Rect::GetBottomLeft() const
{
    return Point(x, GetBottom());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Point Rect::GetBottomRight() const
{
    return Point(GetRight(), GetBottom());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool Rect::IsEmpty() const
{
    return width == 0.0f || height == 0.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool Rect::Contains(float x_, float y_) const
{
    return !IsEmpty() &&
        x_ >= GetLeft() && x_ <= GetRight() &&
        y_ >= GetTop() && y_ <= GetBottom();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool Rect::Contains(const Point& point) const
{
    return Contains(point.x, point.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool Rect::Contains(const Rect& rect) const
{
    return !IsEmpty() && !rect.IsEmpty() && 
        rect.GetLeft() >= GetLeft() && rect.GetRight() <= GetRight() &&
        rect.GetTop() >= GetTop() && rect.GetBottom() <= GetBottom();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Rect::Inflate(float width_, float height_)
{
    x -= width_;
    y -= height_;
    width += 2.0f * width_;
    height += 2.0f * height_;

    if (width <= 0.0f || height <= 0.0f)
    {
        x = 0.0f;
        y = 0.0f;
        width = 0.0f;
        height = 0.0f;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Rect::Inflate(const Size& size)
{
    Inflate(size.width, size.height);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Rect Rect::Intersect(const Rect& rect) const
{
    float x1 = Max(GetLeft(), rect.GetLeft());
    float x2 = Min(GetRight(), rect.GetRight());
    if (x2 >= x1)
    {
        float y1 = Max(GetTop(), rect.GetTop());
        float y2 = Min(GetBottom(), rect.GetBottom());
        if (y2 >= y1)
        {
            return Rect(x1, y1, x2, y2);
        }
    }

    return Rect::Empty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool Rect::IntersectsWith(const Rect& rect) const
{
    Size s = Intersect(rect).GetSize();
    return s.width > FLT_EPSILON && s.height > FLT_EPSILON;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Rect::Offset(const Point& offset)
{
    x += offset.x;
    y += offset.y;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Rect::Scale(float scaleX, float scaleY)
{
    width *= scaleX;
    height *= scaleY;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Rect::Expand(const Point& point)
{
    float x0 = Min(x, point.x);
    float y0 = Min(y, point.y);
    float x1 = Max(GetRight(), point.x);
    float y1 = Max(GetBottom(), point.y);

    x = x0;
    y = y0;
    width = x1 - x0;
    height = y1 - y0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Rect::Expand(const Rect& rect)
{
    float x0 = Min(x, rect.x);
    float y0 = Min(y, rect.y);
    float x1 = Max(GetRight(), rect.GetRight());
    float y1 = Max(GetBottom(), rect.GetBottom());

    x = x0;
    y = y0;
    width = x1 - x0;
    height = y1 - y0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Rect::Transform(const Transform2& mtx)
{
    if (!IsInfinity(width) && !IsInfinity(height))
    {
        AABBox2 box = AABBox2(x, y, x + width, y + height) * mtx;

        Vector2 boxMin = box.Min();
        x = boxMin.x;
        y = boxMin.y;

        Vector2 boxDiagonal = box.Diagonal();
        width = boxDiagonal.x;
        height = boxDiagonal.y;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Rect::Transform(const Matrix4& mtx)
{
    // Use a 2D transformation whenever is possible
    if (IsZero(mtx[0][2]) && IsZero(mtx[1][2]) && IsOne(mtx[2][2]) && IsZero(mtx[3][2]))
    {
        Transform(Transform2(mtx[0].XY(), mtx[1].XY(), mtx[3].XY()));
    }
    else if (!IsInfinity(width) && !IsInfinity(height))
    {
        float l = GetLeft();
        float r = GetRight();
        float t = GetTop();
        float b = GetBottom();

        Vector4 tlp = Vector4(l, t, 0.0f, 1.0f) * mtx;
        Vector4 trp = Vector4(r, t, 0.0f, 1.0f) * mtx;
        Vector4 blp = Vector4(r, b, 0.0f, 1.0f) * mtx;
        Vector4 brp = Vector4(l, b, 0.0f, 1.0f) * mtx;

        Point tlpw(tlp.x / tlp.w, tlp.y / tlp.w);
        Point trpw(trp.x / trp.w, trp.y / trp.w);
        Point blpw(blp.x / blp.w, blp.y / blp.w);
        Point brpw(brp.x / brp.w, brp.y / brp.w);

        width = 0.0f;
        height = 0.0f;

        x = tlpw.x;
        y = tlpw.y;

        Expand(trpw);
        Expand(blpw);
        Expand(brpw);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Rect Rect::Empty()
{
    return Rect(0.0f, 0.0f, 0.0f, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Rect Rect::Infinite()
{
    return Rect(-FLT_INF, -FLT_INF, FLT_INF, FLT_INF);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Recti::Recti(int left, int top, int right, int bottom): x(left), y(top), width(right - left),
    height(bottom - top)
{
    NS_ASSERT(left <= right);
    NS_ASSERT(top <= bottom);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Recti::Recti(const Sizei& size): x(0), y(0), width(size.width), height(size.height)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Recti::Recti(const Pointi& location, const Sizei& size): x(location.x), y(location.y),
    width(size.width), height(size.height)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool Recti::operator==(const Recti& rect) const
{
    return x == rect.x && y == rect.y && width == rect.width && height == rect.height;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool Recti::operator!=(const Recti& rect) const
{
    return !(*this == rect);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Pointi Recti::GetLocation() const
{
    return Pointi(x, y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Recti::SetLocation(const Pointi& location)
{
    x = location.x;
    y = location.y;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Sizei Recti::GetSize() const
{
    return Sizei(width, height);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Recti::SetSize(const Sizei& size)
{
    width = size.width;
    height = size.height;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline int Recti::GetLeft() const
{
    return x;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline int Recti::GetRight() const
{
    return x + width;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline int Recti::GetTop() const
{
    return y;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline int Recti::GetBottom() const
{
    return y + height;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Pointi Recti::GetTopLeft() const
{
    return Pointi(x, y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Pointi Recti::GetTopRight() const
{
    return Pointi(GetRight(), y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Pointi Recti::GetBottomLeft() const
{
    return Pointi(x, GetBottom());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Pointi Recti::GetBottomRight() const
{
    return Pointi(GetRight(), GetBottom());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool Recti::IsEmpty() const
{
    return width == 0 || height == 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool Recti::Contains(int x_, int y_) const
{
    return !IsEmpty() &&  x_ >= GetLeft() && x_ <= GetRight() && y_ >= GetTop() && y_ <= GetBottom();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool Recti::Contains(const Pointi& point) const
{
    return Contains(point.x, point.y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool Recti::Contains(const Recti& rect) const
{
    return !IsEmpty() && !rect.IsEmpty() &&
        rect.GetLeft() >= GetLeft() && rect.GetRight() <= GetRight() &&
        rect.GetTop() >= GetTop() && rect.GetBottom() <= GetBottom();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Recti::Inflate(int width_, int height_)
{
    x -= width_;
    y -= height_;
    width += 2 * width_;
    height += 2 * height_;

    if (width <= 0.0f || height <= 0.0f)
    {
        x = 0;
        y = 0;
        width = 0;
        height = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Recti::Inflate(const Sizei& size)
{
    Inflate(size.width, size.height);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Recti Recti::Intersect(const Recti& rect) const
{
    int x1 = Max(GetLeft(), rect.GetLeft());
    int x2 = Min(GetRight(), rect.GetRight());
    if (x2 >= x1)
    {
        int y1 = Max(GetTop(), rect.GetTop());
        int y2 = Min(GetBottom(), rect.GetBottom());
        if (y2 >= y1)
        {
            return Recti(x1, y1, x2, y2);
        }
    }

    return Recti::Empty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool Recti::IntersectsWith(const Recti& rect) const
{
    Sizei s = Intersect(rect).GetSize();
    return s.width > 0 && s.height > 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Recti::Offset(const Pointi& offset)
{
    x += offset.x;
    y += offset.y;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Recti::Scale(int scaleX, int scaleY)
{
    width *= scaleX;
    height *= scaleY;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Recti::Expand(const Pointi& point)
{
    int x0 = Min(x, point.x);
    int y0 = Min(y, point.y);
    int x1 = Max(GetRight(), point.x);
    int y1 = Max(GetBottom(), point.y);

    x = x0;
    y = y0;
    width = x1 - x0;
    height = y1 - y0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Recti::Expand(const Recti& rect)
{
    int x0 = Min(x, rect.x);
    int y0 = Min(y, rect.y);
    int x1 = Max(GetRight(), rect.GetRight());
    int y1 = Max(GetBottom(), rect.GetBottom());

    x = x0;
    y = y0;
    width = x1 - x0;
    height = y1 - y0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
inline Recti Recti::Empty()
{
    return Recti(0, 0, 0, 0);
}

}
