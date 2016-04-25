<?php
/**
 * @file
 * Page callback functions.
 */

/**
 * Function to update data for quicktab in quicktabs_remember table.
 */
function _quicktabs_remember_update_quicktab_location($quicktab_name, $tab_number = 0) {
  global $user;
  $quicktab = quicktabs_load($quicktab_name);
  if (isset($quicktab)) {
    $quicktabs_remembered_data = _quicktabs_remember_get_quicktabs();
    $quicktabs_remembered = array_filter($quicktabs_remembered_data);
    if (in_array($quicktab->machine_name, array_keys($quicktabs_remembered))) {
      if (in_array($tab_number, array_keys($quicktab->tabs))) {
        try {
          db_merge('quicktabs_remember')
            ->key(array(
              'uid' => $user->uid,
              'quicktab_machine_name' => $quicktab_name,
            ))
            ->fields(array(
              'last_tab' => $tab_number,
            ))
            ->execute();
          return drupal_json_output(array('status' => 'success'));
        }
        catch (Exception $e) {
          watchdog('quicktabs_remember', $e->getMessage());
          return drupal_json_output(array('status' => 'failed'));
        }
      }
      else {
        return drupal_json_output(array('status' => 'access_denied'));
      }
    }
    else {
      return drupal_json_output(array('status' => 'access_denied'));
    }
  }
  else {
    return drupal_json_output(array('status' => 'access_denied'));
  }
}
