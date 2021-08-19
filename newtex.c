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
#include<libconfig.h>

#define DEFAULT_CONFIG "/etc/newtex.d/newtex.conf"


/*
 * Verifies that the new file doesn't already exist and 
 * that the template file exists
 *
 * @param filename The file
 *
 * @param template The template
 */
void verify_paths(char* filename, char* template){
    if( access( template, F_OK ) != 0 ) {
        fprintf( stderr, "Specified template doesn't exist.\n" );
        exit(1);
    }

    if( access( filename, F_OK ) == 0 ) {
        fprintf( stderr, "Specified file already exists.\n" );
        exit(1);
    }
}


/*
 * Builds the path of the template
 *
 * @param template The name of the template to use
 *
 * @param extension The file extension to use
 *
 * @param template_dir The directory of the template file
 */
char* build_templatepath(char* template, char* extension, char* template_dir){
    int length = strlen(template_dir);
    length += strlen(template);
    length += strlen(extension);

    char* filepath = (char*)malloc(length);
    filepath[0] = '\0';
    strcat(filepath, template_dir);
    strcat(filepath, template);
    strcat(filepath, extension);

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
    filepath[0] = '\0';
    strcat(filepath, cwd);
    strcat(filepath, "/");
    strcat(filepath, filename);
    strcat(filepath, extension);

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
    char *template_dir, *template, *extension, *filename = NULL;

    // Read the config file
    config_t cfg, *cf;
    cf = &cfg;
    config_init(cf);
    config_read_file(cf, DEFAULT_CONFIG);

    config_lookup_string(cf, "template_dir", (const char**)&template_dir);
    config_lookup_string(cf, "template", (const char**)&template);
    config_lookup_string(cf, "extension", (const char**)&extension);

    // Read the options
    struct option long_options[] = {
        {"template", required_argument, NULL, 't'},
        {"extension", required_argument, NULL, 'e'},
        {"directory", required_argument, NULL, 'd'}
    };
    while((opt = getopt_long(argc, argv, "t:e:d:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 't':
                template = optarg;
                break;
            case 'e':
                extension = optarg;
                break;
            case 'd':
                template_dir = optarg;
                break;
            default:
                exit(1);
        }
    }

    filename = argv[optind];

    if (filename == NULL) {
        fprintf(stderr, "No filename provided\n");
        exit(1);
    }

    char* filepath = build_filepath(filename, extension);
    char* templatepath = build_templatepath(template, extension, template_dir);
    verify_paths(filepath, templatepath);
    build_template(filepath, templatepath);

    return 0;
}

