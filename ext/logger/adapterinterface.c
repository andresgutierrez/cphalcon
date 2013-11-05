
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2013 Phalcon Team (http://www.phalconphp.com)       |
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

/**
 * Phalcon\Logger\AdapterInterface initializer
 */
PHALCON_INIT_CLASS(Phalcon_Logger_AdapterInterface){

	PHALCON_REGISTER_INTERFACE(Phalcon\\Logger, AdapterInterface, logger_adapterinterface, phalcon_logger_adapterinterface_method_entry);

	return SUCCESS;
}

/**
 * Sets the message formatter
 *
 * @param Phalcon\Logger\FormatterInterface $formatter
 * @return Phalcon\Logger\Adapter
 */
PHALCON_DOC_METHOD(Phalcon_Logger_AdapterInterface, setFormatter);

/**
 * Returns the internal formatter
 *
 * @return Phalcon\Logger\FormatterInterface
 */
PHALCON_DOC_METHOD(Phalcon_Logger_AdapterInterface, getFormatter);

/**
 * Filters the logs sent to the handlers to be greater or equals than a specific level
 *
 * @param int $level
 * @return Phalcon\Logger\Adapter
 */
PHALCON_DOC_METHOD(Phalcon_Logger_AdapterInterface, setLogLevel);

/**
 * Returns the current log level
 *
 * @return int
 */
PHALCON_DOC_METHOD(Phalcon_Logger_AdapterInterface, getLogLevel);

/**
 * Sends/Writes messages to the file log
 *
 * @param string $message
 * @param int $type
 * @return Phalcon\Logger\Adapter
 */
PHALCON_DOC_METHOD(Phalcon_Logger_AdapterInterface, log);

/**
 * Starts a transaction
 *
 * @return Phalcon\Logger\Adapter
 */
PHALCON_DOC_METHOD(Phalcon_Logger_AdapterInterface, begin);

/**
 * Commits the internal transaction
 *
 * @return Phalcon\Logger\Adapter
 */
PHALCON_DOC_METHOD(Phalcon_Logger_AdapterInterface, commit);

/**
 * Rollbacks the internal transaction
 *
 * @return Phalcon\Logger\Adapter
 */
PHALCON_DOC_METHOD(Phalcon_Logger_AdapterInterface, rollback);

/**
 * Closes the logger
 *
 * @return boolean
 */
PHALCON_DOC_METHOD(Phalcon_Logger_AdapterInterface, close);

/**
 * Sends/Writes a debug message to the log
 *
 * @param string $message
 * @param ing $type
 * @return Phalcon\Logger\Adapter
 */
PHALCON_DOC_METHOD(Phalcon_Logger_AdapterInterface, debug);

/**
 * Sends/Writes an error message to the log
 *
 * @param string $message
 * @param ing $type
 * @return Phalcon\Logger\Adapter
 */
PHALCON_DOC_METHOD(Phalcon_Logger_AdapterInterface, error);

/**
 * Sends/Writes an info message to the log
 *
 * @param string $message
 * @param ing $type
 * @return Phalcon\Logger\Adapter
 */
PHALCON_DOC_METHOD(Phalcon_Logger_AdapterInterface, info);

/**
 * Sends/Writes a notice message to the log
 *
 * @param string $message
 * @param ing $type
 * @return Phalcon\Logger\Adapter
 */
PHALCON_DOC_METHOD(Phalcon_Logger_AdapterInterface, notice);

/**
 * Sends/Writes a warning message to the log
 *
 * @param string $message
 * @param ing $type
 * @return Phalcon\Logger\Adapter
 */
PHALCON_DOC_METHOD(Phalcon_Logger_AdapterInterface, warning);

/**
 * Sends/Writes an alert message to the log
 *
 * @param string $message
 * @param ing $type
 * @return Phalcon\Logger\Adapter
 */
PHALCON_DOC_METHOD(Phalcon_Logger_AdapterInterface, alert);

