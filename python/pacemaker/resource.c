/*
 * Copyright 2025 the Pacemaker project contributors
 *
 * The version control history for this file may have further details.
 *
 * This source code is licensed under the GNU General Public License version 2
 * or later (GPLv2+) WITHOUT ANY WARRANTY.
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>

PyMODINIT_FUNC PyInit_resource(void);

static PyObject *PacemakerError_Type = NULL;

// Method definitions (empty for now)
static PyMethodDef ResourceMethods[] = {
    {NULL, NULL, 0, NULL}
};

// Module definition
static struct PyModuleDef resourcemodule = {
    PyModuleDef_HEAD_INIT,
    "pacemaker.resource",
    "Pacemaker resource C extension module",
    -1,
    ResourceMethods
};

// Module initialization function
PyMODINIT_FUNC PyInit_resource(void) {
    PyObject *module = NULL;
    PyObject *errors_module = NULL;
    PyObject *temp_pacemaker_error_class = NULL; // Temporary holder

    module = PyModule_Create(&resourcemodule);
    if (module == NULL) {
        // PyModule_Create sets the error, nothing to clean yet
        return NULL;
    }

    errors_module = PyImport_ImportModule("pacemaker.errors");
    if (errors_module == NULL) {
        /* PyImport_ImportModule sets the error */
        goto error_cleanup;
    }

    temp_pacemaker_error_class = PyObject_GetAttrString(errors_module, "PacemakerError");
    if (temp_pacemaker_error_class == NULL) {
        /* PyImport_GetAttrString sets the error */
        goto error_cleanup;
    }

    if (!PyExceptionClass_Check(temp_pacemaker_error_class)) {
        PyErr_SetString(PyExc_TypeError, "pacemaker.errors.PacemakerError is not an exception class.");
        goto error_cleanup;
    }

    // All resources acquired successfully. Now update the global static.
    Py_XDECREF(PacemakerError_Type); // Clean up old one, if any from a previous load.

    PacemakerError_Type = temp_pacemaker_error_class; // Global now holds the new reference from temp_pacemaker_error_class.
    Py_INCREF(PacemakerError_Type); // The global static variable takes its own strong reference.

    // Now we can DECREF our local temp_pacemaker_error_class as its reference
    // (if it was a new one) is either held by PacemakerError_Type or, if it was
    // a borrowed reference (not the case for GetAttrString), it's correctly managed.
    // PyObject_GetAttrString returns a new reference, so we must DECREF it.
    Py_DECREF(temp_pacemaker_error_class);
    temp_pacemaker_error_class = NULL;

    Py_DECREF(errors_module); // Done with the errors_module reference.
    errors_module = NULL;

    return module;

error_cleanup:
    Py_XDECREF(module);
    Py_XDECREF(errors_module);
    Py_XDECREF(temp_pacemaker_error_class);
    return NULL;
}
