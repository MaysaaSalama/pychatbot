#ifndef _TOPICSYSTEMH
#define _TOPICSYSTEMH

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

#define NO_REJOINDER -1   
#define BLOCKED_REJOINDER -2 

//   kinds of top level rules
#define QUESTION '?'
#define STATEMENT 's'
#define STATEMENT_QUESTION 'u'
#define RANDOM_GAMBIT   'r' 
#define GAMBIT   't'

#define ENDUNIT '`'				// marks end of a rule in compiled script

#define USED_CODES 75			// Encode/Decode is base 75
#define ENDUNITTEXT "`000 "		// script compile rule closing sequence
#define JUMP_OFFSET 4			//   immediately after any ` are 3 characters of jump info, then either  "space letter :" or "space null"
#define MAX_JUMP_OFFSET (USED_CODES*USED_CODES*USED_CODES) 

#define MAX_REFERENCE_TOPICS 1000	// how many topics a sentence can refer to at once

#define SAVEOLDCONTEXT() 	int oldRuleID = currentRuleID; unsigned int oldTopic = currentTopicID; char* oldRule = currentRule; unsigned int oldRuleTopic = currentRuleTopic;

#define RESTOREOLDCONTEXT() currentRuleID = oldRuleID; currentTopicID = oldTopic; currentRule = oldRule; currentRuleTopic = oldRuleTopic;

// decompose a currentRuleID into its pieces
#define TOPLEVELID(x) ((unsigned int) (x & 0x0000ffff))
#define REJOINDERID(x) ((unsigned int) (x >> 16))
#define MAKE_REJOINDERID(x) (x << 16)
#define ONE_REJOINDER 0x00010000

// decompose RULEMAX info into gambits and top level rules
#define MAKE_GAMBIT_MAX(x) (x << 16)
#define GAMBIT_MAX(x) (x >> 16)
#define RULE_MAX(x) (x & 0x0000ffff)

// used by FindNextRule
#define NEXTRULE -1				// any responder,gambit,rejoinder
#define NEXTTOPLEVEL 2			// only responders and gambits

#define NOMORERULES 0x0fffffff		// finished walking a rule index map

#define MAX_TOPIC_STACK 50

extern bool stats;
extern unsigned int ruleCount;

extern char timeStamp0[20];
extern char timeStamp1[20];
extern char buildStamp0[150];
extern char buildStamp1[150];

extern bool ruleErased;
extern unsigned int* topicDebugMap;

extern unsigned int numberOfTopics; 
extern unsigned int lastTopic;		
extern unsigned int duplicateCount;
extern unsigned int xrefCount;

extern unsigned int currentTopicID;
extern char* currentRule;	
extern int currentRuleID;
extern int currentReuseID;
extern int currentRuleTopic;
extern bool debugTopic;

extern int outputRejoinderRuleID;
extern int outputRejoinderTopic;
extern int inputRejoinderRuleID;
extern int inputRejoinderTopic;

extern unsigned int** gambitTagMap;
extern unsigned int topicIndex,pendingTopicIndex;
extern unsigned int topicStack[MAX_TOPIC_STACK+1];
extern unsigned int** ruleOffsetMap;
extern unsigned int* topicMaxRule;
extern unsigned int pendingTopicList[MAX_TOPIC_STACK+1];
extern unsigned int* topicFlagsMap;
extern unsigned int* topicLastGambittedMap;
extern unsigned int* topicLastResponderedMap;
extern unsigned int* topicLastRejoinderedMap;

unsigned int ProcessRuleOutput(char* rule, unsigned int id,char* buffer);
unsigned int TestRule(int responderID,char* ptr,char* buffer);
unsigned int PerformTopic(int active,char* buffer);
unsigned int FindTypedResponse(char type,char* buffer,unsigned int& id);
bool Repeatable(char* rule);
void ResetTopicReply();
void SetRejoinder(char* rule);
void SetErase(bool force = false);
void UndoErase(char* ptr,unsigned int topic,unsigned int id);
void AddKeep(char* ptr);

int PushTopic(unsigned int topic);
void PopTopic();

unsigned int DoOutput(char* buffer,char* rule, unsigned int id);

// encoding
void DummyEncode(char* &data);
void Encode(unsigned int val,char* &ptr,bool single = false);
unsigned int Decode(char* data,bool single = false);
char* FullEncode(uint64 val,char* ptr);
uint64 FullDecode(char* data);

// data accessors
unsigned int TopicUsedCount(unsigned int topic);
void GetActiveTopicName(char* buffer);
unsigned int FindTopicIDByName(char* request);
char* FindNextRule(signed char level, char* at,int& id);
int GetTopicFlags(unsigned int topic);
char* GetRuleTag(unsigned int& topic,int& id,char* tag);
char* GetRule(unsigned int topic, int id);
char* GetLabelledRule(unsigned int& topic, char* word,char* arg2,bool &fulllabel, bool& crosstopic,int& id);
int HasGambits(unsigned int topic);
char* FindNextLabel(unsigned int topic,char* label, char* ptr,int &id,bool alwaysAllowed);
char* RuleBefore(unsigned int topic,char* rule);
char* GetTopicFile(unsigned int topic);

bool TopLevelQuestion(char* word);
bool TopLevelStatement(char* word);
bool TopLevelGambit(char* word);
bool Rejoinder(char* word);

char* GetLabel(char* rule,char* label);
char* GetPattern(char* rule,char* label,char* pattern); // returns start of output and modified pattern
char* GetOutputCopy(char* ptr); // returns copy of output only
bool TopLevelRule(char* word);
char* GetTopicName(unsigned int topic,bool actual = true);
char* GetTopicData(unsigned int topic);
void SetTopicData(unsigned int topic,char* data);
bool BlockedBotAccess(unsigned int topic);

bool SetRuleDisableMark(unsigned int topic, unsigned int id);
void ClearRuleDisableMark(unsigned int topic,unsigned int id);
bool UsableRule(unsigned int topic,unsigned int n);

void AddRepeatable(char* ptr);
void AddTopicFlag(unsigned int topic, unsigned int flag);
void RemoveTopicFlag(unsigned int topic, unsigned int flag);

void SetTopicDebugMark(unsigned int topic,unsigned char val);
void SetDebugRuleMark(unsigned int topic,unsigned int id);
char* ShowRule(char* rule);
void DisplayTopicFlags(unsigned int topic);

// bulk topic I/O
char* WriteTopicData(char* ptr);
bool ReadTopicData();

// general topic system control
void LoadTopicSystem();
void ResetTopicSystem();
void ResetTopics();
void ResetTopic(unsigned int id);
void InitKeywords(const char* name,uint64 build,bool mark=false,bool concept=true);

// Interesting topics
unsigned int GetPendingTopicUnchanged();
void AddPendingTopic(unsigned int topic);
bool RemovePendingTopic(unsigned int topic);
void ClearPendingTopics();
void PendingTopics(int set);
char* ShowPendingTopics();
bool IsCurrentTopic(unsigned int topic);

#endif
