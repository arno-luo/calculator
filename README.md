# calculator

## gramar:

#### *expression*
        term ('+' | '-' term)*               
#### *term*
        factor ('*' | '/' | '%' factor)*       
#### *factor*
        number
        | '(' expression ')'
#### *number*
        literal float number
