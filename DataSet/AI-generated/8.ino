// Predefined password for authentication
const String predefinedPassword = "arduino123";

// Variable to keep track of authentication state
bool isAuthenticated = false;

void setup() {
  Serial.begin(9600); // Initialize Serial communication at 9600 baud rate
  Serial.println("AuthMiddleware started. Please authenticate to continue.");
}

void loop() {
  if (!isAuthenticated) {
    checkAuthentication(); // Check if the user has authenticated
  } else {
    // User is authenticated, allow access to protected functions
    protectedFunction();
  }

  delay(1000); // Delay to prevent Serial flooding
}

// Function to check user authentication
void checkAuthentication() {
  if (Serial.available() > 0) {
    String receivedPassword = Serial.readStringUntil('\n'); // Read the input until newline character

    // Trim any extra whitespace or newline characters
    receivedPassword.trim();

    if (receivedPassword.equals(predefinedPassword)) {
      isAuthenticated = true;
      Serial.println("Authentication successful! Access granted.");
    } else {
      Serial.println("Authentication failed! Try again.");
    }
  }
}

// Protected function that requires authentication to access
void protectedFunction() {
  Serial.println("Accessing protected function...");
  // Add code for protected functionality here

  // For demonstration, reset authentication after showing access
  Serial.println("Returning to authentication state for demonstration.");
  isAuthenticated = false; // Reset authentication state for repeated testing
}
