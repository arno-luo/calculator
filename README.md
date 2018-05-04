# calculator

## grammar:

expression
    term
    term "+" expression 
    term "-" expression 
term
    element
    element "*" term 
    element "/" term 
    element "%" term 
element
    number
    "("expression")"
number
    digital 
    digital"."digital
digital
    [0-9]
    [0-9]digital   
