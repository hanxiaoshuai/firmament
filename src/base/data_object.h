// The Firmament project
// Copyright (c) 2011-2013 Malte Schwarzkopf <malte.schwarzkopf@cl.cam.ac.uk>
//
// Data object class definition. In Firmament, a data object is a chunk of
// binary data, in memory or not, that can be read, written or executed. It is
// globally uniquely named by a DataObjectName.
//
// The notion of a Firmament data object is closely related to the DIOS notions
// of a name and a reference.

#ifndef FIRMAMENT_DATA_OBJECT_H
#define FIRMAMENT_DATA_OBJECT_H

#include <string>

#include "base/common.h"
#include "misc/printable_interface.h"

namespace firmament {

// Imported from libDIOS.
#define DIOS_NAME_BITS 256
#define DIOS_NAME_BYTES (DIOS_NAME_BITS/8)
#define DIOS_NAME_QWORDS (DIOS_NAME_BYTES/8)

typedef struct {
  union {
    uint64_t value[DIOS_NAME_QWORDS];
    uint8_t raw[DIOS_NAME_BYTES];
  };
} dios_name_t;

class DataObject : public PrintableInterface {
 public:
  explicit DataObject(const dios_name_t& name);
  explicit DataObject(const char* name);
  explicit DataObject(const uint8_t* name);
  explicit DataObject(const string& name);
  bool operator==(const DataObject& other_do) const;
  bool operator<(const DataObject& other_do) const;


  inline const uint8_t* name() const {
    return name_.raw;
  }
  inline const string* name_str() const {
    char ret[DIOS_NAME_BYTES+1];
    memcpy(ret, name_.raw, DIOS_NAME_BYTES);
    ret[DIOS_NAME_BYTES] = '\0';
    return new string(ret);
  }
  inline const char* name_bytes() const {
    return reinterpret_cast<const char*>(name_.raw);
  }
  inline const string name_printable_string() const {
    string ret = "";
    for (uint32_t i = 0; i < DIOS_NAME_QWORDS; ++i)
      ret += to_hex_string(name_.value[i]);
    return ret;
  }
  virtual ostream& ToString(ostream* stream) const {
    return *stream << "<DataObject, name=" << name_printable_string() << ", at="
                   << this << ", location=" << ">";
  }

 private:
  dios_name_t name_;
  //dios_value_t location_;
};

}  // namespace firmament

#endif  // FIRMAMENT_PLATFORMS_DATA_OBJECT_H
