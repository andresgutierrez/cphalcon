
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
 * Phalcon_Model_Query
 *
 * Phalcon_Model_Query is designed to simplify building of search on models.
 * It provides a set of helpers to generate searchs in a dynamic way to support differents databases.
 *
 * 
 *
 */

PHP_METHOD(Phalcon_Model_Query, __construct){

	zval *a0 = NULL, *a1 = NULL, *a2 = NULL, *a3 = NULL;

	PHALCON_MM_GROW();

	PHALCON_INIT_VAR(a0);
	array_init(a0);
	zend_update_property(phalcon_model_query_ce, this_ptr, "_data", strlen("_data"), a0 TSRMLS_CC);
	
	PHALCON_INIT_VAR(a1);
	array_init(a1);
	zend_update_property(phalcon_model_query_ce, this_ptr, "_models", strlen("_models"), a1 TSRMLS_CC);
	
	PHALCON_INIT_VAR(a2);
	array_init(a2);
	zend_update_property(phalcon_model_query_ce, this_ptr, "_parameters", strlen("_parameters"), a2 TSRMLS_CC);
	
	PHALCON_INIT_VAR(a3);
	array_init(a3);
	zend_update_property(phalcon_model_query_ce, this_ptr, "_conditions", strlen("_conditions"), a3 TSRMLS_CC);

	PHALCON_MM_RESTORE();
}

/**
 * Set the Phalcon_Model_Manager instance to use in a query
 *
 * 
 *
 * @param Phalcon_Model_Manager $manager
 */
PHP_METHOD(Phalcon_Model_Query, setManager){

	zval *manager = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &manager) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_update_property_zval(this_ptr, "_manager", strlen("_manager"), manager TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Add models to use in query
 *
 * @param string $model
 */
PHP_METHOD(Phalcon_Model_Query, from){

	zval *model = NULL;
	zval *t0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &model) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, "_models", sizeof("_models")-1, PHALCON_NOISY TSRMLS_CC);
	phalcon_array_append(&t0, model, PHALCON_NO_SEPARATE_THX TSRMLS_CC);
	phalcon_update_property_zval(this_ptr, "_models", strlen("_models"), t0 TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Add conditions to use in query
 *
 * @param string $condition
 */
PHP_METHOD(Phalcon_Model_Query, where){

	zval *condition = NULL;
	zval *t0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &condition) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, "_conditions", sizeof("_conditions")-1, PHALCON_NOISY TSRMLS_CC);
	phalcon_array_append(&t0, condition, PHALCON_NO_SEPARATE_THX TSRMLS_CC);
	phalcon_update_property_zval(this_ptr, "_conditions", strlen("_conditions"), t0 TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Set parameter in query to different database adapters.
 *
 * @param string $parameter
 */
PHP_METHOD(Phalcon_Model_Query, setParameters){

	zval *parameter = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &parameter) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_update_property_zval(this_ptr, "_parameters", strlen("_parameters"), parameter TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Set the data to use to make the conditions in query
 *
 * @param array $data
 */
PHP_METHOD(Phalcon_Model_Query, setInputData){

	zval *data = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &data) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_update_property_zval(this_ptr, "_data", strlen("_data"), data TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Set the limit of rows to show
 *
 * @param int $limit
 */
PHP_METHOD(Phalcon_Model_Query, setLimit){

	zval *limit = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &limit) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	phalcon_update_property_zval(this_ptr, "_limit", strlen("_limit"), limit TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

PHP_METHOD(Phalcon_Model_Query, getResultset){


	
}

/**
 * Get the conditions of query
 *
 * @return string $query
 */
PHP_METHOD(Phalcon_Model_Query, getConditions){

	zval *controller_front = NULL, *model_manager = NULL, *model_name = NULL;
	zval *entity = NULL, *meta_data = NULL, *attributes = NULL, *numeric_types = NULL;
	zval *i = NULL, *parameters = NULL, *conditions = NULL, *value = NULL, *param = NULL;
	zval *condition = NULL, *index = NULL;
	zval *t0 = NULL, *t1 = NULL, *t2 = NULL, *t3 = NULL, *t4 = NULL, *t5 = NULL, *t6 = NULL;
	zval *t7 = NULL;
	zval *r0 = NULL, *r1 = NULL, *r2 = NULL, *r3 = NULL, *r4 = NULL, *r5 = NULL, *r6 = NULL;
	zval *r7 = NULL, *r8 = NULL, *r9 = NULL, *r10 = NULL, *r11 = NULL, *r12 = NULL, *r13 = NULL;
	zval *r14 = NULL, *r15 = NULL, *r16 = NULL, *r17 = NULL, *r18 = NULL;
	zval *i0 = NULL;
	zval *a0 = NULL, *a1 = NULL;
	zval *c0 = NULL;
	HashTable *ah0, *ah1, *ah2;
	HashPosition hp0, hp1, hp2;
	zval **hd;
	char *hash_index;
	uint hash_index_len;
	ulong hash_num;
	int hash_type;
	int eval_int;

	PHALCON_MM_GROW();
	PHALCON_ALLOC_ZVAL_MM(t0);
	phalcon_read_property(&t0, this_ptr, "_manager", sizeof("_manager")-1, PHALCON_NOISY TSRMLS_CC);
	if (!zend_is_true(t0)) {
		PHALCON_ALLOC_ZVAL_MM(r0);
		PHALCON_CALL_STATIC(r0, "phalcon_controller_front", "getinstance");
		PHALCON_CPY_WRT(controller_front, r0);
		
		PHALCON_ALLOC_ZVAL_MM(r1);
		PHALCON_CALL_METHOD(r1, controller_front, "getmodelcomponent", PHALCON_NO_CHECK);
		PHALCON_CPY_WRT(model_manager, r1);
		PHALCON_CALL_METHOD_PARAMS_1_NORETURN(this_ptr, "setmanager", model_manager, PHALCON_NO_CHECK);
	} else {
		PHALCON_ALLOC_ZVAL_MM(t1);
		phalcon_read_property(&t1, this_ptr, "_manager", sizeof("_manager")-1, PHALCON_NOISY TSRMLS_CC);
		PHALCON_CPY_WRT(model_manager, t1);
	}
	
	PHALCON_ALLOC_ZVAL_MM(t2);
	phalcon_read_property(&t2, this_ptr, "_models", sizeof("_models")-1, PHALCON_NOISY TSRMLS_CC);
	if (phalcon_valid_foreach(t2 TSRMLS_CC)) {
		ah0 = Z_ARRVAL_P(t2);
		zend_hash_internal_pointer_reset_ex(ah0, &hp0);
		fes_a355_0:
		if(zend_hash_get_current_data_ex(ah0, (void**) &hd, &hp0) != SUCCESS){
			goto fee_a355_0;
		}
		
		PHALCON_INIT_VAR(model_name);
		ZVAL_ZVAL(model_name, *hd, 1, 0);
		PHALCON_INIT_VAR(r2);
		PHALCON_CALL_METHOD_PARAMS_1(r2, model_manager, "getmodel", model_name, PHALCON_NO_CHECK);
		PHALCON_CPY_WRT(entity, r2);
		if (!zend_is_true(entity)) {
			PHALCON_INIT_VAR(i0);
			object_init_ex(i0, phalcon_model_exception_ce);
			PHALCON_INIT_VAR(r3);
			PHALCON_CONCAT_SVS(r3, "The model ", model_name, " does not exist");
			PHALCON_CALL_METHOD_PARAMS_1_NORETURN(i0, "__construct", r3, PHALCON_CHECK);
			phalcon_throw_exception(i0 TSRMLS_CC);
			return;
		}
		
		PHALCON_INIT_VAR(r4);
		PHALCON_CALL_METHOD(r4, model_manager, "getmetadata", PHALCON_NO_CHECK);
		PHALCON_CPY_WRT(meta_data, r4);
		
		PHALCON_INIT_VAR(r5);
		PHALCON_CALL_METHOD_PARAMS_1(r5, meta_data, "getattributes", entity, PHALCON_NO_CHECK);
		PHALCON_CPY_WRT(attributes, r5);
		
		PHALCON_INIT_VAR(r6);
		PHALCON_CALL_METHOD_PARAMS_1(r6, meta_data, "getdatatypesnumeric", entity, PHALCON_NO_CHECK);
		PHALCON_CPY_WRT(numeric_types, r6);
		
		PHALCON_INIT_VAR(t3);
		phalcon_read_property(&t3, this_ptr, "_data", sizeof("_data")-1, PHALCON_NOISY TSRMLS_CC);
		
		PHALCON_INIT_VAR(r7);
		phalcon_fast_count(r7, t3 TSRMLS_CC);
		if (zend_is_true(r7)) {
			PHALCON_INIT_VAR(i);
			ZVAL_LONG(i, 0);
			
			PHALCON_INIT_VAR(a0);
			array_init(a0);
			PHALCON_CPY_WRT(parameters, a0);
			
			PHALCON_INIT_VAR(a1);
			array_init(a1);
			PHALCON_CPY_WRT(conditions, a1);
			
			PHALCON_INIT_VAR(t4);
			phalcon_read_property(&t4, this_ptr, "_data", sizeof("_data")-1, PHALCON_NOISY TSRMLS_CC);
			if (phalcon_valid_foreach(t4 TSRMLS_CC)) {
				ah1 = Z_ARRVAL_P(t4);
				zend_hash_internal_pointer_reset_ex(ah1, &hp1);
				fes_a355_1:
				if(zend_hash_get_current_data_ex(ah1, (void**) &hd, &hp1) != SUCCESS){
					goto fee_a355_1;
				} else {
					PHALCON_INIT_VAR(param);
					PHALCON_GET_FOREACH_KEY(param, ah1, hp1);
				}
				PHALCON_INIT_VAR(value);
				ZVAL_ZVAL(value, *hd, 1, 0);
				PHALCON_INIT_VAR(r8);
				PHALCON_CALL_FUNC_PARAMS_2(r8, "in_array", param, attributes, 0x03E);
				if (zend_is_true(r8)) {
					PHALCON_INIT_VAR(t5);
					ZVAL_STRING(t5, "", 1);
					PHALCON_INIT_VAR(r9);
					is_not_identical_function(r9, t5, value TSRMLS_CC);
					PHALCON_INIT_VAR(r11);
					PHALCON_CALL_FUNC_PARAMS_1(r11, "is_null", value, 0x041);
					PHALCON_INIT_VAR(r10);
					boolean_not_function(r10, r11 TSRMLS_CC);
					PHALCON_INIT_VAR(r12);
					phalcon_and_function(r12, r9, r10);
					if (zend_is_true(r12)) {
						if (!PHALCON_COMPARE_STRING(value, "@")) {
							eval_int = phalcon_array_isset(numeric_types, param);
							if (eval_int) {
								PHALCON_INIT_VAR(r13);
								PHALCON_CONCAT_VSV(r13, param, " = ?", i);
								PHALCON_CPY_WRT(condition, r13);
								phalcon_array_update(&parameters, i, &value, PHALCON_SEPARATE_PLZ, PHALCON_COPY, PHALCON_NO_CTOR TSRMLS_CC);
							} else {
								PHALCON_INIT_VAR(r14);
								PHALCON_CONCAT_VSV(r14, param, " LIKE ?", i);
								PHALCON_CPY_WRT(condition, r14);
								
								PHALCON_INIT_VAR(r15);
								PHALCON_CONCAT_SVS(r15, "%", value, "%");
								phalcon_array_update(&parameters, i, &r15, PHALCON_SEPARATE_PLZ, PHALCON_COPY, PHALCON_NO_CTOR TSRMLS_CC);
							}
							phalcon_array_append(&conditions, condition, PHALCON_SEPARATE_PLZ TSRMLS_CC);
						}
					}
				}
				PHALCON_SEPARATE(i);
				increment_function(i);
				zend_hash_move_forward_ex(ah1, &hp1);
				goto fes_a355_1;
				fee_a355_1:
				if(0){}
			} else {
				return;
			}
		} else {
			PHALCON_INIT_VAR(t6);
			phalcon_read_property(&t6, this_ptr, "_parameters", sizeof("_parameters")-1, PHALCON_NOISY TSRMLS_CC);
			PHALCON_CPY_WRT(parameters, t6);
			
			PHALCON_INIT_VAR(t7);
			phalcon_read_property(&t7, this_ptr, "_conditions", sizeof("_conditions")-1, PHALCON_NOISY TSRMLS_CC);
			PHALCON_CPY_WRT(conditions, t7);
		}
		
		PHALCON_INIT_VAR(c0);
		ZVAL_STRING(c0, " AND ", 1);
		
		PHALCON_INIT_VAR(r16);
		phalcon_fast_join(r16, c0, conditions TSRMLS_CC);
		PHALCON_CPY_WRT(conditions, r16);
		if (phalcon_valid_foreach(parameters TSRMLS_CC)) {
			ah2 = Z_ARRVAL_P(parameters);
			zend_hash_internal_pointer_reset_ex(ah2, &hp2);
			fes_a355_2:
			if(zend_hash_get_current_data_ex(ah2, (void**) &hd, &hp2) != SUCCESS){
				goto fee_a355_2;
			} else {
				PHALCON_INIT_VAR(index);
				PHALCON_GET_FOREACH_KEY(index, ah2, hp2);
			}
			PHALCON_INIT_VAR(value);
			ZVAL_ZVAL(value, *hd, 1, 0);
			PHALCON_INIT_VAR(r17);
			PHALCON_INIT_VAR(r18);
			PHALCON_CONCAT_SV(r18, "?", index);
			PHALCON_CALL_FUNC_PARAMS_3(r17, "str_replace", r18, value, conditions, 0x003);
			PHALCON_CPY_WRT(conditions, r17);
			zend_hash_move_forward_ex(ah2, &hp2);
			goto fes_a355_2;
			fee_a355_2:
			if(0){}
		} else {
			return;
		}
		if (PHALCON_COMPARE_STRING(conditions, "")) {
			PHALCON_INIT_VAR(conditions);
			ZVAL_STRING(conditions, "1=1", 1);
		}
		
		
		PHALCON_RETURN_CHECK_CTOR(conditions);
		zend_hash_move_forward_ex(ah0, &hp0);
		goto fes_a355_0;
		fee_a355_0:
		if(0){}
	} else {
		return;
	}
	
	PHALCON_MM_RESTORE();
}

/**
 * Get instance of model query
 *
 * @param string $modelName
 * @param array $data
 * @return Phalcon_Model_Query
 */
PHP_METHOD(Phalcon_Model_Query, fromInput){

	zval *model_name = NULL, *data = NULL, *query = NULL;
	zval *i0 = NULL;

	PHALCON_MM_GROW();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &model_name, &data) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	PHALCON_ALLOC_ZVAL_MM(i0);
	object_init_ex(i0, phalcon_model_query_ce);
	PHALCON_CALL_METHOD_NORETURN(i0, "__construct", PHALCON_CHECK);
	PHALCON_CPY_WRT(query, i0);
	PHALCON_CALL_METHOD_PARAMS_1_NORETURN(query, "from", model_name, PHALCON_NO_CHECK);
	PHALCON_CALL_METHOD_PARAMS_1_NORETURN(query, "setinputdata", data, PHALCON_NO_CHECK);
	
	PHALCON_RETURN_CTOR(query);
}

