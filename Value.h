#ifndef VALUE_H
#define VALUE_H

#include <iostream>
#include <string>
#include <list>
#include <vector>

enum ValueType {
  StringValue,
  NumberValue,
  ObjectValue,
  ArrayValue,
  BooleanValue,
  NullValue,
  FuncValue
};

struct Value {
  const ValueType type;
  Value (ValueType t) : type(t) {}
  virtual ~Value() {}
  virtual std::ostream& print(std::ostream& os, int indent) = 0;
};

struct StringValue : public Value {
  const std::string str;
  StringValue(const std::string& s) : Value(StringValue), str(s) {}
  virtual std::ostream& print(std::ostream& os, int indent);
};

struct NumberValue : public Value {
  double number;
  NumberValue(double n) : Value(NumberValue), number(n) {}
  virtual std::ostream& print(std::ostream& os, int indent);
};

// XXXX

struct ObjectValue  : public Value {
};

struct ArrayValue : public Value {
};

struct BoolValue : public Value {
};

struct NullValue : public Value {
};

struct FuncValue : public Value {
};

#endif // VALUE_H
