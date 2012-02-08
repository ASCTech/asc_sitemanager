<?php
// $Id$
/**
 * @file
 * Permission functions
 */

/**
 * The permission page
 */
function permission_page() {
  // Initialize the page content variable
  $output = '';

  // Display the form
  $output .= drupal_get_form('asc_sitemanager_permission_form');

  // Return the page content
  return $output;
} // function permission_page()

/**
 * The permission form
 */
function asc_sitemanager_permission_form($form_state) {

  if (empty($form_state['storage']['values']['step'])) {
    $page = 1;
  }
  elseif ($form_state['storage']['values']['step'] == 2) {
    $page = 2;
  }
  else {
    $page = 1;
  }

  // Declare the form
  $form = array();

  switch ($page) {
    case 1:
      $perm_mode = array(
        '0' => 'Install Mode',
        '1' => 'Normal Mode',
      );

      $environment = array(
        '0' => 'Development',
        '1' => 'Staging',
        '2' => 'Production',
      );

      $form['permission'] = array(
        '#type' => 'fieldset',
        '#title' => t('Set Permissions'),
      );

      $form['permission']['perm_mode'] = array(
        '#type' => 'select',
        '#title' => t('Permission Type'),
        '#options' => $perm_mode,
        '#description' => t("Select the type of permissions you would like to set. <strong>NOTE</strong>: Install mode makes the drupal install vulnerable to attack."),
        '#required' => TRUE,
      );

      $form['permission']['environment'] = array(
        '#type' => 'select',
        '#title' => t('Select Environment'),
        '#options' => $environment,
        '#description' => t("Select the environment on which you would like to set permissions."),
        '#required' => TRUE,
      );

      // Define our global variable
      $form['permission']['submit'] = array(
      '#type' => 'submit',
      '#title' => t('Set Permissions'),
      '#value' => t('Set Permissions'),
      );
    break;
    case 2:

      $perm_mode = $form_state['storage']['values']['perm_mode'];
      if ($perm_mode == 0) {
        $perm_mode = t('Install Mode');
      }
      else {
        $perm_mode = t('Normal Mode');
      }
      $environment = $form_state['storage']['values']['environment'];
      if ($environment == 0) {
        $environment = t('Development');
      }
      elseif ($environment == 1) {
        $environment = t('Staging');
      }
      else {
        $environment = t('Production');
      }

      $reset_options = array(
        '0' => 'No',
        '1' => 'Yes',
      );

      $form['permission'] = array(
        '#type' => 'fieldset',
        '#title' => t('Confirm Changes'),
      );

      $form['permission']['answer'] = array(
        '#type' => 'select',
        '#title' => t('Are you sure you want to set the permissions to ' . $perm_mode . ' on the ' . $environment . ' environment?'),
        '#options' => $reset_options,
        '#description' => t("Confirm that you would like to change the permissions."),
        '#required' => TRUE,
      );

      $form['permission']['submit'] = array(
      '#type' => 'submit',
      '#title' => t('Confirm'),
      '#value' => t('Confirm'),
      );
    break;
  }

  // Return the form to system settings
  return $form;
} // function asc_sitemanager_permission_form($form_state)

function asc_sitemanager_permission_form_submit($form, &$form_state) {

  if (empty($form_state['storage']['values']['step'])) {
    // if there is no previous values redraw for second step
    $form_state['storage']['values'] = $form_state['values'];
    $form_state['storage']['values']['step'] = 2;
    $form_state['rebuild'] = TRUE;
  }
  elseif ($form_state['storage']['values']['step'] == 2) {
    $answer = $form_state['values']['answer'];
    if ($answer == 0) {
      drupal_set_message(t('Action Cancelled.'));
    }
    else {
      $perm_mode = $form_state['storage']['values']['perm_mode'];
      if ($perm_mode == 0) {
        $perm_mode_name = t('Install Mode');
      }
      else {
        $perm_mode_name = t('Normal Mode');
      }
      $environment = $form_state['storage']['values']['environment'];
      if ($environment == 0) {
        $environment_name = t('Development');
      }
      elseif ($environment == 1) {
        $environment_name = t('Staging');
      }
      else {
        $environment_name = t('Production');
      }

      $output = asc_sitemanager_set_permissions($environment, $perm_mode);
      drupal_set_message(t('Permissions have been set to ' . $perm_mode_name . ' on the ' . $environment_name . ' environment.<br /><br />' . $output));
    }
    drupal_goto($base_path . 'sitemanager/2/4');
  }
  else {
    drupal_goto($base_path . 'sitemanager/2/4');
  }

} // function asc_sitemanager_permission_form_submit($form, &$form_state)