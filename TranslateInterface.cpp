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

void TranslateInterface::toNormalRussiaSTF()
{
    vector<wstring> temp;
    for (int i = 0; i < russianLinesSTF.size(); i++)
    {
        wstring currentLine = russianLinesSTF[i];
        wstring newLine;
        for (int j = 0; j < currentLine.size(); j++)
        {
            newLine += currentLine[j];
            if (currentLine[j] == '\r' && newLine.size() > 0 && newLine != L"\r" && newLine != L"\t\r")
            {
                if (currentLine[j] != '\r')
                {
                    newLine += L'\r';
                }
                temp.push_back(newLine);
                newLine.clear();
            }
        }
        if (newLine.size() > 0 && newLine != L"\r" && newLine != L"\t\r")
        {
            if (newLine[newLine.size() - 1] != '\r')
            {
                newLine += L'\r';
            }
            temp.push_back(newLine);
            newLine.clear();
        }
    }

    russianLinesSTF = temp;
}

void TranslateInterface::toNormalChineSTF()
{
    vector<wstring> temp;
    for (int i = 0; i < chinesLinesSTF.size(); i++)
    {
        wstring currentLine = chinesLinesSTF[i];
        wstring newLine;
        for (int j = 0; j < currentLine.size(); j++)
        {
            newLine += currentLine[j];
            if (currentLine[j] == '\r' && newLine.size() > 0 && newLine != L"\r" && newLine != L"\t\r")
            {
                if (currentLine[j] != '\r')
                {
                    newLine += L'\r';
                }
                temp.push_back(newLine);
                newLine.clear();
            }
        }
        if (newLine.size() > 0 && newLine != L"\r" && newLine != L"\t\r")
        {
            if (newLine[newLine.size() - 1] != '\r')
            {
                newLine += L'\r';
            }
            temp.push_back(newLine);
            newLine.clear();
        }
    }

    chinesLinesSTF = temp;
}

int TranslateInterface::openBracket(wstring line)
{
    for (int i = 0; i < 16; i++)
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
            if (currentName == L"")
            {
                int posName = currentLine.find(L" Name=");
                if (posName != string::npos)
                {
                    int posOpenQuote = currentLine.find(L"\"", posName);
                    int posCloseQuote = currentLine.find(L"\"", posOpenQuote + 1);
                    currentName = currentLine.substr(posOpenQuote + 1, posCloseQuote - posOpenQuote - 1);
                }
            }
            russianDataXML[currentName] = dataLine;
            index = secondIndex;
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
            if (currentLine[j] == '\r' && newLine.size() > 0 && newLine != L"\r" && newLine != L"\t\r")
            {
                if (currentLine[j] != '\r')
                {
                    newLine += L'\r';
                }
                temp.push_back(newLine);
                newLine.clear();
            }
        }
        if (newLine.size() > 0 && newLine != L"\r" && newLine != L"\t\r")
        {
            if (newLine[newLine.size() - 1] != '\r')
            {
                newLine += L'\r';
            }
            temp.push_back(newLine);
            newLine.clear();
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
            if (currentLine[j] == '\r' && newLine.size() > 0 && newLine != L"\r" && newLine != L"\t\r")
            {
                if (currentLine[j] != '\r')
                {
                    newLine += L'\r';
                }
                temp.push_back(newLine);
                newLine.clear();
            }
        }
        if (newLine.size() > 0 && newLine != L"\r" && newLine != L"\t\r")
        {
            if (newLine[newLine.size() - 1] != '\r')
            {
                newLine += L'\r';
            }
            temp.push_back(newLine);
            newLine.clear();
        }
    }

    chinesLinesXML = temp;
}

bool check(wstring line)
{
    for (int i = 0; i < 16; i++)
    {
        wstring currentOpenBracket = OPENBRACKET[i];
        int posOpenBracket = line.find(currentOpenBracket, currentOpenBracket.size());
        if (posOpenBracket != string::npos)
        {
            return false;
        }
    }

    int posX = line.find(L" x=");
    int posY = line.find(L" y=");
    
    if (line[posX + 4] == L'-' || line[posY + 4] == L'-')
    {
        return false;
    }
    return true;
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
                    chinesDataXML.insert(currentName);
                    if (russianDataXML.find(currentName) != russianDataXML.end())
                    {
                        if (check(russianDataXML[currentName]))
                        {
                            dataLine = russianDataXML[currentName];
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
                if (currentName == L"")
                {
                    int posName = currentLine.find(L" Name=");
                    if (posName != string::npos)
                    {
                        int posOpenQuote = currentLine.find(L"\"", posName);
                        int posCloseQuote = currentLine.find(L"\"", posOpenQuote + 1);
                        currentName = currentLine.substr(posOpenQuote + 1, posCloseQuote - posOpenQuote - 1);
                        chinesDataXML.insert(currentName);
                        if (russianDataXML.find(currentName) != russianDataXML.end())
                        {
                            if (check(russianDataXML[currentName]))
                            {
                                dataLine = russianDataXML[currentName];
                            }
                        }
                    }
                }
            }
            index = secondIndex;
        }
        outputLinesXML.push_back(dataLine);
    }
}

bool TranslateInterface::isComment(int index, wstring currentLine)
{
    wstring cur = currentLine.substr(index, 2);
    wstring newLine = L"//";
    return cur == newLine;
}

bool isNumber(wchar_t c)
{
    return c >= 48 && c <= 57;
}

bool isSpace(wchar_t c)
{
    return c == '\t' || c == ' ';
}

bool startLineID(int index, wchar_t c)
{
    return index <= 1 && isNumber(c);
}

void TranslateInterface::initRussianDataSTF()
{
    for (int i = 0; i < russianLinesSTF.size(); i++)
    {
        wstring currentLine = russianLinesSTF[i];
        wstring currentData;
        wstring id;
        wstring space;
        for (int j = 0; j < currentLine.size(); j++)
        {
            if (isNumber(currentLine[j]))
            {
                id += currentLine[j];
            }
            else if (isSpace(currentLine[j]))
            {
                space += currentLine[j];
            }
            else if (id.size() > 0)
            {
                while (!startLineID(j, currentLine[j]))
                {
                    currentData += currentLine[j];
                    j++;
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
                }
                russianDatasSTF[id] = currentData;
                i--;
                break;
            }
        }
    }
}

void TranslateInterface::initChineDataSTF()
{
    for (int i = 0; i < chinesLinesSTF.size(); i++)
    {
        wstring currentLine = chinesLinesSTF[i];
        wstring currentData;
        wstring id;
        wstring space;
        for (int j = 0; j < currentLine.size(); j++)
        {
            if (isNumber(currentLine[j]))
            {
                id += currentLine[j];
            }
            else if (isSpace(currentLine[j]))
            {
                space += currentLine[j];
            }
            else if (id.size() > 0)
            {
                while (!startLineID(j, currentLine[j]))
                {
                    currentData += currentLine[j];
                    j++;
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
                            chineDatasSTF[id].str = currentData;
                            chineDatasSTF[id].space = space;
                            return;
                        }
                    }
                }
                chineDatasSTF[id].str = currentData;
                chineDatasSTF[id].space = space;
                i--;
                break;
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

    toOutput();

    for (const auto iter : russianDataXML)
    {
        if (chinesDataXML.find(iter.first) == chinesDataXML.end())
        {
            outputLinesXML.push_back(iter.second);
        }
    }
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
        outputLinesSTF.push_back(to_wstring(toOut[i].first) + toOut[i].second.second + toOut[i].second.first);
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

   /* toNormalRussiaSTF();
    toNormalChineSTF();*/
    /*initRussianDataSTF();
    initChineDataSTF();
    toOutputSTF();*/

    ofstream fout(out + L"\\" + fileName, ios::out | ios::binary);
    fout.imbue(locale(file.getloc(), new codecvt_utf16<wchar_t, 0x10ffff, consume_header>));

    wstring_convert<codecvt_utf16<
        wchar_t, 0x10ffff, codecvt_mode(generate_header | little_endian)>> conv;
    for (const auto currentLine : russianLinesSTF)
    {
        fout << conv.to_bytes(currentLine);
    }
    /*for (int i = russianLinesSTF.size(); i < chinesLinesSTF.size(); i++)
    {
        fout << conv.to_bytes(chinesLinesSTF[i]);
    }*/
    /*for (const auto currentLine : outputLinesSTF)
    {
        fout << conv.to_bytes(currentLine);
    }*/
    fout.close();
}