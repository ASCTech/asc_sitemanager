<?php
// $Id$
/**
 * @file
 * All shell script calls
 *
 * Includes the scriptcaller function that handles all of the logic for
 * actually connecting to the server and making the server requests.
 */

/**
 * The get sites script call
 */
function asc_sitemanager_get_sites($environment = 'stag', $format = 0) {

  // Define the script to be called
  $script_call = 'get-sites ' . $environment . ' ' . $format;
  // Call the script
  $output = asc_sitemanager_scriptcaller($script_call, 2);

  // Return the results of the script call
  return $output;
} // function asc_sitemanager_get_sites($environment = 'stag') {

/**
 * The training sites reset script call
 */
function asc_sitemanager_reset_training_sites($type) {

  // Define the script to be called
  $script_call = 'rebuild-training-sites ' . $type;
  // Call the script
  $output = asc_sitemanager_scriptcaller($script_call, 0);

  // Return the results of the script call
  return $output;
} // function asc_sitemanager_reset_training_sites($type)

/**
 * The create site script call
 */
function asc_sitemanager_create_site($sitename, $sitetitle, $type) {

  // Define the script to be called
  $script_call = 'createsite ' . $sitename . ' ' . $sitetitle . ' ' . $type;
  // Call the script
  $output = asc_sitemanager_scriptcaller($script_call, 2);
  // Return the results of the script call
  return $output;
} // function asc_sitemanager_create_site($sitename, $sitetitle, $type)

/**
 * The move site script call
 */
function asc_sitemanager_move_site($movetype, $sitename, $sitetitle, $type) {

  // Define the script to be called
  $script_call = $movetype . ' ' . $sitename . ' ' . $sitetitle . ' ' . $type;
  // Call the script
  $output = asc_sitemanager_scriptcaller($script_call, 0);

  // Return the results of the script call
  return $output;
} // function asc_sitemanager_move_site($movetype, $sitename, $sitetitle, $type)

/**
 * The permission script call
 * @mode = 1, install - 0, normal
 */
function asc_sitemanager_set_permissions($environment, $mode) {

  if ($environment == 0) {
    $environment_name = t('dev');
  }
  elseif ($environment == 1) {
    $environment_name = t('stag');
  }
  else {
    $environment_name = t('prod');
  }

  // Define the script to be called
  if ($mode == 1) {
    $script_call = 'set-default-permissions web ' . $environment_name . ' _default true';
  }
  else {
    $script_call = 'set-default-permissions web ' . $environment_name . ' _default true true';
  }

  // Call the script
  $output = asc_sitemanager_scriptcaller($script_call, 0);

  // Return the results of the script call
  return $output;
} // function asc_sitemanager_set_permissions($environment, $mode)

/**
 * Call a script on the server
 *
 * @debug Pass 0 for no debug, 1 for command as passed output only, 2 for command as passed and dev null
 */
function asc_sitemanager_scriptcaller($script_call, $debug = 0) {
  // Define the username
  $temp_user = variable_get("asc_sitemanager_admin_username", '');
  // Check to see if a password has been set
  if (variable_get("asc_sitemanager_passtoggle", FALSE) == TRUE) {
    $decryptedpass = decrypt(variable_get("asc_sitemanager_admin_password", 'NOVALUE'), variable_get("asc_sitemanager_admin_password_salt", 'NOVALUE'));
    $server_user = $temp_user . ':' . $decryptedpass;
  }
  else {
    $server_user = $temp_user;
  }

  $server_url = variable_get("asc_sitemanager_remote_server", 'nfs-prod.asc.ohio-state.edu');
  $script_dir = variable_get("asc_sitemanager_script_dir", '/usr/local/osu/scripts/');
  $server_port = variable_get("asc_sitemanager_remote_port", '2200');
  $command = 'ssh -p ' . $server_port . ' ' . $server_user . '@' . $server_url . ' "' . $script_dir . $script_call . '"';
  // dev null output does not seem to be working
  /*if ($debug == 2) {
    $command .= ' > /dev/null 2>&1"';
  }
  else {
    $command .= '"';
  }*/

  $shell_results = shell_exec($command);
  // The shell returns the site listing in a single line, white space is encoded.
  // URL encode the string and replace spaces with breaks.
  $shell_results = str_replace('%0A', '<br />', urlencode($shell_results));
  $output = '';
  if ($debug != 0) {
    $output = $command . '<br />';
  }
  $output .= trim(urldecode($shell_results));
  return $output;
}