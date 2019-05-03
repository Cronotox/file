#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <process.h>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct student
{
	char Name[20];
	int ID;
	int Grade;
public:
	void getdata()
	{
		cout << "Enter the name of the student:";
		cin >> Name;
		cout << "Enter the ID of the student:";
		cin >> ID;
		cout << "Enter the grade of the student:";
		cin >> Grade;
	}
	void putdata()
	{
		cout << "\nName:" << Name << endl;
		cout << "ID:" << ID;
		cout << "\tGrade:" << endl << Grade;
	}
	int getrno()
	{
		return ID;
	}
};

void insert()
{
	student insert;
	ofstream f("file2.dat", ios::binary | ios::app);
	if (!f)
	{
		cout << "file didn't open";
	
		return;
	}
	insert.getdata();
	f.write((char*)&insert, sizeof(insert));
	f.close();
}

void Delete()
{
	ifstream f1("file2.dat", ios::binary);
	ofstream f2("temp.dat", ios::binary);
	student del;
	int rollno;
	f1.seekg(0);
	cout << "Enter the roll no of the record whose record to be deleted:";
	cin >> rollno;
	char record = 'n';
	while (!f1.eof())
	{
		f1.read((char*)&del, sizeof(del));
		if (del.getrno() != rollno)
			f2.write((char*)&del, sizeof(del));
		else
			record = 'y';
	}
	if (record == 'n')
		cout << "Record does not exist";
	else
		cout << "Record with roll number " << rollno << " has been deleted";
	f1.close();
	f2.close();
	remove("file2.dat");
	rename("temp.dat", "file2.dat");
}

void display()
{
	student disp;
	ifstream f("file2.dat", ios::binary);
	while (f.read((char*)&disp, sizeof(disp)))
	{
		disp.putdata();
	}
}

void Sort()
{
	fstream f1("file2.dat", ios::binary | ios::ate | ios::in | ios::out);
	
	student obj1, obj2;
	long size = f1.tellg() / sizeof(student);

	for (int i = 0; i < size - 1; ++i)
	{

		for (int j = i + 1; j < size - 1 - i; ++j)
		{
			f1.read((char*)&obj1, sizeof(obj1));
			f1.read((char*)&obj2, sizeof(obj2));
			if (obj1.getrno() > obj2.getrno())
			{
				f1.seekp(-48, ios::cur);
				f1.write((char*)&obj2, sizeof(obj2));
				f1.write((char*)&obj1, sizeof(obj1));
				f1.seekp(-24, ios::cur);
			}
		}
	}
	f1.close();
}

void Wipe()
{
	ofstream f1;
	char x;

	cout << "!Warning: if you proceed, all data from this file will be deleted, continue? (y/n)" << endl;
	cin >> x;

	if (x == 'y') {
		f1.open("file2.dat", ios::binary | ios::out | ios::trunc);

	}
	


	f1.close();
}

void Check()
{
	ifstream f1("file2.dat", ios::binary);

	if (f1.fail()) {

		cout << "binary file cannot be found\n" << endl;
	}


	if (f1.good()) {

		cout << "binary file found\n" << endl;
	}


}

void Search()
{
	student a;
	fstream f1;
	int n;

	cout << "what ID would you like to search in the file?" << endl;
	cin >> n;

	f1.open("file2.dat", ios::binary | ios::in  );
	while (f1.read((char*)&a, sizeof(a))) {

		if (a.getrno() == n) {
			a.putdata();
		}
	}
	f1.close();
	
}

void Modify()
{
	fstream f1;
	student b;
	int X = 0;
	int N;

	cout << "type in ID of existent ";
	cin >> N;
	f1.open("file2.dat", ios::in | ios::out);
	while (f1.read((char*)&b, sizeof(b)) && X == 0) {

		if (b.getrno() == N) {
			
			b.putdata();
			cout << "\nEnter the new record data" << endl;
			b.getdata();
			int pos =-1* static_cast<int>(sizeof(b));
			f1.seekp(pos, ios::cur);
			f1.write((char*)&b, sizeof(b));
			X = 1;
		}
	}
	f1.close();
}

void Create()
{
	char filename[50];
	cout << " what name would you like to give the file? (make sure to end with .txt)" << endl;
	cin >> filename;

	ofstream f1(filename, ios::binary | ios::ate | ios::in | ios::out);
	f1.open(filename, ios::binary);
	f1.close();

	
}

int main()
{
	system("CLS");


	int choice1 = 0;
	
	char choice2 = 'y';
	do
	{
		cout << "\n1.Insert a record";
		cout << "\t2.Display a record";
		cout << "\n3.Delete a record";
		cout << "\n4.Sort the file";
		cout << "\n5.Create a file";
		cout << "\n6.Check if file exist";
		cout << "\n7.Wipe content of the file";
		cout << "\n8.Search for a file";
		cout << "\t9.Modify an existent record";
		cout << "\t\t10.Exit\n";
		cout << "Enter the choice:";
		cin >> choice1;
		switch (choice1)
		{
		case 1: insert();  break;
		case 2: display(); break;
		case 3: Delete();  break;
		case 4: Sort();    break;
		case 5: Create();  break;
		case 6: Check();   break;
		case 7: Wipe();	   break;
		case 8: Search();  break;
		case 9: Modify();  break;
		case 10: exit(0);   break;
		default: cout << "\nWrong choice entered";
		}
		cout << "\nFurther file handling(y/n):";
		cin >> choice2;
	} while (choice2 == 'y');
	
}