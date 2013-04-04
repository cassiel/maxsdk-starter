/**
        @file
        simplemaxcpp - a max object shell
        jeremy bernstein - jeremy@bootsquad.com

        @ingroup	examples
*/

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object

////////////////////////// object struct
typedef struct _simplemaxcpp
{
        t_object					ob;			// the object itself (must be first)
} t_simplemaxcpp;

///////////////////////// function prototypes
//// standard set
void *simplemaxcpp_new(t_symbol *s, long argc, t_atom *argv);
void simplemaxcpp_free(t_simplemaxcpp *x);
void simplemaxcpp_assist(t_simplemaxcpp *x, void *b, long m, long a, char *s);

//////////////////////// global class pointer variable
t_class *simplemaxcpp_class;


int C74_EXPORT main(void)
{
        // object initialization, OLD STYLE
        // setup((t_messlist **)&simplemaxcpp_class, (method)simplemaxcpp_new, (method)simplemaxcpp_free, (short)sizeof(t_simplemaxcpp),
        //		0L, A_GIMME, 0);
    // addmess((method)simplemaxcpp_assist,			"assist",		A_CANT, 0);

        // object initialization, NEW STYLE
        t_class *c;

        c = class_new("simplemaxcpp", (method)simplemaxcpp_new, (method)simplemaxcpp_free, (long)sizeof(t_simplemaxcpp),
                                  0L /* leave NULL!! */, A_GIMME, 0);

        /* you CAN'T call this from the patcher */
    class_addmethod(c, (method)simplemaxcpp_assist,			"assist",		A_CANT, 0);

        class_register(CLASS_BOX, c); /* CLASS_NOBOX */
        simplemaxcpp_class = c;

        post("I am the simplemaxcpp object");
        return 0;
}

void simplemaxcpp_assist(t_simplemaxcpp *x, void *b, long m, long a, char *s)
{
        if (m == ASSIST_INLET) { // inlet
                sprintf(s, "I am inlet %ld", a);
        }
        else {	// outlet
                sprintf(s, "I am outlet %ld", a);
        }
}

void simplemaxcpp_free(t_simplemaxcpp *x)
{
        ;
}

/*
 A_GIMME signature =
        t_symbol	*s		objectname
        long		argc	num additonal args
        t_atom		*argv	array of t_atom structs
                 type = argv->a_type
                 if (type == A_LONG) ;
                 else if (type == A_FLOAT) ;
                 else if (type == A_SYM) ;
*/
/*
        t_symbol {
                char *s_name;
                t_object *s_thing;
        }
*/
void *simplemaxcpp_new(t_symbol *s, long argc, t_atom *argv)
{
        t_simplemaxcpp *x = NULL;
    long i;

        // object instantiation, OLD STYLE
        // if (x = (t_simplemaxcpp *)newobject(simplemaxcpp_class)) {
        //      ;
        // }

        // object instantiation, NEW STYLE
        if (x = (t_simplemaxcpp *)object_alloc(simplemaxcpp_class)) {
        object_post((t_object *)x, "a new %s object was instantiated: 0x%X", s->s_name, x);
        object_post((t_object *)x, "it has %ld arguments", argc);

        for (i = 0; i < argc; i++) {
            if ((argv + i)->a_type == A_LONG) {
                object_post((t_object *)x, "arg %ld: long (%ld)", i, atom_getlong(argv+i));
            } else if ((argv + i)->a_type == A_FLOAT) {
                object_post((t_object *)x, "arg %ld: float (%f)", i, atom_getfloat(argv+i));
            } else if ((argv + i)->a_type == A_SYM) {
                object_post((t_object *)x, "arg %ld: symbol (%s)", i, atom_getsym(argv+i)->s_name);
            } else {
                object_error((t_object *)x, "forbidden argument");
            }
        }
        }
        return (x);
}
