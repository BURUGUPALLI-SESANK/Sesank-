#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

// Structure to hold book information
struct Book {
    int id;
    char title[100];
    char author[50];
    int year;
    int availableCopies;
};

// Function to add a book record
void addBook(struct Book books[], int *numBooks) {
    if (*numBooks >= MAX_BOOKS) {
        printf("Cannot add more books. Maximum limit reached.\n");
        return;
    }

    struct Book newBook;
    printf("Enter book ID: ");
    scanf("%d", &newBook.id);

    printf("Enter book title: ");
    getchar();  // Consume newline left by scanf
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0;  // Remove newline

    printf("Enter book author: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0;  // Remove newline

    printf("Enter publication year: ");
    scanf("%d", &newBook.year);

    printf("Enter number of available copies: ");
    scanf("%d", &newBook.availableCopies);

    books[*numBooks] = newBook;
    (*numBooks)++;
    printf("Book added successfully.\n");
}

// Function to display all book records
void displayBooks(struct Book books[], int numBooks) {
    if (numBooks == 0) {
        printf("No books to display.\n");
        return;
    }

    printf("\nBook Records:\n");
    printf("ID\tTitle\t\tAuthor\t\tYear\tAvailable Copies\n");
    for (int i = 0; i < numBooks; i++) {
        printf("%d\t%s\t%s\t%d\t%d\n", books[i].id, books[i].title, books[i].author, books[i].year, books[i].availableCopies);
    }
}

// Function to search for a book by ID
int searchBookByID(struct Book books[], int numBooks, int id) {
    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Function to edit book details
void editBook(struct Book books[], int numBooks) {
    int id;
    printf("Enter the ID of the book to edit: ");
    scanf("%d", &id);

    int index = searchBookByID(books, numBooks, id);
    if (index == -1) {
        printf("Book with ID %d not found.\n", id);
        return;
    }

    struct Book *book = &books[index];
    printf("Editing book: %s\n", book->title);

    printf("Enter new title: ");
    getchar();  // Consume the newline character
    fgets(book->title, sizeof(book->title), stdin);
    book->title[strcspn(book->title, "\n")] = 0;  // Remove newline

    printf("Enter new author: ");
    fgets(book->author, sizeof(book->author), stdin);
    book->author[strcspn(book->author, "\n")] = 0;  // Remove newline

    printf("Enter new publication year: ");
    scanf("%d", &book->year);

    printf("Enter new number of available copies: ");
    scanf("%d", &book->availableCopies);

    printf("Book updated successfully.\n");
}

// Function to delete a book record
void deleteBook(struct Book books[], int *numBooks) {
    int id;
    printf("Enter the ID of the book to delete: ");
    scanf("%d", &id);

    int index = searchBookByID(books, *numBooks, id);
    if (index == -1) {
        printf("Book with ID %d not found.\n", id);
        return;
    }

    for (int i = index; i < *numBooks - 1; i++) {
        books[i] = books[i + 1];
    }

    (*numBooks)--;
    printf("Book deleted successfully.\n");
}

// Function to save book records to a file
void saveToFile(struct Book books[], int numBooks) {
    FILE *file = fopen("library.dat", "wb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fwrite(&numBooks, sizeof(int), 1, file);
    fwrite(books, sizeof(struct Book), numBooks, file);
    fclose(file);
    printf("Data saved to file.\n");
}

// Function to load book records from a file
void loadFromFile(struct Book books[], int *numBooks) {
    FILE *file = fopen("library.dat", "rb");
    if (file == NULL) {
        printf("No data file found. Starting fresh.\n");
        return;
    }

    fread(numBooks, sizeof(int), 1, file);
    fread(books, sizeof(struct Book), *numBooks, file);
    fclose(file);
    printf("Data loaded from file.\n");
}

// Function to display the menu
void displayMenu() {
    printf("\nLibrary Management System\n");
    printf("1. Add book\n");
    printf("2. Edit book\n");
    printf("3. Delete book\n");
    printf("4. Display all books\n");
    printf("5. Save data\n");
    printf("6. Load data\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Book books[MAX_BOOKS];
    int numBooks = 0;
    int choice;

    // Load data from file
    loadFromFile(books, &numBooks);

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(books, &numBooks);
                break;
            case 2:
                editBook(books, numBooks);
                break;
            case 3:
                deleteBook(books, &numBooks);
                break;
            case 4:
                displayBooks(books, numBooks);
                break;
            case 5:
                saveToFile(books, numBooks);
                break;
            case 6:
                loadFromFile(books, &numBooks);
                break;
            case 7:
                saveToFile(books, numBooks);
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
