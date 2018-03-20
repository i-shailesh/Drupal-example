<?php

/**
 * @file
 * Contains \Drupal\batch_cron_q\Controller\BatchCronQueueController.
 */

namespace Drupal\batch_cron_q\Controller;

class BatchCronQueueController {
  public function content() {

     $nids = \Drupal::entityQuery('node')
    ->condition('type', 'article')
    ->sort('created', 'ASC')
    ->execute();
    // batch process    
    $batch = array(
      'title' => t('Exporting'),
      'operations' => array(
        array('batch_cron_q_migrate', array($nids,'courses', array('foo' => 'bar'))),
      ),
      'finished' => 'batch_cron_q_migrate_finished_callback',
      'file' => drupal_get_path('module', 'batch_cron_q') . '/batch_cron_q.migrate.inc',
    );

    batch_set($batch);
    return batch_process('user');
  }
}
