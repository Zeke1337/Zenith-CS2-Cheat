#pragma once
#include <string>
#include "proc.h"
#include <windows.h>
#include <winhttp.h>
#include <iostream>
#include <string>
#include "login.h"

std::string SendPostRequest(const std::wstring& server, const std::wstring& path, const std::string& data);
bool valid();