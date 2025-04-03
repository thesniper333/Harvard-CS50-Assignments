// JavaScript to handle the blur effect and message removal
window.addEventListener('load', () => {
    const blurOverlay = document.getElementById('blurOverlay');

    // Wait for 3 seconds, then remove the overlay
    setTimeout(() => {
        blurOverlay.style.transition = 'opacity 0.5s ease';
        blurOverlay.style.opacity = '0';

        // Remove the overlay from the DOM after transition
        setTimeout(() => {
            blurOverlay.style.display = 'none';
        }, 500);
    }, 3000);
});
