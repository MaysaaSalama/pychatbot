#ifndef _TESTINGH
#define _TESTINGH
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

#define TESTING_REPEATALLOWED 1000

// simple
#define TRACE_BASIC 1	
#define TRACE_MATCH 2
#define TRACE_VARIABLE 4

// mild
#define TRACE_PREPARE 8
#define TRACE_OUTPUT 16
#define TRACE_PATTERN 16

// deep
#define TRACE_HIERARCHY 32
#define TRACE_INFER 64
#define TRACE_SUBSTITUTE 128
#define TRACE_FACTCREATE 256
#define TRACE_VARIABLESET 512
// #define NO_TRACE 1024 // control on a topic 
#define TRACE_USER 2048
#define TRACE_POS 4096
#define TRACE_QUERY 8192
#define TRACE_TCP 16384

// codes returned from :command
#define COMMANDED 0
#define NOPROCESS 1
#define BEGINANEW 2
#define OUTPUTASGIVEN 3

// values of the auto testing
#define OKTEST 1
#define WHYTEST 2

#ifndef DISCARDTESTING

typedef void (*COMMANDPTR)(char* input);

typedef struct CommandInfo 
{
	const char* word;			// dictionary word entry
	COMMANDPTR fn;				// function to use to get it
	const char* comment;		// what to say about it
	bool debugger;				// can debugger use this command
} CommandInfo;

extern CommandInfo commandSet[];

void InitCommandSystem();
int Command(char* input,char* output);
int CountSet(WORDP D,unsigned int baseStamp);
void CopyFile2File(const char* newname,const char* oldname,bool autoNumber);

void Sortit(char* name,int oneline);
void SortTopic(WORDP D,uint64 junk);
void SortTopic0(WORDP D,uint64 junk);

#endif

int DoCommand(char* input,char* output,bool authorize=true);

#endif
