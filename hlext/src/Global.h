//
// Created by ryen on 12/23/24.
//

#ifndef GLOBAL_H
#define GLOBAL_H

#define HL_NAME(n) MECore_##n

#include <hl.h>

#define _VECTOR2 _OBJ(_F32 _F32)
#define _VECTOR3 _OBJ(_F32 _F32 _F32)
#define _VECTOR4 _OBJ(_F32 _F32 _F32 _F32)
#define _QUAT _VECTOR4

#endif //GLOBAL_H