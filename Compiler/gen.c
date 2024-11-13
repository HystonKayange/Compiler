#include <stdio.h>
#include<string.h>
#include "type.h"
#include <stdlib.h>



void code_generation(A_NODE *);
void gen_program(A_NODE *); 
void gen_expression(A_NODE *); 
void gen_arg_expression(A_NODE *);
void gen_statement(A_NODE *); 
void gen_statement_list(A_NODE *); 
void gen_initializer_global(A_NODE *);
void gen_declaration_list(A_ID *); 
void gen_declaration(A_ID *); 
void print_A_TYPE(A_TYPE *);
void print_A_ID(A_ID *);
void print_A_ID_NAME(A_ID *);
void print_STRING(char *);
void print_integer(int);
void gen_for_expression(A_NODE *node);



 


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
     switch(node->name) {
	case N_EXP_IDENT:
		print_A_ID_NAME(node->clink);
		break;
	case N_EXP_INT_CONST:
		print_integer(node->clink);
		break;
	case N_EXP_FLOAT_CONST:
		print_STRING(node->clink);
		break;
	case N_EXP_CHAR_CONST:
		print_integer(node->clink);
		break;
	case N_EXP_STRING_LITERAL:
		print_STRING(node->clink);
		break;
	case N_EXP_ARRAY:
		gen_expression(node->llink);
		gen_expression(node->rlink);
		break;
	case N_EXP_FUNCTION_CALL:
		gen_expression(node->llink);
		gen_arg_expression(node->rlink);
		break;
	case N_EXP_STRUCT:
		gen_expression(node->llink);
		printf("struct");
		print_STRING(node->rlink);
		break;
	case N_EXP_ARROW:
		gen_expression(node->llink);
		print_STRING(node->rlink);
		break;
	case N_EXP_POST_INC:
		gen_expression(node->clink);
		printf("++");
		break;
	case N_EXP_POST_DEC:
		gen_expression(node->clink);
		printf("--");
		break;
	case N_EXP_PRE_INC:
		printf("++");
		gen_expression(node->clink);
		break;
	case N_EXP_PRE_DEC:
		printf("--");
		gen_expression(node->clink);
		break;
	case N_EXP_AMP:
	case N_EXP_STAR:
	case N_EXP_NOT:
	case N_EXP_PLUS:
	case N_EXP_MINUS:
	case N_EXP_SIZE_EXP:
		gen_expression(node->clink);
		break;
	case N_EXP_SIZE_TYPE:
		print_A_TYPE(node->clink);
		break;
	case N_EXP_CAST:
		print_A_TYPE(node->llink);
		gen_expression(node->rlink);
		break;
	case N_EXP_MUL:
		gen_expression(node->llink);
		printf(" * ");
		gen_expression(node->rlink);
		break;
	case N_EXP_DIV:
		gen_expression(node->llink);
		printf(" / ");
		gen_expression(node->rlink);
		break;
	case N_EXP_MOD:
			gen_expression(node->llink);
		printf(" %% ");
		gen_expression(node->rlink);
		break;
	case N_EXP_ADD:
		gen_expression(node->llink);
		printf(" + ");
		gen_expression(node->rlink);
		break;
	case N_EXP_SUB:
		gen_expression(node->llink);
		printf(" - ");
		gen_expression(node->rlink);
		break;
	case N_EXP_LSS:
		gen_expression(node->llink);
		printf(" < ");
		gen_expression(node->rlink);
		break;
	case N_EXP_GTR:
		gen_expression(node->llink);
		printf(" > ");
		gen_expression(node->rlink);
		break;
	case N_EXP_LEQ:
		gen_expression(node->llink);
		printf(" <= ");
		gen_expression(node->rlink);
		break;
	case N_EXP_GEQ:
		gen_expression(node->llink);
		printf(" >= ");
		gen_expression(node->rlink);
		break;
	case N_EXP_NEQ:
		gen_expression(node->llink);
		printf(" != ");
		gen_expression(node->rlink);
		break;
	case N_EXP_EQL:
		gen_expression(node->llink);
		printf(" == ");
		gen_expression(node->rlink);
		break;
	case N_EXP_AND:
		gen_expression(node->llink);
		printf(" && ");
		gen_expression(node->rlink);
		break;
	case N_EXP_OR:
		gen_expression(node->llink);
		printf(" || ");
		gen_expression(node->rlink);
		break;
	case N_EXP_ASSIGN:
		gen_expression(node->llink);
		printf("=");
		gen_expression(node->rlink);
		break;
	default:
		
	}
}
        

void gen_statement(A_NODE *node)
{
              switch (node->name) {
	case N_STMT_LABEL_CASE:
		printf("case");
		gen_expression(node->llink);
		printf(":");
		gen_statement(node->rlink);
		break;
	case N_STMT_LABEL_DEFAULT:
		printf("default:");
		gen_statement(node->clink);
		break;
	case N_STMT_COMPOUND:
		printf("{\n");
		if (node->llink)
		gen_declaration_list(node->llink);
		gen_statement_list(node->rlink);
		printf("}\n");
		break;
	case N_STMT_EMPTY:
		printf(";");
		break;
	case N_STMT_EXPRESSION:
		gen_expression(node->clink);
		printf(";\n");
		break;
	case N_STMT_IF_ELSE:
		printf("if ( ");
		gen_expression(node->llink);
		printf(")");
		gen_statement(node->clink);
		printf("else");
		gen_statement(node->rlink);
		break;
	case N_STMT_IF:
		printf("if(");
		gen_expression(node->llink);
		printf(")");
		gen_statement(node->rlink);
		break;
	case N_STMT_SWITCH:
		printf("switch ( ");
		gen_expression(node->llink);
		printf(")");
		gen_statement(node->rlink);
		break;
	case N_STMT_WHILE:
		printf("while ( ");
		gen_expression(node->llink);
		printf(")");
		gen_statement(node->rlink);
		break;
	case N_STMT_DO:
		printf("do");
		gen_statement(node->llink);
		printf("while( ");
		gen_expression(node->rlink);
		printf(")");
		break;
	case N_STMT_FOR:
		printf("for ( ");
		gen_for_expression(node->llink);
		printf(")");
		gen_statement(node->rlink);
		break;
	case N_STMT_CONTINUE:
		printf("continue;");
		break;
	case N_STMT_BREAK:
		printf("break;");
		break;
	case N_STMT_RETURN:
		printf("return ");
		if (node->clink)
		gen_expression(node->clink);
		printf(";");
		break;
	default:
		
		break;
	}
}
void gen_statement_list(A_NODE *node) 

{
        switch (node->name) {
	case N_STMT_LIST:
		gen_statement(node->llink);
		gen_statement_list(node->rlink);
		break;
	case N_STMT_LIST_NIL:
		break;
	default :
		
	} 
}

void gen_initializer_global(A_NODE *node){
    
switch(node->name) {
		case N_INIT_LIST:
			gen_initializer_global(node->llink);
			gen_initializer_global(node->rlink);
			break;
	case N_INIT_LIST_ONE:
		gen_expression(node->clink);
		break;
	case N_INIT_LIST_NIL:
		break;
	default :
		
	}

}



void print_STRING(char *str) {
	printf("(%s)", str);
}
void print_integer(int a)
{
	printf(" %d", a);
}
void print_A_ID_NAME(A_ID *id)
{
	printf("%s", id->name);
}
void print_A_TYPE(A_TYPE *t)
{
	if (t==int_type)
		printf(" int");
	else if (t==float_type)
		printf(" float");
	else if (t==char_type)
		printf(" char %d",t->size);
	else if (t==void_type)
		printf(" void");
	else if (t->kind==T_NULL)
		printf("(null)");
	else
	switch (t->kind) {
		case T_ENUM:
			t->prt=TRUE;
			printf("ENUM\n");
			gen_declaration_list(t->field);
			break;
		case T_POINTER:
			t->prt=TRUE;
			printf("*");
			print_A_TYPE(t->element_type);
			break;
		case T_ARRAY:
			t->prt=TRUE;
			if (t->expr)
				gen_expression(t->expr);
			else {
				printf("(none)\n");}
				printf("| ELEMENT_TYPE\n");
				print_A_TYPE(t->element_type);
			break;
		case T_STRUCT:
			t->prt=TRUE;
			printf("STRUCT\n");
			gen_declaration_list(t->field);
			break;
		case T_UNION:
			t->prt=TRUE;
			printf("UNION\n");
			gen_declaration_list(t->field);
			break;
		case T_FUNC:
			t->prt=TRUE;
			printf("()");
			gen_declaration_list(t->field);
			print_A_TYPE(t->element_type);
			if (t->expr) {
				gen_statement(t->expr);}
			}
}

void print_A_ID(A_ID *id)
{
printf("%s", id->name);
if (id->type) 
{
	print_A_TYPE(id->type);
	printf("\n");
}
if (id->init) 
	{
		printf("| INIT\n");
		if (id->kind==ID_ENUM_LITERAL)
			gen_expression(id->init);
		else
			gen_initializer_global(id->init); 
	}
}

void gen_declaration_list(A_ID *id)
{
	while(id) {
	print_A_ID(id);
	id=id->link;
	}
}

void gen_arg_expression(A_NODE *node){

    switch(node->name) 
	{
		case N_ARG_LIST :
			gen_expression(node->llink);
			gen_arg_expression(node->rlink);
		break;
		case N_ARG_LIST_NIL:
		break;
		default:
		
	}
}
void gen_for_expression(A_NODE *node){
    switch (node->name) {
	case N_FOR_EXP :
	if (node->llink)
		gen_expression(node->llink);
		printf(";");
	if (node->clink)
		gen_expression(node->clink);
		printf(";");
	if (node->rlink)
		gen_expression(node->rlink);
		break;
	}


}
