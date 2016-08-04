# -*- coding: GBK -*-
# 联系作者 qq 150237442


def getItem(idx):
    def g(self):
        return self._list[idx]
    return g
def setItem(idx):
    def s(self, p):
        self._list[idx] = p
    return s
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
    field_property_str = string.join(["    %s = property(getItem(%d), setItem(%d))\n"%(field_name_list[i], i, i) for i in range(len(field_name_list)) ], '')
    
    field_repr_str = "\"(" + string.join(['%s=%%s'%name for name in field_name_list], ", ") + ")\""+"%%(%s)"%(string.join(["self.%s"%name for name in field_name_list], ", "))
    template = """class %(typename)s():
    def __repr__(self):
        return %(field_repr_str)s 
    def __init__(self, %(field_default_value_pair_str)s):
        self._list = [%(field_default_value_str)s]

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