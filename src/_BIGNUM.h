#ifndef MONTGOMERY_H
#define MONTGOMERY_H

#include <gmp.h>

struct BigNumber
{
   mpz_t Number;
};
typedef BigNumber BIG;

#endif