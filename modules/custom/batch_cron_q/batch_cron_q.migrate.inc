<?php

use Drupal\node\Entity\Node;

function batch_cron_q_migrate($nids, $type, $options = array(), &$context) {

  $message = 'Deleting Node...';
  $results = array();
  foreach ($nids as $nid) {
    $node = Node::load($nid);
    $results[] = $node->delete();
  }
  $context['message'] = $message;
  $context['results'] = $results;

  // Do heavy coding here...
  $message = 'Ready spaghetti...';

  switch ($type) {
    case 'courses':
      $message = 'migrating courses...';
      $context['results'][] = $options;
      break;
    default:
      $message = 'migrating somethine else...';
      break;
  }
}

function batch_cron_q_migrate_finished_callback($success, $results, $operations) {
 // The 'success' parameter means no fatal PHP errors were detected. All
  // other error management should be handled using 'results'.
  if ($success) {
    $message = \Drupal::translation()->formatPlural(
        count($results), 'One post processed.', '@count posts processed.'
    );
  }
  else {
    $message = t('Finished with an error.');
  }
  drupal_set_message($message);
  //$_SESSION['disc_migrate_batch_results'] = $results;
}

