/*
   ADMISSION MANAGEMENT SYSTEM

   STUDENT 1: Ashutosh
   Contribution:
   - Login System (Authentication)
   - Add Record
   - Modify Record
   - Delete Record

   STUDENT 2: Aryan
   Contribution:
   - View Records
   - Search Record
   - Main Menu Control
    */

#include <stdio.h>
#include <string.h>

// Structure
struct Student
{
    long long int id;
    char name[50];
    char course[50];
    float fees;
};

// Login
int login()
{
    char user[20], pass[20];

    printf("\n--- LOGIN ---\n");
    printf("Enter Username: ");
    scanf("%s", user);

    printf("Enter Password: ");
    scanf("%s", pass);

    if (strcmp(user, "graphic") == 0 && strcmp(pass, "0987") == 0)
        return 1;

    return 0;
}

// Add Record
void addRecord()
{
    struct Student s;
    FILE *fp = fopen("students.dat", "ab");

    if (fp == NULL)
    {
        printf("File error!\n");
        return;
    }

    printf("\nEnter ID: ");
    scanf("%lld", &s.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    printf("Enter Fees: ");
    scanf("%f", &s.fees);

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);
    printf("Record added!\n");
}

// View All
void viewAll()
{
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("No records found.\n");
        return;
    }

    printf("\n%-15s %-20s %-15s %-10s\n", "ID", "Name", "Course", "Fees");
    printf("-----------------------------------------------------------------\n");

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.id != -1)
            printf("%-15lld %-20s %-15s %-10.2f\n", s.id, s.name, s.course, s.fees);
    }
    fclose(fp);
}

// Search
void searchRecord()
{
    struct Student s;
    long long int targetID;
    int found = 0;

    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("No records found.\n");
        return;
    }

    printf("\nEnter ID to Search: ");
    scanf("%lld", &targetID);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.id == targetID)
        {
            printf("\nRecord Found:\n");
            printf("Name: %s\nCourse: %s\nFees: %.2f\n",
                   s.name, s.course, s.fees);
            found = 1;
            break;
        }
    }

    if (found == 0)
        printf("Record not found.\n");

    fclose(fp);
}

// Modify
void modifyRecord()
{
    struct Student s;
    long long int targetID;
    int found = 0;

    FILE *fp = fopen("students.dat", "rb+");

    if (fp == NULL)
    {
        printf("File error!\n");
        return;
    }

    printf("\nEnter ID to Modify: ");
    scanf("%lld", &targetID);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.id == targetID)
        {
            found = 1;

            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Course: ");
            scanf(" %[^\n]", s.course);

            printf("Enter New Fees: ");
            scanf("%f", &s.fees);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            printf("Record updated!\n");
            break;
        }
    }

    if (found == 0)
        printf("ID not found.\n");

    fclose(fp);
}

// Delete (Logical)
void deleteRecord()
{
    struct Student s;
    long long int targetID;
    int found = 0;

    FILE *fp = fopen("students.dat", "rb+");

    if (fp == NULL)
    {
        printf("File error!\n");
        return;
    }

    printf("\nEnter ID to Delete: ");
    scanf("%lld", &targetID);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.id == targetID)
        {
            found = 1;

            s.id = -1; // mark as deleted

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            printf("Record deleted!\n");
            break;
        }
    }

    if (found == 0)
        printf("ID not found.\n");

    fclose(fp);
}

// MAIN
int main()
{
    int x = login();
    if (x == 0)
    {
        printf("Invalid credentials!\n");
        return 0;
    }

    int choice;

    while (1)
    {
        printf("\n---- ADMISSION MANAGEMENT SYSTEM ----\n");
        printf("1. Add\n2. View\n3. Search\n4. Modify\n5. Delete\n6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addRecord();
            break;
        case 2:
            viewAll();
            break;
        case 3:
            searchRecord();
            break;
        case 4:
            modifyRecord();
            break;
        case 5:
            deleteRecord();
            break;
        case 6:
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }
}