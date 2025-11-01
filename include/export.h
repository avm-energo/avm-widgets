#pragma once

#include <QtCore/qglobal.h>

#if defined(WD_EXPORTS)
#define WD_EXPORT Q_DECL_EXPORT
#elif defined(WD_IMPORTS)
#define WD_EXPORT Q_DECL_IMPORT
#else
#define WD_EXPORT
#endif
