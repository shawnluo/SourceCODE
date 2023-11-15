#include <termios.h>
#include <unistd.h>

/*
这段代码将从标准输入中读取字符，并且在读取时不会回显字符，直到用户按下Enter键才会将输入的字符传递给程序。
当然，您可以根据自己的需要进行属性设置。
*/
int main()
{
    struct termios attr;
    tcgetattr(STDIN_FILENO, &attr);          // 获取当前终端属性
    attr.c_lflag &= ~(ECHO);                 // 禁用回显
    attr.c_lflag &= ~(ICANON);               // 非标准模式读取输入数据
    tcsetattr(STDIN_FILENO, TCSANOW, &attr); // 设置终端属性
    return 0;
}

int main() {
    struct termios term;

    if (tcgetattr(STDIN_FILENO, &term) != 0)
        perror("tcgetatt() error");
    else {
        if (term.c_iflag & BRKINT)
            puts("BRKINT is set");
        else
            puts("BRKINT is not set");
        if (term.c_cflag & PARODD)
            puts("Odd parity is used");
        else
            puts("Even parity is used");
        if (term.c_lflag & ECHO)
            puts("ECHO is set");
        else
            puts("ECHO is not set");
        printf("The end-of-file character is x'%02x'\n", term.c_cc[VEOF]);
    }
}