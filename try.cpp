#include <any>
#include <event.h>
#include <vector>
#include <iostream>
#include "call.h"
int test (int x,double y) {
    return x + y;
}
int main() {
    auto pack = FunctionPack(test);
    auto ret = pack.Call({1,1.1});
    std::cout << std::any_cast<int>(ret) << std::endl;
    return 0;
}