typedef enum {
  TYPE_UNKNOWN,
  TYPE_BOOLEAN,
  TYPE_BYTE,
  TYPE_CHAR,
  TYPE_INTEGER,
  TYPE_REAL,
  TYPE_SET,
  TYPE_STRING,
  TYPE_POINTER,
  TYPE_ARRAY,
  TYPE_RECORD,
  TYPE_PROCEDURE,
} TypeKind;

typedef struct Type Type;

typedef struct ArrayType {
  // can be 0, or -1 for open arrays
  int num_elements;
  Type *element_type;
} ArrayType;

typedef struct PointerType {
  Type *element_type;
} PointerType;

typedef struct FormalParameter {
  const char *name;
  Type *type;
  bool is_var_parameter;
} FormalParameter;

typedef struct ProcedureType {
  FormalParameter *params;
  Type *return_type;
} ProcedureType;

typedef struct RecordField {
  const char *name;
  Type *type;
  bool is_exported;
} RecordField;

typedef struct RecordType {
  Type *base_type;
  RecordField *fields;
} RecordType;

struct Type {
  TypeKind kind;
  union {
    ArrayType array_type;
    PointerType pointer_type;
    ProcedureType procedure_type;
    RecordType record_type;
  };
};

Type booleanType;
Type byteType;
Type charType;
Type integerType;
Type realType;
Type setType;
Type stringType;

#define TYPE_POOL_SIZE 1024
Type type_pool[TYPE_POOL_SIZE];
Type *type_pool_current;
Type *type_pool_end;

void init_builtin_types(void) {
  booleanType.kind = TYPE_BOOLEAN;
  byteType.kind = TYPE_BYTE;
  charType.kind = TYPE_CHAR;
  integerType.kind = TYPE_INTEGER;
  realType.kind = TYPE_REAL;
  setType.kind = TYPE_SET;
  stringType.kind = TYPE_STRING;
  type_pool_current = type_pool;
  type_pool_end = type_pool_current + TYPE_POOL_SIZE;
}

Type *alloc_type(void) {
  if (type_pool_current >= type_pool_end) {
    assert(0);
  }
  return type_pool_current++;
}

Type *make_array_type(Type *element_type, int num_elements) {
  Type *t = alloc_type();
  t->kind = TYPE_ARRAY;
  t->array_type.element_type = element_type;
  t->array_type.num_elements = num_elements;
  return t;
}

Type *make_pointer_type(Type *element_type) {
  Type *t = alloc_type();
  t->kind = TYPE_POINTER;
  t->pointer_type.element_type = element_type;
  return t;
}

void type_test(void) {
  assert(type_pool_current == type_pool);
  for (int i=0; i < 10; i++) {
    alloc_type();
  }
  assert(type_pool_current == (type_pool + 10));
  Type *a = make_array_type(&integerType, 10);
  assert(a->kind == TYPE_ARRAY);
  assert(a->array_type.element_type == &integerType);
  assert(a->array_type.num_elements == 10);
  Type *p = make_pointer_type(a);
  assert(p->kind == TYPE_POINTER);
  assert(p->pointer_type.element_type == a);
}
