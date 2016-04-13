<?php
/**
 * @file
 * InlineEntityFormPluggableControllerPlugin.inc
 */

/**
 * Base class for Inline Entity Form Controller plugins.
 *
 * @see InlineEntityFormPluggableControllerPluginInterface.
 */
abstract class InlineEntityFormPluggableControllerPlugin implements InlineEntityFormPluggableControllerPluginInterface {
  /**
   * The entity type in which operations will be performed on.
   *
   * @var string
   */
  protected $entity_type = NULL;

  /**
   * InlineEntityFormPluggableControllerPlugin constructor.
   *
   * @param string $entity_type
   *   The entity type (e.g. node) for which operations will be performed on.
   */
  public function __construct($entity_type) {
    $this->entity_type = $entity_type;
  }

  /**
   * Returns the entity type.
   *
   * @return string
   *   The entity type.
   */
  final public function getEntityType() {
    return $this->entity_type;
  }

  /**
   * Perform operations prior to the $entity object being saved.
   *
   * @param object $entity
   *   The entity object about to be saved.
   * @param object $parent_entity
   *   The parent entity object which references $entity.
   * @param string $parent_entity_type
   *   The parent entity type.
   * @param boolean $needs_save
   *   A boolean indicating whether or not the $entity should be or needs to be
   *   saved. Value is passed by reference to allow for alterations to occur.
   *   However, if TRUE, changing to FALSE is not recommended and only should
   *   FALSE values be changed to TRUE should changes occur to $entity to force
   *   it to be saved via entity_save().
   */
  public function preEntitySave($entity, $parent_entity, $parent_entity_type, &$needs_save) {
    // Empty implementation.
  }

  /**
   * Perform operations after the $entity object is saved.
   *
   * @param object $entity
   *   The entity object about that was saved (or wasn't, if $needs_save in the
   *   preEntitySave() function was changed from TRUE to FALSE).
   * @param object $parent_entity
   *   The parent entity object which references $entity.
   * @param string $parent_entity_type
   *   The parent entity type.
   * @param boolean $saved
   *   A boolean indicating whether the entity was actually saved.
   */
  public function postEntitySave($entity, $parent_entity, $parent_entity_type, $saved = FALSE) {
    // Empty implementation.
  }
}