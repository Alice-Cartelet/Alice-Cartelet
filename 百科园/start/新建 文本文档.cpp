#include <iostream>
#include <windows.h>

int main()
{
    WIN32_FIND_DATA findData;
    HANDLE hFind;
    std::string path = "C:\\Exam\\*"; // 搜索C盘根目录下的所有文件夹
    hFind = FindFirstFile(path.c_str(), &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cout << "无法打开C盘" << std::endl;
        return 1;
    }
    do {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) { // 如果是文件夹
            std::string folderName = findData.cFileName;
            if (folderName >= "202283720000" && folderName <= "202283720036") { // 判断是否在指定范围内
                std::cout << folderName << " 存在" << std::endl;
            }
        }
    } while (FindNextFile(hFind, &findData));
    FindClose(hFind);
    return 0;
}

