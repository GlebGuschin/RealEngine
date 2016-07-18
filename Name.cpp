
#include "stdafx.h"
#include "Name.hpp"



void Name::Init() {

	if (!Table) {
			Table = new TableItem[ MAX_NAMES ];
	}

}

void Name::Finit() {

	if (Counter == 0) delete Table;

}

Name::TableItem* Name::Table = NULL;
unsigned Name::Counter = 0;


/*
	Name::Name( const char* name ) {

		std::string string( name );
		Map::iterator it = map.find( string );
		if( it == map.end() ) {
		    map.insert( Map::value_type( string, 1 ) );		
		    this->it = map.begin();	
		} else {
		    it->second++;	
		    this->it = it;
		}	

	}

        Name::~Name() {

		 //Map::iterator it = map.find( string );
 		 //assert( it != map.end() );					
		 
		 if( it->second == 1 ) {
    		     map.erase( it );	
		 } else {
                     it->second--; 
		 }
		
	}


Name::Map Name::map;

*/

