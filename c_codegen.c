void gen_statements(Statement *s);
void gen_expr(Expr *e);

char *codegenBuf = NULL;
int codegenIndent = 0;

void gen_str(const char *s) { buf_printf(codegenBuf, "%s", s); }

void gen_qname(const char *packageName, const char *name) {
  if (packageName && packageName[0]) {
    gen_str(packageName);
    gen_str("_");
  }
  gen_str(name);
}

void geni(void) {
  for (int i = 0; i < codegenIndent; i++) {
    gen_str("  ");
  }
}

void gen_type(Type *t, const char *packageName, const char *name) {
  if (t->name) {
    gen_qname(t->package_name, t->name);
    gen_str(" ");
    gen_qname(packageName, name);
  } else {
    switch (t->kind) {
      case TYPE_UNKNOWN:
        assert(0);
        break;
      case TYPE_INCOMPLETE:
        assert(0);
        break;
      case TYPE_BOOLEAN:
        gen_str("bool ");
        gen_qname(packageName, name);
        break;
      case TYPE_BYTE:
        gen_str("int ");
        gen_qname(packageName, name);
        break;
      case TYPE_CHAR:
        gen_str("char ");
        gen_qname(packageName, name);
        break;
      case TYPE_INTEGER:
        gen_str("int ");
        gen_qname(packageName, name);
        break;
      case TYPE_REAL:
        gen_str("float ");
        gen_qname(packageName, name);
        break;
      case TYPE_SET:
        gen_str("int ");
        gen_qname(packageName, name);
        break;
      case TYPE_STRING:
        assert(0);
        break;
      case TYPE_POINTER:
        if (t->pointer_type.element_type->kind == TYPE_RECORD) {
          gen_str("struct ");
        }
        gen_type(t->pointer_type.element_type, "", "");
        gen_str(" *");
        gen_qname(packageName, name);
        break;
      case TYPE_ARRAY: {
        Type *origType = t;
        while (t->kind == TYPE_ARRAY) {
          t = t->array_type.element_type;
        }
        gen_type(t, packageName, name);
        t = origType;
        while (t->kind == TYPE_ARRAY) {
          gen_str("[");
          if (t->array_type.num_elements_expr) {
            gen_expr(t->array_type.num_elements_expr);
          }
          gen_str("]");
          t = t->array_type.element_type;
        }
        break;
      }
      case TYPE_RECORD:
        gen_str("struct ");
        gen_qname(packageName, name);
        gen_str(" {\n");
        codegenIndent++;
        if (t->needs_typeinfo) {
          geni();
          gen_str("oberon_typeid _tid;\n");
        }
        for (size_t i = 0; i < buf_len(t->record_type.fields); i++) {
          geni();
          gen_type(t->record_type.fields[i].type, NULL,
                   t->record_type.fields[i].name);
          gen_str(";\n");
        }
        codegenIndent--;
        geni();
        gen_str("} ");
        gen_qname(packageName, name);
        break;
      case TYPE_PROCEDURE:
        if (t->procedure_type.return_type) {
          gen_type(t->procedure_type.return_type, "", "");
        } else {
          gen_str("void");
        }
        gen_str(" (*");
        gen_qname(packageName, name);
        gen_str(")(");
        if (t->procedure_type.params) {
          for (size_t i = 0; i < buf_len(t->procedure_type.params); i++) {
            gen_type(t->procedure_type.params[i].type, "", "");
            if (t->procedure_type.params[i].type->kind == TYPE_RECORD) {
              gen_str("*");
            }
            if (i != buf_len(t->procedure_type.params) - 1) {
              gen_str(", ");
            }
          }
        } else {
          gen_str("void");
        }
        gen_str(")");
        break;
      default:
        assert(0);
        break;
    }
  }
}

void gen_typedef(Type *t, const char *packageName, const char *name) {
  assert(t);
  if (packageName && name) {
    geni();
    gen_str("typedef ");
    Type nakedType = *t;
    nakedType.package_name = NULL;
    nakedType.name = NULL;
    gen_type(&nakedType, packageName, name);
    gen_str(";\n");
  }
}

const char *sanitize_string(const char *s) {
  assert(strlen(s) < 1024);
  static char buf[1024];
  char *p = buf;
  while (*s) {
    if (*s == '\\') {
      *p++ = '\\';
      *p++ = '\\';
    } else if (*s == '"') {
      *p++ = '\\';
      *p++ = '"';
    } else if (*s == '\n') {
      *p++ = '\\';
      *p++ = 'n';
    } else if (*s == '\t') {
      *p++ = '\\';
      *p++ = 't';
    } else {
      *p++ = *s;
    }
    s++;
  }
  *p = '\0';
  return buf;
}

void gen_val(Val val) {
  switch (val.kind) {
    case VAL_UNKNOWN:
      assert(0);
      break;
    case VAL_INTEGER:
      buf_printf(codegenBuf, "%d", val.iVal);
      break;
    case VAL_REAL:
      buf_printf(codegenBuf, "%g", val.rVal);
      break;
    case VAL_SET:
      buf_printf(codegenBuf, "%d", val.setVal);
      break;
    case VAL_BOOLEAN:
      buf_printf(codegenBuf, "%d", val.bVal);
      break;
    case VAL_STRING:
      buf_printf(codegenBuf, "\"%s\"", sanitize_string(val.sVal));
      break;
    case VAL_NIL:
      gen_str("0");
      break;
    default:
      assert(0);
      break;
  }
}

void gen_char_lit(char c) {
  if (isgraph(c) && c != '\'' && c != '\\') {
    buf_printf(codegenBuf, "'%c'", c);
  } else {
    buf_printf(codegenBuf, "'\\%o'", c);
  }
}

void gen_unary_expr(TokenKind op, Expr *expr) {
  assert(expr);
  if (op == TOKEN_MINUS) {
    if (expr->type->kind == TYPE_SET) {
      gen_str("~");
    } else {
      gen_str("-");
    }
    gen_str("(");
    gen_expr(expr);
    gen_str(")");
  } else if (op == TOKEN_PLUS) {
    gen_expr(expr);
  } else if (op == TOKEN_TILDE) {
    gen_str("!(");
    gen_expr(expr);
    gen_str(")");
  } else if (op == TOKEN_AS_SET_ELT) {
    gen_str("(1 <<");
    gen_expr(expr);
    gen_str(")");
  } else {
    assert(0);
  }
}

void gen_binary_c(const char *cOp, Expr *lhs, Expr *rhs, bool coerceToChar) {
  gen_str("(");
  if (coerceToChar && lhs->type->kind == TYPE_STRING) {
    gen_char_lit(lhs->val.sVal[0]);
  } else {
    gen_expr(lhs);
  }
  gen_str(" ");
  gen_str(cOp);
  gen_str(" ");
  if (coerceToChar && rhs->type->kind == TYPE_STRING) {
    gen_char_lit(rhs->val.sVal[0]);
  } else {
    gen_expr(rhs);
  }
  gen_str(")");
}

void gen_strcmp(Expr *lhs, Expr *rhs, const char *epilog) {
  gen_str("(strcmp(");
  gen_expr(lhs);
  gen_str(", ");
  gen_expr(rhs);
  gen_str(") ");
  gen_str(epilog);
  gen_str(")");
}

void gen_binary_expr(TokenKind op, Expr *lhs, Expr *rhs) {
  assert(lhs);
  assert(rhs);
  bool isSet = lhs->type == &setType;
  bool isString = is_string_type(lhs->type) && is_string_type(rhs->type);
  bool coerceToChar =
      (lhs->type->kind == TYPE_CHAR && rhs->type->kind == TYPE_STRING) ||
      (lhs->type->kind == TYPE_STRING && rhs->type->kind == TYPE_CHAR);

  switch (op) {
    case TOKEN_PLUS:
      gen_binary_c(isSet ? "|" : "+", lhs, rhs, coerceToChar);
      break;
    case TOKEN_MINUS:
      gen_binary_c(isSet ? "& ~" : "-", lhs, rhs, coerceToChar);
      break;
    case TOKEN_STAR:
      gen_binary_c(isSet ? "&" : "*", lhs, rhs, coerceToChar);
      break;
    case TOKEN_SLASH:
      gen_binary_c(isSet ? "^" : "/", lhs, rhs, coerceToChar);
      break;
    case TOKEN_DIV:
      gen_binary_c("/", lhs, rhs, coerceToChar);
      break;
    case TOKEN_MOD:
      gen_binary_c("%", lhs, rhs, coerceToChar);
      break;
    case TOKEN_XOR:
      gen_binary_c("^", lhs, rhs, coerceToChar);
      break;
    case TOKEN_AMP:
      gen_binary_c("&&", lhs, rhs, coerceToChar);
      break;
    case TOKEN_OR:
      gen_binary_c("||", lhs, rhs, coerceToChar);
      break;
    case TOKEN_DOTDOT:
      gen_str("make_set_range(");
      gen_expr(lhs);
      gen_str(", ");
      gen_expr(rhs);
      gen_str(")");
      break;
    case TOKEN_LT:
      if (isString) {
        gen_strcmp(lhs, rhs, "< 0");
      } else {
        gen_binary_c("<", lhs, rhs, coerceToChar);
      }
      break;
    case TOKEN_LTEQ:
      if (isString) {
        gen_strcmp(lhs, rhs, "<= 0");
      } else {
        gen_binary_c("<=", lhs, rhs, coerceToChar);
      }
      break;
    case TOKEN_GT:
      if (isString) {
        gen_strcmp(lhs, rhs, "> 0");
      } else {
        gen_binary_c(">", lhs, rhs, coerceToChar);
      }
      break;
    case TOKEN_GTEQ:
      if (isString) {
        gen_strcmp(lhs, rhs, ">= 0");
      } else {
        gen_binary_c(">=", lhs, rhs, coerceToChar);
      }
      break;
    case TOKEN_EQ:
      if (isString) {
        gen_strcmp(lhs, rhs, "== 0");
      } else {
        gen_binary_c("==", lhs, rhs, coerceToChar);
      }
      break;
    case TOKEN_POUND:
      if (isString) {
        gen_strcmp(lhs, rhs, "!= 0");
      } else {
        gen_binary_c("!=", lhs, rhs, coerceToChar);
      }
      break;
    case TOKEN_IN:
      gen_str("((1 << ");
      gen_expr(lhs);
      gen_str(") & ");
      gen_expr(rhs);
      gen_str(")");
      break;
    case TOKEN_IS: {
      Expr fieldRef;
      Expr deref;
      fieldRef.kind = EXPR_FIELDREF;
      fieldRef.fieldref.field_name = "_tid";
      fieldRef.fieldref.expr = lhs;
      fieldRef.is_const = false;
      if (lhs->type->kind == TYPE_POINTER) {
        deref.kind = EXPR_POINTERDEREF;
        deref.pointerderef.expr = lhs;
        deref.is_const = false;
        fieldRef.fieldref.expr = &deref;
      }
      gen_str("does_type_extend(");
      gen_expr(&fieldRef);
      if (rhs->type->kind == TYPE_POINTER) {
        buf_printf(codegenBuf, ", %d)",
                   rhs->type->pointer_type.element_type->type_id);
      } else {
        buf_printf(codegenBuf, ", %d)", rhs->type->type_id);
      }
      break;
    }
    default:
      assert(0);
      break;
  }
}

void gen_paren_expr(Expr *e) {
  if (e->kind == EXPR_BINARY) {
    gen_expr(e);
  } else {
    gen_str("(");
    gen_expr(e);
    gen_str(")");
  }
}

void gen_builtin_procedure(Expr *proc, Expr **args) {
  if (proc->type->name == builtin_ord) {
    if (is_one_char_string(args[0])) {
      gen_char_lit(args[0]->val.sVal[0]);
    } else {
      gen_expr(args[0]);
    }
  } else if (proc->type->name == builtin_chr) {
    gen_str("((char)");
    gen_expr(args[0]);
    gen_str(")");
  } else if (proc->type->name == builtin_abs) {
    gen_str("oberon_abs");
    gen_paren_expr(args[0]);
  } else if (proc->type->name == builtin_dec) {
    // DEC(x) --> x--
    // DEC(x, n) --> x -= n
    gen_expr(args[0]);
    if (buf_len(args) == 2) {
      gen_str(" -= ");
      gen_expr(args[1]);
    } else {
      gen_str("--");
    }
  } else if (proc->type->name == builtin_inc) {
    // INC(x) --> x++
    // INC(x, n) --> x += n
    gen_expr(args[0]);
    if (buf_len(args) == 2) {
      gen_str(" += ");
      gen_expr(args[1]);
    } else {
      gen_str("++");
    }
  } else if (proc->type->name == builtin_new) {
    // NEW(p) --> p = malloc(sizeof(<P ELEMENT TYPE>))
    Expr *p = args[0];
    gen_expr(p);
    gen_str(" = malloc(sizeof(");
    gen_qname(p->type->pointer_type.element_type->package_name,
              p->type->pointer_type.element_type->name);
    gen_str("))");
    if (p->type->pointer_type.element_type->needs_typeinfo) {
      gen_str("; ");
      gen_expr(p);
      buf_printf(codegenBuf, "->_tid = %d",
                 p->type->pointer_type.element_type->type_id);
    }
  } else {
    assert(0);
  }
}

bool is_record(Type *t) { return t->kind == TYPE_RECORD; }

bool is_pointer(Type *t) { return t->kind == TYPE_POINTER; }

void gen_lengthof(Expr *e) {
  assert(e->type->kind == TYPE_ARRAY || e->type->kind == TYPE_STRING);
  if (e->type->kind == TYPE_STRING) {
    buf_printf(codegenBuf, "%d", strlen(e->val.sVal));
  } else if (e->type->kind == TYPE_ARRAY && e->type->array_type.num_elements_expr) {
    gen_expr(e->type->array_type.num_elements_expr);
  } else if (e->kind == EXPR_IDENTREF) {
    gen_qname(e->identref.package_name, e->identref.name);
    gen_str("__len");
  } else {
    assert(0);
  }
}

void gen_proccall(Expr *proc, Expr **args) {
  assert(proc);
  if (proc->type->kind == TYPE_BUILTIN_PROCEDURE) {
    gen_builtin_procedure(proc, args);
  } else {
    gen_expr(proc);
    gen_str("(");
    for (size_t i = 0; i < buf_len(args); i++) {
      bool recordFormal = is_record(proc->type->procedure_type.params[i].type);
      bool pointerFormal =
          is_pointer(proc->type->procedure_type.params[i].type);
      bool needCast =
          (recordFormal &&
           proc->type->procedure_type.params[i].type != args[i]->type) ||
          (pointerFormal &&
           proc->type->procedure_type.params[i].type != args[i]->type);
      if (needCast) {
        gen_str("(");
        gen_type(proc->type->procedure_type.params[i].type, "", "");
        if (recordFormal) {
          gen_str("*)(");
        } else {
          gen_str(")(");
        }
      }
      if (proc->type->procedure_type.params[i].is_var_parameter ||
          recordFormal) {
        gen_str("&(");
      }
      gen_expr(args[i]);
      if (proc->type->procedure_type.params[i].is_var_parameter ||
          recordFormal) {
        gen_str(")");
      }
      if (needCast) {
        gen_str(")");
      }
      if (proc->type->procedure_type.params[i].is_open_array) {
        gen_str(", ");
        gen_lengthof(args[i]);
      }
      if (i != buf_len(args) - 1) {
        gen_str(", ");
      }
    }
    gen_str(")");
  }
}

void gen_expr(Expr *e) {
  assert(e);
  if (e->is_const) {
    gen_val(e->val);
  } else {
    switch (e->kind) {
      case EXPR_UNKNOWN:
        assert(0);
        break;
      case EXPR_UNARY:
        gen_unary_expr(e->unary.op, e->unary.expr);
        break;
      case EXPR_BINARY:
        gen_binary_expr(e->binary.op, e->binary.lhs, e->binary.rhs);
        break;
      case EXPR_IDENTREF:
        if (e->is_var_param || (e->is_param && is_record(e->type))) {
          gen_str("(*");
        }
        gen_qname(e->identref.package_name, e->identref.name);
        if (e->is_var_param || (e->is_param && is_record(e->type))) {
          gen_str(")");
        }
        break;
      case EXPR_PROCCALL:
        gen_proccall(e->proccall.proc, e->proccall.args);
        break;
      case EXPR_FIELDREF:
        gen_expr(e->fieldref.expr);
        gen_str(".");
        gen_str(e->fieldref.field_name);
        break;
      case EXPR_POINTERDEREF:
        gen_str("(*");
        gen_expr(e->pointerderef.expr);
        gen_str(")");
        break;
      case EXPR_ARRAYREF:
        gen_expr(e->arrayref.expr);
        gen_str("[");
        gen_expr(e->arrayref.array_index);
        gen_str("]");
        break;
      case EXPR_TYPEGUARD:
        gen_str("((");
        gen_qname(e->typeguard.type->package_name, e->typeguard.type->name);
        gen_str(")");
        gen_expr(e->typeguard.expr);
        gen_str(")");
        break;
      case EXPR_INTEGER:
      case EXPR_REAL:
      case EXPR_STRING:
      case EXPR_NIL:
      case EXPR_TRUE:
      case EXPR_FALSE:
      case EXPR_EMPTYSET:
      default:
        assert(0);
        break;
    }
  }
}

void gen_elseifs(ElseIf *elseifs) {
  for (size_t i = 0; i < buf_len(elseifs); i++) {
    geni();
    gen_str("} else if ");
    gen_paren_expr(elseifs[i].cond);
    gen_str(" {\n");
    codegenIndent++;
    gen_statements(elseifs[i].body);
    codegenIndent--;
  }
}

int get_case_val(Expr *e) {
  assert(e->is_const);
  if (e->val.kind == VAL_INTEGER) {
    return e->val.iVal;
  } else if (e->val.kind == VAL_STRING) {
    return e->val.sVal[0];
  } else {
    assert(0);
  }
  return 0;
}

void gen_case_statement(Statement *s) {
  gen_str("switch ");
  gen_paren_expr(s->case_stmt.cond);
  gen_str(" {\n");
  for (size_t i = 0; i < buf_len(s->case_stmt.case_cases); i++) {
    codegenIndent++;
    for (size_t j = 0; j < buf_len(s->case_stmt.case_cases[i].cond); j++) {
      Expr *e = s->case_stmt.case_cases[i].cond[j];
      int lowVal;
      int highVal;
      if (e->kind == EXPR_BINARY) {
        lowVal = get_case_val(e->binary.lhs);
        highVal = get_case_val(e->binary.rhs);
      } else {
        lowVal = get_case_val(e);
        highVal = lowVal;
      }
      for (int c = lowVal; c <= highVal; c++) {
        geni();
        gen_str("case ");
        if (is_integer_type(s->case_stmt.cond->type)) {
          buf_printf(codegenBuf, "%d:\n", c);
        } else {
          assert(s->case_stmt.cond->type == &charType);
          gen_char_lit(c);
          gen_str(":\n");
        }
      }
    }
    codegenIndent++;
    gen_statements(s->case_stmt.case_cases[i].body);
    geni();
    gen_str("break;\n");
    codegenIndent -= 2;
  }
  geni();
  gen_str("}\n");
}

void gen_statement(Statement *s) {
  assert(s);
  if (s->kind != STMT_EMPTY) {
    geni();
  }
  switch (s->kind) {
    case STMT_UNKNOWN:
      assert(0);
      break;
    case STMT_IF:
      gen_str("if ");
      gen_paren_expr(s->if_stmt.cond);
      gen_str(" {\n");
      codegenIndent++;
      gen_statements(s->if_stmt.then_clause);
      codegenIndent--;
      gen_elseifs(s->if_stmt.elseifs);
      if (s->if_stmt.else_clause) {
        geni();
        gen_str("} else {\n");
        codegenIndent++;
        gen_statements(s->if_stmt.else_clause);
        codegenIndent--;
      }
      geni();
      gen_str("}\n");
      break;
    case STMT_CASE:
      gen_case_statement(s);
      break;
    case STMT_WHILE:
      if (s->while_stmt.elseifs) {
        gen_str("while (1) {\n");
        codegenIndent++;
        geni();
        gen_str("if ");
        gen_expr(s->while_stmt.cond);
        gen_str(" {\n");
        codegenIndent++;
        gen_statements(s->while_stmt.body);
        codegenIndent--;
        gen_elseifs(s->while_stmt.elseifs);
        geni();
        gen_str("} else { break; }\n");
        codegenIndent--;
        geni();
        gen_str("}\n");
      } else {
        gen_str("while ");
        gen_paren_expr(s->while_stmt.cond);
        gen_str(" {\n");
        codegenIndent++;
        gen_statements(s->while_stmt.body);
        codegenIndent--;
        geni();
        gen_str("}\n");
      }
      break;
    case STMT_REPEAT:
      gen_str("do {\n");
      codegenIndent++;
      gen_statements(s->repeat_stmt.body);
      codegenIndent--;
      geni();
      gen_str("} while (!");
      gen_expr(s->repeat_stmt.cond);
      gen_str(");\n");
      break;
    case STMT_FOR:
      gen_str("for (");
      gen_str(s->for_stmt.ident);
      gen_str(" = ");
      gen_expr(s->for_stmt.start);
      gen_str("; ");
      gen_str(s->for_stmt.ident);
      if (s->for_stmt.positive_increment) {
        gen_str(" <= ");
      } else {
        gen_str(" >= ");
      }
      gen_expr(s->for_stmt.end);
      gen_str("; ");
      gen_str(s->for_stmt.ident);
      if (s->for_stmt.increment) {
        gen_str(" += ");
        gen_expr(s->for_stmt.increment);
      } else {
        gen_str("++");
      }
      gen_str(") {\n");
      codegenIndent++;
      gen_statements(s->for_stmt.body);
      codegenIndent--;
      geni();
      gen_str("}\n");
      break;
    case STMT_ASSIGNMENT:
      if (s->assignment_stmt.lvalue->type->kind == TYPE_CHAR &&
          s->assignment_stmt.rvalue->type->kind == TYPE_STRING) {
        assert(s->assignment_stmt.rvalue->is_const);
        gen_expr(s->assignment_stmt.lvalue);
        gen_str(" = ");
        gen_char_lit(s->assignment_stmt.rvalue->val.sVal[0]);
        gen_str(";\n");
      } else if (is_string_type(s->assignment_stmt.lvalue->type) &&
                 is_string_type(s->assignment_stmt.rvalue->type)) {
        gen_str("strncpy(");
        gen_expr(s->assignment_stmt.lvalue);
        gen_str(", ");
        gen_expr(s->assignment_stmt.rvalue);
        gen_str(", sizeof(");
        gen_expr(s->assignment_stmt.lvalue);
        gen_str("));\n");
      } else if (is_record(s->assignment_stmt.lvalue->type)) {
        assert(is_record(s->assignment_stmt.rvalue->type));
        gen_str("memcpy(&(");
        gen_expr(s->assignment_stmt.lvalue);
        gen_str("), &(");
        gen_expr(s->assignment_stmt.rvalue);
        gen_str("), sizeof(");
        gen_expr(s->assignment_stmt.lvalue);
        gen_str("));\n");
      } else {
        bool needsCast =
            (s->assignment_stmt.lvalue->type !=
             s->assignment_stmt.rvalue->type) &&
            (s->assignment_stmt.lvalue->type->kind != TYPE_PROCEDURE);
        gen_expr(s->assignment_stmt.lvalue);
        gen_str(" = ");
        if (needsCast) {
          gen_str("(");
          gen_qname(s->assignment_stmt.lvalue->type->package_name,
                    s->assignment_stmt.lvalue->type->name);
          gen_str(")(");
        }
        gen_expr(s->assignment_stmt.rvalue);
        if (needsCast) {
          gen_str(")");
        }
        gen_str(";\n");
      }
      break;
    case STMT_PROCCALL:
      gen_proccall(s->proc_call_stmt.proc, s->proc_call_stmt.args);
      gen_str(";\n");
      break;
    case STMT_EMPTY:
      break;
    default:
      assert(0);
      break;
  }
}

void gen_statements(Statement *s) {
  for (size_t i = 0; i < buf_len(s); i++) {
    gen_statement(s + i);
  }
}

void gen_init_helper(Type *t, const char *nameSoFar) {
  char newName[1024];
  if (t->needs_typeinfo) {
    geni();
    buf_printf(codegenBuf, "%s._tid = %d;\n", nameSoFar, t->type_id);
  }
  if (t->kind == TYPE_ARRAY && t->array_type.num_elements_expr->val.iVal) {
    for (int i = 0; i < t->array_type.num_elements_expr->val.iVal; i++) {
      snprintf(newName, 1024, "%s[%d]", nameSoFar, i);
      gen_init_helper(t->array_type.element_type, newName);
    }
  }
  if (t->kind == TYPE_RECORD) {
    for (size_t i = 0; i < buf_len(t->record_type.fields); i++) {
      snprintf(newName, 1024, "%s.%s", nameSoFar,
               t->record_type.fields[i].name);
      gen_init_helper(t->record_type.fields[i].type, newName);
    }
  }
}

void gen_initializers(Type *t, const char *packageName, const char *name) {
  char nameSoFar[1024];
  if (packageName && packageName[0]) {
    snprintf(nameSoFar, 1024, "%s_%s", packageName, name);
  } else {
    snprintf(nameSoFar, 1024, "%s", name);
  }
  gen_init_helper(t, nameSoFar);
}

void gen_decl(Decl *d) {
  assert(d);
  geni();
  switch (d->kind) {
    case DECL_UNKNOWN:
      assert(0);
      break;
    case DECL_INCOMPLETE:
      assert(0);
      break;
    case DECL_IMPORT:
      assert(0);
      break;
    case DECL_CONST:
#if 0
      // These are correct, but don't actually get used anywhere
      gen_str("#define ");
      gen_qname(d->package_name, d->name);
      gen_str(" (");
      gen_expr(d->const_val.expr);
      gen_str(")\n");
#endif
      break;
    case DECL_TYPE:
      // Do nothing, typedefs were already generated
      break;
    case DECL_VAR:
      // Only generate global vars
      if (d->package_name && d->package_name[0]) {
        gen_type(d->type, d->package_name, d->name);
        gen_str(";\n");
      }
      break;
    case DECL_PARAM:
      // Don't do anything, handled in procedure gen
      break;
    case DECL_VARPARAM:
      // Don't do anything, handled in procedure gen
      break;
    case DECL_PROC:
      if (d->type->kind == TYPE_BUILTIN_PROCEDURE ||
          d->type->procedure_type.native) {
        // nothing to declare
        break;
      }
      assert(d->type->kind == TYPE_PROCEDURE);
      if (d->type->procedure_type.return_type) {
        gen_qname(d->type->procedure_type.return_type->package_name,
                  d->type->procedure_type.return_type->name);
      } else {
        gen_str("void");
      }
      gen_str(" ");
      gen_qname(d->package_name, d->name);
      if (d->type->procedure_type.params) {
        gen_str("(");
        for (size_t i = 0; i < buf_len(d->type->procedure_type.params); i++) {
          Type *formal = d->type->procedure_type.params[i].type;
          Type varParam;
          // This is an interesting special case. An open array is passed
          // by pointer already. Adding VAR to it simply makes it readonly.
          // Thus, if something is a var param **and** an open array, pretend
          // it isn't a var param. This means tweaking the procedure
          // declaration, to avoid weird things being generated later.
          if (d->type->procedure_type.params[i].is_var_parameter &&
              d->type->procedure_type.params[i].is_open_array) {
            d->type->procedure_type.params[i].is_var_parameter = false;
          }

          if (d->type->procedure_type.params[i].is_var_parameter ||
              is_record(formal)) {
            varParam.kind = TYPE_POINTER;
            varParam.name = NULL;
            varParam.package_name = NULL;
            varParam.pointer_type.element_type = formal;
            formal = &varParam;
          }
          gen_type(formal, NULL, d->type->procedure_type.params[i].name);
          if (d->type->procedure_type.params[i].is_open_array) {
            gen_str(", size_t ");
            gen_qname(NULL, d->type->procedure_type.params[i].name);
            gen_str("__len");
          }
          if (i != buf_len(d->type->procedure_type.params) - 1) {
            gen_str(", ");
          }
        }
        gen_str(") {\n");
      } else {
        gen_str("(void) {\n");
      }
      codegenIndent++;
      for (size_t i = 0; i < buf_len(d->proc_decl.decls); i++) {
        if (d->proc_decl.decls[i].state == DECLSTATE_RESOLVED) {
          assert(d->proc_decl.decls[i].kind == DECL_VAR ||
                 d->proc_decl.decls[i].kind == DECL_VARPARAM ||
                 d->proc_decl.decls[i].kind == DECL_CONST ||
                 d->proc_decl.decls[i].kind == DECL_PARAM);
          if (d->proc_decl.decls[i].kind == DECL_VAR) {
            assert(!d->proc_decl.decls[i].package_name[0]);
            geni();
            gen_type(d->proc_decl.decls[i].type,
                     d->proc_decl.decls[i].package_name,
                     d->proc_decl.decls[i].name);
            gen_str(";\n");
            gen_initializers(d->proc_decl.decls[i].type,
                             d->proc_decl.decls[i].package_name,
                             d->proc_decl.decls[i].name);
          } else if (d->type->procedure_type.params[i].is_open_array) {
            // Generate code to avoid unused var reference
            geni();
            gen_str("(void)");
            gen_qname(d->proc_decl.decls[i].package_name, d->proc_decl.decls[i].name);
            gen_str("__len;\n");
          }
        }
      }
      // DRIBBLE
#if 0
      geni();
      gen_str("puts(\"");
      gen_qname(d->package_name, d->name);
      gen_str("\");\n");
#endif
      // END DRIBBLE
      gen_statements(d->proc_decl.body);
      if (d->proc_decl.ret_val) {
        geni();
        gen_str("return (");
        gen_expr(d->proc_decl.ret_val);
        gen_str(");\n");
      }
      codegenIndent--;
      geni();
      gen_str("}\n\n");
      break;
    default:
      assert(0);
      break;
  }
}

void generate_c_code(Type **types, Decl **decls) {
  gen_str("typedef int oberon_typeid;\n");
  bool need_codegen_inits = false;
  for (size_t i = 0; i < buf_len(types); i++) {
    if (types[i]->needs_typeinfo) {
      need_codegen_inits = true;
      break;
    }
  }
  if (need_codegen_inits) {
    gen_str("oberon_typeid oberon_typeinfos[1024] = {\n");
    for (size_t i = 0; i < buf_len(types); i++) {
      if (types[i]->needs_typeinfo) {
        buf_printf(codegenBuf, "  [%d] = %d,\n", types[i]->type_id,
                   (types[i]->record_type.base_type
                        ? types[i]->record_type.base_type->type_id
                        : 0));
      }
    }
    gen_str("};\n");
  } else {
    gen_str("oberon_typeid oberon_typeinfos[1];\n");
  }
  gen_str("#include \"runtime.c\"\n\n");

  for (size_t i = 0; i < buf_len(types); i++) {
    gen_typedef(types[i], types[i]->package_name, types[i]->name);
  }
  for (size_t i = 0; i < buf_len(decls); i++) {
    gen_decl(decls[i]);
  }
  gen_str("\nint main(void) {\n");
  codegenIndent++;
  for (size_t i = 0; i < buf_len(decls); i++) {
    if (strstr(decls[i]->name, MODULE_INIT_NAME)) {
      geni();
      gen_qname(decls[i]->package_name, decls[i]->name);
      gen_str("();\n");
    }
  }
  geni();
  gen_str("return 0;\n");
  codegenIndent--;
  geni();
  gen_str("}\n");
}

void gen_test(void) {
  resolve_test_file();
  generate_c_code(gReachableTypes, gReachableDecls);
  write_file("out.c", codegenBuf);
  printf("PASS: gen_test\n");
}
