

const first_button = document.getElementById('change-background-button');
const second_button = document.getElementById('change-links-button');
const background_images = ["photo1.jpg", "photo2.jpg", "photo3.jpg", "photo4.jpg", "photo5.jpg"]
let index = 0
let color_changed = false;

first_button.addEventListener('click', function onClick(event) {
    if (index === 4) {
        index = 0;
    }
    else  {
        index += 1;
    }

    document.body.style.backgroundImage = `url('${background_images[index]}')`;
});

second_button.addEventListener('click', function onClick(event) {
    const links = document.getElementsByTagName("a");
    if (color_changed) {
        for(let i = 0; i < links.length; i++) {
            if(links[i].href) {
                links[i].style.color = "#FFF";
            }
        }
        color_changed = false;
    }
    else {
        for(let i = 0; i < links.length; i++) {
            if(links[i].href) {
                links[i].style.color = "#000";
            }
        }
        color_changed = true;
    }
});