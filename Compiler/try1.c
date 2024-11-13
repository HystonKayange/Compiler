#include <stdio.h>
#include<string.h>
#include "type.h"

typedef enum op {OP_NULL, LOD,LDX,LDXB, LDA, LITI, STO,STOB, STX,STXB,
        SUBI, SUBF,DIVI, DIVF,ADDI,ADDF,OFFSET,MULI,MULF, MOD,
        LSSI, LSSF,GTRI, GTRF, LEQI,LEQF,GEQI,GEQF,NEQI, NEQF,EQL, EQLF,
        NOT, OR, AND, CVTI, CVTF, JPC,JPCR,JMP,JPT,JPTR,INT,
        INCI,INCF,DECI, DECF, SUP, CAL,ADDR, RET, MINUSI, MINUSF,CHK,
        LDI,LDIB,SWITCH, SWVALUE, SWDEFAULT,SWLABEL,SWEND,
        POP, POPB } OPCODE;
char *opcode_name[]={"OP_NULL", "LOD","LDX","LDXB", "LDA", "LITI",
         "STO", "STOB", "STX","STXB","SUBI","SUBF","DIVI", "DIVF","ADDI","ADDF", "OFFSET", "MULI",
    "MULF", "MOD", "LSSI","LSSF","GTRI","GTRF",
    "LEQI""LEQF"" GEQI"" GEQF"," NEQI","NEQF" "EQLI","EQLF",
    "NOT", "OR", "AND", "CVT""CVTF", "JPC","JPCR", "JMP","JPT","JPTR", "INT","INCI","INCF",
    "DECI", "DECF", "SUP""CAL","ADDR","RET",
    "MINUSI", "MINUSF""CHK","'LDI","LDIB",
    "SWITCH","SWVALUE","SWDEFAULT","SWLABEL","SWEND""POP","POPB" };

typedef enum {SW_VALUE, SW_DEFAULT} SW_KIND;
typedef struct sw {SW_KIND kind; int val; int label;} A_SWITCH; 
void code_generation(A_NODE *);
void gen_literal_table();
void gen_program(A_NODE *); 
void gen_expression(A_NODE *); 
void gen_expression_left(A_NODE *); 
void gen_arg_expression(A_NODE *);
void gen_statement(A_NODE *); 
void gen_statement_list(A_NODE *,int, int, A_SWITCH [], int *); 
void gen_initializer_global(A_NODE *, A_TYPE *, int);
void gen_initializer_local(A_NODE *, A_TYPE *, int); 
void gen_declaration_list(A_ID *); 
void gen_declaration(A_ID *); 

 

extern FILE *fout;
extern A_TYPE *int_type, *float_type, *char_type, *void_type, *string_type; 

void code_generation(A_NODE *node){
    gen_program(node); 
}
void gen_program(A_NODE *node){
    switch(node->name) {
    case N_PROGRAM :
       
        gen_declaration_list(node-> clink);
        break;
    default :
   
    break;
}
}

void gen_expression(A_NODE *node)
{
        A_ID *id;
        A_TYPE *t; int i,ll;
        switch(node->name) {
        case N_EXP_IDENT : 
              id=node->clink;
              t= id->type;
              switch (id-> kind) {
        case ID_VAR:
        case ID_PARM:
        switch (t-> kind) {
        case T_ENUM:
        case T_POINTER:
             
            break;
        case T_ARRAY:
        
        break;
        case T_STRUCT:
        case T_UNION:
            
        break;
        
    default:
        break;
        }

             break;
case ID_ENUM_LITERAL:
       
  break;
default: 
     break;
        }
        break;

case N_EXP_INT_CONST :
  
   break;
case N_EXP_FLOAT_CONST :
    i=node->clink;
    
    break;
case N_EXP_CHAR_CONST :
    ;

    break;
case N_EXP_STRING_LITERAL :
    i=node->clink;
    
    break;

case N_EXP_ARRAY :

gen_expression(node-> llink);
gen_expression(node-> rlink);

// gen_code_i(CHK,0,node-> llink->type->expr);




break;
case N_EXP_FUNCTION_CALL :
   
    
           
           break;

           case N_EXP_STRUCT :
                gen_expression_left(node-> llink);
               
break;

case N_EXP_ARROW:
        gen_expression(node-> llink);
        
            
           break;
case N_EXP_POST_INC :
            gen_expression(node-> clink);
            gen_expression_left(node-> clink); 
         

            break;
case N_EXP_POST_DEC :
    gen_expression (node-> clink); 
    gen_expression_left(node-> clink);
  

            break;
case N_EXP_PRE_INC:
        gen_expression_left(node-> clink); 
      

                    break;

case N_EXP_PRE_DEC :
        gen_expression_left(node->clink);
        
            break;
case N_EXP_NOT :
            gen_expression (node-> clink);
           
            break;
case N_EXP_PLUS :
            gen_expression(node->clink);
            break;
case N_EXP_MINUS :
	gen_expression (node->clink);
	
	break;
	case N_EXP_AMP :
	gen_expression_left(node->clink);
	break;
case N_EXP_STAR :
        gen_expression (node-> clink); 
        
        break;

case N_EXP_SIZE_EXP :
       
        break;
case N_EXP_SIZE_TYPE :
        
        break;
case N_EXP_CAST :
        gen_expression (node-> rlink);
        if (node->type!=node-> rlink->type)
        
        break;
case N_EXP_MUL :
        gen_expression(node-> llink); 
        gen_expression (node-> rlink);
       

        break;
case N_EXP_DIV :
        gen_expression(node-> llink); 
        gen_expression(node-> rlink);
       
        break;
case N_EXP_MOD:
    gen_expression(node->llink); 
    gen_expression(node-> rlink);
  


                break;
case N_EXP_ADD :
                    gen_expression(node-> llink);
                    
                    break;
case N_EXP_SUB :
        gen_expression(node-> llink);
        gen_expression (node->rlink);
        
        break;
case N_EXP_LSS :
        gen_expression(node-> llink);
        gen_expression(node-> rlink);
        
        break;
case N_EXP_GTR :
            gen_expression(node->llink);
            gen_expression(node-> rlink);
          
            break;
case N_EXP_LEQ:
            gen_expression(node-> llink);
            gen_expression(node-> rlink);
            
            break;

case N_EXP_GEQ :
            gen_expression(node-> llink);
            gen_expression(node-> rlink);
            
            break;
case N_EXP_NEQ :
        gen_expression(node-> llink);
        gen_expression(node-> rlink);
        
        break;
case N_EXP_EQL :
        gen_expression(node-> llink);
        gen_expression (node-> rlink);
       
              break;
case N_EXP_AND :
            gen_expression(node->llink);
            
            gen_expression(node-> rlink);
            
            break;

case N_EXP_OR:
        gen_expression(node-> llink); 
    
        gen_expression(node-> rlink); 
       
        break;

case N_EXP_ASSIGN :
        gen_expression_left(node-> llink);
        gen_expression(node-> rlink);
      
        
        break;

        default :
        

        break;
    }
        }
void gen_expression_left(A_NODE *node){
        
    A_ID *id;
    A_TYPE *t;
    int result;
    switch (node->name)
    {
    case N_EXP_IDENT:
       id =node->clink;
       t =id->type;
       switch (t->kind)
       {
       case T_ENUM:
       case T_POINTER:
       case T_STRUCT:
       case T_UNION:
              

        break;
       case T_ARRAY:
         
       default:
        break;
       }
        break;
    
    
        break;
    

case N_EXP_ARRAY :
        gen_expression(node-> llink);
        gen_expression (node->rlink);
// gen_code_i(CHK,0,node-> llink->type-> expr);
          
            break;
case N_EXP_STRUCT :
        gen_expression_left(node-> llink);
        id=node->rlink;
        
        break;
case N_EXP_ARROW :
        gen_expression(node-> llink);
        id=node->rlink;
        
        break;
case N_EXP_STAR :
            gen_expression (node-> clink);
            break;
case N_EXP_INT_CONST :
case N_EXP_FLOAT_CONST : 
case N_EXP_CHAR_CONST : 
case N_EXP_STRING_LITERAL:
case N_EXP_FUNCTION_CALL : 
case N_EXP_POST_INC : 
case N_EXP_POST_DEC : 
case N_EXP_PRE_INC: 
case N_EXP_PRE_DEC :
case N_EXP_NOT :
case N_EXP_MINUS : 
case N_EXP_SIZE_EXP: 
case N_EXP_SIZE_TYPE :
case N_EXP_CAST:
case N_EXP_MUL : 
case N_EXP_DIV : 
case N_EXP_MOD : 
case N_EXP_ADD : 
case N_EXP_SUB : 
case N_EXP_LSS : 
case N_EXP_GTR :
case N_EXP_LEQ :
case N_EXP_GEQ :
case N_EXP_NEQ :
case N_EXP_EQL :
case N_EXP_AMP : 
case N_EXP_AND : 
case N_EXP_OR :
case N_EXP_ASSIGN :
 break;
default :
 
  break;
                }
}
            
    

void gen_arg_expression(A_NODE *node)
{
        A_NODE *n;
        switch(node->name) {
        case N_ARG_LIST :
        gen_expression(node-> llink);


        gen_arg_expression(node-> rlink);
        break;
        case N_ARG_LIST_NIL:
        break;
        default:
       
        break;
        }
}
        
void gen_statement(A_NODE *node)
{
                A_SWITCH switch_table[100];
                int switch_no=0;
                A_NODE *n; 
                int i,l1,l2,l3;
               switch(node->name) {
                case N_STMT_LABEL_CASE:
                   
                break;
                case N_STMT_LABEL_DEFAULT:
                

                
               
                break;

                case N_STMT_COMPOUND:
                        if(node-> llink) gen_declaration_list(node-> llink);
                         
                        break;

                case N_STMT_EMPTY:
                          break;
                case N_STMT_EXPRESSION:
                        n= node->clink;
                        gen_expression(n); 
                        i=n->type-> size;
                      
                       
                        break;
case N_STMT_IF:
gen_expression (node-> llink);





break;
case N_STMT_IF_ELSE:
gen_expression(node-> llink);



break;
case N_STMT_SWITCH:
gen_expression(node-> llink);
;
for (i=1;i<=switch_no;i++) {


}
break;
case N_STMT_WHILE:


gen_expression(node-> llink);



break;


case N_STMT_DO:



gen_expression (node-> rlink);

break;
case N_STMT_FOR:
n=node->llink;

if (n->llink) {
gen_expression(n-> llink);
i=n->llink->type->size;
 }

if (n->clink) {
gen_expression(n-> clink);



if(n-> rlink){
gen_expression(n-> rlink);
i=n-> rlink->type->size;
}
break;
case N_STMT_CONTINUE:

break;
case N_STMT_BREAK:

;
break;
case N_STMT_RETURN: 
n=node->clink;
if(n) {
i=n->type-> size; if (1%4) i=i/4*4+4; 

gen_expression(n);

break;
default :
 
break;
}
}
}
}
void gen_statement_list(A_NODE *node, int cont_label, int break_label, A_SWITCH 
sw[], int *sn) 

{
switch(node->name) {
case N_STMT_LIST:

gen_statement_list(node->rlink, cont_label, break_label, sw,sn); 
break;

case N_STMT_LIST_NIL:
break;
default :

break;
}
}
void gen_initializer_global(A_NODE *node, A_TYPE *t, int addr){

}
void gen_initializer_local(A_NODE *node, A_TYPE *t, int addr){

}

void gen_declaration_list(A_ID *id){
while (id) {
gen_declaration(id); 
id=id->link;
}
}
void gen_declaration(A_ID *id){
                int i;
                A_NODE *node;
                switch (id-> kind) {
                case ID_VAR:
                if (id->init)
                if (id->level==0)
                gen_initializer_global(id ->init,id->type,id->address);
                else
                gen_initializer_local(id-> init, id-> type,id-> address);
                break;
                case ID_FUNC:
                if (id->type->expr) {
                
              
               
                break;
                case ID_PARM:


                case ID_TYPE: case ID_ENUM:
                case ID_STRUCT:
                case ID_FIELD:
                case ID_ENUM_LITERAL:
                case ID_NULL:
                break;
                default: 
                      
                break;
                }
                      
                }
}

