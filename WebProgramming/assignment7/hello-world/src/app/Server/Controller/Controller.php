<?php
// enable CORS - required for Angular UI
header('Access-Control-Allow-Origin: *');
header('Content-type: application/json');
require '../Repository/Repository.php';

class Controller
{
  private $repository;

  public function __construct()
  {
    $this->repository = new Repository();
  }

  public function service()
  {
    if ($_SERVER['REQUEST_METHOD'] == 'GET') {
      $this->getAllFiles();
    } else {
      $json = file_get_contents('php://input');
      $array = json_decode($json);
      if ($array->operation == 'getAllFilesByType') {
        $this->getAllFilesByType($array->type);
      } else if ($array->operation == 'getAllFilesByFormat') {
        $this->getAllFilesByFormat($array->format);
      } else if ($array->operation == 'getFileById') {
        $this->getFileById($array->id);
      } else if ($array->operation == "addFile") {
        $this->addFile($array->title, $array->author, $array->noPages, $array->type, $array->format);
      } else if ($array->operation == "deleteFile") {
        $this->deleteFile($array->id);
      } else {
        $this->updateFile($array->id, $array->title, $array->author, $array->noPages, $array->type, $array->format);
      }
    }
  }


  private function getAllFiles()
  {
    $result = $this->repository->getAll();
    if ($result->num_rows > 0) {
      $array = array();

      while ($row = $result->fetch_assoc()) {
        $obj = array(
          'id' => $row['id'],
          'title' => $row['title'],
          'author' => $row['author'],
          'noOfPages' => $row['noPages'],
          'type' => $row['type'],
          'format' => $row['format'],
        );
        array_push($array, $obj);
      }
      echo json_encode($array);
    } else {
      echo "0 results";
    }
  }

  private function getAllFilesByFormat($format)
  {
    if ($format == "ALL") {
      $result = $this->repository->getAll();
    } else {
      $result = $this->repository->getByFormat($format);
    }
    if ($result->num_rows > 0) {
      $array = array();

      while ($row = $result->fetch_assoc()) {
        $obj = array(
          'id' => $row['id'],
          'title' => $row['title'],
          'author' => $row['author'],
          'noOfPages' => $row['noPages'],
          'type' => $row['type'],
          'format' => $row['format'],
        );
        array_push($array, $obj);
      }
      echo json_encode($array);
    } else {
      echo "0 results";
    }
  }

  private function getAllFilesByType($type)
  {
    if ($type == "") {
      $result = $this->repository->getAll();
    } else {
      $result = $this->repository->getByType($type);
    }
    if ($result->num_rows > 0) {
      $array = array();

      while ($row = $result->fetch_assoc()) {
        $obj = array(
          'id' => $row['id'],
          'title' => $row['title'],
          'author' => $row['author'],
          'noOfPages' => $row['noPages'],
          'type' => $row['type'],
          'format' => $row['format'],
        );
        array_push($array, $obj);
      }
      echo json_encode($array);
    } else {
      echo "0 results";
    }
  }

  private function getFileById($id)
  {
    $result = $this->repository->getById($id);
    $response = array();

    while ($row = $result->fetch_assoc()) {
      $response = $row;
    }
    echo json_encode($response);
  }

  private function addFile($title, $author, $noPages, $type, $format)
  {
    echo $title, $author, $noPages, $type, $format;
    $document = new DocumentDTO($title, $author, $noPages, $type, $format);
    return $this->repository->add($document);
  }

  private function deleteFile($id)
  {
    return $this->repository->delete($id);
  }

  private function updateFile($id, $title, $author, $noPages, $type, $format)
  {
    $document = new DocumentDTO($title, $author, $noPages, $type, $format);
    $document->setId($id);
    return $this->repository->update($document);
  }
}

$controller = new Controller();
$controller->service();