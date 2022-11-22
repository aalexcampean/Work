<?php
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
            if (isset($_POST['operation']) && !empty($_POST['operation'])) {
                if ($_POST['operation'] == "getAllFilesByFormat") {
                    if (isset($_POST['format'])) {
                        $this->getAllFilesByFormat($_POST['format']);
                        $response['status'] = 200;
                        $response['message'] = 'Success';
                        return $response;
                    }
                } else if ($_POST['operation'] == "getAllFilesByType") {
                    if (isset($_POST['type'])) {
                        $this->getAllFilesByType($_POST['type']);
                        $response['status'] = 200;
                        $response['message'] = 'Success';
                        return $response;
                    }
                } else if ($_POST['operation'] == 'getFileById') {
                    if (isset($_POST['id'])) {
                        $this->getFileById($_POST['id']);
                        $response['status'] = 200;
                        $response['message'] = 'Success';
                        return $response;
                    }
                } else if ($_POST['operation'] == 'addFile') {
                    if (isset($_POST['title']) && isset($_POST['author']) && isset($_POST['noPages']) && isset($_POST['type'])
                        && isset($_POST['format'])) {
                        return $this->addFile($_POST['title'], $_POST['author'], $_POST['noPages'], $_POST['type'], $_POST['format']);
                    }
                } else if ($_POST['operation'] == 'deleteFile') {
                    if (isset($_POST['id'])) {
                        return $this->deleteFile($_POST['id']);
                    }
                } else if ($_POST['operation'] == 'updateFile') {
                    if (isset($_POST['id']) && $_POST['title'] && isset($_POST['author']) && isset($_POST['noPages']) && isset($_POST['type'])
                        && isset($_POST['format'])) {
                        return $this->updateFile($_POST['id'], $_POST['title'], $_POST['author'], $_POST['noPages'], $_POST['type'], $_POST['format']);
                    }
                }
            }
        }
        $response['status'] = 400;
        $response['message'] = 'Invalid / data not found';
        return $response;
    }

    private function getAllFiles()
    {
        $table = '<table class="table">
      <thead>
        <tr>
          <th scope="col">ID</th>
          <th scope="col">Title</th>
          <th scope="col">Author</th>
          <th scope="col">Nr. Of Pages</th>
          <th scope="col">Type</th>
          <th scope="col">Format</th>
          <th scope="col">Modify</th>
        </tr>
      </thead>
      <tbody>';

        $result = $this->repository->getAll();
        $rowCount = 1;
        while ($row = $result->fetch_assoc()) {
            $table .= '<tr>
          <th scope="row">' . $rowCount . '</th>
          <td>' . $row['title'] . '</td>
          <td>' . $row['author'] . '</td>
          <td>' . $row['noPages'] . '</td>
          <td>' . $row['type'] . '</td>
          <td>' . $row['format'] . '</td>
          <td class="button-container">
          <button type="button" class="btn btn-primary custom-button2 full-with-button" onclick="populateModal(' . $row['id'] . ')">Update</button>
          <button type="button" class="btn btn-primary custom-button2 full-with-button" onclick="deleteFile(' . $row['id'] . ')">Delete</button>
          </td>
        </tr>';
            $rowCount += 1;
        }
        $table .= '</tbody></table>';
        echo $table;
    }

    private function getAllFilesByFormat($format)
    {
        $table = '<table class="table">
      <thead>
        <tr>
          <th scope="col">ID</th>
          <th scope="col">Title</th>
          <th scope="col">Author</th>
          <th scope="col">Nr. Of Pages</th>
          <th scope="col">Type</th>
          <th scope="col">Format</th>
          <th scope="col">Modify</th>
        </tr>
      </thead>
      <tbody>';

        if ($format == "ALL") {
            $result = $this->repository->getAll();
        } else {
            $result = $this->repository->getByFormat($format);
        }

        $rowCount = 1;
        while ($row = $result->fetch_assoc()) {
            $table .= '<tr>
          <th scope="row">' . $rowCount . '</th>
          <td>' . $row['title'] . '</td>
          <td>' . $row['author'] . '</td>
          <td>' . $row['noPages'] . '</td>
          <td>' . $row['type'] . '</td>
          <td>' . $row['format'] . '</td>
          <td class="button-container">
          <button type="button" class="btn btn-primary custom-button2 full-with-button" onclick="populateModal(' . $row['id'] . ')">Update</button>
          <button type="button" class="btn btn-primary custom-button2 full-with-button" onclick="deleteFile(' . $row['id'] . ')">Delete</button>
          </td>
        </tr>';
            $rowCount += 1;
        }
        $table .= '</tbody></table>';
        echo $table;
    }

    private function getAllFilesByType($type)
    {
        $table = '<table class="table">
      <thead>
        <tr>
          <th scope="col">ID</th>
          <th scope="col">Title</th>
          <th scope="col">Author</th>
          <th scope="col">Nr. Of Pages</th>
          <th scope="col">Type</th>
          <th scope="col">Format</th>
          <th scope="col">Modify</th>
        </tr>
      </thead>
      <tbody>';

        if ($type == "") {
            $result = $this->repository->getAll();
        } else {
            $result = $this->repository->getByType($type);
        }

        $rowCount = 1;
        while ($row = $result->fetch_assoc()) {
            $table .= '<tr>
          <th scope="row">' . $rowCount . '</th>
          <td>' . $row['title'] . '</td>
          <td>' . $row['author'] . '</td>
          <td>' . $row['noPages'] . '</td>
          <td>' . $row['type'] . '</td>
          <td>' . $row['format'] . '</td>
          <td class="button-container">
          <button type="button" class="btn btn-primary custom-button2 full-with-button" onclick="populateModal(' . $row['id'] . ')">Update</button>
          <button type="button" class="btn btn-primary custom-button2 full-with-button" onclick="deleteFile(' . $row['id'] . ')">Delete</button>
          </td>
        </tr>';
            $rowCount += 1;
        }
        $table .= '</tbody></table>';
        echo $table;
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