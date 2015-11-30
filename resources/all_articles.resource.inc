<?php

/**
 * Return node data for article contents.
 */
function _site_ws_all_articles($nid) {
  /*return array(
    "hello" => 'test',
    "goodbye" => "forever",
    "php_cms" => array(
      "wordpress",
      "joomla",
      "drupal",
    )
  );*/

  $data = array();
  if (isset($nid) && is_numeric($nid)) {
    $query = db_select('node', 'n');
    $query->leftJoin('field_data_body', 'b', 'n.nid = b.entity_id');
    $query->leftJoin('field_data_field_article_image', 'im', 'n.nid = im.entity_id');
    $query->leftJoin('field_data_field_article_attachments', 'a', 'n.nid = a.entity_id');

    $article = $query->fields('n')
      ->fields('b', array('body_value'))
      ->fields('im', array('field_article_image_fid'))
      ->fields('a', array('field_article_attachments_fid'))
      ->condition('n.type', 'article', '=')
      ->condition('n.nid', $nid, '=')
      ->condition('n.status', 0, '>')
      ->execute();
    while($result = $article->fetchAssoc()) {
      $result['url'] = '/'.drupal_get_path_alias('node/'.$result['nid']); // add url.
      $result['created'] = date ('Y-m-d', $result['created']); // format date.
      $data[] = $result;
    }
    return $data;
  }

  $query = db_select('node', 'n');
  $query->leftJoin('field_data_body', 'b', 'n.nid = b.entity_id');
  $query->leftJoin('field_data_field_article_image', 'im', 'n.nid = im.entity_id');
  $query->leftJoin('field_data_field_article_attachments', 'a', 'n.nid = a.entity_id');

  $articles = $query->fields('n')
    ->fields('b', array('body_value'))
    ->fields('im', array('field_article_image_fid'))
    ->fields('a', array('field_article_attachments_fid'))
    ->condition('n.type', 'article', '=')
    ->condition('n.status', 0, '>')
    ->execute();

  while($result = $articles->fetchAssoc()) {
    $result['url'] = '/'.drupal_get_path_alias('node/'.$result['nid']); // add url.
    $result['created'] = date ('Y-m-d', $result['created']); // format date.
    $data[] = $result;
  }

  return $data;
}