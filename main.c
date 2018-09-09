#include <unistd.h>
#include <string.h>

int main()
{
    char *str = "Coucou";
    write(1, str, strlen(str));
    return (0);
}
