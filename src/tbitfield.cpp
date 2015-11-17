#include "tbitfield.h"

#define B_pMem (sizeof(TELEM) * 8)

TBitField::TBitField(int len)   
{
	if (len<0)  throw out_of_range("out of range"); 
	MemLen=(len+B_pMem-1)/B_pMem; 
	pMem=new TELEM[MemLen]; 
	if (pMem!=NULL) 
		for (int i=0;i<MemLen;i++) 
			pMem[i]=0; 
	BitLen = len; 
}

TBitField::TBitField(const TBitField &bf)
{
	BitLen=bf.BitLen; 
	MemLen=bf.MemLen; 
	pMem=new TELEM[MemLen]; 
	for (int i=0;i<MemLen;i++) 
		pMem[i]=bf.pMem[i]; 
}

TBitField::~TBitField()
{
	delete []pMem; 
	pMem = NULL; 
}

int TBitField::GetMemIndex(const int n) const 
{
	return n / B_pMem; 
}

TELEM TBitField::GetMemMask(const int n) const 
{
	return 1 << (n % B_pMem); 
}

int TBitField::GetLength(void) const
{
	return BitLen; 
}

void TBitField::SetBit(const int n)
{
	if ((n<0) || (n>=BitLen)) 
		throw 
		out_of_range("Out of range"); 
	pMem[GetMemIndex(n)]|=GetMemMask(n); 
}

void TBitField::ClrBit(const int n) 
{
	if ( (n <0) || (n >= BitLen) ) 
		throw out_of_range("Out of range"); 
	pMem[GetMemIndex(n)] &=~GetMemMask(n); 
}

int TBitField::GetBit(const int n) const 
{
	if ((n<0) || (n>=BitLen)) 
		throw 
		out_of_range("out of range"); 
	return (((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0)? 0 : 1);
}

TBitField& TBitField::operator=(const TBitField &bf)
{
	if (this!=&bf)
	{
		BitLen = bf.BitLen; 
		MemLen = bf.MemLen; 
		delete []pMem; 
		pMem = new TELEM[MemLen]; 
		for (int i=0; i<MemLen; i++) 
			pMem[i] = bf.pMem[i];
	}
	return *this; 
}

int TBitField::operator==(const TBitField &bf) const
{
	int f=1; 
	if (BitLen==bf.BitLen) 
	{ 
		for (int i=0;i<MemLen;i++) 
			if (pMem[i]!=bf.pMem[i]) 
			{ 
				f=0; 
				break; 
			} 
	} 
	else 
		f=0;
	return f; 
}

int TBitField::operator!=(const TBitField &bf) const 
{
	return !(*this == bf); 
}

TBitField TBitField::operator|(const TBitField &bf) 
{
	int n=BitLen;
	if (n<bf.BitLen)
		n=bf.BitLen;
	TBitField tmp(n);
	for (int i=0;i<MemLen;i++)
		tmp.pMem[i]=pMem[i];
	for (int i=0;i<bf.MemLen;i++)
		tmp.pMem[i]|=bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf)
{
	int n=BitLen;
	if (n<bf.BitLen)
		n=bf.BitLen;
	TBitField tmp(n);
	for (int i=0;i<MemLen;i++)
		tmp.pMem[i]=pMem[i];
	for (int i=0;i<bf.MemLen;i++)
		tmp.pMem[i]&=bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) 
{
	int n=BitLen;
	TBitField tmp(n);
	TELEM f = 0;
	for (int i=0;i<(BitLen % B_pMem);i++)
		f |= GetMemMask(i);
	pMem[MemLen - 1] |= (~f);
	for (int i=0;i<MemLen;i++)
		tmp.pMem[i]=~pMem[i];
	return tmp;
}

istream &operator>>(istream &istr, TBitField &bf)
{
	int i=0; char c; 
	do { istr >> c; } while (c!=' '); 
	while (1) 
	{ 
		istr >> c; 
		if (c=='0') bf.ClrBit(i++); 
		else if (c=='1') bf.SetBit(i++); 
		else break; 
	} 
	return istr; 
}

ostream &operator<<(ostream &ostr, const TBitField &bf)
{
	for (int i=0;i<bf.GetLength();i++)
		if (bf.GetBit(i)) ostr <<'1'; else ostr<<'0';
	return ostr;
}