#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "functions.h"

#define MAX 30

// Root declaration
struct RBNode *tree;

void display(struct RBNode *);

int main()
{
    int opt;
    struct RBNode *newContact, *search, *delete;
    char name[MAX], no[MAX], mail[MAX], buff[5];
    char query[MAX], val[MAX];

    do
    {
        printf("\n\n#####Phone directory application#####");
        printf("\n1. Create a Phone Directory");
        printf("\n2. Enter a new contact");
        printf("\n3. Search for a contact");
        printf("\n4. Display the phone directory");
        printf("\n5. Delete a contact");
        printf("\n6. EXIT!");
        printf("\nChoose an option: ");
        scanf("%d", &opt);

        switch (opt)
        {
        case 1:
            create_RBTree(tree);
            break;
        case 2:
            printf("\nProcessing...");
            fgets(buff, MAX, stdin);
            printf("\nEnter name: ");
            fgets(name, MAX, stdin);
            printf("\nEnter number: ");
            fgets(no, MAX, stdin);
            printf("\nEnter email: ");
            fgets(mail, MAX, stdin);
            newContact = create_node(name, no, mail);
            tree = insertNode(tree, newContact);
            break;
        case 3:
            printf("\nProcessing...");
            fgets(buff, MAX, stdin);
            printf("\nEnter search query: ");
            fgets(query, MAX, stdin);
            search = nodeHavingValue(tree, query);
            display(search);
            break;
        case 4:
            inOrderTraverseTree(tree);
            break;
        case 5:
            printf("\nProcessing...");
            fgets(buff, MAX, stdin);
            printf("\nDelete the value: ");
            fgets(val, MAX, stdin);
            delete = nodeHavingValue(tree, val);
            tree = deleteNode(tree, delete);
            break;
        }
    } while (opt != 6);
}

void create_RBTree(struct RBNode *tree)
{
    tree = NULL;
}

void inOrderTraverseTree(struct RBNode *root)
{
    if (root != NULL)
    {
        inOrderTraverseTree(root->left);
        printf("\n %s ", root->contactName);
        printf("%s ", root->contactNo);
        printf("%s ", root->email);
        inOrderTraverseTree(root->right);
    }
}

void display(struct RBNode *node_to_display)
{
    printf("\nContact Name: %s", node_to_display->contactName);
    printf("\nContact No: %s", node_to_display->contactNo);
    printf("\nContact email: %s", node_to_display->email);
}