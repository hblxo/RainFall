// #include <>

class N
{
    N(void);
    N(int n){};
    N(int n, int m);
    int operator-(N &);
};

void N::N(int)(int arg_8h, int arg_ch)
{
    // N::N(int)
    *(code **)arg_8h = vtable.N .0;
    *(int *)(arg_8h + 0x68) = arg_ch;
    return;
}

int N::operator-(N &)(int arg_8h, int arg_ch)
{
    // N::operator-(N&)
    return *(int *)(arg_8h + 0x68) - *(int *)(arg_ch + 0x68);
}

void N::setAnnotation(char *)(void *s1, char *s)
{
    undefined4 uVar1;

    // N::setAnnotation(char*)
    uVar1 = strlen(s);
    memcpy((int)s1 + 4, s, uVar1);
    return;
}

void main(char **argv, char **envp)
{
    N *s1;
    code **arg_8h;
    int var_bp_4h;

    if ((int)argv < 2)
    {
        _exit(1);
    }
    s1 = new N(0x6c);
    N::N(int)((int)s1, 5);
    arg_8h = (code **)operator new (unsigned int)(0x6c);
    N::N(int)((int)arg_8h, 6);
    N::setAnnotation(char *)(s1, envp[1]);
    (**(code **)*arg_8h)(arg_8h, s1);
    return;
}
