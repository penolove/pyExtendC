#include <Python.h>

static PyObject *exmodError;

static PyObject* exmod_say_hello(PyObject* self, PyObject *args){
    const char* msg;
    int sts=0;
    if(!PyArg_ParseTuple(args, "s", &msg)){
        return NULL; // return Errors
    }
    if(strcmp(msg,"this_is_an_error")==0){
        PyErr_SetString(exmodError,"Tis is a exception");
    }else{
        printf("This is a C world,\n your msf is %s\n",msg);
        sts=21; //return 0 for success
    }

    return Py_BuildValue("i",sts);
}

//seems to regist the method
static PyMethodDef exmod_methods[] ={
    {"say_hello",  exmod_say_hello, METH_VARARGS, "a fucking hello"},
    {NULL, NULL, 0, NULL}
};

//init function -> it should be called init(name)
PyMODINIT_FUNC initexmod(void){
    PyObject *m;
    m = Py_InitModule("exmod",exmod_methods);
    if(m==NULL) return;

    exmodError = PyErr_NewException("spam.error", NULL, NULL);
    Py_INCREF(exmodError);
    PyModule_AddObject(m, "error", exmodError); //reigst this error
}
