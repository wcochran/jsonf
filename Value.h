#ifndef VALUE_H
#define VALUE_H

#include <iostream>
#include <string>
#include <list>
#include <vector>

enum ValueType {
  STRING_VALUE,
  NUMBER_VALUE,
  OBJECT_VALUE,
  ARRAY_VALUE,
  BOOLEAN_VALUE,
  NULL_VALUE,
  FUNC_VALUE
};

struct Value {
  const ValueType type;
  Value (ValueType t) : type(t) {}
  virtual ~Value() {}
  virtual std::ostream& print(std::ostream& os, int indent) = 0;
};

struct StringValue : public Value {
  const std::string str;
  StringValue(const std::string& s) : Value(STRING_VALUE), str(s) {}
  virtual std::ostream& print(std::ostream& os, int indent);
};

struct NumberValue : public Value {
  double number;
  NumberValue(double n) : Value(NUMBER_VALUE), number(n) {}
  virtual std::ostream& print(std::ostream& os, int indent);
};

struct ObjectValue  : public Value {
  std::list<pair<std::string,Value*> > _members;
  ObjectValue(const std::list<pair<std::string,Value*> >& members)
    : Value(OBJECT_VALUE), _members(members) {}
  virtual ~ObjectValue();
  virtual std::ostream& print(std::ostream& os, int indent);
};

struct ArrayValue : public Value {
  std::vector<Value*> _array;
  ArrayValue(const std::vector<Value*>& array)
    : Value(ARRAY_VALUE), _array(array) {}
  virtual ~ArrayValue() {}
  virtual std::ostream& print(std::ostream& os, int indent);
};

struct BoolValue : public Value {
  const bool val;
  BoolValue(bool v) : Value(BOOL_VALUE), val(v) {}
  virtual std::ostream& print(std::ostream& os, int indent);
};

struct NullValue : public Value {
  NullValue() : Value(NULL_VALUE) {}
  virtual std::ostream& print(std::ostream& os, int indent);
};

struct FuncValue : public Value {
  Expr *_func;
  FuncValue(Expr *f) : Value(FUNC_VALUE), _func(f) {}
  virtual std::ostream& print(std::ostream& os, int indent);
};

#endif // VALUE_H
