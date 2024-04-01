// Project identifier: 1CAEF3A0FEDD0DEC26BA9808C69D4D22A9962768

#include "evaluate.hpp"

int64_t evaluate(std::string const& expression) {
    // Your implementation goes here
    char temp;
    stack<int64_t> nums;
    stack<char> operators;

    for (int i = 0; i < (int)expression.size(); ++i) {
        temp = expression[i];
        if (isNumber(temp)) {
            nums.push((int64_t)temp - '0');
        } else {
            operators.push(temp);
        }
        tryCalc(nums, operators);
    }
    tryCalc(nums, operators);
    return nums.top();
}

bool isNumber(char c) {
    if ((int)c == 42 || (int)c == 43 || (int)c == 45 || (int)c == 47) {
        return false;
    }
    return true;
}

void tryCalc(stack<int64_t> &nums, stack<char> &operators) {
    while(nums.size() > 1 && !operators.empty()) {
        // can do some calculation
        int64_t first = nums.top();
        nums.pop();
        int64_t second = nums.top();
        nums.pop();
        char op = operators.top();
        operators.pop();
        int64_t ans = 0;
        switch (op) {
            case '+':
                ans = first + second;
                break;
            case '-':
                ans = second - first;
                break;
            case '*':
                ans = first * second;
                break;
            case '/':
                ans = second / first;
                break;
            default:
                std::cerr << "bad" << std::endl;
                exit(1);
        }
        nums.push(ans);
    }
}
