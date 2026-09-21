#include <stdio.h>

struct vec
{
    int *mass;
    size_t len;
};


int main(int argc, char const *argv[])
{
    struct vec v;
    printf("%d\n", v.len);
}

