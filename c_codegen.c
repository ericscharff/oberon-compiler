void gen_statements(Statement *s);

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

void gen_type(Type *t) {
  if (t->name) {
    gen_qname(t->package_name, t->name);
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
        gen_str("char");
        break;
      case TYPE_INTEGER:
        gen_str("int");
        break;
      case TYPE_REAL:
        assert(0);
        break;
      case TYPE_SET:
        assert(0);
        break;
      case TYPE_STRING:
        assert(0);
        break;
      case TYPE_POINTER:
        assert(0);
        break;
      case TYPE_ARRAY:
        assert(0);
        break;
      case TYPE_RECORD:
        assert(0);
        break;
      case TYPE_PROCEDURE:
        assert(0);
        break;
      default:
        assert(0);
        break;
    }
  }
}

void gen_typedef(Type *t) {
  assert(t);
  geni();
  gen_str("typedef ");
  gen_type(t);
  gen_str(" ");
  gen_qname(t->package_name, t->name);
  gen_str(";\n");
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

void gen_expr(Expr *e) {
  assert(e);
  if (e->is_const) {
    gen_val(e->val);
  } else {
  }
}

void gen_elseifs(ElseIf *elseifs) {
  for (size_t i=0; i < buf_len(elseifs); i++) {
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
  geni();
  switch (s->kind) {
    case STMT_UNKNOWN:
      assert(0);
      break;
    case STMT_IF:
      gen_str("if ");
      gen_expr(s->if_stmt.cond);
      gen_str("{\n");
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
      gen_str("{\n");
      codegenIndent++;
      gen_statements(s->while_stmt.body);
      codegenIndent--;
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
      assert(s->proc_call_stmt.proc);
      assert(s->proc_call_stmt.proc->kind == EXPR_IDENTREF);
      gen_qname(s->proc_call_stmt.proc->identref.package_name, s->proc_call_stmt.proc->identref.name);
      gen_str("(");
      for (size_t i=0; i < buf_len(s->proc_call_stmt.args); i++) {
        gen_expr(s->proc_call_stmt.args[i]);
      }
      gen_str(");\n");
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
      if (d->package_name && d->package_name[0]) {
        assert(0);
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
          gen_type(d->type->procedure_type.params[i].type);
          if (d->type->procedure_type.params[i].is_open_array) {
            gen_str("*");
          }
          gen_str(" ");
          gen_str(d->type->procedure_type.params[i].name);
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
            gen_type(d->proc_decl.decls[i].type);
            gen_str(" ");
            gen_str(d->proc_decl.decls[i].name);
            gen_str(";\n");
          }
        }
      }
      gen_statements(d->proc_decl.body);
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
    gen_typedef(types[i]);
  }
  for (int i = buf_len(decls) - 1; i >= 0; i--) {
    gen_decl(decls[i]);
  }
}

void gen_test(void) {
  // resolve_test_static();
  resolve_test_file();
  generate_c_code(gReachableTypes, gReachableDecls);
  puts(codegenBuf);
}
