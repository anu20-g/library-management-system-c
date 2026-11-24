/*
 * Library Management System (File Handling)
 * Team 1
 * Concepts: Structures, File Handling
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[60];
    char author[40];
    int isIssued; // 0: Available, 1: Issued
};

void addBook() {
    FILE *fp = fopen("library.dat", "ab");
    if (!fp) { printf("Error opening file!\n"); return; }
    struct Book b;
    printf("\nEnter Book ID: ");
    scanf("%d", &b.id);
    getchar();
    printf("Enter Book Title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = 0;
    printf("Enter Author: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = 0;
    b.isIssued = 0;
    fwrite(&b, sizeof(struct Book), 1, fp);
    fclose(fp);
    printf(">> Book record saved to file.\n");
}

void displayBooks() {
    FILE *fp = fopen("library.dat", "rb");
    if (!fp) { printf("\nNo book catalog found.\n"); return; }
    struct Book b;
    printf("\n======================== BOOK CATALOG ========================\n");
    printf("%-8s %-30s %-20s %-10s\n", "ID", "Title", "Author", "Status");
    printf("--------------------------------------------------------------\n");
    while (fread(&b, sizeof(struct Book), 1, fp)) {
        printf("%-8d %-30s %-20s %-10s\n", b.id, b.title, b.author, b.isIssued ? "ISSUED" : "AVAILABLE");
    }
    printf("==============================================================\n");
    fclose(fp);
}

void searchBook() {
    FILE *fp = fopen("library.dat", "rb");
    if (!fp) { printf("Catalog empty.\n"); return; }
    int id, found = 0;
    struct Book b;
    printf("Enter Book ID to search: ");
    scanf("%d", &id);
    while (fread(&b, sizeof(struct Book), 1, fp)) {
        if (b.id == id) {
            printf("Found: ID %d | Title: %s | Author: %s | %s\n",
                   b.id, b.title, b.author, b.isIssued ? "Currently Issued" : "Available");
            found = 1;
            break;
        }
    }
    if (!found) printf("Book ID %d not found.\n", id);
    fclose(fp);
}

int main() {
    int choice;
    while (1) {
        printf("\n--- LIBRARY MANAGEMENT SYSTEM ---\n");
        printf("1. Add Book\n2. View All Books\n3. Search Book\n4. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1 || choice == 4) break;
        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            default: printf("Invalid choice.\n");
        }
    }
    printf("Library portal closed.\n");
    return 0;
}
