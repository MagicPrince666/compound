/**
 * @file analyze_bin.h
 * @author your name (you@domain.com)
 * @brief 分析二进制
 * @version 0.1
 * @date 2021-12-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <fstream>

class AnalyzeBin
{
public:
    AnalyzeBin(std::string binary_file);
    ~AnalyzeBin();

private:
    bool Start();

    std::ifstream binary_;
};