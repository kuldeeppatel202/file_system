#include <bits/stdc++.h>
#include "Contiguous.cpp"
#include "linked.cpp"
#include "indexed.cpp"
#include "modified.cpp"
using namespace std;
struct input_file
{
    string filename;
    int size;
    string data;
};
int main()
{

    vector<input_file> file_list(10);
    for (auto &it : file_list)
    {
        cin >> it.filename;
        cin >> it.size;
        cin >> it.data;
    }
    ContiguousFileSystem Contiguous_File_System(100, 10);
    IndexedFileSystem Indexed_File_System(100, 10);
    LinkedFileSystem Linked_File_System(100, 10);
    ModifiedContiguousFileSystem Modified_Contiguous_File_System(100, 10);

    for (auto &it : file_list)
    {
        Contiguous_File_System.createFile(it.filename, it.size);
        // cout<<it.filename<<" created in contiguous file system"<<endl;

        Contiguous_File_System.writeFile(it.filename, it.data);
        // cout<<it.filename<<" writen in contiguous file system"<<endl;
        Modified_Contiguous_File_System.createFile(it.filename, it.size);
        // cout<<it.filename<<" created in modeified file system"<<endl;
        Modified_Contiguous_File_System.writeFile(it.filename, it.data);
        // cout<<it.filename<<" writen in modeified file system"<<endl;
        Indexed_File_System.createFile(it.filename, it.size);
        // cout<<it.filename<<" created in indexed file system"<<endl;
        Indexed_File_System.writeFile(it.filename, it.data);
        // cout<<it.filename<<" writen in indexed file system"<<endl;
        Linked_File_System.createFile(it.filename, it.size);
        // cout<<it.filename<<" created in linked file system"<<endl;
        Linked_File_System.writeFile(it.filename, it.data);
    }
    Contiguous_File_System.Print();
    Indexed_File_System.Print();
    Linked_File_System.Print();
    Modified_Contiguous_File_System.Print();

    Contiguous_File_System.deleteFile("Auxiliary.txt");
    Contiguous_File_System.deleteFile("pointed.txt");
    Contiguous_File_System.deleteFile("Program.txt");

    Linked_File_System.deleteFile("Auxiliary.txt");
    Linked_File_System.deleteFile("pointed.txt");
    Linked_File_System.deleteFile("Program.txt");

    Indexed_File_System.deleteFile("Auxiliary.txt");
    Indexed_File_System.deleteFile("pointed.txt");
    Indexed_File_System.deleteFile("Program.txt");

    Modified_Contiguous_File_System.deleteFile("Auxiliary.txt");
    Modified_Contiguous_File_System.deleteFile("pointed.txt");
    Modified_Contiguous_File_System.deleteFile("Program.txt");

    Contiguous_File_System.Print();
    Indexed_File_System.Print();
    Linked_File_System.Print();
    Modified_Contiguous_File_System.Print();

    Contiguous_File_System.createFile(file_list[9].filename, file_list[9].size);
    Contiguous_File_System.writeFile(file_list[9].filename, file_list[9].data);

    Indexed_File_System.createFile(file_list[9].filename, file_list[9].size);
    Indexed_File_System.writeFile(file_list[9].filename, file_list[9].data);

    Linked_File_System.createFile(file_list[9].filename, file_list[9].size);
    Linked_File_System.writeFile(file_list[9].filename, file_list[9].data);

    Modified_Contiguous_File_System.createFile(file_list[9].filename, file_list[9].size);
    Modified_Contiguous_File_System.writeFile(file_list[9].filename, file_list[9].data);

    Contiguous_File_System.Print();
    Indexed_File_System.Print();
    Linked_File_System.Print();
    Modified_Contiguous_File_System.Print();

    return 0;
}