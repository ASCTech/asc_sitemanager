<?php
// $Id$
/**
 * @file
 * The main site management functions
 */

// Define the menu to be displayed at the top of all pages
$GLOBALS['mainmenu'] = '
  <ul>
    <li><a href="' . base_path() . 'sitemanager/1" title="Visit the ASC Site Manager main menu">Home</a></li>
    <li><a href="' . base_path() . 'sitemanager/2" title="Visit the ASC Site Manager Main Section">Site Management</a></li>
    <li><a href="' . base_path() . 'sitemanager/3" title="Visit the ASC Site Manager Training Section">Training</a></li>
    <li><a href="' . base_path() . 'admin/settings/sitemanager" title="Visit the ASC Site Manager Administration Section">Module Administration</a></li>
  </ul>
';

// Includes for section functions
include('asc_sitemanager_admin.inc');
include('asc_sitemanager_management.inc');
include('asc_sitemanager_training.inc');
include('asc_sitemanager_scripts.inc');
include('asc_sitemanager_createsite.inc');
include('asc_sitemanager_getsites.inc');
include('asc_sitemanager_movesite.inc');
include('asc_sitemanager_permission.inc');

/**
 * The main controller function
 */
function asc_sitemanager_main($action = 1, $page = 0) {

  // Initialize the page content variable
  $output = '';

  // Display the appropriate page based on the requested action
  switch ($action) {
    case 1:
      // Display the main menu
      $output .= asc_sitemanager_mainmenu();
      break;
    case 2:
      // Display the site management pages
      $output .= asc_sitemanager_management($page);
      break;
    case 3:
      // Display the training pages
      $output .= asc_sitemanager_training($page);
      break;
    case 99:
      // Display the administration pages
      $output .= asc_sitemanager_admin();
      break;
    default:
      // Display the main menu
      $output .= asc_sitemanager_mainmenu();
      break;
  }

  // Return the page content
  return $output;
} // function asc_sitemanager_main($action = 1)

/**
 * The menu page
 */
function asc_sitemanager_mainmenu() {
  // Initialize the page content variable
  $output = '';

  $output .= $GLOBALS['mainmenu'];

  $output .= '
    <div class="asc-sitemanager-main">
      <h2>Welcome to the ASC Site Manager</h2>
      <p>
      From here administrators can create new sites, reset training sites, or make changes to this module. For this module to work the server
      hosting the scripts and the machine hosting the module must have an ssh key pair. No password is used or transmitted in the system. Ideally,
      this should be moved so that it can be executed from the dev server.
      </p>
      <p>
      <strong>Notes about this iteration<strong>: This was built to be transfered to the Casanova infrastructure. There are a few things (create site and move site) that
      currently do not work. All code is in place for these items and they should function as expected. All other functionality is already working as
      expected but will need to be tested on Casanova.
      </p>
    </div>
  ';

  // Return the page content
  return $output;
} // function asc_sitemanager_mainmenu()