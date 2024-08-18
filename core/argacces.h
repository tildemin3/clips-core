   /*******************************************************/
   /*      "C" Language Integrated Production System      */
   /*                                                     */
   /*             CLIPS Version 6.40  08/25/16            */
   /*                                                     */
   /*             ARGUMENT ACCESS HEADER FILE             */
   /*******************************************************/

/*************************************************************/
/* Purpose: Provides access routines for accessing arguments */
/*   passed to user or system functions defined using the    */
/*   DefineFunction protocol.                                */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*      Brian L. Dantes                                      */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.24: Renamed BOOLEAN macro type to intBool.         */
/*                                                           */
/*            Added IllegalLogicalNameMessage function.      */
/*                                                           */
/*      6.30: Support for long long integers.                */
/*                                                           */
/*            Added const qualifiers to remove C++           */
/*            deprecation warnings.                          */
/*                                                           */
/*            Converted API macros to function calls.        */
/*                                                           */
/*      6.40: Removed LOCALE definition.                     */
/*                                                           */
/*            Pragma once and other inclusion changes.       */
/*                                                           */
/*            Added support for booleans with <stdbool.h>.   */
/*                                                           */
/*            Removed use of void pointers for specific      */
/*            data structures.                               */
/*                                                           */
/*            ALLOW_ENVIRONMENT_GLOBALS no longer supported. */
/*                                                           */
/*            UDF redesign.                                  */
/*                                                           */
/*************************************************************/

#ifndef _H_argacces

#pragma once

#define _H_argacces

#include "expressn.h"
#include "evaluatn.h"
#include "moduldef.h"

   /**
    * @brief Get the logical name from the UDF context.
    * @param context The UDF context.
    * @param defaultLogicalName The default logical name to use if not specified.
    * @return The logical name.
    */
   const char                    *GetLogicalName(UDFContext *,const char *);

   /**
    * @brief Get the file name from the UDF context.
    * @param context The UDF context.
    * @return The file name.
    */
   const char                    *GetFileName(UDFContext *);

   /**
    * @brief Get the construct name from the UDF context.
    * @param context The UDF context.
    * @param functionName The name of the function calling this.
    * @param constructType The type of construct.
    * @return The construct name.
    */
   const char                    *GetConstructName(UDFContext *,const char *,const char *);

   /**
    * @brief Print an error message for an incorrect number of arguments.
    * @param theEnv The environment.
    * @param functionName The name of the function.
    * @param countRelation The relation of the count (EXACTLY, AT_LEAST, NO_MORE_THAN).
    * @param expectedNumber The expected number of arguments.
    */
   void                           ExpectedCountError(Environment *,const char *,int,unsigned int);

   /**
    * @brief Print an error message for failing to open a file.
    * @param theEnv The environment.
    * @param functionName The name of the function.
    * @param fileName The name of the file that couldn't be opened.
    */
   void                           OpenErrorMessage(Environment *,const char *,const char *);

   /**
    * @brief Check if the number of arguments passed to a function is correct.
    * @param theEnv The environment.
    * @param theFunction The function definition.
    * @param argumentCount The actual number of arguments passed.
    * @return True if the argument count is correct, false otherwise.
    */
   bool                           CheckFunctionArgCount(Environment *,struct functionDefinition *,int);

   /**
    * @brief Print an error message for an incorrect argument type.
    * @param theEnv The environment.
    * @param functionName The name of the function.
    * @param whichArg The index of the argument.
    */
   void                           ExpectedTypeError0(Environment *,const char *,unsigned int);

   /**
    * @brief Print an error message for an incorrect argument type, including the expected type.
    * @param theEnv The environment.
    * @param functionName The name of the function.
    * @param whichArg The index of the argument.
    * @param expectedType The expected type of the argument.
    */
   void                           ExpectedTypeError1(Environment *,const char *,unsigned int,const char *);

   /**
    * @brief Print an error message for an incorrect argument type, using the function's argument restriction list.
    * @param theEnv The environment.
    * @param functionName The name of the function.
    * @param whichArg The index of the argument.
    */
   void                           ExpectedTypeError2(Environment *,const char *,unsigned int);

   /**
    * @brief Get the module name from the UDF context.
    * @param context The UDF context.
    * @param whichArgument The index of the argument containing the module name.
    * @param error A pointer to a boolean that will be set to true if an error occurs.
    * @return The module, or NULL if not found or an error occurs.
    */
   Defmodule                     *GetModuleName(UDFContext *,unsigned int,bool *);

   /**
    * @brief Get a fact or instance argument from the UDF context.
    * @param context The UDF context.
    * @param whichArgument The index of the argument.
    * @param returnValue A pointer to a UDFValue to store the result.
    * @return A pointer to the fact or instance, or NULL if an error occurs.
    */
   void                          *GetFactOrInstanceArgument(UDFContext *,unsigned int,UDFValue *);

   /**
    * @brief Print an error message for an illegal logical name.
    * @param theEnv The environment.
    * @param functionName The name of the function.
    */
   void                           IllegalLogicalNameMessage(Environment *,const char *);

#endif

