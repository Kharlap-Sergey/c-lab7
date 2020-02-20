// Union_and_counting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// добавить вывод должности у teacher и вывод положение у customer
#include <iostream>

using namespace std;

const int IdentifyLen = 15;
const int lastNameLen = 20;
const int MaxAmountOfPeople = 5;

struct Position{
    bool techer = false;
    bool headtecher = false;
    bool professor = false;
    bool docent = false;
};
struct Specification {
    bool one = false;
    bool two = false;
    bool three = false;
    bool fore = false;
};

struct Gender {
    bool man = false,
        woman = false;
};

struct Student {
    char examboockNumber[IdentifyLen] = "NON";
    char lastName[lastNameLen] = "";
    double averageGrade;
    Gender gender;
};

struct Teacher {
    char identifyNumber[IdentifyLen] = "NON";
    char lastName[lastNameLen] = "";
    Position position;
};
struct Customer {
    char pusportNumber[IdentifyLen] = "NON";
    char lastName[lastNameLen] = "";
    Specification spec;
};

struct ListOFpeople{
    Student student;
    Teacher teacher;
    Customer customer;
    bool used = false;
};

ListOFpeople list[MaxAmountOfPeople];
int AmountPerson = 0;


void Interact();

int main()
{
    setlocale(LC_ALL, "rus");
    Interact();
}

void Print(Student person) {
    puts(person.lastName);
    puts(person.examboockNumber);
    cout << person.averageGrade;
    if (person.gender.man) cout << " man";
    else cout << " woman\n";
}

void IdentefyPosition(Position person) {
    if (person.techer)
    {
        cout << "teacher";
    }
    else if (person.headtecher)
        cout << "headTeacher";
    else if (person.professor)
        cout << "professor";
    else cout << "docent";
}
void Print(Teacher person) {
    puts(person.lastName);
    puts(person.identifyNumber);
    IdentefyPosition(person.position)
}
void Print(Customer person) {
    puts(person.lastName);
    puts(person.lastName);
}
void PrintPerson(ListOFpeople person) {
    Print(person.student);
    Print(person.teacher);
    Print(person.customer);
    cout << endl;
}

Student ReadStudent() {
    Student student;
    char gende[10];
    getchar();
    cin.getline(student.examboockNumber, IdentifyLen, ' ');
    cin.getline(student.lastName, lastNameLen, ' ');
    cin.getline(gende, 10, ' ');
    cin >> student.averageGrade;

    Gender gender;
    //puts(gende);
    if (strcmp("man",gende) == 0) student.gender.man = true;
    else student.gender.woman = true;

    return student;
}

Teacher ReadTeacher() {
    Teacher teacher;
    cin.getline(teacher.identifyNumber, IdentifyLen, ' ');
    cin.getline(teacher.lastName, lastNameLen, ' ');

    char position[10];
    cin.getline(position, 10, ' ');

    if (strcmp(position,"t") == 0)
    {
        teacher.position.techer = true;
    }
    else if (strcmp(position, "ht") == 0)
    {
        teacher.position.headtecher = true;
    }
    else if (strcmp(position,"pr")==0)
    {
        teacher.position.professor = true;
    }
    else
    {
        teacher.position.docent = true;
    }
    return teacher;
}

Customer ReadCustomer() {
    Customer customer;
    
    cin.getline(customer.pusportNumber, IdentifyLen, ' ');
    cin.getline(customer.lastName, lastNameLen, ' ');
    
    char spec[15];
    cin.getline(spec, 15);
    if (strcmp(spec,"one") == 0)
    {
        customer.spec.one = true;
    }
    else if (strcmp(spec ,"two")==0)
    {
        customer.spec.two = true;
    }
    else if (strcmp(spec,"three")==0)
    {
        customer.spec.three = true;
    }
    else customer.spec.fore = true;
    return customer;
}

ListOFpeople ReadPerson() {
    cout << "if you whant enter the student's information enter 1, for teacher enter 2, for customer enter 3\n";
    int type;
    cin >> type;
    
    ListOFpeople newPerson;
    newPerson.used = true;
    if (type == 1) {
       //getchar();
        cout << "введите номер_зачетной_книжки фамилию пол средний_балл";
        newPerson.student = ReadStudent();
    }
    else if(type == 2) {
        cout << "введити инд_номер фамилию должность";
        newPerson.teacher = ReadTeacher();
    }
    else if (type == 3) {
        cout << "введите паспортные_данные фамилию спецификацию";
        newPerson.customer = ReadCustomer();
    }
    else cout << "eror";

    return newPerson;
}
void SendExceededSizeError() {
    char mesenge[] = "There are not empty places!";
    puts(mesenge);
}

void AddMember(ListOFpeople* array, ListOFpeople personality) {
    if (AmountPerson == MaxAmountOfPeople) {
        SendExceededSizeError();
        return;
    }

    for (int i = 0; i < MaxAmountOfPeople; i++) {
        auto person = array[i];
        
        if (!person.used) {
            array[i] = personality;
            array[i].used = true;
            AmountPerson++;
            return;
        }
    }
}

///return 0 if first == second
int CompareStudent(Student first, Student second) {
    return strcmp(first.examboockNumber, second.examboockNumber);
}
int CompareTeacher(Teacher first, Teacher second) {
    return strcmp(first.identifyNumber, second.identifyNumber);
}
int CompareCustomer(Customer first, Customer second) {
    return strcmp(first.pusportNumber, second.pusportNumber);
}
int Compare(ListOFpeople first, ListOFpeople second) {
    int ans = CompareStudent(first.student, second.student);
    if (ans != 0) return ans;
    ans = CompareTeacher(first.teacher, second.teacher);
    if (ans != 0) return ans;
    ans = CompareCustomer(first.customer, second.customer);
    return ans;
}

void SendEmptyOrIdentifyEror() {
    char mesenge[] = "There is not this object in this list";
    puts(mesenge);
}

void DeleteMember(ListOFpeople* array, ListOFpeople personality) {


    for (int i = 0; i < MaxAmountOfPeople; i++) {
        auto person = array[i];

        if (Compare(person, personality) == 0) {
            ListOFpeople newPattern;
            array[i] = newPattern;
            array[i].used = false;
            AmountPerson--;
            return;
        }
    }

    SendEmptyOrIdentifyEror();
}

void PrintPersons(ListOFpeople* array) {
    for (int i = 0; i < AmountPerson; i++) {
        ListOFpeople person;
        if (Compare(person, array[i]) == 0) continue;

        PrintPerson(array[i]);
    }
}

void Interact() {
    while (true) {
        cout << "если хотите добавить введите 1, удалить - 2, ввывести - 3";
        int pat;
        cin >> pat;

        if (pat == 1) {
            auto person = ReadPerson();
            AddMember(list, person);
        }
        else if (pat == 2) {
            auto person = ReadPerson();
            DeleteMember(list, person);
        }
        else PrintPersons(list);
    }
}

