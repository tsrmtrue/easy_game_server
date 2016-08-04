#-*- coding:GBK -*-
import sys
sys.path.append('../')

"""
      1.给定一个建表的sql语句，生成一个c++结构，以及一个给结构赋值的宏
      2.给定一个field的list，生成一个c++结构，以及一个给定结构赋值的宏
"""
import MySQLdb
import re
import string

def get_fields(create_str):
    #s = create_str.replace('\r\n', '')
    #[field,type,(count)]
    pat = re.compile('^[ ]*`(\w+)`[ ]+(\w+)(\(\d+\))?[ ]+(UNSIGNED)?', re.MULTILINE)
    result = pat.findall(create_str)
    # print result
    return result

def get_valid_fields(fields):
    templist = []
    for f in fields:
        if f[0] in ['CREATE','PRIMARY','UNIQUE','KEY','ENGINE']:
            pass
        else:
            templist.append(f)
    #print "get valid fields"
    #print templist
    return templist

def get_valid_fields_filter(valid_fields, filter_fields):
    temp_list = []
    for vf in valid_fields:
        if vf[0] in filter_fields:
            temp_list.append(vf)
            filter_fields.remove(vf[0])
    if len(filter_fields) <> 0:
        print "not valid field(s) :", filter_fields
        print valid_fields
        return None
    return temp_list

def build_select_all_str(table_name):
    return '#define SELECT_SQL_%s_ALL \"SELECT * FROM %s  \"\n'%(table_name.upper(),table_name)

def get_field_name(field):
    return field[0]

def get_condition(field):
    name = field[0]
    format = get_cpp_format(field)
    return "%(name)s=%(format)s"%(locals())

def get_select_struct_members(field):
    name = field[0]
    if field[1] in ['BLOB', 'CHAR', "VARCHAR"]:
        #extendname = get_extend_member_name(name)
        return '_%(name)s'%(locals())
        #return 'm_pMyConn->EscapeString((const char*)(st.%(name)s), st.%(extendname)s)'%(locals())
    return 'st.%(name)s'%(locals())

def build_select_str(needfields, byfields, table_name, operation, all=False):
    TABLE_NAME = table_name.upper()
    operation = operation.upper()
    conditions = string.join(map(get_condition, byfields), " AND ")
    if len(byfields) > 0:
        conditions = "WHERE " + conditions
    structMembers = string.join(map(get_select_struct_members, byfields), ',')
    if len(byfields) > 0:
        structMembers = ", "+structMembers
    if all:
        needs = "*"
    else:
        needs = string.join(map(get_field_name, needfields), ',')
    select_template = """
#define SELECT_SQL_%(TABLE_NAME)s_%(operation)s(st) "SELECT %(needs)s FROM %(table_name)s %(conditions)s"%(structMembers)s
"""
    return select_template%(locals())

def build_limit_select_str(needfields, byfields, table_name, operation, orderby, isdesc, limit, all=False):
    table_name_upper = table_name.upper()
    operation = operation.upper()
    wherecondition = ""
    structMembers = ""
    if byfields <> None and len(byfields) > 0:
        wherecondition = string.join(map(get_condition, byfields), " AND ")
        wherecondition = "WHERE "+wherecondition
        structMembers = string.join(map(get_select_struct_members, byfields), ',')
        structMembers = ", "
    if all:
        needs = "*"
    else:
        needs = string.join(map(get_field_name, needfields), ',')
    order = "DESC"
    if not isdesc:
        order = "ASC"
    limit_str = ""
    if limit <> None and limit <> "" and limit <> "0":
        limit_str = "limit %s"%(limit)
    select_template = """
#define %(operation)s_LIMIT %(limit)s 
#define SELECT_SQL_%(table_name_upper)s_%(operation)s(st) "SELECT %(needs)s FROM %(table_name)s %(wherecondition)s order by %(orderby)s %(order)s %(limit_str)s"%(structMembers)s
"""
    return select_template%(locals())


def get_cpp_format(field):
    #print "get cpp format"
    #print field
    #print g_sql_2_cpp_type[field[1]]
    #print get_member_count(field) 
    if field[1] in ['BLOB',]:#datetime 定义为char数组，数据库里存的是字符串
        return "'%s'"
    elif g_sql_2_cpp_type[field[1]] in ['char', ] and get_member_count(field) <> '':
        return "'%s'"
    elif field[1] in ['BIGINT',]:
        return "'%llu'"
    if field[3] == 'UNSIGNED':
        return "'%u'"
    else :
        return "'%d'"
    

def get_update_str(field):
    field_name = field[0]
    type = get_cpp_format(field)
    return '%(field_name)s=%(type)s'%(locals())


def build_update_str(updateFields, constraintFields, table_name, operation):
    #print fields
    #print map(get_update_str, fields)
    TABLE_NAME = table_name.upper()
    operation = operation.upper()
    updates = string.join(map(get_update_str, updateFields), ',')
    constraints = string.join(map(get_update_str, constraintFields), ',')
    updateValues = string.join(map(get_update_fields, updateFields), ',')
    constraintValues = string.join(map(get_update_fields, constraintFields), ',')
    update_template = """
#define UPDATE_SQL_%(TABLE_NAME)s_%(operation)s "UPDATE %(table_name)s SET %(updates)s  WHERE %(constraints)s", %(updateValues)s,%(constraintValues)s
"""
    return update_template%(locals())

def get_update_fields(field):
    name = field[0]
    if field[1] in ['BLOB', 'CHAR', "VARCHAR"]:
        #extendname = get_extend_member_name(name)
        return '_%(name)s'%(locals())
        #return 'm_pMyConn->EscapeString((const char*)(st.%(name)s), st.%(extendname)s)'%(locals())
    return 'st.%(name)s'%(locals())

def get_escap_fields(field):
    if field[1] in ['BLOB', 'CHAR', "VARCHAR"]:
        name = field[0]
        length = "1024*50"
        sourceLength = ""
        if field[2] <> '':
            length = field[2][1:-1]
            sourceLength = "strlen(st.%(name)s)"%(locals())
        else :
            extendname = get_extend_member_name(name)
            sourceLength = "st.%(extendname)s"%(locals())
        return 'char _%(name)s[(%(length)s)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.%(name)s), %(sourceLength)s, _%(name)s, sizeof(_%(name)s));'%(locals())
        #return 'm_pMyConn->EscapeString((const char*)(st.%(name)s), st.%(extendname)s)'%(locals())
    return ""
    
def build_escaping_macro(fields, table_name, operation):
    """得到cpp结构的参数列表
    """
    op = operation.upper()
    tb_name = table_name.upper()
    fields = string.join(map(get_escap_fields, fields), ';')
    return "#define MACRO_ESCAPE_FIELDS_%(op)s_%(tb_name)s(st) %(fields)s  \n"%(locals())
    
    
    
def build_cpp_insert_fields_macro(fields, table_name, operation):
    """得到cpp结构的参数列表
    """
    op = operation.upper()
    tb_name = table_name.upper()
    fields = string.join(map(get_update_fields, fields), ',')
    return "#define MACRO_STRUCT_FIELDS_%(op)s_%(tb_name)s(st) %(fields)s  \n"%(locals())

def get_field_name(field):
    return field[0]

def build_insert_str(fields, table_name, operation):
    #print fields
    #print map(get_update_str, fields)
    OP = operation.upper()
    TB_NAME = table_name.upper()
    fields_name = string.join(map(get_field_name, fields), ',')
    values = string.join(map(get_cpp_format, fields), ',')
    return '#define INSERT_SQL_%(OP)s_%(TB_NAME)s \"INSERT INTO %(table_name)s (%(fields_name)s) VALUES(%(values)s) \"\n'%(locals())
    
#创建cpp结构
g_sql_2_cpp_type = {
                    'BIGINT':'long long',
                    'BIGINT UNSIGNED':'unsigned long long',
                    'VARCHAR':'char',
                    'CHAR':'char',
                    'char':'char',
                    'SMALLINT':'unsigned short',
                    'TINYINT':'unsigned char',
                    'INTEGER':'int',
                    'INTEGER UNSIGNED' : 'unsigned int',
                    'MEDIUMINT':'int',
                    'BLOB':'unsigned char',
                    'DATETIME':'char',
                    'datetime':'char',
                    'TIMESTAMP':'unsigned int',
                    'timestamp':'unsigned int',
                    }


g_blob_length = {}
def set_blob_length(d):
    global g_blob_length
    g_blob_length = d


def add_blob_length(key, value):
    global g_blob_length
    g_blob_length[key] = value

g_sql_map = {}

def set_sql_map(d):
    global g_sql_map
    g_sql_map = d

def add_sql_map(key, value):
    global g_sql_map
    g_sql_map[key] = value

def get_member_count(field,):
    global g_blob_length
    if field[1] == 'VARCHAR':
        return '[%s]'%(field[2][1:-1])
    elif field[1] == 'BLOB':
        size = g_blob_length.get(field[0], None)
        return '[%s]'%(size)
    elif field[1] == 'DATETIME':
        return '[32]'
    elif field[1] == 'CHAR':
        return '[%s]'%(field[2][1:-1])
    return ''

def get_extend_member_name(name):
    return '_current_%s_length'%(name)

def get_extend_member(type, field):
    if type in ['BLOB']:
        return 'int %s;'%(get_extend_member_name(field))
    return ''


def get_member(f):
    global g_sql_2_cpp_type
    type = f[1]
    if f[3] <> '':
        type = type + " " +f[3]
    type = g_sql_2_cpp_type.get(type, None)
    if type == None:
        print 'errrrrrrrrrrrrrrrrrrrrrrror', f
    field = f[0]
    count = get_member_count(f)
    extend = get_extend_member(f[1], field)
    return '%(type)s %(field)s%(count)s;%(extend)s'%(locals())

g_struct_name_list = list()

def build_cpp_struct(valid_fields, sqlname):
    struct_template = """struct %(struct_name)s
{
    %(members)s
};
"""
    struct_name = sqlname
    global g_struct_name_list
    g_struct_name_list.append("%(struct_name)s"%(locals()))
    #print valid_fields
    #print map(get_member, valid_fields)
    try :
        members = string.join(map(get_member, valid_fields), '\n    ')
        return struct_template%(locals()) 
    except KeyError, e:
        print valid_fields;
        raise e
    except :
        print "err7777", valid_fields
        raise BaseException()
    return "" 


def build_convert_field(field):
    field_name = field[0]
    if field[1] in ['BLOB',]:#datetime 定义为char数组，数据库里存的是字符串
        extend = get_extend_member_name(field_name)
        return 'getFieldLength(RC, _i,(st.%(extend)s));autoAssignChunck(RC,_i++, st.%(field_name)s, (st.%(extend)s));'%(locals())
    elif g_sql_2_cpp_type[field[1]] == 'char' and get_member_count(field) <> '':
        return 'autoAssign(RC,_i++, st.%(field_name)s, sizeof(st.%(field_name)s));'%(locals())
    else :
        return 'autoAssign(RC,_i++,st.%(field_name)s,0);'%(locals())


def build_convert_macro(fields, name):
    #创建赋值的宏
    convert_template = """
#define CONVERT_RECORD_%(operation)s(RC,st) \\
int _i = 0;\\
%(member)s

"""
    operation = name.upper()
    member = string.join(map(build_convert_field, fields), '\\\n') + '\n'
    return convert_template%(locals())

def build_create_table_sql(create_sql, table_name):
    return '#define CREATE_TABLE_%s  '%table_name.upper() + '\"' + create_sql.replace('`', '').replace('\n', '\\\n') + '\"\n'

def build_sql_by_createsql(targetList):
    str = ''
    str = '\n/****************************************************************************/\n'
    global g_sql_map
    for table_name in targetList:
        if table_name not in g_sql_map.keys():
            continue
        # print table_name
        valid_fields = get_valid_fields(get_fields(g_sql_map[table_name]))
        str += build_create_table_sql(g_sql_map[table_name], table_name)
        str += build_cpp_struct(valid_fields, 'Sql_SelectAll_'+table_name+'')
        str += build_convert_macro(valid_fields, table_name+'_selectall')
        #str += build_select_all_str(table_name)
    return str

def build_select_sql_by_field_list(needfieldlist, byfieldlist, table_name, operation):
    """指定表格，还有field列表，将判断field名字是不是合法，然后生成sql语句，赋值宏，fields对应的数据结构
    operation应该是包含操作和具体的事件，比如,select_entergame,insert_newrole
    本函数生成select语句相关的"""
    str = '\n/****************************************************************************/\n'
    global g_sql_map
    valid_fields = get_valid_fields(get_fields(g_sql_map[table_name]))
    valid_fields_by = get_valid_fields_filter(valid_fields, byfieldlist)
    valid_fields_need = get_valid_fields_filter(valid_fields, needfieldlist)
    #print valid_fields
    str += build_cpp_struct(valid_fields_need, 'Sql_Select_'+table_name+'_'+operation)
    str += build_convert_macro(valid_fields_need, table_name+'_'+operation)
    str += build_escaping_macro(valid_fields_by, table_name, operation)
    str += build_select_str(valid_fields_need, valid_fields_by, table_name, operation)
    return str

def build_select_sql_by_field_list_limit(needfieldlist, byfieldlist, table_name, operation, orderby, limit, isdesc=False):
    """limit版本 指定表格，还有field列表，将判断field名字是不是合法，然后生成sql语句，赋值宏，fields对应的数据结构
    operation应该是包含操作和具体的事件，比如,select_entergame,insert_newrole
    本函数生成select语句相关的"""
    str = '\n/****************************************************************************/\n'
    global g_sql_map
    valid_fields = get_valid_fields(get_fields(g_sql_map[table_name]))
    valid_fields_by = get_valid_fields_filter(valid_fields, byfieldlist)
    valid_fields_need = get_valid_fields_filter(valid_fields, needfieldlist)
    #print valid_fields
    str += build_cpp_struct(valid_fields_need, 'Sql_Select_'+table_name+'_'+operation)
    str += build_convert_macro(valid_fields_need, table_name+'_'+operation)
    str += build_escaping_macro(valid_fields_by, table_name, operation)
    str += build_limit_select_str(valid_fields_need,valid_fields_by, table_name, operation, orderby, isdesc, limit, False)
    return str


def build_select_sql_all_by_field_list(byfieldlist, table_name, operation):
    """指定表格，还有field列表，将判断field名字是不是合法，然后生成sql语句，赋值宏，fields对应的数据结构
    operation应该是包含操作和具体的事件，比如,select_entergame,insert_newrole
    本函数生成select语句相关的"""
    str = '\n/****************************************************************************/\n'
    global g_sql_map
    valid_fields = get_valid_fields(get_fields(g_sql_map[table_name]))
    valid_fields_by = get_valid_fields_filter(valid_fields, byfieldlist)
    #print valid_fields
    str += build_cpp_struct(valid_fields_by, 'Sql_SelectAll_'+table_name+'_'+operation)
    #str += build_convert_macro(valid_fields_specified, table_name+'_'+operation)    
    str += build_escaping_macro(valid_fields_by, table_name, operation)
    str += build_select_str([],valid_fields_by, table_name, operation, True)
    return str

def build_limit_select_sql_all_by_field_list(byfieldlist, table_name, operation, orderby, limit, isdesc=False):
    """指定表格，还有field列表，将判断field名字是不是合法，然后生成sql语句，赋值宏，fields对应的数据结构
    operation应该是包含操作和具体的事件，比如,select_entergame,insert_newrole
    本函数生成select语句相关的"""
    str = '\n/****************************************************************************/\n'
    global g_sql_map
    valid_fields = get_valid_fields(get_fields(g_sql_map[table_name]))
    valid_fields_by = get_valid_fields_filter(valid_fields, byfieldlist)
    #print valid_fields
    str += build_cpp_struct(valid_fields_by, 'Sql_SelectAll_'+table_name+'_'+operation)
    #str += build_convert_macro(valid_fields_specified, table_name+'_'+operation)
    str += build_escaping_macro(valid_fields_by, table_name, operation)
    str += build_limit_select_str([],valid_fields_by, table_name, operation, orderby, isdesc, limit, True)
    return str


def build_update_sql_by_field_list(updateFieldList, constraintFieldList, table_name, operation):
    """指定表格，还有field列表，将判断field名字是不是合法，然后生成sql语句，赋值宏，fields对应的数据结构
    operation应该是包含操作和具体的事件，比如,select_entergame,insert_newrole
    本函数生成update语句相关的"""
    str = '\n/****************************************************************************/\n'
    global g_sql_map
    valid_fields = get_valid_fields(get_fields(g_sql_map[table_name]))
    valid_fields_update = get_valid_fields_filter(valid_fields, updateFieldList)
    valid_fields_constraint = get_valid_fields_filter(valid_fields, constraintFieldList)
    valid_fields_total = []
    for l in valid_fields_update:
        valid_fields_total.append(l)
    for l in valid_fields_constraint:
        if l not in valid_fields_update:
            valid_fields_total.append(l)
    #print  valid_fields_specified
    str += build_cpp_struct(valid_fields_total, 'Sql_Update_'+table_name+'_'+operation)
    str += build_escaping_macro(valid_fields_update, table_name, operation)
    str += build_update_str(valid_fields_update, valid_fields_constraint, table_name, operation)
    #str += build_cpp_insert_fields_macro(valid_fields_specified, table_name, operation)
    return str

def build_insert_sql_by_field_list(fieldlist, table_name, operation):
    """指定表格，还有field列表，将判断field名字是不是合法，然后生成sql语句，赋值宏，fields对应的数据结构
    operation应该是包含操作和具体的事件，比如,select_entergame,insert_newrole
    本函数生成insert语句相关的"""
    str = '\n/****************************************************************************/\n'
    global g_sql_map
    valid_fields = get_valid_fields(get_fields(g_sql_map[table_name]))
    valid_fields_specified = get_valid_fields_filter(valid_fields, fieldlist)
    #print  valid_fields_specified
    str += build_cpp_struct(valid_fields_specified, 'Sql_Insert_'+table_name+'_'+operation)
    str += build_insert_str(valid_fields_specified, table_name, operation)
    str += build_escaping_macro(valid_fields_specified, table_name, operation)
    str += build_cpp_insert_fields_macro(valid_fields_specified, table_name, operation)#这个结构的变量表次序是一样的
    return str

def build_wrap_member(struct_name):
    return "        %(struct_name)s st_%(struct_name)s;"%(locals())

def build_wrap_struct(module_name):
    global g_struct_name_list
    wrap_struct_template = """struct SDB_Wrap%(module_name)s
{
    int socket;//用来寻找发起的玩家
    int operateId;//操作id
    int operateType;
    int operateUserData;
    int rcCount;//返回结果的多少,0,没有结果,1,一个结果,2,二个...
    int dbErrcode;//错误值
    unsigned long long insertId;//如果是insert操作，这里是返回插入id
    unsigned int dbId;//具体连哪个db，需要有配置文件支持
    union{
%(member)s
        char temp[512]; //特殊情况下使用
        } _u;
};
"""
    member = string.join(map(build_wrap_member, g_struct_name_list), '\n')
    return wrap_struct_template%(locals())

def build_db_operator_enum_member(struct_name):
    enum_name = string.upper(struct_name)[4:]#把第一个Sql_去掉
    return "        DB_OPRATOR_%(enum_name)s,"%(locals())

def build_operation_enum(model_name):
    global g_struct_name_list
    operator_enum_template="""
enum {
        NONE_OPERATION%(model_name)s=0,
%(members)s
    };
"""
    members = string.join(map(build_db_operator_enum_member, g_struct_name_list), '\n') + '\n'
    return operator_enum_template%(locals())



