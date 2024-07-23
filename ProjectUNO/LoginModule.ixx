export module LoginModule;
import GlobalModule;
#include "raylib.h"
#include "regex"

const char* usernameInstructions = "Username must:\n"
"- Start with a capital letter\n"
"- Have at least three characters\n"
"- Contain only lowercase letters after the first letter";

const char* passwordInstructions = "Password must:\n"
"- Be at least 8 characters long\n"
"- Contain at least one uppercase letter\n"
"- Contain at least one lowercase letter\n"
"- Contain at least one digit";


export Rectangle usernameInputArea = { screenWidth / 2.0f - 100, screenHeight / 2.0f - 50, 200, 30 };
export Rectangle passwordInputArea = { screenWidth / 2.0f - 100, screenHeight / 2.0f + 20, 200, 30 };
export Rectangle loginButton = { screenWidth / 2.0f - 100, screenHeight / 2.0f + 90, 200, 50 };

// Function to draw the login screen and handle button clicks
export void drawLogin() {
    // Color for username input area
    Color usernameInputColor = GRAY;
    if (usernameInputAreaActive) {
        if (username.empty()) {
            usernameInputColor = WHITE; // White when selected and 
        }
        else {
            usernameInputColor = isUsernameValidFlag ? GREEN : RED; // Green if valid, red if 
        }
    }

    // Draw username label and input area
    DrawText("Username:", usernameInputArea.x - MeasureText("Username:", 20) - 10, usernameInputArea.y + (usernameInputArea.height / 2) - 10, 20, WHITE);
    DrawRectangleLines(usernameInputArea.x, usernameInputArea.y, usernameInputArea.width, usernameInputArea.height, usernameInputColor);
    DrawText(username.c_str(), usernameInputArea.x + 5, usernameInputArea.y + (usernameInputArea.height / 2) - 10, 20, WHITE);

    // Color for password input area
    Color passwordInputColor = GRAY;
    if (passwordInputAreaActive) {
        if (password.empty()) {
            passwordInputColor = WHITE; // White when selected and 
        }
        else {
            passwordInputColor = isPasswordValidFlag ? GREEN : RED; // Green if valid, red if not
        }
    }

    // Draw password label and input area
    DrawText("Password:", passwordInputArea.x - MeasureText("Password:", 20) - 10, passwordInputArea.y + (passwordInputArea.height / 2) - 10, 20, WHITE);
    DrawRectangleLines(passwordInputArea.x, passwordInputArea.y, passwordInputArea.width, passwordInputArea.height, passwordInputColor);
    DrawText(password.c_str(), passwordInputArea.x + 5, passwordInputArea.y + (passwordInputArea.height / 2) - 10, 20, WHITE);

    // Draw login button
    DrawRectangleRec(loginButton, GRAY);
    DrawText("LOGIN", loginButton.x + (loginButton.width / 2) - MeasureText("LOGIN", 20) / 2, loginButton.y + (loginButton.height / 2) - 10, 20, WHITE);

    // Draw instructions below the login button if needed
    if (!isUsernameValidFlag || !isPasswordValidFlag) {
        int instructionsY = loginButton.y + loginButton.height + 20; // Initial vertical position
        int instructionsX = loginButton.x - 100;
        if (!isUsernameValidFlag) {
            DrawText(usernameInstructions, instructionsX, instructionsY, 20, WHITE);
            instructionsY += 80; // Increase y position for the next instruction
        }
        if (!isPasswordValidFlag) {
            DrawText(passwordInstructions, instructionsX, instructionsY, 20, WHITE);
        }
    }
}



export void checkInputFocus() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePoint = GetMousePosition();
        usernameInputAreaActive = CheckCollisionPointRec(mousePoint, usernameInputArea);
        passwordInputAreaActive = CheckCollisionPointRec(mousePoint, passwordInputArea);
    }
}

export bool isUsernameValid(const std::string& username) {
    // Define your username validation criteria
    std::regex usernameRegex("^[A-Z][a-z]{2,}$");
    return std::regex_match(username, usernameRegex);
}

// Function to check if the password is valid
export bool isPasswordValid(const std::string& password) {
    // Define your password validation criteria
    // At least 8 characters, at least one uppercase, one lowercase, and one digit
    std::regex passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$");
    return std::regex_match(password, passwordRegex);
}

export void handleInput() {
    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (usernameInputAreaActive && !username.empty()) {
            username.pop_back();
            isUsernameValidFlag = isUsernameValid(username);
        }
        else if (passwordInputAreaActive && !password.empty()) {
            password.pop_back();
            isPasswordValidFlag = isPasswordValid(password);
        }
    }

    int key = GetKeyPressed();
    if (key >= 32 && key <= 126) {
        bool shiftPressed = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
        if (key >= 'A' && key <= 'Z') {
            if (!shiftPressed) {
                key += 32; // Convert to lowercase
            }
        }
        else if (key >= 'a' && key <= 'z') {
            if (shiftPressed) {
                key -= 32; // Convert to uppercase
            }
        }

        if (usernameInputAreaActive) {
            username += (char)key;
            isUsernameValidFlag = isUsernameValid(username);
        }
        else if (passwordInputAreaActive) {
            password += (char)key;
            isPasswordValidFlag = isPasswordValid(password);
        }
    }
}

export bool isLoginValid() {
    isUsernameValidFlag = isUsernameValid(username);
    isPasswordValidFlag = isPasswordValid(password);

    if (isUsernameValidFlag && isPasswordValidFlag) {
        return true;
    }
    return false;
}

export bool isLoginClicked() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, loginButton)) {
            DrawRectangleRec(loginButton, BLACK);
            return true;
        }
    }
    return false;
}
