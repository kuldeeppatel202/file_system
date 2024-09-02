#include <bits/stdc++.h>
using namespace std;

struct LinkedFile
{
    std::string filename;
    int startBlock;
    int size;
    LinkedFile(std::string filename, int startBlock , int size)
        : filename(filename), startBlock(startBlock)  , size(size){}
};

struct linked_Block
{
    std::string data;
    string filename;
    int nextBlock;

    // Block(const std::string &data, int nextBlock)
    //     : data(data), nextBlock(nextBlock) {}
};

class LinkedFileSystem
{
public:
    LinkedFileSystem(int diskSize, int blockSize)
        : diskSize(diskSize), blockSize(blockSize)
    {
        // initialize the free block list
        for (int i = 0; i < diskSize / blockSize; ++i)
        {
            freeBlocks.push_back(i);
        }
        int num = diskSize/blockSize;
        if(num*blockSize < diskSize) num++;
        disk.resize(num);
    }

    // create a new file with linked allocation
    void createFile(std::string filename, int size)
    {
        //cout<<freeBlocks.size()<<" "<<size/blockSize;
        int num = size/blockSize;
        if(num*blockSize < size) num++;
        if (freeBlocks.size() < num)
        {
           fail_to_add.push_back(filename);
            return;
        }
        vector<string>::iterator ptr = find(fail_to_add.begin() , fail_to_add.end() , filename);
        if(ptr != fail_to_add.end())
        fail_to_add.erase(ptr);

        int startBlock = freeBlocks.front();
        freeBlocks.pop_front();

        files.push_back(LinkedFile(filename, startBlock , size));

        int remainingBytes = size;
        int currentBlock = startBlock;
        while (remainingBytes > 0)
        {
            int i = blockSize;
            while(i-- && remainingBytes > 0)
            {
                disk[currentBlock].data.push_back(' ');
                remainingBytes--;
            }
            if(remainingBytes > 0)
            {
                disk[currentBlock].nextBlock = freeBlocks.front();
                currentBlock = freeBlocks.front();
                freeBlocks.pop_front();
            }
        }
        disk[currentBlock].nextBlock = -1;
    }

    // read data from a file
    std::string readFile(std::string filename)
    {
        for (const auto &file : files)
        {
            if (file.filename == filename)
            {
                int blockIndex = file.startBlock;
                int data_index = 0;
                int bytesRead = 0;
                std::string data;
                data.reserve(file.size);

                while (bytesRead < file.size)
                {
                    data += disk[blockIndex].data[data_index++];
                    if(data_index >= blockSize)
                    {
                        blockIndex = disk[blockIndex].nextBlock;
                        data_index = 0;
                    }
                    bytesRead++;
                }

                return data;
            }
        }

        
        return "";
    }

    void writeFile(string filename , string data)
    {
        for (int i = 0; i < files.size(); ++i)
        {
            if (files[i].filename == filename)
            {
                int blockIndex = files[i].startBlock;
                
                if (data.size() > files[i].size)
                {
                    std::cerr << "Write exceeds file size" << std::endl;
                    return;
                }
                for(int j = 0, k = 0; j < files[i].size; ++j, ++k)
                {
                    if (k >= blockSize)
                    {
                        blockIndex = disk[blockIndex].nextBlock;
                        k = 0;
                    }
                    disk[blockIndex].filename = filename;
                    disk[blockIndex].data[k] = data[j];
                }
                return;
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
                blockIndex = files[i].startBlock;
                files.erase(files.begin() + i);
                break;
            }
        }
        if(i == files.size()+1)
        {
             std::cerr << "File : "<<filename<<" not found" << std::endl;
            return;
        }
        while(blockIndex != -1)
        {
            freeBlocks.push_back(blockIndex);
            int temp = disk[blockIndex].nextBlock;
            disk[blockIndex].nextBlock = -1;
            disk[blockIndex].filename = ""; 
            blockIndex = temp;

        }

        
    }
    void Print()
    {
        cout<<endl<<"-----------------------------Linked Allocation-----------------------------"<<endl<<endl;
        cout <<endl<<endl<< "Total number of blocks : " << disk.size() << endl;

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

        cout<<endl<<endl<<"Linked List : "<<endl;
        for(auto &it : files)
        {
            int bi = it.startBlock;
            cout<<"                 "<<it.filename<<" ";
            while(bi != -1)
            {
                cout<<bi<<"-->";
                bi = disk[bi].nextBlock;
            }
            cout<<"/0"<<endl;
        }
        cout<<endl<<"Files which are failed to be added :- "<<endl;
        for(auto &it : fail_to_add)
        cout<<"                 "<<it<<endl;
        
    }
private:
    int diskSize;
    int blockSize;
    std::list<int> freeBlocks;
    std::vector<LinkedFile> files;
    std::vector<linked_Block> disk;
    std::vector<string> fail_to_add;
};