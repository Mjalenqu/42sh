|Nom de fonction|Prototype|Description|Valeur de retour|
|:--------:|:--------:|:--------:|:--------:|
|bzero|void ft_bzero(void *elem, int i)|Met a 0 les i premiers element de elem||
|isalpha|int ft_isalpha(int c)|Verifie si l'argiment est une lettre majuscule ou minuscule|1 si vrai, 0 sinon|
|isascii|int ft_isascii(int c)|Verifie si l'argument est un caractere ASCII|1 si vrai, 0 sinon|
|itoa|char *ft_itoa(int c)|Convertit un int en une chaine de caractere|Resultat de la conversion|
|putchar|void ft_putchar(char c)|Ecrit le caractere c sur la sortie standard converti en un unsigned char||
|putchar_fd|void ft_putchar_fd(char c, int fd)|Ecrit le caractere c, sur le descripteur de fichier fd, converti en un unsigned char||
|putendl|void ft_putendl(const char *s)|Ecris la chaine de caractere passee en parametre sur la sortie standard avec un retour a la ligne||
|putendl_fd|void ft_putendl_fd(const char *s, int fd)|Ecris la chaine de caractere passee en parametre sur le descripteur de fichier fd avec un retour a la ligne||
|putstr|void ft_putstr(const char *str)|Ecrit la chaine de caractere jusqu'au '\0' sur la sortie standard||
|putstr_fd|void ft_putstr_fd(const char *str, int fd)|Ecrit la chaine de caractere jusqu'au '\0' sur le descripteur de fichier fd||
|putstr_tab|void ft_putstr_tab(char **tab)|Ecrit le "tableau" de chaines de caractere sur la sortie standard. Chaque chaine est suivie dun retour a la ligne||
|strcat|char *ft_strcat(char *dest, char *src);|Ajoute la chaîne src à la fin de la chaîne dest en écrasant son caractère nul (« \0 »). Les chaînes ne doivent pas se chevaucher, et la chaîne dest doit être assez grande pour accueillir le résultat. La chaine dest est terminee par '\0'|Pointeur sur la chaine dest|
|strcmp|int ft_strcmp(const char *s1, const char *s2)|Compare les 2 chaines de caractere jusau'a la premiere difference|0 si les 2 chaines sont identique, *s1 - *s2 sinon|
|strcpy|char *ft_strcpy(char *dest, const char *src)|Copie la chaîne pointée par dans la chaîne pointée par dest. La chaîne dest doit être assez grande pour accueillir la copie|Pointeur sur la chaine de dest|
|strdel|void ft_strdel(char **str)|Prend en paramètre l’adresse d’une chaîne de caractères qui doit être libérée avec free(3) et son pointeur mis à NULL.||
|strdup|char *ft_strdup(char *str)|Retourne un pointeur sur une nouvelle chaine dupliquee en utilisant malloc(3) et pouvant etre liberee en utilisant free(3)|Un pointeur vers la chaine dupliquee ou NULL en cas d'erreur|
|strequ|int ft_strequ(const char *s1, const char *s2)|Compare les 2 chaines|1 si les 2 chaines sont identique, 0 sinon|
|strjoin|char *ft_strjoin(const char *s1, const char *s2) |Alloue (avec malloc(3)) et retourne une chaîne de caractères “fraiche” terminée par un ’\0’ résultant de la concaténation de s1 et s2.| Nouvelle chaine de caractere ou NULL en cas d'erreur|
|strjoin_free|void ft_strjoin_free(char **s1, const char *s2)|Concatene *s1 et s2 et remplace *s1 apres avoir free(). s1 doit etre un pointeur sur une chaine allouee avec malloc(3). Le pointeur s1 est mis a NULL si la nouvelle allocation (malloc(3)) echoue||
|strjoin_insert|void ft_strjoin_insert(char **s1, char *s2, int i)|Insere s2 dans *s1 a l'index i et remplace *s1 apres avoir free(). s1 doit etre un pointeur sur une chaine allouee avec malloc(3). Le pointeur s1 est mis a NULL si la nouvelle allocation (malloc(3)) echoue||
|strlen|int ft_strlen(const char *str) |Calculates the length of the string s, excluding '\0'|Length of string|
|strnew|char *ft_strnew(int size)|Allocates with malloc(3) a new string lenght of size filled with '\0'|The allocated string|
|strrmvi||||
|strstr|char *ft_strstr(const char *s1, const char *tofind)|Look fot the string tofind in s1|Address of the begining of tofind in s1 if found else NULL|
|strsub|char *ft_strsub(char const *s, unsigned int start, size_t len)|Duplicate string s from start for len lenght. duplicated string is alocated with malloc(3)|The duplicated string|
|voidrev|void *ft_voidrev(void *s)|Reverse the element, for example, if you pass a string it'll work as a strrev|Return it's argument|
|voidswap|void ft_voidswap(void *elem1, void *elem2)|Exchange the arguments address||
|ft_put_space||||
|ft_strsplit||||
