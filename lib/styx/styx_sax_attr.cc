#include "styx_sax.hh"

string	StyxSaxAttr::getName()
{
  return (name);
}

string	StyxSaxAttr::getValue()
{
  return (value);
}

StyxSaxAttr::StyxSaxAttr(string name, string value)
{
  this->name = name;
  this->value = value;
}
