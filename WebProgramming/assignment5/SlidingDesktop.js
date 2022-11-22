$(document).ready(function () {
    function toBottom() {
        $("html, body").scrollTop($(document).height());
    }
    toBottom()


    $(".window").bind("click", function () {
        if($(window).scrollTop() === 0) {
            toBottom()
        }
        else {
            var y = $(window).scrollTop();
            $('html, body').animate({ scrollTop: y - 1200 });
        }
    });
});
