/*
 * includes printf, fgets, fopen, fprintf, fclose
 * time(), ctime() 
 * strlen() strip newline from ctime() output
 */
#include <stdio.h>
#include <time.h>
#include <string.h>

int main() 
{
    // filename path to output md in obsidian vault
    char filename[200];
    // reused for each answer to 10 log encode/transfer prompts
    char buffer[500];

    printf("Problem name (e.g. LC0323-Connected-Components): ");
    fgets(filename, 200, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE *f = fopen(filename, "a");
        if (!f) { printf("ERROR: cannot open file\n"); return 1; }
    return 0;

    fopen:
        time_t now = time(NULL)
        char *ts = ctime(&now)
        ts[strcspn(ts, "\n")] = '\0';          // strip newline from ctime output
        fprintf(f, "# %s\n*%s*\n\n", filename, ts);  

    const char *prompts[10] = {
        "Problem summary: "
    }
}