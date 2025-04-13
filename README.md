# ocaml-cpp-ffi

This project was practice for using OCaml & C++ FFI. 

There is an AST defintion in frontend/ast.ml and a simple AST is defined in bin/main.ml.

The AST is then processed in backend/ast.cpp. It is then pretty-printed to the screen. 

The pretty-printing uses the variant/visitor pattern and can easily be changed to generating IR.