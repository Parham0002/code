/**
 * @file exam.h
 * @author Parham Rezaei (knightpslow@gmail.com)
 * @brief Exam program header file is for student management program using binary files in C.
 * it is a simple program that allows the user to create, update, and delete student records.
 * and  it uses binary files to store the student records.
 * @date 2024-12-05
 *
 * @copyright Copyright (c) 2024
 *
 */

// exam.h header file for exam program
#ifndef EXAM_H
#define EXAM_H

// include standard library headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

// define constants for program
#define FILENAME "students.bin"
#define NAME_LEN 32
#define MAX_STUDENTS 100
#define SINGLE_STUDENT 1
#define ZERO 0
#define ONE 1

/**
 * @brief typedef for student structc
 * and it is used to store student information
 */
typedef struct student
{
    char name[NAME_LEN];
    uint32_t id;
    uint8_t age;
} Student;

/**
 * @brief Create a student object
 * and it is used to create a new student record
 * and it is used to store student information
 * @param filename
 */
void create_student(const char *filename);

/**
 * @brief
 *  it is used to print all student records and
 * and it is used to store student information
 * @param filename
 */
void print_student(const char *filename);

/**
 * @brief
 * it is used to update a student record
 * @param filename
 * @param id
 * @param newname
 * @param age
 */
void update_student(const char *filename, uint32_t id, const char *newname, uint8_t age);
/**
 * @brief
 *  it is used to delete a student record
 * and it is used to store student information
 * @param filename
 * @param id
 */
void delete_student(const char *filename, uint32_t id);

#endif // EXAM_H