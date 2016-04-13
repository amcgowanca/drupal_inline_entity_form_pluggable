<?php
/**
 * @file
 * InlineEntityFormPluggableControllerPluginInterface.inc
 */

/**
 * Interface for describing Inline Entity Form controller Plugins.
 */
interface InlineEntityFormPluggableControllerPluginInterface {
  /**
   * InlineEntityFormPluggableControllerPluginInterface constructor.
   *
   * @param string $entity_type
   *   The entity type.
   */
  public function __construct($entity_type);

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
  public function preEntitySave($entity, $parent_entity, $parent_entity_type, &$needs_save);

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
  public function postEntitySave($entity, $parent_entity, $parent_entity_type, $saved = FALSE);
}
