/*
	A library system simulator using C++ and text files as databases
*/
#include <iostream>
#include "FileManipulator.h"

using namespace std;

int main()
{
    FileManipulator obj;
    while ( 1 )
    {
        cout<<"1) Add New Book"<<endl
            <<"2) Add New Author"<<endl
            <<"3) Delete Book (ID)"<<endl
            <<"4) Delete Author (ID)"<<endl
            <<"5) Print Book(ID)"<<endl
            <<"6) Print Book(Author_ID)"<<endl
            <<"7) Print Author(ID)"<<endl
            <<"8) Print Author(name)"<<endl
            <<"9) Write a Query"<<endl
            <<"10) Exit"<<endl;
        int choice;
        cin>>choice;
        switch ( choice )
        {
        case 1:
            obj.AddBook();
            break;
        case 2:
            obj.AddAuthor();
            break;
        case 3:
            obj.DeleteBook();
            break;
        case 4:
            obj.DeleteAuthor();
            break;
        case 5:
            {
                cout<<"Enter Book ID that You Want to Print from Books: ";
                string id;
                cin>>id;
                cout<<obj.PrintBook(id,1)<<endl;
                break;
            }
        case 6:
            {
                cout<<"Enter Author ID that You Want to Print from Books: ";
                string id;
                cin>>id;
                cout<<obj.PrintBook(id,0)<<endl;
                break;
            }
        case 7:
            {
                cout<<"Enter Author ID that You Want to Print from Authors: ";
                string id;
                cin>>id;
                cout<<obj.PrintAuthor(id,1)<<endl;
                break;
            }
        case 8:
            {
                cout<<"Enter Author Name that You Want to Print from Authors: ";
                string id;
                cin>>id;
                cout<<obj.PrintAuthor(id,0)<<endl;
                break;
            }
        case 9:
            obj.EnterQuery();
            break;
        case 10:
            return 0;
        default:
            cout<<"Wrong Input"<<endl;
            break;
        }
    cout<<"----------------------------------------------------------------------------"<<endl;
    }
}
