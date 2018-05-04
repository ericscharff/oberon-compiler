typedef enum {
  TYPE_UNKNOWN,
  TYPE_INCOMPLETE,
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

const char *type_kind_names[] = {
    [TYPE_UNKNOWN] = "<unknown>",   [TYPE_INCOMPLETE] = "<incomplete>",
    [TYPE_BOOLEAN] = "BOOLEAN",     [TYPE_BYTE] = "BYTE",
    [TYPE_CHAR] = "CHAR",           [TYPE_INTEGER] = "INTEGER",
    [TYPE_REAL] = "REAL",           [TYPE_SET] = "SET",
    [TYPE_STRING] = "<string>",     [TYPE_POINTER] = "POINTER",
    [TYPE_ARRAY] = "ARRAY",         [TYPE_RECORD] = "RECORD",
    [TYPE_PROCEDURE] = "PROCEDURE",
};

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
  bool is_open_array;
} FormalParameter;

typedef struct ProcedureType {
  FormalParameter *params;  // buf
  Type *return_type;
} ProcedureType;

typedef struct RecordField {
  const char *name;
  Type *type;
  bool is_exported;
} RecordField;

typedef struct RecordType {
  Type *base_type;
  RecordField *fields;  // buf
} RecordType;

struct Type {
  TypeKind kind;
  const char *name;  // Only declared types have names;
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

Type *new_incomplete_type(void) {
  Type *t = alloc_type();
  t->kind = TYPE_INCOMPLETE;
  t->name = NULL;
  return t;
}

Type *new_array_type(Type *element_type, int num_elements) {
  Type *t = alloc_type();
  t->kind = TYPE_ARRAY;
  t->name = NULL;
  t->array_type.element_type = element_type;
  t->array_type.num_elements = num_elements;
  return t;
}

Type *new_pointer_type(Type *element_type) {
  Type *t = alloc_type();
  t->kind = TYPE_POINTER;
  t->name = NULL;
  t->pointer_type.element_type = element_type;
  return t;
}

Type *new_procedure_type(FormalParameter *params, Type *return_type) {
  Type *t = alloc_type();
  t->kind = TYPE_PROCEDURE;
  t->name = NULL;
  t->procedure_type.params = params;
  t->procedure_type.return_type = return_type;
  return t;
}

Type *new_record_type(Type *base_type, RecordField *fields) {
  Type *t = alloc_type();
  t->kind = TYPE_RECORD;
  t->name = NULL;
  t->record_type.base_type = base_type;
  t->record_type.fields = fields;
  return t;
}

Type *lookup_field(Type *type, const char *fieldName) {
  for (Type *t = type; t != NULL; t = t->record_type.base_type) {
    if (t->kind == TYPE_POINTER) {
      t = type->pointer_type.element_type;
    }
    if (t->kind != TYPE_RECORD) {
      return NULL;
    }
    for (size_t i = 0; i < buf_len(t->record_type.fields); i++) {
      if (t->record_type.fields[i].name == fieldName) {
        return t->record_type.fields[i].type;
      }
    }
  }
  return NULL;
}

void dbg_dump_type(Type *t) {
  if (t) {
    printf("<type kind: %s", type_kind_names[t->kind]);
    switch (t->kind) {
      case TYPE_ARRAY:
        printf(" %d ", t->array_type.num_elements);
        dbg_dump_type(t->array_type.element_type);
        break;
      case TYPE_POINTER:
        printf(" ");
        // dbg_dump_type(t->pointer_type.element_type);
        break;
      case TYPE_PROCEDURE:
        printf(" ");
        for (size_t i = 0; i < buf_len(t->procedure_type.params); i++) {
          printf(
              " name: %s open_array: %d var: %s ",
              t->procedure_type.params[i].name,
              t->procedure_type.params[i].is_open_array,
              t->procedure_type.params[i].is_var_parameter ? "true" : "false");
          dbg_dump_type(t->procedure_type.params[i].type);
        }
        printf(" : ");
        dbg_dump_type(t->procedure_type.return_type);
        break;
      case TYPE_RECORD:
        printf(" base: ");
        dbg_dump_type(t->record_type.base_type);
        for (size_t i = 0; i < buf_len(t->record_type.fields); i++) {
          printf(" name: %s exported: %s ", t->record_type.fields[i].name,
                 t->record_type.fields[i].is_exported ? "true" : "false");
          dbg_dump_type(t->record_type.fields[i].type);
        }
        break;
      default:
        break;
    }
    printf(">");
  } else {
    printf("<null type>");
  }
}

void type_test(void) {
  assert(type_pool_current == type_pool);
  for (int i = 0; i < 10; i++) {
    alloc_type();
  }
  assert(type_pool_current == (type_pool + 10));
  Type *a = new_array_type(&integerType, 10);
  assert(a->kind == TYPE_ARRAY);
  assert(a->array_type.element_type == &integerType);
  assert(a->array_type.num_elements == 10);
  Type *p = new_pointer_type(a);
  assert(p->kind == TYPE_POINTER);
  assert(p->pointer_type.element_type == a);
  FormalParameter *param = NULL;
  buf_push(param, (FormalParameter){"i", &integerType, false, false});
  buf_push(param, (FormalParameter){"j", &integerType, false, true});
  buf_push(param, (FormalParameter){"k", &integerType, false, false});
  buf_push(param, (FormalParameter){"l", &integerType, false, false});
  Type *proc = new_procedure_type(param, &charType);
  assert(proc->kind == TYPE_PROCEDURE);
  assert(proc->procedure_type.params == param);
  assert(proc->procedure_type.return_type == &charType);
  dbg_dump_type(proc);
  printf("\n");
  RecordField *fields = NULL;
  buf_push(fields, (RecordField){"alpha", &integerType, true});
  buf_push(fields, (RecordField){"beta", &realType, false});
  Type *rec = new_record_type(NULL, fields);
  dbg_dump_type(rec);
  printf("\n");
  assert(rec->kind == TYPE_RECORD);
  assert(rec->record_type.base_type == NULL);
  assert(strcmp(rec->record_type.fields[0].name, "alpha") == 0);
  assert(rec->record_type.fields[0].type == &integerType);
  assert(rec->record_type.fields[0].is_exported == true);
  assert(strcmp(rec->record_type.fields[1].name, "beta") == 0);
  assert(rec->record_type.fields[1].type == &realType);
  assert(rec->record_type.fields[1].is_exported == false);
}
