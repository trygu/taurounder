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

#ifndef ROUNDERCTRL_H
#define	ROUNDERCTRL_H

#include "RProgressListener.h"
#include "RCallback.h"
#include <iostream>
#include <time.h>

//#include "WrapCRP.h"

/* Portable export macro (was __declspec(dllexport), Windows-only). */
#if defined(TAUARGUS_STATIC)
    #define ROUNDER_EXPORT
#elif defined(_WIN32) || defined(__CYGWIN__)
    #define ROUNDER_EXPORT __declspec(dllexport)
#else
    #define ROUNDER_EXPORT __attribute__((visibility("default")))
#endif

class ROUNDER_EXPORT RounderCtrl
//class RounderCtrl
{
private:

public:
    /*RounderCtrl()
    {
    }
    
    ~RounderCtrl()
    {
    }*/
    
    void SetProgressListener(RProgressListener *jProgressListener);
    void SetCallback(RCallback *jCallback);
    void SetDoubleConstant(const int variable, double value);

   /* void SetJJconstantsInt(const int ConstName, const long ConstValue);
    void SetJJconstantsDbl(const int ConstName, const double ConstValue);
    long GetJJconstantsInt(const int ConstName);
    double GetJJconstantsDbl(const int ConstName);
    std::string GetErrorString(int ErrorNumber);
    */
    int DoRound(char *Solver, char *InFileName, double Base, double *UpperBound, double *LowerBound, long Auditing, char *SolutionFile, 
                 char* StatisticsFile, char *LicenseFile, char *LogFile, long MaxTime, long ZeroRestricted, char *NamePathExe, 
                 double *MaxJump, long *NumberJump, double *UsedTime, long *ErrorCode);
    
    std::string GetVersion();
};

#endif	/* ROUNDERCTRL_H */


