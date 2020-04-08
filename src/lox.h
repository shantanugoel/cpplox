#ifndef LOX_H_
#define LOX_H_

#include <string>

namespace lox {

class Lox {
 public:
  void RunPrompt(void);
  void RunFile(std::string_view path);
};

}  // namespace lox
#endif  // LOX_H_