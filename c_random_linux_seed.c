#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>

unsigned int seed_generate() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    unsigned int s_sec = (unsigned int)ts.tv_sec;
    unsigned int s_nano = (unsigned int)ts.tv_nsec;
    unsigned int s_urand = 1; 
    unsigned int s_tmp = 1;
    FILE *f = fopen("/dev/urandom", "rb");
    if (f) {
        fread(&s_urand, sizeof(s_urand), 1, f);
        fclose(f);
    }
    DIR *dir = opendir("/tmp");
    if (dir) {
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL) s_tmp++;
        closedir(dir);
    }
    return s_sec ^ s_nano ^ s_urand ^ s_tmp;
}
