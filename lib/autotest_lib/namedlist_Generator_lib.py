# -*- coding: GBK -*-
# 联系作者 qq 150237442
#完成:增加del,去除标志位的作用,测试
#完成:set数组的时候，t.x[2] = 3,只调用了get，没有调用set，麻烦啊
#完成:测试mylist的效率问题，还有嵌套
#完成,改造getItem 设置基类,如果是自定义对象,则添加一个_parent变量,以及idx,在set的时候,回调setidx
class mybaseobject(object):
    def set_parent_idx(self):
        if self.__dict__.get('_parent') <> None and self.__dict__.get('_parent_idx') <> None:
            self._parent._tag[self._parent_idx/8] |= 1<<(self._parent_idx%8)
            self._parent.set_parent_idx()
    def set_parent_and_idx(self, parent, idx):
        self._parent = parent
        self._parent_idx = idx

def getItem(idx):
    def g(self):
        #print "get"
        class mylist(list):#
            def setst(self, st):
                self._st = st
            def __setitem__(self,i,y):
                self._st._tag[idx/8] |= 1<<(idx%8)
                if isinstance(self._st, mybaseobject):
                    self._st.set_parent_idx()
                list.__setitem__(self._st._list[idx],i,y)
                #print "after list.__setitem__(self,i,y)", self
            def __getitem__(self,y):
                if isinstance(self._st._list[idx][y], mybaseobject):
                    #print "======getitem mybase======="
                    self._st._list[idx][y].set_parent_and_idx(self._st, idx)
                return self._st._list[idx][y]
        if isinstance(self._list[idx], list):
            l = mylist(self._list[idx])#
            l.setst(self)
            return l
            #print "normal type"
        elif isinstance(self._list[idx], mybaseobject):
            self._list[idx].set_parent_and_idx(self, idx)
            """self._list[idx]._parent = self
            self._list[idx]._parent_idx = idx"""
            return self._list[idx]
            #print "need mylist"
        else:
            return self._list[idx]
    return g
def setItem(idx):
    def s(self, p):
        #print "set"
        self._tag[idx/8] |= 1<<(idx%8)
        self._list[idx] = p
        self.set_parent_idx()
    return s
def delItem(idx):
    def d(self):
        #print "del"
        self._tag[idx/8] &= ~(1<<(idx%8))
    return d
        

import re
import string
import sys as _sys

def namedList(typename, fields, verbose=False):
    def getfieldtypes(field_names):
        """ Get the type and array's count if it has for each field
        """
        def getfield(name):
            """parse the field for the name, type and count
            """
            pattern = "^(?P<name>\w+)(=*(?P<type>\w+)*(\[(?P<count>\d+)\])*)"
            #print re.match(pattern, name).groupdict()
            return re.match(pattern, name).groupdict()
        field_types = list()
        for name in field_names:
            typeinfo = getfield(name)
            if typeinfo == None:
                raise ValueError('Type names and field names cannot be parsed: %r' % name)
            #recheck after
            """if typeinfo['type'] != None and typeinfo['type'] not in globals():
                raise ValueError('The field %r\'s type has not been defined: %r' % (typeinfo["name"], typeinfo["type"]))"""
            for info in field_types:
                if info["name"] == typeinfo["name"]:
                    raise ValueError('Encountered duplicated field name: %r' % typeinfo["name"]) 
            field_types.append(typeinfo)
        #print field_types
        return field_types
    
    if isinstance(fields, basestring):
        fields = fields.replace(',', ' ').split() # names separated by whitespace and/or commas
    field_types_dict = getfieldtypes(fields)
    
    def getDefaultValue(field_type):
        if field_type['count'] == None:
            if field_type['type'] == None:
                return 'None'
            else :
                return "%s()"%field_type['type']
        else:
            if field_type['type'] == None:
                return '[None for i in range(%s)]'%field_type['count']
            else:
                return '[%s() for i in range(%s)]'%(field_type['type'], field_type['count'])
    def getDefaultValuePair(field_type):
        return "%s=%s"%(field_type['name'], getDefaultValue(field_type))    
    field_default_value_list = map(getDefaultValuePair, field_types_dict)
    field_default_value_pair_str = string.join(field_default_value_list, ', ')
    
    def getInitAssign(field_type):
        return "        self.%s = %s\n"%(field_type['name'], field_type['name'])
    field_init_str = string.join(map(getInitAssign, field_types_dict), '')
    
    
    field_default_value_str = string.join(map(getDefaultValue, field_types_dict), ', ')

    field_name_list = ['%s'%field_type['name'] for field_type in field_types_dict ]
    field_property_str = string.join(["    %s = property(getItem(%d), setItem(%d), delItem(%d))\n"%(field_name_list[i], i, i, i) for i in range(len(field_name_list)) ], '')
    
    field_repr_str = "\"(" + string.join(['%s=%%s'%name for name in field_name_list], ", ") + ")\""+"%%(%s)"%(string.join(["self.%s"%name for name in field_name_list], ", "))
    
    tag_str = "self._tag = [0 for i in range(%d)]"%(len(field_name_list)/8+1)
    
    template = """class %(typename)s(mybaseobject):
    def __repr__(self):
        return %(field_repr_str)s + "\\n" + self._tag.__repr__()
    def __init__(self, %(field_default_value_pair_str)s):
        self._list = [%(field_default_value_str)s]
        %(tag_str)s

        return
%(field_property_str)s"""%locals()
    
    
    property_head = """
#%(field_init_str)s"""

    if verbose:
        print template
    try:
        exec template in globals()
    except SyntaxError, e:
        raise SyntaxError(e.message + ':\n' )
    result = globals()[typename]

    # For pickling to work, the __module__ variable needs to be set to the frame
    # where the named tuple is created.  Bypass this step in enviroments where
    # sys._getframe is not defined (Jython for example).
    if hasattr(_sys, '_getframe'):
        result.__module__ = _sys._getframe(1).f_globals['__name__']
    #return result

    #global g_percentage
    #g_percentage += 1
    #print g_percentage
    return result

#test example
#namedList("struct_SDF_DT_RoleSimpleData", "RoleId,RoleName,Level,Sex,Career,Hair,Face,Body,Hand,Leg,Foot,Helmet,Mask,Cloth,ShoulderLeft,Back,Res,", True)
#namedList("struct_LGDT_LOGIN_SUCCESS", "UserId,DigitID,SessionID[8],Sig[32],LastSelect,RoleCount,RoleList=struct_SDF_DT_RoleSimpleData[5],", True)
#LGPKG_LOGIN_REQ = namedList("LGPKG_LOGIN_REQ", "Type,InfoLen,Info[512],",True)