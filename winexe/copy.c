#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

void CopyFileCMD()
{
    system("DiskPart /s .\\DiskAttach.txt");
    system("copy /y .\\Bootx64.efi G:\\efi\\boot\\");
    system("copy /y .\\Loader.efi G:\\efi\\boot\\");
    
    system("copy /y .\\TestR3.exe G:\\");
    system("DiskPart /s .\\DiskDetach.txt");
}

int main(int argc, char *argv[])
{
    CopyFileCMD();
    return 0;
}