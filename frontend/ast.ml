type 'a node = { elt: 'a ; loc : int }

type ret_ty = 
  | Void 
  | Int
  | Bool

type id = string

type ty = 
  | Tint
  | Tbool

type aop = 
  | Eq 
  | PluEq
  | MinEq

type exp = 
  | Eint of int
  | Ebool of bool
  | Evar of id node

type stmt = 
  | Assn of id node * aop * exp node
  | Ret of exp node

and block = stmt node list

type fdecl = { 
  frtyp : ret_ty; 
  fname : id; 
  args : (ty * id) list; 
  mutable body : block 
}

external convert_caml_ast : fdecl node -> unit = "convert_caml_ast"