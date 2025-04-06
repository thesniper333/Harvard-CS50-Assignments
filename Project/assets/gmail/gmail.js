// Load stored credentials or use placeholders
const CLIENT_ID = localStorage.getItem("gmailClientId") || "";
const CLIENT_SECRET = localStorage.getItem("gmailClientSecret") || "";
const API_KEY = localStorage.getItem("gmailApiKey") || "";
const SCOPES = 'https://www.googleapis.com/auth/gmail.readonly';

document.addEventListener("DOMContentLoaded", function () {
    // Ensure the API container is hidden initially
    document.getElementById("gmail-api-container").style.display = "none";

    document.getElementById("save-gmail-api").addEventListener("click", function () { 
        const clientId = document.getElementById("gmail-client-id").value.trim();
        const clientSecret = document.getElementById("gmail-client-secret").value.trim();
        const apiKey = document.getElementById("gmail-api-key").value.trim();

        if (clientId && clientSecret && apiKey) {
            localStorage.setItem("gmailClientId", clientId);
            localStorage.setItem("gmailClientSecret", clientSecret);
            localStorage.setItem("gmailApiKey", apiKey);
            
            // Hide the API container and show buttons again
            document.getElementById("gmail-api-container").style.display = "none";
            document.getElementById("change-gmail-api").style.display = "block";
           

            location.reload();
        } 
    });

    document.getElementById("change-gmail-api").addEventListener("click", function () {
        // Show the API container
        document.getElementById("gmail-api-container").style.display = "block";
        // Hide the buttons
        document.getElementById("change-gmail-api").style.display = "none";
        document.getElementById("logout").style.display = "none";
    });
});

// Hide API Key input when clicked outside
document.addEventListener("click", function (event) {
    const apiKeyContainer = document.getElementById("gmail-api-container");
    const changeApiKeyButton = document.getElementById("change-gmail-api");
    const isLoggedIn = localStorage.getItem("google_access_token") !== null;
    const logoutButton = document.getElementById("logout");

    if (apiKeyContainer.style.display === "block" &&  
        event.target !== changeApiKeyButton &&  
        !apiKeyContainer.contains(event.target)) {
        apiKeyContainer.style.display = "none";
        changeApiKeyButton.style.display = "block";
        if (isLoggedIn) {
            logoutButton.style.display = "block";  // Show logout only if logged in
        }
        

    }
    

});


// Save API Credentials to Local Storage
document.getElementById("save-gmail-api").addEventListener("click", function () { 
    const clientId = document.getElementById("gmail-client-id").value.trim();
    const clientSecret = document.getElementById("gmail-client-secret").value.trim();
    const apiKey = document.getElementById("gmail-api-key").value.trim();

    if (clientId && clientSecret && apiKey) {
        localStorage.setItem("gmailClientId", clientId);
        localStorage.setItem("gmailClientSecret", clientSecret);
        localStorage.setItem("gmailApiKey", apiKey);
        
        document.getElementById("gmail-api-container").style.display = "none";
        document.getElementById("change-gmail-api").style.display = "block";
        location.reload();
    } 
});

// Allow user to change stored credentials
document.getElementById("change-gmail-api").addEventListener("click", function () {
    document.getElementById("gmail-api-container").style.display = "block";
    document.getElementById("change-gmail-api").style.display = "none";
});


let tokenClient; // Google OAuth client

function handleAuthClick() {
  
  initializeGoogleAuth();
  
  tokenClient.requestAccessToken();

  tokenClient.callback = (response) => {
    if (response.access_token) {
        localStorage.setItem("google_access_token", response.access_token);
        document.getElementById("login").style.display = "none";
        document.getElementById("email-list").style.display = "block";
        document.getElementById("logout").style.display = "block";

        // ✅ Fetch emails immediately after login
        fetchEmails(response.access_token);
        startAutoFetch(response.access_token);
    } else {
        console.error("Failed to receive access token");
    }
 };
}



// Fetch emails from Gmail API

function fetchEmails(token) {
  fetch('https://www.googleapis.com/gmail/v1/users/me/messages?labelIds=INBOX&q=is:unread', {
      headers: { Authorization: `Bearer ${token}` }
  })
  .then((response) => response.json())
  .then((data) => {
      if (data.messages && data.messages.length > 0) {
          Promise.all(
              data.messages.map(msg =>
                  fetch(`https://www.googleapis.com/gmail/v1/users/me/messages/${msg.id}`, {
                      headers: { Authorization: `Bearer ${token}` }
                  }).then(res => res.json())
              )
          ).then(emailDataList => {
              emailDataList.reverse(); // 🔥 Reverse to show newest first
              firstEmailId = emailDataList[emailDataList.length - 1].id; // Store latest email
              appendSortedEmails(emailDataList, true);
          });
      } else {
          console.log("No unread emails found.");
          
          
         
          
      }
  })
  .catch((error) => console.error('Failed to fetch emails', error));
}




// Fetch new emails

function fetchNewEmails(token) {
  if (!firstEmailId) return; // If no email has been loaded, do nothing

  fetch(`https://www.googleapis.com/gmail/v1/users/me/messages?labelIds=INBOX&q=is:unread`, {
      headers: { Authorization: `Bearer ${token}` }
  })
  .then((response) => response.json())
  .then((data) => {
      if (data.messages && data.messages.length > 0) {
          Promise.all(
              data.messages.map(msg =>
                  fetch(`https://www.googleapis.com/gmail/v1/users/me/messages/${msg.id}`, {
                      headers: { Authorization: `Bearer ${token}` }
                  }).then(res => res.json())
              )
          ).then(emailDataList => {
              emailDataList.reverse(); // Ensure newest first
              const newEmails = emailDataList.filter(email => email.id !== firstEmailId && !displayedEmailIds.has(email.id));

              if (newEmails.length > 0) {
                  firstEmailId = newEmails[0].id; // Update latest email
                  appendSortedEmails(newEmails, false);
              }
          });
      }
  })
  .catch((error) => console.error('Failed to fetch new emails', error));
}

  
// Append emails to the email list

const displayedEmailIds = new Set(); // Track displayed emails

function appendSortedEmails(emailDataList, clearList) {
    const container = document.getElementById('email-list');

    if (clearList) {
        container.innerHTML = ""; // Clear list only on first load
        displayedEmailIds.clear(); // Clear tracked emails
    }

    emailDataList.forEach((emailData) => {
        if (!displayedEmailIds.has(emailData.id)) { // Only add if not already displayed
            const headers = emailData.payload.headers;
            let subject = headers.find(header => header.name === "Subject")?.value || "No Subject";
            const from = headers.find(header => header.name === "From")?.value || "Unknown Sender";
            const date = new Date(parseInt(emailData.internalDate)).toLocaleString(); // Convert timestamp

            // Shorten subject to prevent interference with the date/time
            const maxSubjectLength = 30;
            if (subject.length > maxSubjectLength) {
                subject = subject.substring(0, maxSubjectLength) + "...";
            }

            // Create the Gmail direct link
            const gmailLink = `https://mail.google.com/mail/u/0/#inbox/${emailData.id}`;

            // Create the email container div
            const emailElement = document.createElement("div");
            emailElement.classList.add("email");

            // Wrap content inside <a> tag
            emailElement.innerHTML = `
                <a href="${gmailLink}" target="_blank" class="email-link">
                    <div class="email-left">
                        <span class="blinking-circle"></span> <!-- Blinking Circle -->
                        <strong class="email-sender">${from}</strong> 
                    </div>
                    <div class="email-right">
                        <span class="email-subject">${subject}</span>
                        <span class="email-date">${date}</span> <!-- Date aligned right -->
                    </div>
                </a>
            `;

            // Remove email from list after opening Gmail link
            emailElement.querySelector(".email-link").addEventListener("click", function (event) {
                const circle = this.querySelector(".blinking-circle");
                if (circle) circle.remove(); // Remove blinking circle

                // Delay removal to allow the Gmail link to open properly
                setTimeout(() => {
                    emailElement.remove();
                }, 2000); // 2-second delay ensures Gmail opens first
            });

            container.prepend(emailElement); // 🔥 Prepend to show newest first

            displayedEmailIds.add(emailData.id); // Track this email as displayed
        }
    });
}


//Auto-fetch emails
let latestEmailId = null; // Store the most recent email ID

function startAutoFetch(token) {
  console.log("Starting real-time email fetching...");
  setInterval(() => fetchNewEmails(token), 5000); // Fetch every 5 seconds
}
  
// Sign Out handler
function handleSignOut() {
  google.accounts.oauth2.revoke(sessionStorage.getItem("google_access_token"), () => {
    console.log("User signed out.");

    // Show login button, hide logout button
    document.getElementById("login").style.display = "block";
    document.getElementById("email-list").style.display = "none";
    document.getElementById("logout").style.display = "none";

    // Clear stored token
    localStorage.removeItem("google_access_token");

    // Clear email list
    document.getElementById("email-list").innerHTML = "";
  });
}

// Refresh access token before expiration so user does not need to sign in again
function refreshAccessToken() {
  const refreshToken = localStorage.getItem("google_refresh_token");
  if (!refreshToken) {
      console.error("No refresh token found! User must sign in again.");
      return;
  }

  fetch(`https://oauth2.googleapis.com/token`, {
      method: "POST",
      headers: { "Content-Type": "application/x-www-form-urlencoded" },
      body: new URLSearchParams({
          client_id: CLIENT_ID,
          client_secret: CLIENT_SECRET,  // Replace with actual client secret
          refresh_token: refreshToken,
          grant_type: "refresh_token",
      })
  })
  .then(response => response.json())
  .then(data => {
      if (data.access_token) {
          console.log("Access token refreshed successfully!");
          localStorage.setItem("google_access_token", data.access_token);
          startAutoFetch(data.access_token);
      } else {
          console.error("Failed to refresh access token:", data);
      }
  })
  .catch(error => console.error("Token refresh error:", error));
}

// Refresh token every 55 minutes (before expiration)
setInterval(refreshAccessToken, 55 * 60 * 1000);

  


// Initialize Google Auth

function initializeGoogleAuth() {
    if (typeof google === 'undefined') {
        console.error('Google Identity Services library not loaded');
        return;
    }

    const storedClientId = localStorage.getItem("gmailClientId") || CLIENT_ID;

    tokenClient = google.accounts.oauth2.initTokenClient({
        client_id: storedClientId,
        scope: SCOPES,
        prompt: '',
        callback: (response) => {
            if (response.access_token) {
                localStorage.setItem("google_access_token", response.access_token);
                localStorage.setItem("google_refresh_token", response.refresh_token);
                document.getElementById("login").style.display = "none";
                document.getElementById("logout").style.display = "block";
                fetchEmails(response.access_token);
                startAutoFetch(response.access_token);
            } else {
                console.error('Failed to receive access token');
            }
        },
    });

    console.log('Google OAuth client initialized');
}


// Initialize Google Auth on page load and auto-login if token is stored

document.addEventListener("DOMContentLoaded", function () {
  const storedToken = localStorage.getItem("google_access_token");
  if (storedToken) {
      document.getElementById("login").style.display = "none";
      document.getElementById("email-list").style.display = "block";
      document.getElementById("logout").style.display = "block";
      fetchEmails(storedToken);
      startAutoFetch(storedToken);
  } else {
      console.log("No stored token found. User needs to log in.");
  }
});


// Add event listener to the login button
document.getElementById('login').addEventListener('click', handleAuthClick);
document.getElementById("logout").addEventListener("click", handleSignOut);

