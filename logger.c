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

    return 0;
}