/**
 * @file example.h
 * @author Shihao Tian (shihao.tian@outlook.com)
 * @brief Examples
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

typedef int (*fn)(int argc, char** argv);

extern int TestBlob(int argc, char** argv);
extern int TestBlobPtr(int argc, char** argv);
extern int TestScreen(int argc, char** argv);
