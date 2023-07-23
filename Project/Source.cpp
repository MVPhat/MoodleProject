#include "Header.h"

void goTo(SHORT posX, SHORT posY)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

    SetConsoleCursorPosition(hStdout, Position);
}

void DisableCtrButton(bool Close, bool Min, bool Max)
{
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);

    if (Close == 1)
    {
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
    if (Min == 1)
    {
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (Max == 1)
    {
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}

void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void gotoxy(SHORT posX, SHORT posY)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

    SetConsoleCursorPosition(hStdout, Position);
}

bool checkAcc(string filename, account user, int& index)
{
    ifstream file;
    file.open(filename);
    while (!file.eof())
    {
        string name, pass;
        file >> index >> name >> pass;
        if (name.compare(user.name) == 0 && pass.compare(user.password) == 0)
        {
            file.close();
            return true;
        }
    }
    file.close();
    index = 0;
    return false;
}
void clearPass(account& user)
{
    user.name = "";
    user.password = "";
    goTo(72, 18);
    cout << "Your password or account are wrong.";
}
void changePass(string filename, account& user, int index, string newpass)
{
    fstream file;
    file.open(filename);
    while (!file.eof())
    {
        int i;
        string pass;
        file >> i;
        int size = file.tellg();
        if (i != index)
        {
            file >> pass >> pass;
        }
        else
        {
            file.seekp(size);
            file << ' ' << user.name << ' ' << newpass << "                                            ";
            user.password = newpass;
            file.close();
            break;
        }
    }
    file.close();
}

void SetColor(int ForgC) {
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
void ShowCur(bool a) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;

    ConCurInf.dwSize = 20;
    ConCurInf.bVisible = a;
    SetConsoleCursorInfo(handle, &ConCurInf);
}
void setSemesterDefault(SchoolYear* SchoolYearHead, SchoolYear*& defaultyear)
{
    SchoolYear* pCur = SchoolYearHead;
    int i = 0;
    string year, semester;
    while (pCur != nullptr)
    {
        gotoxy(72, 12 + i);
        cout << "YEAR: " << pCur->year << " , SEMESTER: ";
        while (pCur->headSem != nullptr)
            cout << pCur->headSem->semX << ", ";
        i += 2;
    }
    gotoxy(72, 12 + i);
    cout << "PLEASE ENTER THE YEAR AND THE SEMESTER, YOU WANT TO DO: ";
    cin >> year >> semester;
}
void menu(int& ctrl1) {
    goTo(68, 18);
    system("color F0");
    SetColor(0);
    string* a = new string[3];
    a[0] = "ACADEMIC STAFF MEMBER";
    a[1] = "STUDENT";
    a[2] = "EXIT";
    cout << "WHO ARE YOU?????";
    SetColor(3);
    goTo(70, 20);
    cout << a[0];
    SetColor(0);
    goTo(70, 22);
    cout << a[1];
    goTo(70, 24);
    cout << a[2];
    int ctrl;
    //int x, y, i = 0;
    ctrl1 = 0;
  /*  x = 72;
    y = 12;*/
    ShowCur(0);
    while (1) {
        ctrl = _getch();
        if (ctrl == 72 || ctrl == 87 || ctrl == 119) {
            ctrl1--;
            ctrl1 = (ctrl1 + 3) % 3;
            goTo(70, 20);
            cout << a[0];
            goTo(70, 22);
            cout << a[1];
            goTo(70, 24);
            cout << a[2];
            SetColor(3);
            goTo(70, 18 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 80 || ctrl == 83 || ctrl == 115) {
            ctrl1++;
            ctrl1 = (ctrl1 + 3) % 3;
            goTo(70, 20);
            cout << a[0];
            goTo(70, 22);
            cout << a[1];
            goTo(70, 24);
            cout << a[2];
            SetColor(3);
            goTo(70, 20 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 13) {
            system("CLS");
            return;
        }
    }

    delete[]a;
}
void menuTeacher(int& ctrl1)
{
    system("CLS");
    system("color F0");
    SetColor(0);
    string* a = new string[7];
    a[0] = "SCHOOLYEAR";
    a[1] = "SEMESTER";
    a[2] = "POINT";
    a[3] = "CLASS";
    a[4] = "COURSE";
    a[5] = "SET DEFAULT";
    a[6] = "BACK";
    SetColor(3);
    goTo(72, 12);
    cout << a[0];
    SetColor(0);
    goTo(72, 14);
    cout << a[1];
    goTo(72, 16);
    cout << a[2];
    goTo(72, 18);
    cout << a[3];
    goTo(72, 20);
    cout << a[4];
    goTo(72, 22);
    cout << a[5];
    goTo(72, 24);
    cout << a[6];
    int ctrl;
    ctrl1 = 0;
    ShowCur(0);
    while (1) {
        ctrl = _getch();
        if (ctrl == 72) {
            ctrl1--;
            ctrl1 = (ctrl1 + 7) % 7;
            goTo(72, 12);
            cout << a[0];
            goTo(72, 14);
            cout << a[1];
            goTo(72, 16);
            cout << a[2];
            goTo(72, 18);
            cout << a[3];
            goTo(72, 20);
            cout << a[4];
            goTo(72, 22);
            cout << a[5];
            goTo(72, 24);
            cout << a[6];
            SetColor(3);
            goTo(72, 12 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 80) {
            ctrl1++;
            ctrl1 = (ctrl1 + 7) % 7;
            goTo(72, 12);
            cout << a[0];
            goTo(72, 14);
            cout << a[1];
            goTo(72, 16);
            cout << a[2];
            goTo(72, 18);
            cout << a[3];
            goTo(72, 20);
            cout << a[4];
            goTo(72, 22);
            cout << a[5];
            goTo(72, 24);
            cout << a[6];
            SetColor(3);
            goTo(72, 12 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 13) {
            system("CLS");
            return;
        }
    }
    delete[]a;
}
void setDefault(SchoolYear*choose, semester*chooseSem)
{
    ofstream file;
    file.open("default.txt");
    file << choose->year << " " << chooseSem->semX;
    file.close();
    gotoxy(72, 24);
    cout << "Succesfully. Press any key to continue.";
    _getch();
}
void menuStudent(int& ctrl1)
{
    system("CLS");
    system("color F0");
    SetColor(0);
    string* a = new string[7];
    a[0] = "ENROLL COURSE";
    a[1] = "YOUR COURSES";
    a[2] = "REMOVE COURSE";
    a[3] = "VIEW POINT";
    a[4] = "CHANGE PASSWORD";
    a[5] = "VIEW PROFILE";
    a[6] = "BACK";
    SetColor(3);
    goTo(72, 12);
    cout << a[0];
    SetColor(0);
    goTo(72, 14);
    cout << a[1];
    goTo(72, 16);
    cout << a[2];
    goTo(72, 18);
    cout << a[3];
    goTo(72, 20);
    cout << a[4];
    goTo(72, 22);
    cout << a[5];
    goTo(72, 24);
    cout << a[6];
    int ctrl;
    ctrl1 = 0;
    ShowCur(0);
    while (1) {
        ctrl = _getch();
        if (ctrl == 72) {
            ctrl1--;
            ctrl1 = (ctrl1 + 7) % 7;
            goTo(72, 12);
            cout << a[0];
            goTo(72, 14);
            cout << a[1];
            goTo(72, 16);
            cout << a[2];
            goTo(72, 18);
            cout << a[3];
            goTo(72, 20);
            cout << a[4];
            goTo(72, 22);
            cout << a[5];
            goTo(72, 24);
            cout << a[6];
            SetColor(3);
            goTo(72, 12 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 80) {
            ctrl1++;
            ctrl1 = (ctrl1 + 7) % 7;
            goTo(72, 12);
            cout << a[0];
            goTo(72, 14);
            cout << a[1];
            goTo(72, 16);
            cout << a[2];
            goTo(72, 18);
            cout << a[3];
            goTo(72, 20);
            cout << a[4];
            goTo(72, 22);
            cout << a[5];
            goTo(72, 24);
            cout << a[6];
            SetColor(3);
            goTo(72, 12 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 13) {
            system("CLS");
            return;
        }
    }
    delete[]a;
}
void menuSchoolyear(int& ctrl1)
{
    system("CLS");
    goTo(70, 10);
    system("color F0");
    SetColor(0);
    string* a = new string[3];
    cout << "SCHOOLYEAR";
    a[0] = "CREATE";
    a[1] = "VIEW";
    a[2] = "BACK";
    SetColor(3);
    goTo(72, 12);
    cout << a[0];
    SetColor(0);
    goTo(72, 14);
    cout << a[1];
    goTo(72, 16);
    cout << a[2];
    ctrl1 = 0;
    int ctrl;
    ShowCur(0);
    while (1) {
        ctrl = _getch();
        if (ctrl == 72) {
            ctrl1--;
            ctrl1 = (ctrl1 + 3) % 3;
            goTo(72, 12);
            cout << a[0];
            goTo(72, 14);
            cout << a[1];
            goTo(72, 16);
            cout << a[2];
            SetColor(3);
            goTo(72, 12 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 80) {
            ctrl1++;
            ctrl1 = (ctrl1 + 3) % 3;
            goTo(72, 12);
            cout << a[0];
            goTo(72, 14);
            cout << a[1];
            goTo(72, 16);
            cout << a[2];
            SetColor(3);
            goTo(72, 12 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 13) {
            system("CLS");
            return;
        }
    }
    delete[]a;
}
void menuSemester(int& ctrl1)
{
    system("CLS");
    goTo(70, 10);
    system("color F0");
    SetColor(0);
    string* a = new string[3];
    cout << "SEMESTER";
    a[0] = "CREATE";
    a[2] = "BACK";
    SetColor(3);
    goTo(72, 12);
    cout << a[0];
    SetColor(0);
    goTo(72, 14);
    cout << a[1];
    ctrl1 = 0;
    int ctrl;
    ShowCur(0);
    while (1) {
        ctrl = _getch();
        if (ctrl == 72) {
            ctrl1--;
            ctrl1 = (ctrl1 + 2) % 2;
            goTo(72, 12);
            cout << a[0];
            goTo(72, 14);
            cout << a[1];
            SetColor(3);
            goTo(72, 12 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 80) {
            ctrl1++;
            ctrl1 = (ctrl1 + 2) % 2;
            goTo(72, 12);
            cout << a[0];
            goTo(72, 14);
            cout << a[1];
            SetColor(3);
            goTo(72, 12 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 13) {
            system("CLS");
            return;
        }
    }
    delete[]a;
}
void menuCourse(int& ctrl1)
{
    system("CLS");
    goTo(70, 10);
    system("color F0");
    SetColor(0);
    string* a = new string[5];
    cout << "COURSE";
    a[0] = "ADD";
    a[1] = "VIEW";
    a[2] = "PUBLISHED POINT";
    a[3] = "UPDATE";
    a[4] = "BACK";
    SetColor(3);
    goTo(72, 12);
    cout << a[0];
    SetColor(0);
    goTo(72, 14);
    cout << a[1];
    goTo(72, 16);
    cout << a[2];
    goTo(72, 18);
    cout << a[3];
    goTo(72, 20);
    cout << a[4];
    ctrl1 = 0;
    int ctrl;
    ShowCur(0);
    while (1) {
        ctrl = _getch();
        if (ctrl == 72) {
            ctrl1--;
            ctrl1 = (ctrl1 + 5) % 5;
            goTo(72, 12);
            cout << a[0];
            goTo(72, 14);
            cout << a[1];
            goTo(72, 16);
            cout << a[2];
            goTo(72, 18);
            cout << a[3];
            goTo(72, 20);
            cout << a[4];
            SetColor(3);
            goTo(72, 12 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 80) {
            ctrl1++;
            ctrl1 = (ctrl1 + 5) % 5;
            goTo(72, 12);
            cout << a[0];
            goTo(72, 14);
            cout << a[1];
            goTo(72, 16);
            cout << a[2];
            goTo(72, 18);
            cout << a[3];
            goTo(72, 20);
            cout << a[4];
            SetColor(3);
            goTo(72, 12 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 13) {
            system("CLS");
            return;
        }
    }
    delete[]a;
}

void menuClass(int& ctrl1)
{
    system("CLS");
    goTo(70, 10);
    system("color F0");
    SetColor(0);
    string* a = new string[3];
    cout << "CLASS";
    a[0] = "CREATE FROM CSV FILE";
    a[1] = "VIEW";
    a[2] = "BACK";
    SetColor(3);
    goTo(72, 12);
    cout << a[0];
    SetColor(0);
    goTo(72, 14);
    cout << a[1];
    goTo(72, 16);
    cout << a[2];
    ctrl1 = 0;
    int ctrl;
    ShowCur(0);
    while (1) {
        ctrl = _getch();
        if (ctrl == 72) {
            ctrl1--;
            ctrl1 = (ctrl1 + 3) % 3;
            goTo(72, 12);
            cout << a[0];
            goTo(72, 14);
            cout << a[1];
            goTo(72, 16);
            cout << a[2];
            SetColor(3);
            goTo(72, 12 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 80) {
            ctrl1++;
            ctrl1 = (ctrl1 + 3) % 3;
            goTo(72, 12);
            cout << a[0];
            goTo(72, 14);
            cout << a[1];
            goTo(72, 16);
            cout << a[2];
            SetColor(3);
            goTo(72, 12 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 13) {
            system("CLS");
            return;
        }
    }
    delete[]a;
}
void studentLogin(string& name, string& pass) {
    ShowCur(1);
    int num = 0;
    string a;
    goTo(72, 14);
    cout << "USERNAME:";
    goTo(72, 16);
    cout << "PASSWORD:";
    char ctrl;
    goTo(81, 14);
    while (1) {
        ctrl = _getch();
        if (ctrl == 8) {
            if (name.size() != 0) {
                name.pop_back();
                goTo(81 + name.size(), 14);
                cout << " ";
                goTo(81 + name.size(), 14);
            }
        }
        else if (ctrl != 13) {
            name = name + ctrl;
            cout << ctrl;
        }
        else break;
    }
    goTo(81, 16);
    while (1) {
        ctrl = _getch();
        if (ctrl == 8) {
            if (pass.size() != 0) {
                pass.pop_back();
                goTo(81 + pass.size(), 16);
                cout << " ";
                goTo(81 + pass.size(), 16);
            }
        }
        else if (ctrl != 13) {
            pass = pass + ctrl;
            cout << "*";
        }
        else break;
    }
}
void teacherLogin(string& name, string& pass) {
    ShowCur(1);
    int num = 0;
    string a;
    goTo(72, 14);
    cout << "USERNAME:";
    goTo(72, 16);
    cout << "PASSWORD:";
    char ctrl;
    goTo(81, 14);
    while (1) {
        ctrl = _getch();
        if (ctrl == 8) {
            if (name.size() != 0) {
                name.pop_back();
                goTo(81 + name.size(), 14);
                cout << " ";
                goTo(81 + name.size(), 14);
            }
        }
        else if (ctrl != 13) {
            name = name + ctrl;
            cout << ctrl;
        }
        else break;
    }
    goTo(81, 16);
    while (1) {
        ctrl = _getch();
        if (ctrl == 8) {
            if (pass.size() != 0) {
                pass.pop_back();
                goTo(81 + pass.size(), 16);
                cout << " ";
                goTo(81 + pass.size(), 16);
            }
        }
        else if (ctrl != 13) {
            pass = pass + ctrl;
            cout << "*";
        }
        else break;
    }
}
void clearLogin()
{
    goTo(81, 14);
    cout << "                                              ";
    goTo(81, 16);
    cout << "                                              ";
}
// input output delete student CSV 
void inputStudent(ifstream& f, classR*& classNameHead, string className) {
    classR* cur = classNameHead;
    int i = 0;
    while (cur != nullptr && cur->className != className) cur = cur->next;
    if (cur == nullptr) return;
    ofstream file;
    file.open("AccStd.txt", ios::app);
    int index = createAccStu() + 1;
    char n;
    f >> i;
    student* temp = cur->stu;
    student1* temp1 = cur->stu1;
    while (i--) {
        if (cur->stu == nullptr) {
            cur->stu = new student;
            temp = cur->stu;
        }
        else {
            temp->nextStu = new student;
            temp = temp->nextStu;
        }
        if (cur->stu1 == nullptr) {
            cur->stu1 = new student1;
            temp1 = cur->stu1;
        }
        else {
            temp1->nextStu = new student1;
            temp1 = temp1->nextStu;
        }
        f >> temp->no;
        f >> n;
        f >> temp->stuId;
        f >> n;

        getline(f, temp->firstName, ',');
        getline(f, temp->lastName, ',');
        getline(f, temp->gender, ',');
        getline(f, temp->date, ',');
        f >> temp->socId;
        temp1->no = temp->no;
        temp1->stuId = temp->stuId;
        temp1->firstName = temp->firstName;
        temp1->lastName = temp->lastName;
        temp1->gender = temp->gender;
        temp1->date = temp->date;
        temp1->socId = temp->socId;
        temp1->courseHead = nullptr;
        file << index << " " << temp->stuId << " " << 12345 << endl;
        temp1->nextStu = nullptr;
        temp->nextStu = nullptr;
        index++;
    }
}

void outputStudentFromClass(classR* classHead, string className) {

    while (classHead) {
        if (classHead->className == className) {
            cout << "Class: " << className << endl;
            student* cur = classHead->stu;
            if (cur == nullptr) cout << "Class has no Student !" << endl;
            while (cur) {
                cout << "Student no: " << cur->no << endl;
                cout << "Student ID: " << cur->stuId << endl;
                cout << "First name: " << cur->firstName << endl;
                cout << "Last name: " << cur->lastName << endl;
                cout << "Gender: " << cur->gender << endl;
                cout << "Date: " << cur->date << endl;
                cout << "Social id: " << cur->socId << endl;
                cout << "\n----------------------------------------" << endl;
                cur = cur->nextStu;
            }

            return;
        }
        classHead = classHead->next;
    }
    cout << "We don't have class name: " << className << "\n Please create the new class !" << endl;
}
void viewListOfStudentInACourse(Course* courseHead, int courseID) {
    while (courseHead) {
        if (courseHead->id == courseID) {
            cout << "Course: " << courseHead->courseName << endl;
            student* cur = courseHead->stuHead;
            if (cur == nullptr) cout << "Course has no Student !" << endl;
            while (cur) {
                cout << "Student no: " << cur->no << endl;
                cout << "Student ID: " << cur->stuId << endl;
                cout << "first name: " << cur->firstName << endl;
                cout << "last name: " << cur->lastName << endl;
                cout << "gender: " << cur->gender << endl;
                cout << "date: " << cur->date << endl;
                cout << "social id: " << cur->socId << endl;
                cout << "----------------------------------------" << endl;
                cur = cur->nextStu;
            }
            return;
        }
        courseHead = courseHead->next;
    }
    cout << "We have no Course iD: " << courseID << "\n Please create new Course !" << endl;
}
void viewAllClasss(classR* classHead) {
    classR* cur = classHead;
    while (cur) {
        cout << "Class: " << cur->className << endl;
        cur = cur->next;
    }
}

void deleteClassR(classR*& classHead) {
    classR* cur = classHead;
    while (classHead) {
        cur = cur->next;
        student* temp = classHead->stu;
        while (classHead->stu) {
            temp = temp->nextStu;
            delete classHead->stu;
            classHead->stu = temp;
        }
        student1* temp1 = classHead->stu1;
        while (classHead->stu1) {
            temp1 = temp1->nextStu;
            Course* courseTemp = classHead->stu1->courseHead;
            while (classHead->stu1->courseHead) {
                courseTemp = courseTemp->next;
                delete classHead->stu1->courseHead;
                classHead->stu1->courseHead = courseTemp;
            }
            delete classHead->stu1;
            classHead->stu1 = temp1;
        }
        delete classHead;
        // classHead = cur;
    }
}

void createClass(classR*& classHead, string className) {
    if (classHead == nullptr) {
        classHead = new classR;
        classHead->className = className;
        classHead->next = nullptr;
        return;
    }
    classR* cur = classHead;
    while (cur->next) cur = cur->next;
    cur->next = new classR;
    cur = cur->next;
    cur->className = className;
    cur->next = nullptr;
}

void writingCSV(string fileName, int n) {
    ofstream f;
    f.open(fileName, ios_base::out);
    if (f.fail() == true) {
        cout << "Can't open file " << endl;
        return;
    }

    string t;
    cout << "Please input student data: No,SID,FirstName,LastName,Gender,DateofBirth,SocialID : " << endl;

    for (int i = 0; i < n; i++) {
        cout << "student " << i + 1 << ": ";
        if (i == 0)cin.ignore(1);
        getline(cin, t);
        if (i == n - 1) { f << t; }
        else f << t << endl;
    }
    f.close();
}

void readingAllCSVStudentFile(string fileName, classR*& classHead, string className, bool& check) {
    ifstream file;
    file.open(fileName, ios_base::in);
    if (file.fail() == true) {
        cout << "Can't open file";
        check = false;
        return;
    }
    createClass(classHead, className);
    inputStudent(file, classHead, className);

}

void readingCSV(string fileName, classR*& classHead, string className) {
    ifstream file;
    file.open(fileName, ios_base::in);
    if (file.fail() == true) {
        cout << "Can't open file";
        return;
    }
    createClass(classHead, className);
    inputStudent(file, classHead, className);
    file.close();
}

// Create Course
void createCourse(Course*& courseHead) {
    if (courseHead == nullptr) {
        courseHead = new Course;
        courseHead->next = nullptr;
        return;
    }
    Course* cur = courseHead;
    cur->next = new Course;
    cur = cur->next;
    cur->next = nullptr;
}

void inputCourse(ifstream& f, Course*& courseHead) {
    Course* cur = courseHead;
    if (cur == nullptr) return;
    while (cur->next != nullptr) cur = cur->next;

    char n;
    sessionPerform* temp = cur->headDay;
    int i = 1;
    while (f.good()) {
        if (i != 1) {
            cur->next = new Course;
            cur = cur->next;
            cur->next = nullptr;
        }
        if (cur->headDay == nullptr) {
            cur->headDay = new sessionPerform;
            temp = cur->headDay;
        }
        else {
            temp->next = new sessionPerform;
            temp = temp->next;
        }

        f >> cur->id;
        f >> n;
        getline(f, cur->courseName, ',');
        getline(f, cur->teacherName, ',');
        f >> cur->creditNum;
        f >> n;
        f >> cur->maxStuNum;
        f >> n;
        f >> cur->dayTotal;
        f >> n;
        getline(f, temp->sesDay, ',');
        getline(f, temp->sestime, ',');

        temp->next = new sessionPerform;
        temp = temp->next;

        getline(f, temp->sesDay, ',');
        getline(f, temp->sestime, '\n');

        temp->next = nullptr;
        i++;
    }

}

void outputCourse(Course* courseHead) {
    Course* cur = courseHead;
    if (cur == nullptr) {
        cout << "There is no course now - Please input !" << endl;
        return;
    }
    gotoxy(5, 3);
    cout << "Course ID      Course Name              Teacher Name            Credits      Max students      Total days      Day session";
    int i = 5;
    while (cur != nullptr) {
        gotoxy(5, i);
        cout << cur->id;
        gotoxy(20, i);
        cout << cur->courseName;
        gotoxy(45, i);
        cout << cur->teacherName;
        gotoxy(69, i);
        cout << cur->creditNum;
        gotoxy(82, i);
        cout << cur->maxStuNum;
        gotoxy(100, i);
        cout << cur->dayTotal;
        gotoxy(116, i);
        int e = 1;
        while (cur->headDay != nullptr)
        {
            cout << cur->headDay->sesDay << "-" << cur->headDay->sestime << "  ";
            cur->headDay = cur->headDay->next;
        }
        i += 2;
        cur = cur->next;
    }
    gotoxy(72, i);
    cout << "press any key to exit";
    _getch();
}

void updateCourse(string courseName, string fileName, Course*& courseHead) {

    Course* cur = courseHead;
    while (cur != nullptr && cur->courseName != courseName) cur = cur->next;
    if (cur == nullptr) return;
    cout << "Enter Course information again to update: ";
    writingCSVCourseFile(fileName);

    ifstream f; char n; sessionPerform* temp = cur->headDay;
    f.open(fileName, ios_base::out);
    f >> cur->id;
    f >> n;
    getline(f, cur->courseName, ',');
    getline(f, cur->teacherName, ',');
    f >> cur->creditNum;
    f >> n;
    f >> cur->maxStuNum;
    f >> n;
    f >> cur->dayTotal;
    f >> n;
    getline(f, temp->sesDay, ',');
    getline(f, temp->sestime, ',');

    temp = temp->next;

    getline(f, temp->sesDay, ',');
    getline(f, temp->sestime, ',');
    f.close();
}
void teacherUpdateCourse(string courseName, Course*& courseHead, classR*& classHead) {
    Course* cur = courseHead;
    while (cur != nullptr && cur->courseName != courseName) cur = cur->next;
    if (cur == nullptr) {
        cout << "There Has No Course Name : " << courseName << endl;
        cout << "\n Please Create New Course !" << endl;
        return;
    }
    int oldCourseID = cur->id;
    sessionPerform* temp = cur->headDay;
    cout << "Enter Course information again to update: " << endl;
    cout << "Old ID = " << cur->id << "--> New Course ID: ";
    cin >> cur->id;
    cout << "Old Name : " << cur->courseName << "--> New Course Name: ";
    cin >> cur->courseName;
    cout << "Old Teacher Name : " << cur->teacherName << "--> New Teacher Name: ";
    cin >> cur->teacherName;
    cout << "Old Credit = " << cur->creditNum << "--> New Course Credit Number =  ";
    cin >> cur->creditNum;
    cout << "Old Max Student Num = " << cur->maxStuNum << "--> New Max Student Num = ";
    cin >> cur->maxStuNum;
    cout << "Old Total Day = " << cur->dayTotal << "--> New Total Day: ";
    cin >> cur->dayTotal;
    cout << "Old Session Day 1 = " << temp->sesDay << "--> New Session Day 1: ";
    cin >> temp->sesDay;
    string day1 = temp->sesDay;
    cout << "Old Session Time 1 = " << temp->sesDay << "--> New Session Time 1: ";
    cin >> temp->sestime;
    string time1 = temp->sestime;
    temp = temp->next;
    cout << "Old Session Day 2 = " << temp->sesDay << "--> New Session Day 2: ";
    cin >> temp->sesDay;
    cout << "Old Session Time 2 = " << temp->sesDay << "--> New Session Time 2: ";
    cin >> temp->sestime;
    classR* classCur = classHead;
    while (classCur) {
        student1* stu1 = classCur->stu1;
        student1* stu1Cur = stu1;
        while (stu1Cur) {
            Course* course = stu1Cur->courseHead;
            Course* courseCur = course;
            while (courseCur) {
                if (courseCur->id == oldCourseID) {
                    courseCur->id = cur->id;
                    courseCur->courseName = cur->courseName;
                    courseCur->teacherName = cur->teacherName;
                    courseCur->creditNum = cur->creditNum;
                    courseCur->maxStuNum = cur->maxStuNum;  
                    courseCur->dayTotal = cur->dayTotal;
                    courseCur->headDay->sesDay = day1;
                    courseCur->headDay->sestime = time1;
                    courseCur->headDay->next->sesDay = temp->sesDay;
                    courseCur->headDay->next->sestime = temp->sestime;
                    break;
                }
                courseCur = courseCur->next;
            }
            stu1Cur = stu1Cur->nextStu;
        }
        classCur = classCur->next;
    }
}
void readingCSVCourseFile(Course*& courseHead) {
    ifstream file;
    string fileName;
    gotoxy(40, 10);
    cout << "Please enter the name of file course to add course: ";
    cin >> fileName;
    file.open(fileName, ios_base::in);
    if (file.fail() == true) {
        cout << "Can't open file";
        return;
    }
    Course* cur = courseHead;
    if (cur == nullptr) {
        createCourse(courseHead);
        inputCourse(file, courseHead);
    }
    else {
        while (cur->next) cur = cur->next;
        createCourse(cur);
    }
    inputCourse(file, cur);
    file.close();
}

void deleteCourse(Course*& courseHead) {
    Course* cur = courseHead;
    while (courseHead) {
        sessionPerform* temp = cur->headDay;
        cur = cur->next;
        while (cur->headDay) {
            temp = temp->next;
            delete cur->headDay;
            cur->headDay = temp;
        }
        delete courseHead;
        courseHead = cur;
    }
}

void writingCSVCourseFile(string fileName) {
    ofstream f;
    f.open(fileName, ios_base::out);
    if (f.fail() == true) {
        cout << "Can't open file " << endl;
        return;
    }
    string t;
    cout << " \n Course Information : ID,CourseName,TeacherName,CreditNum,maxStudentNum,dayTotal,Session Day1,TimeOfDay1,SessionDay2,TimeOfDay2: " << endl;
    getline(cin, t);
    f << t << endl;
    f.close();
}

bool checkIsYear(SchoolYear* head, string newyear) {
    while (head != nullptr) {
        if (head->year == newyear)
            return false;
        head = head->SYnext;
    }
    return true;
}

void InSchoolYeartxt(SchoolYear*& head) {
    ifstream fin;
    string inyear;
    SchoolYear* cur = new SchoolYear;
    fin.open("SchoolYear.txt");
    if (fin.is_open()) {
        while (!fin.eof()) {
            getline(fin, inyear, ' ');
            if (head == nullptr) {
                head = new SchoolYear;
                head->year = inyear;
                head->SYnext = nullptr;
                cur = head;
            }
            else {
                cur->SYnext = new SchoolYear;
                cur = cur->SYnext;
                cur->year = inyear;
                cur->SYnext = nullptr;
            }

        }
    }
    fin.close();
}

void CreateSchoolYear(SchoolYear*& SchoolYearHead) {
    // SetColor(0);
    ShowCur(1);
    string newyear, begin, end;
    char stop = 'Y'; //check to stop while
    SchoolYear* Year = SchoolYearHead;
    while (stop != 'N' && stop != 'n') {
        goTo(51, 8);
        cout << "Input School Year wants to create: ";
        cin >> newyear;
        if (checkIsYear(SchoolYearHead, newyear)) {
            while (Year->SYnext != nullptr)
                Year = Year->SYnext;
            Year->SYnext = new SchoolYear;
            Year = Year->SYnext;
            Year->year = newyear;
            Year->SYnext = nullptr;
            _mkdir((("Sources/") + (Year->year)).c_str());
            Year->headSem = new semester;
            _mkdir((("Sources/") + (Year->year) + ("/Semester1")).c_str());
            gotoxy(51, 10); cout << "Input day start of Semester1: ";
            cin >> begin;
            Year->headSem->start = begin;
            Year->headSem->semX = 1;
            gotoxy(51, 11); cout << "Input day end of Semester1: ";
            cin >> end;
            Year->headSem->end = end;
            Year->headSem->nextSem = nullptr;
            
           
            goTo(51, 13); cout << "Do you want to continue (Y/N): ";
            cin >> stop;
            system("cls");
        }
        else {
            system("cls");
            gotoxy(56, 12); cout << "This school year has exist!\n";
            gotoxy(56, 14); cout << "Press any key to continue.";
            _getch();
            break;
        }
    }
}

void updateSY(SchoolYear*& head) {
    ofstream fout;
    fout.open("SchoolYear.txt");
    if (fout.is_open()) {
        SchoolYear* cur = head;
        while (cur->SYnext != nullptr) {
            fout << cur->year << " ";
            cur = cur->SYnext;
        }
        fout << cur->year;
        fout.close();

    }
}

void ViewSchoolYear(SchoolYear* headyear) {
    if (headyear == nullptr) {
        gotoxy(53, 10); cout << "School Year is empty!\n";
        gotoxy(53, 12); cout << "You must create School Year";
        gotoxy(53, 14); cout << "Press any key to continue.\n";
        _getch();
        return;
    }

    int i = 12;
    gotoxy(73, 10); cout << "List of School Year: \n";
    while (headyear != nullptr) {
        gotoxy(78, i);
        cout << headyear->year << endl;
        headyear = headyear->SYnext;
        i += 2;
    }
    gotoxy(70, i); cout << "Press any key to back.\n";
    _getch();
}

void deleteSchoolYear(SchoolYear*& headyear) {
    SchoolYear* Dele, * pCur = headyear;
    string deleteyear;
    cout << "Input School Year want to delete: ";
    cin >> deleteyear;
    while (pCur->SYnext != nullptr) {
        if (deleteyear.compare(headyear->SYnext->year) == 0) {
            Dele = pCur->SYnext;
            pCur->SYnext = Dele->SYnext;
            delete Dele;
        }
        pCur = pCur->SYnext;
    }
}

void CreateSem(SchoolYear*& headyear) {
    system("cls");
    gotoxy(63, 5); cout << "Press any key to create Semesters for each year!\n";
    _getch();
    system("cls");
    string sy;
    SchoolYear* pCur = headyear;
    semester* pTemp = pCur->headSem;
    cin.get();
    gotoxy(60, 5); cout << "Input School Year to create semester: ";
    cin >> sy;
    while (pCur != nullptr) {
        if (pCur->year == sy && !pCur->headSem->check) {
            int i = 0;
            while (i != 2) {
                string path = pCur->year, starts, ends;
                string FolderSem = "Semester2";
                _mkdir(("Sources/" + path + "/" + FolderSem).c_str());
                FolderSem = "Semester3";
                _mkdir(("Sources/" + path + "/" + FolderSem).c_str());
                system("cls");
                ShowCur(1);
                gotoxy(65, 7); cout << "Input date start and end of semester " << i + 2 << " of " << path << ":\n";
                gotoxy(65, 8); cout << "Date start :"; cin >> starts;
                gotoxy(65, 9); cout << "Date end :"; cin >> ends;
                pCur->headSem->check = true;
                pTemp->nextSem = new semester;
                pTemp = pTemp->nextSem;
                pTemp->start = starts;
                pTemp->end = ends;
                fstream f;
               
                pTemp->semX = i + 1;
                pTemp->nextSem = nullptr;
                ++i;
            }
            system("cls");
            gotoxy(55, 10); cout << "Create Semesters of " << sy << " successfully!";
            gotoxy(57, 12); cout << "Press any key to continue!";
            _getch();
            system("cls");
            return;
        }
        else if (pCur->year == sy && pCur->headSem->check) {
            gotoxy(55, 10); cout << pCur->year << " had created semesters.";
            gotoxy(57, 12); cout << "Press any key to continue!";
            _getch();
            system("cls");
            return;
        }
        pCur = pCur->SYnext;
        if (pCur != nullptr)
            pTemp = pCur->headSem;
    }

    gotoxy(60, 7); cout << "School Year " << sy << " does not exist!";
    gotoxy(60, 9); cout << "Press any key to continue!";
    _getch();
    system("cls");
}


void InDaySem(SchoolYear*& head) {
    ifstream f;
    string s, e;
    SchoolYear* temp = head;
    semester* cur = new semester;
    while (temp != nullptr) {
        f.open("Sources/" + temp->year + "/day.txt");
        int i = 1;
        while (!f.eof()) {
            f >> s;
            f >> e;
            if (temp->headSem == nullptr) {
                temp->headSem = new semester;
                cur = temp->headSem;
                cur->start = s;
                cur->end = e;
                cur->check = true;
                cur->semX = i;
                cur->nextSem = nullptr;
            }
            else {
                cur->nextSem = new semester;
                cur = cur->nextSem;
                cur->start = s;
                cur->end = e;
                cur->check = true;
                cur->semX = i;
                cur->nextSem = nullptr;
            }
            ++i;
        }
        temp = temp->SYnext;
        f.close();
    }
}

void updatedaySem(SchoolYear*& head) {
    SchoolYear* temp = head;
    semester* cur;
    ofstream fout;
    while (temp != nullptr) {
        cur = temp->headSem;
        fout.open("Sources/" + temp->year + "/day.txt");
        while (cur->nextSem != nullptr) {
            fout << cur->start << " ";
            fout << cur->end << endl;
            cur = cur->nextSem;
        }
        fout << cur->start << " ";
        fout << cur->end;
        fout.close();
        temp = temp->SYnext;
    }
}


void saveStudent1ToClassR(classR*& classHead) {
    classR* cur = classHead;
    while (cur) {
        coppyStudent(cur->stu1, cur->stu);
        cur = cur->next;
    }
}
void coppyStudent(student1*& stu1Head, student* stuHead) {
    student* cur = stuHead;
    student1* cur1 = stu1Head;
    if (stu1Head == nullptr && cur != nullptr) {
        stu1Head = new student1;
        cur1 = stu1Head;
    }
    while (cur->nextStu != nullptr) {
        cur1->nextStu = new student1;
        cur1 = cur1->nextStu;
        cur1->nextStu = nullptr;
        cur = cur->nextStu;
    }
    cur = stuHead;
    cur1 = stu1Head;
    while (cur) {
        cur1->date = cur->date;
        cur1->firstName = cur->firstName;
        cur1->gender = cur->gender;
        cur1->lastName = cur->lastName;
        cur1->no = cur->no;
        cur1->socId = cur->socId;
        cur1->stuId = cur->stuId;
        cur = cur->nextStu;
        cur1 = cur1->nextStu;
    }
}
student1* findStudentWithSID(classR* classHead, int SID) {
    classR* cur = classHead;
    while (cur) {
        student1* temp = cur->stu1;
        while (temp) {
            if (temp->stuId == SID) return cur->stu1;
            temp = temp->nextStu;
        }
        cur = cur->next;
    }
    return nullptr;
}
int createAccStu()
{
    fstream file;
    int index;
    string user, pass;
    file.open("accStd.txt");
    while (!file.eof())
    {
        file >> index >> user >> pass;
    }
    file.close();
    return index;
}
void enrollOneStudent(int courseID, int SID, student1*& stuHead, Course*& courseHead, bool& check) {
    if (checkTimeEnroll(courseID, SID, stuHead, courseHead) == true) {
        student1* stuCur = stuHead;
        Course* courseCur = courseHead;
        while (stuCur->stuId != SID) stuCur = stuCur->nextStu;
        while (courseCur->id != courseID) courseCur = courseCur->next;
        // insert courseID in student struct of specified class
        Course* studentCourseHead = stuCur->courseHead;
        if (stuCur->courseHead == nullptr) {
            stuCur->courseHead = new Course;
            studentCourseHead = stuCur->courseHead;
        }
        else {
            int n = 1;
            while (studentCourseHead->next) {
                n++;
                studentCourseHead = studentCourseHead->next;
            }
            if (n > 5) return;
            studentCourseHead->next = new Course;
            studentCourseHead = studentCourseHead->next;
        }
        // Coppy course information
        studentCourseHead->id = courseID;
        studentCourseHead->courseName = courseCur->courseName;
        studentCourseHead->creditNum = courseCur->creditNum;
        studentCourseHead->dayTotal = courseCur->dayTotal;
        studentCourseHead->headDay = courseCur->headDay;
        studentCourseHead->maxStuNum = courseCur->maxStuNum;
        studentCourseHead->teacherName = courseCur->teacherName;

        studentCourseHead->next = nullptr;
        // insert studentID in courseStruct of specified course
        student* studentListInCourseStruct = courseCur->stuHead;
        if (courseCur->stuHead == nullptr) {
            courseCur->stuHead = new student;
            studentListInCourseStruct = courseCur->stuHead;
        }
        else {
            while (studentListInCourseStruct->nextStu) studentListInCourseStruct = studentListInCourseStruct->nextStu;
            studentListInCourseStruct->nextStu = new student;
            studentListInCourseStruct = studentListInCourseStruct->nextStu;
        }
        studentListInCourseStruct->stuId = SID;
        studentListInCourseStruct->date = stuCur->date;
        studentListInCourseStruct->firstName = stuCur->firstName;
        studentListInCourseStruct->gender = stuCur->gender;
        studentListInCourseStruct->lastName = stuCur->lastName;
        studentListInCourseStruct->no = stuCur->no;
        studentListInCourseStruct->socId = stuCur->socId;
        studentListInCourseStruct->nextStu = nullptr;
    }
    else check = false;
}

void viewListEnrollOneStudent(int SID, student1* stuHead) {
    student1* stuCur = stuHead;
    while (stuCur != nullptr && stuCur->stuId != SID) {
        stuCur = stuCur->nextStu;
    }
    if (stuCur == nullptr)   return;


    Course* courseCur = stuCur->courseHead;
    while (courseCur != nullptr) {
        cout << "Course Name: " << courseCur->courseName << endl;
        cout << "Credit Num: " << courseCur->creditNum << endl;
        cout << "Day Total: " << courseCur->dayTotal << endl;
        cout << "Course ID: " << courseCur->id << endl;
        cout << "maxStudent: " << courseCur->maxStuNum << endl;
        cout << "Teacher Name: " << courseCur->teacherName << endl;
        cout << "Session Day 1: " << courseCur->headDay->sesDay << endl;
        cout << "Session time 1: " << courseCur->headDay->sestime << endl;
        cout << "Session Day 2: " << courseCur->headDay->next->sesDay << endl;
        cout << "Session time 2: " << courseCur->headDay->next->sestime << endl;
        cout << "---------------------------------------------" << endl;
        courseCur = courseCur->next;
    }
}

bool checkTimeEnroll(int courseID, int SID, student1* stuHead, Course* courseHead) {
    student1* stuCur = stuHead;
    Course* courseCur = courseHead;
    while (stuCur != nullptr && stuCur->stuId != SID) stuCur = stuCur->nextStu;
    if (stuCur == nullptr) return  false;
    student1* stutemp = stuCur;
    Course* courseTemp = stuCur->courseHead;
    while (courseTemp) {
        if (courseTemp->id == courseID) {
            system("cls");
            gotoxy(61,14); cout << "This Session Had Been Enrolled " << endl;
            return false;
        }
        courseTemp = courseTemp->next;
    }
    while (courseCur != nullptr && courseCur->id != courseID) courseCur = courseCur->next;
    if (courseCur == nullptr) return false;

    string day1 = courseCur->headDay->sesDay;
    string day2 = courseCur->headDay->next->sesDay;
    string time1 = courseCur->headDay->sestime;
    string time2 = courseCur->headDay->next->sestime;
    //courseCur = courseHead;
    courseCur = stuCur->courseHead;
    while (courseCur) {
        if (courseCur->id != courseID) {
            string Nday1 = courseCur->headDay->sesDay;
            string Nday2 = courseCur->headDay->next->sesDay;
            string Ntime1 = courseCur->headDay->sestime;
            string Ntime2 = courseCur->headDay->next->sestime;
            if ((Nday1 == day1 && Ntime1 == time1) || (Nday1 == day2 && Ntime1 == time2)) return false;
            if ((Nday2 == day1 && Ntime2 == time1) || (Nday2 == day2 && Ntime2 == time2)) return false;
        }
        courseCur = courseCur->next;
        return true;
    }
    return true;
}

void removeCourseOneStudent(int courseID, int SID, student1*& stuHead, Course*& courseHead) {

}



void saveFile(SchoolYear* yearHead)
{
    ofstream fout, fout2, fout3;
    while (yearHead != nullptr)
    {
        char i = '1';
        while (yearHead->headSem != nullptr)
        {
            fout.open("Sources/" + yearHead->year + "/Semester" + i + "/course.txt");
            fout2.open("Sources/" + yearHead->year + "/Semester" + i + "/student.txt");
            fout3.open("Sources/" + yearHead->year + "/Semester" + i + "/session.txt");
            while (yearHead->headSem->cour != nullptr)
            {
                fout << yearHead->headSem->cour->id << endl;
                fout << yearHead->headSem->cour->courseName << endl;
                fout << yearHead->headSem->cour->teacherName << endl;
                fout << yearHead->headSem->cour->creditNum << endl;
                fout << yearHead->headSem->cour->maxStuNum << endl;
                fout << yearHead->headSem->cour->dayTotal << endl;

                fout << yearHead->headSem->cour->published << endl;


                while (yearHead->headSem->cour->stuHead != nullptr)
                {
                    fout2 << yearHead->headSem->cour->stuHead->no << endl;
                    fout2 << yearHead->headSem->cour->stuHead->stuId << endl;
                    fout2 << yearHead->headSem->cour->stuHead->firstName << endl;
                    fout2 << yearHead->headSem->cour->stuHead->lastName << endl;
                    fout2 << yearHead->headSem->cour->stuHead->gender << endl;
                    fout2 << yearHead->headSem->cour->stuHead->date << endl;
                    fout2 << yearHead->headSem->cour->stuHead->socId << endl;
                    fout2 << yearHead->headSem->cour->stuHead->point.mid << endl;
                    fout2 << yearHead->headSem->cour->stuHead->point.final << endl;
                    fout2 << yearHead->headSem->cour->stuHead->point.total << endl;
                    yearHead->headSem->cour->stuHead = yearHead->headSem->cour->stuHead->nextStu;
                }
                fout2 << 0 << endl;
                while (yearHead->headSem->cour->headDay != nullptr)
                {
                    fout3 << yearHead->headSem->cour->headDay->sesDay << endl;
                    fout3 << yearHead->headSem->cour->headDay->sestime << endl;
                    yearHead->headSem->cour->headDay = yearHead->headSem->cour->headDay->next;
                }
                fout3 << 0 << endl;
                yearHead->headSem->cour = yearHead->headSem->cour->next;
            }
            fout << -1;
            fout.close();
            fout2.close();
            fout3.close();
            yearHead->headSem = yearHead->headSem->nextSem;
            i++;
        }
        yearHead = yearHead->SYnext;
    }
}
void saveClass(classR* classHead)
{
    ofstream fout, fout2, fout3, fout4, fout5;
    fout.open("class.txt");
    fout2.open("stu.txt");
    fout3.open("stu1.txt");
    fout4.open("cour.txt");
    fout5.open("ses.txt");
    while (classHead != nullptr)
    {
        fout << classHead->className << endl;
        while (classHead->stu != nullptr)
        {
            fout2 << classHead->stu->no << endl;
            fout2 << classHead->stu->stuId << endl;
            fout2 << classHead->stu->firstName << endl;
            fout2 << classHead->stu->lastName << endl;
            fout2 << classHead->stu->gender << endl;
            fout2 << classHead->stu->date << endl;
            fout2 << classHead->stu->socId << endl;
            classHead->stu = classHead->stu->nextStu;
        }
        fout2 << 0 << endl;
        while (classHead->stu1 != nullptr)
        {
            fout3 << classHead->stu1->no << endl;
            fout3 << classHead->stu1->stuId << endl;
            fout3 << classHead->stu1->firstName << endl;
            fout3 << classHead->stu1->lastName << endl;
            fout3 << classHead->stu1->gender << endl;
            fout3 << classHead->stu1->date << endl;
            fout3 << classHead->stu1->socId << endl;
            while (classHead->stu1->courseHead != nullptr)
            {
                fout4 << classHead->stu1->courseHead->id << endl;
                fout4 << classHead->stu1->courseHead->courseName << endl;
                fout4 << classHead->stu1->courseHead->teacherName << endl;
                fout4 << classHead->stu1->courseHead->creditNum << endl;
                fout4 << classHead->stu1->courseHead->maxStuNum << endl;
                fout4 << classHead->stu1->courseHead->dayTotal << endl;
                fout4 << classHead->stu1->courseHead->published << endl;
                while (classHead->stu1->courseHead->headDay != nullptr)
                {
                    fout5 << classHead->stu1->courseHead->headDay->sesDay << endl;
                    fout5 << classHead->stu1->courseHead->headDay->sestime << endl;
                    classHead->stu1->courseHead->headDay = classHead->stu1->courseHead->headDay->next;
                }
                fout5 << 0 << endl;
                classHead->stu1->courseHead = classHead->stu1->courseHead->next;
            }
            fout4 << -1 << endl;
            classHead->stu1 = classHead->stu1->nextStu;
        }
        fout3 << 0 << endl;
        classHead = classHead->next;
    }
    fout << -1 << endl;
    fout.close();
    fout2.close();
    fout3.close();
    fout4.close();
    fout5.close();
}
void readClass(classR*& classHead1)
{
    ifstream fout, fout2, fout3, fout4, fout5;
    string s;
    int n, n1, n2;
    classR* classHead = new classR, * tempClass = classHead1;
    classHead1 = classHead;
    fout.open("class.txt");
    fout2.open("stu.txt");
    fout3.open("stu1.txt");
    fout4.open("cour.txt");
    fout5.open("ses.txt");
    while (!fout.eof())
    {
        fout >> s;
        if (s == "-1")
        {
            tempClass->next = nullptr;
            break;
        }
        classHead->className = s;
        tempClass = classHead;
        student* stuHead = new student, * tempStu = stuHead;
        classHead->stu = stuHead;
        while (!fout2.eof())
        {
            fout2 >> n;
            if (n == 0)
            {
                tempStu->nextStu = nullptr;
                break;
            }
            stuHead->no = n;
            fout2 >> stuHead->stuId;
            fout2.ignore();
            getline(fout2, stuHead->firstName, '\n');
            getline(fout2, stuHead->lastName, '\n');
            fout2 >> stuHead->gender;
            fout2 >> stuHead->date;
            fout2 >> stuHead->socId;
            tempStu = stuHead;
            stuHead->nextStu = new student;
            stuHead = stuHead->nextStu;
        }
        student1* stuHead1 = new student1, * tempStu1 = stuHead1;
        classHead->stu1 = stuHead1;
        while (!fout3.eof())
        {
            fout3 >> n1;
            if (n1 == 0)
            {
                tempStu1->nextStu = nullptr;
                break;
            }
            stuHead1->no = n1;
            fout3 >> stuHead1->stuId;
            fout3.ignore();
            getline(fout3, stuHead1->firstName, '\n');
            getline(fout3, stuHead1->lastName, '\n');
            fout3 >> stuHead1->gender;
            fout3 >> stuHead1->date;
            fout3 >> stuHead1->socId;
 
            tempStu1 = stuHead1;
            Course* courseHead = new Course, * tempCourse = courseHead;
            stuHead1->courseHead = courseHead;
            while (!fout4.eof())
            {
                fout4 >> n2;
                if (n2 == -1)
                {
                    if (courseHead == tempCourse)
                    {
                        courseHead = nullptr;
                    }
                    else
                    {
                        tempCourse->next = nullptr;
                    }
                    break;
                }
                courseHead->id = n2;
                fout4.ignore();
                getline(fout4, courseHead->courseName,'\n');
                getline(fout4 ,courseHead->teacherName,'\n');
                fout4 >> courseHead->creditNum;
                fout4 >> courseHead->maxStuNum;
                fout4 >> courseHead->dayTotal;
                fout4 >> courseHead->published;
                tempCourse = courseHead;
                sessionPerform* sesHead = new sessionPerform, * tempSes = sesHead;
                courseHead->headDay = sesHead;
                while (!fout5.eof())
                {
                    fout5 >> s;
                    if (s == "0")
                    {
                        tempSes->next = nullptr;
                        break;
                    }
                    sesHead->sesDay = s;
                    fout5 >> sesHead->sestime;
                    tempSes = sesHead;
                    sesHead->next = new sessionPerform;
                    sesHead = sesHead->next;
                }
                courseHead->next = new Course;
                courseHead = courseHead->next;
            }
            stuHead1->nextStu = new student1;
            stuHead1 = stuHead1->nextStu;
        }
        classHead->next = new classR;
        classHead = classHead->next;
    }
    fout.close();
    fout2.close();
    fout3.close();
    fout4.close();
    fout5.close();
}

void readFile(SchoolYear*& yearHead1)
{
    ifstream fout, fout2, fout3;
    SchoolYear* yearHead = yearHead1;
    while (yearHead != nullptr)
    {
        char i = '1';
        semester* semesterHead = yearHead->headSem;

        while (yearHead->headSem != nullptr)
        {
            fout.open("Sources/" + yearHead->year + "/Semester" + i + "/course.txt");
            fout2.open("Sources/" + yearHead->year + "/Semester" + i + "/student.txt");
            fout3.open("Sources/" + yearHead->year + "/Semester" + i + "/session.txt");
            int n, n1;
            string s;
            Course* courseHead = new Course, * tempCourse = courseHead;
            yearHead->headSem->cour = courseHead;
            while (!fout.eof())
            {

                fout >> n;
                if (n == -1)
                {
                    tempCourse->next = nullptr;
                    break;
                }
                courseHead->id = n;
                fout.ignore();
                getline(fout, courseHead->courseName,'\n');
                getline(fout, courseHead->teacherName,'\n');
                fout >> courseHead->creditNum;
                fout >> courseHead->maxStuNum;
                fout >> courseHead->dayTotal;
                fout >> courseHead->published;
                tempCourse = courseHead;
                student* stuHead = new student, * tempStu = stuHead;
                courseHead->stuHead = stuHead;
                while (!fout2.eof())
                {
                    fout2 >> n1;
                    if (n1 == 0)
                    {
                        tempStu->nextStu = nullptr;
                        break;
                    }
                    stuHead->no = n1;
                    fout2 >> stuHead->stuId;
                    fout2.ignore();
                    getline(fout2, stuHead->firstName, '\n');
                    getline(fout2, stuHead->lastName, '\n');
                    fout2 >> stuHead->gender;
                    fout2 >> stuHead->date;
                    fout2 >> stuHead->socId;
                    fout2 >> stuHead->point.mid;
                    fout2 >> stuHead->point.final;
                    fout2 >> stuHead->point.total;
                    tempStu = stuHead;
                    stuHead->nextStu = new student;
                    stuHead = stuHead->nextStu;
                }
                sessionPerform* sesHead = new sessionPerform, * tempSes = sesHead;
                courseHead->headDay = sesHead;
                while (!fout3.eof())
                {
                    fout3 >> s;
                    if (s == "0")
                    {
                        tempSes->next = nullptr;
                        break;
                    }
                    sesHead->sesDay = s;
                    fout3 >> sesHead->sestime;
                    tempSes = sesHead;
                    sesHead->next = new sessionPerform;
                    sesHead = sesHead->next;
                }

                courseHead->next = new Course;
                courseHead = courseHead->next;

            }

            i++;
            fout.close();
            fout2.close();
            fout3.close();
            yearHead->headSem = yearHead->headSem->nextSem;
        }
        yearHead->headSem = semesterHead;
        yearHead = yearHead->SYnext;
    }
}

Course* loadDefaultCourse(SchoolYear* yearHead)
{
    ifstream file;
    file.open("default.txt");
    string year;
    int sem;
    file >> year;
    file >> sem;
    file.close();
   
    while (yearHead->year != year)
    {
        yearHead = yearHead->SYnext;
    }
    while (yearHead->headSem->semX != sem)
    {
        yearHead->headSem = yearHead->headSem->nextSem;
    }
    return yearHead->headSem->cour;
}
void displayAllCourse(Course* head, int& ctrl1) {
    if (head == nullptr) {
        gotoxy(73, 10); cout << "........... is empty!\n";
        gotoxy(73, 12); cout << "You must ...............";
        gotoxy(70, 15); cout << "Press any key to continue.\n";
        _getch();
        return;
    }
    Course* cur = head;
    int n = 0;
    while (cur != nullptr) {
        n++;
        cur = cur->next;
    }
    cur = head;
    string* a = new string[n];
    for (int i = 0; i < n; i++) {
        a[i] = cur->courseName;
        cur = cur->next;
    }
    cur = head;
    SetColor(0);
    for (int i = 0; i < n; i++) {
        goTo(72, 16 + 2 * i);
        cout << a[i];
    }
    SetColor(3);
    goTo(72, 16);
    cout << a[0] << endl;
    int ctrl;
    ctrl1 = 0;
    while (1) {
        ctrl = _getch();
        if (ctrl == 72) {
            ctrl1--;
            ctrl1 = (ctrl1 + n) % n;
            SetColor(0);
            for (int i = 0; i < n; i++) {
                goTo(72, 16 + 2 * i);
                cout << a[i] << endl;
            }
            SetColor(3);
            goTo(72, 16 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 80) {
            ctrl1++;
            ctrl1 = (ctrl1 + n) % n;
            SetColor(0);
            for (int i = 0; i < n; i++) {
                goTo(72, 16 + 2 * i);
                cout << a[i] << endl;
            }
            SetColor(3);
            goTo(72, 16 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 13) {
            system("CLS");
            return;
        }
    }
}

void displayCourse(int ctrl, Course* head) {
    if (head == nullptr) return;
    for (int i = 0; i < ctrl; i++) {
        head = head->next;
    }
    cout << "ID of course:" << head->id << endl;
    cout << "Name of course:" << head->courseName << endl;
    cout << "Name of teacher:" << head->teacherName << endl;
    cout << "Schedule" << head->headDay->sesDay << " " << head->headDay->sestime << " , " << head->headDay->next->sesDay << " " << head->headDay->next->sestime << endl;
    cout << "Press any key to back";
    _getch();
}

int stringToInt(string a)
{
    stringstream geek;
    geek << a;
    int b;
    geek >> b;
    return b;
}

void chooseCourse(Course* head, Course*& choose) {
    if (head == nullptr) {
        gotoxy(73, 10); cout << "........... is empty!\n";
        gotoxy(73, 12); cout << "You must ...............";
        gotoxy(70, 15); cout << "Press any key to continue.\n";
        _getch();
        return;
    }
    choose = head;
    Course* cur = head;
    int n = 0;
    while (cur != nullptr) {
        n++;
        cur = cur->next;
    }
    cur = head;
    string* a = new string[n];
    for (int i = 0; i < n; i++) {
        a[i] = cur->courseName;
        cur = cur->next;
    }
    cur = head;
    SetColor(0);
    for (int i = 0; i < n; i++) {
        goTo(72, 16 + 2 * i);
        cout << a[i] << endl;
    }
    SetColor(3);
    goTo(72, 16);
    cout << a[0] << endl;
    int ctrl;
    int ctrl1 = 0;
    while (1) {
        ctrl = _getch();
        if (ctrl == 72) {
            ctrl1--;
            ctrl1 = (ctrl1 + n) % n;
            SetColor(0);
            for (int i = 0; i < n; i++) {
                goTo(72, 16 + 2 * i);
                cout << a[i] << endl;
            }
            SetColor(3);
            goTo(72, 16 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 80) {
            ctrl1++;
            ctrl1 = (ctrl1 + n) % n;
            SetColor(0);
            for (int i = 0; i < n; i++) {
                goTo(72, 16 + 2 * i);
                cout << a[i] << endl;
            }
            SetColor(3);
            goTo(72, 16 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 13) {
            for (int i = 0; i < ctrl1; i++) {
                if (choose->courseName == a[ctrl1]) return;
                choose = choose->next;
            }
            system("CLS");
            return;
        }
    }
}

void deleteStuCourse(Course*& head,Course*&head1,student1*&stuHead) {
    Course* pCur = head, *pCur1 = head1;

   if (head == nullptr) {

        gotoxy(73, 10); cout << "........... is empty!\n";
        gotoxy(73, 12); cout << "You must ...............";
        gotoxy(70, 15); cout << "Press any key to continue.\n";
        _getch();
        return;
   }
   else
   {
       int i = 0;
       while (pCur != nullptr)
       {
           gotoxy(70, 12 + i);
           cout << "id: " << pCur->id << " - Course name: " << pCur->courseName;
           i += 2;
           pCur = pCur->next;
       }
       pCur = head;
       string s;
       gotoxy(70, 12 + i);
       cout << "Please enter the Course name to remove: ";
       cin >> s;
       if (pCur->courseName == s)
       {
           head = head->next;
           delete pCur;
       }
       else 
       {
           while (pCur->next->courseName != s && pCur->next != nullptr)
           {
               pCur = pCur->next;
           }
           if (pCur->next != nullptr)
           {
               Course* tmp = pCur->next;
               pCur->next = pCur->next->next;
               delete tmp;
           }
       }
       while (pCur1 != nullptr && pCur1->courseName != s)
       {
           pCur1 = pCur1->next;
       }
       if (pCur1 != nullptr)
       {
           student* pStu = pCur1->stuHead;
           if (pStu->stuId == stuHead->stuId)
           {
               pCur1->stuHead = pCur1->stuHead->nextStu;
               delete pStu;
           }
           else
           {
               while (pStu->nextStu->stuId != stuHead->stuId && pStu->nextStu != nullptr)
               {
                   pStu = pStu->nextStu;
               }
               if (pStu->nextStu != nullptr)
               {
                   student* ptmp = pStu->nextStu;
                   pStu->nextStu = pStu->nextStu->nextStu;
                   delete ptmp;
               }
           }
       }
      
   }
}

void displayYear(SchoolYear* head, SchoolYear* &choose){

    choose = head;
    SchoolYear* cur = head;
    int n = 0;
    while (cur != nullptr) {
        n++;
        cur = cur->SYnext;
    }
    cur = head;
    string* a = new string[n];
    for (int i = 0; i < n; i++) {
        a[i] = cur->year;
        cur = cur->SYnext;
    }
    cur = head;
    SetColor(0);
    for (int i = 0; i < n; i++) {
        goTo(72, 16 + 2 * i);
        cout << a[i] << endl;
    }
    SetColor(3);
    goTo(72, 16);
    cout << a[0] << endl;
    int ctrl;
    int ctrl1 = 0;
    while (1) {
        ctrl = _getch();
        if (ctrl == 72) {
            ctrl1--;
            ctrl1 = (ctrl1 + n) % n;
            SetColor(0);
            for (int i = 0; i < n; i++) {
                goTo(72, 16 + 2 * i);
                cout << a[i] << endl;
            }
            SetColor(3);
            goTo(72, 16 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 80) {
            ctrl1++;
            ctrl1 = (ctrl1 + n) % n;
            SetColor(0);
            for (int i = 0; i < n; i++) {
                goTo(72, 16 + 2 * i);
                cout << a[i] << endl;
            }
            SetColor(3);
            goTo(72, 16 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 13) {
            for (int i = 0; i < ctrl1; i++) {
                choose = choose->SYnext;
            }
            system("CLS");
            return;
        }
    }
}
void displaySes(SchoolYear* head, semester*& choose) {
    choose = head->headSem;
    string a[3];
    a[0] = "Semester 1";
    a[1] = "Semester 2";
    a[2] = "Semester 3";
    int n = 3;
    SetColor(0);
    for (int i = 0; i < n; i++) {
        goTo(72, 16 + 2 * i);
        cout << a[i] << endl;
    }
    SetColor(3);
    goTo(72, 16);
    cout << a[0] << endl;
    int ctrl;
    int ctrl1 = 0;
    while (1) {
        ctrl = _getch();
        if (ctrl == 72) {
            ctrl1--;
            ctrl1 = (ctrl1 + n) % n;
            SetColor(0);
            for (int i = 0; i < n; i++) {
                goTo(72, 16 + 2 * i);
                cout << a[i] << endl;
            }
            SetColor(3);
            goTo(72, 16 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 80) {
            ctrl1++;
            ctrl1 = (ctrl1 + n) % n;
            SetColor(0);
            for (int i = 0; i < n; i++) {
                goTo(72, 16 + 2 * i);
                cout << a[i] << endl;
            }
            SetColor(3);
            goTo(72, 16 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 13) {
            for (int i = 0; i < ctrl1; i++) {
                choose = choose->nextSem;
            }
            system("CLS");
            return;
        }
    }
}
void displayClass(classR* head, classR*& choose) {
    choose = head;
    classR* cur = head;
    int n = 0;
    while (cur != nullptr) {
        n++;
        cur = cur->next;
    }
    cur = head;
    string* a = new string[n];
    for (int i = 0; i < n; i++) {
        a[i] = cur->className;
        cur = cur->next;
    }
    cur = head;
    SetColor(0);
    for (int i = 0; i < n; i++) {
        goTo(72, 16 + 2 * i);
        cout << a[i] << endl;
    }
    SetColor(3);
    goTo(72, 16);
    cout << a[0] << endl;
    int ctrl;
    int ctrl1 = 0;
    while (1) {
        ctrl = _getch();
        if (ctrl == 72) {
            ctrl1--;
            ctrl1 = (ctrl1 + n) % n;
            SetColor(0);
            for (int i = 0; i < n; i++) {
                goTo(72, 16 + 2 * i);
                cout << a[i] << endl;
            }
            SetColor(3);
            goTo(72, 16 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 80) {
            ctrl1++;
            ctrl1 = (ctrl1 + n) % n;
            SetColor(0);
            for (int i = 0; i < n; i++) {
                goTo(72, 16 + 2 * i);
                cout << a[i] << endl;
            }
            SetColor(3);
            goTo(72, 16 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 13) {
            for (int i = 0; i < ctrl1; i++) {
                choose = choose->next;
            }
            system("CLS");
            return;
        }
    }
}

void disAllStuClass(classR* hed) {
    student1* head = hed->stu1;
    while (head != nullptr) {
        cout << "No: " << head->no << endl;
        cout << "ID: " << head->stuId << endl;
        cout << "Full name: " << head->firstName << " " << head->lastName << endl;
        cout << "Sex: " << head->gender << endl;
        cout << "Birth: " << head->date << endl;
        cout << "Social ID: " << head->socId << endl;
        cout << "-------------------------" << endl;
        head = head->nextStu;
    }
    cout << " Press any key to back";
    _getch();
}
void inputPointMid(Course*& head) {
    ShowCur(1);
    SetColor(0);
    cout << "NO  Student ID  Full Name         Midterm Point " << endl;
    student* cur = head->stuHead;
    int i = 1;
    while (cur != nullptr) {
        cout << i << "   " << cur->stuId << "    " << cur->firstName << " " << cur->lastName;
        goTo(39, i);
        cin >> cur->point.mid;
        cur->point.total = cur->point.final * 0.6 + cur->point.mid * 0.4;
        cur = cur->nextStu;
        i++;
    }
}
void inputPointFinal(Course*& head) {
    ShowCur(1);
    SetColor(0);
    cout << "NO  Student ID  Full Name         Final Point " << endl;
    student* cur = head->stuHead;
    int i = 1;
    while (cur != nullptr) {
        cout << i << "   " << cur->stuId << "    " << cur->firstName << " " << cur->lastName;
        goTo(39, i);
        cin >> cur->point.final;
        cur->point.total = cur->point.final * 0.6 + cur->point.mid * 0.4;
        cur = cur->nextStu;
        i++;
    }
}
void menuPoint(int& ctrl1) {
    SetColor(0);
    string a[3];
    a[0] = "VIEW POINT";
    a[1] = "ENTER POINT";
    a[2] = "EXPORT POINT";
    int n = 3;
    for (int i = 0; i < n; i++) {
        goTo(72, 16 + 2 * i);
        cout << a[i] << endl;
    }
    SetColor(3);
    goTo(72, 16);
    cout << a[0] << endl;
    int ctrl;
    ctrl1 = 0;
    while (1) {
        ctrl = _getch();
        if (ctrl == 72) {
            ctrl1--;
            ctrl1 = (ctrl1 + n) % n;
            SetColor(0);
            for (int i = 0; i < n; i++) {
                goTo(72, 16 + 2 * i);
                cout << a[i] << endl;
            }
            SetColor(3);
            goTo(72, 16 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 80) {
            ctrl1++;
            ctrl1 = (ctrl1 + n) % n;
            SetColor(0);
            for (int i = 0; i < n; i++) {
                goTo(72, 16 + 2 * i);
                cout << a[i] << endl;
            }
            SetColor(3);
            goTo(72, 16 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 13) {
            system("CLS");
            return;
        }
    }
}
void displapPoint(Course* head) {
    ShowCur(1);
    SetColor(0);
    cout << "NO  Student ID  Full Name         Midterm Point   Final Point  Total Point" << endl;
    student* cur = head->stuHead;
    int i = 1;
    while (cur != nullptr) {
        if( i < 10)  cout << i << "   " ;
        else  cout << i << "  " ;
        cout <<  cur->stuId << "    " << cur->firstName << " " << cur->lastName;
        goTo(39, i);
        if( cur->point.mid  < 10) cout << cur->point.mid << "             " ;
        else cout << cur->point.mid << "            " ;
        if(cur->point.final  < 10 ) cout << cur->point.final << "             " ;
        else cout << cur->point.final << "            "; 
        cout << cur->point.total << endl;
        cur = cur->nextStu;
        i++;
    }
    cout << "Press any key to back !!!!";
    _getch();
}
void menuClass1(int& ctrl1) {
    SetColor(0);
    string a[2];
    a[0] = "VIEW CLASS";
    a[1] = "ENTER CLASS";
    int n = 2;
    for (int i = 0; i < n; i++) {
        goTo(72, 16 + 2 * i);
        cout << a[i] << endl;
    }
    SetColor(3);
    goTo(72, 16);
    cout << a[0] << endl;
    int ctrl;
    ctrl1 = 0;
    while (1) {
        ctrl = _getch();
        if (ctrl == 72) {
            ctrl1--;
            ctrl1 = (ctrl1 + n) % n;
            SetColor(0);
            for (int i = 0; i < n; i++) {
                goTo(72, 16 + 2 * i);
                cout << a[i] << endl;
            }
            SetColor(3);
            goTo(72, 16 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 80) {
            ctrl1++;
            ctrl1 = (ctrl1 + n) % n;
            SetColor(0);
            for (int i = 0; i < n; i++) {
                goTo(72, 16 + 2 * i);
                cout << a[i] << endl;
            }
            SetColor(3);
            goTo(72, 16 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 13) {
            system("CLS");
            return;
        }
    }
}
void menuPoint1(int& ctrl1) {
    SetColor(0);
    string a[2];
    a[0] = "MID POINT";
    a[1] = "FINAL POINT";
    int n = 2;
    for (int i = 0; i < n; i++) {
        goTo(72, 16 + 2 * i);
        cout << a[i] << endl;
    }
    SetColor(3);
    goTo(72, 16);
    cout << a[0] << endl;
    int ctrl;
    ctrl1 = 0;
    while (1) {
        ctrl = _getch();
        if (ctrl == 72) {
            ctrl1--;
            ctrl1 = (ctrl1 + n) % n;
            SetColor(0);
            for (int i = 0; i < n; i++) {
                goTo(72, 16 + 2 * i);
                cout << a[i] << endl;
            }
            SetColor(3);
            goTo(72, 16 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 80) {
            ctrl1++;
            ctrl1 = (ctrl1 + n) % n;
            SetColor(0);
            for (int i = 0; i < n; i++) {
                goTo(72, 16 + 2 * i);
                cout << a[i] << endl;
            }
            SetColor(3);
            goTo(72, 16 + ctrl1 * 2);
            cout << a[ctrl1];
            SetColor(0);
        }
        if (ctrl == 13) {
            system("CLS");
            return;
        }
    }
}

void publishedPoint(Course*& head, int ctrl) {
    SetColor(0);
    if (head == nullptr) return;
    for (int i = 0; i < ctrl; i++) {
        head = head->next;
    }
    head->published = true;
    cout << "Published succesfull!!! Press any key to back"; _getch();
}
void viewStdPoint(Course*& head, int ctrl, int  id) {
    SetColor(0);
    if (head == nullptr) return;
    for (int i = 0; i < ctrl; i++) {
        head = head->next;
    }
    if (checkStucCourse(head, id)) {
        if (head->published) {
            student* stu = head->stuHead;
            while (stu->stuId != id) {
                stu = stu->nextStu;

            }
            cout << "Student ID  Full Name         Midterm Point   Final Point  Total Point" << endl;
            student* cur = stu;
            cout << cur->stuId << "    " << cur->firstName << " " << cur->lastName;
            goTo(39, 1);
            cout << cur->point.mid << "             " << cur->point.final << "             " << cur->point.total << endl;
        }
        else cout << "Your point is unpublished!!!! Come back later !!!!! Press any key to back!!!!"; _getch();
    }
    else cout << "you don't enroll this course!!! Press any key to back!!!!"; _getch();

}
void viewProfile(student1* stuHead, int stuId)
{
    while (stuHead->stuId != stuId)
    {
        stuHead = stuHead->nextStu;
    }
    gotoxy(72, 10);
    cout << "NO: " << stuHead->no;
    gotoxy(72, 12);
    cout << "ID: " << stuHead->stuId;
    gotoxy(72, 14);
    cout << "SOCIAL ID: " << stuHead->socId;
    gotoxy(72, 16);
    cout << "NAME: " << stuHead->firstName << " " << stuHead->lastName;
    gotoxy(72, 18);
    cout << "GENDER: " << stuHead->gender;
    gotoxy(72, 20);
    cout << "DATE: " << stuHead->date;
    gotoxy(72, 22);
    cout << "press any key to back ";
    _getch();
}
bool checkStucCourse(Course* head, int id) {
    student* headStu = head->stuHead;
    while (headStu != nullptr) {
        if (headStu->stuId == id) {
            return true;
        }
        headStu = headStu->nextStu;
    }
    return false;
}
void outputPointCSV(Course* head){
    ofstream fa;
    ifstream f;
    f.open("default.txt");
    string year ,Sem ;
    f>> year;
    f>> Sem;
    f.close();
    if(head == nullptr ) return;
    fa.open(year +'_'+ Sem+'_' + head->courseName + ".csv");
    student* cur = head->stuHead;
    int i = 1;
    while (cur != nullptr) {
        fa << i << "," << cur->stuId << "," << cur->firstName << "," << cur->lastName<<",";
        goTo(39, i);
        fa << cur->point.mid << "," << cur->point.final << "," << cur->point.total << endl;
        cur = cur->nextStu;
        i++;
    }
    fa.close();
}

void hello() {
    for (int i = 1; i <= 8; ++i) {
        if (i == 1) {
            gotoxy(38, 7); cout << char(201);
            for (int j = 1; j <= 80; ++j) {
                gotoxy(38 + j, 7); cout << char(205);
            }
            gotoxy(118, 7); cout << char(187);
        }
        else if (i == 8) {
            gotoxy(38, 14); cout << char(200);
            for (int j = 1; j <= 80; ++j) {
                gotoxy(38 + j, 14); cout << char(205);
            }
            gotoxy(118, 14); cout << char(188);
        }
        else {
            gotoxy(38, i + 6); cout << char(186);
            gotoxy(118, i + 6); cout << char(186);
        }
    }
    gotoxy(41, 8); cout << "MMMMM      MMMMM   OOOOOOOOO    OOOOOOOOO   DDDDDDD    LL        EEEEEEEEEE" << endl;
    gotoxy(41, 9); cout << "M    M    M    M  OO       OO  OO       OO  DD     DD  LL        EE" << endl;
    gotoxy(41, 10); cout << "M  M  M  M  M  M  OO       OO  OO       OO  DD     DD  LL        EEEEEEEEE" << endl;
    gotoxy(41, 11); cout << "M  MM  MM  MM  M  OO       OO  OO       OO  DD     DD  LL        EEEEEEEEE" << endl;
    gotoxy(41, 12); cout << "M  M        M  M  OO       OO  OO       OO  DD     DD  LL        EE" << endl;
    gotoxy(41, 13); cout << "MMMM        MMMM   OOOOOOOOO    OOOOOOOOO   DDDDDDD    LLLLLLLL  EEEEEEEEEE" << endl;
}