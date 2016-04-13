<?php
/**
 * @file
 * InlineEntityFormWorkbenchParentNodeMatch.inc
 */

/**
 * Workbench Moderation parent node status match.
 *
 * Matches the referenced entity to the parent node if the parent node has a
 * higher publishing status (e.g. if the entity is not published but the parent
 * entity is, the entity is moved to a published state).
 *
 * @see InlineEntityFormPluggableControllerPlugin
 */
class InlineEntityFormWorkbenchParentNodeMatch extends InlineEntityFormPluggableControllerPlugin {
  /**
   * {@inheritdoc}
   */
  public function preEntitySave($entity, $parent_entity, $parent_entity_type, &$entity_needs_save) {
    if ('node' == $parent_entity_type) {
      $needs_save = $this->upgradeNodeEntityStatus($entity, $parent_entity);
      if (!$entity_needs_save && $needs_save) {
        $entity_needs_save = TRUE;
      }
    }
  }

  /**
   * Upgrades a child node entity to parent's status if the parent is Published.
   *
   * @param object $entity
   *   The child node entity to upgrade.
   * @param object $parent_entity
   *   The parent node to the child to match statuses.
   *
   * @return bool
   *   Returns a boolean indicating if the $entity node needs saving.
   */
  public function upgradeNodeEntityStatus($entity, $parent_entity) {
    $wrapper = entity_metadata_wrapper('node', $entity);
    inline_entity_form_workbench_node_status_set_processed_state($parent_entity, TRUE);
    if (workbench_moderation_node_type_moderated($wrapper->getBundle())) {
      if (NODE_PUBLISHED != $wrapper->status->value()) {
        return $this->_matchWorkbenchModerationStates($entity, $parent_entity);
      }
    }
    else {
      return $this->_matchParentWorkbenchModerationToStatus($entity, $parent_entity);
    }
    return FALSE;
  }

  protected function _matchWorkbenchModerationStates(&$entity, &$parent_entity) {
    if (isset($parent_entity->type) && workbench_moderation_node_type_moderated($parent_entity->type)) {
      if (isset($parent_entity->workbench_moderation_state_current) && isset($parent_entity->workbench_moderation_state_new)) {
        $published_state = workbench_moderation_state_published();
        if ($published_state == $parent_entity->workbench_moderation_state_new) {
          $entity->workbench_moderation_state_new = $published_state;
          if (!isset($entity->workbench_moderation_state_current)) {
            $entity->workbench_moderation_state_current = workbench_moderation_state_none();
          }
          return TRUE;
        }
      }
      elseif (isset($parent_entity->workbench_moderation) && isset($parent_entity->workbench_moderation['current'])) {
        $workbench_moderation_current = $parent_entity->workbench_moderation['current'];
        if (isset($workbench_moderation_current->from_state) && isset($workbench_moderation_current->state)) {
          $published_state = workbench_moderation_state_published();
          if ($published_state == $workbench_moderation_current->state) {
            $entity->workbench_moderation_state_new = $published_state;
            return TRUE;
          }
        }
      }
    }
    else {
      return $this->_matchParentNodeStatusToWorkbenchModeration($entity, $parent_entity);
    }
    return FALSE;
  }

  protected function _matchParentWorkbenchModerationToStatus(&$entity, &$parent_entity) {
    if (isset($parent_entity->type) && workbench_moderation_node_type_moderated($parent_entity->type)) {
      if (isset($parent_entity->workbench_moderation_state_current) && isset($parent_entity->workbench_moderation_state_new)) {
        $published_state = workbench_moderation_state_published();
        if ($published_state == $parent_entity->workbench_moderation_state_new && NODE_NOT_PUBLISHED == $entity->status) {
          $entity->status = NODE_PUBLISHED;
          return TRUE;
        }
      }
      elseif (isset($parent_entity->workbench_moderation) && isset($parent_entity->workbench_moderation['current'])) {
        $workbench_moderation_current = $parent_entity->workbench_moderation['current'];
        if (isset($workbench_moderation_current->from_state) && isset($workbench_moderation_current->state)) {
          $published_state = workbench_moderation_state_published();
          if ($published_state == $workbench_moderation_current->state) {
            $entity->status = NODE_PUBLISHED;
            return TRUE;
          }
        }
      }
    }
    else {
      return $this->_matchNodeStatuses($entity, $parent_entity);
    }
    return FALSE;
  }

  protected function _matchParentNodeStatusToWorkbenchModeration(&$entity, &$parent_entity) {
    if (isset($parent_entity->status)) {
      if (NODE_PUBLISHED == $parent_entity->status) {
        if (!isset($entity->workbench_moderation_state_current)) {
          $entity->workbench_moderation_state_current = workbench_moderation_state_none();
        }
        $entity->workbench_moderation_state_new = workbench_moderation_state_published();
        return TRUE;
      }
    }
  }

  protected function _matchNodeStatuses(&$entity, &$parent_entity) {
    if ($entity->status != $parent_entity->status && NODE_PUBLISHED != $entity->status) {
      if (NODE_PUBLISHED == $parent_entity->status) {
        $entity->status = NODE_PUBLISHED;
        return TRUE;
      }
    }
    return FALSE;
  }
}
