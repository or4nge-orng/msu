#pragma once

#include <memory>
#include <fstream>

class str_stack {
    private:
        int cap, used, total, blocks;

        char tmp_filename[64];
        mutable std::fstream tmp_file;

        std::unique_ptr<char[]> body;

        int top_start() const;

        int flush(); // flush block from ram to file
        int read_block();
        
        int open_tmpfile();
        void discard_tmpfile();
        int copy_tmpfile(const str_stack &o);
        void swap(str_stack &o);

    public:
        str_stack(int n = 1024);
        str_stack(const str_stack &o);
        str_stack(str_stack &&o) noexcept;
        ~str_stack();

        str_stack &operator=(const str_stack &o);
        str_stack &operator=(str_stack &&o) noexcept;

        int push(const char *s); // push string s to stack, return 1 if success, 0 if fail
        int top_len() const; // return length of string on top of stack, -1 if stack is empty
        int pop(); // pop string from stack, return 1 if success, 0 if fail
        int top_copy(char *dst, int dst_size) const; // copy string on top of stack to dst, return 1 if success, 0 if fail

        int size() const; // return number of strings in stack
        int blocks_in_file() const;
        int block_size() const;

        int save(const char *name) const;
        int load(const char *name);
};

void print_all(str_stack s);