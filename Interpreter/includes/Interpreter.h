#ifndef INTERPRETER_INTERPRETER_H
#define INTERPRETER_INTERPRETER_H
#include <vector>
#include <string>
#include <stack>

class ShObject{
    char gc_status_;
public:
    int value_;
};

struct Frame{
    std::vector<ShObject> local_variables;
    std::stack<ShObject> stack;
};

class Interpreter{
    Frame current_frame_;
    void ExecuteNextInstruction(const std::ifstream& ifstream);
   public:
    void ExecuteMain(const std::string& path, size_t start_offset);
};

#endif //INTERPRETER_INTERPRETER_H