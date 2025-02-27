#pragma once

#ifdef _WIN32

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <DirectXColors.h>
#include <DirectXMath.h>

#include <comdef.h>

#endif

#include <array>

#include <array>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <numbers>
#include <set>
#include <span>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#ifdef _WIN32

#include "Error.h"

#endif

using namespace DirectX; // for XMFLOAT3 etc.
