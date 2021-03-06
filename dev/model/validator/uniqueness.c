
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
 * Phalcon_Model_Validator_Uniqueness
 *
 * Validates that a field or a combination of a set of fields are not
 * present more than once in the existing records of the related table
 *
 *
 *
 */

/**
 * Executes the validator
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Model_Validator_Uniqueness, validate){

	zval *record = NULL, *field = NULL, *conditions = NULL, *compose_field = NULL;
	zval *value = NULL, *manager = NULL, *meta_data = NULL, *primary_fields = NULL;
	zval *primary_field = NULL, *options = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL, *r4 = NULL, *r5 = NULL, *r6 = NULL;
	zval *r7 = NULL, *r8 = NULL, *r9 = NULL, *r10 = NULL, *r11 = NULL, *r12 = NULL, *r13 = NULL;
	zval *r14 = NULL, *r15 = NULL, *r16 = NULL, *r17 = NULL, *r18 = NULL, *r19 = NULL, *r20 = NULL;
	zval *i0 = NULL;
	zval *a0 = NULL;
	zval *c0 = NULL, *c1 = NULL, *c2 = NULL;
	zval *t0 = NULL;
	HashTable *ah0, *ah1;
	HashPosition hp0, hp1;
	zval **hd;
	int eval_int;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(r0);
	PHALCON_CALL_METHOD(r0, this_ptr, "isrequired", PHALCON_NO_CHECK);
	if (zend_is_true(r0)) {
		PHALCON_ALLOC_ZVAL_MM(r1);
		PHALCON_CALL_METHOD(r1, this_ptr, "getrecord", PHALCON_NO_CHECK);
		PHALCON_ALLOC_ZVAL_MM(i0);
		if (phalcon_clone(i0, r1 TSRMLS_CC) == FAILURE){
			return;
		}
		PHALCON_CPY_WRT(record, i0);
		
		PHALCON_ALLOC_ZVAL_MM(r2);
		PHALCON_CALL_METHOD(r2, this_ptr, "getfieldname", PHALCON_NO_CHECK);
		PHALCON_CPY_WRT(field, r2);
		
		PHALCON_INIT_VAR(a0);
		array_init(a0);
		PHALCON_CPY_WRT(conditions, a0);
		if (Z_TYPE_P(field) == IS_ARRAY) { 
			if (phalcon_valid_foreach(field TSRMLS_CC)) {
				ah0 = Z_ARRVAL_P(field);
				zend_hash_internal_pointer_reset_ex(ah0, &hp0);
				fes_d73d_0:
				if(zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) != SUCCESS){
					goto fee_d73d_0;
				}
				PHALCON_INIT_VAR(compose_field);
				ZVAL_ZVAL(compose_field, *hd, 1, 0);
				PHALCON_INIT_VAR(r3);
				PHALCON_INIT_VAR(r4);
				PHALCON_CALL_METHOD_PARAMS_1(r4, record, "readattribute", compose_field, PHALCON_NO_CHECK);
				PHALCON_CALL_FUNC_PARAMS_1(r3, "addslashes", r4, 0x00F);
				PHALCON_CPY_WRT(value, r3);
				
				PHALCON_INIT_VAR(r5);
				PHALCON_CONCAT_VSVS(r5, compose_field, "='", value, "'");
				phalcon_array_append(&conditions, r5, PHALCON_SEPARATE_PLZ TSRMLS_CC);
				zend_hash_move_forward_ex(ah0, &hp0);
				goto fes_d73d_0;
				fee_d73d_0:
				if(0){}
			} else {
				return;
			}
		} else {
			PHALCON_ALLOC_ZVAL_MM(r6);
			PHALCON_ALLOC_ZVAL_MM(r7);
			PHALCON_CALL_METHOD(r7, this_ptr, "getvalue", PHALCON_NO_CHECK);
			PHALCON_CALL_FUNC_PARAMS_1(r6, "addslashes", r7, 0x00F);
			PHALCON_CPY_WRT(value, r6);
			
			PHALCON_ALLOC_ZVAL_MM(r8);
			PHALCON_CONCAT_VSVS(r8, field, "='", value, "'");
			phalcon_array_append(&conditions, r8, PHALCON_SEPARATE_PLZ TSRMLS_CC);
		}
		
		PHALCON_ALLOC_ZVAL_MM(r9);
		PHALCON_CALL_METHOD(r9, record, "getmanager", PHALCON_NO_CHECK);
		PHALCON_CPY_WRT(manager, r9);
		
		PHALCON_ALLOC_ZVAL_MM(r10);
		PHALCON_CALL_METHOD(r10, manager, "getmetadata", PHALCON_NO_CHECK);
		PHALCON_CPY_WRT(meta_data, r10);
		
		PHALCON_ALLOC_ZVAL_MM(r11);
		PHALCON_CALL_METHOD_PARAMS_1(r11, meta_data, "getprimarykeyattributes", record, PHALCON_NO_CHECK);
		PHALCON_CPY_WRT(primary_fields, r11);
		if (phalcon_valid_foreach(primary_fields TSRMLS_CC)) {
			ah1 = Z_ARRVAL_P(primary_fields);
			zend_hash_internal_pointer_reset_ex(ah1, &hp1);
			fes_d73d_1:
			if(zend_hash_get_current_data_ex(ah1, (void**) &hd, &hp1) != SUCCESS){
				goto fee_d73d_1;
			}
			
			PHALCON_INIT_VAR(primary_field);
			ZVAL_ZVAL(primary_field, *hd, 1, 0);
			PHALCON_INIT_VAR(r12);
			PHALCON_INIT_VAR(r13);
			PHALCON_INIT_VAR(r14);
			PHALCON_CALL_METHOD_PARAMS_1(r14, record, "readattribute", primary_field, PHALCON_NO_CHECK);
			PHALCON_CALL_FUNC_PARAMS_1(r13, "addslashes", r14, 0x00F);
			PHALCON_CONCAT_VSVS(r12, primary_field, "<>'", r13, "'");
			phalcon_array_append(&conditions, r12, PHALCON_SEPARATE_PLZ TSRMLS_CC);
			zend_hash_move_forward_ex(ah1, &hp1);
			goto fes_d73d_1;
			fee_d73d_1:
			if(0){}
		} else {
			return;
		}
		
		PHALCON_INIT_VAR(c0);
		ZVAL_STRING(c0, " AND ", 1);
		
		PHALCON_ALLOC_ZVAL_MM(r15);
		phalcon_fast_join(r15, c0, conditions TSRMLS_CC);
		PHALCON_CPY_WRT(conditions, r15);
		
		PHALCON_ALLOC_ZVAL_MM(r16);
		PHALCON_CALL_STATIC_ZVAL_PARAMS_1(r16, record, "count", conditions);
		
		PHALCON_INIT_VAR(t0);
		ZVAL_LONG(t0, 0);
		
		PHALCON_INIT_VAR(r17);
		is_smaller_function(r17, t0, r16 TSRMLS_CC);
		if (zend_is_true(r17)) {
			PHALCON_ALLOC_ZVAL_MM(r18);
			PHALCON_CALL_METHOD(r18, this_ptr, "getoptions", PHALCON_NO_CHECK);
			PHALCON_CPY_WRT(options, r18);
			eval_int = phalcon_array_isset_string(options, "message", strlen("message")+1);
			if (eval_int) {
				PHALCON_ALLOC_ZVAL_MM(r19);
				phalcon_array_fetch_string(&r19, options, "message", strlen("message"), PHALCON_NOISY TSRMLS_CC);
				PHALCON_INIT_VAR(c1);
				ZVAL_STRING(c1, "unique", 1);
				PHALCON_CALL_METHOD_PARAMS_3_NORETURN(this_ptr, "appendmessage", r19, field, c1, PHALCON_NO_CHECK);
			} else {
				PHALCON_ALLOC_ZVAL_MM(r20);
				PHALCON_CONCAT_SVS(r20, "Value of field '", field, "' is already present in another record");
				PHALCON_INIT_VAR(c2);
				ZVAL_STRING(c2, "unique", 1);
				PHALCON_CALL_METHOD_PARAMS_3_NORETURN(this_ptr, "appendmessage", r20, field, c2, PHALCON_NO_CHECK);
			}
			
			PHALCON_MM_RESTORE();
			RETURN_FALSE;
		}
	}
	PHALCON_MM_RESTORE();
	RETURN_TRUE;
}

