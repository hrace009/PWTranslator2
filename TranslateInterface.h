#ifndef TRANSLATEINTERFACE_H
#define TRANSLATEINTERFACE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <codecvt>
#include <unordered_map>
#include <windows.h>
#include <msclr/marshal_cppstd.h>

using namespace std;

class TranslateInterface
{
private:
    struct currentData
    {
        wstring x;
        wstring y;
        wstring width;
        wstring height;
        wstring nextString;
        wstring secondString;
    };
    vector<wstring> chinesLines;
    vector<wstring> russianLines;
    vector<wstring> outputLines;
    unordered_map<wstring, currentData> russianDatas;
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> convert;
    int globalIndex;
    vector<wstring> files;
    wstring path1;
    wstring path2;
    wstring out;

    void initFiles(wstring firstPath, wstring dir);
    void initFolders(wstring path2);
    void clear();
public:

    TranslateInterface(System::String^ firstPath, System::String^ secondPath, System::String^ outputPath);
    virtual ~TranslateInterface();
    bool isName(int index, wstring currentLine);
    bool isX(int index, wstring currentLine);
    bool isY(int index, wstring currentLine);
    bool isWidth(int index, wstring currentLine);
    bool isHeight(int index, wstring currentLine);
    bool isString(int index, wstring currentLine);
    bool isNextString(wstring currentLine);
    void initRussianData();
    void toOutput(wstring currentLine);
    void translateFile(wstring fileName);
    vector<wstring> getAllFiles();
};

#endif