// ====================
// THEME TOGGLE
// ====================
const toggle = document.getElementById("themeToggle");
const html = document.documentElement;

// Apply saved theme on load
const savedTheme = localStorage.getItem("theme") || "light";
html.setAttribute("data-theme", savedTheme);

// Toggle theme on button click
toggle.addEventListener("click", () => {
  const current = html.getAttribute("data-theme");
  const newTheme = current === "light" ? "dark" : "light";
  html.setAttribute("data-theme", newTheme);
  localStorage.setItem("theme", newTheme);
});

// ====================
// DATE & TIME DISPLAY
// ====================
function updateTime() {
  const now = new Date();
  const formatted = now.toLocaleString('en-GB', {
    day: "2-digit",
    month: "2-digit",
    year: "numeric",
    hour: "2-digit",
    minute: "2-digit",
    second: "2-digit",
    hour12: true
  });
  const datetimeElement = document.getElementById("datetime");
  if (datetimeElement) {
    datetimeElement.textContent = formatted;
  }
}
setInterval(updateTime, 1000);
updateTime();

// ====================
// PAGE LOAD TRANSITION
// ====================
window.addEventListener("DOMContentLoaded", () => {
  document.body.classList.add("fade-in");
});
