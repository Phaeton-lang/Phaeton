#include <fstream>
#include <iostream>

#include "ph/CodeGen/OMPCG.h"
#include "ph/CodeGen/GraphCG.h"
#include "ph/Parse/Parser.h"
#include "ph/Sema/Sema.h"

int main(int argc, char *argv[]) {

  std::ifstream in_file;

  if (argc != 2) {
    std::cout << "Usage: Translate [input file]... " << '\n';
    return -1;
  } else {
    in_file.open(argv[1]);
    if (!in_file.is_open()) {
      std::cout << "Error! Fail to open " << argv[1] << '\n';
      return -1;
    }
  }

  std::filebuf *file_buf = in_file.rdbuf();
  std::size_t size = file_buf->pubseekoff(0, in_file.end, in_file.in);
  file_buf->pubseekpos(0, in_file.in);

  char *input = new char[size + 1];
  file_buf->sgetn(input, size);
  input[size] = 0;

  in_file.close();

  Parser parser(input);
  if (parser.parse()) {
    return -1;
  }

  // parser.getAST()->dump();
  delete[] input;

  Sema sema;
  sema.visitProgram(parser.getAST());
  GraphCodeGen gcg(&sema);
  OpenMPEmitter omp(&gcg, true);
  omp.genCode(parser.getAST());
  std::cout << omp.getCode();

  Program::destroy(parser.getAST());

  return 0;
}
