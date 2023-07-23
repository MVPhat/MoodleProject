#include "Header.h"
//#include "Source.cpp"

int main(){
	resizeConsole(1270, 600); // width, height
	DisableCtrButton(0,0,0); // 1: off, 0: on     lần lượt là tắt - thu nhỏ - full screen
	system("color F0");
	SchoolYear* SchoolYearHead = nullptr;
	classR* classHead = nullptr;
	account user;
	string className;
	Course* courseHead = nullptr;
	student1* stuHead = nullptr;
	int ctrl = 0, index;
	int ctrl1=0;
	InSchoolYeartxt(SchoolYearHead);
	InDaySem(SchoolYearHead);
	readFile(SchoolYearHead); // doc file luu
	readClass(classHead);
	courseHead = loadDefaultCourse(SchoolYearHead);
	while (1)
	{
		hello();
		menu(ctrl);
		//teacher
		if (ctrl == 0) {

			while (1)
			{
				clearLogin();
				user.name = "";
				user.password = "";
				teacherLogin(user.name, user.password);
				bool check = checkAcc("accTea.txt", user, index);
				if (!check)
					clearPass(user);
				else
					break;
			}
			while (1)
			{
				courseHead = loadDefaultCourse(SchoolYearHead);
				menuTeacher(ctrl);
				if (ctrl == 0)
				{
					menuSchoolyear(ctrl);
					if (ctrl == 0)
					{
						CreateSchoolYear(SchoolYearHead);
						updateSY(SchoolYearHead);
					}
					else if (ctrl == 1)
					{
						SchoolYear* choose = nullptr;
						semester* chooseSem = nullptr;
						Course* courseH = nullptr;
						displayYear(SchoolYearHead, choose);
						displaySes(choose, chooseSem);
						if(chooseSem != nullptr ) {
							courseH = chooseSem->cour;
							displayAllCourse(courseH, ctrl);
							displayCourse(ctrl, courseH);
						}
					}
					else if (ctrl == 2)
					{
						continue;
					}
				}
				else if (ctrl == 1)
				{
					menuSemester(ctrl);
					if (ctrl == 0)
					{
						CreateSem(SchoolYearHead);
						updatedaySem(SchoolYearHead);
					}
					else if (ctrl == 1)
					{
						continue;
					}
				}
				else if (ctrl == 2)
				{
					ctrl1 = 0;
					menuPoint(ctrl1);
					displayAllCourse(courseHead, ctrl);
					Course* courseH = courseHead;
					for( int i = 0 ; i <ctrl ;i++){
						courseH = courseH -> next;
					}
					if (ctrl1 == 1){
						menuPoint1(ctrl1);
						if(ctrl1 == 0)
						 	inputPointMid(courseH);
						else if(ctrl1 == 1)
						 	inputPointFinal(courseH);
					}
					else if (ctrl1 == 0) 
						displapPoint(courseH);
					else{
						outputPointCSV(courseH);
					}
				}
				else if (ctrl == 3)
				{
					menuClass(ctrl);
					if(ctrl == 0)
					{
						//enter from csv
					
						string fileClassName;
						cout << "Enter className: ";
						cin >> className;
						cout << "Enter Student file name : ";
						cin >> fileClassName;
						bool check = true;
						readingAllCSVStudentFile(fileClassName, classHead, className, check);
						
					}
					else if (ctrl == 1)
					{
						/*classR* choose = nullptr;
						displayClass(classHead, choose);
						disAllStuClass(choose);		*/
						viewAllClasss(classHead);
						cout << "\nEnter Class Name to view Student: ";			
						cin >> className;
						system("cls");
						outputStudentFromClass(classHead, className);
						cout << "Enter Any Key To Come Back !";
						_getch();
					
					}
					else if (ctrl == 2)
					{
						
						break;
					}
				}
				else if (ctrl == 4)
				{
					while(1){
						menuCourse(ctrl);
						if (ctrl == 0)
						{
							readingCSVCourseFile(courseHead);
							
							//add course
						}
						else if (ctrl == 1)
						{
							outputCourse(courseHead);

							//view coourse
						}
						else if (ctrl == 2)
						{
							Course* courseH = courseHead;
							displayAllCourse(courseH, ctrl);
							publishedPoint(courseH,ctrl);
						}
						else if (ctrl == 3)
						{
							//update course
							cout << "\n Enter Course Name To Update: ";
							string CID;
							cin >> CID;
							teacherUpdateCourse(CID, courseHead, classHead);
						}
						else if (ctrl == 4)
						{
							break;
						}
					}
				}
				else if (ctrl == 5)
				{
					SchoolYear* choose = nullptr;
					semester* chooseSem = nullptr;
					Course* courseH = nullptr;
					displayYear(SchoolYearHead, choose);
					displaySes(choose, chooseSem);
					setDefault(choose, chooseSem);
					courseHead = loadDefaultCourse(choose);
				}
				else if(ctrl == 6)
				{
					break;
				}
			}
			continue;
		}
		//student
		else if (ctrl == 1)
		{
			while (1)
			{
				clearLogin();
				user.name = "";
				user.password = "";
				studentLogin(user.name, user.password);
				bool check = checkAcc("accStd.txt", user, index);
				if (!check)
					clearPass(user);
				else
					break;
			}
			int id = stringToInt(user.name);
			stuHead = findStudentWithSID(classHead, id);
			while (1)
			{
				courseHead = loadDefaultCourse(SchoolYearHead);
				menuStudent(ctrl);
				if (ctrl == 0) {
				//	int id = stringToInt(user.name);
					bool check = true;
			
					if (check) {

						Course* choose = nullptr;
						chooseCourse(courseHead, choose);
						//stuHead = findStudentWithSID(classHead, id);
						enrollOneStudent(choose->id, id, stuHead, courseHead, check);
		
						if (check) {
							//viewListEnrollOneStudent(id, stuHead);
							
							goTo(61, 16);
							cout << "Enroll successful !!!! Press any key to back !!!!";
							_getch();
						}
						else {
							system("cls");
							goTo(61, 16);
							cout << "Enroll unsucessfull !!!! Press any key to back !!!!";
							_getch();
						}
					}
				}
				else if (ctrl == 1) {
					//student1* stuHead = findStudentWithSID(classHead, stringToInt(user.name));
					//outputCourse(stuHead->courseHead);
					viewListEnrollOneStudent(id, stuHead);
					cout << "Press Any Key To Back ";
					_getch();
				}
				else if (ctrl == 2) {
					stuHead = findStudentWithSID(classHead, stringToInt(user.name));
					deleteStuCourse(stuHead->courseHead, courseHead, stuHead);
	
				}
				else if (ctrl == 3) {
					int id = stringToInt(user.name);
					Course* courseH = nullptr;
					courseH = courseHead;
					displayAllCourse(courseH, ctrl);
					viewStdPoint(courseH,ctrl,id);
				}
				else if (ctrl == 5)
				{
					viewProfile(stuHead, id);
				}
				else if (ctrl == 6) {
					break;
				}
				else if (ctrl == 4) {
					string a;
					goTo(72, 16);
					cout << "Enter your new password:";
					cin >> a;
					changePass("accStd.txt", user, index, a);
				}
			}
		}
		else if (ctrl == 2)
		{
			break;
		}
	}
	saveFile(SchoolYearHead);
	saveClass(classHead);


	system("pause");
	return 0;
}
