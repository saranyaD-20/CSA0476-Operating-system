#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int emp_id;
    char name[50];
    float salary;
};

void addEmployee(FILE* file) {
    struct Employee employee;
    printf("Enter Employee ID: ");
    scanf("%d", &employee.emp_id);
    printf("Enter Name: ");
    scanf("%s", employee.name);
    printf("Enter Salary: ");
    scanf("%f", &employee.salary);
    fwrite(&employee, sizeof(struct Employee), 1, file);
    printf("Employee added successfully.\n");
}

void readEmployee(FILE* file) {
    int emp_id;
    printf("Enter Employee ID to read: ");
    scanf("%d", &emp_id);
    struct Employee employee;

    while (fread(&employee, sizeof(struct Employee), 1, file)) {
        if (employee.emp_id == emp_id) {
            printf("Employee ID: %d\nName: %s\nSalary: %.2f\n", employee.emp_id, employee.name, employee.salary);
            return;
        }
    }

    printf("Employee not found.\n");
}

void updateEmployee(FILE* file) {
    int emp_id;
    printf("Enter Employee ID to update: ");
    scanf("%d", &emp_id);
    struct Employee employee;
    long pos = -1;

    while (fread(&employee, sizeof(struct Employee), 1, file)) {
        pos = ftell(file) - sizeof(struct Employee);
        if (employee.emp_id == emp_id) {
            printf("Enter New Name: ");
            scanf("%s", employee.name);
            printf("Enter New Salary: ");
            scanf("%f", &employee.salary);
            fseek(file, pos, SEEK_SET);
            fwrite(&employee, sizeof(struct Employee), 1, file);
            printf("Employee updated successfully.\n");
            return;
        }
    }

    printf("Employee not found.\n");
}

void deleteEmployee(FILE* file) {
    int emp_id;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &emp_id);
    struct Employee employee;
    FILE* temp_file = fopen("temp.dat", "wb");

    while (fread(&employee, sizeof(struct Employee), 1, file)) {
        if (employee.emp_id != emp_id) {
            fwrite(&employee, sizeof(struct Employee), 1, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);
    remove("employees.dat");
    rename("temp.dat", "employees.dat");
    printf("Employee deleted successfully.\n");
}

int main() {
    FILE* file = fopen("employees.dat", "ab+");
    if (file == NULL) {
        perror("File open error");
        exit(1);
    }

    int choice;

    while (1) {
        printf("\nEmployee Record System\n");
        printf("1. Add Employee\n");
        printf("2. Read Employee\n");
        printf("3. Update Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(file);
                break;
            case 2:
                readEmployee(file);
                break;
            case 3:
                updateEmployee(file);
                break;
            case 4:
                deleteEmployee(file);
                file = fopen("employees.dat", "ab+"); // Reopen the file in append and read mode
                break;
            case 5:
                fclose(file);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}

