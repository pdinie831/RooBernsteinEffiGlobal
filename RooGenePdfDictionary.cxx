// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME RooGenePdfDictionary

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "RooGenePdf.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_RooGenePdf(void *p = 0);
   static void *newArray_RooGenePdf(Long_t size, void *p);
   static void delete_RooGenePdf(void *p);
   static void deleteArray_RooGenePdf(void *p);
   static void destruct_RooGenePdf(void *p);
   static void streamer_RooGenePdf(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooGenePdf*)
   {
      ::RooGenePdf *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooGenePdf >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RooGenePdf", ::RooGenePdf::Class_Version(), "RooGenePdf.h", 19,
                  typeid(::RooGenePdf), DefineBehavior(ptr, ptr),
                  &::RooGenePdf::Dictionary, isa_proxy, 16,
                  sizeof(::RooGenePdf) );
      instance.SetNew(&new_RooGenePdf);
      instance.SetNewArray(&newArray_RooGenePdf);
      instance.SetDelete(&delete_RooGenePdf);
      instance.SetDeleteArray(&deleteArray_RooGenePdf);
      instance.SetDestructor(&destruct_RooGenePdf);
      instance.SetStreamerFunc(&streamer_RooGenePdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooGenePdf*)
   {
      return GenerateInitInstanceLocal((::RooGenePdf*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RooGenePdf*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr RooGenePdf::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RooGenePdf::Class_Name()
{
   return "RooGenePdf";
}

//______________________________________________________________________________
const char *RooGenePdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooGenePdf*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RooGenePdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooGenePdf*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooGenePdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooGenePdf*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooGenePdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooGenePdf*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void RooGenePdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooGenePdf.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      RooAbsPdf::Streamer(R__b);
      _x.Streamer(R__b);
      _y.Streamer(R__b);
      _z.Streamer(R__b);
      _coefList.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, RooGenePdf::IsA());
   } else {
      R__c = R__b.WriteVersion(RooGenePdf::IsA(), kTRUE);
      RooAbsPdf::Streamer(R__b);
      _x.Streamer(R__b);
      _y.Streamer(R__b);
      _z.Streamer(R__b);
      _coefList.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooGenePdf(void *p) {
      return  p ? new(p) ::RooGenePdf : new ::RooGenePdf;
   }
   static void *newArray_RooGenePdf(Long_t nElements, void *p) {
      return p ? new(p) ::RooGenePdf[nElements] : new ::RooGenePdf[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooGenePdf(void *p) {
      delete ((::RooGenePdf*)p);
   }
   static void deleteArray_RooGenePdf(void *p) {
      delete [] ((::RooGenePdf*)p);
   }
   static void destruct_RooGenePdf(void *p) {
      typedef ::RooGenePdf current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_RooGenePdf(TBuffer &buf, void *obj) {
      ((::RooGenePdf*)obj)->::RooGenePdf::Streamer(buf);
   }
} // end of namespace ROOT for class ::RooGenePdf

namespace {
  void TriggerDictionaryInitialization_RooGenePdfDictionary_Impl() {
    static const char* headers[] = {
"RooGenePdf.h",
0
    };
    static const char* includePaths[] = {
"/usr/local/root-6.04.18/include/root",
"/gwpool/users/dini/CMSKStarMuMu/RooBernsteinEffi/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(Your description goes here...)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$RooGenePdf.h")))  RooGenePdf;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "RooGenePdf.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"RooGenePdf", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("RooGenePdfDictionary",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_RooGenePdfDictionary_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_RooGenePdfDictionary_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_RooGenePdfDictionary() {
  TriggerDictionaryInitialization_RooGenePdfDictionary_Impl();
}
