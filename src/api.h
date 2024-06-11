#pragma once

#if defined _WIN32 || defined __CYGWIN__
#  define MinimumJerkController_DLLIMPORT __declspec(dllimport)
#  define MinimumJerkController_DLLEXPORT __declspec(dllexport)
#  define MinimumJerkController_DLLLOCAL
#else
// On Linux, for GCC >= 4, tag symbols using GCC extension.
#  if __GNUC__ >= 4
#    define MinimumJerkController_DLLIMPORT __attribute__((visibility("default")))
#    define MinimumJerkController_DLLEXPORT __attribute__((visibility("default")))
#    define MinimumJerkController_DLLLOCAL __attribute__((visibility("hidden")))
#  else
// Otherwise (GCC < 4 or another compiler is used), export everything.
#    define MinimumJerkController_DLLIMPORT
#    define MinimumJerkController_DLLEXPORT
#    define MinimumJerkController_DLLLOCAL
#  endif // __GNUC__ >= 4
#endif // defined _WIN32 || defined __CYGWIN__

#ifdef MinimumJerkController_STATIC
// If one is using the library statically, get rid of
// extra information.
#  define MinimumJerkController_DLLAPI
#  define MinimumJerkController_LOCAL
#else
// Depending on whether one is building or using the
// library define DLLAPI to import or export.
#  ifdef MinimumJerkController_EXPORTS
#    define MinimumJerkController_DLLAPI MinimumJerkController_DLLEXPORT
#  else
#    define MinimumJerkController_DLLAPI MinimumJerkController_DLLIMPORT
#  endif // MinimumJerkController_EXPORTS
#  define MinimumJerkController_LOCAL MinimumJerkController_DLLLOCAL
#endif // MinimumJerkController_STATIC
