# -*- coding: utf-8 -*-


import string
from parse_h_struct import *

g_encode_dict = {
              "unsigned int"        :"encode_long",
              "int"                 :"encode_long",              
              "short"               :"encode_short",
              "unsigned short"      :"encode_short",
              "unsigned long long"  :"nolonglong",
              "long long"           :"nolonglong",              
              "char"                :"encode_byte",
              "unsigned char"       :"encode_byte",
              }


g_decode_dict = {
              "unsigned int"        :"decode_long",
              "int"                 :"decode_long_signed",              
              "short"               :"decode_short",
              "unsigned short"      :"decode_short",
              "unsigned long long"  :"nolonglong",
              "long long"           :"nolonglong",
              "char"                :"decode_byte",
              "unsigned char"       :"decode_byte",
               }

g_type_len_dict = {
              "unsigned int"        :"4",
              "int"                 :"4",              
              "short"               :"2",
              "unsigned short"      :"2",
              "unsigned long long"  :"8",
              "long long"           :"8",
              "char"                :"1",
              "unsigned char"       :"1",
               }

g_type_2_java_dict = {
              "unsigned int"        :"int",
              "int"                 :"int",              
              "short"               :"short",
              "unsigned short"      :"short",
              "unsigned long long"  :"long",
              "long long"           :"long",
              "char"                :"char",
              "unsigned char"       :"byte",


}
g_decode_func_list = []
g_encode_func_list = []

g_projectPrefix = ""

def get_type_len_by_type(type):
    global g_type_len_dict
    return g_type_len_dict.get(type, "")
    
def get_decode_by_type(type):
    global g_projectPrefix
    global g_hton_dict
    projectPrefix = g_projectPrefix
    s = g_decode_dict.get(type, None)
    if s == "nolonglong":
        raise ValueError('longlong of: %(type)r' % locals())
    
    if s == None:
        s = "%(s)s.decode(buf, __used__)"%(locals())
    else:
        s=s+"(buf, __used__)"
    return s

def get_encode_by_type(type):
    global g_projectPrefix
    global g_ntoh_dict
    projectPrefix = g_projectPrefix

    s = g_encode_dict.get(type, None)
    if s == "nolonglong":
        raise ValueError('longlong of: %(type)r' % locals())

    if s == None:
        s = "%(s)s.encode"%(locals())
    return s

# def build_member_encode_4_java(member):
#     type = member[0]
#     name = member[1]
#     count = member[2]
#     refer = member[3]
#     if refer <> "":
#         refer = refer[2:-2]
#     encode_ = get_encode_by_type(type)
#     single_standard_type_template = """
#     local _s = %(encode_)s(st.%(name)s)
#     if _s == nil then
#         error(" return nil %(name)s")
#         return nil
#     else
#         buf = buf .. _s
#     end
# """
#     array_bytes_template = """
#     if %(for_limit)s > %(count)s then 
#         error(" return nil %(name)s forlimit" .. %(for_limit)s .."count" .. %(count)s)
#         return nil
#     end
#     buf = buf..st.%(name)s
# """
#     array_standard_type_template = """
#     if %(for_limit)s > %(count)s then
#         error(" return nil %(name)s forlimit" .. %(for_limit)s .."count" .. %(count)s)
#         return nil
#     end
#     for i=1, %(for_limit)s do
#         local _s = %(encode_)s(st.%(name)s[i])
#         if _s == nil then
#             error(" return nil %(name)s")
#             return nil
#         end
#         buf = buf.._s
#     end

# """
#     array_struct_type_template = """
#     %(check_count)s
#     for i=1, %(for_limit)s do
#         local _s = %(encode_)s(st.%(name)s%(array_ptr)s)
#         if _s == nil then
#             error(" return nil %(name)s")
#             return nil
#         end
#         buf = buf.._s
#     end
# """
#     string_type_template = """
#     if string.len(st.%(name)s) > %(count)s then
#         error(" return nil %(name)s")
#         return nil
#     end
#     local _s = encode_short(string.len(st.%(name)s))
#     if _s == nil then
#         error(" return nil %(name)s")
#         return nil
#     else
#         buf = buf .. _s
#     end
#     buf = buf..st.%(name)s
# """
#     for_limit = "%(count)s"%(locals())
#     if count == "":
#         for_limit = "1"
#     if refer <> "":
#         for_limit = "st.%(refer)s"%(locals())

#     check_count = ""
#     if count <> "" and refer <> "":
#         check_count = """
#     if st.%(refer)s > %(count)s then
#         error(" return nil %(name)s forlimit" .. st.%(refer)s .. "count" .. %(count)s)
#         return nil
#     end"""%(locals())

#     if isMemberNumber(member):
#         #»ù±¾ÀàÐÍ
#         if count <> "":
#             #bytes
#             if type == "unsigned char  nouse":
#                 for_limit = "string.len(st.%(name)s)"%(locals())
#                 return array_bytes_template%(locals())
#             #ÆäËûÊý×é
#             else:
#                 return array_standard_type_template%(locals())
#         else:
#         #·ÇÊý×é
#             return single_standard_type_template%(locals())
#     elif isMemberString(member):
#         for_limit = "string.len(st.%(name)s)"%(locals())
#         return string_type_template%(locals())
#     elif isMemberStruct(member):
#         if for_limit == "":
#             print member
#         array_ptr = ""
#         if count <> "":
#             array_ptr = "[i]"
#         return array_struct_type_template%(locals())

"""
def get_build_struct_class_4_java(structName):
    return build_struct_class_4_java(structName, "")

def get_build_struct_class_4_java_4_passport(structName):
    return build_struct_class_4_java(structName, "passport")
"""

def build_member_define_4_java(member):
    type = member[0]
    name = member[1]
    count = member[2]
    refer = member[3]
    if refer <> "":
        refer = refer[2:-2]
    global g_type_2_java_dict
    javatype = g_type_2_java_dict.get(type, None)
    init = ""
    if javatype == None:
        javatype = type
        init = " = new " + type + "()";
    if count != "":
        if javatype == "char":
            javatype = "String"
        elif javatype == "byte":
            javatype = "byte[]"
            init = " = new byte["+count+"]";
        elif javatype == type:
            javatype = javatype+"[]"
            init = " = new " + type + "["+count+"]";


    # if refer <> "":
    #     for_limit = "st.%(refer)s"%(locals())
    return "        " + javatype + " " + name + init + ";"


def build_member_constructor_4_java(member):
    type = member[0]
    name = member[1]
    count = member[2]
    refer = member[3]
    if refer <> "":
        refer = refer[2:-2]
    javatype = g_type_2_java_dict.get(type, None)
    if javatype == None and count != "":
        return """            for (int i = 0; i < %(count)s; i++) {
                %(name)s[i] = new %(type)s();
            }
"""%(locals())
    return ""


def build_member_encode_4_java(member):
    type = member[0]
    name = member[1]
    count = member[2]
    refer = member[3]
    if refer <> "":
        refer = refer[2:-2]
    global g_type_2_java_dict
    javatype = g_type_2_java_dict.get(type, None)
    if javatype != None:
        if count != "":
            if javatype == "char":
                javatype = "String"
            elif javatype == "byte":
                javatype = "byteArray"
        return """            if (false == encode_%(javatype)s(__t__, __used__, %(name)s))
            {
                return false;
            }
        """%(locals())

    else:
        javatype = type
        if count == "":
            return """            if (false == %(name)s.encode(__t__, __used__)) {
                return false;
            }

        """%(locals())
        else:
            return """            if(%(refer)s > %(count)s)
            {
                return false;
            }
            for(int i = 0; i<%(refer)s; ++i)
            {
                if (false == %(name)s[i].encode(__t__, __used__)) {
                    return false;
                }

            }
            """%(locals())

def build_member_decode_4_java(member):
    type = member[0]
    name = member[1]
    count = member[2]
    refer = member[3]
    if refer <> "":
        refer = refer[2:-2]
    global g_type_len_dict
    type_length = g_type_len_dict.get(type, None)
    global g_type_2_java_dict
    javatype = g_type_2_java_dict.get(type, None)
    if javatype != None:
        if count != "":
            if javatype == "char":
                javatype = "String"
            elif javatype == "byte":
                javatype = "byteArray"
            return """            if ((%(name)s = decode_%(javatype)s(__t__, __used__)) == null)
            {
                return  false;
            }
            """%(locals())
        else:
            return """            if (__used__[0] + %(type_length)s > __t__.length) {
                return false;
            }
            %(name)s = decode_%(javatype)s(__t__, __used__);

            """%(locals())

    else:
        javatype = type
        if count == "":
            return """            %(name)s = new %(type)s();
            if (false == %(name)s.decode(__t__, __used__))
            {
                return false;
            }
        """%(locals())
        else:
            return """            if(%(refer)s > %(count)s)
            {
                return false;
            }
            for (int i = 0; i < %(refer)s; ++i)
            {
                if (false == %(name)s[i].decode(__t__, __used__))
                {
                    return false;
                }
            }
            """%(locals())

def build_struct_class_4_java(structName):
    global g_struct_dict
    global g_projectPrefix
    projectPrefix = g_projectPrefix

    struct = g_struct_dict.get(structName, None)
    if struct == None:
        raise ValueError('build build_struct_encode_4_cpp not found the definition of: %(structName)s' % locals())
    
    encode_template = """
    public class %(structName)s {

%(members)s

%(constructor)s

%(encode_function)s

%(decode_function)s

    }
"""
    encode_function_template = """
        boolean encode(byte[] __t__, int[] __used__) {
%(member_encodes)s
            return true;
        }
"""
    decode_function_template = """
        boolean decode(byte[] __t__, int[] __used__) {
%(member_decodes)s
            return true;
        }
"""
    constructor_template = """
        public %(structName)s() {
%(member_constructor)s
            return ;
        }
"""

    func_name = "encode_%(structName)s"%(locals())
    global g_encode_func_list
    g_encode_func_list.append(func_name)
    
    members = string.join(map(build_member_define_4_java, struct), '\n');
    member_encodes = string.join(map(build_member_encode_4_java, struct), '\n');
    member_decodes = string.join(map(build_member_decode_4_java, struct), '\n');
    member_constructor = string.join(map(build_member_constructor_4_java, struct), '\n');
    encode_function = encode_function_template%(locals())
    decode_function = decode_function_template%(locals())
    constructor = constructor_template%(locals())

    return encode_template%(locals())    
    
def build_enum_4_java(enum):
    name = enum[0]
    value = enum[1]
    return """    public static final int %(name)s = %(value)s;"""%(locals())

def build_packing_4_java():
    global g_projectPrefix
    projectPrefix = g_projectPrefix
    encode_template = """
package com.example.hasee.myapplication;

public class CPnlProtocol {

%(all_enum)s

    public static boolean encode_byte(byte[] t, int[] used, byte b) {
        if (used[0] + 1 > t.length) {
            return false;
        }
        t[used[0]] = b;
        used[0]++;
        return true;
    }

    public static boolean encode_short(byte[] t, int[] used, short s) {
        if (used[0] + 2 > t.length) {
            return false;
        }
        t[used[0]++] = (byte) (s >> 8 & 0xff);
        t[used[0]++] = (byte) (s & 0xff);
        return true;
    }

    public static boolean encode_int(byte[] t, int[] used, int i) {
        if (used[0] + 4 > t.length) {
            return false;
        }
        t[used[0]++] = (byte) (i >> 24 & 0xff);
        t[used[0]++] = (byte) (i >> 16 & 0xff);
        t[used[0]++] = (byte) (i >> 8 & 0xff);
        t[used[0]++] = (byte) (i & 0xff);
        return true;
    }

    public static boolean encode_byteArray(byte[] t, int[] used, byte[] s)
    {
        if (used[0] + s.length + 2 > t.length) {
            return false;
        }
        encode_short(t, used, (short)s.length);
        System.arraycopy(s, 0, t, used[0], s.length);
        used[0] += s.length;
        return true;
    }

    public static boolean encode_String(byte[] t, int[] used, String s) {
        return encode_byteArray(t, used, s.getBytes());
    }

    //decode函数 必须之前就做好检查数组越界，这里只能返回一个值，因此返回目标值
    public static byte decode_byte(byte[] t, int[] used) {
        byte _t = t[used[0]];
        used[0]++;
        return _t;
    }

    public static int decode_int(byte[] t, int[] used) {
        int _t = 0;
        _t = ((int) (t[used[0] + 3]) & 0xff)
                + (((int) t[used[0] + 2] & 0xff) << 8)
                + (((int) t[used[0] + 1] & 0xff)<< 16)
                + (((int) t[used[0]] & 0xff)<< 24);
        used[0] += 4;
        return _t;
    }

    public static short decode_short(byte[] t, int[] used) {
        short _t = 0;
        int _t2 = ((int) (t[used[0] + 1]) & 0xff)
                + (((int) t[used[0]] & 0xff) << 8);
        _t = (short)_t2;
        used[0] += 2;
        return _t;
    }


    public static byte[] decode_byteArray(byte[] t, int[] used)
    {
        if (used[0] + 2 > t.length) {
            return null;
        }
        short l = decode_short(t, used);

        byte[] _t = new  byte[l];
        if (used[0] + l > t.length) {
            return null;
        }
        System.arraycopy(t, used[0], _t, 0, l);
        used[0] += l;
        return _t;
    }

    public static String decode_String(byte[] t, int[] used)
    {
        byte[] b = decode_byteArray(t, used);
        if (b != null)
        {
            return new String(b);
        }
        return null;
    }
%(JavaClasses)s

}
"""
    # global g_all_enum
    # all_enum = g_all_enum
    global g_enum_value_list
    all_enum = string.join(map(build_enum_4_java, g_enum_value_list), '\n')
    global g_struct_dict
    JavaClasses = string.join(map(build_struct_class_4_java, g_struct_dict.keys()), '\n')
    return encode_template%(locals())


    
g_all_enum = ""

def parseHFileWithTarget(hFile,targetPackingFile):
    f = open(hFile, 'r')
    filestr = f.read()


    # filestr2 = string.replace(filestr, "\n", " nnn ")
    # filestr2 = string.replace(filestr2, "\t", " ttt ")
    # print filestr2

    # global g_all_enum
    # enums = []
    # s = parseCppGetAllEnum(filestr2)
    # for l in s:
    #     l = string.replace(l, "ttt", "\t")
    #     l = string.replace(l, "nnn", "\n")
    #     enums.append(l)
    # g_all_enum = string.join(enums, "\n")
    # print g_all_enum


    filestr = string.replace(filestr, "\n", " ")
    filestr = string.replace(filestr, "\t", " ")


    #print [filestr, ]
    parseCppStruct(filestr)

    parseCppEnum(filestr)
    parseEnumValueAll()
    # global g_enum_dict 
    # print buildEnumValueString()
    
    w = open(targetPackingFile, 'w')
    w.write(build_packing_4_java())
    w.close()
    


#def main():
#    parseHFile("../Common/Protocols/protocols.h")

print "hello "
