#ifndef _OUTPUTPROCESSH_
#define _OUTPUTPROCESSH_
#ifdef INFORMATION
Copyright (C) 2011-2013 by Bruce Wilcox

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#endif

#include "common.h"

#define CHOICE_LIMIT 100

extern unsigned int currentOutputLimit;
extern char* currentOutputBase;
extern char* currentRuleOutputBase;
extern unsigned int outputNest;

// styles of output
char* StdIntOutput(int n);
char* StdFloatOutput(float n);
void ReformatString(char* buffer,char* word,unsigned int controls = 0);

// output buffer management
void AllocateOutputBuffer();
void FreeOutputBuffer();
void PushOutputBuffers();
void PopOutputBuffers();
void ResetOutput();

// ways to generate output
char* ReadCommandArg(char* ptr, char* answer,unsigned int &result,unsigned int control = 0);
char* ReadShortCommandArg(char* ptr, char* buffer,unsigned int& result,unsigned int control = 0);
char* Output(char* ptr,char* buffer,unsigned int &result,int controls = 0);
char* FreshOutput(char* ptr,char* buffer,unsigned int &result,int controls = 0,unsigned limit = maxBufferSize);

#endif
