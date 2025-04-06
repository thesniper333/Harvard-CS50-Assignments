const bgUpload = document.getElementById("bg-upload");

// ✅ Load stored background on page load
document.addEventListener("DOMContentLoaded", () => {
    const storedBg = localStorage.getItem("backgroundImage");
    if (storedBg) {
        document.body.style.background = `url(${storedBg}) no-repeat center center/cover`;
    }
});

// ✅ Handle Image Upload
bgUpload.addEventListener("change", function (event) {
    const file = event.target.files[0];
    if (file) {
        const reader = new FileReader();
        reader.onload = function (e) {
            document.body.style.background = `url(${e.target.result}) no-repeat center center/cover`;
            localStorage.setItem("backgroundImage", e.target.result); // Save in localStorage
        };
        reader.readAsDataURL(file);
    }
});

