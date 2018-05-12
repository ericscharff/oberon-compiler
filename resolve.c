void resolve_expr(Expr *e);

void eval_unary_expr(Expr *e, Expr *expr) {
  assert(e);
  assert(expr);
  assert(expr->is_const);
  assert(expr->type);

  e->is_const = true;
  switch (e->unary.op) {
    case TOKEN_PLUS:
      if (expr->type == &integerType || expr->type == &realType) {
        e->val = expr->val;
        e->type = expr->type;
      } else {
        errorloc(expr->loc, "Unary plus requires INTEGER or REAL, got %s",
                 expr->type->name);
      }
      break;
    case TOKEN_MINUS:
      if (expr->type == &integerType) {
        e->val.kind = VAL_INTEGER;
        e->type = expr->type;
        e->val.iVal = -expr->val.iVal;
      } else if (expr->type == &realType) {
        e->val.kind = VAL_REAL;
        e->type = expr->type;
        e->val.rVal = -expr->val.rVal;
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
  assert(e->kind == EXPR_UNARY);
  resolve_expr(e->unary.expr);
  if (e->unary.expr->is_const) {
    eval_unary_expr(e, e->unary.expr);
  } else {
    assert(0);
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
    case TOKEN_STAR:
      if (lhs->type == &integerType) {
        e->val.kind = VAL_INTEGER;
        e->val.iVal = lhs->val.iVal * rhs->val.iVal;
      } else if (lhs->type == &realType) {
        e->val.kind = VAL_REAL;
        e->val.rVal = lhs->val.rVal * rhs->val.rVal;
      } else {
        assert(0);
      }
      break;
    default:
      assert(0);
      break;
  }
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
        errorloc(e->loc, "Types %s and %s must match for operator %s", lhs->type->name, rhs->type->name, op_name(e->binary.op));
      }
      if (lhs->type == &integerType || lhs->type == &realType || lhs->type == &setType || lhs->type == &byteType) {
        e->type = lhs->type;
      } else {
        errorloc(e->loc, "INTEGER, REAL, SET, or BYTE expected for operator %s", op_name(e->binary.op));
      }
      break;
    case TOKEN_DIV:
    case TOKEN_MOD:
      if (lhs->type != rhs->type) {
        errorloc(e->loc, "Types %s and %s must match for operator %s", lhs->type->name, rhs->type->name, op_name(e->binary.op));
      }
      if (lhs->type == &integerType) {
        e->type = lhs->type;
      } else {
        errorloc(e->loc, "INTEGER expected for operator %s", op_name(e->binary.op));
      }
      break;
    case TOKEN_LT:
    case TOKEN_LTEQ:
    case TOKEN_GT:
    case TOKEN_GTEQ:
      if (!is_equivalent(lhs->type, rhs->type)) {
        errorloc(e->loc, "Types %s and %s must match for operator %s", lhs->type->name, rhs->type->name, op_name(e->binary.op));
      }
      if (lhs->type == &integerType || lhs->type == &realType || lhs->type == &charType || lhs->type == &stringType || is_string_type(lhs->type)) {
        e->type = &booleanType;
      } else {
        errorloc(e->loc, "INTEGER, REAL, CHAR, or STRING expected for operator %s", op_name(e->binary.op));
      }
      break;
    case TOKEN_EQ:
    case TOKEN_POUND:
      if (!is_equivalent(lhs->type, rhs->type)) {
        errorloc(e->loc, "Types %s and %s must match for operator %s", lhs->type->name, rhs->type->name, op_name(e->binary.op));
      }
      e->type = &booleanType;
      break;
    case TOKEN_IN:
      if (lhs->type != &integerType) {
        errorloc(e->loc, "left side of IN must be INTEGER, not %s", lhs->type->name);
      }
      if (rhs->type != &setType) {
        errorloc(e->loc, "right side of IN must be SET, not %s", rhs->type->name);
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
      assert(0);
      break;
    case EXPR_PROCCALL:
      assert(0);
      break;
    case EXPR_FIELDREF:
      assert(0);
      break;
    case EXPR_POINTERDEREF:
      assert(0);
      break;
    case EXPR_ARRAYREF:
      assert(0);
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
  assert(0);
}

void resolve_var_decl(Decl *d) {
  assert(d->kind == DECL_VAR);
  assert(0);
}

void resolve_param_decl(Decl *d) {
  assert(d->kind == DECL_PARAM);
  assert(0);
}

void resolve_varparam_decl(Decl *d) {
  assert(d->kind == DECL_VARPARAM);
  assert(0);
}

void resolve_proc_decl(Decl *d) {
  assert(d->kind == DECL_PROC);
  assert(0);
}

void resolve_decls(Decl *decls) {
  for (size_t i = 0; i < buf_len(decls); i++) {
    switch (decls[i].state) {
      case DECLSTATE_UNRESOLVED:
        decls[i].state = DECLSTATE_RESOLVING;
        switch (decls[i].kind) {
          case DECL_INCOMPLETE:
            errorloc(decls[i].loc, "Declaration incomplete for %s",
                     decls[i].name);
            break;
          case DECL_IMPORT:
            assert(0);
            break;
          case DECL_CONST:
            resolve_const_decl(&decls[i]);
            break;
          case DECL_TYPE:
            resolve_type_decl(&decls[i]);
            break;
          case DECL_VAR:
            resolve_var_decl(&decls[i]);
            break;
          case DECL_PARAM:
            resolve_param_decl(&decls[i]);
            break;
          case DECL_VARPARAM:
            resolve_varparam_decl(&decls[i]);
            break;
          case DECL_PROC:
            resolve_proc_decl(&decls[i]);
            break;
          default:
            assert(0);
            break;
        }
        decls[i].state = DECLSTATE_RESOLVED;
        break;
      case DECLSTATE_RESOLVING:
        errorloc(decls[i].loc, "Circular reference for %s", decls[i].name);
        break;
      case DECLSTATE_RESOLVED:
        break;
      default:
        assert(0);
        break;
    }
  }
}

void resolve_test(void) {
  Scope globalScope;
  enter_scope(&globalScope);
  init_global_types();
  init_global_defs();
  init_stream("",
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
              "  kOneSixSet = {1, 6,7,9};\n"
              "  k=1*2+3*4;\n"
              "  SixFactorial = 1*2*3*4*5*6;\n"
              "  SixFactorialF = 1.0*2.0*3.0*4.0*5.0*6.0;\n"
              "END abc.");
  next_token();
  Module *m = parse_module();
  resolve_decls(m->decls);
  exit_scope();
  assert(current_scope == NULL);
}
