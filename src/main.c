#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void countdir(const char *name) {
    DIR *dir;
    struct dirent *entry;
    int count = 0;

    if (!(dir = opendir(name))) {
        return;
    }

    if (!(entry = readdir(dir))) {
        return;
    }

    do {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        count++;

        if (entry->d_type == DT_DIR) {
            char path[BUFSIZ];
            int len = snprintf(path, sizeof(path) - 1, "%s/%s", name, entry->d_name);
            path[len] = 0;

            countdir(path);
        }
    } while ((entry = readdir(dir)));

    printf("%d %s\n", count, name);
    closedir(dir);
}

int main(int argc, char **argv) {
    char *root = ".";

    if (argc >= 2) {
        root = argv[1];
    }

    countdir(root);
    return EXIT_SUCCESS;
}
