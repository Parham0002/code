#include "exam.h" // exam.h header file
int main()
{
    char choice;
    uint32_t id;
    char name[NAME_LEN];
    uint8_t age;
    Student student;

    // loop until exit
    do
    {
        printf("\n--- Menu ---\n");
        printf("C) Create A Student\n");
        printf("P) Print all Students\n");
        printf("U) Update A Student\n");
        printf("D) Delete A Student\n");
        printf("E) Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        getchar();
        // switch case for menu
        switch ((int)tolower(choice))
        {
        case 'c':
            create_student(FILENAME); // create student
            break;
        case 'p':
            print_student(FILENAME); // print students
            break;
        case 'u': // update student
            printf("Enter ID of the student to update: ");
            scanf("%u", &id);
            getchar();
            printf("Enter new Name: ");
            scanf("%s", name);
            getchar();
            printf("Enter new Age: ");
            scanf("%hhu", &age);
            getchar();
            update_student(FILENAME, id, name, age);
            break;
        case 'd': // delete student
            printf("Enter ID of the student to delete: ");
            scanf("%u", &id);
            getchar();
            delete_student(FILENAME, id);
            break;
        case 'e': /// exit
            printf("Exiting program.\n");
            break;
        default: // invalid choice
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 'e');
    return 0;
}
