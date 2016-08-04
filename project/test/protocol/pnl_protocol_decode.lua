
function decode_long(s, i)
    if i + 4 > string.len(s) + 1 then
        return nil
    end
    local a = string.byte(s,i,i)
    if a == nil then a = 0 end
    local b = string.byte(s,i+1,i+1)
    if b == nil then b = 0 end
    local c = string.byte(s,i+2,i+2)
    if c == nil then c = 0 end
    local d = string.byte(s,i+3,i+3)
    if d == nil then d = 0 end
    --print(a,b,c,d)
    return a*0x100*0x100*0x100 + b*0x100*0x100 + c*0x100 + d
end

function decode_long_signed(s, i)
    if i + 4 > string.len(s) + 1 then
        return nil
    end
    local a = string.byte(s,i,i)
    if a == nil then a = 0 end
    local b = string.byte(s,i+1,i+1)
    if b == nil then b = 0 end
    local c = string.byte(s,i+2,i+2)
    if c == nil then c = 0 end
    local d = string.byte(s,i+3,i+3)
    if d == nil then d = 0 end
    --print(a,b,c,d)
    e = a*0x100*0x100*0x100 + b*0x100*0x100 + c*0x100 + d
    if e < 0x80000000 then
        return e
    else 
        return -(0x7fffffff - (e - 0x80000000 - 1))
    end
end

function decode_short(s, i)
    if i + 2 > string.len(s)+1 then
        return nil
    end
    local a = string.byte(s,i,i)
    if a == nil then a = 0 end
    local b = string.byte(s,i+1,i+1)
    if b == nil then b = 0 end
    return a*0x100 + b
end

function decode_byte(s, i)
    if i + 1 > string.len(s)+1 then
        return nil
    end
    local a = string.byte(s,i,i)
    if a == nil then a = 0 end
    return a
end

protocol_decode_lua = {}

protocol_decode_lua["decode_SBasicDataEx"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.guid = decode_long(buf, __used__)
    if st.guid == nil then
        error(" return nil guid")
        return nil
    else
        __used__ = __used__ + 4
    end


    
    st.ns = {}
    for i=1, 1 do
        if  __used__>string.len(buf) + 1 then
            error(" return nil ns")
            return nil
        end

        st.ns = protocol_decode_lua.decode_SBasicDataNtf(buf, __used__)
        if st.ns == nil then
            error(" return nil ns")
            return nil
        else
            __used__ =  st.ns.__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SGetStageReq"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.stageId = decode_long(buf, __used__)
    if st.stageId == nil then
        error(" return nil stageId")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.blockId = decode_short(buf, __used__)
    if st.blockId == nil then
        error(" return nil blockId")
        return nil
    else
        __used__ = __used__ + 2
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SProtocolTypeRsp"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.errcode = decode_byte(buf, __used__)
    if st.errcode == nil then
        error(" return nil errcode")
        return nil
    else
        __used__ = __used__ + 1
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SKickNtf"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SPackedFiles"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.count = decode_short(buf, __used__)
    if st.count == nil then
        error(" return nil count")
        return nil
    else
        __used__ = __used__ + 2
    end


    
    if st.count > 100 then
        error(" return nil files for limit:" .. st.count .. " count " .. 100 )
        return nil
    end
    st.files = {}
    for i=1, st.count do
        if  __used__>string.len(buf) + 1 then
            error(" return nil files")
            return nil
        end

        st.files[i] = protocol_decode_lua.decode_SPackedFileIndex(buf, __used__)
        if st.files[i] == nil then
            error(" return nil files")
            return nil
        else
            __used__ =  st.files[i].__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SBasicDataString"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.t = decode_long(buf, __used__)
    if st.t == nil then
        error(" return nil t")
        return nil
    else
        __used__ = __used__ + 4
    end


    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil sv")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil sv")
        return nil
    end
    st.sv = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SBasicDataNtf"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.count = decode_long(buf, __used__)
    if st.count == nil then
        error(" return nil count")
        return nil
    else
        __used__ = __used__ + 4
    end


    
    if st.count > 32 then
        error(" return nil t for limit:" .. st.count .. " count " .. 32 )
        return nil
    end
    st.t = {}
    for i=1, st.count do
        if  __used__>string.len(buf) + 1 then
            error(" return nil t")
            return nil
        end

        st.t[i] = protocol_decode_lua.decode_SBasicData(buf, __used__)
        if st.t[i] == nil then
            error(" return nil t")
            return nil
        else
            __used__ =  st.t[i].__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SRole"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    
    st.roleBasic = {}
    for i=1, 1 do
        if  __used__>string.len(buf) + 1 then
            error(" return nil roleBasic")
            return nil
        end

        st.roleBasic = protocol_decode_lua.decode_SBasicRoleInfo(buf, __used__)
        if st.roleBasic == nil then
            error(" return nil roleBasic")
            return nil
        else
            __used__ =  st.roleBasic.__used__
        end
    end


    
    st.paraNow = {}
    for i=1, 1 do
        if  __used__>string.len(buf) + 1 then
            error(" return nil paraNow")
            return nil
        end

        st.paraNow = protocol_decode_lua.decode_SRoleParameters(buf, __used__)
        if st.paraNow == nil then
            error(" return nil paraNow")
            return nil
        else
            __used__ =  st.paraNow.__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SEasyLoginRsp"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.type = decode_long_signed(buf, __used__)
    if st.type == nil then
        error(" return nil type")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.errcode = decode_long(buf, __used__)
    if st.errcode == nil then
        error(" return nil errcode")
        return nil
    else
        __used__ = __used__ + 4
    end


    
    st.roleList = {}
    for i=1, 1 do
        if  __used__>string.len(buf) + 1 then
            error(" return nil roleList")
            return nil
        end

        st.roleList = protocol_decode_lua.decode_SEasyRoleInfo4LoginList(buf, __used__)
        if st.roleList == nil then
            error(" return nil roleList")
            return nil
        else
            __used__ =  st.roleList.__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SEasyRoleInfo4Login"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil rolename")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil rolename")
        return nil
    end
    st.rolename = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l


    st.userid = decode_long_signed(buf, __used__)
    if st.userid == nil then
        error(" return nil userid")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SRegisterReq"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil account")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil account")
        return nil
    end
    st.account = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l


    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil pwd")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil pwd")
        return nil
    end
    st.pwd = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l


    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil mac")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil mac")
        return nil
    end
    st.mac = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SBasicRoleInfo"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.userid = decode_long(buf, __used__)
    if st.userid == nil then
        error(" return nil userid")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.guid = decode_long_signed(buf, __used__)
    if st.guid == nil then
        error(" return nil guid")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.showLevel = decode_long(buf, __used__)
    if st.showLevel == nil then
        error(" return nil showLevel")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.mateid = decode_long(buf, __used__)
    if st.mateid == nil then
        error(" return nil mateid")
        return nil
    else
        __used__ = __used__ + 4
    end


    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil macAddress")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil macAddress")
        return nil
    end
    st.macAddress = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l


    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil rolename")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil rolename")
        return nil
    end
    st.rolename = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l


    st.level = decode_long_signed(buf, __used__)
    if st.level == nil then
        error(" return nil level")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.professionId = decode_long_signed(buf, __used__)
    if st.professionId == nil then
        error(" return nil professionId")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.exp = decode_long_signed(buf, __used__)
    if st.exp == nil then
        error(" return nil exp")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.popularity = decode_long_signed(buf, __used__)
    if st.popularity == nil then
        error(" return nil popularity")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.expTotal = decode_long_signed(buf, __used__)
    if st.expTotal == nil then
        error(" return nil expTotal")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.diamond = decode_long_signed(buf, __used__)
    if st.diamond == nil then
        error(" return nil diamond")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.money = decode_long_signed(buf, __used__)
    if st.money == nil then
        error(" return nil money")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.exploit = decode_long_signed(buf, __used__)
    if st.exploit == nil then
        error(" return nil exploit")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.vigor = decode_long_signed(buf, __used__)
    if st.vigor == nil then
        error(" return nil vigor")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.vigorMax = decode_long_signed(buf, __used__)
    if st.vigorMax == nil then
        error(" return nil vigorMax")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.leaderForce = decode_long_signed(buf, __used__)
    if st.leaderForce == nil then
        error(" return nil leaderForce")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.killingValue = decode_long_signed(buf, __used__)
    if st.killingValue == nil then
        error(" return nil killingValue")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.halliconId = decode_long_signed(buf, __used__)
    if st.halliconId == nil then
        error(" return nil halliconId")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SLeaveMsg2GMReq"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil msg")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil msg")
        return nil
    end
    st.msg = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SCreateRsp"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.errcode = decode_long(buf, __used__)
    if st.errcode == nil then
        error(" return nil errcode")
        return nil
    else
        __used__ = __used__ + 4
    end


    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil name")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil name")
        return nil
    end
    st.name = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l


    st.userid = decode_long(buf, __used__)
    if st.userid == nil then
        error(" return nil userid")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SProbeAnswer"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.a = decode_byte(buf, __used__)
    if st.a == nil then
        error(" return nil a")
        return nil
    else
        __used__ = __used__ + 1
    end


    st.b = decode_byte(buf, __used__)
    if st.b == nil then
        error(" return nil b")
        return nil
    else
        __used__ = __used__ + 1
    end


    st.c = decode_byte(buf, __used__)
    if st.c == nil then
        error(" return nil c")
        return nil
    else
        __used__ = __used__ + 1
    end


    st.d = decode_byte(buf, __used__)
    if st.d == nil then
        error(" return nil d")
        return nil
    else
        __used__ = __used__ + 1
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SBasicDataChangeReq"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    
    st.sbdn = {}
    for i=1, 1 do
        if  __used__>string.len(buf) + 1 then
            error(" return nil sbdn")
            return nil
        end

        st.sbdn = protocol_decode_lua.decode_SBasicDataNtf(buf, __used__)
        if st.sbdn == nil then
            error(" return nil sbdn")
            return nil
        else
            __used__ =  st.sbdn.__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SGetRoleInfoRsp"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    
    st.role = {}
    for i=1, 1 do
        if  __used__>string.len(buf) + 1 then
            error(" return nil role")
            return nil
        end

        st.role = protocol_decode_lua.decode_SRole(buf, __used__)
        if st.role == nil then
            error(" return nil role")
            return nil
        else
            __used__ =  st.role.__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SBasicDataBroadcastNtf"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.guid = decode_long(buf, __used__)
    if st.guid == nil then
        error(" return nil guid")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.t = decode_long(buf, __used__)
    if st.t == nil then
        error(" return nil t")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.v = decode_long(buf, __used__)
    if st.v == nil then
        error(" return nil v")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.jerseyId = decode_long(buf, __used__)
    if st.jerseyId == nil then
        error(" return nil jerseyId")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SGetRoleInfoReq"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.i = decode_long_signed(buf, __used__)
    if st.i == nil then
        error(" return nil i")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SBindAccountReq"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil account")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil account")
        return nil
    end
    st.account = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l


    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil pwd")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil pwd")
        return nil
    end
    st.pwd = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SGmcmdRsp"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.nouse = decode_long(buf, __used__)
    if st.nouse == nil then
        error(" return nil nouse")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SLogoffReq"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SEnterRsp"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.errcode = decode_long(buf, __used__)
    if st.errcode == nil then
        error(" return nil errcode")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.roleCount = decode_long(buf, __used__)
    if st.roleCount == nil then
        error(" return nil roleCount")
        return nil
    else
        __used__ = __used__ + 4
    end


    
    if st.roleCount > 1 then
        error(" return nil roles for limit:" .. st.roleCount .. " count " .. 1 )
        return nil
    end
    st.roles = {}
    for i=1, st.roleCount do
        if  __used__>string.len(buf) + 1 then
            error(" return nil roles")
            return nil
        end

        st.roles[i] = protocol_decode_lua.decode_SRole(buf, __used__)
        if st.roles[i] == nil then
            error(" return nil roles")
            return nil
        else
            __used__ =  st.roles[i].__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SGMAnswerRsp"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil answer")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil answer")
        return nil
    end
    st.answer = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SEasyLoginReq"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.type = decode_long_signed(buf, __used__)
    if st.type == nil then
        error(" return nil type")
        return nil
    else
        __used__ = __used__ + 4
    end


    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil easyAccount")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil easyAccount")
        return nil
    end
    st.easyAccount = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SLogConsumeDiamond"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.type = decode_long(buf, __used__)
    if st.type == nil then
        error(" return nil type")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.gID = decode_long(buf, __used__)
    if st.gID == nil then
        error(" return nil gID")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.itemID = decode_long(buf, __used__)
    if st.itemID == nil then
        error(" return nil itemID")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SBasicDataChangeNtf"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    
    st.sbdn = {}
    for i=1, 1 do
        if  __used__>string.len(buf) + 1 then
            error(" return nil sbdn")
            return nil
        end

        st.sbdn = protocol_decode_lua.decode_SBasicDataNtf(buf, __used__)
        if st.sbdn == nil then
            error(" return nil sbdn")
            return nil
        else
            __used__ =  st.sbdn.__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SBasicDataExNtf"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.count = decode_long(buf, __used__)
    if st.count == nil then
        error(" return nil count")
        return nil
    else
        __used__ = __used__ + 4
    end


    
    if st.count > 21 then
        error(" return nil updates for limit:" .. st.count .. " count " .. 21 )
        return nil
    end
    st.updates = {}
    for i=1, st.count do
        if  __used__>string.len(buf) + 1 then
            error(" return nil updates")
            return nil
        end

        st.updates[i] = protocol_decode_lua.decode_SBasicDataEx(buf, __used__)
        if st.updates[i] == nil then
            error(" return nil updates")
            return nil
        else
            __used__ =  st.updates[i].__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SGetAllStageDescReq"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SLoadFinishedReq"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.intoScene = decode_long(buf, __used__)
    if st.intoScene == nil then
        error(" return nil intoScene")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SGetAllStageDescRsp"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.count = decode_long(buf, __used__)
    if st.count == nil then
        error(" return nil count")
        return nil
    else
        __used__ = __used__ + 4
    end


    
    if st.count > 50 then
        error(" return nil stages for limit:" .. st.count .. " count " .. 50 )
        return nil
    end
    st.stages = {}
    for i=1, st.count do
        if  __used__>string.len(buf) + 1 then
            error(" return nil stages")
            return nil
        end

        st.stages[i] = protocol_decode_lua.decode_SStageInfo(buf, __used__)
        if st.stages[i] == nil then
            error(" return nil stages")
            return nil
        else
            __used__ =  st.stages[i].__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SProbeNtf"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.a = decode_byte(buf, __used__)
    if st.a == nil then
        error(" return nil a")
        return nil
    else
        __used__ = __used__ + 1
    end


    st.b = decode_byte(buf, __used__)
    if st.b == nil then
        error(" return nil b")
        return nil
    else
        __used__ = __used__ + 1
    end


    st.c = decode_byte(buf, __used__)
    if st.c == nil then
        error(" return nil c")
        return nil
    else
        __used__ = __used__ + 1
    end


    st.d = decode_byte(buf, __used__)
    if st.d == nil then
        error(" return nil d")
        return nil
    else
        __used__ = __used__ + 1
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SGlobalNtf"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.t = decode_short(buf, __used__)
    if st.t == nil then
        error(" return nil t")
        return nil
    else
        __used__ = __used__ + 2
    end


    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil msg")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil msg")
        return nil
    end
    st.msg = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l


    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil role")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil role")
        return nil
    end
    st.role = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_STreasureUpdateNtf"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.count = decode_long_signed(buf, __used__)
    if st.count == nil then
        error(" return nil count")
        return nil
    else
        __used__ = __used__ + 4
    end


    
    if st.count > 100 then
        error(" return nil treasures for limit:" .. st.count .. " count " .. 100 )
        return nil
    end
    st.treasures = {}
    for i=1, st.count do
        if  __used__>string.len(buf) + 1 then
            error(" return nil treasures")
            return nil
        end

        st.treasures[i] = protocol_decode_lua.decode_STreasureInBag(buf, __used__)
        if st.treasures[i] == nil then
            error(" return nil treasures")
            return nil
        else
            __used__ =  st.treasures[i].__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SRoleParameters"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.quizCount = decode_long_signed(buf, __used__)
    if st.quizCount == nil then
        error(" return nil quizCount")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.quizScore = decode_long_signed(buf, __used__)
    if st.quizScore == nil then
        error(" return nil quizScore")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.moral = decode_long_signed(buf, __used__)
    if st.moral == nil then
        error(" return nil moral")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.tidy = decode_long_signed(buf, __used__)
    if st.tidy == nil then
        error(" return nil tidy")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SGmcmdReq"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil cmd")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil cmd")
        return nil
    end
    st.cmd = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SGeneralErrorNtf"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.errcode = decode_long(buf, __used__)
    if st.errcode == nil then
        error(" return nil errcode")
        return nil
    else
        __used__ = __used__ + 4
    end


    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil msg")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil msg")
        return nil
    end
    st.msg = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SEnterReq"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.userid = decode_long(buf, __used__)
    if st.userid == nil then
        error(" return nil userid")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SProtocolTypeRpt"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.type = decode_byte(buf, __used__)
    if st.type == nil then
        error(" return nil type")
        return nil
    else
        __used__ = __used__ + 1
    end


    st.version = decode_byte(buf, __used__)
    if st.version == nil then
        error(" return nil version")
        return nil
    else
        __used__ = __used__ + 1
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SCreateExReq"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil rolename")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil rolename")
        return nil
    end
    st.rolename = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l


    st.professionId = decode_long_signed(buf, __used__)
    if st.professionId == nil then
        error(" return nil professionId")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.vip = decode_long_signed(buf, __used__)
    if st.vip == nil then
        error(" return nil vip")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SBasicData"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.t = decode_long(buf, __used__)
    if st.t == nil then
        error(" return nil t")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.v = decode_long(buf, __used__)
    if st.v == nil then
        error(" return nil v")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SServerStatusReporter"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil servername")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil servername")
        return nil
    end
    st.servername = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l


    st.maxLoad = decode_long(buf, __used__)
    if st.maxLoad == nil then
        error(" return nil maxLoad")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.currentLoad = decode_long(buf, __used__)
    if st.currentLoad == nil then
        error(" return nil currentLoad")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.protocolVer = decode_long(buf, __used__)
    if st.protocolVer == nil then
        error(" return nil protocolVer")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SBasicDataStringNtf"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.count = decode_long(buf, __used__)
    if st.count == nil then
        error(" return nil count")
        return nil
    else
        __used__ = __used__ + 4
    end


    
    if st.count > 32 then
        error(" return nil t for limit:" .. st.count .. " count " .. 32 )
        return nil
    end
    st.t = {}
    for i=1, st.count do
        if  __used__>string.len(buf) + 1 then
            error(" return nil t")
            return nil
        end

        st.t[i] = protocol_decode_lua.decode_SBasicDataString(buf, __used__)
        if st.t[i] == nil then
            error(" return nil t")
            return nil
        else
            __used__ =  st.t[i].__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SGeneralWordsNtf"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil msg")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil msg")
        return nil
    end
    st.msg = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SRegisterRsp"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.errcode = decode_byte(buf, __used__)
    if st.errcode == nil then
        error(" return nil errcode")
        return nil
    else
        __used__ = __used__ + 1
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_STreasureInBag"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.index = decode_long_signed(buf, __used__)
    if st.index == nil then
        error(" return nil index")
        return nil
    else
        __used__ = __used__ + 4
    end


    
    st.t = {}
    for i=1, 1 do
        if  __used__>string.len(buf) + 1 then
            error(" return nil t")
            return nil
        end

        st.t = protocol_decode_lua.decode_STreasure(buf, __used__)
        if st.t == nil then
            error(" return nil t")
            return nil
        else
            __used__ =  st.t.__used__
        end
    end


    st.leftTimeSecond = decode_long_signed(buf, __used__)
    if st.leftTimeSecond == nil then
        error(" return nil leftTimeSecond")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SBindAccountRsp"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.errcode = decode_long(buf, __used__)
    if st.errcode == nil then
        error(" return nil errcode")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SCreateReq"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil rolename")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil rolename")
        return nil
    end
    st.rolename = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l


    st.professionId = decode_long_signed(buf, __used__)
    if st.professionId == nil then
        error(" return nil professionId")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SGetStageRsp"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.totalSize = decode_long(buf, __used__)
    if st.totalSize == nil then
        error(" return nil totalSize")
        return nil
    else
        __used__ = __used__ + 4
    end


    
    st.file = {}
    for i=1, 1 do
        if  __used__>string.len(buf) + 1 then
            error(" return nil file")
            return nil
        end

        st.file = protocol_decode_lua.decode_SStageFile(buf, __used__)
        if st.file == nil then
            error(" return nil file")
            return nil
        else
            __used__ =  st.file.__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SEasyRoleInfo4LoginList"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.count = decode_byte(buf, __used__)
    if st.count == nil then
        error(" return nil count")
        return nil
    else
        __used__ = __used__ + 1
    end


    
    if st.count > 5 then
        error(" return nil easyRoleList for limit:" .. st.count .. " count " .. 5 )
        return nil
    end
    st.easyRoleList = {}
    for i=1, st.count do
        if  __used__>string.len(buf) + 1 then
            error(" return nil easyRoleList")
            return nil
        end

        st.easyRoleList[i] = protocol_decode_lua.decode_SEasyRoleInfo4Login(buf, __used__)
        if st.easyRoleList[i] == nil then
            error(" return nil easyRoleList")
            return nil
        else
            __used__ =  st.easyRoleList[i].__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SLogoffRsp"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SServerLoadFinishNtf"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.temp = decode_long_signed(buf, __used__)
    if st.temp == nil then
        error(" return nil temp")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SBasicDataStringChangeReq"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    
    st.sbdn = {}
    for i=1, 1 do
        if  __used__>string.len(buf) + 1 then
            error(" return nil sbdn")
            return nil
        end

        st.sbdn = protocol_decode_lua.decode_SBasicDataStringNtf(buf, __used__)
        if st.sbdn == nil then
            error(" return nil sbdn")
            return nil
        else
            __used__ =  st.sbdn.__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SBasicDataStringChangeNtf"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    
    st.sbdn = {}
    for i=1, 1 do
        if  __used__>string.len(buf) + 1 then
            error(" return nil sbdn")
            return nil
        end

        st.sbdn = protocol_decode_lua.decode_SBasicDataStringNtf(buf, __used__)
        if st.sbdn == nil then
            error(" return nil sbdn")
            return nil
        else
            __used__ =  st.sbdn.__used__
        end
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SMiscDB"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.shootMonsterCount = decode_long_signed(buf, __used__)
    if st.shootMonsterCount == nil then
        error(" return nil shootMonsterCount")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SStageFile"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.stageId = decode_long(buf, __used__)
    if st.stageId == nil then
        error(" return nil stageId")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.blockId = decode_short(buf, __used__)
    if st.blockId == nil then
        error(" return nil blockId")
        return nil
    else
        __used__ = __used__ + 2
    end


    st.nextBlcokId = decode_short(buf, __used__)
    if st.nextBlcokId == nil then
        error(" return nil nextBlcokId")
        return nil
    else
        __used__ = __used__ + 2
    end


    st.length = decode_short(buf, __used__)
    if st.length == nil then
        error(" return nil length")
        return nil
    else
        __used__ = __used__ + 2
    end


    if st.length > 20480 then
        error(" return nil file for limit:" .. st.length .. " count " .. 20480 )
        return nil
    end
    if st.length + __used__>string.len(buf) + 1 then
        error(" return nil file for limit:" .. st.length .. " buf len " .. string.len(buf))
        return nil
    end
    st.file = string.sub(buf, __used__, __used__+st.length)
    __used__ = __used__ + st.length

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SPackedFileIndex"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil name")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil name")
        return nil
    end
    st.name = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l


    st.startIndex = decode_long(buf, __used__)
    if st.startIndex == nil then
        error(" return nil startIndex")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.endIndex = decode_long(buf, __used__)
    if st.endIndex == nil then
        error(" return nil endIndex")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SStageInfo"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.stageId = decode_long(buf, __used__)
    if st.stageId == nil then
        error(" return nil stageId")
        return nil
    else
        __used__ = __used__ + 4
    end


    if 32 > 32 then
        error(" return nil md5 for limit:" .. 32 .. " count " .. 32 )
        return nil
    end
    if 32 + __used__>string.len(buf) + 1 then
        error(" return nil md5 for limit:" .. 32 .. " buf len " .. string.len(buf))
        return nil
    end
    st.md5 = string.sub(buf, __used__, __used__+32)
    __used__ = __used__ + 32


    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil name")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil name")
        return nil
    end
    st.name = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l


    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil desc")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil desc")
        return nil
    end
    st.desc = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l


    st.size = decode_long(buf, __used__)
    if st.size == nil then
        error(" return nil size")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_STreasure"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.guid = decode_long_signed(buf, __used__)
    if st.guid == nil then
        error(" return nil guid")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.count = decode_long_signed(buf, __used__)
    if st.count == nil then
        error(" return nil count")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.itemId = decode_long_signed(buf, __used__)
    if st.itemId == nil then
        error(" return nil itemId")
        return nil
    else
        __used__ = __used__ + 4
    end


    st.createTime = decode_long_signed(buf, __used__)
    if st.createTime == nil then
        error(" return nil createTime")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end


protocol_decode_lua["decode_SProtocolVersionNtf"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    
    st.v = decode_long(buf, __used__)
    if st.v == nil then
        error(" return nil v")
        return nil
    else
        __used__ = __used__ + 4
    end

    
    st.__used__ = __used__
    return st
end

