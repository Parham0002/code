#include "tamrin.h"

int main()
{
    int choice;
    char name[SIZE_LEN];
    int id;

    do
    {
        printf("\n--- Menu ---\n");
        printf("1. Create Record\n");
        printf("2. Read Records\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create_record(FILENAME);
            break;
        case 2:
            read_record(FILENAME);
            break;
        case 3:
            printf("Enter ID of the record to update: ");
            scanf("%d", &id);
            printf("Enter new Name: ");
            scanf("%s", name);
            update_record(FILENAME, id, name);
            break;
        case 4:
            printf("Enter ID of the record to delete: ");
            scanf("%d", &id);
            delete_record(FILENAME, id);
            break;
        case 5:
            printf("Exiting program.\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}