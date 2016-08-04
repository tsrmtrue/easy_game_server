#include "ConfigureParser.h"
#include <string>
#include <fstream>
#include "ConfigureEnumMap.h"
#include <string.h>
#include <stdlib.h>
using namespace std;

bool parseSServerConfig(const char* pStr, SServerConfig& st)
{
    memset(&st, 0, sizeof(st));
    std::string s = pStr;
    size_t start = 0;
    size_t foundIndex = 0;


    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        st.id = atoi(s.substr(start, foundIndex-start).c_str());
        start = foundIndex+1;
    }
    else
    {
        return false;
    }


    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        strncpy(st.name, s.substr(start, foundIndex-start).c_str(), foundIndex - start);
        start = foundIndex+1;
    }
    else
    {
        return false;
    }


    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        strncpy(st.ip, s.substr(start, foundIndex-start).c_str(), foundIndex - start);
        start = foundIndex+1;
    }
    else
    {
        return false;
    }


    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        st.port = atoi(s.substr(start, foundIndex-start).c_str());
        start = foundIndex+1;
    }
    else
    {
        return false;
    }


    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        strncpy(st.db_ip, s.substr(start, foundIndex-start).c_str(), foundIndex - start);
        start = foundIndex+1;
    }
    else
    {
        return false;
    }


    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        st.db_port = atoi(s.substr(start, foundIndex-start).c_str());
        start = foundIndex+1;
    }
    else
    {
        return false;
    }


    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        strncpy(st.db_u, s.substr(start, foundIndex-start).c_str(), foundIndex - start);
        start = foundIndex+1;
    }
    else
    {
        return false;
    }


    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        strncpy(st.db_p, s.substr(start, foundIndex-start).c_str(), foundIndex - start);
        start = foundIndex+1;
    }
    else
    {
        return false;
    }


    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        strncpy(st.db, s.substr(start, foundIndex-start).c_str(), foundIndex - start);
        start = foundIndex+1;
    }
    else
    {
        return false;
    }


    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        st.rolelimit = atoi(s.substr(start, foundIndex-start).c_str());
        start = foundIndex+1;
    }
    else
    {
        return false;
    }


    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        st.sleep = atoi(s.substr(start, foundIndex-start).c_str());
        start = foundIndex+1;
    }
    else
    {
        return false;
    }


    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        st.iocpworkers = atoi(s.substr(start, foundIndex-start).c_str());
        start = foundIndex+1;
    }
    else
    {
        return false;
    }


    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        st.isopen = getEnumValue(s.substr(start, foundIndex-start));
        start = foundIndex+1;
    }
    else
    {
        return false;
    }


    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        strncpy(st.globalNtf, s.substr(start, foundIndex-start).c_str(), foundIndex - start);
        start = foundIndex+1;
    }
    else
    {
        return false;
    }


    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        st.canRegister = getEnumValue(s.substr(start, foundIndex-start));
        start = foundIndex+1;
    }
    else
    {
        return false;
    }


    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        st.isNew = getEnumValue(s.substr(start, foundIndex-start));
        start = foundIndex+1;
    }
    else
    {
        return false;
    }

    return true;
}


bool parseSServerConfigFile(const char* pFilename, std::vector<SServerConfig>& sts)
{
    ifstream inf(pFilename);
    if (!inf.is_open())
    {
        return false;
    }
    char temp[20480] = "";
    inf.getline(temp, sizeof(temp));
    while (!inf.eof())
    {
        memset(temp, 0, sizeof(temp));
        inf.getline(temp, sizeof(temp));
        temp[strlen(temp)]=',';
        SServerConfig st = {0};
        if (parseSServerConfig(temp, st))
        {
            sts.push_back(st);
        }
    }
    inf.close();
    return true;
}

