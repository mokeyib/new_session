<?php

/*
 * create the courses and jobs that we use for all sessions
 */
function new_session_initialize () {
  global $user;
  module_load_include('inc', 'new_session', 'constants');

  $msg = "<h1>Initializing new session</h1>\n";
  $msg .= "<ul>\n";
  $msg .= _ns_initialize_away(1, PERIOD1);
  $msg .= _ns_initialize_away(2, PERIOD2);
  $msg .= _ns_initialize_away(3, PERIOD3);
  $msg .= _ns_initialize_away(4, PERIOD4);

  $msg .= _ns_initialize_vols_free_before();
  $msg .= _ns_initialize_vols_free_period(1, PERIOD1);
  $msg .= _ns_initialize_vols_free_period(2, PERIOD2);
  $msg .= _ns_initialize_vols_free_lunch();
  $msg .= _ns_initialize_vols_free_period(3, PERIOD3);
  $msg .= _ns_initialize_vols_free_period(4, PERIOD4);
  $msg .= _ns_initialize_vols_free_after();

  $msg .= _ns_initialize_party();

  $msg .= "</ul>\n";

  return $msg;
}

/**
 * initialize a party planning course
 * @return string the <li> enclosed text to print for a status message
 */
function _ns_initialize_party () {
  module_load_include('inc', 'new_session', 'constants');

  $course_nid = _ns_create_course('Party Planning', 'Party', LUNCH,
      LOBBY,
      'Planning for a end of session party. Add as many teachers and '.
      'assistants as desired. Use teacher if you plan to take more '.
      'responsibility, and teaching assistant if you just want to help.');
  $msg = "<li>New party planning node with nid <a href=\"../node/".
      $course_nid ."\">". $course_nid ."</a> created.\n";

  $msg .= "<ul>\n";
  $nid = _ns_create_job($course_nid, TEACHER);
  $msg .= "<li>Teacher, nid <a href=\"../node/". $nid ."\">". $nid .
          "</a> created.</li>\n";
  $nid = _ns_create_job($course_nid, TEACHING_ASSISTANT);
  $msg .= "<li>Teaching assistant, nid <a href=\"../node/". $nid ."\">". $nid .
          "</a> created.</li>\n";
  $msg .= "</ul></li>";

  return $msg;
}

/**
 * initialize one period of Not at Co-op
 * @param int $period the number of the period (1, 2, 3, 4)
 * @param int $period the nid of the period
 * @return string the <li> enclosed text to print for a status message
 */
function _ns_initialize_away($period_num, $period) {
  module_load_include('inc', 'new_session', 'constants');
  $course_nid = _ns_create_course('Not at Co-op ('.$period_num.')',
      'Away', $period, OUTSIDE,
      'Please sign up for this if you are not going to be at co-op this period.');
  return "<li>New node Away ".$period_num." with nid <a href=\"../node/".
      $course_nid ."\">". $course_nid ."</a> created.</li>\n";
}

/**
 * initialize Volunteers and Free Play Before
 * @return string the <li> enclosed text to print for a status message
 */
function _ns_initialize_vols_free_before () {
  module_load_include('inc', 'new_session', 'constants');
  $course_nid = _ns_create_vols_free_course('Volunteers and Free Play (0)',
      'Vols & Free', BEFORE);
  $msg = "<li>New node Vols & Free Before with nid <a href=\"../node/".
      $course_nid ."\">". $course_nid ."</a> created.\n";

  $msg .= "<ul>\n";
  $nid = _ns_create_job($course_nid, AUDITORIUM_MONITOR);
  $msg .= "<li>Auditorium monitor, nid <a href=\"../node/". $nid ."\">". $nid .
          "</a> created.</li>\n";
  $nid = _ns_create_job($course_nid, SET_UP);
  $msg .= "<li>Setup manager, nid <a href=\"../node/". $nid ."\">". $nid .
          "</a> created.</li>\n";
  $nid = _ns_create_job($course_nid, VOLUNTEER_MGR);
  $msg .= "<li>Volunteer manager, nid <a href=\"../node/". $nid ."\">". $nid .
          "</a> created.</li>\n";
  $msg .= "</ul></li>";

  return $msg;
}

/**
 * initialize Volunteers and Free Play Lunch
 * @return string the <li> enclosed text to print for a status message
 */
function _ns_initialize_vols_free_lunch () {
  module_load_include('inc', 'new_session', 'constants');
  $course_nid = _ns_create_vols_free_course('Volunteers and Free Play (2.5)',
      'Vols & Free', LUNCH);
  $msg = "<li>New node Vols & Free Lunch with nid <a href=\"../node/".
      $course_nid ."\">". $course_nid ."</a> created.\n";

  $msg .= "<ul>\n";
  $nid = _ns_create_job($course_nid, LUNCH_CLEAN);
  $msg .= "<li>Lunch cleanup manager, nid <a href=\"../node/". $nid ."\">". $nid .
          "</a> created.</li>\n";
  $nid = _ns_create_job($course_nid, LUNCH_TIME);
  $msg .= "<li>Lunch time keeper, nid <a href=\"../node/". $nid ."\">". $nid .
          "</a> created.</li>\n";
  $nid = _ns_create_job($course_nid, GYM_MONITOR);
  $msg .= "<li>Gym monitor, nid <a href=\"../node/". $nid ."\">". $nid .
          "</a> created.</li>\n";
  $nid = _ns_create_job($course_nid, GYM_MONITOR);
  $msg .= "<li>Gym monitor, nid <a href=\"../node/". $nid ."\">". $nid .
          "</a> created.</li>\n";
  $msg .= "</ul></li>";

  return $msg;
}

/**
 * initialize Volunteers and Free Play After
 * @return string the <li> enclosed text to print for a status message
 */
function _ns_initialize_vols_free_after () {
  module_load_include('inc', 'new_session', 'constants');
  $course_nid = _ns_create_vols_free_course('Volunteers and Free Play (5)',
      'Vols & Free', AFTER);
  $msg = "<li>New node Vols & Free After with nid <a href=\"../node/".
      $course_nid ."\">". $course_nid ."</a> created.\n";

  $msg .= "<ul>\n";
  $nid = _ns_create_job($course_nid, CLEAN_UP);
  $msg .= "<li>Cleanup manager, nid <a href=\"../node/". $nid ."\">". $nid .
          "</a> created.</li>\n";
  $nid = _ns_create_job($course_nid, AUDITORIUM_MONITOR);
  $msg .= "<li>Auditorium monitor, nid <a href=\"../node/". $nid ."\">". $nid .
          "</a> created.</li>\n";
  for ($i = 0; $i < 5; $i++) {
    $nid = _ns_create_job($course_nid, COMMITTEE);
    $msg .= "<li>Committee member, nid <a href=\"../node/". $nid ."\">". $nid .
            "</a> created.</li>\n";
  }
  $msg .= "</ul></li>";

  return $msg;
}

/**
 * initialize one period of Volunteers and Free Play
 * @param int $period the number of the period (1, 2, 3, 4)
 * @param int $period the nid of the period
 * @return string the <li> enclosed text to print for a status message
 */
function _ns_initialize_vols_free_period ($period_num, $period) {
  module_load_include('inc', 'new_session', 'constants');
  $course_nid = _ns_create_vols_free_course('Volunteers and Free Play ('.$period_num.')',
      'Vols & Free', $period);
  $msg = "<li>New node Vols & Free ".$period_num." with nid <a href=\"../node/".
      $course_nid ."\">". $course_nid ."</a> created.\n";

  $msg .= "<ul>\n";
  for ($i = 0; $i < 2; $i++) {
    $nid = _ns_create_job($course_nid, AUDITORIUM_MONITOR);
    $msg .= "<li>Auditorium monitor, nid <a href=\"../node/". $nid ."\">". $nid .
            "</a> created.</li>\n";
  }
  for ($i = 0; $i < 2; $i++) {
    $nid = _ns_create_job($course_nid, GAME_MONITOR);
    $msg .= "<li>Game room monitor, nid <a href=\"../node/". $nid ."\">". $nid .
            "</a> created.</li>\n";
  }
  for ($i = 0; $i < 2; $i++) {
    $nid = _ns_create_job($course_nid, GYM_MONITOR);
    $msg .= "<li>Gym monitor, nid <a href=\"../node/". $nid ."\">". $nid .
            "</a> created.</li>\n";
  }
  for ($i = 0; $i < 2; $i++) {
    //  $nid = _ns_create_job($course_nid, PLAYGROUND);
    //  $msg .= "<li>Playground monitor, nid <a href=\"../node/". $nid ."\">". $nid .
    //          "</a> created.</li>\n";
  }
  $nid = _ns_create_job($course_nid, FLOATER);
  $msg .= "<li>Floater, nid <a href=\"../node/". $nid ."\">". $nid .
          "</a> created.</li>\n";
  $nid = _ns_create_job($course_nid, UNASSIGNED);
  $msg .= "<li>Unassigned Volunteer, nid <a href=\"../node/". $nid ."\">". $nid .
          "</a> created.</li>\n";
  $msg .= "</ul></li>\n";

  return $msg;
}

/**
 * create a single volunteers and free play course
 * @param string $title the title of the course
 * @param string $short_title the short title of the course
 * @param int $period the period nid for the course
 * @return int the nid
 */
function _ns_create_vols_free_course ($title, $short_title, $period) {
  module_load_include('inc', 'new_session', 'constants');
  return _ns_create_course($title, $short_title, $period, LOBBY,
      'If you do not want a class assignment this period (either as a student or a '.
      'volunteer), sign up as a student of this class. You can move freely among any '.
      'of the open free play areas (auditorium, computer lab, game room, gym, playground).'.
      'Note that not each area is open each period.'.
      'This is also a placeholder for certain volunteer jobs.');
}

/**
 * create a single course
 * @param string $title the title of the course
 * @param string $short_title the short title of the course
 * @param int $period the period nid for the course
 * @param int $room the room nid for the course
 * @param string $description a description of the course
 * @return int the nid
 */
function _ns_create_course ($title, $short_title, $period, $room,
     $description) {
  global $user;

  $node = (object) NULL;
  $node->type = 'course';
  $node->title = $title;
  $node->uid = $user->uid;
  $node->created = strtotime("now");
  $node->changed = strtotime("now");
  $node->status = 1;
  $node->comment = 0;
  $node->promote = 0;
  $node->moderate = 0;
  $node->sticky = 0;
  // add CCK field data
  $node->field_course_short_name[0]['value'] = $short_title;
  $node->field_course_description[0]['value'] = $description;
  $node->field_course_age_firm[0]['value'] = 'Suggestion';
  $node->field_course_min_students[0]['value'] = 1;
  $node->field_course_max_students[0]['value'] = 100;
  $node->field_course_room_reqs[0]['value'] = '.';
  $node->field_course_time_reqs[0]['value'] = '.';
  $node->field_course_dropins[0]['value'] = 'No drop-ins';
  $node->field_course_period[0]['nid'] = $period;
  $node->field_course_room[0]['nid'] = $room;

  // save node
  node_save($node);

  return $node->nid;
}

/**
 * create a new job
 * @param int $nid the node id of the course
 * @param int $job the job id of the job
 * @return int the nid
 */
function _ns_create_job ($nid, $job) {
  global $user;

  $node = (object) NULL;
  $node->type = 'volunteer_signup';
  $node->uid = $user->uid;
  $node->created = strtotime("now");
  $node->changed = strtotime("now");
  $node->status = 1;
  $node->comment = 0;
  $node->promote = 0;
  $node->moderate = 0;
  $node->sticky = 0;
  // add CCK field data
  $node->field_vol_signup_course[0]['nid'] = $nid;
  $node->field_vol_job[0]['nid'] = $job;

  // save node
  node_save($node);

  return $node->nid;
}
