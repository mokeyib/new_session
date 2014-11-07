<?php

/**
 * a form to collect the rec center dates
 * testing git
 */
function _ns_rec_dates_form (&$form_state, $nid) {
  // store the nid for the validation step
  $form['nid'] = array(
  	'#type' => 'value',
    '#value' => $nid,
  );

  // now the form elements
  $form['dates'] = array(
  	'#type' => 'fieldset',
    '#title' => t('Recreation Center Dates'),
  );
  $form['dates']['rec_start'] = array(
    '#type' => 'date',
    '#title' => t('Start Date'),
    '#default_value' => _ns_date_array(),
    '#required' => TRUE,
  );
  $form['dates']['rec_end'] = array(
    '#type' => 'date',
    '#title' => t('Start Date'),
    '#default_value' => _ns_date_array(),
    '#required' => TRUE,
  );

  // and a submit button
  $form['submit'] = array(
  	'#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

/**
 * the user has submitted dates. We need to check that they're valid
 * they're valid if start is after today, end is after start
 */
function _ns_rec_dates_form_validate ($form, &$form_state) {
  $rec_start = $form_state['values']['rec_start'];
  $rec_start = _ns_date_convert($rec_start);
  if ($rec_start < strtotime('now')) {
    form_set_error('', t('Start date: '. _ns_date_print($rec_start) .' is before today'));
  } else {
    $rec_end = $form_state['values']['rec_end'];
    $rec_end = _ns_date_convert($rec_end);
    if ($rec_end < $rec_start) {
      form_set_error('', t('End date: '. _ns_date_print($rec_end) .' is before start date: '.
                    _ns_date_print($rec_start)));
    }
  }
  $form_state['values']['start_secs'] = $rec_start;
  $form_state['values']['end_secs'] = $rec_end;
}

/**
 * the user has clicked submit and the data was accepted
 */
function _ns_rec_dates_form_submit ($form, &$form_state) {
  module_load_include('inc', 'new_session', 'new_session_db');
  $nid = $form_state['values']['nid'];
  // calculate all of the Tuesdays between the start and end dates
  $class_dates = _ns_find_tuesdays($form_state['values']['start_secs'],
                                   $form_state['values']['end_secs']);
  // store everything in the database
  _ns_db_put($nid, 'rec_start', $form_state['values']['start_secs']);
  _ns_db_put($nid, 'rec_end', $form_state['values']['end_secs']);
  for ($i = 1; $i <= count($class_dates); $i++) {
    _ns_db_put($nid, 'week'.$i, $class_dates[$i]);
  }

   // we're done, so redirect to a page we've set up for the next step.
  $form_state['redirect'] = sprintf('admin/new_session_confirm_dates/'. $nid);

}

/**
 * find all the tuesdays between two given dates
 * @param long $start the start of the rec center session, in seconds (strtotime format)
 * @param long $end the end of the rec center session, in seconds (strtotime format)
 * @return array of longs, indexed 1..n, all the Tuesdays
 */
function _ns_find_tuesdays($start, $end) {
  $SECONDS_PER_DAY = 60*60*24;
  // figure out what day of the week $start is (Tuesday is 2)
  $day = date('w', $start);
  if ($day > 2) {
    $days_to_add = 9 - $day;
  } else {
    $days_to_add = 2 - $day;
  }
  $week = 1;
  // find the first Tuesday
  $next = $start + $days_to_add*$SECONDS_PER_DAY;
  while ($next < $end) {
    $classes[$week] = $next;
    // the next Tuesday is 7 days later
    $next = $classes[$week] + 7*$SECONDS_PER_DAY;
    $week++;
  }
  return $classes;
}

/**
 * a form to confirm all of the dates for the session
 * @param int $nid the node id of the session
 */
function _ns_confirm_dates_form (&$form_state, $nid) {
  // store the nid for later
  $form['nid'] = array(
  	'#type' => 'value',
    '#value' => $nid,
  );

  module_load_include('inc', 'new_session', 'new_session_db');
  // create a section with a title for all of the preparation dates
  // things like offering classes, signing up, paying fees, etc.
  // first calculate all the appropriate dates and store in the database
  _ns_prep_dates($nid);
  $form['prep'] = array(
  	'#type' => 'fieldset',
    '#title' => t('Session Preparation Dates'),
  );
  $date = _ns_db_get($nid, 'offer_start');
  $form['prep']['offer_start'] = array(
    '#type' => 'date',
    '#title' => t('Start of Course Offerings'),
    '#default_value' => _ns_date_array($date),
    '#required' => TRUE,
  );
  $date = _ns_db_get($nid, 'offer_end');
  $form['prep']['offer_end'] = array(
    '#type' => 'date',
    '#title' => t('End of Course Offerings'),
    '#default_value' => _ns_date_array($date),
    '#required' => TRUE,
  );
  $date = _ns_db_get($nid, 'schedule_posted');
    $form['prep']['schedule_posted'] = array(
    '#type' => 'date',
    '#title' => t('Schedule Posted'),
    '#default_value' => _ns_date_array($date),
    '#required' => TRUE,
  );
  $date = _ns_db_get($nid, 'member_reg_start');
    $form['prep']['member_reg_start'] = array(
    '#type' => 'date',
    '#title' => t('Start of Registration for Current Members'),
    '#default_value' => _ns_date_array($date),
    '#required' => TRUE,
  );
  $date = _ns_db_get($nid, 'former_reg_start');
  $form['prep']['former_reg_start'] = array(
    '#type' => 'date',
    '#title' => t('Start of Registration for Former Members'),
    '#default_value' => _ns_date_array($date),
    '#required' => TRUE,
  );
  $date = _ns_db_get($nid, 'new_member_reg_start');
    $form['prep']['new_member_reg_start'] = array(
    '#type' => 'date',
    '#title' => t('Start of Registration for New Members'),
    '#default_value' => _ns_date_array($date),
    '#required' => TRUE,
  );
  $date = _ns_db_get($nid, 'reg_end');
    $form['prep']['reg_end'] = array(
    '#type' => 'date',
    '#title' => t('End of Registration'),
    '#default_value' => _ns_date_array($date),
    '#required' => TRUE,
  );
  $date = _ns_db_get($nid, 'fees_posted');
    $form['prep']['fees_posted'] = array(
    '#type' => 'date',
    '#title' => t('Fees Posted'),
    '#default_value' => _ns_date_array($date),
    '#required' => TRUE,
  );
  $date = _ns_db_get($nid, 'fees_due');
    $form['prep']['fees_due'] = array(
    '#type' => 'date',
    '#title' => t('Fees Due'),
    '#default_value' => _ns_date_array($date),
    '#required' => TRUE,
  );

  // class dates
  $form['classes'] = array(
  	'#type' => 'fieldset',
    '#title' => t('Session Dates'),
  );
  for ($i = 1; $i <= 12; $i++) {
    $date = _ns_db_get($nid, 'week'.$i);
    // we don't always use all dates, so break if we get past the last date
    if ($date == '') break;
    $form['classes']['week'.$i] = array(
      '#type' => 'date',
      '#title' => t('Week '. $i),
      '#default_value' => _ns_date_array($date),
      '#required' => TRUE,
    );
  }

  // and a submit button
  $form['submit'] = array(
  	'#type' => 'submit',
    '#value' => t('Confirm Dates'),
  );
  return $form;
}

/**
 * validate the dates that the user entered (basically, make sure everything is in order
 * @todo fix date error reporting (here and possibly other validate functions)
 */
function _ns_confirm_dates_form_validate ($form, &$form_state) {
  // deal with the class dates
  // skip to the first element that exists
  for ($i = 12; !isset($form_state['values']['week'.$i]); $i--);
  // now loop through all of the actual dates (remember to skip
  // $i=1, since there is no date before it to compare it to)
  $form_state['values']['week'.$i.' num'] =
      _ns_date_convert($form_state['values']['week'.$i]);
  for (; $i > 1; $i--) {
    $form_state['values']['week'.($i-1).' num'] =
        _ns_date_convert($form_state['values']['week'.($i-1)]);
    if ($form_state['values']['week'.$i.' num'] <=
        $form_state['values']['week'.($i-1).' num']) {
      $err = 'Week '. $i .': '.
                     _ns_date_print($form_state['values']['week'.$i.' num']).
                     ' must be after week '. ($i-1) .': '.
                     _ns_date_print($form_state['values']['week'.($i-1).' num']);
      form_set_error('', $err);
    }
  }
  $form_state['values']['fees_due num'] =
      _ns_date_convert($form_state['values']['fees_due']);
  if ($form_state['values']['week1 num'] <= $form_state['values']['fees_due num']) {
    form_set_error('', 'Week 1: '.
                   _ns_date_print($form_state['values']['week1 num']).
                   ' must be after fees due: '.
                   _ns_date_print($form_state['values']['fees_due num']));
  }
  $form_state['values']['fees_posted num'] =
      _ns_date_convert($form_state['values']['fees_posted']);
  if ($form_state['values']['fees_due num'] <= $form_state['values']['fees_posted num']) {
    form_set_error('', 'Fees due: '.
                   _ns_date_print($form_state['values']['fees_due num']).
                   ' must be after fees posted: '.
                   _ns_date_print($form_state['values']['fees_posted num']));
  }
  $form_state['values']['reg_end num'] =
      _ns_date_convert($form_state['values']['reg_end']);
  if ($form_state['values']['fees_posted num'] <= $form_state['values']['reg_end num']) {
    form_set_error('', 'Fees posted: '.
                   _ns_date_print($form_state['values']['fees_posted num']).
                   ' must be after registration ends: '.
                   _ns_date_print($form_state['values']['reg_end num']));
  }
  // all registration start dates must be before registration ends (we don't care how they
  // relate to each other)
  $form_state['values']['new_member_reg_start num'] =
      _ns_date_convert($form_state['values']['new_member_reg_start']);
  if ($form_state['values']['reg_end num'] <= $form_state['values']['new_member_reg_start num']) {
    form_set_error('', 'End of registration: '.
                   _ns_date_print($form_state['values']['reg_end num']).
                   ' must be after new member registration start: '.
                   _ns_date_print($form_state['values']['new_member_reg_start num']));
  }
  $form_state['values']['former_reg_start num'] =
      _ns_date_convert($form_state['values']['former_reg_start']);
  if ($form_state['values']['reg_end num'] <= $form_state['values']['former_reg_start num']) {
    form_set_error('', 'End of registration: '.
                   _ns_date_print($form_state['values']['reg_end num']).
                   ' must be after former member registration start: '.
                   _ns_date_print($form_state['values']['former_reg_start num']));
  }
  $form_state['values']['member_reg_start num'] =
      _ns_date_convert($form_state['values']['member_reg_start']);
  if ($form_state['values']['reg_end num'] <= $form_state['values']['member_reg_start num']) {
    form_set_error('', 'End of registration: '.
                   _ns_date_print($form_state['values']['reg_end num']).
                   ' must be after member registration start: '.
                   _ns_date_print($form_state['values']['member_reg_start num']));
  }
  // all registration start dates need to be after schedule posted (we don't care how
  // they relate to each other)
  $form_state['values']['schedule_posted num'] =
      _ns_date_convert($form_state['values']['schedule_posted']);
  if ($form_state['values']['member_reg_start num'] <= $form_state['values']['schedule_posted num']) {
    form_set_error('', 'Start of member registration: '.
                   _ns_date_print($form_state['values']['member_reg_start num']).
                   ' must be after schedule posted: '.
                   _ns_date_print($form_state['values']['schedule_posted num']));
  }
  if ($form_state['values']['former_reg_start num'] <= $form_state['values']['schedule_posted num']) {
    form_set_error('', 'Start of former member registration: '.
                   _ns_date_print($form_state['values']['former_reg_start num']).
                   ' must be after schedule posted: '.
                   _ns_date_print($form_state['values']['schedule_posted num']));
  }
  if ($form_state['values']['new_member_reg_start num'] <= $form_state['values']['schedule_posted num']) {
    form_set_error('', 'Start of new member registration: '.
                   _ns_date_print($form_state['values']['new_member_reg_start num']).
                   ' must be after schedule posted: '.
                   _ns_date_print($form_state['values']['schedule_posted num']));
  }
  $form_state['values']['offer_end num'] =
      _ns_date_convert($form_state['values']['offer_end']);
  if ($form_state['values']['schedule_posted num'] <= $form_state['values']['offer_end num']) {
    form_set_error('', 'Posting of schedule: '.
                   _ns_date_print($form_state['values']['schedule_posted num']).
                   ' must be after ending of course offerings: '.
                   _ns_date_print($form_state['values']['offer_end num']));
  }
  $form_state['values']['offer_start num'] =
      _ns_date_convert($form_state['values']['offer_start']);
  if ($form_state['values']['offer_end num'] <= $form_state['values']['offer_start num']) {
    form_set_error('', 'Ending of course offerings: '.
                   _ns_date_print($form_state['values']['offer_end num']).
                   ' must be after start of course offerings: '.
                   _ns_date_print($form_state['values']['offer_start num']));
  }
}
/**
 * all dates have been validated. Put them in the calendar
 */
function _ns_confirm_dates_form_submit ($form, &$form_state) {
  // deal with the class dates
  // skip to the first element that exists
  for ($i = 12; !isset($form_state['values']['week'.$i]); $i--);
  for (; $i > 0; $i--) {
    _ns_create_event($form_state, 'week'.$i, 'Week '.$i);
  }
  _ns_create_event($form_state, 'offer_start', 'Course Offerings');
  _ns_create_event($form_state, 'schedule_posted', 'Schedule Posted');
  _ns_create_event($form_state, 'member_reg_start', 'Member Registration');
  _ns_create_event($form_state, 'former_reg_start', 'Former Member Registration');
  _ns_create_event($form_state, 'new_member_reg', 'New Member Registration');
  _ns_create_event($form_state, 'fees_posted', 'Fees Posted');
  _ns_create_event($form_state, 'fees_due', 'Fees Due');
}

/**
 * calculate the preparation dates for the given session. Store these dates
 * in our custom field
 */
function _ns_prep_dates ($nid) {
  module_load_include('inc', 'new_session', 'new_session_db');
  $first_class = _ns_db_get($nid, 'week1');
  $SECONDS_PER_DAY = 60*60*24;

  // fees due two weeks before classes start (usually the last day of the
  // previous session
  $fees_due = $first_class - 7*$SECONDS_PER_DAY;
  _ns_db_put($nid, 'fees_due', $fees_due);

  // fees posted 4 days before that
  $fees_posted = $fees_due - 7*$SECONDS_PER_DAY;
  _ns_db_put($nid, 'fees_posted', $fees_posted);

  // registration closes 3 days before that
  $reg_end = $fees_posted - 3*$SECONDS_PER_DAY;
  _ns_db_put($nid, 'reg_end', $reg_end);

  // registration for new members opens 2 days before that
  $new_member_reg_start = $reg_end - 10*$SECONDS_PER_DAY;
  _ns_db_put($nid, 'new_member_reg_start', $new_member_reg_start);

  // registration for former members the day before that
  $former_reg_start = $new_member_reg_start - $SECONDS_PER_DAY;
  _ns_db_put($nid, 'former_reg_start', $former_reg_start);
  // registration for members the day before that
  $member_reg_start = $former_reg_start - $SECONDS_PER_DAY;
  _ns_db_put($nid, 'member_reg_start', $member_reg_start);

  // schedule posted the day before that
  $schedule_posted = $member_reg_start - $SECONDS_PER_DAY;
  _ns_db_put($nid, 'schedule_posted', $schedule_posted);

  // class offerings close 2 days before
  $offer_end = $schedule_posted - 2*$SECONDS_PER_DAY;
  _ns_db_put($nid, 'offer_end', $offer_end);
    // and they open 4 days before
  $offer_start = $offer_end - 4*$SECONDS_PER_DAY;
  _ns_db_put($nid, 'offer_start', $offer_start);
}

/**
 * return the date as an array with elements for 'year', 'month', and 'day
 * @param long $date the date as a long (strtotime format) if -1, use current
 *        date
 * @return array the array form of the date
 */
function _ns_date_array ($date = -1) {
  if ($date == -1) {
    return date_parse(date('Y/m/d'));
  } else {
    return date_parse(date('Y/m/d', $date));
  }
}

/**
 * convert the date to a long
 * @param array $date the array form of the date
 * @return the strtotime form of the date
 */
function _ns_date_convert ($date) {
  return mktime(0, 0, 0, $date['month'], $date['day'], $date['year']);
}

/**
 * return a printable version of the date m/d/Y
 * @param long $date the strtotime version of the date, or the array version
 * @return string the printable version of the date
 */
function _ns_date_print ($date) {
  if (gettype($date) == 'array') {
    $date = _ns_date_convert($date);
  }
  return date('m/d/Y', $date);
}

/**
 * create the events for the calendar
 * @param array $form_state the form data
 * @param string $element which event we're creating
 * @param string $title the title of the event
 */
function _ns_create_event ($form_state, $element, $title) {
  global $user;
  module_load_include('inc', 'node', 'node.pages');
  module_load_include('inc', 'new_session', 'new_session_db');

  // get the session season for including in the event titles
  $season = _ns_db_get($form_state['values']['nid'], 'season');

  // all the member events (others are all public)
  $event_type = 'public_event';
  if ($element === 'offer_start' ||
      $element === 'member_reg_start' ||
      $element === 'former_reg_start') {
    $event_type = 'member_event';
  }

  // most events use the same start and end date
  $start_date = $form_state['values'][$element];
  $end_date = $start_date;
  if ($element === 'offer_start') {
    $end_date = $form_state['values']['offer_end'];
  }
  $str = substr($element, -9);
  if (substr($element, -9) === 'reg_start') {
    $end_date = $form_state['values']['reg_end'];
  }
  $start_time = '11:30PM';
  $end_time = '11:30PM';
  $str = substr($element, 0, 4);
  if (substr($element, 0, 4) === 'week') {
    $start_time = '09:45AM';
    $end_time = '03:15PM';
  }

  $node = array('type' => $event_type);
  $new_form_state = array();
  $new_form_state['values']['uid'] = $user->uid;
  $new_form_state['values']['title'] = $season .' '. $title;
  $new_form_state['values']['field_date'][0]['value'] = array(
      'date' => _ns_date_print($start_date),
      'time' => $start_time,
  );
  $new_form_state['values']['field_date'][0]['value2'] = array(
      'date' => _ns_date_print($end_date),
      'time' => $end_time,
  );

  $new_form_state['values']['op'] = t('Save'); // required value
  drupal_execute($event_type .'_node_form', $new_form_state, (object)$node);
}