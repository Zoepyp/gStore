#include "RDFParser.h"
/*	if you want to parse a triple file, you need to create a RDFParser object
*	and run parseFile several times until all the triple is processed
*	for example:
*		RDFParser _RDFParser(filename);
*		triple_array = new Triple_with_objtype[RDFParser::RDFParser::TRIPLE_NUM_PER_GROUP];
*		while (true)
*		{
*			triple_num = 0;
*			_RDFParser.parseFile();
*			if (triple_num == 0)	break;
*			......
*		}		
*/
string RDFParser::parseFile(TripleWithObjType* _triple_array, int& _triple_num)
{
	string _subject, _predicate, _object, _objectSubType;
	Type::Type_ID _objectType;

	while (_triple_num < RDFParser::TRIPLE_NUM_PER_GROUP)
	{
		try
		{
			if (!this->_TurtleParser.parse(_subject, _predicate, _object, _objectType, _objectSubType))		break;
		}
		catch (const TurtleParser::Exception& _e) 
		{
			cout <<"args 2:"<< _e.message << endl;
			this->_TurtleParser.discardLine();
			continue;
		}

		_subject = "<" + _subject + ">";
		_predicate = "<" + _predicate + ">";

		TripleWithObjType::ObjectType _object_type = TripleWithObjType::None;
		if (_objectType == Type::Type_URI)
		{
			_object = "<" + _object + ">";
			_object_type = TripleWithObjType::Entity;
		}
		else
		{
			if (_objectType == Type::Type_Literal)
				_object = "\"" + _object + "\"";
			else if (_objectType == Type::Type_CustomLanguage)
				_object = "\"" + _object + "\"@" + _objectSubType;
			else if (_objectType == Type::Type_String)
				_object = "\"" + _object + "\"^^<http://www.w3.org/2001/XMLSchema#string>";
			else if (_objectType == Type::Type_Integer)
			{
				long long ll;
				try
				{
					ll = stoll(_object);
				}
				catch (invalid_argument &e)
				{
					cout << "Triple " << _triple_num << " integer value invalid, _object = " << _object << endl;
					continue;
				}
				catch (out_of_range &e)
				{
					cout << "Triple " << _triple_num << " integer out of range." << endl;
					continue;
				}
				_object = "\"" + _object + "\"^^<http://www.w3.org/2001/XMLSchema#integer>";
			}
			else if (_objectType == Type::Type_Decimal)
				_object = "\"" + _object + "\"^^<http://www.w3.org/2001/XMLSchema#decimal>";
			else if (_objectType == Type::Type_Double)
			{
				double d;
				try
				{
					d = stod(_object);
				}
				catch (invalid_argument &e)
				{
					cout << "Triple " << _triple_num << " double value invalid." << endl;
					continue;
				}
				if (_object.length() == 3 && toupper(_object[0]) == 'N' && toupper(_object[1]) == 'A'
					&& toupper(_object[2]) == 'N')
				{
					cout << "Triple " << _triple_num << " double value is NaN." << endl;
					continue;
				}
				_object = "\"" + _object + "\"^^<http://www.w3.org/2001/XMLSchema#double>";
			}
			else if (_objectType == Type::Type_Boolean)
				_object = "\"" + _object + "\"^^<http://www.w3.org/2001/XMLSchema#boolean>";
			else if (_objectType == Type::Type_CustomType)
			{
				// cout << "Triple " << _triple_num << " is custom type." << endl;
				if (_objectSubType == "http://www.w3.org/2001/XMLSchema#long")
				{
					long long ll;
					try
					{
						ll = stoll(_object);
					}
					catch (invalid_argument &e)
					{
						cout << "Triple " << _triple_num << " long value invalid, _object = " << _object << endl;
						continue;
					}
					catch (out_of_range &e)
					{
						cout << "Triple " << _triple_num << " xsd:long out of range." << endl;
						continue;
					}
				}
				else if (_objectSubType == "http://www.w3.org/2001/XMLSchema#int")
				{
					long long ll;
					try
					{
						ll = stoll(_object);
					}
					catch (invalid_argument &e)
					{
						cout << "Triple " << _triple_num << " int value invalid, _object = " << _object << endl;
						continue;
					}
					catch (out_of_range &e)
					{
						cout << "Triple " << _triple_num << " xsd:int out of range." << endl;
						continue;
					}
					if (ll < (long long)INT_MIN || ll > (long long)INT_MAX)
					{
						cout << "Triple " << _triple_num << " xsd:int out of range." << endl;
						continue;
					}
				}
				else if (_objectSubType == "http://www.w3.org/2001/XMLSchema#short")
				{
					long long ll;
					try
					{
						ll = stoll(_object);
					}
					catch (invalid_argument &e)
					{
						cout << "Triple " << _triple_num << " short value invalid, _object = " << _object << endl;
						continue;
					}
					catch (out_of_range &e)
					{
						cout << "Triple " << _triple_num << " xsd:short out of range." << endl;
						continue;
					}
					if (ll < (long long)SHRT_MIN || ll > (long long)SHRT_MAX)
					{
						cout << "Triple " << _triple_num << " xsd:short out of range." << endl;
						continue;
					}
				}
				else if (_objectSubType == "http://www.w3.org/2001/XMLSchema#byte")
				{
					long long ll;
					try
					{
						ll = stoll(_object);
					}
					catch (invalid_argument &e)
					{
						cout << "Triple " << _triple_num << " byte value invalid, _object = " << _object << endl;
						continue;
					}
					catch (out_of_range &e)
					{
						cout << "Triple " << _triple_num << " xsd:byte out of range." << endl;
						continue;
					}
					if (ll < (long long)SCHAR_MIN || ll > (long long)SCHAR_MAX)
					{
						cout << "Triple " << _triple_num << " xsd:byte out of range." << endl;
						continue;
					}
				}
				else if (_objectSubType == "http://www.w3.org/2001/XMLSchema#float")
				{
					float f;
					try
					{
						f = stof(_object);
					}
					catch (invalid_argument &e)
					{
						cout << "Triple " << _triple_num << " float value invalid." << endl;
						continue;
					}
					if (_object.length() == 3 && toupper(_object[0]) == 'N' && toupper(_object[1]) == 'A'
						&& toupper(_object[2]) == 'N')
					{
						cout << "Triple " << _triple_num << " float value is NaN." << endl;
						continue;
					}
				}
				_object = "\"" + _object + "\"^^<" + _objectSubType + ">";
			}
			_object_type = TripleWithObjType::Literal;
		}

		_triple_array[_triple_num++] = TripleWithObjType(_subject, _predicate, _object, _object_type);
	}
	return "";
}

string RDFParser::parseFile(TripleWithObjType* _triple_array, int& _triple_num,string _error_log)
{
	string _subject, _predicate, _object, _objectSubType;
	Type::Type_ID _objectType;
	ofstream ofile;             //定义输出文件
	ofile.open(_error_log,ios::app);
	if (!ofile)
	{
		cout << " file can not be opened." << endl;
	}
	cout << "_error_log:" << _error_log << endl;
	while (_triple_num < RDFParser::TRIPLE_NUM_PER_GROUP)
	{
		try
		{
			if (!this->_TurtleParser.parse(_subject, _predicate, _object, _objectType, _objectSubType))		break;
		}
		catch (const TurtleParser::Exception& _e)
		{
			cout <<"error:"<< _e.message << endl;
			//cout << _subject << "||" << _predicate << "||" << _object << "||" << _e.message << endl;
			
			ofile << _subject << "||" << _predicate << "||" << _object << "||" << _e.message << endl;
			this->_TurtleParser.discardLine();
			continue;
		}

		_subject = "<" + _subject + ">";
		_predicate = "<" + _predicate + ">";

		TripleWithObjType::ObjectType _object_type = TripleWithObjType::None;
		if (_objectType == Type::Type_URI)
		{
			_object = "<" + _object + ">";
			_object_type = TripleWithObjType::Entity;
		}
		else
		{
			if (_objectType == Type::Type_Literal)
				_object = "\"" + _object + "\"";
			else if (_objectType == Type::Type_CustomLanguage)
				_object = "\"" + _object + "\"@" + _objectSubType;
			else if (_objectType == Type::Type_String)
				_object = "\"" + _object + "\"^^<http://www.w3.org/2001/XMLSchema#string>";
			else if (_objectType == Type::Type_Integer)
			{
				long long ll;
				try
				{
					ll = stoll(_object);
				}
				catch (invalid_argument& e)
				{
					cout << "Triple " << _triple_num << " integer value invalid, _object = " << _object << endl;
					continue;
				}
				catch (out_of_range& e)
				{
					cout << "Triple " << _triple_num << " integer out of range." << endl;
					continue;
				}
				_object = "\"" + _object + "\"^^<http://www.w3.org/2001/XMLSchema#integer>";
			}
			else if (_objectType == Type::Type_Decimal)
				_object = "\"" + _object + "\"^^<http://www.w3.org/2001/XMLSchema#decimal>";
			else if (_objectType == Type::Type_Double)
			{
				double d;
				try
				{
					d = stod(_object);
				}
				catch (invalid_argument& e)
				{
					cout << "Triple " << _triple_num << " double value invalid." << endl;
					continue;
				}
				if (_object.length() == 3 && toupper(_object[0]) == 'N' && toupper(_object[1]) == 'A'
					&& toupper(_object[2]) == 'N')
				{
					cout << "Triple " << _triple_num << " double value is NaN." << endl;
					continue;
				}
				_object = "\"" + _object + "\"^^<http://www.w3.org/2001/XMLSchema#double>";
			}
			else if (_objectType == Type::Type_Boolean)
				_object = "\"" + _object + "\"^^<http://www.w3.org/2001/XMLSchema#boolean>";
			else if (_objectType == Type::Type_CustomType)
			{
				// cout << "Triple " << _triple_num << " is custom type." << endl;
				if (_objectSubType == "http://www.w3.org/2001/XMLSchema#long")
				{
					long long ll;
					try
					{
						ll = stoll(_object);
					}
					catch (invalid_argument& e)
					{
						cout << "Triple " << _triple_num << " long value invalid, _object = " << _object << endl;
						continue;
					}
					catch (out_of_range& e)
					{
						cout << "Triple " << _triple_num << " xsd:long out of range." << endl;
						continue;
					}
				}
				else if (_objectSubType == "http://www.w3.org/2001/XMLSchema#int")
				{
					long long ll;
					try
					{
						ll = stoll(_object);
					}
					catch (invalid_argument& e)
					{
						cout << "Triple " << _triple_num << " int value invalid, _object = " << _object << endl;
						continue;
					}
					catch (out_of_range& e)
					{
						cout << "Triple " << _triple_num << " xsd:int out of range." << endl;
						continue;
					}
					if (ll < (long long)INT_MIN || ll >(long long)INT_MAX)
					{
						cout << "Triple " << _triple_num << " xsd:int out of range." << endl;
						continue;
					}
				}
				else if (_objectSubType == "http://www.w3.org/2001/XMLSchema#short")
				{
					long long ll;
					try
					{
						ll = stoll(_object);
					}
					catch (invalid_argument& e)
					{
						cout << "Triple " << _triple_num << " short value invalid, _object = " << _object << endl;
						continue;
					}
					catch (out_of_range& e)
					{
						cout << "Triple " << _triple_num << " xsd:short out of range." << endl;
						continue;
					}
					if (ll < (long long)SHRT_MIN || ll >(long long)SHRT_MAX)
					{
						cout << "Triple " << _triple_num << " xsd:short out of range." << endl;
						continue;
					}
				}
				else if (_objectSubType == "http://www.w3.org/2001/XMLSchema#byte")
				{
					long long ll;
					try
					{
						ll = stoll(_object);
					}
					catch (invalid_argument& e)
					{
						cout << "Triple " << _triple_num << " byte value invalid, _object = " << _object << endl;
						continue;
					}
					catch (out_of_range& e)
					{
						cout << "Triple " << _triple_num << " xsd:byte out of range." << endl;
						continue;
					}
					if (ll < (long long)SCHAR_MIN || ll >(long long)SCHAR_MAX)
					{
						cout << "Triple " << _triple_num << " xsd:byte out of range." << endl;
						continue;
					}
				}
				else if (_objectSubType == "http://www.w3.org/2001/XMLSchema#float")
				{
					float f;
					try
					{
						f = stof(_object);
					}
					catch (invalid_argument& e)
					{
						cout << "Triple " << _triple_num << " float value invalid." << endl;
						continue;
					}
					if (_object.length() == 3 && toupper(_object[0]) == 'N' && toupper(_object[1]) == 'A'
						&& toupper(_object[2]) == 'N')
					{
						cout << "Triple " << _triple_num << " float value is NaN." << endl;
						continue;
					}
				}
				_object = "\"" + _object + "\"^^<" + _objectSubType + ">";
			}
			_object_type = TripleWithObjType::Literal;
		}

		_triple_array[_triple_num++] = TripleWithObjType(_subject, _predicate, _object, _object_type);

	}
	cout << "RDFParser parseFile done!" << endl;
	ofile.close();
	return "";
}

string RDFParser::parseFileSample(TripleWithObjType* _triple_array, int& _triple_num, int UPBOUND)
{
	string _subject, _predicate, _object, _objectSubType;
	Type::Type_ID _objectType;

	while (_triple_num < UPBOUND)
	{
		try
		{
			if (!this->_TurtleParser.parse(_subject, _predicate, _object, _objectType, _objectSubType))		break;
		}
		catch (const TurtleParser::Exception& _e) 
		{
			cout <<"args sample"<< _e.message << endl;
			this->_TurtleParser.discardLine();
			continue;
		}

		_subject = "<" + _subject + ">";
		_predicate = "<" + _predicate + ">";

		TripleWithObjType::ObjectType _object_type = TripleWithObjType::None;
		if (_objectType == Type::Type_URI)
		{
			_object = "<" + _object + ">";
			_object_type = TripleWithObjType::Entity;
		}
		else
		{
			if (_objectType == Type::Type_Literal)
				_object = "\"" + _object + "\"";
			else if (_objectType == Type::Type_CustomLanguage)
				_object = "\"" + _object + "\"@" + _objectSubType;
			else if (_objectType == Type::Type_String)
				_object = "\"" + _object + "\"^^<http://www.w3.org/2001/XMLSchema#string>";
			else if (_objectType == Type::Type_Integer)
				_object = "\"" + _object + "\"^^<http://www.w3.org/2001/XMLSchema#integer>";
			else if (_objectType == Type::Type_Decimal)
				_object = "\"" + _object + "\"^^<http://www.w3.org/2001/XMLSchema#decimal>";
			else if (_objectType == Type::Type_Double)
				_object = "\"" + _object + "\"^^<http://www.w3.org/2001/XMLSchema#double>";
			else if (_objectType == Type::Type_Boolean)
				_object = "\"" + _object + "\"^^<http://www.w3.org/2001/XMLSchema#boolean>";
			else if (_objectType == Type::Type_CustomType)
				_object = "\"" + _object + "\"^^<" + _objectSubType + ">";
			_object_type = TripleWithObjType::Literal;
		}

		_triple_array[_triple_num++] = TripleWithObjType(_subject, _predicate, _object, _object_type);
	}
	return "";
}
/*	if you want to parse a string, you need to create a RDFParser object with no parameter, if the triple has prefix, you also need to provide it.
*	the whole string must be processed in one time of invoking parseString, pay attention to the triples in the string won't exceed the limit of RDFParser::TRIPLE_NUM_PER_GROUP.
*	for example:
*		RDFParser _RDFParser;
*		_RDFParser.parseString(prefix, ..);
*		_RDFParser.parseString(triple string 1, ..);
*		_RDFParser.parseString(triple string 2, ..);
*
*		triple string 1 & 2 will share the common prefix, if you don't want this, create a new RDFParser object.
*		_RDFParser.parseString(prefix + "\n" + triple string 1 + "\n" + triple string 2, ..); is also acceptable.
*/
string RDFParser::parseString(string _str, TripleWithObjType* _triple_array, int& _triple_num)
{
	//clear in each time invoking
	this->_sin.clear();
	this->_sin << _str;
	
	return parseFile(_triple_array, _triple_num);
}
