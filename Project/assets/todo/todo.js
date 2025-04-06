// Load tasks from local storage when the page loads
document.addEventListener("DOMContentLoaded", loadTasks);
        
function addTask() {
    let taskInput = document.getElementById("taskInput");
    let taskText = taskInput.value.trim();
    if (taskText === "") return; // Prevent adding empty tasks
    
    let taskList = document.getElementById("taskList");
    let li = document.createElement("li");
    let taskNumber = taskList.children.length + 1; // Assign a number to the task
    
    // Add task text along with a remove button
    li.innerHTML = `<span>${taskNumber}. ${taskText}</span> <button class="remove-btn" onclick="removeTask(this)">Remove</button>`;
    taskList.appendChild(li);
    
    saveTasks(); // Save tasks to local storage
    taskInput.value = ""; // Clear input field
}

function removeTask(button) {
    let li = button.parentElement;
    li.remove(); // Remove the clicked task
    updateTaskNumbers(); // Update numbering after removal
    saveTasks(); // Save updated list to local storage
}

function saveTasks() {
    let tasks = [];
    document.querySelectorAll("#taskList li span").forEach(span => {
        // Store tasks without their number prefixes
        tasks.push(span.textContent.trim().replace(/^\d+\.\s*/, ""));
    });
    localStorage.setItem("tasks", JSON.stringify(tasks)); // Save tasks in local storage
}

function loadTasks() {
    let tasks = JSON.parse(localStorage.getItem("tasks")) || [];
    let taskList = document.getElementById("taskList");
    taskList.innerHTML = ""; // Clear existing tasks before loading
    tasks.forEach((task, index) => {
        let li = document.createElement("li");
        li.innerHTML = `<span>${index + 1}. ${task}</span> <button class="remove-btn" onclick="removeTask(this)">Remove</button>`;
        taskList.appendChild(li);
    });
}

function updateTaskNumbers() {
    let taskList = document.getElementById("taskList");
    // Reassign numbers to tasks after one is removed
    Array.from(taskList.children).forEach((li, index) => {
        let text = li.querySelector("span").textContent.trim().replace(/^\d+\.\s*/, ""); // Remove old number
        li.querySelector("span").textContent = `${index + 1}. ${text}`; // Update numbering
    });
}
document.getElementById("add-task").addEventListener('click',addTask)