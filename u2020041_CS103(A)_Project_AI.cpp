#include <stdio.h>                // pre-processing directives for renaming and removing files
#include <iostream>               // pre-processing directives
#include <string>                 // pre-processing directives for string function 
#include <fstream>                // pre-processing directives for file handling (i/o)
#include <unistd.h>               // pre-processing directives for pausing the process

using namespace std;

void login ( string );                                       //login interface
void COE_Interface( string, string );                        //COE Interface
void teacher_interface(string, string, string);                      //Teacher Interface
void student_interface(string, string, string);              //student interface    
void Register_Teachers ();                                   //for registration of teachers by coe
void Register_Students (string);                             //for registration of students by both coe and teacher
void Register_Exams ();                                      // for registration of exams
void exams_schedule();                                       // for scheduling exams
void new_message_COE ();                                     // for sending messages (coe)
void recieve_messages_COE();                                 // for recieving messages (coe)
void update_password(string, string, string);                // for updating password (coe)     
void view_exams_teacher(string,string);                      // view exams (teacher)                     
void new_message_teacher();                                  // send messages (teacher)
void recieve_message_teacher();                              // recieve messages (teacher)
void register_for_exam(string);                              // student registration for exam
void view_exams_student(string, string, string);              //To look at the time table (student)
void update_password_student(string, string, string);        // updating of password
void display_become_coe();                                   //styling
void welcome();                                              //styling
void login_display();                                        //styling
void coe_display();                                          //styling
void teacher_display();                                      //styling
void student_display();                                      //styling
void thank_you();                                            //styling
void unregistered_student();
void register_students_teacher( string );

int main ()                                                 //main program
{	
	string ID, Password;
	int i;
	
	ifstream COE("COE_Credentials.txt");
	
	if (!COE.is_open())                                // when program is run first time
	{
		display_become_coe();                        
		cout << "Enter ID: ";                          // INPUT ID
		getline (cin, ID);
		cout << "Enter Password: ";                   // INPUT OUTPUT
		getline(cin, Password);
		
		ofstream COE_in("COE_Credentials.txt");
		COE_in << ID << endl << Password << endl;          // COE DATA IS SAVED IN FILE COE_Credentials.txt
		COE.close();
	}
	
	while (i==0)                                          // loop to check program status open/close
	{
		string num;
		string CHOICE;
		
		system ("CLS");                                 // clears screen
		
		welcome ();	                                                             // welcome display call
		cout << endl << endl << endl << "\t\tChoose an option: " << endl;        // options determine next process
		cout << "\t\t1. COE" << endl;
		cout << "\t\t2. Teacher" << endl;
		cout << "\t\t3. Student" << endl;
		
		getline(cin, num);
		
		login(num);
			
		system ("CLS");
		cout << "Do you want to quit(y/n)?" << endl;                       // prompts user to quit or not
		getline(cin, CHOICE);
			
		if (CHOICE == "Y" || CHOICE == "y")                              // Y breaks loop and program ends
		{
			system ("CLS");
			thank_you();
			break;
		}
	}

	
	
	return 0;
}

void login ( string choice )                       // passed value determines course of action
{
	string Choice;
	if (choice == "1")                              // takes you to COE Part of program
	{
		string ID, Password, ID_Check, Password_Check;
		int i = 0;
				
		system ("CLS");
				
		while (i==0)                              //loop keeps running until user enters correct password
			{
				system ("CLS");
				login_display();                 // call for login display
				cout << endl << endl << endl << endl << endl << endl << endl << "\t\t\t\tEnter ID: ";
				getline (cin, ID_Check);
				
				cout << "\t\t\t\tEnter Password: ";
				getline (cin, Password_Check);
				
				ifstream login;
				login.open("COE_Credentials.txt");                   //for authentication of credits
				while (getline(login, ID), getline(login, Password))
				{
					if (ID == ID_Check && Password == Password_Check)
					{
						break;
					}
				}
				
				if (ID == ID_Check && Password == Password_Check)
				{
					system ("CLS");
					cout << endl << endl << endl << endl << endl << endl << "Successfully Logged In." << endl;
					sleep(1);
					
					system ("CLS");
					cout << endl << endl << endl << endl << endl << endl<< "Loading...";
					sleep(1);
					
					while (i==0)                // this loop is used for keeping the user logged in or log him out
					{
					
						COE_Interface(ID, Password);               // takes you to COE log
						
						system("CLS");
						cout << "Do you want to logout(y/n)?" ;
						getline(cin, Choice);
						
						if (Choice == "Y" || Choice == "y")                // Y logs out user
						{
							i++;
						}
					}
					
					break;
				}
				
				cout << endl << endl << endl << endl << endl << "Wrong Credentials Entered." << endl;
				sleep(1);
				system("CLS");
				cout << endl << endl << endl << endl << endl << "Enter Correct ID or Password." << endl << endl << endl;
				sleep(2);
			}			
	}
	else if (choice == "2")                                     // 2 is the choice for teacher and takes you to the teacher part 
	{
		string ID, Password, subject, ID_Check, Password_Check, message, section, students;
		int i = 0;
		
		ifstream login("Teacher_Info.txt");
		if (login.is_open())                                //checks if file exists
		{
			while (i==0)                                   //loop keeps running until user enters right credits
			{
				system ("CLS");
				login_display();
				cout << endl << endl << endl << endl << "\t\t\t\tEnter ID: ";
				getline (cin, ID_Check);
				
				cout << "\t\t\t\tEnter Password: ";
				getline (cin, Password_Check);
				
				ifstream login("Teacher_Info.txt");                      //Teacher_Info is the file containing teacher information
				
				if (login.is_open())
				{
					while (getline(login, ID), getline(login, Password), getline(login, section), getline(login, subject), getline(login, students))
					{
						if (ID == ID_Check && Password == Password_Check)
						{
							break;
						}
					}
					
					if (ID == ID_Check && Password == Password_Check)
					{
						system ("CLS");
						cout << endl << endl << endl << endl << endl << endl << "Successfully Logged In." << endl;
						sleep(1);
					
						system ("CLS");
						cout << endl << endl << endl << endl << endl << endl << "Loading...";
						sleep(1);
						
						while (i==0)
						{
							system("CLS");
							teacher_interface(ID, Password, section);               //takes you to teacher log
							system ("CLS");
							cout << "Do you want to logout(y/n)?";
							getline(cin, Choice);
							
							if (Choice == "Y" || Choice == "y")
							{
								i++;
							}
						}
						break;
					}
					
					cout << endl << endl << endl << endl << endl << endl << "Wrong Credentials Entered." << endl;
					sleep(1);
					system ("CLS");
					cout << endl << endl << endl << endl << endl << endl << "Enter Correct ID or Password." << endl << endl << endl;
					sleep(2);
				}
			}
		}
		else
		{
			system ("CLS");
			cout << "The File Does Not Exist." << endl;
			cout << "Message COE? " << endl;                   // if file doesn't exist user can tell coe that file is not present 
			getline(cin, message);
			
			if (message == "Y"|| message == "y")
					{
						new_message_teacher();                  // a teacher can message coe using this function
					}
		}
		login.close();
	}
	else if(choice == "3")                                       // this choice takes you to the student part of the program
	{
		string ID, Password, name, section, subjects, ID_Check, Password_Check, section_check;
		int i = 0;
	
	while (i==0)
	{	
		system("CLS");
		login_display();                     // login styling
		
		ifstream login("Student_Info.txt");           // the file in which student's info is present
		if (login.is_open())                             // if file is present then it will proceed
		{	
			system ("CLS");
			login_display();
			cout << endl << endl << endl << endl << "\t\t\t\tEnter ID: ";
			getline (cin, ID_Check);
			
			cout << "\t\t\t\tEnter Password: ";
			getline (cin, Password_Check);
			
			while (getline(login, ID), getline(login, Password), getline(login, name), getline(login, section), getline(login, subjects))
				{
					if (ID == ID_Check && Password == Password_Check)
					{
						login.close();
						break;
					}
				}
			
			if (ID == ID_Check && Password == Password_Check)
				{
					system ("CLS");
					cout << endl << endl << endl << endl << endl << endl << "Successfully Logged In." << endl;
					sleep(1);
				
					system ("CLS");
					cout << endl << endl << endl << endl << endl << endl << "Loading...";
					sleep(1);
					while(i==0)                  // loop for log in/out
					{
						login.close();
						system("CLS");
						student_interface(section, ID, Password);                     //takes you to student log
						cout << "Do you want to logout(y/n)?";
						getline(cin, Choice);
							
						if (Choice == "Y" || Choice == "y")
						{
							i++;
						}
					}
					break;
				}
				else if (ID != ID_Check && Password == Password_Check)
				{
					cout << endl << endl << endl << endl << endl << endl << "Wrong Credentials Entered." << endl;
					sleep(1);
					system ("CLS");
					cout << endl << endl << endl << endl << endl << endl << "Enter Correct ID or Password." << endl << endl << endl;
					sleep(1);
				}
				else if (ID != ID_Check && Password != Password_Check)
				{
					cout << "You are not registered." << endl;
					cout << "Want to register(y/n)?" << endl;
					getline (cin, Choice);
					
					if (Choice == "Y" || Choice == "y")
					{
						system("CLS");
						student_display();
						unregistered_student();
					}
				}
				
				login.close();
		}
		else
		{
			system ("CLS");
			cout << "The File Does Not Exist." << endl;            //if file does not exist then user will know
			sleep(3);
			i = 1;
		}
	}
		
	}
}


void COE_Interface (string ID, string Password)          // when user is COE this function runs and it gives the ID and Password of the user to the function
{
	string choice, Choice;
	string air = "COE";                                 // this string is used for other functions
	
	system ("CLS");
	coe_display();                                     // coe styling
	cout << "Choose An Option: " << endl << "1. Register Teachers." << endl << "2. Register Students." << endl << "3. Register Exams." << endl << "4. Create Schedule." << endl << "5. Open Messages Portal." << endl << "6. Change Password."<< endl << "7. Log Out" << endl;
	//to determine the course of action
	getline (cin, choice);
	
	if (choice == "1")              // choosing 1st choice lets coe register teachers
	{
		system("CLS");
		Register_Teachers();       // function for registering teachers
	}
	else if (choice == "2")        // choosing 2nd lets coe register students
	{
		system("CLS") ;
		Register_Students(air);         //function for registering students and it takes COE as a string
	}
	else if (choice == "3")                  // choosing 3rd lets coe register exams
	{
		system("CLS");
		Register_Exams();                    //function for registering exams
	}
	else if (choice == "4")                    // choosing 4th lets coe create a schedule
	{
		system("CLS");
		exams_schedule();                      // function for creating schedule
	}
	else if (choice == "5")                    //5th lets coe send and recieve messages
	{
		system ("CLS");
		coe_display();
		cout << "1. Inbox" << endl << "2. Create a new message." << endl;
		getline(cin, Choice);
		if (Choice == "1")                    // 1 opens inbox of user
		{
			system("CLS");
			recieve_messages_COE();             //function to check messages for coe
		}
		else if(Choice == "2")                   // 2 opens a portal to send messages to teacher
		{
			system("CLS");
			new_message_COE();                   // function to send messages to teacher
		}
	}
	else if (choice == "6")                        //6th lets coe change password
	{
		system("CLS");
		update_password(air, ID, Password);             //function for changing password(coe)
	}
	else if (choice == "7")                          // 7th lets coe log out
	{
		system ("CLS");
	}
}

void teacher_interface( string id, string pass, string sct )                 // this function opens teacher's portal
{
	string choice;                                   
	
	system ("CLS");
	teacher_display();                                           // teacher portal styling
	cout  << endl << "1. Register Students" << endl << "2. View Exams" << endl << "3. View Students" << endl << "4. Open Messages Portal" << endl << "5. Log Out" << endl;
	getline(cin, choice);
	// to choose next course of action
	if (choice == "1")                                         // 1 lets teacher register students
	{
		system("CLS");
		register_students_teacher(sct);                                // passes Teacher as string in function and calls for function to register students
	}
	else if (choice == "2")                                    // 2 lets teacher view his duty days
	{
		system("CLS");
		view_exams_teacher(id, pass);                        // function to view exams of teacher and takes ID and Password of teacher 
	}
	else if (choice == "3")                                 // 3 lets teacher view total number of students in his faculty/course
	{
		system("CLS");
		teacher_display();
		string ID, passwords, Section, section_file, section, name, subjects, Choice;
		int count;
		cout << "Section is: " << sct << endl;
		cout << "Enter Section(.txt): ";                             // to get filename of faculty in which students are registered 
		getline (cin, section_file);
		
		system("CLS");
		teacher_display();
		
		ifstream student_out(section_file.c_str());
		while (getline(student_out, ID), getline(student_out, passwords), getline(student_out, name), getline(student_out, Section), getline(student_out, subjects))
		{
			if (!(Section == sct))
			{
				cout << "There is a student not belonging to this faculty in the file." << endl;
			} 
			else if (Section == sct)
			{
				cout << endl << "ID: " << ID << endl << "Name: " << name << endl;
				count++;
			}
		}
		
		cout << endl << "Total Students: " << count << endl;
		student_out.close();
		cout << endl << "Continue?";
		getline(cin, Choice);
		if (Choice == "Y" || Choice == "y")
		{
			system ("CLS");
		} 
		
	}
	else if (choice == "4")                            //4 lets teacher send and recieve messages
	{
		system("CLS");
		teacher_display();
		string choice;
		cout << "1. Inbox" << endl << "2. Create a new message" << endl;
		getline(cin, choice);
		//determines to open inbox or compose
		if (choice == "1")
		{
			system("CLS");
			recieve_message_teacher();              //opens teacher inbox
		}
		else if (choice == "2")
		{
			system("CLS");
			new_message_teacher();               // opens teacher's new message portal
		}
	}
	else if (choice == "5")                //5 logs you out of program
	{
		system("CLS");
	}
}

void student_interface( string sect, string iD, string PassWord )                // when student logs in, and the function gives the section, ID and Password to function
{
	system ("CLS");
	student_display();
	string air = "Student";                                         // string used for other functions
	string choice;
	
	cout << "1. View Exams" << endl << "2. Register for exam" << endl << "3. Change Password" << endl << "4. Log Out" << endl;
	getline(cin, choice);
	
	system("CLS");
	
	if (choice == "1")
	{
		system ("CLS");
		view_exams_student(sect, iD, PassWord);                //opens exam schedule and displays student his exams
	}
	else if (choice == "2")
	{
		system("CLS");
		register_for_exam(sect);                       //lets student register for exam
	}
	else if (choice == "3")
	{
		system ("CLS");
		update_password_student(air, iD, PassWord);
	}
}

void Register_Teachers ( )            //function for registering teachers
{
	string students_check, students, names, names_check, passwords, passwords_check, section, subject, choice;
	int count = 0;
	
	ifstream teacher_info("Teacher_Info.txt");                 //file containing teacher info
	
	if (teacher_info.is_open())
	{
		ifstream teacher_info("Teacher_Info.txt");
		
		while (getline(teacher_info, names), getline(teacher_info, passwords), getline(teacher_info, section), getline(teacher_info, subject), getline(teacher_info, students))
		{
			count++;
		}
		teacher_info.close();
		
		if (count == 25)                                   // maximum number of teachers can be 25
		{
			cout << "Maximum Limit Reached." << endl;
		}
		else
		{
			ofstream teacher_info("Teacher_Info.txt", ios::app);               //to register more if allowed
			
			system ("CLS");
			
			coe_display();
			while (true &&  (count < 25))
			{
				names = names_check;
				system ("CLS");
				coe_display();
				
				cout << "Teacher Name: " ;
				getline(cin, names_check);
				
				while (names == names_check)
				{
					system("CLS");
					coe_display();
					cout << "Teacher Name: ";
					getline(cin, names_check);
					cout << "Enter another name. (Name Already Registered)" << endl;
					sleep(2);
				}
				teacher_info << names_check << endl;
				
				cout << "Password: ";
				getline(cin, passwords); 
				teacher_info << passwords << endl;
				
				cout << "Section: ";
				getline(cin, section);
				teacher_info << section << endl; 
				
				cout << "Subjects (Press Spaces to enter more than one): " << endl;
				getline(cin, subject);
				teacher_info << subject << endl;
				
				cout << "Enter No. of students: " ;
				getline(cin, students);
				teacher_info << students << endl;
				
				cout << "Do you want to Enter more (y/n): " ;
				getline(cin, choice);
				
				if (choice == "N" || choice == "n")
				{
					system ("CLS");
					break;
				} 
			}
			
			for (int i=5; i>0; i--)
			{
				cout << i ;
				sleep (1);
			}
		}
		
	}
	else
	{
		cout << "Filename Does Not Exist";                    //in case file does not exist this creates a new file
		for (int i=5; i>0; i--)
		{
			cout << ".";
			sleep (1);
		}
		
		system ("CLS");
		
		cout << endl << endl << endl << endl << endl << endl << endl << "Creating A New File." << endl;
		
		sleep(2);
		
		system("CLS");
		
		names = "";
		
		ofstream teacher_info("Teacher_Info.txt", ios::app);
			
		system ("CLS");
		
		while (true && (count < 25))
			{
				names = names_check;
				system ("CLS");
				coe_display();
				cout << "Teacher Name: ";
				getline(cin, names_check);
				if (names == names_check)
				{
					system("CLS");
					coe_display();
					cout << "Enter Another Name." << endl;
					sleep(2);
					cout << "Teacher Name: ";
					getline(cin, names_check);
				}
				
				
				teacher_info << names_check << endl;
				
				cout << "Password: ";
				getline(cin, passwords); 
				teacher_info << passwords << endl;
				
				cout << "Section: ";
				getline(cin, section);
				teacher_info << section << endl; 
				
				cout << "Subjects (Press Spaces to enter more than one): " << endl;
				getline(cin, subject);
				teacher_info << subject << endl;
				
				cout << "Enter No. of students: " ;
				getline(cin, students);
				teacher_info << students << endl;
				
				cout << "Do you want to Enter more (y/n): " ;
				getline(cin, choice);
				
				if (choice == "N" || choice == "n")
				{
					system ("CLS");
					break;
				} 
			}
		
		if (count == 25)
		{
			system ("CLS");
			cout << "Maximum Limit Reached." << endl;
			sleep (5);
		}
		
		teacher_info.close();
	}
}

void Register_Students ( string Choice )                             // for registeration of students
{
	string ID, passwords, name, name_check, section, Section, subjects, choice, faculty;
	int count = 0;
	
	system ("CLS");
	coe_display();
	
	ifstream student_info("Unregistered.txt");                    //file containing info of unregistered students
	
	if (student_info.is_open())
	{	
		while (getline(student_info, name), getline(student_info, faculty), getline(student_info, subjects))
		{
			count++;
		}
		student_info.close();
		
		if (count == 0)
		{
			cout << "There are " << count << " unregistered students." << endl;                // in case file is empty
			sleep (2);
		}
		else
		{
			cout << "There are " << count << " unregistered students." << endl;                 // tells you how many unregistered
		
			cout << "Do you want to register students(y/n)?" << endl;
			getline(cin, choice);
			
			if (choice == "Y" || choice == "y")
			{
				ofstream student_info("Student_Info.txt", ios::app);                //file for registration of students
				
				system ("CLS");
				
				while (true)
				{
					system ("CLS");
					coe_display();
					
					cout << "Student ID: ";
					getline(cin, ID);
					student_info << ID << endl;
					
					cout << "Password: ";
					getline(cin, passwords);
					student_info << passwords << endl;
					
					cout << "Name: ";
					getline(cin, name_check);
					student_info << name_check << endl;
					
					cout << "Section: ";
					getline(cin, section);
					student_info << section << endl;
					
					cout << "Subjects (Press Space to enter more than one): " << endl;
					getline(cin, subjects);
					student_info << subjects << endl;
					
					cout << "Do you want to Enter more (y/n): " ;
					getline(cin, choice);
					
					if (choice == "N" || choice == "n")
					{
						system("CLS");
						break;
					} 
				}
			}
		}
		
		ifstream unregistered("Unregistered.txt");              //to remove the students who have been registered from the file
		ifstream registered("Student_Info.txt");
		ofstream replacing("Temp_File.txt");
	
		while (!unregistered.eof())
		{
			getline(unregistered, name_check); getline(unregistered, faculty); getline(unregistered, subjects);
			getline(registered, ID); getline(registered, passwords); getline(registered, name); getline(registered, section); getline(registered, subjects);
		
			if (name_check != name)
			{
				replacing << name_check << endl << faculty << endl << subjects << endl;
			}
		}
		
		unregistered.close();
		registered.close();
		replacing.close();
	
		remove ("Unregistered.txt");
		rename ("Temp_File.txt", "Unregistered.txt");
	}
	else
	{
		system ("CLS");
		coe_display();
			
		cout << "There is no file.";                    //in case there is no file                 
		for (int i=3; i>0; i--)
		{
			cout << ".";
			sleep (1);
		}
		
		system ("CLS");
		coe_display();
		
		cout << "Do you want to register(y/n)?";
		getline(cin, choice);
		if (choice == "Y" || choice == "y")
		{
			system("CLS");
			coe_display();
			ofstream registeration("Student_Info.txt", ios::app);
			while (true)
				{
					system ("CLS");
					coe_display();
					
					cout << "Student ID: ";
					getline(cin, ID);
					registeration << ID << endl;
					
					cout << "Password: ";
					getline(cin, passwords);
					registeration << passwords << endl;
					
					cout << "Name: ";
					getline(cin, name_check);
					registeration << name_check << endl;
					
					cout << "Section: ";
					getline(cin, section);
					registeration << section << endl;
					
					cout << "Subjects (Press Space to enter more than one): " << endl;
					getline(cin, subjects);
					registeration << subjects << endl;
					
					cout << "Do you want to Enter more (y/n): " ;
					getline(cin, choice);
					
					if (choice == "N" || choice == "n")
					{
						system("CLS");
						break;
					} 
				}
			
		}
	}
}


void Register_Exams()                  //for registration of exams
{
	string ID, Instructor_ID, strength, choice;
	int count;
	
	ifstream examinations("Exams.txt");                  //exams containing file
	
	if (examinations.is_open())
	{	
		while (getline (examinations, ID), getline (examinations, Instructor_ID), getline (examinations, strength))
		{
			count++;
		}
		
		if (count == 25)
		{
			cout << "Maximum Exams Limit Reached." << endl;
		}
		else
		{
			ofstream examinations("Exams.txt", ios::app);
			
			while (true && count < 25)
			{
				system("CLS");
				coe_display();
				cout << "Exam ID: ";
				getline(cin, ID);
				examinations << ID << endl;
				
				cout << "Instructor: ";
				getline (cin, Instructor_ID);
				examinations << Instructor_ID << endl;
				
				cout << "Total Strength Of Course: ";
				getline(cin, strength);
				examinations << strength << endl;
				 
				cout << "Do you want to enter more(y/n)" << endl;
				getline(cin, choice);
				if (choice == "N" || choice == "n")
				{
					system("CLS");
					break;
				}
			}
		}
	}
	else
	{
		cout << "Filename Does Not Exist";
		for (int i=5; i>0; i--)
		{
			cout << ".";
			sleep (1);
		}
		
		system ("CLS");
		coe_display();
		cout << "Create a new file(y/n)?" << endl;
		getline(cin,choice);
		
		if (choice == "Y" || choice == "y")
		{
		
			ofstream examinations("Exams.txt", ios::app);
				
			system ("CLS");
			
			while (true && count < 25)
			{
				system("CLS");
				coe_display();
				cout << "Exam ID: ";
				getline(cin, ID);
				examinations << ID << endl;
				
				cout << "Instructor: ";
				getline (cin, Instructor_ID);
				examinations << Instructor_ID << endl;
				
				cout << "Total Strength Of Course: ";
				getline(cin, strength);
				examinations << strength << endl;
				 
				cout << "Do you want to enter more(y/n)" << endl;
				getline(cin, choice);
				if (choice == "N" || choice == "n")
				{
					system("CLS");
					break;
				}
			}
		}
	}
}

void exams_schedule()
{
	string ID, Instructor_ID, hall, date, day, time, subject, section, choice;
	int count; 
	
	ifstream schedule("Schedule.txt");
	
	if (!schedule.is_open())
	{
		system ("CLS");
		coe_display();
		cout << "No Schedule Created." << endl;
		cout << "Create Schedule(y/n)?" << endl;
		getline(cin, choice);
		if (choice == "Y" || choice == "y")
		{
			system("CLS");
			coe_display();
			ofstream Schedule_in("Schedule.txt", ios::app);
			while (true && count < 25)
			{
				system("CLS");
				coe_display();
				cout << "ID: ";
				getline(cin, ID);
				Schedule_in << ID << endl;
				
				cout << "Instructor: ";
				getline(cin, Instructor_ID);
				Schedule_in << Instructor_ID << endl;
				
				cout << "Hall: ";
				getline(cin, hall);
				Schedule_in << hall << endl;
				
				cout << "Date: ";
				getline(cin, date); 
				Schedule_in << date << endl;
				
				cout << "Day: ";
				getline(cin, day);
				Schedule_in << day << endl;
				
				cout << "Time: ";
				getline(cin, time);
				Schedule_in << time << endl;
				
				cout << "Section: " << endl;
				getline(cin, section);
				Schedule_in << section << endl;
				if (count == 24)
				{
					system("CLS");
					cout << "Maximum Limit Reached." << endl;
				}
				
				cout << "Do you want to enter more(y/n)?";
				getline(cin, choice);
				if (choice == "N" || choice == "n")
				{
					break;
				}
			}
			
			Schedule_in.close();
		}
	}
	else
	{
		while (getline(schedule, ID), getline(schedule, Instructor_ID), getline(schedule, hall), getline(schedule, subject), getline(schedule, date), getline(schedule, day), getline(schedule, time), getline(schedule, section))
		{
			count++;
		}
		
		schedule.close();
		
		ofstream Schedule_in("Schedule.txt", ios::app);
		while (true && count < 25)
			{
				system("CLS");
				coe_display();
				cout << "ID: ";
				getline(cin, ID);
				Schedule_in << ID << endl;
				
				cout << "Instructor: ";
				getline(cin, Instructor_ID);
				Schedule_in << Instructor_ID << endl;
				
				cout << "Hall: ";
				getline(cin, hall);
				Schedule_in << hall << endl;
				
				cout << "Date: ";
				getline(cin, date); 
				Schedule_in << date << endl;
				
				cout << "Day: ";
				getline(cin, day);
				Schedule_in << day << endl;
				
				cout << "Time: ";
				getline(cin, time);
				Schedule_in << time << endl;
				
				cout << "Section: " << endl;
				getline(cin, section);
				Schedule_in << section << endl;
				if (count == 24)
				{
					system("CLS");
					cout << "Maximum Limit Reached." << endl;
				}
				
				cout << "Do you want to enter more(y/n)?";
				getline(cin, choice);
				if (choice == "N" || choice == "n")
				{
					break;
				}
			}
		
		if (count == 24)
		{
			system("CLS");
			coe_display();
			cout << "Maximum Limit Reached." << endl;
		}
		Schedule_in.close();
	}
}

void new_message_COE ()
{
	string message, name, date, time, choice;
	int i;
	
	while (i==0)
	{
		ofstream messages("New_Messages_COE.txt", ios::app);
		
		while (true)
		{
			system("CLS");
			coe_display();
			cout << "Message(Keep in a single line): ";
			getline(cin, message);
			messages << message << endl;
			cout << "Name: ";
			getline(cin, name);
			messages << name << endl;
			cout << "Date: ";
			getline(cin, date);
			messages << date << endl;
			cout << "Time: ";
			getline(cin, time); 
			messages << time << endl;
				
			cout << "Do You Want To Enter More Messages(y/n)?" << endl;
			getline(cin, choice);
			
			if (choice == "N" || choice == "n")
			{
				system("CLS");
				messages.close();
				i++;
				break;
			}
		}
	}
}

void recieve_messages_COE ()
{
	string message, name, date, time, choice, name_check;
	int i,j;
	
	coe_display();
	ifstream messages ("New_Messages_Teacher.txt");
	
	if(!messages.is_open())
	{
		cout << "No new messages." << endl;
		sleep(3);
		system ("CLS");
		coe_display();
		cout << "Do you want to send a message(y/n)?" << endl;
		getline(cin, choice);
		if (choice == "Y" || choice == "y")
		{
			new_message_COE();
		}
	}
	else
	{
		do 
			{
				while (getline(messages, message), getline(messages, name), getline(messages, date), getline(messages, time))
				{
					i++;
				}
				
				messages.close();
				
				system("CLS");
				coe_display();
				
				cout << "You Have " << i << " New Messages!!!" << endl;
				sleep (2);
				
				system("CLS");
				coe_display();
				ifstream messages("New_Messages_Teacher.txt");
				
				cout << "Want to check all(y/n)?" << endl;
				getline(cin, choice);
				
				if (choice == "Y" || choice == "y")
				{
					system("CLS");
					coe_display();
					i = 0;
					while (getline(messages, message), getline(messages, name), getline(messages, date), getline(messages, time))
					{
						i++;
						cout << "Message No: " << i << endl << message << endl << "Sender: " << name << endl << "Date: " << date << endl << "Time: " << time << endl;
						sleep(2);
					}
					
					cout << "Do you want to reply(y/n)?" << endl;
					getline(cin, choice);
					if(choice == "Y" || choice == "y")
					{
						system("CLS");
						coe_display();
						new_message_COE();
					}
					messages.close();
					
					ofstream messages("New_Messages_Teacher.txt");
					
					messages << "" ;
					
					messages.close();
					
					j++;
				}
				else
				{
					system("CLS");
					coe_display();
					cout << "Enter Sender's Name: " << endl;
					getline(cin, name_check);
					ifstream messages("New_Messages_Teacher.txt");
					while (getline(messages, message), getline(messages, name), getline(messages, date), getline(messages, time))
					{
						if (name != name_check)
						{
							system("CLS");
							coe_display();
							cout << "No new messages." << endl;
							sleep(2);
							
							ofstream tempfile("Temp_File.txt", ios::app);
							tempfile << message << endl << name << endl << date << endl << time << endl;
							tempfile.close();
						}
						
						if (name == name_check)
						{
							system("CLS");
							coe_display();
							cout << "Message No: " << i << endl << message << endl << "Sender: " << name << endl << "Date: " << date << endl << "Time: " << time << endl; 
							sleep(2);
						}
					}
					
					cout << "Do you want to send a message(y/n)?" << endl;
					getline(cin, choice);
					if (choice == "Y" || choice == "y")
					{
						new_message_COE();
					}
					
					j++;
				}
				
			}while (j==0);
	}
	messages.close();
					
	remove("New_Messages_Teacher.txt");
	rename("Temp_File.txt", "New_Messages_Teacher.txt");
	
}

void update_password (string choice, string ID_, string paSSword)
{
	string Password, ID, password, change;
	int i;
	
	ifstream COE_update("COE_Credentials.txt");
	getline(COE_update, ID);
	getline(COE_update, Password);
	COE_update.close();
	
	system("CLS");
	coe_display();	
	cout << "Enter a New Password: " << endl;
	getline(cin, change);	
			
	ofstream update("COE_Credentials.txt");
	update << ID << endl << change << endl;
}

void new_message_teacher()
{
	string message, name, date, time, choice;
	int i; 
	
	while (i==0)
	{
		ofstream messages("New_Messages_Teacher.txt", ios::app);
		
		while (true)
		{
			system("CLS");
			teacher_display();
			cout << "Message (Must be in a single line.): ";
			getline(cin, message);
			messages << message << endl;
			
			cout << "Name: " << endl;
			getline(cin, name);
			messages << name << endl;
			
			cout << "Date: ";
			getline(cin, date);
			messages << date << endl;
			
			cout << "Time: ";
			getline(cin, time); 
			messages << time << endl;
				
			cout << "Do You Want To Enter More Messages(y/n)?" << endl;
			getline(cin, choice);
			
			if (choice == "N" || choice == "n")
			{
				messages.close();
				i++;
				break;
			}
		}
	}
}

void recieve_message_teacher()
{
	string message, name, date, time, choice, name_check;
	int i,j;
	
	ifstream messages ("New_Messages_COE.txt");
	ofstream tempfile("Temp_File.txt");
	
	if (!messages.is_open())
	{
		system("CLS");
		teacher_display();
		cout << "No new Messages." << endl;
		sleep(2);
		cout << "Do you want to send a message(y/n)?" << endl;
		getline(cin, choice);
		if (choice == "Y" || choice == "y")
		{
			new_message_COE();
		}
	}
	else
	{
		do
		{
			while (getline(messages, message), getline(messages, name), getline(messages, date), getline(messages, time))
				{
					i++;
				}
				
				messages.close();
				
				system("CLS");
				teacher_display();
				
				cout << "You Have " << i << " New Messages!!!" << endl;
				sleep(2);
				
				system("CLS");
				
				ifstream messages("New_Messages_COE.txt");
				teacher_display();
				cout << "Want to check all(y/n)?" << endl;
				getline(cin, choice);
				
				if (choice == "Y" || choice == "y")
				{
					i = 0;
					while (getline(messages, message), getline(messages, name), getline(messages, date), getline(messages, time))
					{
						i++;
						cout << "Message No: " << i << endl << message << endl << "Sender: " << name << endl << "Date: " << date << endl << "Time: " << time << endl;
					}
					
					cout << "Do you want to send a message(y/n)?" << endl;
					getline(cin, choice);
					if (choice == "Y" || choice == "y")
					{
						new_message_COE();
					}
					
					messages.close();
					
					ofstream messages("New_Messages_COE.txt");
					
					messages << "" ;
					
					messages.close();
					
					j++;
				}
				else
				{
					system ("CLS");
					teacher_display();
					cout << "Enter Name: " << endl;
					getline(cin, name_check);
					while (getline(messages, message), getline(messages, name), getline(messages, date), getline(messages, time))
					{
						if (name != name_check)
						{
							system("CLS");
							teacher_display();
							cout << "No new messages." << endl;
							sleep(2);
							tempfile << message << endl << name << endl << date << endl << time << endl;
							tempfile.close();
						}
						
						if (name == name_check)
						{
							system("CLS");
							teacher_display();
							cout << "Message No: " << i << endl << message << endl << "Sender: " << name << endl << "Date: " << date << endl << "Time: " << time << endl; 
							sleep(2);
							cout << "Do you want to send a message(y/n)?" << endl;
							getline(cin, choice);
							if (choice == "Y" || choice == "y")
							{
								new_message_COE();
							}
						}
						
						tempfile.close();
						messages.close();
						remove("New_Messages_COE.txt");
						rename("Temp_File.txt", "New_Messages_COE.txt");
						
					}
					
					cout << "Do you want to send a message(y/n)?" << endl;
					getline(cin, choice);
					if (choice == "Y" || choice == "y")
					{
						new_message_COE();
					}
					
					j++;
				}
			
		}while(j==0);
	}
	
}
	

void view_exams_teacher( string id, string pass )
{
	string ID, Instructor_ID, hall, date, day, time, section, ID_Check, choice;
	
	ifstream view("Schedule.txt");
	
	if (!view.is_open())
	{
		cout << "No Schedule Created." << endl;
		sleep(2);
		cout << "Message COE(y/n)?" << endl;
		getline(cin, choice);
		if (choice == "Y" || choice == "y")
		{
			new_message_teacher();
		}
	}
	while (getline(view, ID), getline(view, Instructor_ID), getline(view, hall), getline(view, date), getline(view, day), getline(view, time), getline(view, section))
	{
		if (id == Instructor_ID)
		{
			system("CLS");
			teacher_display();
			cout << endl << "ID: " << ID << endl << "Instructor: " << Instructor_ID << endl << "Hall: " << hall << endl << "Date: " << date << endl << "Day: " << day << endl << "Time: " << time << endl << "Section: " << section << endl;
			cout << "Want to Continue(y/n)?" << endl;
			getline(cin, choice);
			if (choice == "N" || choice == "n")
			{
				break;
			}
		}
		else
		{
			cout << "No Exams Scheduled for you." << endl;
			sleep(2);
			break;
		}
	}	
}

void view_exams_student ( string secti, string Id, string Password )
{
	string subject, Subject, section, choice, ID, Instructor_ID, hall, date, day, time;
	int j;
	
	ifstream schedule_out("Schedule.txt");
	
	if (!schedule_out.is_open())
	{
		cout << "Does Not Exist." << endl;
	}	
	else
	{
		do
		{
			schedule_out.close();
			
			system("CLS");
			student_display();
			
			cout << "Do you want to check all: ";
			getline(cin, choice);
			if (choice == "Y" || choice == "y")
			{
				system("CLS");
				student_display();
				ifstream scheduleview("Schedule.txt");
				while (getline(scheduleview, ID), getline(scheduleview, Instructor_ID), getline(scheduleview, hall), getline(scheduleview, date), getline(scheduleview, day), getline(scheduleview, time), getline(scheduleview, section))
				{
					if (secti == section)
					{
						cout << "ID: " << ID << endl << "Instructor: " << Instructor_ID << endl << "Hall: " << hall << endl << "Subject: " << subject << endl << "Date: " << date << endl << "Day: " << day << endl << "Time: " << time << endl << "Section: "  << section << endl;
						j++;
						sleep (4);
					}
				}
			}
			else
			{
				system ("CLS");
				student_display();
				cout << "Enter Subject: ";
				getline(cin, Subject);
				
				system ("CLS");
				student_display();
				ifstream schedule_out("Schedule.txt");
				while (getline(schedule_out, ID), getline(schedule_out, Instructor_ID), getline(schedule_out, hall), getline(schedule_out, subject), getline(schedule_out, date), getline(schedule_out, day), getline(schedule_out, time), getline(schedule_out, section))
				{
					if (Subject == subject)
					{
						cout << "ID: " << ID << endl << "Instructor: " << Instructor_ID << endl << "Hall: " << hall << endl << "Subject: " << subject << endl << "Date: " << date << endl << "Day: " << day << endl << "Time: " << time << endl << "Section: " << endl;
						sleep(4);
						j++;
						break;
					}
				}
			}
			
			cout << "Do you want to continue(y/n)?";
			getline(cin, choice);
			if (choice == "Y" || choice == "y")
			{
				system("CLS");
			}
			
		}while (j==0);
		
	}
}	
	
void register_for_exam( string stud )
{	
	string ID, Password, schuedule, Instructor_ID, hall, subject, date, day, time, section;
	ifstream register_(stud.c_str());
	
	if (!register_.is_open())
	{
		cout << "Enter ID: ";
		getline(cin, ID);
		cout << endl << "Enter Password: ";
		getline(cin, Password);
		ofstream registery("Unregistered_Students.txt");
		registery << ID << endl << Password << endl;
		cout << "You have been registered." << endl;
	}
	else
	{
		cout << "You have already been registered." << endl;
		ifstream show("Schedule.txt");
		
		while (getline(show, ID), getline(show, Instructor_ID), getline(show, hall), getline(show, subject), getline(show, date), getline(show, day), getline(show, time), getline(show, section))
		{
			if (stud == section)
			{
				 cout << endl << "ID: " << ID << "Instructor: " << endl << "Hall: " << endl << "Date: " << date << "Day: " << endl << "Time: " << time << endl << "Section: " << endl;
				 break;
			}
		}
	}
}

void update_password_student( string choice, string ID_, string paSSword )
{
		string ID, asswords, name, section, Section, subjects, Password, passwords;
		
		system ("CLS");
		student_display();
		
		ifstream student_update ("Student_Info.txt",ios::out);
		ofstream tempfile("TempFile.txt");
		
		system("CLS");
		student_display();
		
		cout << "Enter a new password: ";
		getline(cin, Password);
		
		while (getline(student_update, ID), getline(student_update, passwords), getline(student_update, name), getline(student_update, section), getline(student_update, subjects))
		{
			
			if (ID != ID_ && passwords != paSSword)
			{
				tempfile << ID << endl << passwords << endl << name << endl << section << endl << subjects << endl;
			}
			
			if (paSSword == passwords)
			{
				tempfile << ID << endl << Password << endl << name << endl << section << subjects << endl;
			}
			
		}
		student_update.close();
		tempfile.close();
		remove ("Student_Info.txt");
		rename ("TempFile.txt", "Student_Info.txt");
}

void display_become_coe ()
{	
	cout << "\t\t\t __   ___ __  __         ___            __   __   ___" << endl;
	cout << "\t\t\t|__) |__ /  `/  \\   |\\/| |__      /\\    /  ` /  \\ |__  "<< endl;
	cout << "\t\t\t|__) |___\\__,\\__/  |  | |___    /~~\\   \\__, \\__/ |___" << endl;
	cout << "\t\t********************************************************************" << endl;
}

void welcome ()
{
cout << "\t\t\t\t      ___       __   __        ___" << endl;
cout << "\t\t\t\t|  | |__  |    /  ` /  \\ |\\/| |__ " << endl;
cout << "\t\t\t\t|/\\| |___ |___ \\__, \\__/ |  | |___" << endl;
cout << "\t\t\t\t***********************************" << endl;
}

void login_display ()
{
cout << "\t\t\t\t\t      __   __"           << endl;
cout << "\t\t\t\t\t|    /  \\ / _` | |\\ |" << endl;
cout << "\t\t\t\t\t|___ \\__/ \\__> | | \\|" << endl;
cout << "\t\t\t\t       ************************" << endl;
                     
}

void coe_display()
{
cout << "\t\t\t\t\t __   __   ___" << endl; 
cout << "\t\t\t\t\t/  ` /  \\ |__ " << endl;
cout << "\t\t\t\t\t\\__, \\__/ |___" << endl;
cout << "\t\t\t\t\t**************" << endl;
}

void teacher_display()
{
cout << "\t\t\t\t___  ___       __        ___  __"  << endl;
cout << "\t\t\t\t |  |__   /\\  /  ` |__| |__  |__)"  << endl;
cout << "\t\t\t\t |  |___ /~~\\ \\__, |  | |___ |  \\" << endl;
cout << "\t\t\t\t**********************************" << endl;
}

void student_display()
{
cout << "\t\t\t\t __  ___       __   ___      ___" << endl;
cout << "\t\t\t\t/__`  |  |  | |  \\ |__  |\\ |  |"  << endl;
cout << "\t\t\t\t.__/  |  \\__/ |__/ |___ | \\|  |"  << endl;
cout << "\t\t\t\t*********************************" << endl;
}

void thank_you ()
{
cout << "\t\t\t\t___                             __" << endl;      
cout << "\t\t\t\t |  |__|  /\\  |\\ | |__/    \\ / /  \\ |  |" << endl; 
cout << "\t\t\t\t |  |  | /~~\\ | \\| |  \\     |  \\__/ \\__/" << endl;
cout << "\t\t\t\t****************************************" << endl;
}

void unregistered_student ()
{
	string name, faculty, subjects;
	
	system ("CLS");
	student_display();
	
	ofstream unreg("Unregistered.txt", ios::app);
	
	cout << "Name: ";
	getline(cin, name);
	unreg << name << endl;
		
	cout << "Faculty: ";
	getline(cin, faculty);
	unreg << faculty << endl;
		
	cout << "Subject (Press Space to enter more than one subject): ";
	getline(cin, subjects);
	unreg << subjects << endl;
	
	cout << "Your Registration is in Process." << endl;
	sleep(2);
}

void register_students_teacher(string secto)
{
	string ID, ID_Check, Password, Password_Check, name, name_check, Section, section, section_check, subjects, subjects_check, choice;
	int i, j, count;
	
	system("CLS");
	teacher_display();
	cout << "Your Section Is: " << secto << endl;
	cout << "Enter Section(.txt): " ;
	getline(cin, section);
	
	ifstream registered(section.c_str());
	ifstream info("Students_Info.txt");
	
	if (!registered.is_open())
	{
		cout << "You have not registered any students." << endl;
		sleep(2);
		system("CLS");
		teacher_display();
		cout << "Do you want to register students(y/n)?";
		getline(cin, choice);
		if(choice == "Y" || choice == "y")
		{
			system("CLS");
			teacher_display();
			
			cout << "Your Section is: " << secto << endl;
			cout << "Enter Section(.txt): ";
			getline(cin, section);
			ofstream regist(section.c_str(), ios::app);
			
			for (int i=0; i<50; i++)
			{
				system ("CLS");
				teacher_display();
				cout << "ID: ";
				getline(cin, ID);
				regist << ID << endl;
				
				cout << "Password: ";
				getline(cin, Password);
				regist << Password << endl;
				
				cout << "Name: ";
				getline(cin, name);
				regist << name << endl;
				
				cout << "Section: ";
				getline(cin, Section);
				regist << Section << endl;
				
				cout << "Subjects: ";
				getline(cin, subjects);
				regist << subjects << endl;
				
				cout << "Do you want to enter more (y/n)?" ;
				getline(cin, choice);
				if (choice == "N" || choice == "n")
				{
					i = 50;
					break;
				}
			}
		}
	}
	else
	{
		while (true)
		{
			getline(info, ID); getline(info, Password); getline(info, name); getline(info, Section); getline(info, subjects);
			getline(registered, ID_Check); getline(registered, Password_Check); getline(registered, name_check); getline(registered, section_check); getline(registered, subjects_check);
			
			if (Section == section_check && name != name_check)
			{
				i++;
			}
			else if (Section == section_check && name == name_check)
			{
				j++;
			}
		}
		
		cout << "You have " << i << " unregistered students and " << j << "registered students.";
		for (int k = 0; k<4; k++)
		{
			cout << ".";
			sleep(1);
		}
		
		system ("CLS");
		teacher_display();
		
		cout << "Do you want to register students(y/n): ";
		getline(cin, choice);
		if(choice == "Y" || choice == "y")
		{
			system("CLS");
			teacher_display();
			cout << "Your Section is: " << secto << endl;
			cout << "Enter Section(.txt): ";
			getline(cin, section);
			
			ifstream registeredd(section.c_str());
			
			while (getline(registeredd, ID), getline(registeredd, Password), getline(registeredd, name), getline(registeredd, Section), getline(registeredd, subjects))
			{
				count++;
			}
			
			ofstream registering(section.c_str(),ios::app);
			while(true && count < 50)
			{
				system ("CLS");
				teacher_display();
				cout << "ID: ";
				getline(cin, ID);
				registering << ID << endl;
				
				cout << "Password: ";
				getline(cin, Password);
				registering << Password << endl;
				
				cout << "Name: ";
				getline(cin, name);
				registering << name << endl;
				
				cout << "Section: ";
				getline(cin, Section);
				registering << Section << endl;
				
				cout << "Subjects: ";
				getline(cin, subjects);
				registering << subjects << endl;
				
				cout << "Do you want to enter more (y/n)?" ;
				getline(cin, choice);
				if (choice == "Y" || choice == "y")
				{
					break;
				}
			}
		}
	}
}
