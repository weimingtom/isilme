/*
   Test program for TinyXML.
*/
#include <vector>
#include <string>
#ifdef TIXML_USE_STL
	#include <iostream>
	#include <sstream>
	using namespace std;
#else
	#include <stdio.h>
#endif

#if defined( WIN32 ) && defined( TUNE )
	#include <crtdbg.h>
	_CrtMemState startMemState;
	_CrtMemState endMemState;
#endif

#include "tinyxml.h"

//
// This file demonstrates some basic functionality of TinyXml.
// Note that the example is very contrived. It presumes you know
// what is in the XML file. But it does test the basic operations,
// and show how to add and remove nodes.
//

std::string getTopic( int number )
{
	std::string name;
	int counted = 0;

	TiXmlDocument doc( "Course.xml" );
	if ( !doc.LoadFile() )
		return name;
	if ( number > 7 )
		return name;
	TiXmlElement* element = doc.FirstChildElement( "Root" );
	element = element -> FirstChildElement("Course");
	element = element -> FirstChildElement("Topic");

	while ( counted != number )
	{
		counted++;
		element = element -> NextSiblingElement("Topic");
	}
	name = element -> Attribute("Name");
	return name;
}

std::string getDescription( int number )
{
	int counted = 0;
	std::string description;

	if ( number > 7 )
		return description;
	TiXmlDocument doc( "Course.xml" );
	if ( !doc.LoadFile() )
		return 0;
	TiXmlElement* tokens = doc.FirstChildElement( "Root" );
	tokens = tokens -> FirstChildElement("Course");
	tokens = tokens -> FirstChildElement("Topic");

	while ( counted != number )
	{
		counted++;
		tokens = tokens -> NextSiblingElement("Topic");
	}
	tokens = tokens -> FirstChildElement("Task");
	counted = 0;
	while ( 1 )
	{
		if ( rand() % 3 == 0 )
			break;
		if ( tokens -> NextSiblingElement("Task") == NULL )
			break;
		tokens = tokens -> NextSiblingElement("Task");
	}
	description = tokens -> Attribute("Description");
	return description;
}

TiXmlElement* getFirstToken( int number, XToken &other, TiXmlElement* tokens, std::string description )
{
	int counted = 0;

	if ( number > 7 )
		return tokens;
	tokens = tokens -> FirstChildElement("Course");
	tokens = tokens -> FirstChildElement("Topic");

	while ( counted != number )
	{
		counted++;
		tokens = tokens -> NextSiblingElement("Topic");
	}
	tokens = tokens -> FirstChildElement("Task");
	counted = 0;
	while ( tokens -> Attribute( "Description" ) != description )
		tokens = tokens -> NextSiblingElement("Task");

	if ( tokens -> FirstChildElement("Token") != NULL )
	{
		tokens = tokens -> FirstChildElement("Token");
		while ( rand() % 3 != 0 )
		{
			if ( tokens -> NextSiblingElement("Token") == NULL )
				break;
			tokens = tokens -> NextSiblingElement("Token");
		}
		std::string param = tokens -> Attribute("Spaces");
		if ( param == "1" )
			other.space = true;
		else
			other.space = false;
		param = tokens -> Attribute("NewLine");
		if ( param == "true" )
			other.newLine = true;
		else
			other.newLine = false;
		other.text = tokens -> Attribute("Text");
		other.hasNext = true;
	}
	return tokens;
}

std::string generateInvalidToken()
{
	int counted = 0;
	std::string invalidToken;

	TiXmlDocument doc( "Course.xml" );
	if ( !doc.LoadFile() )
		return invalidToken;
	TiXmlElement* element = doc.FirstChildElement( "Root" );
	element = element -> FirstChildElement("Tokens");
	element = element -> FirstChildElement("Token");
	while ( rand() % 3 != 0 )
	{
		if ( element -> NextSiblingElement("Token") == NULL )
			break;
		element = element -> NextSiblingElement("Token");
	}
	invalidToken = element -> Attribute ("Text");
	return invalidToken;
};

TiXmlElement* getNextToken( XToken &other, TiXmlElement* tokens )
{
	if ( tokens -> FirstChildElement("Token") != NULL )
	{
		tokens = tokens -> FirstChildElement("Token");
		while ( rand() % 3 != 0 )
		{
			if ( tokens -> NextSiblingElement("Token") == NULL )
				break;
			tokens = tokens -> NextSiblingElement("Token");
		}
		std::string param = tokens -> Attribute("Spaces");
		if ( param == "1" )
			other.space = true;
		else
			other.space = false;
		param = tokens -> Attribute("NewLine");
		if ( param == "true" )
			other.newLine = true;
		else
			other.newLine = false;
		other.text = tokens -> Attribute("Text");
		if ( tokens -> FirstChildElement("Token") != NULL ) 
			other.hasNext = true;
		else
			other.hasNext = false;
	}
	return tokens;
}
