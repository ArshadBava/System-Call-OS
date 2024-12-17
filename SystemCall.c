#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_PATH_LENGTH 1024

void list_files();
void create_directory();
void change_directory();
void display_menu();

int main() {
    int choice;

    do {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline from input buffer

        switch (choice) {
            case 1:
                list_files();
                break;
            case 2:
                create_directory();
                break;
            case 3:
                change_directory();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

void display_menu() {
    printf("\n\t\tMAIN MENU\n");
    printf("\t-------------------------\n");
    printf("1. Display List of Files\n");
    printf("2. Create New Directory\n");
    printf("3. Change the Working Directory\n");
    printf("4. Exit\n");
}

void list_files() {
    DIR *dir;
    struct dirent *entry;
    char path[MAX_PATH_LENGTH];

    printf("Enter the directory path (or '.' for current directory): ");
    // Limiting the number of characters to avoid buffer overflow
    if (scanf("%1023s", path) != 1) {
        printf("Invalid input.\n");
        return;
    }

    dir = opendir(path);
    if (dir == NULL) {
        perror("Unable to open directory");
        return;
    }

    printf("\nList of files in %s:\n", path);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}

void create_directory() {
    char dir_name[1024];
    printf("Enter the new directory name: ");
    if (scanf("%1023s", dir_name) != 1) {
        printf("Invalid input.\n");
        return;
    }

    // Windows does not use the second argument for mkdir, so we remove 0755
    if (mkdir(dir_name) == 0) {
        printf("Directory '%s' created successfully.\n", dir_name);
    } else {
        perror("Failed to create directory");
    }
}

void change_directory() {
    char path[MAX_PATH_LENGTH];
    char cwd[MAX_PATH_LENGTH];

    printf("Enter the path to change directory to: ");
    if (scanf("%1023s", path) != 1) {
        printf("Invalid input.\n");
        return;
    }

    if (chdir(path) == 0) {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Directory changed successfully to: %s\n", cwd);
        } else {
            perror("getcwd failed");
        }
    } else {
        perror("Failed to change directory");
    }
}
