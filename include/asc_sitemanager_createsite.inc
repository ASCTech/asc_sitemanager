<?php
// $Id$
/**
 * @file
 * Create site functions
 */

/**
 * The create site page
 */
function create_site_page() {
  // Initialize the page content variable
  $output = '';

  // Display the form
  $output .= drupal_get_form('asc_sitemanager_create_site_form');

  // Return the page content
  return $output;
} // function create_site_page()

/**
 * The create site form
 */
function asc_sitemanager_create_site_form($form) {

  // Declare the form
  $form = array();

  // Define our site type options
  $sitetype_options = array(
    '1' => 'Standard Site',
    '2' => 'Custom Site',
  );

  // Define the fieldset
  $form['createsite'] = array(
    '#type' => 'fieldset',
    '#title' => t('Create Site'),
  );

  // Define the fieldset
  $form['createsite']['message'] = array(
    '#type' => 'markup',
    '#value' => t('<strong style="color: #f00;">Warning</strong>: This section is currently not working. There seems to be a permission problem with the script.'),
  );

  // Define our site name
  $form['createsite']['sitename'] = array(
    '#type' => 'textfield',
    '#title' => t('Site Name'),
    '#description' => t('Enter the name of the site. This is usually the URL "<em>sitename</em>.osu.edu" and will also be the database name. Please note that database names will have hyphens stripped out and be proceeded by a indicator for the environment they represent. So, d_<em>sitename</em> would be the development database name.'),
    '#required' => TRUE,
  );

  // Define our site title
  $form['createsite']['sitetitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Site Title'),
    '#description' => t('Please note that this feature is experimental. If you encounter errors please leave this field blank and the title will default to the site name given above. This inserts the site name with ascii space characters (&amp;#32;) which you may wish to replace before site launch.'),
    '#required' => FALSE,
  );

  // Define our site type
  $form['createsite']['sitetype'] = array(
    '#type' => 'select',
    '#title' => t('Select Site Type'),
    '#options' => $sitetype_options,
    '#description' => t("Choose the type of site you would like to create. Custom Sites are empty drupal sites. Standard Sites have the Standard Site theme and functionality enabled and are copied from the http://standarddemo-d.asc.ohio-state.edu environment."),
    '#required' => TRUE,
  );

  // Define our global variable
  $form['createsite']['submit'] = array(
    '#type' => 'submit',
    '#title' => t('Create Site'),
    '#value' => t('Create Site'),
  );

  // Return the form to system settings
  return $form;
} // function asc_sitemanager_create_site_form($form)

/**
 * The create site form - validate
 */
function asc_sitemanager_create_site_form_validate($form, &$form_state) {
  // Store the sitename and reformat it
  $sitename = $form_state['values']['sitename'];
  $sitestring = trim('<a href="http://' . $sitename . '-s.asc.ohio-state.edu/user/dev" title="Visit the ' . $sitename . ' staging site">http://' . $sitename . '-s.asc.ohio-state.edu/user/dev</a>');

  // Get the list of staging sites
  $stag_site_list_raw = asc_sitemanager_get_sites('stag');
  $stag_site_list = str_replace('<br />', ' ', $stag_site_list_raw);
  // Search the site list for our reformatted site name
  if (stristr(trim($stag_site_list), $sitestring) == TRUE) {
    form_set_error('', t('I\'m sorry, a site named ' . $sitename . ' already exists.'));
  }

} // function asc_sitemanager_create_site_form_validate($form, &$form_state)

/**
 * The create site form - submit handler
 */
function asc_sitemanager_create_site_form_submit($form, &$form_state) {
  // Get the environment selected
  $sitename = $form_state['values']['sitename'];
  $sitetitle = $form_state['values']['sitetitle'];
  $sitetype = $form_state['values']['sitetype'];

  if ($sitetype == '1') {
    $sitetype_name = "Standard Site";
  }
  else {
    $sitetype_name = "Custom Site";
  }

  // TODO: Script call to create site goes here
  //$output = asc_sitemanager_create_site($sitename, $sitetitle, $sitetype);
  $output = 'This is not working...see comment on main form.';


  // Display a confirmation message
  drupal_set_message(t('The "' . $sitetype_name . '" site "' . $sitename . '" with the title "' . $sitetitle . '" has been created.<br /><br />' . $output));
} // function asc_sitemanager_create_site_form_submit($form, &$form_state)