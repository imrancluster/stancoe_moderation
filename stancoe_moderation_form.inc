<?php

/**
 * @file
 * py_moderation_form.inc
 */

/**
 * Page callback: Tonic diet plan configuration
 *
 * @see current_contacts_menu()
 */
function py_moderation_configuration($form, &$form_state) {

    $form['py_content_types'] = array(
        '#type' => 'checkboxes',
        '#options' => node_type_get_names(),
        '#title' => t('Select content types'),
        '#default_value' => variable_get('py_content_types'),
        '#description' => t('Please select necessary content types for manager\'s moderation.'),
    );

    $form['py_role'] = array(
        '#type' => 'radios',
        '#options' => user_roles(),
        '#title' => t('Select user roles'),
        '#default_value' => variable_get('py_role'),
        '#description' => t('Please select user role for content creator.'),
    );

    return system_settings_form($form);
}

/**
 * @param $user
 * @return string
 * @throws Exception
 */
function assign_stancoe_content_creators($user) {

    if (isset($_POST['asign'])) {
        assign_stancoe_content_creators_submit($user->uid, $_POST);
        drupal_set_message('Creators updated!');
    }

    $creators = [];
    foreach(get_all_stanceoe_content_creators() as $result) {
        $creators[] = $result;
    }

    $data = array(
        'creators' => $creators,
        'manager_creators' => get_stancoe_cretors_by_manager($user->uid),
    );

    return theme( 'assign_creators_form', array('data' => $data));
}

/**
 * @return DatabaseStatementInterface|null
 */
function get_all_stanceoe_content_creators() {
    $query = db_select('users_roles', 'ur');
    $query->fields('ur', ['uid']);
    $query->fields('u', ['name']);
    $query->leftJoin('role', 'r', 'r.rid = ur.rid');
    $query->leftJoin('users', 'u', 'u.uid = ur.uid');
    $query->condition('r.rid', variable_get('py_role'));
    $results = $query->execute();

    return $results;
}

/**
 * @param $uid
 * @param $data
 * @return bool|DatabaseStatementInterface|int
 * @throws Exception
 */
function assign_stancoe_content_creators_submit($uid, $data) {

    $query = db_select('stancoe_moderation_assign', 'pma');
    $query->fields('pma')
        ->condition('manager', $uid);
    $restult = $query->execute()->fetchAssoc();

    if (!empty($data['roles'])) {

        if ($restult) {

            $deleted = db_delete('stancoe_moderation_assign')
                    ->condition('manager', $uid)
                    ->execute();


            foreach($data['roles'] as $creator) {
                $inserted = db_insert('stancoe_moderation_assign')
                    ->fields(array(
                        'manager' => $uid,
                        'creators' => $creator,
                        'created' => REQUEST_TIME,
                        'updated' => REQUEST_TIME,
                    ))
                    ->execute();
            }

        } else {

            foreach($data['roles'] as $creator) {
                $inserted = db_insert('stancoe_moderation_assign')
                    ->fields(array(
                        'manager' => $uid,
                        'creators' => $creator,
                        'created' => REQUEST_TIME,
                        'updated' => REQUEST_TIME,
                    ))
                    ->execute();
            }
        }

        return $inserted;
    }

    return false;
}