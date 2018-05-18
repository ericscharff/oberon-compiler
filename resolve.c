void resolve_expr(Expr *e);
void resolve_decl(Decl *d);
void resolve_decls(Decl *d);
void resolve_statements(Statement *body);

#define SCOPE_SIZE 1024
Decl *gResolveScope[SCOPE_SIZE];
int gResolveScopeLast = 0;  // points to first unusd slot (past scope end)

int resolve_scope_enter(void) { return gResolveScopeLast; }

void resolve_scope_leave(int newScope) { gResolveScopeLast = newScope; }

void resolve_scope_push(Decl *declBuf) {
  for (size_t i = 0; i < buf_len(declBuf); i++) {
    assert(gResolveScopeLast < SCOPE_SIZE);
    gResolveScope[gResolveScopeLast++] = declBuf + i;
  }
}

Decl *resolve_find_defn(const char *packageName, const char *name) {
  for (int i = gResolveScopeLast - 1; i >= 0; i--) {
    if (gResolveScope[i]->package_name == packageName &&
        gResolveScope[i]->name == name) {
      return gResolveScope[i];
    }
  }
  return NULL;
}

void eval_unary_expr(Expr *e, Expr *expr) {
  assert(e);
  assert(expr);
  assert(expr->is_const);
  assert(expr->type);

  switch (e->unary.op) {
    case TOKEN_PLUS:
      if (expr->type == &integerType || expr->type == &realType) {
        e->val = expr->val;
        e->type = expr->type;
      } else {
        assert(0);
      }
      break;
    case TOKEN_MINUS:
      if (expr->type == &integerType) {
        e->val.kind = VAL_INTEGER;
        e->val.iVal = -expr->val.iVal;
      } else if (expr->type == &realType) {
        e->val.kind = VAL_REAL;
        e->val.rVal = -expr->val.rVal;
      } else if (expr->type == &setType) {
        e->val.kind = VAL_SET;
        e->val.setVal = ~expr->val.setVal;
      } else {
        assert(0);
      }
      break;
    case TOKEN_AS_SET_ELT:
      if (expr->type == &integerType) {
        e->val.kind = VAL_SET;
        e->type = &setType;
        e->val.setVal = 1 << expr->val.iVal;
      } else {
        errorloc(expr->loc, "Set element expected INTEGER, got %s",
                 expr->type->name);
      }
      break;
    default:
      assert(0);
      break;
  }
}

void resolve_unary_expr(Expr *e) {
  assert(e);
  assert(e->kind == EXPR_UNARY);
  assert(e->unary.expr);

  Expr *expr = e->unary.expr;
  resolve_expr(expr);
  assert(expr->type);
  switch (e->unary.op) {
    case TOKEN_PLUS:
    case TOKEN_MINUS:
      if (expr->type == &integerType || expr->type == &realType ||
          expr->type == &setType || expr->type == &byteType) {
        e->type = expr->type;
      } else {
        errorloc(e->loc, "INTEGER, REAL, SET, or BYTE expected for operator %s",
                 op_name(e->unary.op));
      }
      break;
    case TOKEN_TILDE:
      if (expr->type == &booleanType) {
        e->type = expr->type;
      } else {
        errorloc(e->loc, "BOOLEAN expected for operator %s",
                 op_name(e->unary.op));
      }
      break;
    case TOKEN_AS_SET_ELT:
      if (expr->type == &integerType) {
        e->type = &setType;
      } else {
        errorloc(e->loc, "SET expected for operator %s", op_name(e->unary.op));
      }
      break;
    default:
      assert(0);
      break;
  }
  if (e->unary.expr->is_const) {
    e->is_const = true;
    eval_unary_expr(e, e->unary.expr);
  }
}

void eval_binary_expr(Expr *e, Expr *lhs, Expr *rhs) {
  assert(e);
  assert(lhs);
  assert(lhs->is_const);
  assert(lhs->type);
  assert(rhs);
  assert(rhs->is_const);
  assert(rhs->type);

  switch (e->binary.op) {
    case TOKEN_PLUS:
      if (lhs->type == &integerType) {
        e->val.kind = VAL_INTEGER;
        e->val.iVal = lhs->val.iVal + rhs->val.iVal;
      } else if (lhs->type == &realType) {
        e->val.kind = VAL_REAL;
        e->val.rVal = lhs->val.rVal + rhs->val.rVal;
      } else if (lhs->type == &setType) {
        e->val.kind = VAL_SET;
        e->val.setVal = lhs->val.setVal | rhs->val.setVal;
      } else {
        assert(0);
      }
      break;
    case TOKEN_MINUS:
      if (lhs->type == &integerType) {
        e->val.kind = VAL_INTEGER;
        e->val.iVal = lhs->val.iVal - rhs->val.iVal;
      } else if (lhs->type == &realType) {
        e->val.kind = VAL_REAL;
        e->val.rVal = lhs->val.rVal - rhs->val.rVal;
      } else if (lhs->type == &setType) {
        e->val.kind = VAL_SET;
        e->val.setVal = lhs->val.setVal & ~rhs->val.setVal;
      } else {
        assert(0);
      }
      break;
    case TOKEN_STAR:
      if (lhs->type == &integerType) {
        e->val.kind = VAL_INTEGER;
        e->val.iVal = lhs->val.iVal * rhs->val.iVal;
      } else if (lhs->type == &realType) {
        e->val.kind = VAL_REAL;
        e->val.rVal = lhs->val.rVal * rhs->val.rVal;
      } else if (lhs->type == &setType) {
        e->val.kind = VAL_SET;
        e->val.setVal = lhs->val.setVal & rhs->val.setVal;
      } else {
        assert(0);
      }
      break;
    case TOKEN_SLASH:
      if (lhs->type == &integerType) {
        e->val.kind = VAL_INTEGER;
        e->val.iVal = lhs->val.iVal / rhs->val.iVal;
      } else if (lhs->type == &realType) {
        e->val.kind = VAL_REAL;
        e->val.rVal = lhs->val.rVal / rhs->val.rVal;
      } else if (lhs->type == &setType) {
        e->val.kind = VAL_SET;
        e->val.setVal = lhs->val.setVal ^ rhs->val.setVal;
      } else {
        assert(0);
      }
      break;
    case TOKEN_DIV:
      if (lhs->type == &integerType) {
        e->val.kind = VAL_INTEGER;
        e->val.iVal = lhs->val.iVal / rhs->val.iVal;
      } else {
        assert(0);
      }
      break;
    case TOKEN_MOD:
      if (lhs->type == &integerType) {
        e->val.kind = VAL_INTEGER;
        e->val.iVal = lhs->val.iVal % rhs->val.iVal;
      } else {
        assert(0);
      }
      break;
    case TOKEN_AMP:
      if (lhs->type == &booleanType) {
        e->val.kind = VAL_BOOLEAN;
        e->val.bVal = lhs->val.bVal && rhs->val.bVal;
      } else {
        assert(0);
      }
      break;
    case TOKEN_OR:
      if (lhs->type == &booleanType) {
        e->val.kind = VAL_BOOLEAN;
        e->val.bVal = lhs->val.bVal || rhs->val.bVal;
      } else {
        assert(0);
      }
      break;
    case TOKEN_DOTDOT:
      if (lhs->type == &integerType) {
        uint32_t r = 0;
        int from = lhs->val.iVal;
        int to = rhs->val.iVal;
        while (from <= to) {
          r |= 1 << from;
          from++;
        }
        e->val.kind = VAL_SET;
        e->val.setVal = r;
      } else {
        assert(0);
      }
      break;
    case TOKEN_LT:
      if (lhs->type == &integerType) {
        e->val.kind = VAL_BOOLEAN;
        e->val.bVal = lhs->val.iVal < rhs->val.iVal;
      } else if (lhs->type == &realType) {
        e->val.kind = VAL_BOOLEAN;
        e->val.bVal = lhs->val.rVal < rhs->val.rVal;
      } else {
        assert(0);
      }
      break;
    case TOKEN_LTEQ:
      if (lhs->type == &integerType) {
        e->val.kind = VAL_BOOLEAN;
        e->val.bVal = lhs->val.iVal <= rhs->val.iVal;
      } else if (lhs->type == &realType) {
        e->val.kind = VAL_BOOLEAN;
        e->val.bVal = lhs->val.rVal <= rhs->val.rVal;
      } else {
        assert(0);
      }
      break;
    case TOKEN_GT:
      if (lhs->type == &integerType) {
        e->val.kind = VAL_BOOLEAN;
        e->val.bVal = lhs->val.iVal > rhs->val.iVal;
      } else if (lhs->type == &realType) {
        e->val.kind = VAL_BOOLEAN;
        e->val.bVal = lhs->val.rVal > rhs->val.rVal;
      } else {
        assert(0);
      }
      break;
    case TOKEN_GTEQ:
      if (lhs->type == &integerType) {
        e->val.kind = VAL_BOOLEAN;
        e->val.bVal = lhs->val.iVal >= rhs->val.iVal;
      } else if (lhs->type == &realType) {
        e->val.kind = VAL_BOOLEAN;
        e->val.bVal = lhs->val.rVal >= rhs->val.rVal;
      } else {
        assert(0);
      }
      break;
    case TOKEN_EQ:
      if (lhs->type == &integerType) {
        e->val.kind = VAL_BOOLEAN;
        e->val.bVal = lhs->val.iVal == rhs->val.iVal;
      } else if (lhs->type == &realType) {
        e->val.kind = VAL_BOOLEAN;
        e->val.bVal = lhs->val.rVal == rhs->val.rVal;
      } else if (lhs->type == &setType) {
        e->val.kind = VAL_BOOLEAN;
        e->val.bVal = lhs->val.setVal == rhs->val.setVal;
      } else {
        assert(0);
      }
      break;
    default:
      assert(0);
      break;
  }
}

bool is_one_char_string(Expr *e) {
  return e->is_const && e->val.kind == VAL_STRING && strlen(e->val.sVal) == 1;
}

bool is_equivalent(Expr *a, Expr *b) {
  return is_equivalent_type(a->type, b->type) ||
         (a->type == &charType && is_one_char_string(b)) ||
         (b->type == &charType && is_one_char_string(a));
}

void resolve_binary_expr(Expr *e) {
  assert(e);
  assert(e->kind == EXPR_BINARY);
  assert(e->binary.lhs);
  assert(e->binary.rhs);

  Expr *lhs = e->binary.lhs;
  Expr *rhs = e->binary.rhs;
  resolve_expr(lhs);
  resolve_expr(rhs);
  assert(lhs->type);
  assert(rhs->type);

  switch (e->binary.op) {
    case TOKEN_PLUS:
    case TOKEN_MINUS:
    case TOKEN_STAR:
    case TOKEN_SLASH:
      if (lhs->type != rhs->type) {
        errorloc(e->loc, "Types %s and %s must match for operator %s",
                 lhs->type->name, rhs->type->name, op_name(e->binary.op));
      }
      if (lhs->type == &integerType || lhs->type == &realType ||
          lhs->type == &setType || lhs->type == &byteType) {
        e->type = lhs->type;
      } else {
        errorloc(e->loc, "INTEGER, REAL, SET, or BYTE expected for operator %s",
                 op_name(e->binary.op));
      }
      break;
    case TOKEN_DIV:
    case TOKEN_MOD:
      if (lhs->type != rhs->type) {
        errorloc(e->loc, "Types %s and %s must match for operator %s",
                 lhs->type->name, rhs->type->name, op_name(e->binary.op));
      }
      if (lhs->type == &integerType) {
        e->type = lhs->type;
      } else {
        errorloc(e->loc, "INTEGER expected for operator %s",
                 op_name(e->binary.op));
      }
      break;
    case TOKEN_AMP:
    case TOKEN_OR:
      if (lhs->type == &booleanType && rhs->type == &booleanType) {
        e->type = &booleanType;
      } else {
        errorloc(e->loc, "BOOLEAN expected for operator %s",
                 op_name(e->binary.op));
      }
      break;
    case TOKEN_DOTDOT:
      if (lhs->type == &integerType && rhs->type == &integerType) {
        e->type = &setType;
      } else {
        errorloc(e->loc, "INTEGER expected for operator %s",
                 op_name(e->binary.op));
      }
      break;
    case TOKEN_LT:
    case TOKEN_LTEQ:
    case TOKEN_GT:
    case TOKEN_GTEQ:
      if (lhs->type == rhs->type ||
          (lhs->type == &charType && is_one_char_string(rhs)) ||
          (rhs->type == &charType && is_one_char_string(lhs)) ||
          (is_string_type(lhs->type) && is_string_type(rhs->type))) {
        if (lhs->type == &integerType || lhs->type == &realType ||
            lhs->type == &charType || lhs->type == &byteType ||
            lhs->type == &stringType || is_string_type(lhs->type)) {
          e->type = &booleanType;
        } else {
          errorloc(
              e->loc,
              "INTEGER, REAL, CHAR, BYTE, or STRING expected for operator %s",
              op_name(e->binary.op));
        }
      } else {
        errorloc(e->loc, "Types %s and %s must match for operator %s",
                 lhs->type->name, rhs->type->name, op_name(e->binary.op));
      }
      break;
    case TOKEN_EQ:
    case TOKEN_POUND:
      if (is_equivalent(lhs, rhs)) {
        e->type = &booleanType;
      } else {
        errorloc(e->loc, "Types %s and %s must match for operator %s",
                 lhs->type->name, rhs->type->name, op_name(e->binary.op));
      }
      break;
    case TOKEN_IN:
      if (lhs->type != &integerType) {
        errorloc(e->loc, "left side of IN must be INTEGER, not %s",
                 lhs->type->name);
      }
      if (rhs->type != &setType) {
        errorloc(e->loc, "right side of IN must be SET, not %s",
                 rhs->type->name);
      }
      e->type = &booleanType;
      break;
    case TOKEN_IS:
    default:
      assert(0);
      break;
  }

  if (lhs->is_const && rhs->is_const) {
    e->is_const = true;
    eval_binary_expr(e, lhs, rhs);
  }
}

void resolve_identref(Expr *e) {
  assert(e);
  assert(e->kind == EXPR_IDENTREF);
  const char *name = e->identref.name;
  const char *packageName = e->identref.package_name;
  Decl *d = resolve_find_defn(packageName, name);
  if (!d) {
    errorloc(e->loc, "%s.%s undefined", packageName, name);
  }
  resolve_decl(d);
  e->type = d->type;
  if (d->kind == DECL_CONST) {
    e->is_const = true;
    Expr *constExpr = d->const_val.expr;
    if (constExpr->is_const) {
      e->val = constExpr->val;
    } else {
      errorloc(constExpr->loc, "Expression is not constant");
    }
  }
  // Note - imprted vars are not assignable either
  if (d->kind == DECL_VAR || d->kind == DECL_PARAM ||
      d->kind == DECL_VARPARAM) {
    e->is_assignable = true;
  }
  if (d->kind == DECL_PARAM && d->type->kind == TYPE_RECORD) {
    e->is_assignable = false;
  }
}

void resolve_arrayref(Expr *e) {
  assert(e);
  assert(e->kind == EXPR_ARRAYREF);
  Expr *indexExpr = e->arrayref.array_index;
  Expr *arrayRef = e->arrayref.expr;
  resolve_expr(indexExpr);
  resolve_expr(arrayRef);
  if (indexExpr->type != &integerType) {
    errorloc(indexExpr->loc, "array index type %s should be INTEGER",
             indexExpr->type->name);
  }
  if (arrayRef->type->kind != TYPE_ARRAY) {
    errorloc(arrayRef->loc, "item %s is not an ARRAY", arrayRef->type->name);
  }
  e->type = arrayRef->type->array_type.element_type;
  e->is_assignable = arrayRef->is_assignable;
}

void resolve_type(Type *type) {
  assert(type);
  if (type->resolved) {
    return;
  }
  type->resolved = true;
  if (type->kind == TYPE_POINTER) {
    resolve_type(type->pointer_type.element_type);
  }
  if (type->kind == TYPE_RECORD) {
    Type *base_type = type->record_type.base_type;
    if (base_type) {
      resolve_type(base_type);
      if (base_type->kind != TYPE_RECORD) {
        error("Base record type %s must be a RECORD", base_type->name);
      }
    }
    for (size_t i = 0; i < buf_len(type->record_type.fields); i++) {
      printf("Record field %s\n", type->record_type.fields[i].name);
      // TODO - Check for duplicate field name?
      resolve_type(type->record_type.fields[i].type);
    }
  }
  if (type->kind == TYPE_ARRAY) {
    resolve_type(type->array_type.element_type);
    Expr *e = type->array_type.num_elements_expr;
    resolve_expr(e);
    if (e->is_const) {
      if (e->val.kind == VAL_INTEGER) {
        int size = e->val.iVal;
        if (size > 0) {
          type->array_type.num_elements = size;
          printf("array size %d\n", size);
        } else {
          error("ARRAY size %d must be greater than 0", size);
        }
      } else {
        error("ARRAY capacity must be INTEGER");
      }
    } else {
      error("Array expr must be constant");
    }
  }
}

void verify_proc_param_compatible(FormalParameter *formal, Expr *actual) {
  resolve_type(formal->type);
  resolve_expr(actual);
  if (formal->is_var_parameter && !actual->is_assignable) {
    errorloc(actual->loc, "VAR param expected, actual param is not assignable");
  }
  if (formal->is_open_array) {
    if (formal->type == &charType && is_string_type(actual->type)) {
      // ARRAY OF CHAR -> STRING is OK
      return;
    }
    if (actual->type->kind == TYPE_ARRAY &&
        actual->type->array_type.element_type == formal->type) {
      // ARRAY OF N -> ARRAY <z> OF N is OK
      return;
    }
    errorloc(actual->loc,
             "actual type %s does not match formal type ARRAY OF %s",
             actual->type->name, formal->type->name);
  }
  if (formal->type != actual->type) {
    // This is way too strict
    errorloc(actual->loc, "actual type %s does not match formal type %s",
             actual->type->name, formal->type->name);
  }
}

Type *resolve_proc_call(Expr *proc, Expr **actualParams) {
  assert(proc);

  resolve_expr(proc);
  if (proc->type->kind == TYPE_PROCEDURE) {
    FormalParameter *formalParams = proc->type->procedure_type.params;
    if (buf_len(formalParams) == buf_len(actualParams)) {
      for (size_t i = 0; i < buf_len(formalParams); i++) {
        verify_proc_param_compatible(formalParams + i, actualParams[i]);
      }
    } else {
      errorloc(proc->loc, "Expected %d parameters, got %d",
               buf_len(formalParams), buf_len(actualParams));
    }
  } else {
    errorloc(proc->loc, "%s not a PROCEDURE", proc->type->name);
  }
  return proc->type->procedure_type.return_type;
}

void resolve_expr(Expr *e) {
  assert(e);
  switch (e->kind) {
    case EXPR_UNARY:
      resolve_unary_expr(e);
      break;
    case EXPR_BINARY:
      resolve_binary_expr(e);
      break;
    case EXPR_IDENTREF:
      resolve_identref(e);
      break;
    case EXPR_PROCCALL: {
      Type *retType = resolve_proc_call(e->proccall.proc, e->proccall.args);
      if (retType) {
        e->type = retType;
      } else {
        errorloc(e->loc, "Not a proper procedure");
      }
      break;
    }
    case EXPR_FIELDREF:
      assert(0);
      break;
    case EXPR_POINTERDEREF:
      assert(0);
      break;
    case EXPR_ARRAYREF:
      resolve_arrayref(e);
      break;
    case EXPR_TYPEGUARD:
      assert(0);
      break;
    case EXPR_INTEGER:
      e->is_const = true;
      e->type = &integerType;
      e->val.kind = VAL_INTEGER;
      e->val.iVal = e->integer.iVal;
      break;
    case EXPR_REAL:
      e->is_const = true;
      e->type = &realType;
      e->val.kind = VAL_REAL;
      e->val.rVal = e->real.rVal;
      break;
    case EXPR_STRING:
      e->is_const = true;
      e->type = &stringType;
      e->val.kind = VAL_STRING;
      e->val.sVal = e->string.sVal;
      break;
    case EXPR_NIL:
      e->is_const = true;
      e->type = &nilType;
      e->val.kind = VAL_NIL;
      break;
    case EXPR_TRUE:
      e->is_const = true;
      e->type = &booleanType;
      e->val.kind = VAL_BOOLEAN;
      e->val.bVal = true;
      break;
    case EXPR_FALSE:
      e->is_const = true;
      e->type = &booleanType;
      e->val.kind = VAL_BOOLEAN;
      e->val.bVal = false;
      break;
    case EXPR_EMPTYSET:
      e->is_const = true;
      e->type = &setType;
      e->val.kind = VAL_SET;
      e->val.setVal = 0;
      break;
    default:
      assert(0);
      break;
  }
}

void resolve_const_decl(Decl *d) {
  assert(d->kind == DECL_CONST);
  Expr *e = d->const_val.expr;
  resolve_expr(e);
  if (e->is_const) {
    assert(e->type);
    d->type = e->type;
    printf("CONST name: %s type: %s val: ", d->name, d->type->name);
    dbg_print_val(e->val);
    printf("\n");
  } else {
    errorloc(e->loc, "Const exprssion for %s is not const", d->name);
  }
}

void resolve_type_decl(Decl *d) {
  assert(d->kind == DECL_TYPE);
  resolve_type(d->type);
}

void resolve_var_decl(Decl *d) {
  assert(d->kind == DECL_VAR);
  resolve_type(d->type);
}

void resolve_param_decl(Decl *d) {
  assert(d->kind == DECL_PARAM);
  resolve_type(d->type);
}

void resolve_varparam_decl(Decl *d) {
  assert(d->kind == DECL_VARPARAM);
  assert(0);
}

void resolve_proc_decl(Decl *d) { assert(d->kind == DECL_PROC); }

void resolve_decl(Decl *d) {
  switch (d->state) {
    case DECLSTATE_UNRESOLVED:
      printf("%s resolving\n", d->name);
      d->state = DECLSTATE_RESOLVING;
      switch (d->kind) {
        case DECL_INCOMPLETE:
          errorloc(d->loc, "Declaration incomplete for %s", d->name);
          break;
        case DECL_IMPORT:
          assert(0);
          break;
        case DECL_CONST:
          resolve_const_decl(d);
          break;
        case DECL_TYPE:
          resolve_type_decl(d);
          break;
        case DECL_VAR:
          resolve_var_decl(d);
          break;
        case DECL_PARAM:
          resolve_param_decl(d);
          break;
        case DECL_VARPARAM:
          resolve_varparam_decl(d);
          break;
        case DECL_PROC:
          resolve_proc_decl(d);
          break;
        default:
          assert(0);
          break;
      }
      printf("%s resolution done\n", d->name);
      d->state = DECLSTATE_RESOLVED;
      break;
    case DECLSTATE_RESOLVING:
      errorloc(d->loc, "Circular reference for %s", d->name);
      break;
    case DECLSTATE_RESOLVED:
      printf("%s: already resolved\n", d->name);
      break;
    default:
      assert(0);
      break;
  }
}

// Can rhs be assigned to lhs
bool is_assignable(Expr *lhs, Expr *rhs) {
  if (!lhs->is_assignable) {
    errorloc(lhs->loc, "Cannot assign");
  }
  if (lhs->type == rhs->type) {
    return true;
  }
  if (lhs->type->kind == TYPE_POINTER && rhs->type == &nilType) {
    return true;
  }
  if (lhs->type->kind == TYPE_PROCEDURE && rhs->type == &nilType) {
    return true;
  }
  if (lhs->type == &charType && is_one_char_string(rhs)) {
    return true;
  }
  return false;
}

void resolve_boolean_expr(Expr *e) {
  resolve_expr(e);
  if (e->type != &booleanType) {
    errorloc(e->loc, "BOOLEAN expected, got %s", e->type->name);
  }
}

void resolve_elseifs(ElseIf *elseifs) {
  for (size_t i = 0; i < buf_len(elseifs); i++) {
    resolve_boolean_expr(elseifs[i].cond);
    resolve_statements(elseifs[i].body);
  }
}

void resolve_statements(Statement *body) {
  for (size_t i = 0; i < buf_len(body); i++) {
    switch (body[i].kind) {
      case STMT_UNKNOWN:
        assert(0);
        break;
      case STMT_IF:
        resolve_boolean_expr(body[i].if_stmt.cond);
        resolve_statements(body[i].if_stmt.then_clause);
        resolve_elseifs(body[i].if_stmt.elseifs);
        resolve_statements(body[i].if_stmt.else_clause);
        break;
      case STMT_CASE:
        assert(0);
        break;
      case STMT_WHILE:
        resolve_boolean_expr(body[i].while_stmt.cond);
        resolve_statements(body[i].while_stmt.body);
        resolve_elseifs(body[i].while_stmt.elseifs);
        break;
      case STMT_REPEAT:
        assert(0);
        break;
      case STMT_FOR:
        assert(0);
        break;
      case STMT_ASSIGNMENT:
        resolve_expr(body[i].assignment_stmt.lvalue);
        resolve_expr(body[i].assignment_stmt.rvalue);
        if (!is_assignable(body[i].assignment_stmt.lvalue,
                           body[i].assignment_stmt.rvalue)) {
          errorloc(body[i].loc, "Incompatible types for assignment");
        }
        break;
      case STMT_PROCCALL:
        resolve_proc_call(body[i].proc_call_stmt.proc,
                          body[i].proc_call_stmt.args);
        break;
      case STMT_EMPTY:
        break;
      default:
        assert(0);
        break;
    }
  }
}

void resolve_procedure_body(Decl *procDecl) {
  assert(procDecl);
  assert(procDecl->type);
  assert(procDecl->type->kind == TYPE_PROCEDURE);

  Type *procReturnType = procDecl->type->procedure_type.return_type;
  int oldScope = resolve_scope_enter();
  resolve_scope_push(procDecl->proc_decl.decls);
  resolve_statements(procDecl->proc_decl.body);
  if (procReturnType) {
    resolve_expr(procDecl->proc_decl.ret_val);
    if (procReturnType != procDecl->proc_decl.ret_val->type) {
      errorloc(procDecl->proc_decl.ret_val->loc,
               "RETURN type %s does not match declared type %s",
               procDecl->proc_decl.ret_val->type->name, procReturnType->name);
    }
  } else {
    if (procDecl->proc_decl.ret_val) {
      errorloc(procDecl->proc_decl.ret_val->loc, "RETURN value unexpected");
    }
  }
  resolve_decls(procDecl->proc_decl.decls);
  resolve_scope_leave(oldScope);
}

void resolve_decls(Decl *decls) {
  for (size_t i = 0; i < buf_len(decls); i++) {
    printf("%s: ", decls[i].name);
    switch (decls[i].state) {
      case DECLSTATE_RESOLVED:
        printf("RESOLVED\n");
        if (decls[i].kind == DECL_PROC) {
          resolve_procedure_body(decls + i);
        }
        break;
      case DECLSTATE_RESOLVING:
        printf("INCOMPLETE\n");
        break;
      case DECLSTATE_UNRESOLVED:
        printf("NOT REACHED\n");
        break;
      default:
        assert(0);
        break;
    }
  }
}

void resolve_module(Module *m) {
  int scopeIndex = resolve_scope_enter();
  resolve_scope_push(m->decls);
  resolve_statements(m->body);
  resolve_decls(m->decls);
  resolve_scope_leave(scopeIndex);
}

void resolve_test_file(void) {
  Scope globalScope;
  globalScope.decls = NULL;
  enter_scope(&globalScope, "test");
  init_global_types();
  init_global_defs();

  Module *m = parse_test_file("FibFact.Mod");
  resolve_module(m);
  exit_scope("test");
  assert(current_scope == NULL);
}

void resolve_test(void) {
  Scope globalScope;
  globalScope.decls = NULL;
  enter_scope(&globalScope, "test");
  init_global_types();
  init_global_defs();
  init_stream(
      "",
      "MODULE abc;\n"
      "CONST\n"
      "  one* = +1;\n"
      "  minusone* = -1h;\n"
      "  oneF* = 1.0;\n"
      "  minusoneF* = -1.0;\n"
      "  str = \"Howdy\";\n"
      "  kBoolT = TRUE;\n"
      "  kBoolF = FALSE;\n"
      "  kNil = NIL;\n"
      "  kEmptySet = {};\n"
      "  kOneSet = {1};\n"
      "  kFiveEltSet0 = {1, 6,7,9, 21..27};\n"
      "  kFourEltSet1 = {1, 6,7,9};\n"
      "  kFourEltSet2 = -{1, 6,7,9};\n"
      "  kSetTestSet2 = {2 .. 8, 22 .. 25};\n"
      "  k=1*2+3*4;\n"
      "  minusTwo = 100 - 102;\n"
      "  minusTwoF = 100.0 - 102.0;\n"
      "  minusTwoS = {3, 4, 8, 10} - {4, 8};\n"
      "  SixFactorial = 1*2*3*4*5*6;\n"
      "  SeventyTwo = 720 / 10;\n"
      "  OneHalf = 10.0 / 20.0;\n"
      "  Yes = 3 > 2;\n"
      "  No = 3 < 2;\n"
      "  SixFactorialF = 1.0*2.0*3.0*4.0*5.0*6.0;\n"
      "  Two = one + one;\n"
      "  Four = Two + Two;\n"
      "  kSetX = kOneSet + {27};\n"
      "TYPE\n"
      "  R1 = RECORD a, b, c :INTEGER END;\n"
      "  P1 = POINTER TO R1;\n"
      "  A1 = ARRAY 10, 20, SeventyTwo, 40 OF INTEGER;\n"
      "  A2 = ARRAY 10 OF ARRAY 20 OF ARRAY SeventyTwo OF ARRAY 40 OF "
      "INTEGER;\n"
      "  P2 = POINTER TO R2;\n"
      "  R2 = RECORD q :CHAR; next :P2; a :ARRAY Four OF CHAR; END; \n"
      "VAR\n"
      "  unused: BYTE;\n"
      "  aa :A1;\n"
      "  bb :BOOLEAN;\n"
      "  cc :CHAR;\n"
      "  ii :INTEGER;\n"
      "PROCEDURE Wow; END Wow;"
      "PROCEDURE Wow2(x :INTEGER); BEGIN x := ii; Wow; Wow; Wow END Wow2;\n"
      "PROCEDURE Incr(x :INTEGER):INTEGER; BEGIN RETURN x + 1 END Incr;\n"
      "BEGIN\n"
      "  bb := cc = \"0\"; bb := kEmptySet = kOneSet; bb := cc <= cc;\n"
      "  Wow2(ii);\n"
      "  cc := 041X;\n"
      "  ii := Incr(one) + Incr(minusone);\n"
      "  ii := one; ii := minusone + Four; aa[SixFactorial, 0, 0, 0] := 3\n"
      "END abc.");
  next_token();
  Module *m = parse_module();
  int scopeIndex = resolve_scope_enter();
  resolve_scope_push(m->decls);
  resolve_statements(m->body);
  resolve_decls(m->decls);
  resolve_scope_leave(scopeIndex);
  exit_scope("test");
  assert(current_scope == NULL);
  resolve_test_file();
}
