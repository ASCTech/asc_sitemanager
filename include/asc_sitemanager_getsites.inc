<?php
// $Id$
/**
 * @file
 * Get sites functions
 */

/**
 * The get sites page
 */
function get_sites_page() {
  // Initialize the page content variable
  $output = '';

  // Store the requested environment
  $temp_environment = variable_get($environment, 'stag');

  if ($temp_environment == 'dev') {
    $env_name = 'Development';
  }
  elseif ($temp_environment == 'prod') {
    $env_name = 'Production';
  }
  else {
    $env_name = 'Staging';
  }

  // Display the form
  $output .= drupal_get_form('asc_sitemanager_get_sites_form');

  // Get the list of sites on the requested environment
  $output .= '<strong>' . $env_name . ' Sites</strong>:<br />';

  // Call the script on the server
  $output .= asc_sitemanager_get_sites($temp_environment);

  // Empty the environment variable
  variable_set($environment, 'stag');

  // Return the page content
  return $output;
}

/**
 * The get sites form
 */
function asc_sitemanager_get_sites_form($form) {

  // Declare the form
  $form = array();

  $environment_options = array(
    'dev' => 'Development',
    'staging' => 'Staging',
    'prod' => 'Production',
  );

  $form['getsites'] = array(
    '#type' => 'fieldset',
    '#title' => t('Get Sites'),
  );

  // Define our global variable
  $form['getsites']['environment'] = array(
    '#type' => 'select',
    '#title' => t('Select Environment'),
    '#options' => $environment_options,
    '#description' => t("Choose the environment to display sites from."),
    '#required' => TRUE,
  );

  // Define our global variable
  $form['getsites']['submit'] = array(
    '#type' => 'submit',
    '#title' => t('Get Sites'),
    '#value' => t('Get Sites'),
  );

  // Return the form to system settings
  return $form;
} // function asc_sitemanager_get_sitesform($form, &$form_state)

/**
 * The get sites form - submit handler
 */
function asc_sitemanager_get_sites_form_submit($form, &$form_state) {
  // Get the environment selected
  variable_set($environment, $form_state['values']['environment']);

  // Display a confirmation message
  drupal_set_message(t('Below are the current ' . variable_get($environment, 'stag') . ' sites.'));
}