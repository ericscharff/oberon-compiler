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
        assert(0);
        break;
      case TYPE_BYTE:
        assert(0);
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
        assert(0);
        break;
      case TYPE_STRING:
        assert(0);
        break;
      case TYPE_POINTER:
        gen_str("struct ");
        gen_type(t->pointer_type.element_type, "", "");
        gen_str(" *");
        gen_qname(packageName, name);
        break;
      case TYPE_ARRAY:
        gen_type(t->array_type.element_type, packageName, name);
        gen_str("[");
        if (t->array_type.num_elements_expr) {
          gen_expr(t->array_type.num_elements_expr);
        }
        gen_str("]");
        break;
      case TYPE_RECORD:
        gen_str("struct ");
        gen_qname(packageName, name);
        gen_str(" {\n");
        codegenIndent++;
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

void gen_val(Val val) {
  switch (val.kind) {
    case VAL_UNKNOWN:
      assert(0);
      break;
    case VAL_INTEGER:
      buf_printf(codegenBuf, "%d", val.iVal);
      break;
    case VAL_REAL:
      buf_printf(codegenBuf, "%f", val.rVal);
      break;
    case VAL_SET:
      buf_printf(codegenBuf, "%d", val.setVal);
      break;
    case VAL_BOOLEAN:
      buf_printf(codegenBuf, "%d", val.bVal);
      break;
    case VAL_STRING:
      buf_printf(codegenBuf, "\"%s\"", val.sVal);
      break;
    case VAL_NIL:
      gen_str("0");
      break;
    default:
      assert(0);
      break;
  }
}

void gen_binary_expr(TokenKind op, Expr *lhs, Expr *rhs) {
  assert(lhs);
  assert(rhs);
  assert(op);
  gen_str("(");
  gen_expr(lhs);
  // TODO - op names aren't necessarily the token names
  // TODO - set binary operators are handled specially in C
  // TODO - string binary operators are treaded specially in C
  gen_str(" ");
  gen_str(token_kind_names[op]);
  gen_str(" ");
  gen_expr(rhs);
  gen_str(")");
}

void gen_proccall(Expr *proc, Expr **args) {
  assert(proc);
  gen_expr(proc);
  gen_str("(");
  for (size_t i = 0; i < buf_len(args); i++) {
    gen_expr(args[i]);
    if (i != buf_len(args) - 1) {
      gen_str(", ");
    }
  }
  gen_str(")");
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
        assert(0);
        break;
      case EXPR_BINARY:
        gen_binary_expr(e->binary.op, e->binary.lhs, e->binary.rhs);
        break;
      case EXPR_IDENTREF:
        gen_qname(e->identref.package_name, e->identref.name);
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
        assert(0);
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
    gen_expr(elseifs[i].cond);
    gen_str("{\n");
    codegenIndent++;
    gen_statements(elseifs[i].body);
    codegenIndent--;
  }
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
      gen_expr(s->if_stmt.cond);
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
      assert(0);
      break;
    case STMT_WHILE:
      gen_str("while ");
      assert(!s->while_stmt.elseifs);
      gen_expr(s->while_stmt.cond);
      gen_str(" {\n");
      codegenIndent++;
      gen_statements(s->while_stmt.body);
      codegenIndent--;
      geni();
      gen_str("}\n");
      break;
    case STMT_REPEAT:
      assert(0);
      break;
    case STMT_FOR:
      assert(0);
      break;
    case STMT_ASSIGNMENT:
      gen_expr(s->assignment_stmt.lvalue);
      gen_str(" = ");
      gen_expr(s->assignment_stmt.rvalue);
      gen_str(";\n");
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
      gen_str("#define ");
      gen_qname(d->package_name, d->name);
      gen_str(" (");
      gen_expr(d->const_val.expr);
      gen_str(")\n");
      break;
    case DECL_TYPE:
      assert(0);
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
          assert(!d->type->procedure_type.params[i].is_var_parameter);
          gen_type(d->type->procedure_type.params[i].type, NULL,
                   d->type->procedure_type.params[i].name);
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
                 d->proc_decl.decls[i].kind == DECL_PARAM);
          if (d->proc_decl.decls[i].kind == DECL_VAR) {
            assert(!d->proc_decl.decls[i].package_name[0]);
            geni();
            gen_type(d->proc_decl.decls[i].type,
                     d->proc_decl.decls[i].package_name,
                     d->proc_decl.decls[i].name);
            gen_str(";\n");
          }
        }
      }
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
  for (size_t i = 0; i < buf_len(types); i++) {
    gen_typedef(types[i], types[i]->package_name, types[i]->name);
  }
  for (int i = buf_len(decls) - 1; i >= 0; i--) {
    gen_decl(decls[i]);
  }
}

void gen_test(void) {
  resolve_test_file();
  generate_c_code(gReachableTypes, gReachableDecls);
  puts(codegenBuf);
}
