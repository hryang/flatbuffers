/*
 * Copyright 2014 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// independent from idl_parser, since this code is not needed for most clients

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

namespace flatbuffers {
namespace java {

static std::string GenTypeBasic(const Type &type) {
  static const char *ctypename[] = {
    #define FLATBUFFERS_TD(ENUM, IDLTYPE, CTYPE, JTYPE, GTYPE) #JTYPE,
      FLATBUFFERS_GEN_TYPES(FLATBUFFERS_TD)
    #undef FLATBUFFERS_TD
  };
  return ctypename[type.base_type];
}

static std::string GenTypeGet(const Type &type);

static std::string GenTypePointer(const Type &type) {
  switch (type.base_type) {
    case BASE_TYPE_STRING:
      return "String";
    case BASE_TYPE_VECTOR:
      return GenTypeGet(type.VectorType());
    case BASE_TYPE_STRUCT:
      return type.struct_def->name;
    case BASE_TYPE_UNION:
      // fall through
    default:
      return "Table";
  }
}

static std::string GenTypeGet(const Type &type) {
  return IsScalar(type.base_type)
    ? GenTypeBasic(type)
    : GenTypePointer(type);
}

static void GenComment(const std::string &dc,
                       std::string *code_ptr,
                       const char *prefix = "") {
  std::string &code = *code_ptr;
  if (dc.length()) {
    code += std::string(prefix) + "///" + dc + "\n";
  }
}

static void GenEnum(EnumDef &enum_def, std::string *code_ptr) {
  std::string &code = *code_ptr;
  if (enum_def.generated) return;

  // Generate enum definitions of the form:
  // public static final int name = value;
  // We use ints rather than the Java Enum feature, because we want them
  // to map directly to how they're used in C/C++ and file formats.
  // That, and Java Enums are expensive, and not universally liked.
  GenComment(enum_def.doc_comment, code_ptr);
  code += "public class " + enum_def.name + " {\n";
  for (auto it = enum_def.vals.vec.begin();
       it != enum_def.vals.vec.end();
       ++it) {
    auto &ev = **it;
    GenComment(ev.doc_comment, code_ptr, "  ");
    code += "  public static final " + GenTypeBasic(enum_def.underlying_type);
    code += " " + ev.name + " = ";
    code += NumToString(ev.value) + ";\n";
  }
  code += "};\n\n";
}

// Returns the function name that is able to read a value of the given type.
static std::string GenGetter(const Type &type) {
  switch (type.base_type) {
    case BASE_TYPE_STRING: return "__string";
    case BASE_TYPE_STRUCT: return "__struct";
    case BASE_TYPE_UNION: return "__union";
    case BASE_TYPE_VECTOR: return GenGetter(type.VectorType());
    default:
      return "bb.get" + (SizeOf(type.base_type) > 1
        ? MakeCamel(GenTypeGet(type))
        : "");
  }
}

// Returns the method name for use with add/put calls.
static std::string GenMethod(const Type &type) {
  return IsScalar(type.base_type)
    ? MakeCamel(GenTypeBasic(type))
    : (IsStruct(type) ? "Struct" : "Offset");
}

// Recursively generate arguments for a constructor, to deal with nested
// structs.
static void GenStructArgs(const StructDef &struct_def, std::string *code_ptr,
                          const char *nameprefix) {
  std::string &code = *code_ptr;
  for (auto it = struct_def.fields.vec.begin();
       it != struct_def.fields.vec.end();
       ++it) {
    auto &field = **it;
    if (IsStruct(field.value.type)) {
      // Generate arguments for a struct inside a struct. To ensure names
      // don't clash, and to make it obvious these arguments are constructing
      // a nested struct, prefix the name with the struct name.
      GenStructArgs(*field.value.type.struct_def, code_ptr,
                    (field.value.type.struct_def->name + "_").c_str());
    } else {
      code += ", " + GenTypeBasic(field.value.type) + " " + nameprefix;
      code += MakeCamel(field.name, false);
    }
  }
}

// Recusively generate struct construction statements of the form:
// builder.putType(name);
// and insert manual padding.
static void GenStructBody(const StructDef &struct_def, std::string *code_ptr,
                          const char *nameprefix) {
  std::string &code = *code_ptr;
  code += "    builder.prep(" + NumToString(struct_def.minalign) + ", ";
  code += NumToString(struct_def.bytesize) + ");\n";
  for (auto it = struct_def.fields.vec.rbegin();
       it != struct_def.fields.vec.rend();
       ++it) {
    auto &field = **it;
    if (field.padding)
      code += "    builder.pad(" + NumToString(field.padding) + ");\n";
    if (IsStruct(field.value.type)) {
      GenStructBody(*field.value.type.struct_def, code_ptr,
                    (field.value.type.struct_def->name + "_").c_str());
    } else {
      code += "    builder.put" + GenMethod(field.value.type) + "(";
      code += nameprefix + MakeCamel(field.name, false) + ");\n";
    }
  }
}

static void GenStruct(const Parser &parser, StructDef &struct_def,
                      std::string *code_ptr) {
  if (struct_def.generated) return;
  std::string &code = *code_ptr;

  // Generate a struct accessor class, with methods of the form:
  // public type name() { return bb.getType(i + offset); }
  // or for tables of the form:
  // public type name() {
  //   int o = __offset(offset); return o != 0 ? bb.getType(o + i) : default;
  // }
  GenComment(struct_def.doc_comment, code_ptr);
  code += "public class " + struct_def.name + " extends ";
  code += struct_def.fixed ? "Struct" : "Table";
  code += " {\n";
  if (!struct_def.fixed) {
    // Generate a special accessor for the table that when used as the root
    // of a FlatBuffer
    code += "  public static " + struct_def.name + " getRootAs";
    code += struct_def.name;
    code += "(ByteBuffer _bb) { ";
    code += "_bb.order(ByteOrder.LITTLE_ENDIAN); ";
    code += "return (new " + struct_def.name;
    code += "()).__init(_bb.getInt(_bb.position()) + _bb.position(), _bb); }\n";
    if (parser.root_struct_def == &struct_def) {
      if (parser.file_identifier_.length()) {
        // Check if a buffer has the identifier.
        code += "  public static boolean " + struct_def.name;
        code += "BufferHasIdentifier(ByteBuffer _bb) { return ";
        code += "__has_identifier(_bb, \"" + parser.file_identifier_;
        code += "\"); }\n";
      }
    }
  }
  // Generate the __init method that sets the field in a pre-existing
  // accessor object. This is to allow object reuse.
  code += "  public " + struct_def.name;
  code += " __init(int _i, ByteBuffer _bb) ";
  code += "{ bb_pos = _i; bb = _bb; return this; }\n\n";
  for (auto it = struct_def.fields.vec.begin();
       it != struct_def.fields.vec.end();
       ++it) {
    auto &field = **it;
    if (field.deprecated) continue;
    GenComment(field.doc_comment, code_ptr, "  ");
    std::string type_name = GenTypeGet(field.value.type);
    std::string method_start = "  public " + type_name + " " +
                               MakeCamel(field.name, false);
    // Generate the accessors that don't do object reuse.
    if (field.value.type.base_type == BASE_TYPE_STRUCT) {
      // Calls the accessor that takes an accessor object with a new object.
      code += method_start + "() { return " + MakeCamel(field.name, false);
      code += "(new ";
      code += type_name + "()); }\n";
    } else if (field.value.type.base_type == BASE_TYPE_VECTOR &&
               field.value.type.element == BASE_TYPE_STRUCT) {
      // Accessors for vectors of structs also take accessor objects, this
      // generates a variant without that argument.
      code += method_start + "(int j) { return " + MakeCamel(field.name, false);
      code += "(new ";
      code += type_name + "(), j); }\n";
    }
    std::string getter = GenGetter(field.value.type);
    code += method_start + "(";
    // Most field accessors need to retrieve and test the field offset first,
    // this is the prefix code for that:
    auto offset_prefix = ") { int o = __offset(" +
                         NumToString(field.value.offset) +
                         "); return o != 0 ? ";
    if (IsScalar(field.value.type.base_type)) {
      if (struct_def.fixed) {
        code += ") { return " + getter;
        code += "(bb_pos + " + NumToString(field.value.offset) + ")";
      } else {
        code += offset_prefix + getter;
        code += "(o + bb_pos) : " + field.value.constant;
      }
    } else {
      switch (field.value.type.base_type) {
        case BASE_TYPE_STRUCT:
          code += type_name + " obj";
          if (struct_def.fixed) {
            code += ") { return obj.__init(bb_pos + ";
            code += NumToString(field.value.offset) + ", bb)";
          } else {
            code += offset_prefix;
            code += "obj.__init(";
            code += field.value.type.struct_def->fixed
                      ? "o + bb_pos"
                      : "__indirect(o + bb_pos)";
            code += ", bb) : null";
          }
          break;
        case BASE_TYPE_STRING:
          code += offset_prefix + getter +"(o + bb_pos) : null";
          break;
        case BASE_TYPE_VECTOR: {
          auto vectortype = field.value.type.VectorType();
          if (vectortype.base_type == BASE_TYPE_STRUCT) {
            code += type_name + " obj, ";
            getter = "obj.__init";
          }
          code += "int j" + offset_prefix + getter +"(";
          auto index = "__vector(o) + j * " +
                       NumToString(InlineSize(vectortype));
          if (vectortype.base_type == BASE_TYPE_STRUCT) {
            code += vectortype.struct_def->fixed
                      ? index
                      : "__indirect(" + index + ")";
            code += ", bb";
          } else {
            code += index;
          }
          code += ") : ";
          code += IsScalar(field.value.type.element) ? "0" : "null";
          break;
        }
        case BASE_TYPE_UNION:
          code += type_name + " obj" + offset_prefix + getter;
          code += "(obj, o) : null";
          break;
        default:
          assert(0);
      }
    }
    code += "; }\n";
    if (field.value.type.base_type == BASE_TYPE_VECTOR) {
      code += "  public int " + MakeCamel(field.name, false) + "Length(";
      code += offset_prefix;
      code += "__vector_len(o) : 0; }\n";
    }
    if (field.value.type.base_type == BASE_TYPE_VECTOR ||
        field.value.type.base_type == BASE_TYPE_STRING) {
      code += "  public ByteBuffer " + MakeCamel(field.name, false);
      code += "AsByteBuffer() { return __vector_as_bytebuffer(";
      code += NumToString(field.value.offset) + ", ";
      code += NumToString(field.value.type.base_type == BASE_TYPE_STRING ? 1 :
                          InlineSize(field.value.type.VectorType()));
      code += "); }\n";
    }
  }
  code += "\n";
  if (struct_def.fixed) {
    // create a struct constructor function
    code += "  public static int create" + struct_def.name;
    code += "(FlatBufferBuilder builder";
    GenStructArgs(struct_def, code_ptr, "");
    code += ") {\n";
    GenStructBody(struct_def, code_ptr, "");
    code += "    return builder.offset();\n  }\n";
  } else {
    // Create a set of static methods that allow table construction,
    // of the form:
    // public static void addName(FlatBufferBuilder builder, short name)
    // { builder.addShort(id, name, default); }
    code += "  public static void start" + struct_def.name;
    code += "(FlatBufferBuilder builder) { builder.startObject(";
    code += NumToString(struct_def.fields.vec.size()) + "); }\n";
    for (auto it = struct_def.fields.vec.begin();
         it != struct_def.fields.vec.end();
         ++it) {
      auto &field = **it;
      if (field.deprecated) continue;
      code += "  public static void add" + MakeCamel(field.name);
      code += "(FlatBufferBuilder builder, " + GenTypeBasic(field.value.type);
      auto argname = MakeCamel(field.name, false);
      if (!IsScalar(field.value.type.base_type)) argname += "Offset";
      code += " " + argname + ") { builder.add";
      code += GenMethod(field.value.type) + "(";
      code += NumToString(it - struct_def.fields.vec.begin()) + ", ";
      code += argname + ", " + field.value.constant;
      code += "); }\n";
      if (field.value.type.base_type == BASE_TYPE_VECTOR) {
        auto vector_type = field.value.type.VectorType();
        auto alignment = InlineAlignment(vector_type);
        auto elem_size = InlineSize(vector_type);
        if (!IsStruct(vector_type)) {
          // Generate a method to create a vector from a Java array.
          code += "  public static int create" + MakeCamel(field.name);
          code += "Vector(FlatBufferBuilder builder, ";
          code += GenTypeBasic(vector_type) + "[] data) ";
          code += "{ builder.startVector(";
          code += NumToString(elem_size);
          code += ", data.length, " + NumToString(alignment);
          code += "); for (int i = data.length - 1; i >= 0; i--) builder.add";
          code += GenMethod(vector_type);
          code += "(data[i]); return builder.endVector(); }\n";
        }
        // Generate a method to start a vector, data to be added manually after.
        code += "  public static void start" + MakeCamel(field.name);
        code += "Vector(FlatBufferBuilder builder, int numElems) ";
        code += "{ builder.startVector(";
        code += NumToString(elem_size);
        code += ", numElems, " + NumToString(alignment);
        code += "); }\n";      }
    }
    code += "  public static int end" + struct_def.name;
    code += "(FlatBufferBuilder builder) { return builder.endObject(); }\n";
    if (parser.root_struct_def == &struct_def) {
      code += "  public static void finish" + struct_def.name;
      code += "Buffer(FlatBufferBuilder builder, int offset) { ";
      code += "builder.finish(offset";
      if (parser.file_identifier_.length())
        code += ", \"" + parser.file_identifier_ + "\"";
      code += "); }\n";
    }
  }
  code += "};\n\n";
}

// Save out the generated code for a single Java class while adding
// declaration boilerplate.
static bool SaveClass(const Parser &parser, const Definition &def,
                      const std::string &classcode, const std::string &path,
                      bool needs_imports) {
  if (!classcode.length()) return true;

  std::string namespace_java;
  std::string namespace_dir = path;
  auto &namespaces = parser.namespaces_.back()->components;
  for (auto it = namespaces.begin(); it != namespaces.end(); ++it) {
    if (namespace_java.length()) {
      namespace_java += ".";
      namespace_dir += kPathSeparator;
    }
    namespace_java += *it;
    namespace_dir += *it;
  }
  EnsureDirExists(namespace_dir);

  std::string code = "// automatically generated, do not modify\n\n";
  code += "package " + namespace_java + ";\n\n";
  if (needs_imports) {
    code += "import java.nio.*;\nimport java.lang.*;\nimport java.util.*;\n";
    code += "import flatbuffers.*;\n\n";
  }
  code += classcode;
  auto filename = namespace_dir + kPathSeparator + def.name + ".java";
  return SaveFile(filename.c_str(), code, false);
}

}  // namespace java

bool GenerateJava(const Parser &parser,
                  const std::string &path,
                  const std::string & /*file_name*/,
                  const GeneratorOptions & /*opts*/) {
  using namespace java;

  for (auto it = parser.enums_.vec.begin();
       it != parser.enums_.vec.end(); ++it) {
    std::string enumcode;
    GenEnum(**it, &enumcode);
    if (!SaveClass(parser, **it, enumcode, path, false))
      return false;
  }

  for (auto it = parser.structs_.vec.begin();
       it != parser.structs_.vec.end(); ++it) {
    std::string declcode;
    GenStruct(parser, **it, &declcode);
    if (!SaveClass(parser, **it, declcode, path, true))
      return false;
  }

  return true;
}

}  // namespace flatbuffers