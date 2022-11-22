<?php
require '../Model/DocumentDTO.php';

class Repository
{
    private $connection;

    private string $servername;
    private string $username;
    private string $password;
    private string $dbname;
    private int $port;

    /**
     * @param string $servername
     * @param string $username
     * @param string $password
     * @param string $dbname
     */
    public function __construct()
    {
        $this->servername = "127.0.0.1";
        $this->username = "alex";
        $this->password = "1234";
        $this->dbname = "DocumentManager";
        $this->port = 2019;
    }

    // Connect to Database
    public function connect()
    {
        $this->connection = new mysqli($this->servername, $this->username, $this->password, $this->dbname, $this->port);
        if ($this->connection->connect_error) {
            die("Connection failed: " . $this->connection->connect_error);
        }
    }

    // Disconnect from Database
    public function disconnect()
    {
        $this->connection->close();
    }

    // Show all Websites from the database
    public function getAllWebsites()
    {
        $this->connect();
        $sqlCommand = "SELECT * FROM Document";
        $result = $this->connection->query($sqlCommand);

        $this->disconnect();
        return $result;
    }

    // Show Document with given id from the database
    public function getDocumentsMatchingKeywords(array $keywords)
    {
        $this->connect();
        $sqlCommand = "SELECT * FROM Document WHERE id=" . $documentId;
        $result = $this->connection->query($sqlCommand);

        $this->disconnect();
        return $result;
    }

    // Show all Documents of a given type from the database
    public function getByType(string $documentType)
    {
        $this->connect();
        $sqlCommand = "SELECT * FROM Documents WHERE type='" . $documentType . "'";
        $result = $this->connection->query($sqlCommand);

        $this->disconnect();
        return $result;
    }

    // Show all Documents of a given format from the database
    public function getByFormat(string $documentFormat)
    {
        $this->connect();
        $sqlCommand = "SELECT * FROM Documents WHERE format='" . $documentFormat . "'";
        $result = $this->connection->query($sqlCommand);

        $this->disconnect();
        return $result;
    }
}