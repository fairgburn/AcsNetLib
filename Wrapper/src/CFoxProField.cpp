#include "FoxPro.NET.h"

using namespace AcsNetLibCpp::FoxPro;

CFoxProField::CFoxProField(char* name, char type, int offset, int length)
{
    this->Name = name;
    this->Type = type;
    this->Offset = offset;
    this->Length = length;
}

CFoxProField::~CFoxProField()
{
    //delete[] Name; // created with new
}