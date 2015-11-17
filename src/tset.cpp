#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower=mp;
}

TSet::TSet(const TSet &s) : BitField(1)
{
	BitField=s.BitField; 
	MaxPower=s.MaxPower; 
}

TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower=bf.GetLength();
}

TSet::operator TBitField()
{
	TBitField BP (this->BitField); 
	return BP; 
}

int TSet::GetMaxPower(void) const 
{
	return MaxPower; 
}

int TSet::IsMember(const int Elem) const 
{
	return BitField.GetBit(Elem); 
}

void TSet::InsElem(const int Elem) 
{
	BitField.SetBit(Elem); 
}

void TSet::DelElem(const int Elem) 
{
	BitField.ClrBit(Elem);
}

TSet& TSet::operator=(const TSet &s) 
{
	BitField=s.BitField; 
	MaxPower=s.MaxPower; 
	return *this; 
}

int TSet::operator==(const TSet &s) const 
{
	return BitField==s.BitField;
}

int TSet::operator!=(const TSet &s) const 
{
	return BitField!=s.BitField;
}

TSet TSet::operator+(const TSet &s) 
{
	TSet set1 (BitField|s.BitField ); 
	return set1; 
}

TSet TSet::operator+(const int Elem) 
{
	TSet set1 (BitField); 
	set1.BitField.SetBit (Elem); 
	return set1; 
}

TSet TSet::operator-(const int Elem) 
{
	TSet set1 (BitField); 
	set1.BitField.ClrBit(Elem); 
	return set1; 
}

TSet TSet::operator*(const TSet &s) 
{
	TSet set1 (BitField&s.BitField); 
	return set1; 
}

TSet TSet::operator~(void) 
{
	TSet set1 (~BitField); 
	return set1; 
}

istream &operator>>(istream &istr, TSet &s) 
{
	int a; 
	for (int i=0;i<s.GetMaxPower();i++) 
	{ 
		istr >> a; 
		s.InsElem (a); 
	} 
	return istr; 
}

ostream& operator<<(ostream &ostr, const TSet &s) 
{
	for (int i=0;i<s.GetMaxPower();i++) 
	if (s.IsMember(i))
		ostr << i << ' ';
	return ostr; 
}