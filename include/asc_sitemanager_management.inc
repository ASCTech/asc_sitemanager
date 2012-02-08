<?php
// $Id$
/**
 * @file
 * The site management functions
 */

/**
 * The site management pages
 *
 * This function acts as a controller for the management page.
 *
 */
function asc_sitemanager_management($action = 0) {
  // Initialize the page content variable
  $output = '';

  // Display the section title
  $output .= 'Site Management';
  // Display the main menu
  $output .= $GLOBALS['mainmenu'];

  // Display the appropriate page based on the requested action
  switch ($action) {
    case 0:
      // Display the default page
      $output .= '
        <hr />
        <ul>
          <li><a href="' . base_path() . 'sitemanager/2/1" title="Visit the Create Site page">Create Site</a></li>
          <li><a href="' . base_path() . 'sitemanager/2/2" title="Visit the Get Sites page">Get Sites</a></li>
          <li><a href="' . base_path() . 'sitemanager/2/3" title="Visit the Move Sites page">Move Sites</a></li>
          <li><a href="' . base_path() . 'sitemanager/2/4" title="Visit the permissions page">Set Permissions</a></li>
        </ul>
        <hr />
      ';
      break;
    case 1:
      // Display the create site page
      $output .= create_site_page();
      break;
    case 2:
      // Display the get sites page
      $output .= get_sites_page();
      break;
    case 3:
      // Display the move sites page
      $output .= move_sites_page();
      break;
    case 4:
      // Display the permission page
      $output .= permission_page();
      break;
  }

  // Return the page content
  return $output;
} // function asc_sitemanager_management()