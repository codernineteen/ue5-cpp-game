// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(CppGame, Log, All);
#define CGLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
//Verbosity for log level
#define CGLOG_S(Verbosity) UE_LOG(CppGame, Verbosity, TEXT("%s"), *CGLOG_CALLINFO) // file name and function in which a specific code is located
#define CGLOG(Verbosity, Format, ...) UE_LOG(CppGame, Verbosity, TEXT("%s%s"), *CGLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__)) // CGLOG_S + more info with type string

#define CGCHECK(Expr, ...) { if(!(Expr)) {CGLOG(Error, TEXT("ASSERTION: %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; }}

