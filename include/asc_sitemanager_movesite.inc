<?php
// $Id$
/**
 * @file
 * Move site functions
 */

/**
 * The move sites page
 */
function move_sites_page() {
  // Initialize the page content variable
  $output = '';

  // Display the form
  $output .= drupal_get_form('asc_sitemanager_move_sites_form');

  // Return the page content
  return $output;
} // function move_sites_page()

/**
 * The move sites form
 */
function asc_sitemanager_move_sites_form($form_state) {

  if (empty($form_state['storage']['values']['step'])) {
    $page = 1;
  }
  elseif ($form_state['storage']['values']['step'] == 2) {
    $page = 2;
  }
  elseif ($form_state['storage']['values']['step'] == 3) {
    $page = 3;
  }
  else {
    $page = 1;
  }

  // Declare the form
  $form = array();

  switch ($page) {
    case 1:
      $reset_options = array(
        '0' => 'Development to Staging',
        '1' => 'Staging to Production',
        '2' => 'Production to Development',
      );

      $form['movesites'] = array(
        '#type' => 'fieldset',
        '#title' => t('Select the place to move a site'),
      );

      // Define the fieldset
      $form['movesites']['message'] = array(
        '#type' => 'markup',
        '#value' => t('<strong style="color: #f00;">Warning</strong>: This section is currently not working. There seems to be a permission problem with the script.'),
      );

      $form['movesites']['direction'] = array(
        '#type' => 'select',
        '#title' => t('Where?'),
        '#options' => $reset_options,
        '#description' => t("Select destination and origin."),
        '#required' => TRUE,
      );

      // Define our global variable
      $form['movesites']['submit'] = array(
      '#type' => 'submit',
      '#title' => t('Move Site'),
      '#value' => t('Move Site'),
      );
    break;
    case 2:
      // stristr(trim($stag_site_list), $sitestring)
      $direction = $form_state['storage']['values']['direction'];
      if ($direction == 0) {
        // Development to Staging
        $target_source = t('Development');
        $target_destination = t('Staging');
        $srce_sites_raw = asc_sitemanager_get_sites('dev', 1);
        $dest_sites = asc_sitemanager_get_sites('stag', 1);
      }
      elseif ($direction == 1) {
        // Staging to Production
        $target_source = t('Staging');
        $target_destination = t('Production');
        $srce_sites_raw = asc_sitemanager_get_sites('stag', 1);
        $dest_sites = asc_sitemanager_get_sites('prod', 1);
      }
      else {
        // Production to Development
        $target_source = t('Production');
        $target_destination = t('Development');
        $srce_sites_raw = asc_sitemanager_get_sites('prod', 1);
        $dest_sites = asc_sitemanager_get_sites('dev', 1);
      }

      $srce_site_list = array();
      $srce_sites = str_replace('<br />', ',', $srce_sites_raw);
      $srce_sites = explode(',', $srce_sites);
      foreach ($srce_sites as &$site) {
        if ($site != '') {
          $srce_site_list[$site] = $site;
        }
      }
      $form['movesites'] = array(
        '#type' => 'fieldset',
        '#title' => t('Confirm move Sites Reset'),
      );

      $form['movesites']['direction'] = array(
        '#type' => 'hidden',
        '#value' => $form_state['storage']['values']['direction'],
      );

      $form['movesites']['source_site'] = array(
        '#type' => 'select',
        '#title' => t('Select the Site to move to ' . $target_destination),
        '#options' => $srce_site_list,
        '#description' => t('Select the ' . $target_source . ' site you would like to move to ' . $target_destination . '.'),
        '#required' => TRUE,
      );

      $form['movesites']['submit'] = array(
        '#type' => 'submit',
        '#title' => t('Select'),
        '#value' => t('Select'),
      );

    break;
    case 3:
      $direction = $form_state['values']['direction'];
      $source_site = str_replace('.osu.edu', '', $form_state['values']['source_site']);
      if ($direction == 0) {
        $confirm_dir = t('move the ' . $source_site . ' site from Development to Staging');
        $dest_env = 'stag';
      }
      elseif ($direction == 1) {
        $confirm_dir = t('move the ' . $source_site . ' site from Staging to Production');
        $dest_env = 'prod';
      }
      elseif ($direction == 2) {
        $confirm_dir = t('move the ' . $source_site . ' site from Production to Development');
        $dest_env = 'dev';
      }
      else {
        $confirm_dir = t('location not specified.');
      }

      $reset_options = array(
        '0' => 'No',
        '1' => 'Yes',
      );

      $form['movesites'] = array(
        '#type' => 'fieldset',
        '#title' => t('Confirm Site Move'),
      );

      // Warn the user if we are overwriting an existing site
      $site_list_raw = asc_sitemanager_get_sites($dest_env);
      $site_list = str_replace('<br />', ' ', $site_list_raw);
      // Search the site list for our reformatted site name
      if (stristr(trim($site_list), $source_site) == TRUE) {
        // The site was found, display the warning
        $form['movesites']['warning'] = array(
          '#type' => 'markup',
          '#value' => t('<strong style="color: #f00;">WARNING</strong>: You will overwrite the existing site. Be sure you backup your database and files.'),
        );
      }

      $form['movesites']['answer'] = array(
        '#type' => 'select',
        '#title' => t('Are you sure you want to ' . $confirm_dir . '?'),
        '#options' => $reset_options,
        '#description' => t("Confirm that you would like to move site."),
        '#required' => TRUE,
      );

      $form['movesites']['submit'] = array(
        '#type' => 'submit',
        '#title' => t('Confirm'),
        '#value' => t('Confirm'),
      );
    break;
  }

  // Return the form to system settings
  return $form;
} // function asc_sitemanager_move_sites_form($form_state)

function asc_sitemanager_move_sites_form_submit($form, &$form_state) {

  if (empty($form_state['storage']['values']['step'])) {
    // if there is no previous values redraw for second step
    $form_state['storage']['values'] = $form_state['values'];
    $form_state['storage']['values']['step'] = 2;
    $form_state['rebuild'] = TRUE;
  }
  elseif ($form_state['storage']['values']['step'] == 2) {
    // if there is no previous values redraw for second step
    $form_state['storage']['values'] = $form_state['values'];
    $form_state['storage']['values']['step'] = 3;
    $form_state['rebuild'] = TRUE;
  }
  elseif ($form_state['storage']['values']['step'] == 3) {
    $answer = $form_state['values']['answer'];
    if ($answer == 0) {
      drupal_set_message(t('Action Cancelled.'));
    }
    else {
      $direction = $form_state['storage']['values']['direction'];
      $source_site = $form_state['storage']['values']['source_site'];
      $source_site = str_replace('.osu.edu', '', $source_site);
      if ($direction == 0) {
        //$output = asc_sitemanager_move_site('dev-to-stag', $source_site, $source_site, 1);
        $output = 'This is not working...see comment on main form.';
        drupal_set_message(t('Moved ' . $source_site . ' from Development to Staging<br />' . $output));
      }
      elseif ($direction == 1) {
        //$output = asc_sitemanager_move_site('stag-to-prod', $source_site, $source_site, 1);
        $output = 'This is not working...see comment on main form.';
        drupal_set_message(t('Moved ' . $source_site . ' from Staging to Production<br />' . $output));
      }
      elseif ($direction == 2) {
        //$output = asc_sitemanager_move_site('prod-to-dev', $source_site, $source_site, 1);
        $output = 'This is not working...see comment on main form.';
        drupal_set_message(t('Moved ' . $source_site . ' from Production to Development<br />' . $output));
      }
      else {
        drupal_set_message(t('Location not specified.'));
      }
    }
    drupal_goto($base_path . 'sitemanager/2/3');
  }
  else {
    drupal_goto($base_path . 'sitemanager/2/3');
  }

} // function asc_sitemanager_move_sites_form_submit($form, &$form_state)