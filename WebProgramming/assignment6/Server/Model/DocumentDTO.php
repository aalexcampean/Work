<?php
class DocumentDTO
{
    private $id;
    private $title;
    private $author;
    private $numberOfPages;
    private $type;
    private $format;

    /**
     * @param $id
     * @param $title
     * @param $author
     * @param $numberOfPages
     * @param $type
     * @param $format
     */
    public function __construct($title, $author, $numberOfPages, $type, $format)
    {
        $this->title = $title;
        $this->author = $author;
        $this->numberOfPages = $numberOfPages;
        $this->type = $type;
        $this->format = $format;
    }

    // Id getter/setter
    public function getId()
    {
        return $this->id;
    }

    public function setId($id): void
    {
        $this->id = $id;
    }

    // Title getter/setter
    public function getTitle()
    {
        return $this->title;
    }

    public function setTitle($title): void
    {
        $this->title = $title;
    }

    // Author getter/setter
    public function getAuthor()
    {
        return $this->author;
    }

    public function setAuthor($author): void
    {
        $this->author = $author;
    }

    // Number of Pages getter/setter
    public function getNumberOfPages()
    {
        return $this->numberOfPages;
    }

    public function setNumberOfPages($numberOfPages): void
    {
        $this->numberOfPages = $numberOfPages;
    }

    // Type getter/setter
    public function getType()
    {
        return $this->type;
    }

    public function setType($type): void
    {
        $this->type = $type;
    }

    // Format getter/setter
    public function getFormat()
    {
        return $this->format;
    }

    public function setFormat($format): void
    {
        $this->format = $format;
    }
}