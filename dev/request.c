
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2012 Phalcon Team (http://www.phalconphp.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@phalconphp.com so we can send you a copy immediately.       |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
  |          Eduar Carvajal <eduar@phalconphp.com>                         |
  +------------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_phalcon.h"
#include "phalcon.h"

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/require.h"
#include "kernel/object.h"
#include "kernel/debug.h"
#include "kernel/assert.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "kernel/memory.h"

#include "Zend/zend_operators.h"
#include "Zend/zend_exceptions.h"
#include "Zend/zend_interfaces.h"

/**
 * Phalcon_Request
 *
 * Encapsulates request information for easy and secure access from application controllers.
 *
 * The request object is a simple value object that is passed between the dispatcher and controller classes.
 * It packages the HTTP request environment.
 *
 * 
 *
 */

/**
 * Gets the singleton instance of Phalcon_Request
 *
 * @return Phalcon_Request
 */
PHP_METHOD(Phalcon_Request, getInstance){

	zval *t0 = NULL, *t1 = NULL;
	zval *i0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_OBSERVE_VAR(t0);
	phalcon_read_static_property(&t0, phalcon_request_ce, "_instance", sizeof("_instance")-1 TSRMLS_CC);
	if (!zend_is_true(t0)) {
		PHALCON_ALLOC_ZVAL_MM(i0);
		object_init_ex(i0, phalcon_request_ce);
		PHALCON_CALL_METHOD_NORETURN(i0, "__construct", PHALCON_CHECK);
		zend_update_static_property(phalcon_request_ce, "_instance", sizeof("_instance")-1, i0 TSRMLS_CC);
	}
	PHALCON_OBSERVE_VAR(t1);
	phalcon_read_static_property(&t1, phalcon_request_ce, "_instance", sizeof("_instance")-1 TSRMLS_CC);
	
	PHALCON_RETURN_CHECK_CTOR(t1);
}

/**
 * Overwrites Phalcon_Filter object used to sanitize input data
     *
 *
 *
 * @param Phalcon_Filter $filter
 */
PHP_METHOD(Phalcon_Request, setFilter){

	zval *filter = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &filter) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_update_property_zval(this_ptr, "_filter", strlen("_filter"), filter TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Returns the active filter object used to sanitize input data
 *
 *
 *
 * @return Phalcon_Filter
 */
PHP_METHOD(Phalcon_Request, getFilter){

	zval *t0 = NULL, *t1 = NULL;
	zval *i0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, "_filter", sizeof("_filter")-1, PHALCON_NOISY TSRMLS_CC);
	if (!zend_is_true(t0)) {
		PHALCON_ALLOC_ZVAL_MM(i0);
		object_init_ex(i0, phalcon_filter_ce);
		PHALCON_CALL_METHOD_NORETURN(i0, "__construct", PHALCON_CHECK);
		phalcon_update_property_zval(this_ptr, "_filter", strlen("_filter"), i0 TSRMLS_CC);
	}
	
	PHALCON_ALLOC_ZVAL_MM(t1);
	phalcon_read_property(&t1, this_ptr, "_filter", sizeof("_filter")-1, PHALCON_NOISY TSRMLS_CC);
	
	PHALCON_RETURN_CHECK_CTOR(t1);
}

/**
 * Gets variable from $_POST superglobal applying filters if needed
 *
 *
 *
 * @param string $name
 * @param string|array $filters
 * @return mixed
 */
PHP_METHOD(Phalcon_Request, getPost){

	zval *name = NULL, *filters = NULL;
	zval *g0 = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|z", &name, &filters) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!filters) {
		PHALCON_INIT_VAR(filters);
		ZVAL_NULL(filters);
	}
	
	phalcon_get_global(&g0, "_POST", sizeof("_POST") TSRMLS_CC);
	eval_int = phalcon_array_isset(g0, name);
	if (eval_int) {
		if (zend_is_true(filters)) {
			PHALCON_ALLOC_ZVAL_MM(r0);
			PHALCON_ALLOC_ZVAL_MM(r1);
			PHALCON_CALL_METHOD(r1, this_ptr, "getfilter", PHALCON_NO_CHECK);
			PHALCON_ALLOC_ZVAL_MM(r2);
			phalcon_array_fetch(&r2, g0, name, PHALCON_NOISY TSRMLS_CC);
			PHALCON_CALL_METHOD_PARAMS_2(r0, r1, "sanitize", r2, filters, PHALCON_NO_CHECK);
			PHALCON_RETURN_DZVAL(r0);
		} else {
			PHALCON_ALLOC_ZVAL_MM(r3);
			phalcon_array_fetch(&r3, g0, name, PHALCON_NOISY TSRMLS_CC);
			
			PHALCON_RETURN_CHECK_CTOR(r3);
		}
	}
	PHALCON_MM_RESTORE();
	RETURN_NULL();
}

/**
 * Gets variable from $_GET superglobal applying filters if needed
     *
 *
 *
 * @param string $name
 * @param string|array $filters
 * @return mixed
 */
PHP_METHOD(Phalcon_Request, getQuery){

	zval *name = NULL, *filters = NULL;
	zval *g0 = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|z", &name, &filters) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!filters) {
		PHALCON_INIT_VAR(filters);
		ZVAL_NULL(filters);
	}
	
	phalcon_get_global(&g0, "_GET", sizeof("_GET") TSRMLS_CC);
	eval_int = phalcon_array_isset(g0, name);
	if (eval_int) {
		if (zend_is_true(filters)) {
			PHALCON_ALLOC_ZVAL_MM(r0);
			PHALCON_ALLOC_ZVAL_MM(r1);
			PHALCON_CALL_METHOD(r1, this_ptr, "getfilter", PHALCON_NO_CHECK);
			PHALCON_ALLOC_ZVAL_MM(r2);
			phalcon_array_fetch(&r2, g0, name, PHALCON_NOISY TSRMLS_CC);
			PHALCON_CALL_METHOD_PARAMS_2(r0, r1, "sanitize", r2, filters, PHALCON_NO_CHECK);
			PHALCON_RETURN_DZVAL(r0);
		} else {
			PHALCON_ALLOC_ZVAL_MM(r3);
			phalcon_array_fetch(&r3, g0, name, PHALCON_NOISY TSRMLS_CC);
			
			PHALCON_RETURN_CHECK_CTOR(r3);
		}
	}
	PHALCON_MM_RESTORE();
	RETURN_NULL();
}

/**
 * Gets variable from $_SERVER superglobal
 *
 * @param string $name
 * @return mixed
 */
PHP_METHOD(Phalcon_Request, getServer){

	zval *name = NULL;
	zval *g0 = NULL;
	zval *r0 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &name) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_get_global(&g0, "_SERVER", sizeof("_SERVER") TSRMLS_CC);
	eval_int = phalcon_array_isset(g0, name);
	if (eval_int) {
		PHALCON_ALLOC_ZVAL_MM(r0);
		phalcon_array_fetch(&r0, g0, name, PHALCON_NOISY TSRMLS_CC);
		
		PHALCON_RETURN_CHECK_CTOR(r0);
	}
	PHALCON_MM_RESTORE();
	RETURN_NULL();
}

/**
 * Checks whether $_POST superglobal has certain index
 *
 * @param string $name
 * @return boolean
 */
PHP_METHOD(Phalcon_Request, hasPost){

	zval *name = NULL;
	zval *g0 = NULL;
	zval *r0 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &name) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_get_global(&g0, "_POST", sizeof("_POST") TSRMLS_CC);
	eval_int = phalcon_array_isset(g0, name);
	PHALCON_INIT_VAR(r0);
	ZVAL_BOOL(r0, eval_int);
	
	PHALCON_RETURN_NCTOR(r0);
}

/**
 * Checks whether $_SERVER superglobal has certain index
 *
 * @param string $name
 * @return boolean
 */
PHP_METHOD(Phalcon_Request, hasQuery){

	zval *name = NULL;
	zval *g0 = NULL;
	zval *r0 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &name) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_get_global(&g0, "_GET", sizeof("_GET") TSRMLS_CC);
	eval_int = phalcon_array_isset(g0, name);
	PHALCON_INIT_VAR(r0);
	ZVAL_BOOL(r0, eval_int);
	
	PHALCON_RETURN_NCTOR(r0);
}

/**
 * Checks whether $_SERVER superglobal has certain index
 *
 * @param string $name
 * @return mixed
 */
PHP_METHOD(Phalcon_Request, hasServer){

	zval *name = NULL;
	zval *g0 = NULL;
	zval *r0 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &name) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_get_global(&g0, "_SERVER", sizeof("_SERVER") TSRMLS_CC);
	eval_int = phalcon_array_isset(g0, name);
	PHALCON_INIT_VAR(r0);
	ZVAL_BOOL(r0, eval_int);
	
	PHALCON_RETURN_NCTOR(r0);
}

/**
 * Gets HTTP header from request data
 *
 * @param string $header
 * @return string
 */
PHP_METHOD(Phalcon_Request, getHeader){

	zval *header = NULL;
	zval *g0 = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &header) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_get_global(&g0, "_SERVER", sizeof("_SERVER") TSRMLS_CC);
	eval_int = phalcon_array_isset(g0, header);
	if (eval_int) {
		PHALCON_ALLOC_ZVAL_MM(r0);
		phalcon_array_fetch(&r0, g0, header, PHALCON_NOISY TSRMLS_CC);
		
		PHALCON_RETURN_CHECK_CTOR(r0);
	} else {
		PHALCON_ALLOC_ZVAL_MM(r1);
		PHALCON_CONCAT_SV(r1, "HTTP_", header);
		eval_int = phalcon_array_isset(g0, r1);
		if (eval_int) {
			PHALCON_ALLOC_ZVAL_MM(r2);
			PHALCON_CONCAT_SV(r2, "HTTP_", header);
			PHALCON_ALLOC_ZVAL_MM(r3);
			phalcon_array_fetch(&r3, g0, r2, PHALCON_NOISY TSRMLS_CC);
			
			PHALCON_RETURN_CHECK_CTOR(r3);
		}
	}
	PHALCON_MM_RESTORE();
	RETURN_STRING("", 1);
}

/**
 * Gets HTTP schema (http/https)
 *
 * @return string
 */
PHP_METHOD(Phalcon_Request, getScheme){

	zval *r0 = NULL;
	zval *c0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_INIT_VAR(c0);
	ZVAL_STRING(c0, "HTTP_HTTPS", 1);
	PHALCON_CALL_METHOD_PARAMS_1(r0, this_ptr, "getserver", c0, PHALCON_NO_CHECK);
	if (PHALCON_COMPARE_STRING(r0, "on")) {
		PHALCON_MM_RESTORE();
		RETURN_STRING("https", 1);
	}
	PHALCON_MM_RESTORE();
	RETURN_STRING("http", 1);
}

/**
 * Checks whether request has been made using ajax
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Request, isAjax){

	zval *r0 = NULL, *r1 = NULL;
	zval *c0 = NULL;
	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_INIT_VAR(c0);
	ZVAL_STRING(c0, "HTTP_X_REQUESTED_WITH", 1);
	PHALCON_CALL_METHOD_PARAMS_1(r0, this_ptr, "getheader", c0, PHALCON_NO_CHECK);
	PHALCON_INIT_VAR(t0);
	ZVAL_STRING(t0, "XMLHttpRequest", 1);
	PHALCON_ALLOC_ZVAL_MM(r1);
	is_equal_function(r1, r0, t0 TSRMLS_CC);
	
	PHALCON_RETURN_NCTOR(r1);
}

/**
 * Checks whether request has been made using SOAP
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Request, isSoapRequested){

	zval *g0 = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL;
	zval *c0 = NULL;
	zval *t0 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	phalcon_get_global(&g0, "_SERVER", sizeof("_SERVER") TSRMLS_CC);
	eval_int = phalcon_array_isset_string(g0, "HTTP_SOAPACTION", strlen("HTTP_SOAPACTION")+1);
	if (eval_int) {
		PHALCON_MM_RESTORE();
		RETURN_TRUE;
	} else {
		eval_int = phalcon_array_isset_string(g0, "CONTENT_TYPE", strlen("CONTENT_TYPE")+1);
		if (eval_int) {
			PHALCON_ALLOC_ZVAL_MM(r0);
			phalcon_array_fetch_string(&r0, g0, "CONTENT_TYPE", strlen("CONTENT_TYPE"), PHALCON_NOISY TSRMLS_CC);
			PHALCON_INIT_VAR(c0);
			ZVAL_STRING(c0, "application/soap+xml", 1);
			PHALCON_ALLOC_ZVAL_MM(r1);
			phalcon_fast_strpos(r1, r0, c0 TSRMLS_CC);
			PHALCON_INIT_VAR(t0);
			ZVAL_BOOL(t0, 0);
			PHALCON_INIT_VAR(r2);
			is_not_identical_function(r2, t0, r1 TSRMLS_CC);
			
			PHALCON_RETURN_NCTOR(r2);
		}
	}
	PHALCON_MM_RESTORE();
	RETURN_FALSE;
}

/**
 * Checks whether request has been made using any secure layer
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Request, isSecureRequest){

	zval *r0 = NULL, *r1 = NULL;
	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD(r0, this_ptr, "getscheme", PHALCON_NO_CHECK);
	PHALCON_INIT_VAR(t0);
	ZVAL_STRING(t0, "https", 1);
	PHALCON_INIT_VAR(r1);
	is_identical_function(r1, t0, r0 TSRMLS_CC);
	
	PHALCON_RETURN_NCTOR(r1);
}

/**
 * Gets HTTP raws request body
 *
 * @return string
 */
PHP_METHOD(Phalcon_Request, getRawBody){

	zval *r0 = NULL;
	zval *c0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_INIT_VAR(c0);
	ZVAL_STRING(c0, "php://input", 1);
	PHALCON_CALL_FUNC_PARAMS_1(r0, "file_get_contents", c0, 0x01A);
	PHALCON_RETURN_DZVAL(r0);
}

/**
 * Gets active server address IP
 *
 * @return string
 */
PHP_METHOD(Phalcon_Request, getServerAddress){

	zval *g0 = NULL;
	zval *r0 = NULL, *r1 = NULL;
	zval *c0 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	phalcon_get_global(&g0, "_SERVER", sizeof("_SERVER") TSRMLS_CC);
	eval_int = phalcon_array_isset_string(g0, "SERVER_ADDR", strlen("SERVER_ADDR")+1);
	if (eval_int) {
		PHALCON_ALLOC_ZVAL_MM(r0);
		phalcon_array_fetch_string(&r0, g0, "SERVER_ADDR", strlen("SERVER_ADDR"), PHALCON_NOISY TSRMLS_CC);
		
		PHALCON_RETURN_CHECK_CTOR(r0);
	}
	
	PHALCON_ALLOC_ZVAL_MM(r1);
	
	PHALCON_INIT_VAR(c0);
	ZVAL_STRING(c0, "localhost", 1);
	PHALCON_CALL_FUNC_PARAMS_1(r1, "gethostbyname", c0, 0x047);
	PHALCON_RETURN_DZVAL(r1);
}

/**
 * Gets active server name
 *
 * @return string
 */
PHP_METHOD(Phalcon_Request, getServerName){

	zval *g0 = NULL;
	zval *r0 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	phalcon_get_global(&g0, "_SERVER", sizeof("_SERVER") TSRMLS_CC);
	eval_int = phalcon_array_isset_string(g0, "SERVER_NAME", strlen("SERVER_NAME")+1);
	if (eval_int) {
		PHALCON_ALLOC_ZVAL_MM(r0);
		phalcon_array_fetch_string(&r0, g0, "SERVER_NAME", strlen("SERVER_NAME"), PHALCON_NOISY TSRMLS_CC);
		
		PHALCON_RETURN_CHECK_CTOR(r0);
	}
	PHALCON_MM_RESTORE();
	RETURN_STRING("localhost", 1);
}

/**
 * Gets information about schema, host and port used by the request
 *
 * @return string
 */
PHP_METHOD(Phalcon_Request, getHttpHost){

	zval *scheme = NULL, *name = NULL, *port = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL, *r4 = NULL, *r5 = NULL, *r6 = NULL;
	zval *r7 = NULL, *r8 = NULL, *r9 = NULL, *r10 = NULL;
	zval *c0 = NULL, *c1 = NULL;
	zval *t0 = NULL, *t1 = NULL, *t2 = NULL, *t3 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD(r0, this_ptr, "getscheme", PHALCON_NO_CHECK);
	PHALCON_CPY_WRT(scheme, r0);
	
	PHALCON_ALLOC_ZVAL_MM(r1);
	
	PHALCON_INIT_VAR(c0);
	ZVAL_STRING(c0, "HTTP_SERVER_NAME", 1);
	PHALCON_CALL_METHOD_PARAMS_1(r1, this_ptr, "getserver", c0, PHALCON_NO_CHECK);
	PHALCON_CPY_WRT(name, r1);
	
	PHALCON_ALLOC_ZVAL_MM(r2);
	
	PHALCON_INIT_VAR(c1);
	ZVAL_STRING(c1, "HTTP_SERVER_PORT", 1);
	PHALCON_CALL_METHOD_PARAMS_1(r2, this_ptr, "getserver", c1, PHALCON_NO_CHECK);
	PHALCON_CPY_WRT(port, r2);
	
	PHALCON_INIT_VAR(t0);
	ZVAL_STRING(t0, "http", 1);
	
	PHALCON_ALLOC_ZVAL_MM(r3);
	is_equal_function(r3, scheme, t0 TSRMLS_CC);
	
	PHALCON_INIT_VAR(t1);
	ZVAL_LONG(t1, 80);
	
	PHALCON_ALLOC_ZVAL_MM(r4);
	is_equal_function(r4, port, t1 TSRMLS_CC);
	
	PHALCON_INIT_VAR(r5);
	phalcon_and_function(r5, r3, r4);
	
	PHALCON_INIT_VAR(t2);
	ZVAL_STRING(t2, "https", 1);
	
	PHALCON_ALLOC_ZVAL_MM(r6);
	is_equal_function(r6, scheme, t2 TSRMLS_CC);
	
	PHALCON_INIT_VAR(t3);
	ZVAL_LONG(t3, 443);
	
	PHALCON_ALLOC_ZVAL_MM(r7);
	is_equal_function(r7, port, t3 TSRMLS_CC);
	
	PHALCON_INIT_VAR(r8);
	phalcon_and_function(r8, r6, r7);
	
	PHALCON_INIT_VAR(r9);
	ZVAL_BOOL(r9, zend_is_true(r5) || zend_is_true(r8));
	if (zend_is_true(r9)) {
		
		PHALCON_RETURN_CHECK_CTOR(name);
	}
	
	PHALCON_ALLOC_ZVAL_MM(r10);
	PHALCON_CONCAT_VSV(r10, name, ":", port);
	
	PHALCON_RETURN_CTOR(r10);
}

/**
 * Gets most possibly client IPv4 Address. This methods search in $_SERVER['HTTP_X_FORWARDED_FOR'] and $_SERVER['REMOTE_ADDR']
 *
 * @return string
 */
PHP_METHOD(Phalcon_Request, getClientAddress){

	zval *address = NULL;
	zval *g0 = NULL;
	zval *r0 = NULL, *r1 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	PHALCON_INIT_VAR(address);
	ZVAL_STRING(address, "", 1);
	phalcon_get_global(&g0, "_SERVER", sizeof("_SERVER") TSRMLS_CC);
	eval_int = phalcon_array_isset_string(g0, "HTTP_X_FORWARDED_FOR", strlen("HTTP_X_FORWARDED_FOR")+1);
	if (eval_int) {
		PHALCON_ALLOC_ZVAL_MM(r0);
		phalcon_array_fetch_string(&r0, g0, "HTTP_X_FORWARDED_FOR", strlen("HTTP_X_FORWARDED_FOR"), PHALCON_NOISY TSRMLS_CC);
		PHALCON_CPY_WRT(address, r0);
	} else {
		eval_int = phalcon_array_isset_string(g0, "REMOTE_ADDR", strlen("REMOTE_ADDR")+1);
		if (eval_int) {
			PHALCON_ALLOC_ZVAL_MM(r1);
			phalcon_array_fetch_string(&r1, g0, "REMOTE_ADDR", strlen("REMOTE_ADDR"), PHALCON_NOISY TSRMLS_CC);
			PHALCON_CPY_WRT(address, r1);
		}
	}
	
	
	PHALCON_RETURN_CHECK_CTOR(address);
}

/**
 * Gets HTTP method which request has been made
 *
 * @return string
 */
PHP_METHOD(Phalcon_Request, getMethod){

	zval *g0 = NULL;
	zval *r0 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	phalcon_get_global(&g0, "_SERVER", sizeof("_SERVER") TSRMLS_CC);
	eval_int = phalcon_array_isset_string(g0, "REQUEST_METHOD", strlen("REQUEST_METHOD")+1);
	if (eval_int) {
		PHALCON_ALLOC_ZVAL_MM(r0);
		phalcon_array_fetch_string(&r0, g0, "REQUEST_METHOD", strlen("REQUEST_METHOD"), PHALCON_NOISY TSRMLS_CC);
		
		PHALCON_RETURN_CHECK_CTOR(r0);
	}
	PHALCON_MM_RESTORE();
	RETURN_STRING("", 1);
}

/**
 * Gets HTTP user agent used to made the request
 *
 * @return string
 */
PHP_METHOD(Phalcon_Request, getUserAgent){

	zval *g0 = NULL;
	zval *r0 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	phalcon_get_global(&g0, "_SERVER", sizeof("_SERVER") TSRMLS_CC);
	eval_int = phalcon_array_isset_string(g0, "HTTP_USER_AGENT", strlen("HTTP_USER_AGENT")+1);
	if (eval_int) {
		PHALCON_ALLOC_ZVAL_MM(r0);
		phalcon_array_fetch_string(&r0, g0, "HTTP_USER_AGENT", strlen("HTTP_USER_AGENT"), PHALCON_NOISY TSRMLS_CC);
		
		PHALCON_RETURN_CHECK_CTOR(r0);
	}
	PHALCON_MM_RESTORE();
	RETURN_STRING("", 1);
}

/**
 * Checks whether HTTP method is POST. if $_SERVER['REQUEST_METHOD']=='POST'
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Request, isPost){

	zval *r0 = NULL, *r1 = NULL;
	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD(r0, this_ptr, "getmethod", PHALCON_NO_CHECK);
	PHALCON_INIT_VAR(t0);
	ZVAL_STRING(t0, "POST", 1);
	PHALCON_ALLOC_ZVAL_MM(r1);
	is_equal_function(r1, r0, t0 TSRMLS_CC);
	
	PHALCON_RETURN_NCTOR(r1);
}

/**
 *
 * Checks whether HTTP method is GET. if $_SERVER['REQUEST_METHOD']=='GET'
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Request, isGet){

	zval *r0 = NULL, *r1 = NULL;
	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD(r0, this_ptr, "getmethod", PHALCON_NO_CHECK);
	PHALCON_INIT_VAR(t0);
	ZVAL_STRING(t0, "GET", 1);
	PHALCON_ALLOC_ZVAL_MM(r1);
	is_equal_function(r1, r0, t0 TSRMLS_CC);
	
	PHALCON_RETURN_NCTOR(r1);
}

/**
 * Checks whether HTTP method is PUT. if $_SERVER['REQUEST_METHOD']=='PUT'
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Request, isPut){

	zval *r0 = NULL, *r1 = NULL;
	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD(r0, this_ptr, "getmethod", PHALCON_NO_CHECK);
	PHALCON_INIT_VAR(t0);
	ZVAL_STRING(t0, "PUT", 1);
	PHALCON_ALLOC_ZVAL_MM(r1);
	is_equal_function(r1, r0, t0 TSRMLS_CC);
	
	PHALCON_RETURN_NCTOR(r1);
}

/**
 * Checks whether HTTP method is HEAD. if $_SERVER['REQUEST_METHOD']=='HEAD'
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Request, isHead){

	zval *r0 = NULL, *r1 = NULL;
	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD(r0, this_ptr, "getmethod", PHALCON_NO_CHECK);
	PHALCON_INIT_VAR(t0);
	ZVAL_STRING(t0, "HEAD", 1);
	PHALCON_ALLOC_ZVAL_MM(r1);
	is_equal_function(r1, r0, t0 TSRMLS_CC);
	
	PHALCON_RETURN_NCTOR(r1);
}

/**
 * Checks whether HTTP method is DELETE. if $_SERVER['REQUEST_METHOD']=='DELETE'
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Request, isDelete){

	zval *r0 = NULL, *r1 = NULL;
	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD(r0, this_ptr, "getmethod", PHALCON_NO_CHECK);
	PHALCON_INIT_VAR(t0);
	ZVAL_STRING(t0, "DELETE", 1);
	PHALCON_ALLOC_ZVAL_MM(r1);
	is_equal_function(r1, r0, t0 TSRMLS_CC);
	
	PHALCON_RETURN_NCTOR(r1);
}

/**
 * Checks whether HTTP method is OPTIONS. if $_SERVER['REQUEST_METHOD']=='OPTIONS'
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Request, isOptions){

	zval *r0 = NULL, *r1 = NULL;
	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD(r0, this_ptr, "getmethod", PHALCON_NO_CHECK);
	PHALCON_INIT_VAR(t0);
	ZVAL_STRING(t0, "OPTIONS", 1);
	PHALCON_ALLOC_ZVAL_MM(r1);
	is_equal_function(r1, r0, t0 TSRMLS_CC);
	
	PHALCON_RETURN_NCTOR(r1);
}

/**
 * Checks whether request include attached files
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Request, hasFiles){

	zval *g0 = NULL;
	zval *r0 = NULL, *r1 = NULL;
	zval *t0 = NULL;

	PHALCON_MM_GROW();
	phalcon_get_global(&g0, "_FILES", sizeof("_FILES") TSRMLS_CC);
	if (zend_is_true(g0)) {
		PHALCON_ALLOC_ZVAL_MM(r0);
		phalcon_fast_count(r0, g0 TSRMLS_CC);
		PHALCON_INIT_VAR(t0);
		ZVAL_LONG(t0, 0);
		PHALCON_INIT_VAR(r1);
		is_smaller_function(r1, t0, r0 TSRMLS_CC);
		
		PHALCON_RETURN_NCTOR(r1);
	}
	PHALCON_MM_RESTORE();
	RETURN_FALSE;
}

/**
 * Gets attached files as Phalcon_Request_File instances
 *
 * @return Phalcon_Request_File[]
 */
PHP_METHOD(Phalcon_Request, getUploadedFiles){

	zval *super_files = NULL, *files = NULL, *file = NULL;
	zval *g0 = NULL;
	zval *r0 = NULL;
	zval *a0 = NULL, *a1 = NULL;
	zval *i0 = NULL;
	HashTable *ah0;
	HashPosition hp0;
	zval **hd;

	PHALCON_MM_GROW();
	phalcon_get_global(&g0, "_FILES", sizeof("_FILES") TSRMLS_CC);
	PHALCON_CPY_WRT(super_files, g0);
	
	PHALCON_ALLOC_ZVAL_MM(r0);
	phalcon_fast_count(r0, super_files TSRMLS_CC);
	if (zend_is_true(r0)) {
		PHALCON_INIT_VAR(a0);
		array_init(a0);
		PHALCON_CPY_WRT(files, a0);
		if (phalcon_valid_foreach(super_files TSRMLS_CC)) {
			ah0 = Z_ARRVAL_P(super_files);
			zend_hash_internal_pointer_reset_ex(ah0, &hp0);
			fes_9aea_0:
			if(zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) != SUCCESS){
				goto fee_9aea_0;
			}
			
			PHALCON_INIT_VAR(file);
			ZVAL_ZVAL(file, *hd, 1, 0);
			PHALCON_INIT_VAR(i0);
			object_init_ex(i0, phalcon_request_file_ce);
			PHALCON_CALL_METHOD_PARAMS_1_NORETURN(i0, "__construct", file, PHALCON_CHECK);
			phalcon_array_append(&files, i0, PHALCON_SEPARATE_PLZ TSRMLS_CC);
			zend_hash_move_forward_ex(ah0, &hp0);
			goto fes_9aea_0;
			fee_9aea_0:
			if(0){}
		} else {
			return;
		}
		
		PHALCON_RETURN_CTOR(files);
	}
	
	PHALCON_INIT_VAR(a1);
	array_init(a1);
	
	PHALCON_RETURN_CTOR(a1);
}

/**
 * Gets web page that refers active request. ie: http://www.google.com
 *
 * @return string
 */
PHP_METHOD(Phalcon_Request, getHTTPReferer){

	zval *g0 = NULL;
	zval *r0 = NULL;
	int eval_int;

	PHALCON_MM_GROW();
	phalcon_get_global(&g0, "_SERVER", sizeof("_SERVER") TSRMLS_CC);
	eval_int = phalcon_array_isset_string(g0, "HTTP_REFERER", strlen("HTTP_REFERER")+1);
	if (eval_int) {
		PHALCON_ALLOC_ZVAL_MM(r0);
		phalcon_array_fetch_string(&r0, g0, "HTTP_REFERER", strlen("HTTP_REFERER"), PHALCON_NOISY TSRMLS_CC);
		
		PHALCON_RETURN_CHECK_CTOR(r0);
	}
	PHALCON_MM_RESTORE();
	RETURN_STRING("", 1);
}

/**
 * Process a request header and return an array of values with their qualities
 *
 * @param string $serverIndex
 * @param string $name
 * @return array
 */
PHP_METHOD(Phalcon_Request, _getQualityHeader){

	zval *server_index = NULL, *name = NULL, *http_server = NULL, *parts = NULL;
	zval *returned_parts = NULL, *part = NULL, *header_parts = NULL, *quality = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL, *r4 = NULL, *r5 = NULL;
	zval *c0 = NULL, *c1 = NULL, *c2 = NULL;
	zval *a0 = NULL, *a1 = NULL;
	HashTable *ah0;
	HashPosition hp0;
	zval **hd;
	int eval_int;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &server_index, &name) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD_PARAMS_1(r0, this_ptr, "getserver", server_index, PHALCON_NO_CHECK);
	PHALCON_CPY_WRT(http_server, r0);
	
	PHALCON_ALLOC_ZVAL_MM(r1);
	
	PHALCON_INIT_VAR(c0);
	ZVAL_STRING(c0, "/,\\s*/", 1);
	PHALCON_CALL_FUNC_PARAMS_2(r1, "preg_split", c0, http_server, 0x048);
	PHALCON_CPY_WRT(parts, r1);
	
	PHALCON_INIT_VAR(a0);
	array_init(a0);
	PHALCON_CPY_WRT(returned_parts, a0);
	if (phalcon_valid_foreach(parts TSRMLS_CC)) {
		ah0 = Z_ARRVAL_P(parts);
		zend_hash_internal_pointer_reset_ex(ah0, &hp0);
		fes_9aea_1:
		if(zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) != SUCCESS){
			goto fee_9aea_1;
		}
		
		PHALCON_INIT_VAR(part);
		ZVAL_ZVAL(part, *hd, 1, 0);
		PHALCON_INIT_VAR(c1);
		ZVAL_STRING(c1, ";", 1);
		PHALCON_INIT_VAR(r2);
		phalcon_fast_explode(r2, c1, part TSRMLS_CC);
		PHALCON_CPY_WRT(header_parts, r2);
		eval_int = phalcon_array_isset_long(header_parts, 1);
		if (eval_int) {
			PHALCON_INIT_VAR(r3);
			PHALCON_INIT_VAR(r4);
			phalcon_array_fetch_long(&r4, header_parts, 1, PHALCON_NOISY TSRMLS_CC);
			PHALCON_INIT_VAR(c2);
			ZVAL_LONG(c2, 2);
			PHALCON_CALL_FUNC_PARAMS_2(r3, "substr", r4, c2, 0x002);
			PHALCON_CPY_WRT(quality, r3);
		} else {
			PHALCON_INIT_VAR(quality);
			ZVAL_DOUBLE(quality, 1);
		}
		
		PHALCON_INIT_VAR(a1);
		array_init(a1);
		
		PHALCON_INIT_VAR(r5);
		phalcon_array_fetch_long(&r5, header_parts, 0, PHALCON_NOISY TSRMLS_CC);
		phalcon_array_update(&a1, name, &r5, PHALCON_SEPARATE_PLZ, PHALCON_COPY, PHALCON_NO_CTOR TSRMLS_CC);
		phalcon_array_update_string(&a1, "quality", strlen("quality"), &quality, PHALCON_SEPARATE_PLZ, PHALCON_COPY, PHALCON_NO_CTOR TSRMLS_CC);
		phalcon_array_append(&returned_parts, a1, PHALCON_SEPARATE_PLZ TSRMLS_CC);
		zend_hash_move_forward_ex(ah0, &hp0);
		goto fes_9aea_1;
		fee_9aea_1:
		if(0){}
	} else {
		return;
	}
	
	PHALCON_RETURN_CTOR(returned_parts);
}

/**
 * Process a request header and return the one with best quality
 *
 * @param array $qualityParts
 * @param string $name
 * @return string
 */
PHP_METHOD(Phalcon_Request, _getBestQuality){

	zval *quality_parts = NULL, *name = NULL, *i = NULL, *quality = NULL, *selected_name = NULL;
	zval *accept = NULL;
	zval *t0 = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL, *r4 = NULL, *r5 = NULL, *r6 = NULL;
	HashTable *ah0;
	HashPosition hp0;
	zval **hd;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &quality_parts, &name) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_INIT_VAR(i);
	ZVAL_LONG(i, 0);
	
	PHALCON_INIT_VAR(quality);
	ZVAL_LONG(quality, 0);
	
	PHALCON_INIT_VAR(selected_name);
	ZVAL_STRING(selected_name, "", 1);
	if (phalcon_valid_foreach(quality_parts TSRMLS_CC)) {
		ah0 = Z_ARRVAL_P(quality_parts);
		zend_hash_internal_pointer_reset_ex(ah0, &hp0);
		fes_9aea_2:
		if(zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) != SUCCESS){
			goto fee_9aea_2;
		}
		
		PHALCON_INIT_VAR(accept);
		ZVAL_ZVAL(accept, *hd, 1, 0);
		PHALCON_INIT_VAR(t0);
		ZVAL_LONG(t0, 0);
		PHALCON_INIT_VAR(r0);
		is_equal_function(r0, i, t0 TSRMLS_CC);
		if (zend_is_true(r0)) {
			PHALCON_INIT_VAR(r1);
			phalcon_array_fetch_string(&r1, accept, "quality", strlen("quality"), PHALCON_NOISY TSRMLS_CC);
			PHALCON_CPY_WRT(quality, r1);
			
			PHALCON_INIT_VAR(r2);
			phalcon_array_fetch(&r2, accept, name, PHALCON_NOISY TSRMLS_CC);
			PHALCON_CPY_WRT(selected_name, r2);
		} else {
			PHALCON_INIT_VAR(r3);
			phalcon_array_fetch_string(&r3, accept, "quality", strlen("quality"), PHALCON_NOISY TSRMLS_CC);
			PHALCON_INIT_VAR(r4);
			is_smaller_function(r4, quality, r3 TSRMLS_CC);
			if (zend_is_true(r4)) {
				PHALCON_INIT_VAR(r5);
				phalcon_array_fetch_string(&r5, accept, "quality", strlen("quality"), PHALCON_NOISY TSRMLS_CC);
				PHALCON_CPY_WRT(quality, r5);
				
				PHALCON_INIT_VAR(r6);
				phalcon_array_fetch(&r6, accept, name, PHALCON_NOISY TSRMLS_CC);
				PHALCON_CPY_WRT(selected_name, r6);
			}
		}
		PHALCON_SEPARATE(i);
		increment_function(i);
		zend_hash_move_forward_ex(ah0, &hp0);
		goto fes_9aea_2;
		fee_9aea_2:
		if(0){}
	} else {
		return;
	}
	
	PHALCON_RETURN_CHECK_CTOR(selected_name);
}

/**
 * Gets array with mime/types and their quality accepted by the browser/client from $_SERVER['HTTP_ACCEPT']
 *
 * @return array
 */
PHP_METHOD(Phalcon_Request, getAcceptableContent){

	zval *r0 = NULL;
	zval *c0 = NULL, *c1 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_INIT_VAR(c0);
	ZVAL_STRING(c0, "HTTP_ACCEPT", 1);
	PHALCON_INIT_VAR(c1);
	ZVAL_STRING(c1, "accept", 1);
	PHALCON_CALL_METHOD_PARAMS_2(r0, this_ptr, "_getqualityheader", c0, c1, PHALCON_NO_CHECK);
	PHALCON_RETURN_DZVAL(r0);
}

/**
 * Gets best mime/type accepted by the browser/client from $_SERVER['HTTP_ACCEPT']
 *
 * @return array
 */
PHP_METHOD(Phalcon_Request, getBestAccept){

	zval *r0 = NULL, *r1 = NULL;
	zval *c0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_ALLOC_ZVAL_MM(r1);
	PHALCON_CALL_METHOD(r1, this_ptr, "getacceptablecontent", PHALCON_NO_CHECK);
	PHALCON_INIT_VAR(c0);
	ZVAL_STRING(c0, "accept", 1);
	PHALCON_CALL_METHOD_PARAMS_2(r0, this_ptr, "_getbestquality", r1, c0, PHALCON_NO_CHECK);
	PHALCON_RETURN_DZVAL(r0);
}

/**
 * Gets charsets array and their quality accepted by the browser/client from $_SERVER['HTTP_ACCEPT_CHARSET']
 *
 * @return array
 */
PHP_METHOD(Phalcon_Request, getClientCharsets){

	zval *r0 = NULL;
	zval *c0 = NULL, *c1 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_INIT_VAR(c0);
	ZVAL_STRING(c0, "HTTP_ACCEPT_CHARSET", 1);
	PHALCON_INIT_VAR(c1);
	ZVAL_STRING(c1, "charset", 1);
	PHALCON_CALL_METHOD_PARAMS_2(r0, this_ptr, "_getqualityheader", c0, c1, PHALCON_NO_CHECK);
	PHALCON_RETURN_DZVAL(r0);
}

/**
 * Gets best charset accepted by the browser/client from $_SERVER['HTTP_ACCEPT_CHARSET']
 *
 * @return string
 */
PHP_METHOD(Phalcon_Request, getBestCharset){

	zval *r0 = NULL, *r1 = NULL;
	zval *c0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_ALLOC_ZVAL_MM(r1);
	PHALCON_CALL_METHOD(r1, this_ptr, "getclientcharsets", PHALCON_NO_CHECK);
	PHALCON_INIT_VAR(c0);
	ZVAL_STRING(c0, "charset", 1);
	PHALCON_CALL_METHOD_PARAMS_2(r0, this_ptr, "_getbestquality", r1, c0, PHALCON_NO_CHECK);
	PHALCON_RETURN_DZVAL(r0);
}

/**
 * Gets languages array and their quality accepted by the browser/client from $_SERVER['HTTP_ACCEPT_LANGUAGE']
 *
 * @return array
 */
PHP_METHOD(Phalcon_Request, getLanguages){

	zval *r0 = NULL;
	zval *c0 = NULL, *c1 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_INIT_VAR(c0);
	ZVAL_STRING(c0, "HTTP_ACCEPT_LANGUAGE", 1);
	PHALCON_INIT_VAR(c1);
	ZVAL_STRING(c1, "language", 1);
	PHALCON_CALL_METHOD_PARAMS_2(r0, this_ptr, "_getqualityheader", c0, c1, PHALCON_NO_CHECK);
	PHALCON_RETURN_DZVAL(r0);
}

/**
 * Gets best language accepted by the browser/client from $_SERVER['HTTP_ACCEPT_LANGUAGE']
 *
 * @return string
 */
PHP_METHOD(Phalcon_Request, getBestLanguage){

	zval *r0 = NULL, *r1 = NULL;
	zval *c0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_ALLOC_ZVAL_MM(r1);
	PHALCON_CALL_METHOD(r1, this_ptr, "getlanguages", PHALCON_NO_CHECK);
	PHALCON_INIT_VAR(c0);
	ZVAL_STRING(c0, "language", 1);
	PHALCON_CALL_METHOD_PARAMS_2(r0, this_ptr, "_getbestquality", r1, c0, PHALCON_NO_CHECK);
	PHALCON_RETURN_DZVAL(r0);
}

/**
 * Resets the internal singleton
 */
PHP_METHOD(Phalcon_Request, reset){

	zval *t0 = NULL;

	PHALCON_MM_GROW();
	PHALCON_INIT_VAR(t0);
	ZVAL_NULL(t0);
	zend_update_static_property(phalcon_request_ce, "_instance", sizeof("_instance")-1, t0 TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

