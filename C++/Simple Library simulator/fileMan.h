#ifndef FileManipulator_H
#define FileManipulator_H
#include <iostream>

using namespace std;

class FileManipulator
{
    public:
        FileManipulator();

        void AddBook();
        void AddAuthor();
        void DeleteBook();
        void DeleteAuthor();

        string PrintBook(string,bool);
        string PrintAuthor(string,bool);

        void BookSorter(bool);
        void SortAuthor(bool);
        void EnterQuery();

        int MySearchBook(string,bool,string);
        int MySearchAuthor(string,bool,string);
        int getSize(string,string,string,string);

};

#endif // FileManipulator_H
