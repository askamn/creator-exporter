// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_TYPES_CREATOR_BUFFERS_H_
#define FLATBUFFERS_GENERATED_TYPES_CREATOR_BUFFERS_H_

#include "flatbuffers/flatbuffers.h"

namespace creator {
namespace buffers {

struct Vec2;

struct Vec3;

struct Size;

struct Rect;

struct ColorRGB;

struct ColorRGBA;

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Vec2 FLATBUFFERS_FINAL_CLASS {
 private:
  float x_;
  float y_;

 public:
  Vec2() {
    memset(this, 0, sizeof(Vec2));
  }
  Vec2(float _x, float _y)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)) {
  }
  float x() const {
    return flatbuffers::EndianScalar(x_);
  }
  float y() const {
    return flatbuffers::EndianScalar(y_);
  }
};
FLATBUFFERS_STRUCT_END(Vec2, 8);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Vec3 FLATBUFFERS_FINAL_CLASS {
 private:
  float x_;
  float y_;
  float z_;

 public:
  Vec3() {
    memset(this, 0, sizeof(Vec3));
  }
  Vec3(float _x, float _y, float _z)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)),
        z_(flatbuffers::EndianScalar(_z)) {
  }
  float x() const {
    return flatbuffers::EndianScalar(x_);
  }
  float y() const {
    return flatbuffers::EndianScalar(y_);
  }
  float z() const {
    return flatbuffers::EndianScalar(z_);
  }
};
FLATBUFFERS_STRUCT_END(Vec3, 12);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Size FLATBUFFERS_FINAL_CLASS {
 private:
  float w_;
  float h_;

 public:
  Size() {
    memset(this, 0, sizeof(Size));
  }
  Size(float _w, float _h)
      : w_(flatbuffers::EndianScalar(_w)),
        h_(flatbuffers::EndianScalar(_h)) {
  }
  float w() const {
    return flatbuffers::EndianScalar(w_);
  }
  float h() const {
    return flatbuffers::EndianScalar(h_);
  }
};
FLATBUFFERS_STRUCT_END(Size, 8);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Rect FLATBUFFERS_FINAL_CLASS {
 private:
  float x_;
  float y_;
  float w_;
  float h_;

 public:
  Rect() {
    memset(this, 0, sizeof(Rect));
  }
  Rect(float _x, float _y, float _w, float _h)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)),
        w_(flatbuffers::EndianScalar(_w)),
        h_(flatbuffers::EndianScalar(_h)) {
  }
  float x() const {
    return flatbuffers::EndianScalar(x_);
  }
  float y() const {
    return flatbuffers::EndianScalar(y_);
  }
  float w() const {
    return flatbuffers::EndianScalar(w_);
  }
  float h() const {
    return flatbuffers::EndianScalar(h_);
  }
};
FLATBUFFERS_STRUCT_END(Rect, 16);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(1) ColorRGB FLATBUFFERS_FINAL_CLASS {
 private:
  uint8_t r_;
  uint8_t g_;
  uint8_t b_;

 public:
  ColorRGB() {
    memset(this, 0, sizeof(ColorRGB));
  }
  ColorRGB(uint8_t _r, uint8_t _g, uint8_t _b)
      : r_(flatbuffers::EndianScalar(_r)),
        g_(flatbuffers::EndianScalar(_g)),
        b_(flatbuffers::EndianScalar(_b)) {
  }
  uint8_t r() const {
    return flatbuffers::EndianScalar(r_);
  }
  uint8_t g() const {
    return flatbuffers::EndianScalar(g_);
  }
  uint8_t b() const {
    return flatbuffers::EndianScalar(b_);
  }
};
FLATBUFFERS_STRUCT_END(ColorRGB, 3);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(1) ColorRGBA FLATBUFFERS_FINAL_CLASS {
 private:
  uint8_t r_;
  uint8_t g_;
  uint8_t b_;
  uint8_t a_;

 public:
  ColorRGBA() {
    memset(this, 0, sizeof(ColorRGBA));
  }
  ColorRGBA(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
      : r_(flatbuffers::EndianScalar(_r)),
        g_(flatbuffers::EndianScalar(_g)),
        b_(flatbuffers::EndianScalar(_b)),
        a_(flatbuffers::EndianScalar(_a)) {
  }
  uint8_t r() const {
    return flatbuffers::EndianScalar(r_);
  }
  uint8_t g() const {
    return flatbuffers::EndianScalar(g_);
  }
  uint8_t b() const {
    return flatbuffers::EndianScalar(b_);
  }
  uint8_t a() const {
    return flatbuffers::EndianScalar(a_);
  }
};
FLATBUFFERS_STRUCT_END(ColorRGBA, 4);

}  // namespace buffers
}  // namespace creator

#endif  // FLATBUFFERS_GENERATED_TYPES_CREATOR_BUFFERS_H_
