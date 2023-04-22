#include <iostream>
#include <windows.h>

int main()
{
    WIN32_FIND_DATA findData;
    HANDLE hFind;
    std::string path = "C:\\Exam\\*"; // ����C�̸�Ŀ¼�µ������ļ���
    hFind = FindFirstFile(path.c_str(), &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cout << "�޷���C��" << std::endl;
        return 1;
    }
    do {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) { // ������ļ���
            std::string folderName = findData.cFileName;
            if (folderName >= "202283720000" && folderName <= "202283720036") { // �ж��Ƿ���ָ����Χ��
                std::cout << folderName << " ����" << std::endl;
            }
        }
    } while (FindNextFile(hFind, &findData));
    FindClose(hFind);
    return 0;
}

