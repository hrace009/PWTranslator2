#include "TranslateInterface.h"

void TranslateInterface::initFiles(wstring firstPath, wstring dir)
{
    WIN32_FIND_DATAW wfd;
    wstring path = firstPath + L"\\*.xml";
    HANDLE const hFind = FindFirstFileW(path.c_str(), &wfd);

    if (INVALID_HANDLE_VALUE != hFind)
    {
        do
        {
            files.push_back(dir + &wfd.cFileName[0]);
        } while (NULL != FindNextFileW(hFind, &wfd));

        FindClose(hFind);
    }
    wstring path1 = firstPath + L"\\*";
    HANDLE const hFind1 = FindFirstFileW(path1.c_str(), &wfd);
    if (INVALID_HANDLE_VALUE != hFind1)
    {
        do
        {
            if (wfd.cFileName[0] != L'.' && wfd.dwFileAttributes != FILE_ATTRIBUTE_REPARSE_POINT) {
                if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    initFiles(firstPath + L"\\" + &wfd.cFileName[0], dir + &wfd.cFileName[0] + L"\\");
                }
            }
        } while (NULL != FindNextFileW(hFind1, &wfd));

        FindClose(hFind1);
    }
}

void TranslateInterface::initFolders(wstring path2)
{
    wstring ani = path2 + L"\\ani";
    CreateDirectory(ani.c_str(), NULL);
    ani = path2 + L"\\commeratebook";
    CreateDirectory(ani.c_str(), NULL);
    ani = path2 + L"\\faces";
    CreateDirectory(ani.c_str(), NULL);
    ani = path2 + L"\\faces_new";
    CreateDirectory(ani.c_str(), NULL);
    ani = path2 + L"\\faces_new\\sliders";
    CreateDirectory(ani.c_str(), NULL);
    ani = path2 + L"\\script";
    CreateDirectory(ani.c_str(), NULL);
    ani = path2 + L"\\script\\config";
    CreateDirectory(ani.c_str(), NULL);
    ani = path2 + L"\\terrain";
    CreateDirectory(ani.c_str(), NULL);
    ani = path2 + L"\\version01";
    CreateDirectory(ani.c_str(), NULL);
    ani = path2 + L"\\version01\\faces";
    CreateDirectory(ani.c_str(), NULL);
    ani = path2 + L"\\version01\\wiki";
    CreateDirectory(ani.c_str(), NULL);
    ani = path2 + L"\\wiki";
    CreateDirectory(ani.c_str(), NULL);
}

void TranslateInterface::clear()
{
    chinesLines.clear();
    russianLines.clear();
    russianDatas.clear();
    outputLines.clear();
}

TranslateInterface::TranslateInterface(System::String^ firstPath, System::String^ secondPath, System::String^ outputPath)
{
    msclr::interop::marshal_context context;
    path1 = context.marshal_as<wstring>(firstPath);
    path2 = context.marshal_as<wstring>(secondPath);
    out = context.marshal_as<wstring>(outputPath);
    this->initFiles(path1, L"");
    this->initFolders(path2);
}

TranslateInterface::~TranslateInterface()
{
}

bool TranslateInterface::isName(int index, wstring currentLine)
{
    if (index + 6 > currentLine.size())
    {
        return false;
    }

    wstring cur = currentLine.substr(index, 6);
    wstring name = convert.from_bytes(" Name=");
    return cur == name;
}

bool TranslateInterface::isX(int index, wstring currentLine)
{
    if (index + 3 > currentLine.size())
    {
        return false;
    }

    wstring cur = currentLine.substr(index, 3);
    wstring x = convert.from_bytes(" x=");
    return cur == x;
}

bool TranslateInterface::isY(int index, wstring currentLine)
{
    if (index + 3 > currentLine.size())
    {
        return false;
    }

    wstring cur = currentLine.substr(index, 3);
    wstring y = convert.from_bytes(" y=");
    return cur == y;
}

bool TranslateInterface::isWidth(int index, wstring currentLine)
{
    if (index + 7 > currentLine.size())
    {
        return false;
    }

    wstring cur = currentLine.substr(index, 7);
    wstring wigth = convert.from_bytes(" Width=");
    return cur == wigth;
}

bool TranslateInterface::isHeight(int index, wstring currentLine)
{
    if (index + 8 > currentLine.size())
    {
        return false;
    }

    wstring cur = currentLine.substr(index, 8);
    wstring height = convert.from_bytes(" Height=");
    return cur == height;
}

bool TranslateInterface::isString(int index, wstring currentLine)
{
    if (index + 8 > currentLine.size())
    {
        return false;
    }

    wstring cur = currentLine.substr(index, 8);
    wstring str = convert.from_bytes(" String=");
    return cur == str;
}

bool TranslateInterface::isNextString(wstring currentLine)
{
    for (int index = 0; index < currentLine.size(); index++)
    {
        if (isString(index, currentLine))
        {
            return true;
        }
    }

    return false;
}

void TranslateInterface::initRussianData()
{
    for (int lineIndex = 0; lineIndex < russianLines.size(); lineIndex++)
    {
        currentData data;
        wstring currentLine = russianLines[lineIndex];
        wstring currentName;
        for (int index = 0; index < currentLine.size(); index++)
        {
            wstring currentValue;
            if (isName(index, currentLine))
            {
                int closeIndex = index + 7;
                while (currentLine[closeIndex] != '\"')
                {
                    currentName += currentLine[closeIndex++];
                }
                index = closeIndex;
                russianDatas.insert({ currentName, data });
            }
            if (russianDatas.find(currentName) != russianDatas.end())
            {
                if (isX(index, currentLine))
                {
                    int closeIndex = index + 4;
                    while (currentLine[closeIndex] != '\"')
                    {
                        currentValue += currentLine[closeIndex++];
                    }
                    index = closeIndex;
                    data.x = currentValue;
                }
                else if (isY(index, currentLine))
                {
                    int closeIndex = index + 4;
                    while (currentLine[closeIndex] != '\"')
                    {
                        currentValue += currentLine[closeIndex++];
                    }
                    index = closeIndex;
                    data.y = currentValue;
                }
                else if (isWidth(index, currentLine))
                {
                    int closeIndex = index + 8;
                    while (currentLine[closeIndex] != '\"')
                    {
                        currentValue += currentLine[closeIndex++];
                    }
                    index = closeIndex;
                    data.width = currentValue;
                }
                else if (isHeight(index, currentLine))
                {
                    int closeIndex = index + 9;
                    while (currentLine[closeIndex] != '\"')
                    {
                        currentValue += currentLine[closeIndex++];
                    }
                    index = closeIndex;
                    data.height = currentValue;
                }
            }
        }
        wstring nextLine;
        if (lineIndex + 1 < russianLines.size())
        {
            nextLine = russianLines[lineIndex + 1];
            if (isNextString(nextLine))
            {
                wstring currentValue;
                for (int index = 0; index < nextLine.size(); index++)
                {
                    if (isString(index, nextLine))
                    {
                        int closeIndex = index + 9;
                        while (nextLine[closeIndex] != '\"')
                        {
                            currentValue += nextLine[closeIndex++];
                        }
                        index = closeIndex;
                        data.nextString = currentValue;
                        break;
                    }
                }
            }
        }
        if (lineIndex + 2 < russianLines.size())
        {
            nextLine = russianLines[lineIndex + 2];
            if (isNextString(nextLine))
            {
                wstring currentValue;
                for (int index = 0; index < nextLine.size(); index++)
                {
                    if (isString(index, nextLine))
                    {
                        int closeIndex = index + 9;
                        while (nextLine[closeIndex] != '\"')
                        {
                            currentValue += nextLine[closeIndex++];
                        }
                        index = closeIndex;
                        data.secondString = currentValue;
                        break;
                    }
                }
            }
        }
        russianDatas[currentName] = data;
    }
}

void TranslateInterface::toOutput(wstring currentLine)
{
    currentData russianLine;
    wstring currentName;
    wstring outputLine;

    for (int index = 0; index < currentLine.size(); index++)
    {
        if (isName(index, currentLine))
        {
            wstring name = convert.from_bytes(" Name=\"");
            outputLine += name;
            int closeIndex = index + 7;
            while (currentLine[closeIndex] != '\"')
            {
                currentName += currentLine[closeIndex++];
            }
            index = closeIndex;
            if (russianDatas.find(currentName) != russianDatas.end())
            {
                russianLine = russianDatas[currentName];
            }
            outputLine += currentName;
        }
        else if (isX(index, currentLine))
        {
            if (russianLine.x.size() > 0)
            {
                wstring x = convert.from_bytes(" x=\"");
                outputLine += x;
                outputLine += russianLine.x;
                int closeIndex = index + 4;
                while (currentLine[closeIndex++] != '\"');
                index = closeIndex - 1;
            }
        }
        else if (isY(index, currentLine))
        {
            if (russianLine.y.size() > 0)
            {
                wstring y = convert.from_bytes(" y=\"");
                outputLine += y;
                outputLine += russianLine.y;
                int closeIndex = index + 4;
                while (currentLine[closeIndex++] != '\"');
                index = closeIndex - 1;
            }
        }
        else if (isWidth(index, currentLine))
        {
            if (russianLine.width.size() > 0)
            {
                wstring width = convert.from_bytes(" Width=\"");
                outputLine += width;
                outputLine += russianLine.width;
                int closeIndex = index + 8;
                while (currentLine[closeIndex++] != '\"');
                index = closeIndex - 1;
            }
        }
        else if (isHeight(index, currentLine))
        {
            if (russianLine.width.size() > 0)
            {
                wstring height = convert.from_bytes(" Height=\"");
                outputLine += height;
                outputLine += russianLine.height;
                int closeIndex = index + 9;
                while (currentLine[closeIndex++] != '\"');
                index = closeIndex - 1;
            }
        }
        outputLine += currentLine[index];
    }

    outputLines.push_back(outputLine);
    outputLine.clear();
    if (russianLine.nextString.size() > 0)
    {
        globalIndex++;
        currentLine = chinesLines[globalIndex];
        for (int index = 0; index < currentLine.size(); index++)
        {
            if (isString(index, currentLine))
            {
                if (russianLine.width.size() > 0)
                {
                    wstring height = convert.from_bytes(" String=\"");
                    outputLine += height;
                    outputLine += russianLine.nextString;
                    int closeIndex = index + 9;
                    while (currentLine[closeIndex++] != '\"');
                    index = closeIndex - 1;
                }
            }
            outputLine += currentLine[index];
        }
        outputLines.push_back(outputLine);
    }
    outputLine.clear();
    if (russianLine.secondString.size() > 0)
    {
        globalIndex++;
        currentLine = chinesLines[globalIndex];
        for (int index = 0; index < currentLine.size(); index++)
        {
            if (isString(index, currentLine))
            {
                if (russianLine.width.size() > 0)
                {
                    wstring height = convert.from_bytes(" String=\"");
                    outputLine += height;
                    outputLine += russianLine.secondString;
                    int closeIndex = index + 9;
                    while (currentLine[closeIndex++] != '\"');
                    index = closeIndex - 1;
                }
            }
            outputLine += currentLine[index];
        }
        outputLines.push_back(outputLine);
    }
    return;
}

vector<wstring> TranslateInterface::getAllFiles()
{
    return files;
}

void TranslateInterface::translateFile(wstring fileName)
{
    clear();
    wifstream file(path1 + L"\\" + fileName, ios::in | ios::binary);
    file.imbue(locale(file.getloc(), new codecvt_utf16<wchar_t, 0xffff, consume_header>));

    wstring line;

    while (getline(file, line))
    {
        chinesLines.push_back(line);
    }
    file.close();

    file.open(path2 + L"\\" + fileName, ios::in | ios::binary);
    file.imbue(locale(file.getloc(), new codecvt_utf16<wchar_t, 0xffff, consume_header>));

    while (getline(file, line))
    {
        russianLines.push_back(line);
    }
    file.close();

    initRussianData();

    for (globalIndex = 0; globalIndex < chinesLines.size(); globalIndex++)
    {
        wstring currentLine = chinesLines[globalIndex];
        toOutput(currentLine);
    }

    ofstream fout(out + L"\\" + fileName, ios::out | ios::binary);
    fout.imbue(locale(file.getloc(), new codecvt_utf16<wchar_t, 0x10ffff, consume_header>));
    for (const auto currentLine : outputLines)
    {
        fout << convert.to_bytes(currentLine);
    }
    fout.close();
}