# ocaml-cpp-ffi

This project was practice for using OCaml & C++ FFI. 

There is an AST defintion in frontend/ast.ml and a simple AST is defined in bin/main.ml.

The AST is then processed in backend/ast.cpp. It is then pretty-printed to the screen. 

The pretty-printing uses the variant/visitor pattern and can easily be changed to generating IR.

It is important to note the backend is compiled using Clang, not GCC. This required me to create a new Opam switch
with the C compiler set to Clang. I wrote a guide on how to do this [here](https://gist.github.com/robertfeliciano/5f650d0c9d73707b22e2ec2a1003433b).