#pragma once

#ifndef __NAME_HPP__
#define __NAME_HPP__

#include <assert.h>
#include <string>
//#include <map>
//#include <list>


class Name {

	//std::string name;
	const char*  name;

	unsigned id;
	//typedef std::map< std::string, unsigned > Map;
	//struct {};

	//ap::iterator it;
	enum {
		MAX_NAMES = 1024,
		MAX_NAME_LENGTH = 31
	};


	struct TableItem
	{
		char name[MAX_NAME_LENGTH];
		unsigned counter;
		TableItem() { name[0] = 0; counter = 0; }
	};

	Name(unsigned id_ ) { id = id_; Table[0].counter++; Counter++; }

public:

	Name() { Init();  Table[0].counter++; id = 0; Counter++; }

	Name(const char* name_) {

		Init();
		assert(strlen(name_) <= MAX_NAME_LENGTH );

		for (unsigned i = 1; i < MAX_NAMES; i++) {
					if( strcmp(name_, Table[i].name ) == 0 ) {
							Table[i].counter++;
							id = i;
							Counter++;
							name = &Table[i].name[0];
							return;
					}
				
		}

		for( unsigned i = 1; i < MAX_NAMES; i++ ) {
					if( Table[i].counter == 0 ) {
							strcpy_s( &Table[i].name[ 0 ], MAX_NAME_LENGTH,  name_);
							Table[i].counter = 1;
							id = i;
							Counter++;
							name = &Table[i].name[0];
							return;
				}
		}


		assert(0);

	}

	Name(const Name& name_) { 
		id = name_.id;  
		Table[id].counter++; 
		Counter++; 
		name = &Table[id].name[0]; 
	}

	~Name() {

		Counter--;

		if( Counter == 0 ) {
				Finit();
		} else {
				Table[id].counter--;
		}
	
	}

	Name& operator=(const Name& rhs) { Table[rhs.id].counter++; Counter++; id = rhs.id;  return *this; }

	operator const char*() const { return Table[id].name; }
	operator unsigned() const { return id; }

	bool operator==(const Name& rhs) const { return( id == rhs.id ); }

	bool operator<(const Name& rhs) const { return strcmp(Table[id].name, Table[rhs.id].name) == -1; }

private:

static void Init();
static void Finit();
static TableItem* Table;
static unsigned Counter;


};



#endif






