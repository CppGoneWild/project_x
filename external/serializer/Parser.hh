#ifndef SERIALIZER_PARSER_HH__
#define SERIALIZER_PARSER_HH__


/* Kind of grammar :

alpha = ['a' -'z'] | ['A' - 'Z'] | '_'
digit =  ['0' - '9']
simple_identifier = alpha: (alpha: | digit:)*
raw_identifier = '"' '"' '"' ~['"""']  '"' '"' '"'
identifier = simple_identifier: | raw_identifier:

decimal_separator = '.' | ','
base_id = 'b' | 'o' | 'x' | 'B' | 'O' | 'X'
number_base = '0' (base_id:). digit: (digit:)*
number_dec = ((digit:)* | decimal_separator) (digit:)*
number = number_base: | number_dec:

field_separator = ';'	
expression = identifier: | number: | object: | pack: ';'

pack = '{' (expression:)* '}'
object = '(' (identifier: | number:) ')' pack:

assume that root is (expression:)*

exemple :

(id) { id; """raw   raw"""; 0x45; (id2) {}; }

*/


#include "Tree.hh"

#include <iostream>


namespace serializer
{


I_Node * unserialize(std::istream &, std::string const & = "");


} // serializer


#endif // SERIALIZER_PARSER_HH__
