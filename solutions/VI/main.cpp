#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "student.h"

float calculate_average(Student student)
{
    return (student.math_grade + student.physics_grade + student.informatics_grade) / 3;
}

int main()
{
    FILE *file = fopen("db.bin", "r");
    if (!file)
    {
        printf("Ошибка открытия файла.\n");
        return 1;
    }

    Student students[100]; // Предполагаем, что не более 100 студентов
    int num_students = 0;

    Student line;
    while (fread(&line, sizeof(Student), 1, file) == 1)
    {
        students[num_students] = line;
        num_students++;
    }

    fclose(file);

    // Определяем минимальный средний балл
    float min_average = calculate_average(students[0]);
    for (int i = 1; i < num_students; i++)
    {
        float average = calculate_average(students[i]);
        if (average < min_average)
        {
            min_average = average;
        }
    }

    // Подсчитываем количество студентов с минимальным средним баллом в каждой группе
    int min_average_count[100] = {0}; // Предполагаем, что группы от 1 до 100
    for (int i = 0; i < num_students; i++)
    {
        if (calculate_average(students[i]) == min_average)
        {
            min_average_count[atoi(students[i].group) - 1]++;
        }
    }

    // Находим группу с максимальным количеством студентов с минимальным средним баллом
    int max_count = 0;
    int max_count_group = -1;
    for (int i = 0; i < 100; i++)
    {
        if (min_average_count[i] > max_count)
        {
            max_count = min_average_count[i];
            max_count_group = i + 1;
        }
    }

    printf("Group with maximum students having minimum average grade: %d\n%d студент\naverage: %f", max_count_group, min_average_count[max_count_group - 1], min_average);

    return 0;
}
