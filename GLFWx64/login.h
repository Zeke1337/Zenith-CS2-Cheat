#pragma once

#include <iostream>
#include <string>
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

#pragma comment(lib, "winhttp.lib")

std::string ConvertBSTRToString(BSTR bstr);
std::string optain();


