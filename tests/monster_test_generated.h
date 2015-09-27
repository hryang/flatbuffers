// automatically generated by the FlatBuffers compiler, do not modify

#ifndef FLATBUFFERS_GENERATED_MONSTERTEST_MYGAME_EXAMPLE_H_
#define FLATBUFFERS_GENERATED_MONSTERTEST_MYGAME_EXAMPLE_H_

#include "flatbuffers/flatbuffers.h"

namespace MyGame {
namespace OtherNameSpace {
struct Unused;
}  // namespace OtherNameSpace
}  // namespace MyGame

namespace MyGame {
namespace Example {

struct Test;
struct TestSimpleTableWithEnum;
struct Vec3;
struct Stat;
struct Monster;

enum Color {
  Color_Red = 1,
  Color_Green = 2,
  Color_Blue = 8
};

inline const char **EnumNamesColor() {
  static const char *names[] = { "Red", "Green", "", "", "", "", "", "Blue", NULL };
  return names;
}

inline const char *EnumNameColor(Color e) { return EnumNamesColor()[e - Color_Red]; }

enum Any {
  Any_NONE = 0,
  Any_Monster = 1,
  Any_TestSimpleTableWithEnum = 2
};

inline const char **EnumNamesAny() {
  static const char *names[] = { "NONE", "Monster", "TestSimpleTableWithEnum", NULL };
  return names;
}

inline const char *EnumNameAny(Any e) { return EnumNamesAny()[e]; }

inline bool VerifyAny(flatbuffers::Verifier &verifier, const void *union_obj, Any type);

MANUALLY_ALIGNED_STRUCT(2) Test FLATBUFFERS_FINAL_CLASS {
 private:
  int16_t a_;
  int8_t b_;
  int8_t __padding0;

 public:
  Test(int16_t a, int8_t b)
    : a_(flatbuffers::EndianScalar(a)), b_(flatbuffers::EndianScalar(b)), __padding0(0) { (void)__padding0; }

  int16_t a() const { return flatbuffers::EndianScalar(a_); }
  void mutate_a(int16_t a) { flatbuffers::WriteScalar(&a_, a); }
  int8_t b() const { return flatbuffers::EndianScalar(b_); }
  void mutate_b(int8_t b) { flatbuffers::WriteScalar(&b_, b); }
};
STRUCT_END(Test, 4);

MANUALLY_ALIGNED_STRUCT(16) Vec3 FLATBUFFERS_FINAL_CLASS {
 private:
  float x_;
  float y_;
  float z_;
  int32_t __padding0;
  double test1_;
  int8_t test2_;
  int8_t __padding1;
  Test test3_;
  int16_t __padding2;

 public:
  Vec3(float x, float y, float z, double test1, Color test2, const Test &test3)
    : x_(flatbuffers::EndianScalar(x)), y_(flatbuffers::EndianScalar(y)), z_(flatbuffers::EndianScalar(z)), __padding0(0), test1_(flatbuffers::EndianScalar(test1)), test2_(flatbuffers::EndianScalar(static_cast<int8_t>(test2))), __padding1(0), test3_(test3), __padding2(0) { (void)__padding0; (void)__padding1; (void)__padding2; }

  float x() const { return flatbuffers::EndianScalar(x_); }
  void mutate_x(float x) { flatbuffers::WriteScalar(&x_, x); }
  float y() const { return flatbuffers::EndianScalar(y_); }
  void mutate_y(float y) { flatbuffers::WriteScalar(&y_, y); }
  float z() const { return flatbuffers::EndianScalar(z_); }
  void mutate_z(float z) { flatbuffers::WriteScalar(&z_, z); }
  double test1() const { return flatbuffers::EndianScalar(test1_); }
  void mutate_test1(double test1) { flatbuffers::WriteScalar(&test1_, test1); }
  Color test2() const { return static_cast<Color>(flatbuffers::EndianScalar(test2_)); }
  void mutate_test2(Color test2) { flatbuffers::WriteScalar(&test2_, static_cast<int8_t>(test2)); }
  const Test &test3() const { return test3_; }
  Test &mutable_test3() { return test3_; }
};
STRUCT_END(Vec3, 32);

struct TestSimpleTableWithEnum FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  Color color() const { return static_cast<Color>(GetField<int8_t>(4, 2)); }
  bool mutate_color(Color color) { return SetField(4, static_cast<int8_t>(color)); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, 4 /* color */) &&
           verifier.EndTable();
  }
};

struct TestSimpleTableWithEnumBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_color(Color color) { fbb_.AddElement<int8_t>(4, static_cast<int8_t>(color), 2); }
  TestSimpleTableWithEnumBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  TestSimpleTableWithEnumBuilder &operator=(const TestSimpleTableWithEnumBuilder &);
  flatbuffers::Offset<TestSimpleTableWithEnum> Finish() {
    flatbuffers::Offset<TestSimpleTableWithEnum> o = flatbuffers::Offset<TestSimpleTableWithEnum>(fbb_.EndTable(start_, 1));
    return o;
  }
};

inline flatbuffers::Offset<TestSimpleTableWithEnum> CreateTestSimpleTableWithEnum(flatbuffers::FlatBufferBuilder &_fbb,
   Color color = Color_Green) {
  TestSimpleTableWithEnumBuilder builder_(_fbb);
  builder_.add_color(color);
  return builder_.Finish();
}

struct Stat FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  const flatbuffers::String *id() const { return GetPointer<const flatbuffers::String *>(4); }
  flatbuffers::String *mutable_id() { return GetPointer<flatbuffers::String *>(4); }
  int64_t val() const { return GetField<int64_t>(6, 0); }
  bool mutate_val(int64_t val) { return SetField(6, val); }
  uint16_t count() const { return GetField<uint16_t>(8, 0); }
  bool mutate_count(uint16_t count) { return SetField(8, count); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 4 /* id */) &&
           verifier.Verify(id()) &&
           VerifyField<int64_t>(verifier, 6 /* val */) &&
           VerifyField<uint16_t>(verifier, 8 /* count */) &&
           verifier.EndTable();
  }
};

struct StatBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_id(flatbuffers::Offset<flatbuffers::String> id) { fbb_.AddOffset(4, id); }
  void add_val(int64_t val) { fbb_.AddElement<int64_t>(6, val, 0); }
  void add_count(uint16_t count) { fbb_.AddElement<uint16_t>(8, count, 0); }
  StatBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  StatBuilder &operator=(const StatBuilder &);
  flatbuffers::Offset<Stat> Finish() {
    flatbuffers::Offset<Stat> o = flatbuffers::Offset<Stat>(fbb_.EndTable(start_, 3));
    return o;
  }
};

inline flatbuffers::Offset<Stat> CreateStat(flatbuffers::FlatBufferBuilder &_fbb,
   flatbuffers::Offset<flatbuffers::String> id = 0,
   int64_t val = 0,
   uint16_t count = 0) {
  StatBuilder builder_(_fbb);
  builder_.add_val(val);
  builder_.add_id(id);
  builder_.add_count(count);
  return builder_.Finish();
}

struct Monster FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  const Vec3 *pos() const { return GetStruct<const Vec3 *>(4); }
  Vec3 *mutable_pos() { return GetStruct<Vec3 *>(4); }
  int16_t mana() const { return GetField<int16_t>(6, 150); }
  bool mutate_mana(int16_t mana) { return SetField(6, mana); }
  int16_t hp() const { return GetField<int16_t>(8, 100); }
  bool mutate_hp(int16_t hp) { return SetField(8, hp); }
  const flatbuffers::String *name() const { return GetPointer<const flatbuffers::String *>(10); }
  flatbuffers::String *mutable_name() { return GetPointer<flatbuffers::String *>(10); }
  bool KeyCompareLessThan(const Monster *o) const { return *name() < *o->name(); }
  int KeyCompareWithValue(const char *val) const { return strcmp(name()->c_str(), val); }
  const flatbuffers::Vector<uint8_t> *inventory() const { return GetPointer<const flatbuffers::Vector<uint8_t> *>(14); }
  flatbuffers::Vector<uint8_t> *mutable_inventory() { return GetPointer<flatbuffers::Vector<uint8_t> *>(14); }
  Color color() const { return static_cast<Color>(GetField<int8_t>(16, 8)); }
  bool mutate_color(Color color) { return SetField(16, static_cast<int8_t>(color)); }
  Any test_type() const { return static_cast<Any>(GetField<uint8_t>(18, 0)); }
  bool mutate_test_type(Any test_type) { return SetField(18, static_cast<uint8_t>(test_type)); }
  const void *test() const { return GetPointer<const void *>(20); }
  void *mutable_test() { return GetPointer<void *>(20); }
  const flatbuffers::Vector<const Test *> *test4() const { return GetPointer<const flatbuffers::Vector<const Test *> *>(22); }
  flatbuffers::Vector<const Test *> *mutable_test4() { return GetPointer<flatbuffers::Vector<const Test *> *>(22); }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String> > *testarrayofstring() const { return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String> > *>(24); }
  flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String> > *mutable_testarrayofstring() { return GetPointer<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String> > *>(24); }
  /// an example documentation comment: this will end up in the generated code
  /// multiline too
  const flatbuffers::Vector<flatbuffers::Offset<Monster> > *testarrayoftables() const { return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Monster> > *>(26); }
  flatbuffers::Vector<flatbuffers::Offset<Monster> > *mutable_testarrayoftables() { return GetPointer<flatbuffers::Vector<flatbuffers::Offset<Monster> > *>(26); }
  const Monster *enemy() const { return GetPointer<const Monster *>(28); }
  Monster *mutable_enemy() { return GetPointer<Monster *>(28); }
  const flatbuffers::Vector<uint8_t> *testnestedflatbuffer() const { return GetPointer<const flatbuffers::Vector<uint8_t> *>(30); }
  flatbuffers::Vector<uint8_t> *mutable_testnestedflatbuffer() { return GetPointer<flatbuffers::Vector<uint8_t> *>(30); }
  const MyGame::Example::Monster *testnestedflatbuffer_nested_root() const { return flatbuffers::GetRoot<MyGame::Example::Monster>(testnestedflatbuffer()->Data()); }
  const Stat *testempty() const { return GetPointer<const Stat *>(32); }
  Stat *mutable_testempty() { return GetPointer<Stat *>(32); }
  uint8_t testbool() const { return GetField<uint8_t>(34, 0); }
  bool mutate_testbool(uint8_t testbool) { return SetField(34, testbool); }
  int32_t testhashs32_fnv1() const { return GetField<int32_t>(36, 0); }
  bool mutate_testhashs32_fnv1(int32_t testhashs32_fnv1) { return SetField(36, testhashs32_fnv1); }
  uint32_t testhashu32_fnv1() const { return GetField<uint32_t>(38, 0); }
  bool mutate_testhashu32_fnv1(uint32_t testhashu32_fnv1) { return SetField(38, testhashu32_fnv1); }
  int64_t testhashs64_fnv1() const { return GetField<int64_t>(40, 0); }
  bool mutate_testhashs64_fnv1(int64_t testhashs64_fnv1) { return SetField(40, testhashs64_fnv1); }
  uint64_t testhashu64_fnv1() const { return GetField<uint64_t>(42, 0); }
  bool mutate_testhashu64_fnv1(uint64_t testhashu64_fnv1) { return SetField(42, testhashu64_fnv1); }
  int32_t testhashs32_fnv1a() const { return GetField<int32_t>(44, 0); }
  bool mutate_testhashs32_fnv1a(int32_t testhashs32_fnv1a) { return SetField(44, testhashs32_fnv1a); }
  uint32_t testhashu32_fnv1a() const { return GetField<uint32_t>(46, 0); }
  bool mutate_testhashu32_fnv1a(uint32_t testhashu32_fnv1a) { return SetField(46, testhashu32_fnv1a); }
  int64_t testhashs64_fnv1a() const { return GetField<int64_t>(48, 0); }
  bool mutate_testhashs64_fnv1a(int64_t testhashs64_fnv1a) { return SetField(48, testhashs64_fnv1a); }
  uint64_t testhashu64_fnv1a() const { return GetField<uint64_t>(50, 0); }
  bool mutate_testhashu64_fnv1a(uint64_t testhashu64_fnv1a) { return SetField(50, testhashu64_fnv1a); }
  const flatbuffers::Vector<uint8_t> *testarrayofbools() const { return GetPointer<const flatbuffers::Vector<uint8_t> *>(52); }
  flatbuffers::Vector<uint8_t> *mutable_testarrayofbools() { return GetPointer<flatbuffers::Vector<uint8_t> *>(52); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<Vec3>(verifier, 4 /* pos */) &&
           VerifyField<int16_t>(verifier, 6 /* mana */) &&
           VerifyField<int16_t>(verifier, 8 /* hp */) &&
           VerifyFieldRequired<flatbuffers::uoffset_t>(verifier, 10 /* name */) &&
           verifier.Verify(name()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 14 /* inventory */) &&
           verifier.Verify(inventory()) &&
           VerifyField<int8_t>(verifier, 16 /* color */) &&
           VerifyField<uint8_t>(verifier, 18 /* test_type */) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 20 /* test */) &&
           VerifyAny(verifier, test(), test_type()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 22 /* test4 */) &&
           verifier.Verify(test4()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 24 /* testarrayofstring */) &&
           verifier.Verify(testarrayofstring()) &&
           verifier.VerifyVectorOfStrings(testarrayofstring()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 26 /* testarrayoftables */) &&
           verifier.Verify(testarrayoftables()) &&
           verifier.VerifyVectorOfTables(testarrayoftables()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 28 /* enemy */) &&
           verifier.VerifyTable(enemy()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 30 /* testnestedflatbuffer */) &&
           verifier.Verify(testnestedflatbuffer()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 32 /* testempty */) &&
           verifier.VerifyTable(testempty()) &&
           VerifyField<uint8_t>(verifier, 34 /* testbool */) &&
           VerifyField<int32_t>(verifier, 36 /* testhashs32_fnv1 */) &&
           VerifyField<uint32_t>(verifier, 38 /* testhashu32_fnv1 */) &&
           VerifyField<int64_t>(verifier, 40 /* testhashs64_fnv1 */) &&
           VerifyField<uint64_t>(verifier, 42 /* testhashu64_fnv1 */) &&
           VerifyField<int32_t>(verifier, 44 /* testhashs32_fnv1a */) &&
           VerifyField<uint32_t>(verifier, 46 /* testhashu32_fnv1a */) &&
           VerifyField<int64_t>(verifier, 48 /* testhashs64_fnv1a */) &&
           VerifyField<uint64_t>(verifier, 50 /* testhashu64_fnv1a */) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, 52 /* testarrayofbools */) &&
           verifier.Verify(testarrayofbools()) &&
           verifier.EndTable();
  }
};

struct MonsterBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_pos(const Vec3 *pos) { fbb_.AddStruct(4, pos); }
  void add_mana(int16_t mana) { fbb_.AddElement<int16_t>(6, mana, 150); }
  void add_hp(int16_t hp) { fbb_.AddElement<int16_t>(8, hp, 100); }
  void add_name(flatbuffers::Offset<flatbuffers::String> name) { fbb_.AddOffset(10, name); }
  void add_inventory(flatbuffers::Offset<flatbuffers::Vector<uint8_t> > inventory) { fbb_.AddOffset(14, inventory); }
  void add_color(Color color) { fbb_.AddElement<int8_t>(16, static_cast<int8_t>(color), 8); }
  void add_test_type(Any test_type) { fbb_.AddElement<uint8_t>(18, static_cast<uint8_t>(test_type), 0); }
  void add_test(flatbuffers::Offset<void> test) { fbb_.AddOffset(20, test); }
  void add_test4(flatbuffers::Offset<flatbuffers::Vector<const Test *> > test4) { fbb_.AddOffset(22, test4); }
  void add_testarrayofstring(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String> > > testarrayofstring) { fbb_.AddOffset(24, testarrayofstring); }
  void add_testarrayoftables(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Monster> > > testarrayoftables) { fbb_.AddOffset(26, testarrayoftables); }
  void add_enemy(flatbuffers::Offset<Monster> enemy) { fbb_.AddOffset(28, enemy); }
  void add_testnestedflatbuffer(flatbuffers::Offset<flatbuffers::Vector<uint8_t> > testnestedflatbuffer) { fbb_.AddOffset(30, testnestedflatbuffer); }
  void add_testempty(flatbuffers::Offset<Stat> testempty) { fbb_.AddOffset(32, testempty); }
  void add_testbool(uint8_t testbool) { fbb_.AddElement<uint8_t>(34, testbool, 0); }
  void add_testhashs32_fnv1(int32_t testhashs32_fnv1) { fbb_.AddElement<int32_t>(36, testhashs32_fnv1, 0); }
  void add_testhashu32_fnv1(uint32_t testhashu32_fnv1) { fbb_.AddElement<uint32_t>(38, testhashu32_fnv1, 0); }
  void add_testhashs64_fnv1(int64_t testhashs64_fnv1) { fbb_.AddElement<int64_t>(40, testhashs64_fnv1, 0); }
  void add_testhashu64_fnv1(uint64_t testhashu64_fnv1) { fbb_.AddElement<uint64_t>(42, testhashu64_fnv1, 0); }
  void add_testhashs32_fnv1a(int32_t testhashs32_fnv1a) { fbb_.AddElement<int32_t>(44, testhashs32_fnv1a, 0); }
  void add_testhashu32_fnv1a(uint32_t testhashu32_fnv1a) { fbb_.AddElement<uint32_t>(46, testhashu32_fnv1a, 0); }
  void add_testhashs64_fnv1a(int64_t testhashs64_fnv1a) { fbb_.AddElement<int64_t>(48, testhashs64_fnv1a, 0); }
  void add_testhashu64_fnv1a(uint64_t testhashu64_fnv1a) { fbb_.AddElement<uint64_t>(50, testhashu64_fnv1a, 0); }
  void add_testarrayofbools(flatbuffers::Offset<flatbuffers::Vector<uint8_t> > testarrayofbools) { fbb_.AddOffset(52, testarrayofbools); }
  MonsterBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  MonsterBuilder &operator=(const MonsterBuilder &);
  flatbuffers::Offset<Monster> Finish() {
    flatbuffers::Offset<Monster> o = flatbuffers::Offset<Monster>(fbb_.EndTable(start_, 25));
    fbb_.Required(o, 10);  // name
    return o;
  }
};

inline flatbuffers::Offset<Monster> CreateMonster(flatbuffers::FlatBufferBuilder &_fbb,
   const Vec3 *pos = 0,
   int16_t mana = 150,
   int16_t hp = 100,
   flatbuffers::Offset<flatbuffers::String> name = 0,
   flatbuffers::Offset<flatbuffers::Vector<uint8_t> > inventory = 0,
   Color color = Color_Blue,
   Any test_type = Any_NONE,
   flatbuffers::Offset<void> test = 0,
   flatbuffers::Offset<flatbuffers::Vector<const Test *> > test4 = 0,
   flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String> > > testarrayofstring = 0,
   flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Monster> > > testarrayoftables = 0,
   flatbuffers::Offset<Monster> enemy = 0,
   flatbuffers::Offset<flatbuffers::Vector<uint8_t> > testnestedflatbuffer = 0,
   flatbuffers::Offset<Stat> testempty = 0,
   uint8_t testbool = 0,
   int32_t testhashs32_fnv1 = 0,
   uint32_t testhashu32_fnv1 = 0,
   int64_t testhashs64_fnv1 = 0,
   uint64_t testhashu64_fnv1 = 0,
   int32_t testhashs32_fnv1a = 0,
   uint32_t testhashu32_fnv1a = 0,
   int64_t testhashs64_fnv1a = 0,
   uint64_t testhashu64_fnv1a = 0,
   flatbuffers::Offset<flatbuffers::Vector<uint8_t> > testarrayofbools = 0) {
  MonsterBuilder builder_(_fbb);
  builder_.add_testhashu64_fnv1a(testhashu64_fnv1a);
  builder_.add_testhashs64_fnv1a(testhashs64_fnv1a);
  builder_.add_testhashu64_fnv1(testhashu64_fnv1);
  builder_.add_testhashs64_fnv1(testhashs64_fnv1);
  builder_.add_testarrayofbools(testarrayofbools);
  builder_.add_testhashu32_fnv1a(testhashu32_fnv1a);
  builder_.add_testhashs32_fnv1a(testhashs32_fnv1a);
  builder_.add_testhashu32_fnv1(testhashu32_fnv1);
  builder_.add_testhashs32_fnv1(testhashs32_fnv1);
  builder_.add_testempty(testempty);
  builder_.add_testnestedflatbuffer(testnestedflatbuffer);
  builder_.add_enemy(enemy);
  builder_.add_testarrayoftables(testarrayoftables);
  builder_.add_testarrayofstring(testarrayofstring);
  builder_.add_test4(test4);
  builder_.add_test(test);
  builder_.add_inventory(inventory);
  builder_.add_name(name);
  builder_.add_pos(pos);
  builder_.add_hp(hp);
  builder_.add_mana(mana);
  builder_.add_testbool(testbool);
  builder_.add_test_type(test_type);
  builder_.add_color(color);
  return builder_.Finish();
}

inline bool VerifyAny(flatbuffers::Verifier &verifier, const void *union_obj, Any type) {
  switch (type) {
    case Any_NONE: return true;
    case Any_Monster: return verifier.VerifyTable(reinterpret_cast<const Monster *>(union_obj));
    case Any_TestSimpleTableWithEnum: return verifier.VerifyTable(reinterpret_cast<const TestSimpleTableWithEnum *>(union_obj));
    default: return false;
  }
}

inline const MyGame::Example::Monster *GetMonster(const void *buf) { return flatbuffers::GetRoot<MyGame::Example::Monster>(buf); }

inline Monster *GetMutableMonster(void *buf) { return flatbuffers::GetMutableRoot<Monster>(buf); }

inline bool VerifyMonsterBuffer(flatbuffers::Verifier &verifier) { return verifier.VerifyBuffer<MyGame::Example::Monster>(); }

inline const char *MonsterIdentifier() { return "MONS"; }

inline bool MonsterBufferHasIdentifier(const void *buf) { return flatbuffers::BufferHasIdentifier(buf, MonsterIdentifier()); }

inline const char *MonsterExtension() { return "mon"; }

inline void FinishMonsterBuffer(flatbuffers::FlatBufferBuilder &fbb, flatbuffers::Offset<MyGame::Example::Monster> root) { fbb.Finish(root, MonsterIdentifier()); }

}  // namespace Example
}  // namespace MyGame

#endif  // FLATBUFFERS_GENERATED_MONSTERTEST_MYGAME_EXAMPLE_H_
