#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 50
#define MAX_CHILDREN 100

typedef struct Node
{
    char name[NAME_SIZE];
    int is_directory;                    // 1 if directory, 0 if file
    struct Node *parent;                 // Parent directory
    struct Node *children[MAX_CHILDREN]; // List of children (for directories only)
    int child_count;                     // Number of children in this directory
} Node;

Node *create_node(const char *name, int is_directory, Node *parent)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    strcpy(new_node->name, name);
    new_node->is_directory = is_directory;
    new_node->parent = parent;
    new_node->child_count = 0;
    return new_node;
}

void change_directory(Node **current_directory, const char *dir_name)
{
    if (strcmp(dir_name, "..") == 0)
    { // Move to parent directory
        if ((*current_directory)->parent != NULL)
        {
            *current_directory = (*current_directory)->parent;
        }
        else
        {
            printf("Already at root directory.\n");
        }
    }
    else
    { // Move to a child directory
        for (int i = 0; i < (*current_directory)->child_count; i++)
        {
            if ((*current_directory)->children[i]->is_directory && strcmp((*current_directory)->children[i]->name, dir_name) == 0)
            {
                *current_directory = (*current_directory)->children[i];
                return;
            }
        }
        printf("Directory not found: %s\n", dir_name);
    }
}

void make_directory(Node *current_directory, const char *dir_name)
{
    for (int i = 0; i < current_directory->child_count; i++)
    {
        if (strcmp(current_directory->children[i]->name, dir_name) == 0)
        {
            printf("Directory or file with name '%s' already exists.\n", dir_name);
            return;
        }
    }

    if (current_directory->child_count < MAX_CHILDREN)
    {
        Node *new_dir = create_node(dir_name, 1, current_directory); // 1 indicates directory
        current_directory->children[current_directory->child_count++] = new_dir;
    }
    else
    {
        printf("Maximum number of children reached.\n");
    }
}

void create_file(Node *current_directory, const char *file_name)
{
    // Ensure the file does not already exist
    for (int i = 0; i < current_directory->child_count; i++)
    {
        if (strcmp(current_directory->children[i]->name, file_name) == 0)
        {
            printf("File or directory with name '%s' already exists.\n", file_name);
            return;
        }
    }

    if (current_directory->child_count < MAX_CHILDREN)
    {
        Node *new_file = create_node(file_name, 0, current_directory); // 0 indicates file
        current_directory->children[current_directory->child_count++] = new_file;
    }
    else
    {
        printf("Maximum number of children reached.\n");
    }
}

void list_contents(Node *current_directory)
{
    for (int i = 0; i < current_directory->child_count; i++)
    {
        if (current_directory->children[i]->is_directory)
        {
            printf("[DIR] %s\n", current_directory->children[i]->name);
        }
        else
        {
            printf("[FILE] %s\n", current_directory->children[i]->name);
        }
    }
}

void display_tree(Node *current_directory, int level)
{
    // Print the name of the current directory/file
    for (int i = 0; i < level; i++)
    {
        printf("  "); // Indentation to represent hierarchy
    }

    if (current_directory->is_directory)
    {
        printf("[DIR] %s\n", current_directory->name);
    }
    else
    {
        printf("[FILE] %s\n", current_directory->name);
    }

    // Recursively print all children
    for (int i = 0; i < current_directory->child_count; i++)
    {
        display_tree(current_directory->children[i], level + 1);
    }
}

int main()
{
    // Create the root directory
    Node *root = create_node("root", 1, NULL);
    Node *current_directory = root;

    char command[NAME_SIZE];
    char argument[NAME_SIZE];

    printf("Welcome to the simple file system!\n");

    while (1)
    {
    RESTART:
        printf("\nCurrent Directory: %s> ", current_directory->name);
        scanf("%s", command);

        if (strcmp(command, "cd") == 0)
        {
            scanf("%s", argument);
            change_directory(&current_directory, argument);
        }
        else if (strcmp(command, "mkdir") == 0)
        {
            scanf("%s", argument);
            make_directory(current_directory, argument);
        }
        else if (strcmp(command, "touch") == 0)
        {
            scanf("%s", argument);
            create_file(current_directory, argument);
        }
        else if (strcmp(command, "ls") == 0)
        {
            list_contents(current_directory);
        }
        else if (strcmp(command, "exit") == 0)
        {
            break;
        }
        else if (strcmp(command, "tree") == 0)
        {
            display_tree(root, 0); // Start from the root, level 0
        }
        else if (strcmp(command, "clear") == 0)
        {
            system("clear");
            goto RESTART;
            break;
        }
        else
        {
            printf("Unknown command.\n");
        }
    }

    return 0;
}