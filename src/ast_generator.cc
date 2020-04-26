#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s) {
  size_t start = s.find_first_not_of(WHITESPACE);
  return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s) {
  size_t end = s.find_last_not_of(WHITESPACE);
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s) { return rtrim(ltrim(s)); }

void DefineType(std::ofstream& of, const std::string& base_name,
                const std::string& class_name, const std::string& fields) {
  of << "\nclass " << class_name << " : public " << base_name << " {\n";
  of << " public:\n";
  of << "  " << class_name << " (" << fields << ")"
     << " : ";
  int delimiter_loc_prev = 0;
  int delimiter_loc = -1;
  std::stringstream private_members;
  do {
    delimiter_loc_prev = delimiter_loc + 1;
    delimiter_loc = fields.find(",", delimiter_loc_prev);
    const std::string temp = trim(
        fields.substr(delimiter_loc_prev, delimiter_loc - delimiter_loc_prev));
    const std::string field_type = trim(temp.substr(0, temp.find(" ")));
    const std::string field_name = trim(temp.substr(temp.find(" ")));
    if (delimiter_loc_prev != 0) {
      of << ", ";
    }
    of << field_name << "(" << field_name << ")";
    private_members << "  " << field_type << " " << field_name << ";\n";
  } while (delimiter_loc != -1);

  of << " {}\n";
  of << "\n private:\n";
  of << private_members.str();
  of << "};\n";
}

void DefineAst(std::string_view output_dir, const std::string& base_name,
               const std::vector<const std::string> types) {
  const std::string file_name = base_name + ".h";
  fs::path output_file_path(output_dir);

  std::error_code ec;
  ec.clear();
  fs::create_directory(output_file_path, ec);
  if (ec) {
    std::cerr << ec.message();
    return;
  }

  output_file_path /= file_name;
  std::ofstream of(output_file_path, std::ios::out);
  if (!of.is_open()) {
    std::cerr << std::strerror(errno);
  } else {
    std::string file_header_temp;
    file_header_temp.resize(base_name.length());
    std::transform(base_name.begin(), base_name.end(), file_header_temp.begin(),
                   ::toupper);
    of << "// Auto Generated file. Do not edit by hand.\n";
    of << "#ifndef _" << file_header_temp << "_H_\n";
    of << "#define _" << file_header_temp << "_H_\n";
    of << "namespace lox {\n";
    of << "#include \"token.h\"\n";
    of << "class " << base_name << " {\n";
    of << "};\n";

    for (auto& type : types) {
      size_t delimiter_location = type.find(":");
      std::string class_name = trim(type.substr(0, delimiter_location));
      std::string fields = trim(type.substr(delimiter_location + 1));
      DefineType(of, base_name, class_name, fields);
    }

    of << "}  // namespace lox\n";
    of << "#endif\n";
    of.close();
  }
  return;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: generate_ast <output directory>\n";
    return 1;
  }

  std::string output_dir = argv[1];
  std::vector<const std::string> types = {
      "Binary: Expr left, Token operator, Expr right",
      "Grouping: Expr expression", "Literal: Object value",
      "Unary: Token opreator, Expr right"};

  DefineAst(output_dir, "Expr", types);
  return 0;
}
