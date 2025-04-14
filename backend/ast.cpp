#include "ast.h"

extern "C" {
    #include <caml/memory.h>
    #include <caml/alloc.h>
    #include <caml/custom.h>
    #include <caml/hash.h>
}

RetTy convert_ret_ty(value v) {
    return static_cast<RetTy>(Int_val(v));
}

Ty convert_ty(value v) {
    return static_cast<Ty>(Int_val(v));
}

Aop convert_aop(value v) {
    return static_cast<Aop>(Int_val(v));
}


Node<Exp> convert_exp_node(value v) {
    Node<Exp> node;
    node.loc = Int_val(Field(v, 1));
    value exp = Field(v, 0);

    if (Is_block(exp)) {
        switch (Tag_val(exp)) {
            case 0: {
                int i = Int_val(Field(exp, 0));
                node.elt.val = EInt{i};
                break;
            }
            case 1: {
                bool b = Bool_val(Field(exp, 0));
                node.elt.val = EBool{b};
                break;
            }
            case 2: {
                value id_node = Field(exp, 0);
                std::string var = String_val(Field(id_node, 0));
                node.elt.val = EVar{var};
                break;
            }
        }
    }
    return node;
}


Node<Stmt> convert_stmt_node(value v) {
    Node<Stmt> node;
    node.loc = Int_val(Field(v, 1));
    value stmt = Field(v, 0);

    if (Tag_val(stmt) == 0) {
        AssnStmt assn;
        value id_node = Field(stmt, 0);
        assn.id.elt = String_val(Field(id_node, 0));
        assn.id.loc = Int_val(Field(id_node, 1));
        assn.op = convert_aop(Field(stmt, 1));
        assn.exp = convert_exp_node(Field(stmt, 2));
        node.elt.val = assn;
    } else { 
        Node<Exp> ret_exp = convert_exp_node(Field(stmt, 0));
        node.elt.val = ret_exp;
    }
    return node;
}


Fdecl convert_fdecl(value v) {
    Fdecl f;

    f.rtyp = convert_ret_ty(Field(v, 0));
    f.fname = String_val(Field(v, 1));

    value args = Field(v, 2);
    while (args != Val_emptylist) {
        value pair = Field(args, 0);
        f.args.emplace_back(
            convert_ty(Field(pair, 0)),
            String_val(Field(pair, 1))
        );
        args = Field(args, 1);
    }

    value body = Field(v, 3);
    while (body != Val_emptylist) {
        f.body.push_back(convert_stmt_node(Field(body, 0)));
        body = Field(body, 1);
    }

    return f;
}


extern "C" {
    value convert_caml_ast(value fdecl_node) {
        CAMLparam1(fdecl_node);
        value fdecl_val = Field(fdecl_node, 0);
        Fdecl fdecl = convert_fdecl(fdecl_val);
        std::cout << fdeclToString(fdecl) << std::endl;
        CAMLreturn(Val_unit);
    }
}