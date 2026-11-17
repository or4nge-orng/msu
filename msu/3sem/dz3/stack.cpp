#include "stack.hpp"

#include <stdexcept>
#include <ctime>
#include <iostream>

str_stack::str_stack(int n) :
            cap(n),
            used(0),
            total(0),
            blocks(0),
            body(),
            tmp_file(),
            tmp_filename() {
    if (n < 2) throw std::invalid_argument("Размер строки должен быть больше 1");
    body.reset(new char[cap]);
}

str_stack::str_stack(const str_stack &o) : 
    cap(o.cap),
    used(o.used),
    total(o.total),
    body(new char[o.cap]),
    blocks(o.blocks) {
        if (used) memcpy(body.get(), o.body.get(), used);
        if (blocks > 0) {
            if (!open_tmpfile()) {
                discard_tmpfile();
                throw std::runtime_error("Не удалось скопировать файл-буфер open");
            }
            if (!copy_tmpfile(o)) {
                discard_tmpfile();
                throw std::runtime_error("Не удалось скопировать файл-буфер copy");
            }
        }
    }

str_stack::str_stack(str_stack &&o) noexcept :
    cap(o.cap),
    used(o.used),
    total(o.total),
    body(std::move(o.body)),
    blocks(o.blocks),
    tmp_file(std::move(o.tmp_file)),
    tmp_filename() {
        memcpy(tmp_filename, o.tmp_filename, sizeof(tmp_filename));
        o.used = 0;
        o.total = 0;
        o.blocks = 0;
        o.tmp_filename[0] = '\0';
    }

str_stack::~str_stack() {
    discard_tmpfile();
}

int str_stack::open_tmpfile() {
    static int counter = 0;
    if (tmp_file.is_open()) return 1;
    
    snprintf(tmp_filename, sizeof(tmp_filename), "str_stack_%ld_%d.tmp", long(time(NULL)), counter++);
    tmp_file.clear();
    tmp_file.open(tmp_filename, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    if (!tmp_file.is_open()) {
        tmp_filename[0] = '\0';
        return 0;
    }
    return 1;
}

void str_stack::discard_tmpfile() {
    if (tmp_file.is_open()) {
        tmp_file.close();
    }

    if(tmp_filename[0]) {
        std::remove(tmp_filename);
        tmp_filename[0] = '\0';
    }
    blocks = 0;
}

int str_stack::flush() {
    if (!open_tmpfile()) return 0;

    memset(body.get() + used, 0, cap - used);
    tmp_file.clear();

    tmp_file.seekp((std::streamoff)blocks * cap);
    tmp_file.write(body.get(), cap);
    tmp_file.flush();
    if (!tmp_file) return 0;
    blocks++;
    used = 0;
    return 1;
}

int str_stack::read_block() {
    std::unique_ptr<char[]> tmp(new char[cap]);
    tmp_file.clear();
    tmp_file.seekg((std::streamoff)(blocks - 1) * cap);
    tmp_file.read(tmp.get(), cap);
    if (!tmp_file) return 0;
    int u = cap;
    while (u > 0 && tmp[u - 1] == '\0') u--;
    if (u == 0 || u == cap) return 0;
    body = std::move(tmp);
    used = u + 1;
    blocks--;
    return 1;
}

int str_stack::push(const char *s) {
    
    if (!s) return 0;

    size_t l = strlen(s);

    if (l == 0 || l + 1 > (size_t)cap) return 0;
    int need = (int)l + 1;
    if (!body) body.reset(new char[cap]);


    if (used + need > cap && !flush()) return 0;

    memcpy(body.get() + used, s, need);

    used += need;
    total++;

    return 1;
}

int str_stack::top_start() const {
    int i = used - 1;
    while (i > 0 && body[i - 1] != '\0') i--;
    return i;
}
//TODO: change to one func if possible
int str_stack::top_len() const {
    if (!used) return -1;
    return used - 1 - top_start();
}

int str_stack::pop() {
    if (!used) return 0;
    int start = top_start();

    if (start == 0 && blocks > 0) {
        if (!read_block()) return 0;
    } else {
        used = start;
    }
    total--;
    return 1;
}

int str_stack::top_copy(char *dst, int dst_size) const {
    
    int len = top_len();

    if (len < 0 || !dst || dst_size < len + 1) return 0;

    memcpy(dst, body.get() + top_start(), len + 1);
    return 1;
}

int str_stack::copy_tmpfile(const str_stack &o) {
    o.tmp_file.clear();
    o.tmp_file.seekg(0);
    tmp_file.clear();
    tmp_file.seekp(0);
    for (int i = 0; i < o.blocks * o.cap; i++) {
        int ch = o.tmp_file.get();
        if(ch == EOF) {
            return 0;
        }
        tmp_file.put((char)ch);
    }
    tmp_file.flush();
    return tmp_file ? 1 : 0;
}

int str_stack::size() const {
    return total;
}

int str_stack::blocks_in_file() const {
    return blocks;
}

int str_stack::block_size() const {
    return cap;
}

void str_stack::swap(str_stack &o) {
    std::swap(cap, o.cap);
    std::swap(used, o.used);
    std::swap(total, o.total);
    std::swap(blocks, o.blocks);
    std::swap(tmp_filename, o.tmp_filename);
    body.swap(o.body);
    tmp_file.swap(o.tmp_file);
}

int str_stack::save(const char *name) const {
    if (!name) return 0;
    std::ofstream out(name);
    if (!out) return 0;
    int ok = 1;
    try {
        str_stack t(*this);
        std::unique_ptr<char[]> buf(new char[cap]);
        while (ok && t.size() ) {
            t.top_copy(buf.get(), cap);
            if (strchr(buf.get(), '\n')) ok = 0;
            else out << buf.get() << '\n';
            if (ok && !t.pop()) ok = 0;
        }
    } catch (const std::exception &) {
        ok = 0;
    }

    out.close();
    if (!out) ok = 0;
    if (!ok) std::remove(name);
    return 1;
}

int str_stack::load(const char *name) {
    if (!name) return 0;
    std::ifstream in(name);
    std::unique_ptr<char []> buf(new char[cap]);
    if (!in) return 0;
    str_stack rev(cap);
    while (in.getline(buf.get(), cap)) {
        if (buf[0] == '\0') continue;
        if (!rev.push(buf.get())) return 0;
    }
    if (!in.eof()) return 0;
    str_stack t(cap);
    while (rev.size()) {
        rev.top_copy(buf.get(), cap);
        if (!t.push(buf.get()) || !rev.pop()) return 0;
    }
    *this = std::move(t);
    return 1;
}

str_stack &str_stack::operator=(const str_stack &o) {
    if (this != &o) {
        str_stack t(o);
        swap(t);
    }
    return *this;
}

str_stack &str_stack::operator=(str_stack &&o) noexcept {
    if (this != &o) {
        str_stack t(std::move(o));
        swap(t);
    }
    return *this;
}

void print_all(str_stack s) {
    int cap = s.block_size();
    std::unique_ptr<char[]> buf(new char[cap]);
    str_stack rev(cap);
    while (s.size()) {
        s.top_copy(buf.get(), cap);
        rev.push(buf.get());
        s.pop();
    }
    std::cout << "[";
    while (rev.size()) {
        rev.top_copy(buf.get(), cap);
        std::cout << "'" << buf.get() << "'";
        rev.pop();
        if (rev.size() > 1) std::cout << ", ";
        
    }
    std::cout << "]" << std::endl;
}
