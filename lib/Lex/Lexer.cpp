//===--- Lexer.cpp - Phaeton Language Lexer -------------------------------===//
//
//                     The Phaeton Compiler Infrastructure
//
//===----------------------------------------------------------------------===//
//
//  This file implements the Lexer and Token interfaces.
//
//===----------------------------------------------------------------------===//

#include "ph/Lex/Lexer.h"

#include "lex.yy.h"

#include <map>
#include <string>

using namespace phaeton;

Lexer::Lexer(const char *In) : Input(In) {
  yylex_init(&Scanner);
  yy_scan_string(Input, Scanner);
}

Lexer::~Lexer() { yylex_destroy(Scanner); }

int Lexer::lex() { return yylex(&Val, Scanner); }

std::map<int, const std::string> Lexer::TokenStrings = {
    {KW_VAR, "KW_VAR"},
    {KW_INPUT, "KW_INPUT"},
    {KW_OUTPUT, "KW_OUTPUT"},
    {KW_TYPE, "KW_TYPE"},
    {COLON, "COLON"},
    {LPAREN, "LPAREN"},
    {RPAREN, "RPAREN"},
    {LBRACK, "LBRACK"},
    {RBRACK, "RBRACK"},
    {ADD, "ADD"},
    {SUB, "SUB"},
    {MUL, "MUL"},
    {DIV, "DIV"},
    {DOT, "DOT"},
    {EQUAL, "EQUAL"},
    {INT, "INT"},
    {ID, "ID"}};
