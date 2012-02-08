<?php
// $Id$
/**
 * @file
 * The module administration functions
 */

/**
 * The administration pages
 */
function asc_sitemanager_admin() {
  // Initialize the page content variable
  $output = '';

  $output .= 'Module Administration';
  $output .= $GLOBALS['mainmenu'];

  $output .= drupal_get_form('asc_sitemanager_adminform_form');

  // Return the page content
  return $output;
} // function asc_sitemanager_admin()

/**
 * The administration form
 */
function asc_sitemanager_adminform_form($form) {

  // Declare the form
  $form = array();

  // Define our username variable
  $form['asc_sitemanager_admin_username'] = array(
    '#type' => 'textfield',
    '#size' => '50',
    '#title' => t('Administrator Username'),
    '#default_value' => variable_get("asc_sitemanager_admin_username", ''),
    '#description' => t("Enter the administrator username for the remote server."),
    '#required' => TRUE,
  );

  // Define our remote url variable
  $form['asc_sitemanager_remote_server'] = array(
    '#type' => 'textfield',
    '#size' => '50',
    '#title' => t('Remote Server URL'),
    '#default_value' => variable_get("asc_sitemanager_remote_server", 'nfs-prod.asc.ohio-state.edu'),
    '#description' => t("Enter the address of the remote server (for logging in via ssh)."),
    '#required' => TRUE,
  );

  // Define our script directory variable
  $form['asc_sitemanager_script_dir'] = array(
    '#type' => 'textfield',
    '#size' => '50',
    '#title' => t('Remote Script Directory'),
    '#default_value' => variable_get("asc_sitemanager_script_dir", '/usr/local/osu/scripts/'),
    '#description' => t("Enter the directory that our scripts reside in."),
    '#required' => TRUE,
  );

  // Define our remote port variable
  $form['asc_sitemanager_remote_port'] = array(
    '#type' => 'textfield',
    '#size' => '50',
    '#title' => t('Remote Server Port'),
    '#default_value' => variable_get("asc_sitemanager_remote_port", '2200'),
    '#description' => t("Enter the port of the remote server (for logging in via ssh)."),
    '#required' => TRUE,
  );

  // Toggle password usage on or off
  $form['asc_sitemanager_passtoggle'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Password'),
    '#default_value' => variable_get("asc_sitemanager_passtoggle", FALSE),
    '#description' => t('Check this checkbox to use a password. <strong style="color: #900;">NOTE: This functionality is untested.</strong>'),
    '#required' => TRUE,
  );

  // Define our password variable
  $form['asc_sitemanager_admin_password'] = array(
    '#type' => 'password',
    '#size' => '50',
    '#title' => t('Administrator Password'),
    '#default_value' => variable_get("asc_sitemanager_admin_password", 'NOVALUE'),
    '#description' => t('Enter the administrator password for the remote server. The "Use Password" checkbox above must be checked for this to be used.'),
    '#required' => FALSE,
  );

  // Return the form to system settings
  return system_settings_form($form);
} // function asc_sitemanager_adminform($form, &$form_state)

/**
 * Encrypt the submitted password and store the salt so it can be decrypted later
 */
function asc_sitemanager_adminform_form_validate($form, &$form_state) {
  $salt = makesalt();
  $encryptedpass = encrypt($form_state['values']['asc_sitemanager_admin_password'], $salt);
  variable_set("asc_sitemanager_admin_password", $encryptedpass);
  variable_set("asc_sitemanager_admin_password_salt", $salt);
  $form_state['values']['asc_sitemanager_admin_password'] = variable_get("asc_sitemanager_admin_password", 'NOVALUE');
  // To decrypt the password:
  //$decryptedPass = decrypt(variable_get("asc_sitemanager_admin_password", 'NOVALUE'), variable_get("asc_sitemanager_admin_password_salt", 'NOVALUE'));
}

/**
 * Create a 32 character salt
 */
function makesalt() {
  $alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$$%^&*()_+";
  $i = 0;
  $salt = "";
  for ($i = 0; $i < 32; $i++) {
    $pos = mt_rand(1, drupal_strlen($alpha));
    $salt .= drupal_substr($alpha, $pos, 1);
  }
  return $salt;
} // function makesalt()

/**
 * Encrypt a string with a passed salt
 */
function encrypt($text, $salt) {
    $text = trim(base64_encode(mcrypt_encrypt(MCRYPT_RIJNDAEL_256, $salt, $text, MCRYPT_MODE_ECB, mcrypt_create_iv(mcrypt_get_iv_size(MCRYPT_RIJNDAEL_256, MCRYPT_MODE_ECB), MCRYPT_RAND))));
    return $text;
}

/**
 * Decrypt a string with a passed salt
 */
function decrypt($text, $salt) {
    $text = trim(mcrypt_decrypt(MCRYPT_RIJNDAEL_256, $salt, base64_decode($text), MCRYPT_MODE_ECB, mcrypt_create_iv(mcrypt_get_iv_size(MCRYPT_RIJNDAEL_256, MCRYPT_MODE_ECB), MCRYPT_RAND)));
    return $text;
}