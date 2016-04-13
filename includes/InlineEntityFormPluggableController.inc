<?php
/**
 * @file
 * InlineEntityFormPluggableController.inc
 */

/**
 * Derived from EntityInlineEntityFormController to invoke plugin methods.
 *
 * @see EntityInlineEntityFormController
 */
class InlineEntityFormPluggableController extends EntityInlineEntityFormController {
  /**
   * An array of plugins for this entity type.
   *
   * @var array
   */
  protected $plugins = array();

  /**
   * InlineEntityFormPluggableController constructor.
   *
   * @param string $entity_type
   *   The entity type.
   *
   * @param array $settings
   *   An array of settings for this controller instance.
   */
  public function __construct($entity_type, array $settings) {
    parent::__construct($entity_type, $settings);
    $this->plugins = inline_entity_form_pluggable_get_plugins($this);
  }

  /**
   * {@inheritdoc}
   */
  public function save($entity, $context) {
    $entity_needs_saved = $context['item']['needs_save'];
    foreach ($this->plugins as $plugin_name => $plugin) {
      $plugin['plugin']->preEntitySave($entity, $context['parent_entity'], $context['parent_entity_type'], $entity_needs_saved);
    }

    $entity_saved = FALSE;
    if ($entity_needs_saved) {
      parent::save($entity, $context);
      $entity_saved = TRUE;
    }

    foreach ($this->plugins as $plugin_name => $plugin) {
      $plugin['plugin']->postEntitySave($entity, $context['parent_entity'], $context['parent_entity_type'], $entity_saved);
    }
  }

  /**
   * {@inheritdoc}
   */
  public function delete($ids, $context) {
    parent::delete($ids, $context);
  }
}
