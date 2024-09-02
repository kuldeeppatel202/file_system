#include <bits/stdc++.h>
using namespace std;

struct indxed_Block
{
    std::string data;
    string filename;
    indxed_Block(const std::string &data) 
        : data(data) {}
};

struct IndexedFile
{
    std::string filename;
    int size;
    std::vector<int> indexBlock;

    IndexedFile(std::string filename, std::vector<int> indexBlock , int size)
        : filename(filename), indexBlock(indexBlock) ,size(size){}
};

class IndexedFileSystem
{
public:
    IndexedFileSystem(int diskSize, int blockSize)
        : diskSize(diskSize), blockSize(blockSize)
    {
        // initialize the free block list
        for (int i = 0; i < diskSize / blockSize; ++i)
        {
            freeBlocks.push_back(i);
            disk.push_back(indxed_Block(""));
        }
       
    }

    // create a new file with indexed allocation
    void createFile(std::string filename, int size)
    {
        int num = size/blockSize;
        if(num*blockSize < size) num++;
        if (freeBlocks.size() < num)
        {
            fail_to_add.push_back(filename);
            return;
        }
        vector<std::string>::iterator ptr = std::find(fail_to_add.begin() , fail_to_add.end() , filename);
        if(ptr != fail_to_add.end())
        fail_to_add.erase(ptr);

        vector<int> indexblock;
        while(num--)
        {
            indexblock.push_back(freeBlocks.front());
            freeBlocks.pop_front();
        }
        files.push_back(IndexedFile(filename , indexblock , size));

    }

    // read data from a file
    std::string readFile(std::string filename)
    {
        for (const auto &file : files)
        {
            if (file.filename == filename)
            {
                string data ;
                int  j = 0 , k = 0;
                for(int i = 0 ; i < file.size ; i++ , k++)
                {
                    if(k >= blockSize)
                    {
                        j++;
                        k = 0;
                    }
                    
                    data += disk[file.indexBlock[j]].data[k];
                }
                
                return data;
            }
        }

        
        return "";
    }

    void writeFile(std::string filename,string data)
    {
        bool flag = 1;
        for (const auto &file : files)
        {
            if (file.filename == filename)
            {
                int  j = 0 , k = 0;
                for(int i = 0 ; i < data.size() ; i++ , k++)
                {
                    disk[file.indexBlock[j]].filename = filename;
                    if(k >= blockSize)
                    {
                        
                        j++;
                        k = 0;
                    }
                     
                     disk[file.indexBlock[j]].data[k] = data[i];
                }
                flag = 0;
            }
        }
        
        
    }

    void deleteFile(std::string filename)
    {
        int blockIndex = -1 , i = 0;
        for (; i < files.size(); ++i)
        {
            if (files[i].filename == filename)
            {
                vector<int> index = files[i].indexBlock;
                files.erase(files.begin() + i);
                for(auto &it : index)
                {
                    freeBlocks.push_back(it);
                }
               
               for(int i = 0 ; i < index.size() ; i++)
               {
                disk[index[i]].filename = "";
               }  
                return;             
            }
        }
        if(i == files.size())
        {
            std::cerr << "File not found  for deletion " << std::endl;
            return;
        }
        
    }

    void Print()
    {
        cout<<endl<<"-----------------------------Indexed Allocation-----------------------------"<<endl<<endl;
        cout << "Total number of blocks : " << disk.size() << endl;

        cout << "Number of Free Blocks : " << freeBlocks.size() << endl
             << endl;
        cout << "-------------------------------------------------------------------------------------" << endl;
        cout << "|         Sno         |"
             << "         BlockNumber         |"
             << "         File Name         |" << endl;
        cout << "-------------------------------------------------------------------------------------" << endl;
        int i = 0;
        for (auto &it : disk)
        {
            cout << "         " << i << "                        " << i++ << "                            " << it.filename << endl;
        }

        cout<<endl<<endl<<"Index List : "<<endl;
        for(auto &it : files)
        {
            cout<<"                 "<<it.filename<<" : ";
            for(auto &jt : it.indexBlock)
            cout<<jt<<" ";
            cout<<endl;
        }
        cout<<endl<<"Files which are failed to be added :- "<<endl;
        for(auto &it : fail_to_add)
        cout<<"                 "<<it<<endl;
    }

private:
    int diskSize;
    int blockSize;
    int indexBlockSize;
    std::list<int> freeBlocks;
    std::vector<IndexedFile> files;
    std::vector<indxed_Block> disk;
    std::vector<string> fail_to_add;
};