<!doctype html>
<html lang="en">
<head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Document Manger</title>

    <!-- Bootstrap CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom CSS -->
    <link rel="stylesheet" href="Styling/CommonStyling.css">
</head>

<body>
<div class="modal fade" id="fileFormModal" tabindex="-1" aria-labelledby="exampleModalLabel" aria-hidden="true">
    <div class="modal-dialog modal-dialog-centered">
        <div class="modal-content">
            <div class="modal-header">
                <h5 class="modal-title" id="exampleModalLabel">Document information</h5>
                <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"
                        onclick="modalCleanUp()"></button>
            </div>
            <div class="modal-body">
                <form method="post">
                    <input type="hidden" id="hiddenFileId">
                    <div class="row form-floating mb-3">
                        <textarea class="form-control" placeholder="Title" id="inputTitle" required></textarea>
                        <label for="inputTitle">Title</label>
                    </div>

                    <div class="row form-floating mb-3">
                        <textarea class="form-control" placeholder="Author" id="inputAuthor" required></textarea>
                        <label for="inputAuthor">Author</label>
                    </div>

                    <div class="row form-floating mb-3">
                        <div class="col form-floating mb-3">
                            <textarea class="form-control" placeholder="Author" id="inputNoPages"
                                      required></textarea>
                            <label for="inputNoPages">Number Of Pages</label>
                        </div>

                        <div class="col form-floating mb-3">
                            <textarea class="form-control" placeholder="Author" id="inputType"
                                      required></textarea>
                            <label for="inputType">Type</label>
                        </div>

                        <div class="col form-floating mb-3">
                            <select class="form-select" id="inputFormat" aria-label="Floating label select example">
                                <option selected>PDF</option>
                                <option value="1">JPG</option>
                                <option value="2">PNG</option>
                            </select>
                            <label for="inputFormat">Format</label>
                        </div>
                    </div>

                    <div class="row form-floating mb-3">
                        <button type="submit" class="btn btn-primary custom-button" data-bs-dismiss="modal"
                                onclick="handleAddUpdateOperation()">
                            Submit
                        </button>
                    </div>
                </form>
            </div>
        </div>
    </div>
</div>

<custom-header></custom-header>
<div class="container">
    <div class="row marg-20">
        <div class="col">
            <h1>Your Documents</h1>
        </div>
    </div>
    <div class="row marg-20">
        <div class="col button-container">
            <button type="button" class="btn btn-primary custom-button full-with-button" data-bs-toggle="modal" data-bs-target="#fileFormModal">
                Add New Document
            </button>
        </div>
        <div class="col form-floating mb-3">
            <textarea class="form-control" placeholder="Author" id="inputTypeFilter"
                      required></textarea>
            <label for="inputTypeFilter">Filter by Type</label>
        </div>
        <div class="col form-floating mb-3">
            <select class="form-select" id="inputFormatFilter" aria-label="Floating label select example">
                <option selected>ALL</option>
                <option value="1">PDF</option>
                <option value="2">JPG</option>
                <option value="3">PNG</option>
            </select>
            <label for="inputFormatFilter">Filter by Format</label>
        </div>
    </div>
    <div class="row marg-20">
        <div class="col">
            <div id="file-table"></div>
        </div>
    </div>
</div>

<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.10.2/dist/umd/popper.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.min.js"></script>

<script src="Reusable/Header.js" type="text/javascript" defer></script>
<script src="Reusable/ActivePage.js" type="text/javascript" defer></script>
<script src="../Controller/Controller.js" type="text/javascript" defer></script>
</body>
</html>