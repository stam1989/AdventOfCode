//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <cstdint>
#include <tuple>
#include <utility>
#include <stdarg.h>
#include <string_view>

#include <iostream>

static uint32_t s_AllocCount = 0;

void* operator new(size_t s)
{
    s_AllocCount++;
    std::cout << "Allocating " << s << std::endl;
    return malloc(s);
}

struct Reaction {

    Reaction() = default;
    Reaction( std::pair<size_t, std::string_view>& in,  std::pair<size_t, std::string_view>& out)
        : input(in), output(out) { std::cout << "Copied\n"; }
    Reaction( std::pair<size_t, std::string_view>&& in,  std::pair<size_t, std::string_view>&& out)
        : input(std::move(in)), output(std::move(out)) { std::cout << "Moved\n"; }

    Reaction(const Reaction& r) : input(r.input), output(r.output) { std::cout << "Copied\n"; }

    bool operator=(Reaction& r){
        return input == r.input && output == r.output;
    }


//     std::tuple<std::pair<size_t, std::string_view>> input;
    std::pair<size_t, std::string_view> input;
    std::pair<size_t, std::string_view> output;
};





int main() {

    std::string_view element = "foo1foo1foo1foo1foo1foo1foo1foo1foo1foo1foo1foo1foo1foo1foo1";
    size_t count1 = 3;

    std::string_view element2 = "foo2";
    size_t count2 = 1;

    std::pair<size_t, std::string_view> p1 = std::make_pair(count1, element);
    auto p2 = std::make_pair(count2, element2);
    Reaction r(p1, p2);
    Reaction r2({3, element}, {1, "foo2"});
    Reaction r3(r2);
    Reaction r4 = r3;

    return 0;
}
