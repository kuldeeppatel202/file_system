#include <bits/stdc++.h>
using namespace std;

struct modeified_Block
{
    std::string data;
    string filename;
    int nextBlock;

    modeified_Block(const std::string &data, int nextBlock)
        : data(data), nextBlock(nextBlock) {}
};

class ModifiedContiguousFileSystem
{
public:
    struct ModifiedContiguousFile
    {
        std::string filename;
        int initialBlock;
        std::vector<int> overflowBlocks;

        ModifiedContiguousFile(std::string filename, int initialBlock, vector<int> overflowBlocks)
            : filename(filename), initialBlock(initialBlock), overflowBlocks(overflowBlocks) {}
    };

    ModifiedContiguousFileSystem(int diskSize, int blockSize)
        : diskSize(diskSize), blockSize(blockSize)
    {
        for (int i = 0; i < diskSize / blockSize; ++i)
        {
            disk.push_back(modeified_Block("", -1));
            freeBlocks.push_back(i);
        }
    }

    // create a new file
    void createFile(std::string filename, int size)
    {
        int num = size / blockSize;
        if (num * blockSize < size)
            num++;
        if (freeBlocks.size() < num)
        {
            fail_to_add.push_back(filename);
            return;
        }
        vector<string>::iterator ptr = find(fail_to_add.begin(), fail_to_add.end(), filename);
        if (ptr != fail_to_add.end())
            fail_to_add.erase(ptr);

        vector<int> indexblock;

        while (num--)
        {
            indexblock.push_back(freeBlocks.front());
            freeBlocks.pop_front();
        }
        files.push_back(ModifiedContiguousFile(filename, size, indexblock));
    }

    // read data from a file
    std::string readFile(std::string filename)
    {
        for (auto &file : files)
        {
            if (file.filename == filename)
            {
                string data;
                int j = 0, k = 0;
                for (int i = 0; i < file.initialBlock; i++, k++)
                {
                    if (k >= blockSize)
                    {
                        j++;
                        k = 0;
                    }

                    data += disk[file.overflowBlocks[j]].data[k];
                }

                return data;
            }
        }

        return "";
    }

    // write data to a file
    // write data to a file
    void writeFile(std::string filename, std::string data)
    {
        bool flag = 1;
        for (const auto &file : files)
        {
            if (file.filename == filename)
            {
                int j = 0, k = 0;
                for (int i = 0; i < data.size(); i++, k++)
                {
                    if (k >= blockSize)
                    {
                        j++;
                        k = 0;
                    }
                    disk[file.overflowBlocks[j]].filename = filename;
                    disk[file.overflowBlocks[j]].data[k] = data[i];
                }
                flag = 0;
            }
        }
    }

    void deleteFile(std::string filename)
    {
        int blockIndex = -1, i = 0;
        for (; i < files.size(); ++i)
        {
            if (files[i].filename == filename)
            {
                vector<int> index = files[i].overflowBlocks;
                files.erase(files.begin() + i);
                for (auto &it : index)
                {
                    freeBlocks.push_back(it);
                }
                for (int i = 0; i < index.size(); i++)
                {
                    disk[index[i]].filename = "";
                }
                return;
                return;
            }
        }
        if (i == files.size())
        {
            std::cerr << "File not found  for deletion " << std::endl;
            return;
        }
    }

    void Print()
    {
        cout << endl
             << "-----------------------------Modified Allocation-----------------------------" << endl
             << endl;
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

        cout << endl
             << endl
             << "Index List : " << endl;
        for (auto &it : files)
        {
            cout << "                 " << it.filename << " : ";
            for (auto &jt : it.overflowBlocks)
                cout << jt << " ";
            cout << endl;
        }
        cout << endl
             << "Files which are failed to be added :- " << endl;
        for (auto &it : fail_to_add)
            cout << "                 " << it << endl;
    }

private:
    int diskSize;
    int blockSize;
    int indexBlockSize;
    std::list<int> freeBlocks;
    std::vector<ModifiedContiguousFile> files;
    std::vector<modeified_Block> disk;
    std::vector<string> fail_to_add;
};