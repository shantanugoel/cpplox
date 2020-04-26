#include <algorithm>
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

void DefineType(std::ostream& os, const std::string& base_name,
                const std::string& class_name, const std::string& fields) {
  os << "\nclass " << class_name << " : public " << base_name << " {\n";
  os << " public:\n";
  os << "  " << class_name << " (" << fields << ")"
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
      os << ", ";
    }
    os << field_name << "(" << field_name << ")";
    private_members << "  " << field_type << " " << field_name << ";\n";
  } while (delimiter_loc != -1);

  os << " {}\n";
  os << "\n private:\n";
  os << private_members.str();
  os << "};\n";
}

void DefineAst(const std::string& base_name,
               const std::vector<const std::string> types) {
  std::stringstream os;
  std::string file_header_temp;
  file_header_temp.resize(base_name.length());
  std::transform(base_name.begin(), base_name.end(), file_header_temp.begin(),
                 ::toupper);
  os << "// Auto Generated file. Do not edit by hand.\n";
  os << "#ifndef _" << file_header_temp << "_H_\n";
  os << "#define _" << file_header_temp << "_H_\n";
  os << "namespace lox {\n";
  os << "#include \"token.h\"\n";
  os << "class " << base_name << " {\n";
  os << "};\n";

  for (auto& type : types) {
    size_t delimiter_location = type.find(":");
    std::string class_name = trim(type.substr(0, delimiter_location));
    std::string fields = trim(type.substr(delimiter_location + 1));
    DefineType(os, base_name, class_name, fields);
  }

  os << "}  // namespace lox\n";
  os << "#endif\n";
  std::cout << os.str();
  return;
}

int main() {
  std::vector<const std::string> types = {
      "Binary: Expr left, Token operator, Expr right",
      "Grouping: Expr expression", "Literal: Object value",
      "Unary: Token opreator, Expr right"};

  DefineAst("Expr", types);
  return 0;
}
