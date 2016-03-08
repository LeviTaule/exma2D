////////////////////////////////////////////////////////////////////////////////
//
// ExMa2D - tiny EXternal MAth library for 2D
// Copyright (c) 2016 Levi Taule
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef VERSION_HPP
#define VERSION_HPP

#define EXMA_MAJOR 0
#define EXMA_MINOR 2
#define EXMA_PATCH 1

namespace exma { namespace version {
constexpr unsigned int major = EXMA_MAJOR;
constexpr unsigned int minor = EXMA_MINOR;
constexpr unsigned int patch = EXMA_PATCH;
}}
#endif