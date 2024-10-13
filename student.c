#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 1000
#define PASSWORD "12345"

// Structure to hold student data
typedef struct {
    int roll_no;
    int marks[5];
    float average;
    int rank;
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

// Function to load student data from CSV file
void load_student_data(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (student_count >= MAX_STUDENTS) {
            printf("Reached maximum number of students.\n");
            break;
        }

        int roll_no, sub1, sub2, sub3, sub4, sub5;
        if (sscanf(line, "%d,%d,%d,%d,%d,%d", &roll_no, &sub1, &sub2, &sub3, &sub4, &sub5) == 6) {
            students[student_count].roll_no = roll_no;
            students[student_count].marks[0] = sub1;
            students[student_count].marks[1] = sub2;
            students[student_count].marks[2] = sub3;
            students[student_count].marks[3] = sub4;
            students[student_count].marks[4] = sub5;
            students[student_count].average = (sub1 + sub2 + sub3 + sub4 + sub5) / 5.0;
            student_count++;
        }
    }

    fclose(file);
    printf("Loaded %d students.\n", student_count);
}

// Function to rank students by their average marks
void rank_students() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = 0; j < student_count - i - 1; j++) {
            if (students[j].average < students[j + 1].average) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    // Assign ranks
    for (int i = 0; i < student_count; i++) {
        students[i].rank = i + 1;
    }
}

// Function to check login
int login(int roll_no, char *password) {
    if (strcmp(password, PASSWORD) != 0) {
        return 0; // Incorrect password
    }

    // Find student by roll number
    for (int i = 0; i < student_count; i++) {
        if (students[i].roll_no == roll_no) {
            return i; // Return index of the student
        }
    }

    return -1; // Student not found
}

// Function to display student details
void display_student(int student_index) {
    printf("Roll No: %d\n", students[student_index].roll_no);
    printf("Marks: %d, %d, %d, %d, %d\n", 
        students[student_index].marks[0],
        students[student_index].marks[1],
        students[student_index].marks[2],
        students[student_index].marks[3],
        students[student_index].marks[4]);
    printf("Average: %.2f\n", students[student_index].average);
    printf("Rank: %d\n", students[student_index].rank);
}

int main() {
    load_student_data("students.csv");
    rank_students();

    int roll_no;
    char password[10];

    // Prompt for login
    printf("Enter Roll Number: ");
    scanf("%d", &roll_no);
    printf("Enter Password: ");
    scanf("%s", password);

    int student_index = login(roll_no, password);
    if (student_index >= 0) {
        printf("Login successful!\n");
        display_student(student_index);
    } else {
        printf("Login failed! Incorrect roll number or password.\n");
    }

    return 0;
} 