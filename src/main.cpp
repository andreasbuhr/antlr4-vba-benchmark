#include "ANTLRInputStream.h"
#include "VBALexer.h"
#include "VBAParser.h"
#include <filesystem>
#include <iostream>

int main(int, char**) {
  try {
    std::string code;
    {
      // read file
      std::string inputfilename = "../data/specs.bas";
      if (!std::filesystem::exists(inputfilename)) {
        throw std::runtime_error("Input file not found");
      }
      std::ifstream infile(inputfilename);
      std::stringstream buffer;
      buffer << infile.rdbuf();
      code = buffer.str();
    }
    antlr4::ANTLRInputStream inputStream(code);
    VBALexer lexer(&inputStream);
    antlr4::CommonTokenStream tokens(&lexer);
    VBAParser parser(&tokens);

    auto start = std::chrono::steady_clock::now();
    auto context = parser.startRule();
    auto finish = std::chrono::steady_clock::now();
    double elapsed_seconds = std::chrono::duration_cast<
                                 std::chrono::duration<double>>(finish - start).count();

    std::cout << "Parsing done in " << elapsed_seconds << std::endl;
    return 0;
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }
  return 0;
}