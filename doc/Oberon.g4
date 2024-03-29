grammar Oberon;

/*

letter : 'A' | 'B' | … | 'Z' | 'a' | 'b' | … | 'z' ;
digit : '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' ;
hexdigit : digit | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' ;
integer : digit (digit)* | digit (hexdigit)* 'H' ;
real : digit (digit)* '.' (digit)* (scaleFactor)?  ;
scaleFactor : 'E' ('+' | '-')? digit (digit)* ;
IDENT : letter (letter | digit)* ;
string : ''' (character)* ''' | digit (hexdigit)* 'X' ;

*/

qualident
    : (IDENT '.')? IDENT
    ;
identdef
    : IDENT ('*')?
    ;
number
    : INTEGER | REAL
    ;
constDeclaration
    : identdef '=' constExpression
    ;
constExpression
    : expression
    ;
typeDeclaration
    : identdef '=' type
    ;
type
    : qualident | arrayType | recordType | pointerType | procedureType
    ;
arrayType
    : 'ARRAY' length (',' length)* 'OF' type
    ;
length
    : constExpression
    ;
recordType
    : 'RECORD' ('(' baseType ')')? (fieldListSequence)? 'END'
    ;
baseType
    : qualident
    ;
fieldListSequence
    : fieldList (';' fieldList)*
    ;
fieldList
    : identList ':' type
    ;
identList
    : identdef (',' identdef)*
    ;
pointerType
    : 'POINTER' 'TO' type
    ;
procedureType
    : 'PROCEDURE' (formalParameters)?
    ;
variableDeclaration
    : identList ':' type
    ;
expression
    : simpleExpression (relation simpleExpression)?
    ;
relation
    : '=' | '#' | '<' | '<=' | '>' | '>=' | 'IN' | 'IS'
    ;
simpleExpression
    : ('+' | '-')? term (addOperator term)*
    ;
addOperator
    : '+' | '-' | 'OR'
    ;
term
    : factor (mulOperator factor)*
    ;
mulOperator
    : '*' | '/' | 'DIV' | 'MOD' | '&'
    ;
factor
    : number
    | STRING
    | 'NIL'
    | 'TRUE'
    | 'FALSE'
    | set
    | designator (actualParameters)?
    | '(' expression ')'
    | '~' factor
    ;
designator
    : qualident (selector)*
    ;
selector
    : '.' IDENT | '[' expList ']' | '^' | '(' qualident ')'
    ;
set
    : '{' (element (',' element)*)? '}'
    ;
element
    : expression ('..' expression)?
    ;
expList
    : expression (',' expression)*
    ;
actualParameters
    : '(' (expList)? ')'
    ;
statement
    : (assignment
    | procedureCall
    | ifStatement
    | caseStatement
    | whileStatement
    | repeatStatement
    | forStatement)?
    ;
assignment
    : designator ':=' expression
    ;
procedureCall
    : designator (actualParameters)?
    ;
statementSequence
    : statement (';' statement)*
    ;
ifStatement
    : 'IF' expression 'THEN' statementSequence ('ELSIF' expression 'THEN' statementSequence)* ('ELSE' statementSequence)? 'END'
    ;
caseStatement
    : 'CASE' expression 'OF' caseItem ('|' caseItem)* 'END'
    ;
caseItem
    : (caseLabelList ':' statementSequence)?
    ;
caseLabelList
    : labelRange (',' labelRange)*
    ;
labelRange
    : label ('..' label)?
    ;
label
    : INTEGER | STRING | qualident
    ;
whileStatement
    : 'WHILE' expression 'DO' statementSequence ('ELSIF' expression 'DO' statementSequence)* 'END'
    ;
repeatStatement
    : 'REPEAT' statementSequence 'UNTIL' expression
    ;
forStatement
    : 'FOR' IDENT ':=' expression 'TO' expression ('BY' constExpression)? 'DO' statementSequence 'END'
    ;
procedureDeclaration
    : procedureHeading ';' procedureBody IDENT
    ;
procedureHeading
    : 'PROCEDURE' identdef (formalParameters)?
    ;
procedureBody
    : declarationSequence ('BEGIN' statementSequence)? ('RETURN' expression)? 'END'
    ;
declarationSequence
    : ('CONST' (constDeclaration ';')*)? ('TYPE' (typeDeclaration ';')*)? ('VAR' (variableDeclaration ';')*)? (procedureDeclaration ';')*
    ;
formalParameters
    : '(' (fpSection (';' fpSection)*)? ')' (':' qualident)?
    ;
fpSection
    : ('VAR')? IDENT (',' IDENT)* ':' formalType
    ;
formalType
    : ('ARRAY' 'OF')* qualident
    ;
module
    : 'MODULE' IDENT ';' (importList)? declarationSequence ('BEGIN' statementSequence)? 'END' IDENT '.'
    ;
importList
    : 'IMPORT' importItem (',' importItem)* ';'
    ;
importItem
    : IDENT (':=' IDENT)?
    ;

IDENT : [A-Za-z][A-Za-z0-9]* ;
STRING : (["]~["]*["]) | ([0-9][0-9A-F]*'X') ;
INTEGER : ([0-9]+) | ([0-9][0-9A-F]*'H') ;
REAL : [0-9]+'.'[0-9]*('E'('+'|'-')?[0-9]+)?  ;
WS : [ \t\r\n] -> skip ;
COMMENT : '(*' .*? '*)' -> skip ;
