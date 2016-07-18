#ifndef INIFILE_HPP
#define INIFILE_HPP

#include "String.hpp"
#include "DynamicArray.hpp"
#include "LinearMap.hpp"



struct IniFileSection {
	String name;
  DynamicArray<String> data; 
}; 

void parseKeyValue( const std::string &source, std::string &key, std::string &value );
String getSectionName( const std::string &str );
String getString( const char *text );


class IniFile {

  //std::vector<Section>  sectionArray;

public:

  IniFile();
  ~IniFile();

  bool loadFrom( const String &fileName );
  //const std::vector<Section> & getSections() const;

};


#endif //INIFILE_HPP