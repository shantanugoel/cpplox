#ifndef LOX_H_
#define LOX_H_

#include <string>

namespace lox {

class Lox {
 public:
  void RunPrompt(void);
  void RunFile(const std::string& path);

 private:
  void Run(const std::string& source);
};

}  // namespace lox
#endif  // LOX_H_