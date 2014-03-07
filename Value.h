#ifndef VALUE_H
#define VALUE_H

#include <iostream>
#include <string>
#include <list>
#include <vector>

enum ValueType {
  STRING_VALUE,
  NUM_VALUE,
  OBJECT_VALUE,
  ARRAY_VALUE,
  BOOL_VALUE,
  NULL_VALUE,
  FUNC_VALUE
};

struct Value {
  const ValueType _type;
  Value (ValueType t) : _type(t) {}
  virtual ~Value() {}
  virtual std::ostream& print(std::ostream& os, int indent) {return os;}
};

struct StringValue : public Value {
  const std::string _str;
  StringValue(const std::string& s) : Value(STRING_VALUE), _str(s) {}
};

struct NumValue : public Value {
  double _num;
  NumValue(double n) : Value(NUM_VALUE), _num(n) {}
};

struct ObjectValue  : public Value {
  std::list<std::pair<std::string,Value*> > _members;
  ObjectValue(const std::list<std::pair<std::string,Value*> >& members)
    : Value(OBJECT_VALUE), _members(members) {}
};

struct ArrayValue : public Value {
  std::vector<Value*> _array;
  ArrayValue(const std::vector<Value*>& array)
    : Value(ARRAY_VALUE), _array(array) {}
};

struct BoolValue : public Value {
  const bool _bool;
  BoolValue(bool b) : Value(BOOL_VALUE), _bool(b) {}
};

struct NullValue : public Value {
  NullValue() : Value(NULL_VALUE) {}
};

struct FuncValue : public Value {
  FuncValue() : Value(FUNC_VALUE) {}
};

#endif // VALUE_H
