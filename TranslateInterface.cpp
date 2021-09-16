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
    chinesDataXML.clear();
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

int TranslateInterface::openBracket(wstring line)
{
    for (int i = 0; i < 8; i++)
    {
        wstring currentOpenBracket = OPENBRACKET[i];
        int posOpenBracket = line.find(currentOpenBracket);
        if (posOpenBracket != string::npos)
        {
            return i;
        }
    }

    return -1;
}

bool TranslateInterface::closeBracket(wstring line, int numberOpen)
{
    wstring currentClose = CLOSEBRACKET[numberOpen];
    int posCloseBracket = line.find(currentClose);

    return posCloseBracket != string::npos;
}

bool TranslateInterface::endLine(int start, int numLine, wstring line)
{
    if (start != numLine)
    {
        return false;
    }

    int pos = line.find(L"/>");

    return pos != string::npos;
}

void TranslateInterface::initRussianDataXML()
{
    wstring currentName;
    wstring dataLine;
    for (int index = 0; index < russianLinesXML.size(); index++)
    {
        wstring currentLine = russianLinesXML[index];
        int numberOpenBracket = openBracket(currentLine);
        if (numberOpenBracket != -1)
        {
            dataLine.clear();
            currentName.clear();
            int secondIndex = index;
            while (!closeBracket(currentLine, numberOpenBracket) && !endLine(secondIndex, index, currentLine))
            {
                dataLine += currentLine;
                int posName = currentLine.find(L" Name=");

                if (posName != string::npos)
                {
                    int posOpenQuote = currentLine.find(L"\"", posName);
                    int posCloseQuote = currentLine.find(L"\"", posOpenQuote + 1);
                    currentName = currentLine.substr(posOpenQuote + 1, posCloseQuote - posOpenQuote - 1);
                }
                secondIndex++;
                if (secondIndex == russianLinesXML.size())
                {
                    break;
                }
                currentLine = russianLinesXML[secondIndex];
            }
            if (endLine(secondIndex, index, currentLine) || closeBracket(currentLine, numberOpenBracket))
            {
                dataLine += currentLine;
            }

            russianDataXML[currentName].first = dataLine;
            index = secondIndex;
            int cnt = 0;
            for (int i = 0; i < dataLine.size(); i++)
            {
                if (dataLine[i] == '\r')
                {
                    cnt++;
                }
            }
            russianDataXML[currentName].second = cnt;
        }
    }
}

void TranslateInterface::toNormalRussia()
{
    vector<wstring> temp;
    for (int i = 0; i < russianLinesXML.size(); i++)
    {
        wstring currentLine = russianLinesXML[i];
        wstring newLine;
        for (int j = 0; j < currentLine.size(); j++)
        {
            newLine += currentLine[j];
            if (currentLine[j] == '\r')
            {
                temp.push_back(newLine);
                newLine.clear();
            }
        }
    }

    russianLinesXML = temp;
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
                newLine.clear();
            }
        }
    }

    chinesLinesXML = temp;
}

void TranslateInterface::initChinesDataXML()
{
    wstring currentName;
    wstring dataLine;
    for (int index = 0; index < chinesLinesXML.size(); index++)
    {
        wstring currentLine = chinesLinesXML[index];
        int numberOpenBracket = openBracket(currentLine);
        if (numberOpenBracket != -1)
        {
            dataLine.clear();
            currentName.clear();
            int secondIndex = index;
            while (!closeBracket(currentLine, numberOpenBracket) && !endLine(secondIndex, index, currentLine))
            {
                dataLine += currentLine;
                int posName = currentLine.find(L" Name=");

                if (posName != string::npos)
                {
                    int posOpenQuote = currentLine.find(L"\"", posName);
                    int posCloseQuote = currentLine.find(L"\"", posOpenQuote + 1);
                    currentName = currentLine.substr(posOpenQuote + 1, posCloseQuote - posOpenQuote - 1);
                }
                secondIndex++;
                if (secondIndex == chinesLinesXML.size())
                {
                    break;
                }
                currentLine = chinesLinesXML[secondIndex];
            }
            if (endLine(secondIndex, index, currentLine) || closeBracket(currentLine, numberOpenBracket))
            {
                dataLine += currentLine;
            }
            index = secondIndex;
            int cnt = 0;
            for (int i = 0; i < dataLine.size(); i++)
            {
                if (dataLine[i] == '\r')
                {
                    cnt++;
                }
            }
            chinesDataXML[currentName] = cnt;
        }
    }
}

void TranslateInterface::toOutput()
{
    wstring dataLine;
    wstring currentName;
    bool flag;
    for (int index = 0; index < chinesLinesXML.size(); index++)
    {
        dataLine.clear();
        wstring currentLine = chinesLinesXML[index];
        dataLine += currentLine;
        int numberOpenBracket = openBracket(currentLine);
        flag = false;
        if (numberOpenBracket != -1)
        {
            dataLine.clear();
            currentName.clear();
            int secondIndex = index;
            while (!closeBracket(currentLine, numberOpenBracket) && !endLine(secondIndex, index, currentLine))
            {
                int posName = currentLine.find(L" Name=");

                if (posName != string::npos)
                {
                    int posOpenQuote = currentLine.find(L"\"", posName);
                    int posCloseQuote = currentLine.find(L"\"", posOpenQuote + 1);
                    currentName = currentLine.substr(posOpenQuote + 1, posCloseQuote - posOpenQuote - 1);
                    if (russianDataXML.find(currentName) != russianDataXML.end())
                    {
                        if (russianDataXML[currentName].second == chinesDataXML[currentName])
                        {
                            dataLine = russianDataXML[currentName].first;
                            flag = true;
                        }
                    }
                }
                if (!flag)
                {
                    dataLine += currentLine;
                }
                secondIndex++;
                if (secondIndex == chinesLinesXML.size())
                {
                    break;
                }
                currentLine = chinesLinesXML[secondIndex];
            }
            if (!flag)
            {
                if (endLine(secondIndex, index, currentLine) || closeBracket(currentLine, numberOpenBracket))
                {
                    dataLine += currentLine;
                }
            }
            index = secondIndex;
        }
        outputLinesXML.push_back(dataLine);
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

    toNormalRussia();
    initRussianDataXML();
    toNormalChine();

    if (russianLinesXML.size() > 0)
    {
        chinesLinesXML[0] = russianLinesXML[0];
    }

    initChinesDataXML();
    toOutput();

    wstring_convert<codecvt_utf16<
        wchar_t, 0x10ffff, codecvt_mode(generate_header | little_endian)>> conv;
    ofstream fout(out + L"\\" + fileName, ios::out | ios::binary);
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