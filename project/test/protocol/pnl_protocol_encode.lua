
function encode_long(l)
    local a = l/(0x100*0x100*0x100)%0x100
    local b = l/(0x100*0x100)%0x100
    local c = l/(0x100)%0x100
    local d = l%0x100
    a = math.modf(a, 1)
    b = math.modf(b, 1)
    c = math.modf(c, 1)
    d = math.modf(d, 1)

    return string.char(a,b,c,d)
end

function encode_short(s)
    local a = s/(0x100)%0x100
    local b = s%0x100
    a = math.modf(a, 1)
    b = math.modf(b, 1)
    return string.char(a, b)
end

function encode_byte(b)
    local a = b%0x100
    a = math.modf(a, 1)
    return string.char(a)
end
 
protocol_encode_lua = {}

protocol_encode_lua["encode_SBasicDataEx"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.guid)
    if _s == nil then
        error(" return nil guid")
        return nil
    else
        buf = buf .. _s
    end


    
    for i=1, 1 do
        local _s = protocol_encode_lua.encode_SBasicDataNtf(st.ns)
        if _s == nil then
            error(" return nil ns")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SGetStageReq"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.stageId)
    if _s == nil then
        error(" return nil stageId")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_short(st.blockId)
    if _s == nil then
        error(" return nil blockId")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SProtocolTypeRsp"] = function (st)
    local buf = ""
    
    
    local _s = encode_byte(st.errcode)
    if _s == nil then
        error(" return nil errcode")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SKickNtf"] = function (st)
    local buf = ""
    
    
    
    return buf
end


protocol_encode_lua["encode_SPackedFiles"] = function (st)
    local buf = ""
    
    
    local _s = encode_short(st.count)
    if _s == nil then
        error(" return nil count")
        return nil
    else
        buf = buf .. _s
    end


    
    if st.count > 100 then
        error(" return nil files forlimit" .. st.count .. "count" .. 100)
        return nil
    end
    for i=1, st.count do
        local _s = protocol_encode_lua.encode_SPackedFileIndex(st.files[i])
        if _s == nil then
            error(" return nil files")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SBasicDataString"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.t)
    if _s == nil then
        error(" return nil t")
        return nil
    else
        buf = buf .. _s
    end


    if string.len(st.sv) > 32 then
        error(" return nil sv")
        return nil
    end
    local _s = encode_short(string.len(st.sv))
    if _s == nil then
        error(" return nil sv")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.sv

    
    return buf
end


protocol_encode_lua["encode_SBasicDataNtf"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.count)
    if _s == nil then
        error(" return nil count")
        return nil
    else
        buf = buf .. _s
    end


    
    if st.count > 32 then
        error(" return nil t forlimit" .. st.count .. "count" .. 32)
        return nil
    end
    for i=1, st.count do
        local _s = protocol_encode_lua.encode_SBasicData(st.t[i])
        if _s == nil then
            error(" return nil t")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SRole"] = function (st)
    local buf = ""
    
    
    
    for i=1, 1 do
        local _s = protocol_encode_lua.encode_SBasicRoleInfo(st.roleBasic)
        if _s == nil then
            error(" return nil roleBasic")
            return nil
        end
        buf = buf.._s
    end


    
    for i=1, 1 do
        local _s = protocol_encode_lua.encode_SRoleParameters(st.paraNow)
        if _s == nil then
            error(" return nil paraNow")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SEasyLoginRsp"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.type)
    if _s == nil then
        error(" return nil type")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.errcode)
    if _s == nil then
        error(" return nil errcode")
        return nil
    else
        buf = buf .. _s
    end


    
    for i=1, 1 do
        local _s = protocol_encode_lua.encode_SEasyRoleInfo4LoginList(st.roleList)
        if _s == nil then
            error(" return nil roleList")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SEasyRoleInfo4Login"] = function (st)
    local buf = ""
    
    
    if string.len(st.rolename) > 32 then
        error(" return nil rolename")
        return nil
    end
    local _s = encode_short(string.len(st.rolename))
    if _s == nil then
        error(" return nil rolename")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.rolename


    local _s = encode_long(st.userid)
    if _s == nil then
        error(" return nil userid")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SRegisterReq"] = function (st)
    local buf = ""
    
    
    if string.len(st.account) > 32 then
        error(" return nil account")
        return nil
    end
    local _s = encode_short(string.len(st.account))
    if _s == nil then
        error(" return nil account")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.account


    if string.len(st.pwd) > 32 then
        error(" return nil pwd")
        return nil
    end
    local _s = encode_short(string.len(st.pwd))
    if _s == nil then
        error(" return nil pwd")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.pwd


    if string.len(st.mac) > 32 then
        error(" return nil mac")
        return nil
    end
    local _s = encode_short(string.len(st.mac))
    if _s == nil then
        error(" return nil mac")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.mac

    
    return buf
end


protocol_encode_lua["encode_SBasicRoleInfo"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.userid)
    if _s == nil then
        error(" return nil userid")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.guid)
    if _s == nil then
        error(" return nil guid")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.showLevel)
    if _s == nil then
        error(" return nil showLevel")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.mateid)
    if _s == nil then
        error(" return nil mateid")
        return nil
    else
        buf = buf .. _s
    end


    if string.len(st.macAddress) > 20 then
        error(" return nil macAddress")
        return nil
    end
    local _s = encode_short(string.len(st.macAddress))
    if _s == nil then
        error(" return nil macAddress")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.macAddress


    if string.len(st.rolename) > 64 then
        error(" return nil rolename")
        return nil
    end
    local _s = encode_short(string.len(st.rolename))
    if _s == nil then
        error(" return nil rolename")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.rolename


    local _s = encode_long(st.level)
    if _s == nil then
        error(" return nil level")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.professionId)
    if _s == nil then
        error(" return nil professionId")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.exp)
    if _s == nil then
        error(" return nil exp")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.popularity)
    if _s == nil then
        error(" return nil popularity")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.expTotal)
    if _s == nil then
        error(" return nil expTotal")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.diamond)
    if _s == nil then
        error(" return nil diamond")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.money)
    if _s == nil then
        error(" return nil money")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.exploit)
    if _s == nil then
        error(" return nil exploit")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.vigor)
    if _s == nil then
        error(" return nil vigor")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.vigorMax)
    if _s == nil then
        error(" return nil vigorMax")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.leaderForce)
    if _s == nil then
        error(" return nil leaderForce")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.killingValue)
    if _s == nil then
        error(" return nil killingValue")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.halliconId)
    if _s == nil then
        error(" return nil halliconId")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SLeaveMsg2GMReq"] = function (st)
    local buf = ""
    
    
    if string.len(st.msg) > 256 then
        error(" return nil msg")
        return nil
    end
    local _s = encode_short(string.len(st.msg))
    if _s == nil then
        error(" return nil msg")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.msg

    
    return buf
end


protocol_encode_lua["encode_SCreateRsp"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.errcode)
    if _s == nil then
        error(" return nil errcode")
        return nil
    else
        buf = buf .. _s
    end


    if string.len(st.name) > 32 then
        error(" return nil name")
        return nil
    end
    local _s = encode_short(string.len(st.name))
    if _s == nil then
        error(" return nil name")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.name


    local _s = encode_long(st.userid)
    if _s == nil then
        error(" return nil userid")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SProbeAnswer"] = function (st)
    local buf = ""
    
    
    local _s = encode_byte(st.a)
    if _s == nil then
        error(" return nil a")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_byte(st.b)
    if _s == nil then
        error(" return nil b")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_byte(st.c)
    if _s == nil then
        error(" return nil c")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_byte(st.d)
    if _s == nil then
        error(" return nil d")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SBasicDataChangeReq"] = function (st)
    local buf = ""
    
    
    
    for i=1, 1 do
        local _s = protocol_encode_lua.encode_SBasicDataNtf(st.sbdn)
        if _s == nil then
            error(" return nil sbdn")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SGetRoleInfoRsp"] = function (st)
    local buf = ""
    
    
    
    for i=1, 1 do
        local _s = protocol_encode_lua.encode_SRole(st.role)
        if _s == nil then
            error(" return nil role")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SBasicDataBroadcastNtf"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.guid)
    if _s == nil then
        error(" return nil guid")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.t)
    if _s == nil then
        error(" return nil t")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.v)
    if _s == nil then
        error(" return nil v")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.jerseyId)
    if _s == nil then
        error(" return nil jerseyId")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SGetRoleInfoReq"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.i)
    if _s == nil then
        error(" return nil i")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SBindAccountReq"] = function (st)
    local buf = ""
    
    
    if string.len(st.account) > 32 then
        error(" return nil account")
        return nil
    end
    local _s = encode_short(string.len(st.account))
    if _s == nil then
        error(" return nil account")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.account


    if string.len(st.pwd) > 32 then
        error(" return nil pwd")
        return nil
    end
    local _s = encode_short(string.len(st.pwd))
    if _s == nil then
        error(" return nil pwd")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.pwd

    
    return buf
end


protocol_encode_lua["encode_SGmcmdRsp"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.nouse)
    if _s == nil then
        error(" return nil nouse")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SLogoffReq"] = function (st)
    local buf = ""
    
    
    
    return buf
end


protocol_encode_lua["encode_SEnterRsp"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.errcode)
    if _s == nil then
        error(" return nil errcode")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.roleCount)
    if _s == nil then
        error(" return nil roleCount")
        return nil
    else
        buf = buf .. _s
    end


    
    if st.roleCount > 1 then
        error(" return nil roles forlimit" .. st.roleCount .. "count" .. 1)
        return nil
    end
    for i=1, st.roleCount do
        local _s = protocol_encode_lua.encode_SRole(st.roles[i])
        if _s == nil then
            error(" return nil roles")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SGMAnswerRsp"] = function (st)
    local buf = ""
    
    
    if string.len(st.answer) > 256 then
        error(" return nil answer")
        return nil
    end
    local _s = encode_short(string.len(st.answer))
    if _s == nil then
        error(" return nil answer")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.answer

    
    return buf
end


protocol_encode_lua["encode_SEasyLoginReq"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.type)
    if _s == nil then
        error(" return nil type")
        return nil
    else
        buf = buf .. _s
    end


    if string.len(st.easyAccount) > 128 then
        error(" return nil easyAccount")
        return nil
    end
    local _s = encode_short(string.len(st.easyAccount))
    if _s == nil then
        error(" return nil easyAccount")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.easyAccount

    
    return buf
end


protocol_encode_lua["encode_SLogConsumeDiamond"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.type)
    if _s == nil then
        error(" return nil type")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.gID)
    if _s == nil then
        error(" return nil gID")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.itemID)
    if _s == nil then
        error(" return nil itemID")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SBasicDataChangeNtf"] = function (st)
    local buf = ""
    
    
    
    for i=1, 1 do
        local _s = protocol_encode_lua.encode_SBasicDataNtf(st.sbdn)
        if _s == nil then
            error(" return nil sbdn")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SBasicDataExNtf"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.count)
    if _s == nil then
        error(" return nil count")
        return nil
    else
        buf = buf .. _s
    end


    
    if st.count > 21 then
        error(" return nil updates forlimit" .. st.count .. "count" .. 21)
        return nil
    end
    for i=1, st.count do
        local _s = protocol_encode_lua.encode_SBasicDataEx(st.updates[i])
        if _s == nil then
            error(" return nil updates")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SGetAllStageDescReq"] = function (st)
    local buf = ""
    
    
    
    return buf
end


protocol_encode_lua["encode_SLoadFinishedReq"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.intoScene)
    if _s == nil then
        error(" return nil intoScene")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SGetAllStageDescRsp"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.count)
    if _s == nil then
        error(" return nil count")
        return nil
    else
        buf = buf .. _s
    end


    
    if st.count > 50 then
        error(" return nil stages forlimit" .. st.count .. "count" .. 50)
        return nil
    end
    for i=1, st.count do
        local _s = protocol_encode_lua.encode_SStageInfo(st.stages[i])
        if _s == nil then
            error(" return nil stages")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SProbeNtf"] = function (st)
    local buf = ""
    
    
    local _s = encode_byte(st.a)
    if _s == nil then
        error(" return nil a")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_byte(st.b)
    if _s == nil then
        error(" return nil b")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_byte(st.c)
    if _s == nil then
        error(" return nil c")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_byte(st.d)
    if _s == nil then
        error(" return nil d")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SGlobalNtf"] = function (st)
    local buf = ""
    
    
    local _s = encode_short(st.t)
    if _s == nil then
        error(" return nil t")
        return nil
    else
        buf = buf .. _s
    end


    if string.len(st.msg) > 512 then
        error(" return nil msg")
        return nil
    end
    local _s = encode_short(string.len(st.msg))
    if _s == nil then
        error(" return nil msg")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.msg


    if string.len(st.role) > 64 then
        error(" return nil role")
        return nil
    end
    local _s = encode_short(string.len(st.role))
    if _s == nil then
        error(" return nil role")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.role

    
    return buf
end


protocol_encode_lua["encode_STreasureUpdateNtf"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.count)
    if _s == nil then
        error(" return nil count")
        return nil
    else
        buf = buf .. _s
    end


    
    if st.count > 100 then
        error(" return nil treasures forlimit" .. st.count .. "count" .. 100)
        return nil
    end
    for i=1, st.count do
        local _s = protocol_encode_lua.encode_STreasureInBag(st.treasures[i])
        if _s == nil then
            error(" return nil treasures")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SRoleParameters"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.quizCount)
    if _s == nil then
        error(" return nil quizCount")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.quizScore)
    if _s == nil then
        error(" return nil quizScore")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.moral)
    if _s == nil then
        error(" return nil moral")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.tidy)
    if _s == nil then
        error(" return nil tidy")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SGmcmdReq"] = function (st)
    local buf = ""
    
    
    if string.len(st.cmd) > 64 then
        error(" return nil cmd")
        return nil
    end
    local _s = encode_short(string.len(st.cmd))
    if _s == nil then
        error(" return nil cmd")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.cmd

    
    return buf
end


protocol_encode_lua["encode_SGeneralErrorNtf"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.errcode)
    if _s == nil then
        error(" return nil errcode")
        return nil
    else
        buf = buf .. _s
    end


    if string.len(st.msg) > 512 then
        error(" return nil msg")
        return nil
    end
    local _s = encode_short(string.len(st.msg))
    if _s == nil then
        error(" return nil msg")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.msg

    
    return buf
end


protocol_encode_lua["encode_SEnterReq"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.userid)
    if _s == nil then
        error(" return nil userid")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SProtocolTypeRpt"] = function (st)
    local buf = ""
    
    
    local _s = encode_byte(st.type)
    if _s == nil then
        error(" return nil type")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_byte(st.version)
    if _s == nil then
        error(" return nil version")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SCreateExReq"] = function (st)
    local buf = ""
    
    
    if string.len(st.rolename) > 64 then
        error(" return nil rolename")
        return nil
    end
    local _s = encode_short(string.len(st.rolename))
    if _s == nil then
        error(" return nil rolename")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.rolename


    local _s = encode_long(st.professionId)
    if _s == nil then
        error(" return nil professionId")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.vip)
    if _s == nil then
        error(" return nil vip")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SBasicData"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.t)
    if _s == nil then
        error(" return nil t")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.v)
    if _s == nil then
        error(" return nil v")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SServerStatusReporter"] = function (st)
    local buf = ""
    
    
    if string.len(st.servername) > 64 then
        error(" return nil servername")
        return nil
    end
    local _s = encode_short(string.len(st.servername))
    if _s == nil then
        error(" return nil servername")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.servername


    local _s = encode_long(st.maxLoad)
    if _s == nil then
        error(" return nil maxLoad")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.currentLoad)
    if _s == nil then
        error(" return nil currentLoad")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.protocolVer)
    if _s == nil then
        error(" return nil protocolVer")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SBasicDataStringNtf"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.count)
    if _s == nil then
        error(" return nil count")
        return nil
    else
        buf = buf .. _s
    end


    
    if st.count > 32 then
        error(" return nil t forlimit" .. st.count .. "count" .. 32)
        return nil
    end
    for i=1, st.count do
        local _s = protocol_encode_lua.encode_SBasicDataString(st.t[i])
        if _s == nil then
            error(" return nil t")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SGeneralWordsNtf"] = function (st)
    local buf = ""
    
    
    if string.len(st.msg) > 512 then
        error(" return nil msg")
        return nil
    end
    local _s = encode_short(string.len(st.msg))
    if _s == nil then
        error(" return nil msg")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.msg

    
    return buf
end


protocol_encode_lua["encode_SRegisterRsp"] = function (st)
    local buf = ""
    
    
    local _s = encode_byte(st.errcode)
    if _s == nil then
        error(" return nil errcode")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_STreasureInBag"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.index)
    if _s == nil then
        error(" return nil index")
        return nil
    else
        buf = buf .. _s
    end


    
    for i=1, 1 do
        local _s = protocol_encode_lua.encode_STreasure(st.t)
        if _s == nil then
            error(" return nil t")
            return nil
        end
        buf = buf.._s
    end


    local _s = encode_long(st.leftTimeSecond)
    if _s == nil then
        error(" return nil leftTimeSecond")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SBindAccountRsp"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.errcode)
    if _s == nil then
        error(" return nil errcode")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SCreateReq"] = function (st)
    local buf = ""
    
    
    if string.len(st.rolename) > 64 then
        error(" return nil rolename")
        return nil
    end
    local _s = encode_short(string.len(st.rolename))
    if _s == nil then
        error(" return nil rolename")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.rolename


    local _s = encode_long(st.professionId)
    if _s == nil then
        error(" return nil professionId")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SGetStageRsp"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.totalSize)
    if _s == nil then
        error(" return nil totalSize")
        return nil
    else
        buf = buf .. _s
    end


    
    for i=1, 1 do
        local _s = protocol_encode_lua.encode_SStageFile(st.file)
        if _s == nil then
            error(" return nil file")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SEasyRoleInfo4LoginList"] = function (st)
    local buf = ""
    
    
    local _s = encode_byte(st.count)
    if _s == nil then
        error(" return nil count")
        return nil
    else
        buf = buf .. _s
    end


    
    if st.count > 5 then
        error(" return nil easyRoleList forlimit" .. st.count .. "count" .. 5)
        return nil
    end
    for i=1, st.count do
        local _s = protocol_encode_lua.encode_SEasyRoleInfo4Login(st.easyRoleList[i])
        if _s == nil then
            error(" return nil easyRoleList")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SLogoffRsp"] = function (st)
    local buf = ""
    
    
    
    return buf
end


protocol_encode_lua["encode_SServerLoadFinishNtf"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.temp)
    if _s == nil then
        error(" return nil temp")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SBasicDataStringChangeReq"] = function (st)
    local buf = ""
    
    
    
    for i=1, 1 do
        local _s = protocol_encode_lua.encode_SBasicDataStringNtf(st.sbdn)
        if _s == nil then
            error(" return nil sbdn")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SBasicDataStringChangeNtf"] = function (st)
    local buf = ""
    
    
    
    for i=1, 1 do
        local _s = protocol_encode_lua.encode_SBasicDataStringNtf(st.sbdn)
        if _s == nil then
            error(" return nil sbdn")
            return nil
        end
        buf = buf.._s
    end

    
    return buf
end


protocol_encode_lua["encode_SMiscDB"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.shootMonsterCount)
    if _s == nil then
        error(" return nil shootMonsterCount")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SStageFile"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.stageId)
    if _s == nil then
        error(" return nil stageId")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_short(st.blockId)
    if _s == nil then
        error(" return nil blockId")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_short(st.nextBlcokId)
    if _s == nil then
        error(" return nil nextBlcokId")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_short(st.length)
    if _s == nil then
        error(" return nil length")
        return nil
    else
        buf = buf .. _s
    end


    if st.length > 20480 then
        error(" return nil file forlimit" .. st.length .."count" .. 20480)
        return nil
    end
    for i=1, st.length do
        local _s = encode_byte(st.file[i])
        if _s == nil then
            error(" return nil file")
            return nil
        end
        buf = buf.._s
    end


    
    return buf
end


protocol_encode_lua["encode_SPackedFileIndex"] = function (st)
    local buf = ""
    
    
    if string.len(st.name) > 128 then
        error(" return nil name")
        return nil
    end
    local _s = encode_short(string.len(st.name))
    if _s == nil then
        error(" return nil name")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.name


    local _s = encode_long(st.startIndex)
    if _s == nil then
        error(" return nil startIndex")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.endIndex)
    if _s == nil then
        error(" return nil endIndex")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SStageInfo"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.stageId)
    if _s == nil then
        error(" return nil stageId")
        return nil
    else
        buf = buf .. _s
    end


    if 32 > 32 then
        error(" return nil md5 forlimit" .. 32 .."count" .. 32)
        return nil
    end
    for i=1, 32 do
        local _s = encode_byte(st.md5[i])
        if _s == nil then
            error(" return nil md5")
            return nil
        end
        buf = buf.._s
    end



    if string.len(st.name) > 64 then
        error(" return nil name")
        return nil
    end
    local _s = encode_short(string.len(st.name))
    if _s == nil then
        error(" return nil name")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.name


    if string.len(st.desc) > 256 then
        error(" return nil desc")
        return nil
    end
    local _s = encode_short(string.len(st.desc))
    if _s == nil then
        error(" return nil desc")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.desc


    local _s = encode_long(st.size)
    if _s == nil then
        error(" return nil size")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_STreasure"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.guid)
    if _s == nil then
        error(" return nil guid")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.count)
    if _s == nil then
        error(" return nil count")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.itemId)
    if _s == nil then
        error(" return nil itemId")
        return nil
    else
        buf = buf .. _s
    end


    local _s = encode_long(st.createTime)
    if _s == nil then
        error(" return nil createTime")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


protocol_encode_lua["encode_SProtocolVersionNtf"] = function (st)
    local buf = ""
    
    
    local _s = encode_long(st.v)
    if _s == nil then
        error(" return nil v")
        return nil
    else
        buf = buf .. _s
    end

    
    return buf
end


