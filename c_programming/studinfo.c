#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

// Structure to hold student information
struct Student {
    int id;
    char name[50];
    float grades[5];
    float gpa;
};

// Function to calculate GPA
float calculateGPA(float grades[], int numSubjects) {
    float total = 0;
    for (int i = 0; i < numSubjects; i++) {
        total += grades[i];
    }
    return total / numSubjects;
}

// Function to add a student record
void addStudent(struct Student students[], int *numStudents) {
    if (*numStudents >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }

    struct Student newStudent;
    printf("Enter student ID: ");
    scanf("%d", &newStudent.id);

    printf("Enter student name: ");
    getchar();  // Consume the newline character left by scanf
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;  // Remove newline

    printf("Enter grades for 5 subjects: ");
    for (int i = 0; i < 5; i++) {
        scanf("%f", &newStudent.grades[i]);
    }

    newStudent.gpa = calculateGPA(newStudent.grades, 5);
    students[*numStudents] = newStudent;
    (*numStudents)++;
    printf("Student added successfully.\n");
}

// Function to display all student records
void displayStudents(struct Student students[], int numStudents) {
    if (numStudents == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\nStudent Records:\n");
    printf("ID\tName\t\tGPA\n");
    for (int i = 0; i < numStudents; i++) {
        printf("%d\t%s\t%.2f\n", students[i].id, students[i].name, students[i].gpa);
    }
}

// Function to search for a student by ID
int searchStudentByID(struct Student students[], int numStudents, int id) {
    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Function to edit a student's information
void editStudent(struct Student students[], int numStudents) {
    int id;
    printf("Enter the ID of the student to edit: ");
    scanf("%d", &id);

    int index = searchStudentByID(students, numStudents, id);
    if (index == -1) {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    struct Student *student = &students[index];
    printf("Editing student: %s\n", student->name);

    printf("Enter new name: ");
    getchar();  // Consume the newline character
    fgets(student->name, sizeof(student->name), stdin);
    student->name[strcspn(student->name, "\n")] = 0;  // Remove newline

    printf("Enter new grades for 5 subjects: ");
    for (int i = 0; i < 5; i++) {
        scanf("%f", &student->grades[i]);
    }

    student->gpa = calculateGPA(student->grades, 5);
    printf("Student updated successfully.\n");
}

// Function to delete a student
void deleteStudent(struct Student students[], int *numStudents) {
    int id;
    printf("Enter the ID of the student to delete: ");
    scanf("%d", &id);

    int index = searchStudentByID(students, *numStudents, id);
    if (index == -1) {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    for (int i = index; i < *numStudents - 1; i++) {
        students[i] = students[i + 1];
    }

    (*numStudents)--;
    printf("Student deleted successfully.\n");
}

// Function to save student records to a file
void saveToFile(struct Student students[], int numStudents) {
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fwrite(&numStudents, sizeof(int), 1, file);
    fwrite(students, sizeof(struct Student), numStudents, file);
    fclose(file);
    printf("Data saved to file.\n");
}

// Function to load student records from a file
void loadFromFile(struct Student students[], int *numStudents) {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("No data file found. Starting fresh.\n");
        return;
    }

    fread(numStudents, sizeof(int), 1, file);
    fread(students, sizeof(struct Student), *numStudents, file);
    fclose(file);
    printf("Data loaded from file.\n");
}

// Function to display the menu
void displayMenu() {
    printf("\nStudent Management System\n");
    printf("1. Add student\n");
    printf("2. Edit student\n");
    printf("3. Delete student\n");
    printf("4. Display all students\n");
    printf("5. Save data\n");
    printf("6. Load data\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Student students[MAX_STUDENTS];
    int numStudents = 0;
    int choice;

    // Load data from file
    loadFromFile(students, &numStudents);

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &numStudents);
                break;
            case 2:
                editStudent(students, numStudents);
                break;
            case 3:
                deleteStudent(students, &numStudents);
                break;
            case 4:
                displayStudents(students, numStudents);
                break;
            case 5:
                saveToFile(students, numStudents);
                break;
            case 6:
                loadFromFile(students, &numStudents);
                break;
            case 7:
                saveToFile(students, numStudents);
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
