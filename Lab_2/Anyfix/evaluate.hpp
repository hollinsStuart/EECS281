// Project identifier: 1CAEF3A0FEDD0DEC26BA9808C69D4D22A9962768

#pragma once

#include <string>
#include <cstdint>
#include <stack>
#include <iostream>

using std::int64_t, std::stack, std::cout;

auto evaluate(std::string const& expression) -> std::int64_t;

void tryCalc(stack<int64_t> &nums, stack<char> &operators);

bool isNumber(char c);
