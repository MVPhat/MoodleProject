#ifndef _HEADER_H_
#define _HEADER_H_

#include <fstream>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <string>
#include <time.h>
#include <cstdlib>
#include <mmsystem.h>
#include <direct.h>
#include <sstream>

using namespace std;

struct point{
	float mid = 0.0;
	float total = 0.0 ;
	float final = 0.0;
};
struct account {
	string name, password;
};

struct student {
	int no;
	int stuId;
	string firstName;
	string lastName;
	string gender;
	string date;
	point point;
	int socId;
	student* nextStu = nullptr;
};

//session perform
struct sessionPerform {
	string sesDay;
	string sestime;
	sessionPerform* next = nullptr;
 };

 struct Course { 
	 int id;
	 string courseName;
	 string teacherName;
	 int creditNum;
	 int maxStuNum = 50; 
	 int dayTotal = 0;
	 bool published = false;
	 sessionPerform* headDay = nullptr;
	 Course* next = nullptr;
	 student* stuHead = nullptr;
 };
 struct student1 {
	 int no;
	 int stuId;
	 string firstName;
	 string lastName;
	 sessionPerform* headDay = nullptr;
	 string gender;
	 string date;
	 int socId;
	 student1* nextStu = nullptr;
	 point point;
	 Course* courseHead = nullptr;
 };

 struct classR {
	 string className;
	 student* stu = nullptr;
	 student1* stu1 = nullptr;
	 classR* next = nullptr;
 };

struct semester {
	string start, end;
	int semX;
	semester* nextSem;
	Course* cour = nullptr;
	bool check = false; // true la da tao roi
};

struct SchoolYear {
	string year;
	semester* headSem = nullptr;
	SchoolYear* SYnext;
};
void DisableCtrButton(bool Close, bool Min, bool Max);
void resizeConsole(int width, int height);
void goTo(SHORT posX, SHORT posY);
void clearPass(account& user);
bool checkAcc(string filename, account user, int &index);
void changePass(string filename, account &user, int index, string newpass);
void menu(int& ctrl1);
void menuTeacher(int& ctrl1);
void menuSchoolyear(int& ctrl1);
void menuClass(int& ctrl1);
void menuSemester(int& ctrl1);
void menuStudent(int& ctrl1);
void SetColor(int ForgC);
void ShowCur(bool a);
void teacherLogin(string& name, string& pass);
void studentLogin(string& name, string& pass);
void clearLogin();
int stringToInt(string a );

//input CSV file
void inputStudent(ifstream& f, classR*& classHead, string className);
void outputStudentFromClass(classR* classHead, string className);
void deleteClassR(classR*& classHead);

void readingCSV(string fileName, classR*& classHead, string className);
// create class;
void createClass(classR*& classHead, string className);
void viewAllClasss(classR* classHead);
// create csv file 
void writingCSV(string fileName, int n);

//create course
void readingCSVCourseFile(Course *&courseHead);
void writingCSVCourseFile(string fileName);
void createCourse(Course* &courseHead);
void inputCourse(ifstream &f, Course*& courseHead);
void deleteStuCourse(Course*& head, Course*& head1, student1*& stuHead);
void outputCourse(Course* courseHead);
void updateCourse(string courseName, string fileName,Course* &courseHead);
void teacherUpdateCourse(string courseName, Course*& courseHead, classR*& classHead);
void deleteCourse(Course*& courseHead);
void readingAllCSVStudentFile(string fileName, classR*& classHead, string className, bool& check);
void outputPointCSV(Course* head);
// giao diện đầu

void hello();
void setDefault(SchoolYear*choose,semester*chooseSem);
// Create + output + delete school year
void CreateSchoolYear(SchoolYear*& SchoolYearHead);
bool checkIsYear(SchoolYear* head, string newyear);
void ViewSchoolYear(SchoolYear* headyear);
void viewProfile(student1*stuHead, int stuId);
//create sémester
void createSemester(SchoolYear s[], string year, int semester, string start, string end);
// Export list of student
void exportCSVStudent(string fileName, Course courseHead, string courseName);
void enterResult(string fileName, Course courseHead, string courseName);
void viewScoreBoard();
void chooseCourse(Course* head,Course* &choose);
//Student Enroll
bool checkTimeEnroll(int courseID, int SID, student1* stuHead, Course* courseHead);
void enrollOneStudent(int courseID, int SID, student1* &stuHead, Course* &courseHead,bool &check);
void viewListEnrollOneStudent(int SID, student1* stuHead);
void removeCourseOneStudent(int courseID, int SID, student1* &stuHead, Course* &courseHead);
void coppyStudent(student1*& stu1Head, student* stuHead);
void saveStudent1ToClassR(classR*& classHead);
void deleteStuCourse(Course*& head,Course*&head1,student1*&stuHead);
student1* findStudentWithSID(classR* classHead, int SID);
void viewListOfStudentInACourse(Course* courseHead, int courseID);
bool checkTime(Course cou , student stud);
void pushTime(Course cou , student stud);
void InSchoolYeartxt(SchoolYear*& head);
void updateSY(SchoolYear* &head);
void displayAllCourse(Course* head, int &ctrl1);
void displayCourse( int ctrl, Course* head);
void displayYear(SchoolYear* head, SchoolYear* &choose);
void displaySes(SchoolYear* head,semester* &choose);
void displayClass(classR* head , classR* &choose);
void disAllStuClass(classR* hed);
void inputPointMid(Course* &head);
void inputPointFinal(Course* &head);
void menuPoint(int& ctrl1);
void menuClass(int& ctrl1);
void menuCourse(int& ctrl1);
void menuClass1(int& ctrl1);
void displapPoint(Course* head);
void menuPoint1(int&ctrl1);
void publishedPoint(Course* &head , int ctrl);
void viewStdPoint(Course* &head , int ctrl, int id);
bool checkStucCourse(Course* head , int id);
int createAccStu();
Course* loadDefaultCourse(SchoolYear* yearHead);
void deleteStuCourse(Course*& head, Course*& head1, student1*& stuHead);
void saveClass(classR* classHead);
void saveFile(SchoolYear* yearHead);
void readFile(SchoolYear*& yearHead1);
void readClass(classR*& classHead1);
//create semester

void InDaySem(SchoolYear*& head);
void CreateSem(SchoolYear*& headyear);
void updatedaySem(SchoolYear*& head);
void displapPoint(Course* head);
#endif