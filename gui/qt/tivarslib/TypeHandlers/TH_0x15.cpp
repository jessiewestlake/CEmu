/*
 * Part of tivars_lib_cpp
 * (C) 2015-2018 Adrien "Adriweb" Bertrand
 * https://github.com/adriweb/tivars_lib_cpp
 * License: MIT
 */

#include "TypeHandlers.h"
#include "../tivarslib_utils.h"
#include <regex>

using namespace std;

namespace tivars
{

    data_t TH_0x15::makeDataFromString(const string& str, const options_t& options)
    {
        (void)options;

        bool formatOk = regex_match(str, regex("^([0-9a-fA-F]{2})+$"));

        const size_t length = str.size();
        const size_t bytes  = length / 2;

        if (length == 0 || !formatOk || bytes > 0xFFFF)
        {
            throw invalid_argument("Invalid input string. Needs to be a valid hex data block");
        }

        data_t data = { (uchar)(bytes & 0xFF), (uchar)((bytes >> 8) & 0xFF) };

        for (size_t i = 0; i < length; i += 2)
        {
            data.push_back(hexdec(str.substr(i, 2)));
        }

        return data;
    }

    string TH_0x15::makeStringFromData(const data_t& data, const options_t& options)
    {
        (void)options;

        const size_t byteCount = data.size();
        const size_t lengthExp = (size_t) ((data[0] & 0xFF) + ((data[1] & 0xFF) << 8));
        const size_t lengthDat = byteCount - 2;

        if (lengthExp != lengthDat)
        {
            throw invalid_argument("Invalid data array. Expected " + to_string(lengthExp) + " bytes, got " + to_string(lengthDat));
        }

        string str;

        for (size_t i=2; i<byteCount; i++)
        {
            str += strtoupper(dechex(data[i]));
        }

        return str;
    }
}
