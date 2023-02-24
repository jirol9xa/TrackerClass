#pragma once

#define LOC_INFO(param)                                                                            \
    { __LINE__, __func__, __FILE__, #param }
#define USE(param) param.setLastUseLoc(LOC_INFO(param))
#define CREATE(param) Tracker param(LOC_INFO(param))
#define CREATE_AND_INIT(name, value) Tracker name(LOC_INFO(name), value)
#define CREATE_AND_INIT_TMP_OBJ(name, value)
