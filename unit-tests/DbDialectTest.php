<?php

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

class DbDialectTest extends PHPUnit_Framework_TestCase {

	private function getColumns(){
		return array(
			'column1' => new Phalcon_Db_Column("column1", array(
				'type' => Phalcon_Db_Column::TYPE_VARCHAR,
				'size' => 10
			)),
			'column2' => new Phalcon_Db_Column("column2", array(
				'type' => Phalcon_Db_Column::TYPE_INTEGER,
				'size' => 18,
				'unsigned' => true,
				'notNull' => false
			)),
			'column3' => new Phalcon_Db_Column("column3", array(
				'type' => Phalcon_Db_Column::TYPE_DECIMAL,
				'size' => 10,
				'scale' => 2,
				'unsigned' => false,
				'notNull' => true
			)),
			'column4' => new Phalcon_Db_Column("column4", array(
				'type' => Phalcon_Db_Column::TYPE_CHAR,
				'size' => 100,
				'notNull' => true
			)),
			'column5' => new Phalcon_Db_Column("column5", array(
				'type' => Phalcon_Db_Column::TYPE_DATE,
				'notNull' => true
			)),
			'column6' => new Phalcon_Db_Column("column6", array(
				'type' => Phalcon_Db_Column::TYPE_DATETIME,
				'notNull' => true
			)),
			'column7' => new Phalcon_Db_Column("column7", array(
				'type' => Phalcon_Db_Column::TYPE_TEXT,
				'notNull' => true
			))
		);
	}

	private function getIndexes(){
		return array(
			'index1' => new Phalcon_Db_Index("index1", array('column1')),
			'index2' => new Phalcon_Db_Index("index2", array('column1', 'column2')),
			'PRIMARY' => new Phalcon_Db_Index("PRIMARY", array('column3')),
		);
	}

	private function getReferences(){
		return array(
			'fk1' => new Phalcon_Db_Reference("fk1", array(
				'referencedTable' => 'ref_table',
				'columns' => array('column1'),
				'referencedColumns' => array('column2')
			)),
			'fk2' => new Phalcon_Db_Reference("fk2", array(
				'referencedTable' => 'ref_table',
				'columns' => array('column3', 'column4'),
				'referencedColumns' => array('column5', 'column6')
			)),
		);
	}

	public function testDbColumn(){

		$columns = $this->getColumns();

		//Varchar column
		$column1 = $columns['column1'];

		$this->assertEquals($column1->getName(), 'column1');
		$this->assertEquals($column1->getType(), Phalcon_Db_Column::TYPE_VARCHAR);
		$this->assertEquals($column1->getSize(), 10);
		$this->assertEquals($column1->getScale(), 0);
		$this->assertFalse($column1->isUnsigned());
		$this->assertFalse($column1->isNotNull());

		//Integer column
		$column2 = $columns['column2'];

		$this->assertEquals($column2->getName(), 'column2');
		$this->assertEquals($column2->getType(), Phalcon_Db_Column::TYPE_INTEGER);
		$this->assertEquals($column2->getSize(), 18);
		$this->assertEquals($column2->getScale(), 0);
		$this->assertTrue($column2->isUnsigned());
		$this->assertFalse($column2->isNotNull());

		//Decimal column
		$column3 = $columns['column3'];

		$this->assertEquals($column3->getName(), 'column3');
		$this->assertEquals($column3->getType(), Phalcon_Db_Column::TYPE_DECIMAL);
		$this->assertEquals($column3->getSize(), 10);
		$this->assertEquals($column3->getScale(), 2);
		$this->assertFalse($column3->isUnsigned());
		$this->assertTrue($column3->isNotNull());

		//Char column
		$column4 = $columns['column4'];

		$this->assertEquals($column4->getName(), 'column4');
		$this->assertEquals($column4->getType(), Phalcon_Db_Column::TYPE_CHAR);
		$this->assertEquals($column4->getSize(), 100);
		$this->assertEquals($column4->getScale(), 0);
		$this->assertFalse($column4->isUnsigned());
		$this->assertTrue($column4->isNotNull());

		//Date column
		$column5 = $columns['column5'];

		$this->assertEquals($column5->getName(), 'column5');
		$this->assertEquals($column5->getType(), Phalcon_Db_Column::TYPE_DATE);
		$this->assertEquals($column5->getSize(), 0);
		$this->assertEquals($column5->getScale(), 0);
		$this->assertFalse($column5->isUnsigned());
		$this->assertTrue($column5->isNotNull());

		//Datetime column
		$column6 = $columns['column6'];

		$this->assertEquals($column6->getName(), 'column6');
		$this->assertEquals($column6->getType(), Phalcon_Db_Column::TYPE_DATETIME);
		$this->assertEquals($column6->getSize(), 0);
		$this->assertEquals($column6->getScale(), 0);
		$this->assertFalse($column6->isUnsigned());
		$this->assertTrue($column6->isNotNull());

		//Text column
		$column7 = $columns['column7'];

		$this->assertEquals($column7->getName(), 'column7');
		$this->assertEquals($column7->getType(), Phalcon_Db_Column::TYPE_TEXT);
		$this->assertEquals($column7->getSize(), 0);
		$this->assertEquals($column7->getScale(), 0);
		$this->assertFalse($column7->isUnsigned());
		$this->assertTrue($column7->isNotNull());

	}

	public function testIndexes(){

		$indexes = $this->getIndexes();

		$index1 = $indexes['index1'];
		$this->assertEquals($index1->getName(), 'index1');
		$this->assertEquals($index1->getColumns(), array('column1'));

		$index2 = $indexes['index2'];
		$this->assertEquals($index2->getName(), 'index2');
		$this->assertEquals($index2->getColumns(), array('column1', 'column2'));

		$index3 = $indexes['PRIMARY'];
		$this->assertEquals($index3->getName(), 'PRIMARY');
		$this->assertEquals($index3->getColumns(), array('column3'));

	}

	public function testReferences(){

		$references = $this->getReferences();

		$reference1 = $references['fk1'];
		$this->assertEquals($reference1->getName(), 'fk1');
		$this->assertEquals($reference1->getColumns(), array('column1'));
		$this->assertEquals($reference1->getReferencedTable(), 'ref_table');
		$this->assertEquals($reference1->getReferencedColumns(), array('column2'));

		$reference2 = $references['fk2'];
		$this->assertEquals($reference2->getName(), 'fk2');
		$this->assertEquals($reference2->getColumns(), array('column3', 'column4'));
		$this->assertEquals($reference2->getReferencedTable(), 'ref_table');
		$this->assertEquals($reference2->getReferencedColumns(), array('column5', 'column6'));

	}

	public function testMysqlDialect(){

		$columns = Phalcon_Db_Dialect_Mysql::getColumnList(array('column1', 'column2', 'column3'));
		$this->assertEquals($columns, "`column1`, `column2`, `column3`");

		$columns = $this->getColumns();

		//Column definitions
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::getColumnDefinition($columns['column1']), 'VARCHAR(10)');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::getColumnDefinition($columns['column2']), 'INT(18) UNSIGNED');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::getColumnDefinition($columns['column3']), 'DECIMAL(10,2)');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::getColumnDefinition($columns['column4']), 'CHAR(100)');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::getColumnDefinition($columns['column5']), 'DATE');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::getColumnDefinition($columns['column6']), 'DATETIME');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::getColumnDefinition($columns['column7']), 'TEXT');

		//Add Columns
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addColumn('table', null, $columns['column1']), 'ALTER TABLE `table` ADD `column1` VARCHAR(10)');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addColumn('table', 'schema', $columns['column1']), 'ALTER TABLE `schema`.`table` ADD `column1` VARCHAR(10)');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addColumn('table', null, $columns['column2']), 'ALTER TABLE `table` ADD `column2` INT(18) UNSIGNED');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addColumn('table', 'schema', $columns['column2']), 'ALTER TABLE `schema`.`table` ADD `column2` INT(18) UNSIGNED');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addColumn('table', null, $columns['column3']), 'ALTER TABLE `table` ADD `column3` DECIMAL(10,2) NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addColumn('table', 'schema', $columns['column3']), 'ALTER TABLE `schema`.`table` ADD `column3` DECIMAL(10,2) NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addColumn('table', null, $columns['column4']), 'ALTER TABLE `table` ADD `column4` CHAR(100) NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addColumn('table', 'schema', $columns['column4']), 'ALTER TABLE `schema`.`table` ADD `column4` CHAR(100) NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addColumn('table', null, $columns['column5']), 'ALTER TABLE `table` ADD `column5` DATE NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addColumn('table', 'schema', $columns['column5']), 'ALTER TABLE `schema`.`table` ADD `column5` DATE NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addColumn('table', null, $columns['column6']), 'ALTER TABLE `table` ADD `column6` DATETIME NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addColumn('table', 'schema', $columns['column6']), 'ALTER TABLE `schema`.`table` ADD `column6` DATETIME NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addColumn('table', null, $columns['column7']), 'ALTER TABLE `table` ADD `column7` TEXT NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addColumn('table', 'schema', $columns['column7']), 'ALTER TABLE `schema`.`table` ADD `column7` TEXT NOT NULL');

		//Modify Columns
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::modifyColumn('table', null, $columns['column1']), 'ALTER TABLE `table` MODIFY `column1` VARCHAR(10)');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::modifyColumn('table', 'schema', $columns['column1']), 'ALTER TABLE `schema`.`table` MODIFY `column1` VARCHAR(10)');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::modifyColumn('table', null, $columns['column2']), 'ALTER TABLE `table` MODIFY `column2` INT(18) UNSIGNED');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::modifyColumn('table', 'schema', $columns['column2']), 'ALTER TABLE `schema`.`table` MODIFY `column2` INT(18) UNSIGNED');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::modifyColumn('table', null, $columns['column3']), 'ALTER TABLE `table` MODIFY `column3` DECIMAL(10,2) NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::modifyColumn('table', 'schema', $columns['column3']), 'ALTER TABLE `schema`.`table` MODIFY `column3` DECIMAL(10,2) NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::modifyColumn('table', null, $columns['column4']), 'ALTER TABLE `table` MODIFY `column4` CHAR(100) NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::modifyColumn('table', 'schema', $columns['column4']), 'ALTER TABLE `schema`.`table` MODIFY `column4` CHAR(100) NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::modifyColumn('table', null, $columns['column5']), 'ALTER TABLE `table` MODIFY `column5` DATE NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::modifyColumn('table', 'schema', $columns['column5']), 'ALTER TABLE `schema`.`table` MODIFY `column5` DATE NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::modifyColumn('table', null, $columns['column6']), 'ALTER TABLE `table` MODIFY `column6` DATETIME NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::modifyColumn('table', 'schema', $columns['column6']), 'ALTER TABLE `schema`.`table` MODIFY `column6` DATETIME NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::modifyColumn('table', null, $columns['column7']), 'ALTER TABLE `table` MODIFY `column7` TEXT NOT NULL');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::modifyColumn('table', 'schema', $columns['column7']), 'ALTER TABLE `schema`.`table` MODIFY `column7` TEXT NOT NULL');

		//Drop Columns
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::dropColumn('table', null, 'column1'), 'ALTER TABLE `table` DROP COLUMN `column1`');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::dropColumn('table', 'schema', 'column1'), 'ALTER TABLE `schema`.`table` DROP COLUMN `column1`');

		$indexes = $this->getIndexes();

		//Add Index
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addIndex('table', null, $indexes['index1']), 'ALTER TABLE `table` ADD INDEX `index1` (`column1`)');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addIndex('table', 'schema', $indexes['index1']), 'ALTER TABLE `schema`.`table` ADD INDEX `index1` (`column1`)');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addIndex('table', null, $indexes['index2']), 'ALTER TABLE `table` ADD INDEX `index2` (`column1`, `column2`)');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addIndex('table', 'schema', $indexes['index2']), 'ALTER TABLE `schema`.`table` ADD INDEX `index2` (`column1`, `column2`)');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addIndex('table', null, $indexes['PRIMARY']), 'ALTER TABLE `table` ADD INDEX `PRIMARY` (`column3`)');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addIndex('table', 'schema', $indexes['PRIMARY']), 'ALTER TABLE `schema`.`table` ADD INDEX `PRIMARY` (`column3`)');

		//Drop Index
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::dropIndex('table', null, 'index1'), 'ALTER TABLE `table` DROP INDEX `index1`');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::dropIndex('table', 'schema', 'index1'), 'ALTER TABLE `schema`.`table` DROP INDEX `index1`');

		//Add Primary Key
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addPrimaryKey('table', null, $indexes['PRIMARY']), 'ALTER TABLE `table` ADD PRIMARY KEY (`column3`)');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addPrimaryKey('table', 'schema', $indexes['PRIMARY']), 'ALTER TABLE `schema`.`table` ADD PRIMARY KEY (`column3`)');

		//Drop Primary Key
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::dropPrimaryKey('table', null), 'ALTER TABLE `table` DROP PRIMARY KEY');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::dropPrimaryKey('table', 'schema'), 'ALTER TABLE `schema`.`table` DROP PRIMARY KEY');

		$references = $this->getReferences();

		//Add Foreign Key
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addForeignKey('table', null, $references['fk1']), 'ALTER TABLE `table` ADD FOREIGN KEY `fk1`(`column1`) REFERENCES `ref_table`(`column2`)');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addForeignKey('table', 'schema', $references['fk1']), 'ALTER TABLE `schema`.`table` ADD FOREIGN KEY `fk1`(`column1`) REFERENCES `ref_table`(`column2`)');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addForeignKey('table', null, $references['fk2']), 'ALTER TABLE `table` ADD FOREIGN KEY `fk2`(`column3`, `column4`) REFERENCES `ref_table`(`column5`, `column6`)');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::addForeignKey('table', 'schema', $references['fk2']), 'ALTER TABLE `schema`.`table` ADD FOREIGN KEY `fk2`(`column3`, `column4`) REFERENCES `ref_table`(`column5`, `column6`)');

		$this->assertEquals(Phalcon_Db_Dialect_Mysql::dropForeignKey('table', null, 'fk1'), 'ALTER TABLE `table` DROP FOREIGN KEY `fk1`');
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::dropForeignKey('table', 'schema', 'fk1'), 'ALTER TABLE `schema`.`table` DROP FOREIGN KEY `fk1`');

		//Create tables
		$definition = array(
			'columns' => array(
				$columns['column1'],
				$columns['column2'],
			)
		);
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::createTable('table', null, $definition), 'CREATE TABLE `table` (
	`column1` VARCHAR(10),
	`column2` INT(18) UNSIGNED
)');

		$definition = array(
			'columns' => array(
				$columns['column2'],
				$columns['column3'],
				$columns['column1'],
			),
			'indexes' => array(
				$indexes['PRIMARY']
			)
		);
		$this->assertEquals(Phalcon_Db_Dialect_Mysql::createTable('table', null, $definition), 'CREATE TABLE `table` (
	`column2` INT(18) UNSIGNED,
	`column3` DECIMAL(10,2) NOT NULL,
	`column1` VARCHAR(10),
	PRIMARY KEY (`column3`)
)');

	}

}
