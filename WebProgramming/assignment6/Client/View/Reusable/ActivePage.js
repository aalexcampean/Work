document.addEventListener("DOMContentLoaded", function(){
    //dom is fully loaded, but maybe waiting on images & css files

    // Get current page URL
    var url = window.location.href;

    // remove # from URL
    url = url.substring(0, (url.indexOf("#") == -1) ? url.length : url.indexOf("#"));

    // remove parameters from URL
    url = url.substring(0, (url.indexOf("?") == -1) ? url.length : url.indexOf("?"));

    // select file name
    url = url.substr(url.lastIndexOf("/") + 1);

    // If file name not avilable
    if (url == '') {
        url = 'index.html';
    }

    let customHeader = document.querySelector('custom-header').shadowRoot;
    let navigationItems = customHeader.querySelectorAll('ul li');

    navigationItems.forEach(function(item) {
        let aTag = item.querySelector('a')
        let href = aTag.getAttribute('href');

        // Check filename
        if (url == href) {
            // Add active class
            item.classList.add('active');
            aTag.style.color = '#0101fc'
        }
    });
});