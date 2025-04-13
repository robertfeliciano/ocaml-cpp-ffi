open Ast

let () = 
  let body = 
    [
      { elt = Assn ({ elt = "x"; loc = 1 }, Eq, { elt = Eint 5; loc = 2 }); loc = 3 };
      { elt = Assn ({ elt = "y"; loc = 4 }, Eq, { elt = Eint 10; loc = 5 }); loc = 6 };
      { elt = Assn ({ elt = "y"; loc = 7 }, PluEq, { elt = Evar { elt = "x"; loc = 8 }; loc = 9 }); loc = 10 };
      { elt = Ret  ({ elt = Evar { elt = "y"; loc = 11 }; loc = 12 }); loc = 13 }
    ] in
  let fdecl = { frtyp = Void; fname = "main"; args = [(Tint, "a")]; body } in
  convert_caml_ast { elt = fdecl ; loc = 0 };