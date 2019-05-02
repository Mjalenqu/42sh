|Function Name|Prototype|Description|Return Value|
|:--------:|:--------:|:--------:|:--------:|
|bzero|void ft_bzero(void *elem, int i)|Set i first element of elem to 0||
|isalpha|int ft_isalpha(int c)|Checks if argument is a capital or small letter|1 if true, else 0|
|isascii|int ft_isascii(int c)|Checks if argument is ASCII|1 if true, else 0|
|itoa|char *ft_itoa(int c)|Convert an integer into a string|Result of the conversion|
|putchar|void ft_putchar(char c)|Writes chararacter c on stdout as an unsigned char.||
|putchar_fd|void ft_putchar_fd(char c, int fd)|Writes chararacter c on the file descriptor fd as an unsigned char.||
|putendl|void ft_putendl(const char *s)|Writes the given string on stdout with a '\n'||
|putendl_fd|void ft_putendl_fd(const char *s, int fd)|Writes the given string on fd. fd should be a file descriptor||
|putstr|void ft_putstr(const char *str)|Writes string until '\0' on stdout||
|putstr_fd|void ft_putstr_fd(const char *str, int fd)|Writes string until '\0' on the given file descriptor fd||
|putstr_tab|void ft_putstr_tab(char **s)|Write the "array" of string on stdout. Each string is followed by '\n'||
|strcat|char *ft_strcat(char *dest, char *src)|Add the src string at the end oft dest string deleting it's '\0' and adding one at the end|Address of dest|
|strcmp|int ft_strcmp(const char *s1, const char *s2)|Compare strings untill the first difference|0 if the strings are the same else *s1 - *s2|
|strcpy|char *ft_strcpy(char *dest, const char *src)|Copies the src string in dest. dest should be long enough to contain src|Dest|
|strdel|void ft_strdel(char **str)|Prend en paramètre l’adresse d’une chaîne de caractères qui doit être libérée avec free(3) et son pointeur mis à NULL.||
|strdup|char *ft_strdup(char *str)|Duplicates string and return a pointer to it, the new string is memory allocated with malloc(3) and can be freed with free(3)|Pointer to the new string or NULL if an error occured|
|strequ|int ft_strequ(const char *s1, const char *s2)|Compare strings|1 if the two strings are identical, else 0|
|strjoin|char *ft_strjoin(const char *s1, const char *s2) |Allocates memory for a new string which is the concatenation of s1 ans s2 with malloc(3)| New string or NULL if fails|
|strjoin_free|void ft_strjoin_free(char **s1, const char *s2)|Concatenates *s1 and s2 at *s1 address after freeing it with free(3). s1 has to be allocated with malloc(3). If the new allocation fails, *s1 is set to NULL||
|strjoin_insert|void ft_strjoin_insert(char **s1, char *s2, int i)|Insert s2 in *s1 at index i at *s1 address after freeing it with free(3). s1 has to be allocated with malloc(3). If the new allocation fails, *s1 is set to NULL||
|strlen|int ft_strlen(const char *str)|Calcule la longueur de la chaine excluant le '\0'|Longueur de la chaine|
|strnew|char *ft_strnew(int size)|Cree une chaine de caractere de taille size avec malloc(3) remplie de '\0'|La chaine cree|
|strrmvi||||
|strstr|char *ft_strstr(const char *s1, const char *tofind)|Cherche la chaine tofind dans s1|Revoi un pointeur sur le debut de la chaine tofind dans s1 ou NULL si il n'y est pas|
|strsub|char *ft_strsub(char const *s, unsigned int start, size_t len)|Cree une chaine de caractere identique a s a partir de start sur une longueur len allouee avec malloc(3)|La nouvelle chaine|
|voidrev|void *ft_voidrev(void *s)|Inverse l'ordre des elements, si l'on passe par exemple une chaine de caractere en arguments, le resultat sera le meme que la fonction strrev|Retourne son argument|
|voidswap|void ft_voidswap(void *elem1, void *elem2)|Intervertit les adresse des arguments||
