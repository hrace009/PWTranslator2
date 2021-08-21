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

void TranslateInterface::initSTF(wstring firstPath)
{
    WIN32_FIND_DATAW wfd;
    wstring path = firstPath + L"\\*.stf";
    HANDLE const hFind = FindFirstFileW(path.c_str(), &wfd);

    if (INVALID_HANDLE_VALUE != hFind)
    {
        do
        {
            filesSTF.push_back(&wfd.cFileName[0]);
        } while (NULL != FindNextFileW(hFind, &wfd));

        FindClose(hFind);
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

void TranslateInterface::clearSTF()
{
    chinesLinesSTF.clear();
    chineDatasSTF.clear();
    russianLinesSTF.clear();
    russianDatasSTF.clear();
    outputLinesSTF.clear();
}

TranslateInterface::TranslateInterface(System::String^ firstPath, System::String^ secondPath, System::String^ outputPath)
{
    msclr::interop::marshal_context context;
    path1 = context.marshal_as<wstring>(firstPath);
    path2 = context.marshal_as<wstring>(secondPath);
    out = context.marshal_as<wstring>(outputPath);
    this->initFiles(path1, L"");
    this->initFolders(out);
    this->initSTF(path1);
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
            currentName = L"";
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
    if (russianLine.nextString.size() > 0 && globalIndex < chinesLines.size() - 1)
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
    if (russianLine.secondString.size() > 0 && globalIndex < chinesLines.size() - 1)
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

vector<wstring> TranslateInterface::getAllFilesSTF()
{
    return filesSTF;
}

bool TranslateInterface::isQuote(int index, wstring currentLine)
{
    wstring cur = currentLine.substr(index, 1);
    wstring quote = L"\"";

    return cur == quote;
}

bool TranslateInterface::isNotNumber(int index, wstring currentLine)
{
    wstring cur = currentLine.substr(index, 1);
    return cur == L"0" || cur == L"1" ||
        cur == L"2" || cur == L"3" ||
        cur == L"4" || cur == L"5" ||
        cur == L"6" || cur == L"7" ||
        cur == L"8" || cur == L"9";
}

bool TranslateInterface::isNewLine(int index, wstring currentLine)
{
    wstring cur = currentLine.substr(index, 1);
    wstring newLine = L"\r";
    return cur == newLine;
}

bool TranslateInterface::isComment(int index, wstring currentLine)
{
    wstring cur = currentLine.substr(index, 2);
    wstring newLine = L"//";
    return cur == newLine;
}

wstring TranslateInterface::toNormalID(wstring id)
{
    wstring newID;
    for (int i = 0; i < id.size(); i++)
    {
        if (!isNotNumber(i, id))
        {
            return newID;
        }
        newID += id[i];
    }

    return newID;
}

void TranslateInterface::initRussianDataSTF()
{
    for (int i = 0; i < russianLinesSTF.size(); i++)
    {
        wstring currentLine = russianLinesSTF[i];
        wstring id;
        for (int j = 0; j < currentLine.size(); j++)
        {
            if (isComment(j, currentLine))
            {
                break;
            }
            if (isQuote(j, currentLine))
            {
                id = toNormalID(id);
                wstring currentString;
                currentString += currentLine[j++];
                while (!isQuote(j, currentLine))
                {
                    if (j == currentLine.size())
                    {
                        j = 0;
                        i++;
                        if (i < russianLinesSTF.size())
                        {
                            currentLine = russianLinesSTF[i];
                        }
                        else
                        {
                            return;
                        }
                    }
                    else
                    {
                        currentString += currentLine[j++];
                    }
                }
                currentString += currentLine[j++];
                russianDatasSTF[id] = currentString;
            }
            else
            {
                id += currentLine[j];
            }
        }
    }
}

void TranslateInterface::initChineDataSTF()
{
    for (int i = 0; i < chinesLinesSTF.size(); i++)
    {
        wstring currentLine = chinesLinesSTF[i];
        wstring id;
        for (int j = 0; j < currentLine.size(); j++)
        {
            if (isComment(j, currentLine))
            {
                break;
            }
            if (isQuote(j, currentLine))
            {
                id = toNormalID(id);
                wstring currentString;
                currentString += currentLine[j++];
                while (!isQuote(j, currentLine))
                {
                    if (j == currentLine.size())
                    {
                        j = 0;
                        i++;
                        if (i < chinesLinesSTF.size())
                        {
                            currentLine = chinesLinesSTF[i];
                        }
                        else
                        {
                            return;
                        }
                    }
                    else
                    {
                        currentString += currentLine[j++];
                    }
                }
                currentString += currentLine[j++];
                if (chineDatasSTF.find(id) == chineDatasSTF.end())
                {
                    chineDatasSTF[id] = currentString;
                }
            }
            else
            {
                id += currentLine[j];
            }
        }
    }
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
    wstring_convert<codecvt_utf16<
        wchar_t, 0x10ffff, codecvt_mode(generate_header | little_endian)>> conv;
    for (const auto currentLine : outputLines)
    {
        fout << conv.to_bytes(currentLine);
    }
    fout.close();
}

void TranslateInterface::toOutputSTF()
{
    vector<pair<int, wstring>> toOut;

    for (const auto iter : chineDatasSTF)
    {
        int id = stoi(iter.first);
        if (russianDatasSTF.find(iter.first) != russianDatasSTF.end())
        {
            toOut.push_back({ id, russianDatasSTF[iter.first] });
        }
        else
        {
            toOut.push_back({ id, iter.second });
        }
    }

    sort(toOut.begin(), toOut.end());

    for (int i = 0; i < toOut.size(); i++)
    {
        outputLinesSTF.push_back(to_wstring(toOut[i].first) + L" " + toOut[i].second + L"\r");
    }
}


void TranslateInterface::translateFileSTF(wstring fileName)
{
    clearSTF();
    wifstream file(path1 + L"\\" + fileName, ios::in | ios::binary);
    file.imbue(locale(file.getloc(), new codecvt_utf16<wchar_t, 0xffff, consume_header>));

    wstring line;

    while (getline(file, line))
    {
        chinesLinesSTF.push_back(line);
    }
    file.close();

    file.open(path2 + L"\\" + fileName, ios::in | ios::binary);
    file.imbue(locale(file.getloc(), new codecvt_utf16<wchar_t, 0xffff, consume_header>));

    while (getline(file, line))
    {
        russianLinesSTF.push_back(line);
    }
    file.close();

    initRussianDataSTF();
    initChineDataSTF();
    toOutputSTF();

    ofstream fout(out + L"\\" + fileName, ios::out | ios::binary);
    fout.imbue(locale(file.getloc(), new codecvt_utf16<wchar_t, 0x10ffff, consume_header>));

    wstring_convert<codecvt_utf16<
        wchar_t, 0x10ffff, codecvt_mode(generate_header | little_endian)>> conv;
    for (const auto currentLine : outputLinesSTF)
    {
        fout << conv.to_bytes(currentLine);
    }
    fout.close();
}