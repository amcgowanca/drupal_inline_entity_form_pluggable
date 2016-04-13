<?php
/**
 * @file
 * inline_entity_form_workbench.inline_entity_form_pluggable.inc
 */

/**
 * Implements hook_inline_entity_form_pluggable_plugins().
 */
function inline_entity_form_workbench_inline_entity_form_pluggable_plugins() {
  return array(
    'parent_node_status_match' => array(
      'title' => t('Parent node status match'),
      'description' => t('Matches the parent node status to that of the child node.'),
      'class name' => 'InlineEntityFormWorkbenchParentNodeMatch',
      'file' => 'InlineEntityFormWorkbenchParentNodeMatch.inc',
      'file path' => drupal_get_path('module', 'inline_entity_form_workbench') . '/plugins',
      'entity types' => array('node'),
    )
  );
}
