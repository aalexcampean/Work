$(document).ready(getAllFiles);
$("#inputTypeFilter").on('input', getAllFilesByType);
$("#inputFormatFilter").on('change', getAllFilesByFormat);

function populateModal(id) {
    $('#hiddenFileId').val(id);

    $.ajax({
        url: 'http://127.0.0.1:8000/Server/Controller/Controller.php',
        type: 'POST',
        data: {
            operation: 'getFileById',
            id: id,
        },
        success: function (response) {
            console.log(response);
            var file = JSON.parse(response);

            $('#inputTitle').val(file.title);
            $('#inputAuthor').val(file.author);
            $('#inputNoPages').val(file.noPages);
            $('#inputType').val(file.type);
            // Setting the Format Form Select such that the correct option is selected
            const $select = document.querySelector('#inputFormat');
            const $options = Array.from($select.options);
            const optionToSelect = $options.find(item => item.text === file.format.toUpperCase());
            optionToSelect.selected = true;

            // Showing the modal
            $('#fileFormModal').modal('show')
        }
    })
}

function handleAddUpdateOperation() {
    if ($('#hiddenFileId').val() === "") {
        addFile()
    } else {
        updateFile();
    }
}

function getAllFiles() {
    $.ajax({
        url: 'http://127.0.0.1:8000/Server/Controller/Controller.php',
        type: 'GET',
        success: function (response) {
            if (response !== "0 results") {
                $('#file-table').empty();
                $('#file-table').html(response);
            } else {
                alert("No results");
            }
        }
    })
}

function getAllFilesByType() {
    let inputTypeFilter = $('#inputTypeFilter').val();

    $.ajax({
        url: 'http://127.0.0.1:8000/Server/Controller/Controller.php',
        type: 'POST',
        data: {
            operation: 'getAllFilesByType',
            type: inputTypeFilter
        },
        success: function (response) {
            if (response !== "0 results") {
                $('#file-table').empty();
                $('#file-table').html(response);
            } else {
                alert("No results");
            }
        }
    })
}

function getAllFilesByFormat() {
    let inputFormatFilter = $('#inputFormatFilter :selected').text();

    $.ajax({
        url: 'http://127.0.0.1:8000/Server/Controller/Controller.php',
        type: 'POST',
        data: {
            operation: 'getAllFilesByFormat',
            format: inputFormatFilter
        },
        success: function (response) {
            if (response !== "0 results") {
                $('#file-table').empty();
                $('#file-table').html(response);
            } else {
                alert("No results");
            }
        }
    })
}

function addFile() {
    let inputTitle = $('#inputTitle').val();
    let inputAuthor = $('#inputAuthor').val();
    let inputNoPages = $('#inputNoPages').val();
    let inputType = $('#inputType').val();
    let inputFormat = $('#inputFormat :selected').text();

    $.ajax({
        url: 'http://127.0.0.1:8000/Server/Controller/Controller.php',
        type: 'POST',
        data: {
            operation: 'addFile',
            title: inputTitle,
            author: inputAuthor,
            noPages: inputNoPages,
            type: inputType,
            format: inputFormat
        },
        success: function (response) {
            alert(response);
            getAllFiles();
            modalCleanUp();
        }
    })
}

function updateFile() {
    let inputId = $('#hiddenFileId').val();
    let inputTitle = $('#inputTitle').val();
    let inputAuthor = $('#inputAuthor').val();
    let inputNoPages = $('#inputNoPages').val();
    let inputType = $('#inputType').val();
    let inputFormat = $('#inputFormat :selected').text();

    $.ajax({
        url: 'http://127.0.0.1:8000/Server/Controller/Controller.php',
        type: 'POST',
        data: {
            operation: 'updateFile',
            id: inputId,
            title: inputTitle,
            author: inputAuthor,
            noPages: inputNoPages,
            type: inputType,
            format: inputFormat
        },
        success: function (response) {
            alert(response);
            getAllFiles();
            modalCleanUp();
        }
    })
}

function deleteFile(id) {
    $.ajax({
        url: 'http://127.0.0.1:8000/Server/Controller/Controller.php',
        type: 'POST',
        data: {
            operation: 'deleteFile',
            id: id
        },
        success: function (response) {
            alert(response);
            getAllFiles();
        }
    })
}

function modalCleanUp() {
    $('#hiddenFileId').val('');
    $('#inputTitle').val('');
    $('#inputAuthor').val('');
    $('#inputNoPages').val('');
    $('#inputType').val('');
    // Setting the Format Form Select such that the default one
    const $select = document.querySelector('#inputFormat');
    const $options = Array.from($select.options);
    const optionToSelect = $options.find(item => item.text === "PDF");
    optionToSelect.selected = true;
}
