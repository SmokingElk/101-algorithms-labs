#include <iostream>
#include <string.h>

#include "student.h"

using namespace std;

int readStudent(Student *st)
{
    cin >> st->surname;
    if (strcmp(st->surname, "-1") == 0)
    {
        return 0;
    }
    cin >> st->initials;
    cin >> st->group;
    cin >> st->math_grade;
    cin >> st->physics_grade;
    cin >> st->informatics_grade;
    return 1;
}

int main()
{
    char fileName[] = "db.bin";
    // cin >> fileName;
    Student st;
    FILE *out = fopen(fileName, "w");
    if (!out)
    {
        cout << "Не получилось открыть файл";
        return 0;
    }
    while (readStudent(&st))
    {
        // cout << st.group;
        fwrite(&st, sizeof(st), 1, out);
    }
    fclose(out);
}
