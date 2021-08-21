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
#include <algorithm>

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
    vector<wstring> chinesLinesSTF;
    vector<wstring> russianLines;
    vector<wstring> russianLinesSTF;
    vector<wstring> outputLines;
    vector<wstring> outputLinesSTF;
    unordered_map<wstring, currentData> russianDatas;
    unordered_map<wstring, wstring> russianDatasSTF;
    unordered_map<wstring, wstring> chineDatasSTF;
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> convert;
    int globalIndex;
    vector<wstring> files;
    vector<wstring> filesSTF;
    wstring path1;
    wstring path2;
    wstring out;

    void initFiles(wstring firstPath, wstring dir);
    void initSTF(wstring firstPath);
    void initFolders(wstring path2);
    void clear();
    void clearSTF();

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
    vector<wstring> getAllFilesSTF();

    bool isQuote(int index, wstring currentLine);
    bool isNotNumber(int index, wstring currentLine);
    bool isNewLine(int index, wstring currentLine);
    bool isComment(int index, wstring currentLine);
    wstring toNormalID(wstring id);
    void initRussianDataSTF();
    void initChineDataSTF();
    void toOutputSTF();
    void translateFileSTF(wstring fileName);
};

#endif