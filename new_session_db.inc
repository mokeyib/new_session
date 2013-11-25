<?php
/**
 * This file is where we deal with our custom database table
 * The database table is called 'session_dates' and contains:
 *   $schema['session_dates'] = array(
 *	  nid: the node id of the session (the primary key for the table)
 *    season: the season of the session which we include in event titles
 *            on the calendar
 *	  rec_start: the start date of the rec center session
 *	  rec_end: the end date of the rec center session
 *	  week<n>: the date for week n (where n is 1-12). Leave extra dates
 *	           blank. More than 12 weeks will not be handled gracefully
 *	  offer_start: the start date for offering classes
 *	  offer_end: the end date for offering classes
 *	  schedule_posted: the date when the schedule will be posted
 *	  member_reg_start: the start date for member registration
 *	  former_reg_start: the start date for former member registration
 *	  new_member_reg_start: the start date for new member registration
 *	  reg_end: the end date for registration
 *	  fees_posted: the date when fees are posted
 *	  fees_due: the date when fees are due
 */

/**
 * this is where hook_install() is actually implemented
 * We use this to create the database table
 *  @see _new_session_db_schema()
 */
function _ns_db_install () {
  drupal_install_schema('new_session');
}
/**
 * this is where hook_uninstall() is actually implemented
 * We use this to delete the database table
 *  @see _new_session_db_schema()
 */
function _ns_db_uninstall () {
  drupal_uninstall_schema('new_session');
}

/**
 * this is where hook_schema() is actually implemented
 * This is where we define the database table that will store
 * dates for each session. We call it session_dates
 */
function _ns_db_schema () {
  $schema['session_dates'] = array(
  	'fields' => array(
  	  'nid' => array(
  		'type' => 'int',
  	    'unsigned' => TRUE,
  	    'not null' => TRUE,
  	    'default' => 0,
  	  ),
  	  'season' => array(
  	    'type' => 'text',
  	    'length' => 31,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'rec_start' => array(
  	    'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'rec_end' => array(
  	    'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'week1' => array(
  	    'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'week1' => array(
  	    'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'week2' => array(
  	    'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'week3' => array(
  	    'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'week4' => array(
  	    'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'week5' => array(
  	    'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'week6' => array(
  	    'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'week7' => array(
  	    'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'week8' => array(
  	    'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'week9' => array(
  	    'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'week10' => array(
  	    'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'week11' => array(
  	    'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'week12' => array(
  	    'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'offer_start' => array(
  	  	'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'offer_end' => array(
  	  	'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'schedule_posted' => array(
  	  	'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'member_reg_start' => array(
  	  	'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'former_reg_start' => array(
  	  	'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'new_member_reg_start' => array(
  	  	'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'reg_end' => array(
  	  	'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'fees_posted' => array(
  	  	'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	  'fees_due' => array(
  	  	'type' => 'varchar',
  	    'length' => 127,
  	    'not null' => TRUE,
  	    'default' => '',
  	  ),
  	),
    'indexes' => array(
      'nid' => array('nid'),
    ),
    'primary key' => array('nid'),
  );
  return $schema;
}

/**
 * create a new entry in the session dates table
 */
function _ns_db_insert ($nid) {
  db_query('INSERT INTO {session_dates} (nid) VALUES ('. $nid .')');
}

/**
 * add a value to the table
 */
function _ns_db_put ($nid, $column, $value) {
  if (is_string($value)) {
    $str = 'UPDATE {session_dates} SET '. $column .'=\''. $value .
           '\' WHERE nid='. $nid;
  } else {
    $str = 'UPDATE {session_dates} SET '. $column .'='. $value .
           ' WHERE nid='. $nid;
  }
  db_query($str);
}

/**
 * get an entry from the database
 * @param int $nid the node id of the session we're dealing with
 * @param string $column the column to fetch from the database
 * @return the entry
 */
function _ns_db_get ($nid, $column) {
  return db_result(db_query('SELECT '. $column .' FROM {session_dates} WHERE nid = '. $nid));
}
