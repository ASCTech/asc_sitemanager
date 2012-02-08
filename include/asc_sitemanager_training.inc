<?php
// $Id$
/**
 * @file
 * The training site management functions
 */

/**
 * The training pages
 */
function asc_sitemanager_training() {
  // Initialize the page content variable
  $output = '';

  $output .= 'Training';
  $output .= $GLOBALS['mainmenu'];

  // Temporarily store the variable passed from the form
  $temp_type = trim(variable_get($trainingtype, 'default'));

  switch ($temp_type) {
    case 'ce':
      // Display the sites page
      $output .= reset_training_sites_page('ce');
      break;
    case 'cm':
      // Display the sites page
      $output .= reset_training_sites_page('cm');
      break;
    default:
      // Do nothing, the form was not submitted
      // Display the form
      $output .= drupal_get_form('reset_training_sites_form');
      break;
  }
  unset($temp_type);


  // Return the page content
  return $output;

} // function asc_sitemanager_training()

/**
 * Training site select reset form
 */
function reset_training_sites_form($form) {

  // Declare the form
  $form = array();

  $type_options = array(
    'ce' => 'Content Editor',
    'cm' => 'Content Manager',
  );

  $form['resetsites'] = array(
    '#type' => 'fieldset',
    '#title' => t('Reset Training Sites'),
  );

  // Define our global variable
  $form['resetsites']['type'] = array(
    '#type' => 'select',
    '#title' => t('Select Site Type'),
    '#options' => $type_options,
    '#description' => t("Choose the type of training site that you would like to reset."),
    '#required' => TRUE,
  );

  // Define our global variable
  $form['resetsites']['submit'] = array(
    '#type' => 'submit',
    '#title' => t('Reset Sites'),
    '#value' => t('Reset Sites'),
  );

  // Return the form to system settings
  return $form;
}

/**
 * Training site select reset form - submit handler
 */
function reset_training_sites_form_submit($form, &$form_state) {
  // Get the environment selected
  variable_del($trainingtype);
  variable_set($trainingtype, $form_state['values']['type']);
}

/**
 * Training site reset page
 */
function reset_training_sites_page($type) {
  // Initialize the page content variable
  $output = '';

  // Temporarily store the variable passed from the form
  $temp_type = trim(variable_get($trainingtype, 'default'));
  if ($temp_type == 'ce') {
    $type_name = 'Content Editor';
  }
  else {
    $type_name = 'Content Manager';
  }

  // Display the confirmation form
  $output .= drupal_get_form('confirm_trainingreset_form');

  // Call the script on the server
  //$output .= reset_training_sites($type, 0);

  // Return the page content
  return $output;

} // function reset_training_sites_page($type)

/**
 * Training site reset confirmation form
 */
function confirm_trainingreset_form($form) {

  // Declare the form
  $form = array();

  if (variable_get($trainingtype, 'default') == 'ce') {
    $type_name = 'Content Editor';
  }
  else {
    $type_name = 'Content Manager';
  }

  $reset_options = array(
    '0' => 'No',
    '1' => 'Yes',
  );

  $form['confirmreset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Confirm ' . $type_name . ' Sites Reset'),
  );

  // Define our global variable
  $form['confirmreset']['answer'] = array(
    '#type' => 'select',
    '#title' => t('Are you sure?'),
    '#options' => $reset_options,
    '#description' => t("Confirm that you would like to reset the " . $type_name . " sites."),
    '#required' => TRUE,
  );

  // Define our global variable
  $form['confirmreset']['trainingtype'] = array(
    '#type' => 'hidden',
    '#value' => variable_get($trainingtype, 'default'),
  );

  // Define our global variable
  $form['confirmreset']['submit'] = array(
    '#type' => 'submit',
    '#title' => t('Confirm'),
    '#value' => t('Confirm'),
  );

  // Return the form to system settings
  return $form;
}

/**
 * Training site reset confirmation form - submit handler
 */
function confirm_trainingreset_form_submit($form, &$form_state) {
  // Get the environment selected
  variable_set($resetconfirm, $form_state['values']['answer']);

  $temp_type = $form_state['values']['trainingtype'];
  variable_del($trainingtype);

  if ($temp_type == 'ce') {
    $type_name = t('Content Editor');
  }
  else {
    $type_name = t('Content Manager');
  }

  if ($form_state['values']['answer'] == '1') {
    $reset_output = asc_sitemanager_reset_training_sites($temp_type);
    $mess = t('The ' . $type_name . ' sites have been reset.<br /><br />' . $reset_output);
  }
  else {
    $mess = t('Action Cancelled');
  }

  // Display a confirmation message
  drupal_set_message($mess);
}