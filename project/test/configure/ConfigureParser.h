#ifndef __CONFIGURE_PARSER_H__
#define __CONFIGURE_PARSER_H__
#include <vector>
#include "ConfigureStruct.h"

bool parseSServerConfig(const char* pStr, SServerConfig& st);

bool parseSServerConfigFile(const char* pFilename, std::vector<SServerConfig>& sts);

#endif