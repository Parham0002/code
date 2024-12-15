#include "exam.h" // exam.h header file
// global variables
static uint32_t max_id = ONE;
// create student
void create_student(const char *filename)
{
    // open file
    FILE *file = fopen(filename, "ab");
    // check file
    if (!file)
    {
        perror("unable to open file");
        return;
    }
    // create student
    Student student;
    // get student info
    printf("Enter Name: ");
    scanf("%s", student.name);
    printf("Enter Age: ");
    scanf("%hhu", &student.age);
    // set id
    student.id = max_id++;
    // write to file
    fseek(file, ZERO, SEEK_END);
    fwrite(&student, sizeof(Student), SINGLE_STUDENT, file);
    fclose(file);
    printf("student created successfully.\n");
}

// print students
void print_student(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    // check if file exists
    if (!file)
    {
        perror("unable to open file");
        return;
    }
    // check if file is empty
    fseek(file, ZERO, SEEK_END);
    long size = ftell(file);
    if (size == ZERO)
    {
        printf("File is empty - no student records found!\n");
        fclose(file);
        return;
    }
    rewind(file);
    // print students
    Student student;

    printf("ID\tName\tAge\n");
    printf("------------------\n");
    // read students
    while (fread(&student, sizeof(Student), SINGLE_STUDENT, file) == ONE)
    {
        printf("%u\t%s\t%u\n", student.id, student.name, student.age);
    }
    fclose(file);
}

// update student
void update_student(const char *filename, uint32_t id, const char *newname, uint8_t age)
{
    FILE *file = fopen(filename, "rb+");
    // check if file exists
    if (!file)
    {
        perror("unable to open file");
        return;
    }

    // update student
    Student student;
    // read students from file
    int found = ZERO;

    while (fread(&student, sizeof(Student), SINGLE_STUDENT, file) == ONE)
    { // check id
        if (student.id == id)
        { // update student
            found = ONE;
            strcpy(student.name, newname);
            student.age = age;
            fseek(file, -sizeof(Student), SEEK_CUR);
            fwrite(&student, sizeof(Student), SINGLE_STUDENT, file);
            break;
        }
        else
        {
            printf("student not found.\n");
            break;
        }
    }
    fclose(file);
    if (found)
    {
        printf("student updated successfully.\n");
    }
}

// delete student
void delete_student(const char *filename, uint32_t id)
{
    FILE *file = fopen(filename, "rb");
    // check file
    if (!file)
    {
        perror("unable to open file");
        return;
    }

    FILE *tempfile = fopen("temp.bin", "wb");
    // check file
    if (!tempfile)
    {
        perror("unable to open temporary file");
        fclose(file);
        return;
    }
    // delete student
    Student student;
    // read students
    int found = ZERO;

    while (fread(&student, sizeof(Student), SINGLE_STUDENT, file) == ONE)
    { // check id
        if (student.id == id)
        {
            found = ONE;
            continue;
        }
        fwrite(&student, sizeof(Student), SINGLE_STUDENT, tempfile);
    }
    fclose(file);
    fclose(tempfile);
    // remove old file
    if (found)
    {
        remove(filename);
        rename("temp.bin", filename);
        printf("Record deleted successfully.\n");
    }
    else
    {
        printf("Record not found.\n");
        remove("temp.bin");
    }
}
