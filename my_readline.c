#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>


int READLINE_READ_SIZE = 512;
char *storage = NULL;

// cleans up the persistent buffer. Should be called more the program exits
void init_my_readline(){
    if (storage) {
        free(storage);
        storage = NULL;
    }
}
// replaces `strlen()`
static int get_len(const char *s) {
    int i = 0;
    while (s && s[i]) i++;
    return i;
}

// concatenates two strings with a known length
static char *str_join(char *a, const char *b, int b_len){
    int a_len = get_len(a);
    char *res =malloc((a_len +b_len +1));
    if (!res) return NULL;

    for (int i = 0; i < a_len; i++) res[i] = a[i];
    for (int i = 0; i <b_len; i++) res[a_len +i] = b[i];
    res[a_len +b_len] = '\0';

    free(a);
    return res;
}

// finds the index of the first newline character
static int find_nl(const char *s){
    for (int i = 0; s && s[i]; i++){
        if (s[i] == '\n') return i;
    }
    return -1;
}

// extracts a line from the buffer and trims storage
static char *extract_line(int nl_pos) {
    char *line = malloc(nl_pos + 1);
    if (!line) return NULL;
    for (int i = 0; i < nl_pos; i++) line[i] = storage[i];
    line[nl_pos] = '\0';

    int total_len = get_len(storage);
    int remaining = total_len -nl_pos -1;
    if (remaining > 0) {
        char *new_storage = malloc(remaining + 1);
        if (!new_storage) {
            free(line);
            return NULL;
        }
        for (int i = 0; i < remaining; i++) {
            new_storage[i] = storage[nl_pos + 1 +i];
        }
        new_storage[remaining] = '\0';
        free(storage);
        storage = new_storage;
    } else {
        free(storage);
        storage = NULL;
    }
    return line;
}

// reads from `fd`, returns a line as a heap-allocated string
char *my_readline(int fd) {
    char *buf =malloc(READLINE_READ_SIZE);
    if (!buf) return NULL;

    while(1) {
        int nl_pos = find_nl(storage);
        if (nl_pos >= 0){
            free(buf);
            return extract_line(nl_pos);
        }
        int bytes = read(fd, buf, READLINE_READ_SIZE);
        if (bytes <= 0) break;

        storage = str_join(storage, buf, bytes);
        if (!storage) {
            free(buf);
            return NULL;
        }
    }
    free(buf);

    if (!storage || storage[0] == '\0') {
        free(storage);
        storage =   NULL;
        return NULL;
    }
    char *last_line = storage;
    storage = NULL;
    return last_line;
}


int main(int argc, char **argv) {
    int fd = 0;
    if (argc > 1){
        fd = open(argv[1], O_RDONLY);
        if (fd < 0) return 1;
    }
        
    char *line;
    while ((line = my_readline(fd)) != NULL) {
        printf("%s\n", line);
        free(line);
    }

    if (fd != 0)
        close(fd);
    init_my_readline();

    return 0;
}