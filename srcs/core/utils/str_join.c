#include "inc.h"

char    *str_join(char const *s1, char const *s2)
{
    char  *str;
    size_t  l_s1, l_s2;
    size_t  i, j;

    if (!s1 || !s2)
        return (NULL);
    l_s1 = strlen((char *)s1);
    l_s2 = strlen((char *)s2);
    str = malloc(sizeof(char) * (l_s1 + l_s2 + 1));
    if (!str)
        return (NULL);
    i = -1;
    j = -1;
    while (++i < l_s1)
        str[i] = (char)s1[i];
    while (++j < l_s2)
        str[i++] = (char)s2[j];
    str[i] = '\0';
    return (str);
}