   /*******************************************************/
   /*      "C" Language Integrated Production System      */
   /*                                                     */
   /*             CLIPS Version 6.40  10/01/16            */
   /*                                                     */
   /*                 BLOAD HEADER FILE                   */
   /*******************************************************/

/*************************************************************/
/* Purpose:                                                  */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*      Brian L. Dantes                                      */
/*                                                           */
/* Contributing Programmer(s):                               */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.24: Renamed BOOLEAN macro type to intBool.         */
/*                                                           */
/*      6.30: Borland C (IBM_TBC) and Metrowerks CodeWarrior */
/*            (MAC_MCW, IBM_MCW) are no longer supported.    */
/*                                                           */
/*            Changed integer type/precision.                */
/*                                                           */
/*            Added const qualifiers to remove C++           */
/*            deprecation warnings.                          */
/*                                                           */
/*            Converted API macros to function calls.        */
/*                                                           */
/*      6.31: Data sizes written to binary files for         */
/*            validation when loaded.                        */
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

#ifndef _H_bload

#pragma once

#define _H_bload

#include "utility.h"
#include "extnfunc.h"
#include "exprnbin.h"
#include "symbol.h"
#include "sysdep.h"
#include "symblbin.h"

#define BLOAD_DATA 38

/**
 * @struct bloadData
 * @brief Structure containing data related to binary loading.
 */
struct bloadData
  {
   const char *BinaryPrefixID;
   const char *BinaryVersionID;
   char *BinarySizes;
   struct functionDefinition **FunctionArray;
   bool BloadActive;
   struct voidCallFunctionItem *BeforeBloadFunctions;
   struct voidCallFunctionItem *AfterBloadFunctions;
   struct boolCallFunctionItem *ClearBloadReadyFunctions;
   struct voidCallFunctionItem *AbortBloadFunctions;
  };

#define BloadData(theEnv) ((struct bloadData *) GetEnvironmentData(theEnv,BLOAD_DATA))

#define FunctionPointer(i) ((((i) == ULONG_MAX) ? NULL : BloadData(theEnv)->FunctionArray[i]))

   /**
    * @brief Initialize the binary load data.
    * @param theEnv The environment.
    */
   void                    InitializeBloadData(Environment *);

   /**
    * @brief Execute the bload command.
    * @param theEnv The environment.
    * @param context The UDF context.
    * @param returnValue The return value.
    */
   void                    BloadCommand(Environment *,UDFContext *,UDFValue *);

   /**
    * @brief Load a binary file.
    * @param theEnv The environment.
    * @param fileName The name of the file to load.
    * @return True if the load was successful, false otherwise.
    */
   bool                    Bload(Environment *,const char *);

   /**
    * @brief Load and refresh binary data.
    * @param theEnv The environment.
    * @param objcnt The number of objects to load.
    * @param objsz The size of each object.
    * @param objupdate Function to update each object.
    */
   void                    BloadandRefresh(Environment *,unsigned long,size_t,void (*)(Environment *,void *,unsigned long));

   /**
    * @brief Check if binary data is loaded.
    * @param theEnv The environment.
    * @return True if binary data is loaded, false otherwise.
    */
   bool                    Bloaded(Environment *);

   /**
    * @brief Add a function to be called before binary loading.
    * @param theEnv The environment.
    * @param name The name of the function.
    * @param func The function to call.
    * @param priority The priority of the function.
    * @param context The context to pass to the function.
    */
   void                    AddBeforeBloadFunction(Environment *,const char *,VoidCallFunction *,int,void *);

   /**
    * @brief Add a function to be called after binary loading.
    * @param theEnv The environment.
    * @param name The name of the function.
    * @param func The function to call.
    * @param priority The priority of the function.
    * @param context The context to pass to the function.
    */
   void                    AddAfterBloadFunction(Environment *,const char *,VoidCallFunction *,int,void *);

   /**
    * @brief Add a function to check if binary loading is ready to be cleared.
    * @param theEnv The environment.
    * @param name The name of the function.
    * @param func The function to call.
    * @param priority The priority of the function.
    * @param context The context to pass to the function.
    */
   void                    AddClearBloadReadyFunction(Environment *,const char *,BoolCallFunction *,int,void *);

   /**
    * @brief Add a function to be called if binary loading is aborted.
    * @param theEnv The environment.
    * @param name The name of the function.
    * @param func The function to call.
    * @param priority The priority of the function.
    * @param context The context to pass to the function.
    */
   void                    AddAbortBloadFunction(Environment *,const char *,VoidCallFunction *,int,void *);

   /**
    * @brief Print an error message indicating that a construct cannot be loaded with binary load active.
    * @param theEnv The environment.
    * @param constructName The name of the construct.
    */
   void                    CannotLoadWithBloadMessage(Environment *,const char *);

#endif

