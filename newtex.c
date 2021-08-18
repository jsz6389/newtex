/* SPDX-License-Identifier: GPL-2.0-only
 *
 * newtex.c
 *
 * A utility for creating new files from templates
 *
 * Copyright (C) 2021 Jakob Zielinski <jakobzee3@gmail.com>
 */
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<getopt.h>
#include<string.h>
#include<limits.h>

#define DEFAULT_CONFIG "/etc/newtex.d/newtex.conf"
#define DEFAULT_TEMPLATE_DIR "/etc/newtex.d/templates/"


/*
 * Builds the path of the template
 *
 * @param template The name of the template to use
 *
 * @param extension The file extension to use
 */
char* build_templatepath(char* template, char* extension){
    int length = sizeof(DEFAULT_TEMPLATE_DIR);
    length += strlen(template);
    length += strlen(extension);

    char* filepath = (char*)malloc(length);
    strncat(filepath, DEFAULT_TEMPLATE_DIR, length);
    strncat(filepath, template, length);
    strncat(filepath, extension, length);

    return filepath;
}


/*
 * Builds a filepath
 *
 * @param filename The name of the file
 *
 * @param extension The file extension to use
 *
 * @return The complete filepath
 */
char* build_filepath(char* filename, char* extension){
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    int length = sizeof(cwd);
    length += strlen(filename);
    length += strlen(extension);
    length++;

    char* filepath = (char*)malloc(length);
    strncat(filepath, cwd, length);
    strncat(filepath, "/", length);
    strncat(filepath, filename, length);
    strncat(filepath, extension, length);

    return filepath;
}


/*
 * Builds a template with the provided args
 *
 * @param filepath The path of the new file
 *
 * @param template The template to build the file from
 */
void build_template(char* filepath, char* template){
    char *args[]={"/bin/cp", template, filepath, NULL};
    execvp(args[0], args);
}


int main(int argc, char *argv[]){
    int option_index = 0;
    int opt;

    char* filename = NULL;
    char* template = "base";
    char* extension = ".tex";

    // Read the options
    struct option long_options[] = {
        {"filename", required_argument, NULL, 'f'},
        {"template", required_argument, NULL, 't'},
        {"extension", required_argument, NULL, 'e'}
    };
    while((opt = getopt_long(argc, argv, "f:t:e", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 't':
                template = optarg;
                break;
            case 'e':
                extension = optarg;
                break;
            default:
                exit(1);
        }
    }

    if (filename == NULL) {
        fprintf(stderr, "No filename provided\n");
        exit(1);
    }

    char* filepath = build_filepath(filename, extension);
    printf("%s\n", filepath);
    char* templatepath = build_templatepath(template, extension);
    printf("%s\n", templatepath);
    build_template(filepath, templatepath);

    return 0;
}

