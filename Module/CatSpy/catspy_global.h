#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CATSPY_LIB)
#  define CATSPY_EXPORT Q_DECL_EXPORT
# else
#  define CATSPY_EXPORT Q_DECL_IMPORT
# endif
#else
# define CATSPY_EXPORT
#endif
