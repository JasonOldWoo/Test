#include <stdint.h>
#include <iostream>

typedef int16_t ElemMeta_t;
typedef char ElemType_t;
const int kElemSize = 8;
const int kElemLbits = 0xff;

ElemType_t ElemCtrl_getType(ElemMeta_t desc)
{return (ElemType_t) (desc >> kElemSize);}
ElemType_t ElemCtrl_getOffset(ElemMeta_t desc)
{return (ElemType_t) (desc & kElemLbits);}
ElemMeta_t ElemCtrl_makeDesc(ElemType_t t, ElemType_t p)
{ElemMeta_t ret = t; ret <<= kElemSize; ret |= p; return ret;}

int main()
{
	ElemMeta_t m = ElemCtrl_makeDesc('i', 4);
	std::cout << ElemCtrl_getType(m) << std::endl;
	std::cout << (int) ElemCtrl_getOffset(m) << std::endl;
	return 0;
}
