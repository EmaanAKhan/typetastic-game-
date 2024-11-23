#include "raylib.h"
#include <stdio.h>

#define NUM_QUESTIONS 16

int main() {
    const int screenWidth = 800;
    const int screenHeight = 700;
    InitWindow(screenWidth, screenHeight, "MBTI Quiz");

    Color LIGHTGREEN = {144, 238, 144, 255};
    Color LIGHTPINK = {255, 182, 259, 255};
    Color VIBRANT_COLOR = {224, 255, 255, 255};

    Color bgColors[] = {RAYWHITE, LIGHTGRAY, SKYBLUE, LIGHTGREEN, BEIGE, LIGHTPINK, YELLOW, VIOLET};
    int bgColorIndex = 0;
    bgColorIndex++;
    if (bgColorIndex >= 8) bgColorIndex = 0;

    Color buttonColor = SKYBLUE;
    Color buttonHoverColor = GRAY;

   
    const char *questions[NUM_QUESTIONS] = {
        "I prefer solitary activities over social ones.",
        "For a new project, I prefer working solo over team brainstorming.",
        "I often think before I speak.",
        "I find it draining to socialize with large groups.",
        "In planning, I prefer tried-and-true strategies.",
        "I trust practical experience over theory.",
        "I prefer focusing on the present and concrete info.",
        "I do not like thinking about the future and what could be.",
        "I make decisions based on logic.",
        "I strategize rather than rushing with feelings.",
        "In feedback, I focus on honesty over sparing feelings.",
        "I avoid relying on emotions for decisions.",
        "I prefer a planned and organized approach to life.",
        "I thrive on having everything organized ahead of time.",
        "I find satisfaction in checking off completed tasks.",
        "I feel anxious when plans change unexpectedly."
    };

    int answers[NUM_QUESTIONS] = {0};  

    int currentQuestion = 0;
    int introvertCount = 0, sensingCount = 0, thinkingCount = 0, judgingCount = 0;

    bool quizComplete = false;
    bool introScreen = true;
    char mbti[5] = "";

   
    float startTime = GetTime();  
    const float timeLimit = 180.0f;

   

    while (!WindowShouldClose()) {
       
        float elapsedTime = GetTime() - startTime;
        float remainingTime = timeLimit - elapsedTime;

        if (remainingTime <= 0) {
            remainingTime = 0;
            quizComplete = true;  
        }

        BeginDrawing();

        if (quizComplete) {
            ClearBackground(VIBRANT_COLOR);
        } else {
            ClearBackground(bgColors[bgColorIndex]);  
        }

        if (introScreen) {
            DrawText("Welcome to\n\n\n\nTYPETASTIC ", 150, 100, 50, DARKBLUE);
            DrawText("Your own mbti quiz created by Arquam, Emaan, Ibrahim and Mesum", 50, 250, 20, DARKGRAY);
            DrawText("Answer these questions in time to know your\n\n Myers Briggs Personality Type", 50, 400, 20, DARKGRAY);

            Rectangle startButton = {280, 300, 200, 70};
            if (CheckCollisionPointRec(GetMousePosition(), startButton)) {
                DrawRectangleRec(startButton, buttonHoverColor);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    introScreen = false;
                
                
                
                }
            } else {
                DrawRectangleRec(startButton, buttonColor);
            }
            DrawText("Start Quiz", 335, 315, 20, BLACK);
        } else if (!quizComplete) {
            DrawText("MBTI Quiz", 350, 20, 20, DARKGRAY);
            DrawText(questions[currentQuestion], 50, 100, 20, DARKGRAY);

            const char *options[] = {"Strongly Agree", "Agree", "Neutral", "Disagree", "Strongly Disagree"};
            for (int i = 0; i < 5; i++) {
                Rectangle button = {150, 200 + i * 60, 500, 40};
                if (CheckCollisionPointRec(GetMousePosition(), button)) {
                    DrawRectangleRec(button, buttonHoverColor);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        answers[currentQuestion] = i + 1;

                        if (currentQuestion < 4 && i < 2) introvertCount++;
                        else if (currentQuestion >= 4 && currentQuestion < 8 && i < 2) sensingCount++;
                        else if (currentQuestion >= 8 && currentQuestion < 12 && i < 2) thinkingCount++;
                        else if (currentQuestion >= 12 && currentQuestion < 16 && i < 2) judgingCount++;

                        currentQuestion++;

                       
                        bgColorIndex = (bgColorIndex + 1) % 8;

                        if (currentQuestion >= NUM_QUESTIONS) quizComplete = true;
                    }
                } else {
                    DrawRectangleRec(button, buttonColor);
                }
                DrawText(options[i], 160, 210 + i * 60, 20, BLACK);
            }

           
            int minutes = (int)(remainingTime / 60);
            int seconds = (int)(remainingTime) % 60;
            char timeText[10];
            snprintf(timeText, sizeof(timeText), "%02d:%02d", minutes, seconds);
            DrawText(timeText, 650, 20, 50, RED);

           
            int percentage = (int)((float)currentQuestion / NUM_QUESTIONS * 100);
            char progressText[15];
            snprintf(progressText, sizeof(progressText), "%d%% Completed", percentage);
            DrawText(progressText, 350, 550, 30, DARKBLUE);
        } else {
            DrawText("Quiz Complete!", 300, 150, 30, DARKGREEN);

            mbti[0] = (introvertCount >= 3) ? 'I' : 'E';
            mbti[1] = (sensingCount >= 3) ? 'S' : 'N';
            mbti[2] = (thinkingCount >= 3) ? 'T' : 'F';
            mbti[3] = (judgingCount >= 3) ? 'J' : 'P';
            mbti[4] = '\0';

            DrawText(TextFormat("Your MBTI Type is: %s\n\nYOUR CHARACTER DESCRIPTION IS:", mbti), 100, 250, 25, DARKGRAY);
            DrawText("Press 'R' to Restart\n :", 150, 500, 20, GRAY);
            if (strcmp(mbti, "ISTJ") == 0) {
        DrawText(" **ISTJ: The Sentinel**\n \n  Grounded, responsible, and focused, ISTJs \n are the keepers of order in a chaotic world.\n They take commitment seriously and work tirelessly to ensure stability.\n ISTJs are the quiet backbone of society, dependable and fiercely loyal\n, with a commitment to do things the right way, every time.", 10, 350, 20, DARKGREEN);
    }
            if (strcmp(mbti, "INTP") == 0) {
        DrawText("INTP: The Thinker \n \n Logical, curious,and a little unconventional\n, INTPs are the ones who crack codes and solve mysteries,\n all in their heads. They question everything and love to dive into theoretical universes.\n They’ll skip small talk to explore the depths of philosophy or \ntech like a rebel who prefers logic over emotions.", 10, 350, 20, DARKGREEN);
            }
            if (strcmp(mbti, "ENTJ") == 0) {
            DrawText("**ENTJ: The Commander**\n Born to lead, ENTJs have a vibe that screams “boss.” They\n strategize with precision, making waves wherever \nthey go. They are direct, ambitious, and know how\n to turn vision into action. ENTJs don’t \njust break   boundaries,  they redefine  them.", 10, 350, 20, DARKGREEN);
            }
         if (strcmp(mbti, "ENTP") == 0) {
         DrawText(" **ENTP: The Debater**\nIf there’s an argument, ENTPs\n are the ones making it interesting. Known for their\n quick wit and creative energy, they live for\n intellectual duels. Charming and relentless, \nthey can argue any side and love finding clever\n solutions to tough problems, just to see if they can.", 10, 350, 20, DARKGREEN);
         }
         if (strcmp(mbti, "INTJ") == 0) {
         DrawText("**INFJ: The Sage**\n Wise and mysterious, INFJs are the quiet voices\n with world-changing ideas. Deeply empathetic with a mind that \nalways dives deeper, they seek meaning in\n everything. They’re visionaries who\n see past the surface, offering insights that\n can spark revolutions or healing.", 10, 350, 20, DARKGREEN);
         }
         if (strcmp(mbti, "ENFJ") == 0) {
        DrawText("**ENFJ: The Charmer**\nCharismatic and full of warmth,\n ENFJs are the natural mentors who can light up a room. \n They have this magnetic energy that draws people \n to them, guiding others with \n a blend of wisdom and enthusiasm. Their lives are \n about connection, community, and lifting everyone to their \n full potential.", 10, 350, 20, DARKGREEN);
         }
         if (strcmp(mbti, "ENFP") == 0) {
        DrawText("**ENFP: The Adventurer**\nENFPs are life’s explorers, constantly\n seeking excitement, inspiration, and new ideas\n. They’re the free-spirits who see the\n potential in everyone, making the world \na little brighter with their optimism. \nWith boundless curiosity, they turn each day\n into an adventure and each person into a friend.", 10, 350, 20, DARKGREEN);
         }
        if (strcmp(mbti, "ISFJ") == 0) {
        DrawText("**ISFJ: The Protector**\nGentle yet strong, ISFJs are the\n unsung heroes who dedicate themselves to caring\n for others. With hearts of gold, they put others \nfirst and go above and beyond to create harmony.\nThey don’t seek attention but make an unforgettable\n impact through kindness and quiet strength.", 10, 350, 20, DARKGREEN);
         }
         if (strcmp(mbti, "ISTP") == 0) {
        DrawText("**ISTP: The Virtuoso**\nBold and adaptable, ISTPs are the\n hands-on tinkerers who live to take things apart\n and put them back together. They’re adventurous, \nskilled, and aren’t afraid to take risks.\n With a love for the practical side of life, they’re \nresourceful and never hesitate to jump into action.", 10, 350, 20, DARKGREEN);
         }
       
       
        if (strcmp(mbti, "INTP") == 0) {
        DrawText("**INTP: The Thinker**\nLogical, curious, and a little unconventional,\n INTPs are the ones who crack codes and \nsolve mysteries, all in their heads. \nThey question everything and love to dive into \ntheoretical universes. They’ll skip small talk to \nexplore the depths of philosophy or tech like a rebel\n who prefers logic over emotions.", 10, 350, 20, DARKGREEN);
         }
       
       
        if (strcmp(mbti, "INFJ") == 0) {
        DrawText("**INFJ: The Sage**\nWise and mysterious, INFJs are the quiet voices\n with world-changing ideas. \nDeeply empathetic with a mind that always dives deeper,\n they seek meaning in everything.\n They’re visionaries who see past the surface, \noffering insights that can spark revolutions\n or healing.", 10, 350, 20, DARKGREEN);
         }
         
         if (strcmp(mbti, "INFP") == 0) {
        DrawText("**INFP: The Dreamer**\nIdealistic and poetic, INFPs are on a quest for \nbeauty and truth in a world that sometimes\n feels harsh. With hearts full of empathy,\n they fight for what’s right and express their soul through creativity.\n Gentle yet passionate, \nthey’re artists at heart, quietly changing the \nworld one dream at a time.", 10, 350, 20, DARKGREEN);
       
         }
         
         if (strcmp(mbti, "ESTJ") == 0) {
        DrawText("**ESTJ: The Executive**\nPractical, organized, and in control, ESTJs are the \ngo-to people for making things happen. They bring order \nto chaos with efficiency and a \nno-nonsense attitude. Driven by tradition and grounded \nin reality, they’re the ultimate leaders who\n know how to turn ideas into solid results.", 10, 350, 20, DARKGREEN);
       
         }
         if (strcmp(mbti, "ESFJ") == 0) {
        DrawText("**ESFJ: The Supporter**Social and generous, ESFJs thrive on bringing people together and creating harmony. They’re the friends who remember everyone’s birthdays and make sure no one feels left out. Kind-hearted and full of warmth, ESFJs make communities feel like home, lifting up everyone around them.", 10, 350, 20, DARKGREEN);
       
         }
         if (strcmp(mbti, "ISFP") == 0) {
        DrawText("**ISFP: The Artist**\nCreative and quietly passionate, ISFPs are lovers of\n beauty who live in the present. \nThey express themselves through art, style,\n and action. Free-spirited yet grounded,\n they bring a unique charm that makes life \nfeel like a canvas. Their lives are all \nabout authenticity and emotion.", 10, 350, 20, DARKGREEN);
       
         }
         if (strcmp(mbti, "ESTP") == 0) {
        DrawText("**ESTP: The Maverick**\nBold and outgoing, ESTPs are the thrill-seekers \nwho live in the fast lane. They crave \nexcitement and have an infectious energy that\n can light up any room. Confident and practical,\n they’re ready to take on any challenge, \nunafraid of diving headfirst into the unknown.", 10, 350, 20, DARKGREEN);
       
         }
         if (strcmp(mbti, "ESFP") == 0) {
        DrawText("**ESFP: The Entertainer**\nThe life of the party, ESFPs live for fun,\n laughter, and making memories.\n They love the spotlight and thrive on excitement,\n bringing joy wherever they go.\n With a spontaneous and magnetic personality,\n ESFPs turn the ordinary into something \nworth celebrating, embracing life with\n open arms.", 10, 350, 20, DARKGREEN);
       
         }
            int finalPercentage = 100;
            char finalProgressText[15];
            snprintf(finalProgressText, sizeof(finalProgressText), "%d%% Completed", finalPercentage);
            DrawText(finalProgressText, 350, 550, 30, DARKBLUE);

            if (IsKeyPressed(KEY_R)) {
                currentQuestion = 0;
                introvertCount = sensingCount = thinkingCount = judgingCount = 0;
                quizComplete = false;
                introScreen = true;
                bgColorIndex = 0;  // This is to Reset our color cycle
                for (int i = 0; i < NUM_QUESTIONS; i++) {
                    answers[i] = 0;  // this then Resets the answers
                }
                startTime = GetTime();
            }
        }

        EndDrawing();
    }

    CloseWindow();
   
    return 0;
}
