/*
* Argus Open Source
* Software to apply Statistical Disclosure Control techniques
* 
* Copyright 2014 Statistics Netherlands
* 
* This program is free software; you can redistribute it and/or 
* modify it under the terms of the European Union Public Licence 
* (EUPL) version 1.1, as published by the European Commission.
* 
* You can find the text of the EUPL v1.1 on
* https://joinup.ec.europa.eu/software/page/eupl/licence-eupl
* 
* This software is distributed on an "AS IS" basis without 
* warranties or conditions of any kind, either express or implied.
*/

#include "RounderCtrl.h"
#include "WrapCRP.h"
#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define JJZERO          101
#define JJINF           102
#define JJMINVIOLA      103
#define JJMAXSLACK      104
#define JJMAXTIME	105

///////////////////////////////////////////////////////////////////////
// Private functions
///////////////////////////////////////////////////////////////////////

static RCallback* m_Callback = NULL;
static RProgressListener* m_ProgressListener = NULL;

void RounderCtrl::SetDoubleConstant(const int variable, double value)
{
    CRPSetDoubleConstant(variable,value);
}

void RounderCtrl::SetCallback(RCallback* jCallback)
{
    m_Callback = jCallback;
}

void RounderCtrl::SetProgressListener(RProgressListener* jProgressListener)
{
    m_ProgressListener = jProgressListener;
}

void TAUmessage(double lb, double ub, int nodecount, int nodeleft)
{
    if (m_ProgressListener != NULL)
    {
        m_ProgressListener->UpdateLowerBound(lb);
        m_ProgressListener->UpdateUpperBound(ub);
        m_ProgressListener->UpdateNumberClosedSubProb(nodecount);
        m_ProgressListener->UpdateNumberOpenSubProb(nodeleft);
    }
}

int TAUextratime()
{ 
	return m_Callback->SetExtraTime();
}

int RounderCtrl::DoRound(char *Solver, char *InFileName, double Base, double *UpperBound, double *LowerBound, long Auditing, char *SolutionFile, 
                          char* StatisticsFile, char *LicenseFile, char *LogFile, long MaxTime, long ZeroRestricted, char *NamePathExe, 
                          double *MaxJump, long *NumberJump, double *UsedTime, long *ErrorCode)
{
    int res;
    CRPsetfunctions( &TAUmessage, &TAUextratime ); 
    res = do_round(Solver, InFileName, Base, UpperBound, LowerBound, Auditing, 
                   SolutionFile, StatisticsFile, LicenseFile, LogFile, 
                   MaxTime, ZeroRestricted, NamePathExe, MaxJump, NumberJump, UsedTime, ErrorCode);
    return res;
}

std::string RounderCtrl::GetVersion(){
    return ROUNDERVERSION;
}
