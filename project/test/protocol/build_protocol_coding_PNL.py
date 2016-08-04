# -*- coding: utf-8 -*-

import sys
sys.path.append('../../../lib/protocol_handle')


import build_coding_4_cpp
build_coding_4_cpp.parseHFileWithTarget("pnl_protocol.h", "pnl_protocol_encode.h","pnl_protocol_encode.cpp","pnl_protocol_decode.h","pnl_protocol_decode.cpp")
print "2"

import build_coding_4_java
build_coding_4_java.parseHFileWithTarget("pnl_protocol.h", "CPnlProtocol.java")

import build_coding_4_py
build_coding_4_py.parseAndBuild("pnl_protocol.h", moduleName="PNL", protocolEnum="EProtocolId", relativePath="")

import build_coding_4_lua
build_coding_4_lua.parseHFileWithTarget("pnl_protocol.h", "pnl_protocol_encode.lua", "pnl_protocol_decode.lua")

import build_lua_json_struct_str
build_lua_json_struct_str.parseHFile2LuaProtocol("pnl_protocol.h", "pnl_protocol_enum.lua", "pnl_protocol_table_struct.lua")

print "all ok"
