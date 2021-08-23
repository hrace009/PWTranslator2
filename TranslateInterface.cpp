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
    chinesLinesXML.clear();
    russianLinesXML.clear();
outputLinesXML.clear();
russianDataXML.clear();
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


vector<wstring> TranslateInterface::getAllFiles()
{
    return files;
}

vector<wstring> TranslateInterface::getAllFilesSTF()
{
    return filesSTF;
}

bool TranslateInterface::isName(int index, wstring line)
{
    if (index + 6 >= line.size())
    {
        return false;
    }

    wstring name = L" Name=";
    wstring cur = line.substr(index, 6);

    return name == cur;
}

int TranslateInterface::isOpenBracket(int index, wstring line)
{
    for (int i = 0; i < 8; i++)
    {
        wstring currentOpen = OPENBRACKET[i];

        if (index + currentOpen.size() < line.size())
        {
            wstring cur = line.substr(index, currentOpen.size());
            if (cur == currentOpen)
            {
                return i;
            }
        }
    }

    return -1;
}

bool TranslateInterface::isCloseBracket(int index, wstring line, int numberOpen)
{
    wstring currentClose = CLOSEBRACKET[numberOpen];

    if (index + currentClose.size() >= line.size())
    {
        return false;
    }

    wstring cur = line.substr(index, currentClose.size());

    return currentClose == cur;
}

int TranslateInterface::findCloseQuote(int index, wstring line)
{
    for (; index < line.size(); index++)
    {
        if (line[index] == '\"')
        {
            return index;
        }
    }

    return -1;
}

bool TranslateInterface::endLine(int start, int numLine, int index, wstring line)
{
    if (start != numLine)
    {
        return false;
    }

    if (index + 2 >= line.size())
    {
        return false;
    }

    wstring cur = line.substr(index, 2);
    wstring str = L"/>";

    return str == cur;
}

void TranslateInterface::initRussianDataXML()
{
    for (int index = 0; index < russianLinesXML.size(); index++)
    {
        wstring currentName;
        wstring currentLine = russianLinesXML[index];
        wstring dataLine;
        int startIndex = index;
        for (int j = 0; j < currentLine.size(); j++)
        {
            int numberOpenBracket = isOpenBracket(j, currentLine);
            dataLine += currentLine[j];
            if (numberOpenBracket != -1)
            {
                j++;
                while (!isCloseBracket(j, currentLine, numberOpenBracket) && !endLine(startIndex, index, j, currentLine))
                {
                    if (isName(j, currentLine))
                    {
                        int closeQuote = findCloseQuote(j + 7, currentLine);
                        currentName = currentLine.substr(j + 7, closeQuote - (j + 7));
                    }
                    dataLine += currentLine[j];
                    j++;
                    if (j == currentLine.size())
                    {
                        j = 0;
                        index++;
                        if (index >= russianLinesXML.size())
                        {
                            break;
                        }
                        currentLine = russianLinesXML[index];
                    }
                }
                if (isCloseBracket(j, currentLine, numberOpenBracket))
                {
                    dataLine += CLOSEBRACKET[numberOpenBracket];
                    dataLine += '\r';
                }
                else if (endLine(startIndex, index, j, currentLine))
                {
                    dataLine += L"/>\r";
                }
                russianDataXML[currentName] = dataLine;
            }
        }
    }
}

void TranslateInterface::toNormalChine()
{
    vector<wstring> temp;
    for (int i = 0; i < chinesLinesXML.size(); i++)
    {
        wstring currentLine = chinesLinesXML[i];
        wstring newLine;
        for (int j = 0; j < currentLine.size(); j++)
        {
            newLine += currentLine[j];
            if (currentLine[j] == '\r')
            {
                temp.push_back(newLine);
                newLine = L"";
            }
        }
    }

    chinesLinesXML = temp;
}

void TranslateInterface::toOutput()
{
    for (int index = 0; index < chinesLinesXML.size(); index++)
    {
        wstring currentName;
        wstring currentLine = chinesLinesXML[index];
        wstring dataLine;
        int startIndex = index;
        bool flag = false;
        for (int j = 0; j < currentLine.size(); j++)
        {
            int numberOpenBracket = isOpenBracket(j, currentLine);
            dataLine += currentLine[j];
            if (numberOpenBracket != -1)
            {
                j++;
                while (!isCloseBracket(j, currentLine, numberOpenBracket) && !endLine(startIndex, index, j, currentLine))
                {
                    if (isName(j, currentLine))
                    {
                        int closeQuote = findCloseQuote(j + 7, currentLine);
                        currentName = currentLine.substr(j + 7, closeQuote - (j + 7));
                        if (russianDataXML.find(currentName) != russianDataXML.end())
                        {
                            dataLine = russianDataXML[currentName];
                            flag = true;
                        }
                    }
                    if (!flag)
                    {
                        dataLine += currentLine[j];
                    }
                    j++;
                    if (j == currentLine.size())
                    {
                        j = 0;
                        index++;
                        if (index >= chinesLinesXML.size())
                        {
                            break;
                        }
                        currentLine = chinesLinesXML[index];
                    }
                }
                if (!flag)
                {
                    if (isCloseBracket(j, currentLine, numberOpenBracket))
                    {
                        dataLine += CLOSEBRACKET[numberOpenBracket];
                        dataLine += '\r';
                    }
                    else if (endLine(startIndex, index, j, currentLine))
                    {
                        dataLine += L"/>\r";
                    }
                    flag = true;
                }
                outputLinesXML.push_back(dataLine);
            }
        }
        if (!flag)
        {
            outputLinesXML.push_back(currentLine);
        }
    }
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
        wstring space;
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
                    chineDatasSTF[id].str = currentString;
                    chineDatasSTF[id].space = space;
                }
            }
            else
            {
                if (currentLine[j] == '\t' || currentLine[j] == ' ')
                {
                    space = currentLine[j];
                }
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
        chinesLinesXML.push_back(line);
    }
    file.close();

    file.open(path2 + L"\\" + fileName, ios::in | ios::binary);
    file.imbue(locale(file.getloc(), new codecvt_utf16<wchar_t, 0xffff, consume_header>));

    while (getline(file, line))
    {
        russianLinesXML.push_back(line);
    }
    file.close();

    initRussianDataXML();
    toNormalChine();
    toOutput();

    ofstream fout(out + L"\\" + fileName, ios::out | ios::binary);
    wstring_convert<codecvt_utf16<
        wchar_t, 0x10ffff, codecvt_mode(generate_header | little_endian)>> conv;
    for (const auto currentLine : outputLinesXML)
    {
        fout << conv.to_bytes(currentLine);
    }
    fout.close();
}

void TranslateInterface::toOutputSTF()
{
    vector<pair<int, pair<wstring, wstring>>> toOut;

    for (const auto iter : chineDatasSTF)
    {
        int id = stoi(iter.first);
        if (russianDatasSTF.find(iter.first) != russianDatasSTF.end())
        {
            toOut.push_back({ id, {russianDatasSTF[iter.first], iter.second.space } });
        }
        else
        {
            toOut.push_back({ id, {iter.second.str, iter.second.space} });
        }
    }

    sort(toOut.begin(), toOut.end());

    for (int i = 0; i < toOut.size(); i++)
    {
        outputLinesSTF.push_back(to_wstring(toOut[i].first) + toOut[i].second.second + toOut[i].second.first + L"\r");
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