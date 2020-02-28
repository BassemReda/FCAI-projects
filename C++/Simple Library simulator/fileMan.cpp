#include "FileManipulator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

fstream BookData("BookData.txt",ios::out | ios::in | ios::app );
fstream BookPK("BookPK.txt",ios::out | ios::in | ios::app );
fstream BookSK("BookSK.txt",ios::out | ios::in | ios::app );
fstream AuthorData("AuthorData.txt",ios::out | ios::in | ios::app );
fstream AuthorPK("AuthorPK.txt",ios::out | ios::in | ios::app );
fstream AuthorSK("AuthorSK.txt",ios::out | ios::in | ios::app );


vector<int>bookprimary;
vector<int>booksecondary;
vector<int>bookIdx;
vector<int>bookSecIdx;

vector<int>authorprimary;
vector<int>authorindex;
vector<int>authorsecondaryindex;
vector<string>authorsecondary;


struct Book
{
    string Book_ID,Author_ID,Book_Title,Book_Price;
};

struct Booklabellist
{
    string PK;
    int mynext;
};

vector<Booklabellist>secondary;

struct Authorlabellist
{
    string PK;
    int mynext;
};

vector<Authorlabellist>Autsecondary;

struct Author
{
    string Author_ID,Author_Name,Author_Address,Author_Mobile;
};

FileManipulator::FileManipulator()
{
    //ctor
}


void FileManipulator::AddBook()
{
    if ( !BookPK.is_open() ){
        BookPK.open("BookPK.txt",ios::out | ios::in | ios::app);
    }
    if ( !BookSK.is_open() )
        BookSK.open("BookSK.txt",ios::out | ios::in | ios::app);
    if ( !BookData.is_open() )
        BookData.open("BookData.txt",ios::out | ios::in | ios::app);

    string BookID,AuthorID,BookTitle,price;
    cout<<"Book ID: ";cin>>BookID;
    cout<<"Author ID: ";cin>>AuthorID;
    cout<<"Book Title: ";cin>>BookTitle;
    cout<<"Book Price: ";cin>>price;
    Book obj;
    obj.Author_ID=AuthorID;
    obj.Book_ID=BookID;
    obj.Book_Title=BookTitle;
    obj.Book_Price=price;
    int objsize=getSize(AuthorID,BookID,BookTitle,price);
    int pos=BookData.tellp();
    BookData<<objsize+3<<" "<<obj.Book_ID<<"|"<<obj.Author_ID<<"|"
                          <<obj.Book_Title<<"|"<<obj.Book_Price<<" ";
    int numb=atoi(BookID.c_str());
    bookprimary.push_back(numb);
    bookIdx.push_back(pos);
    BookSorter(1);

    BookSK.seekg(0,ios::beg);
    int msa=MySearchBook(AuthorID,0,"no");
    if ( msa == -1 ){
        Booklabellist temp;
        temp.PK=BookID;
        temp.mynext=-1;
        secondary.push_back(temp);
        int numb2=atoi(obj.Author_ID.c_str());
        booksecondary.push_back(numb2);
        bookSecIdx.push_back(secondary.size()-1);
        BookSK.clear();
        BookSorter(0);
    }
    else{
        Booklabellist temp;
        temp.PK=BookID;
        temp.mynext=-1;
        secondary.push_back(temp);
        while ( secondary[msa].mynext != -1 ){
            msa=secondary[msa].mynext;
        }
        secondary[msa].mynext=secondary.size()-1;
    }
}

void FileManipulator::AddAuthor()
{
    if ( !AuthorPK.is_open() ){
        AuthorPK.open("AuthorPK.txt",ios::out | ios::in | ios::app);
    }
    if ( !AuthorSK.is_open() ){
        AuthorSK.open("AuthorSK.txt",ios::out | ios::in | ios::app);
    }
    if ( !AuthorData.is_open() ){
        AuthorData.open("AuthorData.txt",ios::out | ios::in | ios::app);
    }
    string AuthorID,AuthorName,AuthorAddress,AuthorMobile;
    cout<<"Author ID: ";cin>>AuthorID;
    cout<<"Author Name: ";cin>>AuthorName;
    cout<<"Author Address: ";cin>>AuthorAddress;
    cout<<"Author Mobile: ";cin>>AuthorMobile;
    Author obj;
    obj.Author_ID=AuthorID;
    obj.Author_Name=AuthorName;
    obj.Author_Address=AuthorAddress;
    obj.Author_Mobile=AuthorMobile;
    int objsize=getSize(AuthorID,AuthorName,AuthorAddress,AuthorMobile);
    int pos=AuthorData.tellp();
    AuthorData<<objsize+3<<" "<<obj.Author_ID<<"|"<<obj.Author_Name<<"|"
                    <<obj.Author_Address<<"|"<<obj.Author_Mobile<<" ";
    AuthorPK<<obj.Author_ID<<" "<<pos<<" ";
    int numb=atoi(AuthorID.c_str());
    authorprimary.push_back(numb);
    authorindex.push_back(pos);
    SortAuthor(1);//sort PK file

    AuthorSK.seekg(0,ios::beg);
    int msa=MySearchAuthor(AuthorName,0,"no");
    if ( msa == -1 ){
        Authorlabellist temp;
        temp.PK=AuthorID;
        temp.mynext=-1;
        Autsecondary.push_back(temp);
        authorsecondary.push_back(AuthorName);
        authorsecondaryindex.push_back(Autsecondary.size()-1);
        AuthorSK.clear();
        SortAuthor(0);//sort SK file
    }
    else{
        Authorlabellist temp;
        temp.PK=AuthorID;
        temp.mynext=-1;
        Autsecondary.push_back(temp);
        while ( Autsecondary[msa].mynext != -1 ){
            msa=Autsecondary[msa].mynext;
        }
        Autsecondary[msa].mynext=Autsecondary.size()-1;
    }
}

void FileManipulator::DeleteBook()
{
    string ID;
    cout<<"Delete ID: ";
    cin>>ID;
    int msa=MySearchBook(ID,1,"yes");
    if ( msa != -1 ){
        BookData.close();
        BookData.open("BookData.txt",ios::out | ios::in);
        BookData.seekp(msa+2,ios::beg);
        BookData<<'*';
        BookData.close();
    }
    else{
        cout<<"Book Not Found"<<endl;
    }
    BookSorter(1);
    BookSorter(0);
}

void FileManipulator::DeleteAuthor()
{
    string ID;
    cout<<"Delete ID ";
    cin>>ID;
    int msa=MySearchAuthor(ID,1,"yes");
    if ( msa != -1 ){
        AuthorData.close();
        AuthorData.open("AuthorData.txt",ios::out | ios::in);
        AuthorData.seekp(msa+2,ios::beg);
        AuthorData<<'*';
        AuthorData.close();
    }
    else{
        cout<<"Author Not Found"<<endl;
    }
    SortAuthor(1);
    SortAuthor(0);
}

string FileManipulator::PrintBook(string id,bool flag)
{
    if ( !BookData.is_open() )
        BookData.open("BookData.txt",ios::out | ios::in | ios::app);

    int msa=MySearchBook(id,flag,"no");
    if ( flag ){
        if ( msa == -1 ){
            cout<<"Invalid ID"<<endl;
            return "";
        }
        BookData.clear();
        BookData.seekg(msa+2,ios::beg);
        string x;
        BookData>>x;
        if ( x[0] == '*' || x[1] == '*' ){
            cout<<"This Record Is Deleted"<<endl;
            return "";
        }
        return x;
    }
    else{
        if ( msa == -1 ){
            cout<<"Invalid ID"<<endl;
            return "";
        }
        msa=MySearchBook(secondary[msa].PK,1,"no");
        BookData.clear();
        BookData.seekg(msa+3,ios::beg);
        string x;
        BookData>>x;
        if ( x[0] == '*' || x[1] == '*' ){
            cout<<"This Record Is Deleted"<<endl;
            return "";
        }
        return x;
    }
}

string FileManipulator::PrintAuthor(string id,bool flag)
{
    if ( !AuthorData.is_open() ){
        AuthorData.open("AuthorData.txt",ios::out | ios::in | ios::app);
    }
    int msa=MySearchAuthor(id,flag,"no");
    if ( flag ){
        if ( msa == -1 ){
            cout<<"Invalid ID"<<endl;
            return "";
        }
        AuthorData.clear();
        AuthorData.seekg(msa+2,ios::beg);
        string x;
        AuthorData>>x;
        if ( x[0] == '*' || x[1] == '*' ){
            cout<<"This Record Is Deleted"<<endl;
            return "";
        }
        return x;
    }
    else{
        if ( msa == -1 ){
            cout<<"Invalid ID"<<endl;
            return "";
        }
        msa=MySearchAuthor(Autsecondary[msa].PK,1,"no");
        AuthorData.clear();
        AuthorData.seekg(msa+3,ios::beg);
        string x;
        AuthorData>>x;
        if ( x[0] == '*' || x[1] == '*' ){
            cout<<"This Record Is Deleted"<<endl;
            return "";
        }
        return x;
    }
}



int FileManipulator::MySearchBook(string target,bool flag,string which)
{
    if ( !BookPK.is_open() || !BookSK.is_open() ){
        BookPK.open("BookPK.txt",ios::out | ios::in | ios::app);
        BookSK.open("BookSK.txt",ios::out | ios::in | ios::app);
    }

    int inttarget=atoi(target.c_str());
    if ( flag )
    {
        //binary search
        int low=0,high=bookprimary.size()-1;
        while ( low <= high )
        {
            int mid=low+(high-1)/2;
            if ( bookprimary[mid] == inttarget )
            {
                if ( which == "yes" ){
                    int temp=bookIdx[mid];
                    bookprimary.erase(bookprimary.begin()+mid);
                    bookIdx.erase(bookIdx.begin()+mid);
                    return temp;
                }
                return bookIdx[mid];
            }
            if ( bookprimary[mid] > inttarget ){
                high=mid-1;
            }
            else{
                low=mid+1;
            }
        }
        return -1;
    }
    else{
        int low=0,high=booksecondary.size()-1;
        while ( low <= high ){
            int mid=low+(high-1)/2;
            if ( booksecondary[mid] == inttarget ){
                if ( which == "yes" ){
                    int temp=bookSecIdx[mid];
                    booksecondary.erase(booksecondary.begin()+mid);
                    bookSecIdx.erase(bookSecIdx.begin()+mid);
                    return temp;
                }
                return bookSecIdx[mid];
            }
            if ( booksecondary[mid] > inttarget ){
                high=mid-1;
            }
            else{
                low=mid+1;
            }
        }
        return -1;
    }
}


int FileManipulator::getSize(string x,string y,string z,string w)
{
    int len=x.size()+y.size()+z.size()+w.size();
    return len;
}



int FileManipulator::MySearchAuthor(string target,bool flag,string which)
{
    if ( !AuthorPK.is_open() || !AuthorSK.is_open() ){
        AuthorPK.open("AuthorPK.txt",ios::out | ios::in | ios::app);
        AuthorSK.open("AuthorSK.txt",ios::out | ios::in | ios::app);
    }
    int inttarget=atoi(target.c_str());
    if ( flag ){
        int low=0,high=authorprimary.size()-1;
        while ( low <= high ){
            int mid=low+(high-1)/2;
            if ( authorprimary[mid] == inttarget ){
                if ( which == "yes" ){
                    int temp=authorindex[mid];
                    authorprimary.erase(authorprimary.begin()+mid);
                    authorindex.erase(authorindex.begin()+mid);
                    return temp;
                }
                return authorindex[mid];
            }
            if ( authorprimary[mid] > inttarget ){
                high=mid-1;
            }
            else{
                low=mid+1;
            }
        }
        return -1;
    }
    else{
        int low=0,high=authorsecondary.size()-1;
        while ( low <= high ){
            int mid=low+(high-1)/2;
            if ( authorsecondary[mid] == target ){
                if ( which == "yes" ){
                    int temp=authorsecondaryindex[mid];
                    authorsecondary.erase(authorsecondary.begin()+mid);
                    authorsecondaryindex.erase(authorsecondaryindex.begin()+mid);
                    return temp;
                }
                return authorsecondaryindex[mid];
            }
            if ( authorsecondary[mid] > target ){
                high=mid-1;
            }
            else{
                low=mid+1;
            }
        }
        return -1;
    }
}

void FileManipulator::BookSorter(bool flag)
{
    if ( flag )
    {
        for ( int i=0;i<bookprimary.size()-1;i++){
            for ( int j=0;j<bookprimary.size()-i-1;j++){
                if ( bookprimary[j] > bookprimary[j+1] ){
                    swap(bookprimary[j],bookprimary[j+1]);
                    swap(bookIdx[j],bookIdx[j+1]);
                }
            }
        }
        BookPK.close();
        BookPK.open("BookPK.txt",ios::out | ios::trunc);
        for ( int i=0;i<bookprimary.size();i++){
            BookPK<<bookprimary[i]<<" "<<bookIdx[i]<<" ";
        }
        BookPK.close();
    }
    else{
        for ( int i=0;i<booksecondary.size()-1;i++){
            for ( int j=0;j<booksecondary.size()-i-1;j++){
                if ( booksecondary[j] > booksecondary[j+1] ){
                    swap(booksecondary[j],booksecondary[j+1]);
                    swap(bookSecIdx[j],bookSecIdx[j+1]);
                }
            }
        }
        BookSK.close();
        BookSK.open("BookSK.txt",ios::out | ios::trunc);
        for ( int i=0;i<booksecondary.size();i++){
            BookSK<<booksecondary[i]<<" "<<bookSecIdx[i]<<" ";
        }
        BookSK.close();
    }
}

void FileManipulator::SortAuthor(bool flag)
{
    if ( flag )//PK file
    {
        for ( int i=0;i<authorprimary.size()-1;i++){
            for ( int j=0;j<authorprimary.size()-i-1;j++){
                if ( authorprimary[j] > authorprimary[j+1] ){
                    swap(authorprimary[j],authorprimary[j+1]);
                    swap(authorindex[j],authorindex[j+1]);
                }
            }
        }
        AuthorPK.close();
        AuthorPK.open("AuthorPK.txt",ios::out | ios::trunc);
        for ( int i=0;i<authorprimary.size();i++){
            AuthorPK<<authorprimary[i]<<" "<<authorindex[i]<<" ";
        }
        AuthorPK.close();
    }
    else //SK file
    {
        for ( int i=0;i<authorsecondary.size()-1;i++){
            for ( int j=0;j<authorsecondary.size()-i-1;j++){
                if ( authorsecondary[j] > authorsecondary[j+1] ){
                    swap(authorsecondary[j],authorsecondary[j+1]);
                    swap(authorsecondaryindex[j],authorsecondaryindex[j+1]);
                }
            }
        }
        AuthorSK.close();
        AuthorSK.open("AuthorSK.txt",ios::out | ios::trunc);
        for ( int i=0;i<authorsecondary.size();i++){
            AuthorSK<<authorsecondary[i]<<" "<<authorsecondaryindex[i]<<" ";
        }
        AuthorSK.close();
    }
}


void FileManipulator::EnterQuery()
{
    vector<string>query;
    cout<<"Query ";
    string x,y="";
    cin.ignore();
    getline(cin,x);
    for ( int i=0;i<x.size();i++){
        if ( x[i] == ' ' ){
            query.push_back(y);
            y="";
            continue;
        }
        y+=x[i];
    }
    if ( query[1] == "all" ){
        if ( query[3] == "books" ){
            if ( query.size() > 4 && query[4] == "where" ){
                cout<<PrintBook(query[7],(query[5]=="Book_ID"?1:0))<<endl;
            }
            else if ( query.size() > 4 && query[4] == "and" ){
                for ( int i=0;i<bookprimary.size();i++){
                    stringstream ss;
                    ss>>bookprimary[i];
                    string temp=ss.str();
                    cout<<PrintBook(temp,1)<<endl;
                }
                for ( int i=0;i<authorprimary.size();i++){
                    stringstream ss;
                    ss>>authorprimary[i];
                    string temp=ss.str();
                    cout<<PrintBook(temp,1)<<endl;
                }
            }
        }
        else{
            if ( query.size() > 4 && query[4] == "where" ){
                PrintAuthor(query[7],(query[5]=="Author_ID"?1:0));
            }
        }
    }
    else if ( query[1] == "Book_Title" ){
        if ( query[3] == "books" ){
            if ( query.size() > 4 && query[4] == "where" ){
                cout<<PrintBook(query[7],(query[5]=="Book_ID"?1:0))<<endl;
            }
            else if ( query.size() > 4 && query[4] == "and" ){
                for ( int i=0;i<bookprimary.size();i++){
                    stringstream ss;
                    ss>>bookprimary[i];
                    string temp=ss.str();
                    cout<<PrintBook(temp,1)<<endl;
                }
                for ( int i=0;i<authorprimary.size();i++){
                    stringstream ss;
                    ss>>authorprimary[i];
                    string temp=ss.str();
                    cout<<PrintBook(temp,1)<<endl;
                }
            }
        }
        else{
            if ( query.size() > 4 && query[4] == "where" ){
                PrintAuthor(query[7],(query[5]=="Author_ID"?1:0));
            }
        }
    }
}
