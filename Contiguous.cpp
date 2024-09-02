#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

const int blockSize = 10;
// A block on the disk
struct DiskBlock
{
    std::string data;
    string filename;
    DiskBlock()
    {
        this->data = "";
        this->filename = "";
    }
};

// A file on the disk
struct File
{
    std::string filename;
    int blockIndex;
    int size;
};

class ContiguousFileSystem
{
public:
    ContiguousFileSystem(int diskSize, int blockSize)
    {
        int num = diskSize/blockSize;
        if(num*blockSize < diskSize) num++;
        for (int i = 0; i < num; ++i)
        {
            DiskBlock block;
            block.data.resize(blockSize);
            freeBlocks.push_back(0);
            disk.push_back(block);
        }
    }

    void createFile(std::string filename, int size)
    {
        int max_count = 0;
        int count = 0;
        int blockIndex = 0;
        int prv_index = 0;
        for (int i = 0; i < freeBlocks.size(); i++)
        {
            if (freeBlocks[i] == 0)
            {
                prv_index = i;
                while(i < freeBlocks.size() && freeBlocks[i] == 0)
                {
                    count++;
                    i++;
                }
                if(max_count < count)
                {
                    max_count = count;
                    blockIndex = prv_index;
                }
                count = 0;
            }
        }
        int num = size/blockSize;
        if(num*blockSize < size) num++;
        if (max_count < num)
        {
            fail_to_add.push_back(filename);
            return;
        }
        vector<std::string>::iterator ptr = std::find(fail_to_add.begin() , fail_to_add.end() , filename);
        if(ptr != fail_to_add.end())
        fail_to_add.erase(ptr);

        int  ind = blockIndex;
        while (num--)
            freeBlocks[ind++] = 1;

        File file;
        file.filename = filename;
        file.blockIndex = blockIndex;
        file.size = size;

        for (int j = 0, i = 0; j < size; ++j, ++i)
        {
            disk[blockIndex].data.push_back(' ');
            if (i >= blockSize)
            {
                blockIndex++;
                disk[blockIndex].filename = filename;
                i = 0;
            }
        }

        files.push_back(file);
    }

    void writeFile(std::string filename, std::string data)
    {
        for (int i = 0; i < files.size(); ++i)
        {
            if (files[i].filename == filename)
            {
                int blockIndex = files[i].blockIndex;
                disk[blockIndex].filename = filename;
                if (data.size() > files[i].size)
                {
                    std::cerr << "Write exceeds file size" << std::endl;
                    return;
                }

                for (int j = 0, k = 0; j < files[i].size; ++j, ++k)
                {
                    if (k >= blockSize)
                    {
                        blockIndex++;
                        disk[blockIndex].filename = filename;
                        k = 0;
                    }
                    disk[blockIndex].data[k] = data[j];
                }

                return;
            }
        }

       
    }

    std::string readFile(std::string filename)
    {
        for (int i = 0; i < files.size(); ++i)
        {
            if (files[i].filename == filename)
            {
                std::string fileData;
                int blockIndex = files[i].blockIndex;
                for (int j = 0, i = 0; j < files[i].size; ++j, ++i)
                {
                    fileData += disk[blockIndex].data[i];
                    if (j >= blockSize)
                    {
                        blockIndex++;
                        i = 0;
                    }
                }

                return fileData;
            }
        }

       
        return "";
    }
    void Print()
    {
        cout<<endl<<"-----------------------------Contiguous Allocation-----------------------------"<<endl<<endl;
        cout <<endl<<endl<< "Total number of blocks : " << disk.size() << endl;

        int free_block_count = 0;
        for (auto &it : freeBlocks)
            if (it == 0)
                free_block_count++;

        cout << "Number of Free Blocks : " << free_block_count << endl
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
        cout<<endl<<"Files which are failed to be added :- "<<endl;
        for(auto &it : fail_to_add)
        cout<<"                 "<<it<<endl;

    }
    // Deletes the file with the specified filename
    void deleteFile(std::string filename)
    {
        for (int i = 0; i < files.size(); ++i)
        {
            if (files[i].filename == filename)
            {
                int blockIndex = files[i].blockIndex;
                int numBlocks = files[i].size/blockSize;
                if(numBlocks*blockSize < files[i].size) numBlocks++;


                for (int j = blockIndex , i = 0; i < numBlocks; ++j , ++i)
                {
                    freeBlocks[j] = 0;
                }

                files.erase(files.begin() + i);
            }
        }
        for (int j = 0; j < disk.size(); j++)
        {
            if (disk[j].filename == filename)
            {
                disk[j] = DiskBlock();
                return;
            }
        }

        std::cerr << "File : " << filename << " not found for deletion" << std::endl;
    }

private:
    std::vector<DiskBlock> disk;
    std::vector<int> freeBlocks;
    std::vector<File> files;
    std::vector<string> fail_to_add;
};
