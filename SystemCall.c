#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

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
    char path[1024];

    printf("Enter the directory path (or '.' for current directory): ");
    scanf("%s", path);

    dir = opendir(path);
    if (dir == NULL) {
        perror("Unable to open directory");
        return;
    }

    printf("\nList of files:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}

void create_directory() {
    char dir_name[1024];
    printf("Enter the new directory name: ");
    scanf("%s", dir_name);

    if (mkdir(dir_name, 0755) == 0) {
        printf("Directory '%s' created successfully.\n", dir_name);
    } else {
        perror("Failed to create directory");
    }
}

void change_directory() {
    char path[1024];
    char cwd[1024];

    printf("Enter the path to change directory to: ");
    scanf("%s", path);

    if (chdir(path) == 0) {
        getcwd(cwd, sizeof(cwd));
        printf("Directory changed successfully to: %s\n", cwd);
    } else {
        perror("Failed to change directory");
    }
}
