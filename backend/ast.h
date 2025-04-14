#pragma once

#include <string>
#include <vector>
#include <variant>
#include <sstream>
#include <string_view>
#include <iostream>


enum class RetTy {
    Void, Int, Bool
};

enum class Ty {
    Int, Bool
};

enum class Aop {
    Eq, PluEq, MinEq
};


inline std::string toString(RetTy t) {
    switch (t) {
        case RetTy::Void: return "void";
        case RetTy::Int:  return "int";
        case RetTy::Bool: return "bool";
    }
    return "<?>";
}

inline std::string toString(Ty t) {
    switch (t) {
        case Ty::Int:  return "int";
        case Ty::Bool: return "bool";
    }
    return "<?>";
}

inline std::string toString(Aop op) {
    switch (op) {
        case Aop::Eq:    return "=";
        case Aop::PluEq: return "+=";
        case Aop::MinEq: return "-=";
    }
    return "<?>";
}

inline std::string indent(int level) {
    return std::string(level * 2, ' ');
}


template<typename T>
struct Node {
    T elt;
    int loc;
};


struct EInt  { int value; };
struct EBool { bool value; };
struct EVar  { std::string id; };

using ExpVariant = std::variant<EInt, EBool, EVar>;

struct Exp {
    ExpVariant val;
};


struct AssnStmt {
    Node<std::string> id;
    Aop op;
    Node<Exp> exp;
};

using StmtVariant = std::variant<AssnStmt, Node<Exp>>;

struct Stmt {
    StmtVariant val;
};


struct Fdecl {
    RetTy rtyp;
    std::string fname;
    std::vector<std::pair<Ty, std::string>> args;
    std::vector<Node<Stmt>> body;
};


struct ExpToStringVisitor {
    std::string operator()(const EInt& e) const  { return std::to_string(e.value); }
    std::string operator()(const EBool& e) const { return e.value ? "true" : "false"; }
    std::string operator()(const EVar& e) const  { return e.id; }
};

inline std::string expToString(const Exp& e) {
    return std::visit(ExpToStringVisitor{}, e.val);
}


struct StmtToStringVisitor {
    int indentLevel;
    StmtToStringVisitor(int level) : indentLevel(level) {}

    std::string operator()(const AssnStmt& s) const {
        std::ostringstream oss;
        oss << indent(indentLevel) << s.id.elt << " " << toString(s.op) << " " << expToString(s.exp.elt) << ";";
        return oss.str();
    }

    std::string operator()(const Node<Exp>& ret) const {
        std::ostringstream oss;
        oss << indent(indentLevel) << "return " << expToString(ret.elt) << ";";
        return oss.str();
    }
};

inline std::string stmtToString(const Stmt& s, int indentLevel = 0) {
    return std::visit(StmtToStringVisitor{indentLevel}, s.val);
}


inline std::string fdeclToString(const Fdecl& f) {
    std::ostringstream oss;

    oss << toString(f.rtyp) << " " << f.fname << "(";
    for (size_t i = 0; i < f.args.size(); ++i) {
        const auto& [ty, name] = f.args[i];
        oss << toString(ty) << " " << name;
        if (i + 1 < f.args.size()) oss << ", ";
    }
    oss << ") {\n";

    for (const auto& stmt : f.body) {
        oss << stmtToString(stmt.elt, 1) << "\n";
    }

    oss << "}";
    return oss.str();
}
