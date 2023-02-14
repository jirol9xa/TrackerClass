#pragma once

#define LOC_INFO                                                               \
  { __LINE__, __func__, __FILE__ }
#define USE(param) param.setLastUseLoc(LOC_INFO)
#define CREATE(param) Tracker param(LOC_INFO)
#define CREATE_AND_INIT(name, value) Tracker name(LOC_INFO, value)
