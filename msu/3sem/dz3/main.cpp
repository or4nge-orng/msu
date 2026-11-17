#include "stack.hpp"

#include <iostream>

int main() {
    str_stack s(8);
    char buf[9];
    std::cout << "empty stack. top_len -> -1:\t" << s.top_len() << std::endl;

    std::cout << "push 'ab': push -> 1:\t" << s.push("ab") << std::endl;
    std::cout << "push 'cd': push -> 1:\t" << s.push("cd") << std::endl;
    std::cout << "push 'e': push -> 1:\t" << s.push("e") << std::endl;
    std::cout << "push 'f': push -> 1:\t" << s.push("f") << std::endl;
    std::cout << "push 'gh': push -> 1:\t" << s.push("gh") << std::endl;

    std::cout << "stacks size:\t" << s.size() << " " << s.blocks_in_file() << std::endl;

    std::cout << "top_len -> 2:\t" << s.top_len() << std::endl;

    std::cout << "pop -> 1:\t" << s.pop() << std::endl;
    std::cout << "stacks size:\t" << s.size() << " " << s.blocks_in_file() << std::endl;

    std::cout << "top_len -> 1:\t" << s.top_len() << std::endl;

    std::cout << "top_copy -> 1, buf -> f:\t" << s.top_copy(buf, sizeof(buf)) << " " << buf << std::endl; // 1 ab

    std::cout << "pop -> 1 1:\t" << s.pop() << s.pop() << std::endl;
    std::cout << "stacks size:\t" << s.size() << " " << s.blocks_in_file() << std::endl;
    std::cout << "top_len -> 2:\t" << s.top_len() << std::endl;
    /*
    str_stack a(8);
    a.push("ab"); a.push("cd"); a.push("e"); a.push("f"); a.push("gh");
    str_stack b(a);
    std::cout << a.size() << " " << b.size() << "\n";   // должно быть 5 5
    print_all(a);
    print_all(b);
    */


    str_stack c(8); c.push("old");
    str_stack a(8);
    a.push("ab"); a.push("cd"); a.push("e"); a.push("f"); a.push("gh");
    str_stack b(std::move(a));
    std::cout << "moved from a to b: " << "a size = " << a.size() << "; b size = " << b.size() << std::endl;
    a.push("xyz");
    std::cout<< "pushed 'xyz' to a: " << std::endl <<  "a = ";
    print_all(a);
    c = std::move(b);
    std::cout << "b moved to c: " << b.size() << " " << c.size() << std::endl;
    print_all(c);
    
    std::cout << "save c to save1.txt";
    c.save("save1.txt");
    std::cout << "load from save1.txt to b" << std::endl << "before: ";
    print_all(b);
    b.load("save1.txt");
    std::cout << "after: ";
    print_all(b);
}