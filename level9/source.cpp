#include <string>

class N
{
public:
    int val;
    char annotation[100];

    N(int v) : val(v){};

    void setAnnotation(char *s)
    {
        int len = strlen(s);
        memcpy(annotation, s, len);
    };

    virtual int operator-(N const &rhs)
    {
        return val - rhs.val;
    };

    virtual int operator+(N const &rhs)
    {
        return val + rhs.val;
    };
};

int main(int ac, char **av)
{
    if (ac < 2)
    {
        exit(1);
    }
    N *a = new N(5);
    N *b = new N(6);
    N c = *a;
    N d = *b;
    c.setAnnotation(av[1]);
    return c + d;
}
