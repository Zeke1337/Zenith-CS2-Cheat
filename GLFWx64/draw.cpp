#include "draw.h"



void drawFOVCircle(float radius, const Vec2& screenCenter) {
    int numSegments = 100;
    float angleStep = (2.0f * 3.14159265358979323846f) / numSegments;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; i++) {
        float angle = i * angleStep;
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;
        glVertex2f((screenCenter.X) + x, (screenCenter.Y) + y);
    }
    glEnd();
}

// Function to render text using the bitmap font
void renderText(const char* text, GLuint listBase, float x, float y) {
    glRasterPos2f(x, y);
    glPushAttrib(GL_LIST_BIT);
    glListBase(listBase - 32);
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
    glPopAttrib();
}

void DrawBox(Vec2& FeetCoords, Vec2& HeadCoords, Config& cnf)
{
    glLineWidth(2.0f);
    float height = HeadCoords.Y - FeetCoords.Y;
    float width = height / 3.8f;

    // Draw the filled box with semi-transparent black color
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f); // Black color with 50% transparency
    glBegin(GL_QUADS);
    glVertex2f(FeetCoords.X - (width / 2), FeetCoords.Y);
    glVertex2f(FeetCoords.X + (width / 2), FeetCoords.Y);
    glVertex2f(FeetCoords.X + (width / 2), HeadCoords.Y);
    glVertex2f(FeetCoords.X - (width / 2), HeadCoords.Y);
    glEnd();

    // Draw the box outline
    glColor4f(cnf.fColorEsp[0], cnf.fColorEsp[1], cnf.fColorEsp[2], cnf.fColorEsp[3]);
    glBegin(GL_LINES);
    glVertex2f(FeetCoords.X - (width / 2), FeetCoords.Y);
    glVertex2f(FeetCoords.X - (width / 2), HeadCoords.Y);
    glVertex2f(FeetCoords.X - (width / 2), HeadCoords.Y);
    glVertex2f(FeetCoords.X + (width / 2), HeadCoords.Y);
    glVertex2f(FeetCoords.X + (width / 2), HeadCoords.Y);
    glVertex2f(FeetCoords.X + (width / 2), FeetCoords.Y);
    glVertex2f(FeetCoords.X + (width / 2), FeetCoords.Y);
    glVertex2f(FeetCoords.X - (width / 2), FeetCoords.Y);
    glEnd();
}

void DrawOutline(Vec2& FeetCoords, Vec2& HeadCoords, Config& cnf)
{
    glLineWidth(2.0f);
    float height =  FeetCoords.Y- HeadCoords.Y;
    float width = height / 3.8f;

    // Draw the outline
    glColor4f(cnf.fColorEsp[0], cnf.fColorEsp[1], cnf.fColorEsp[2], cnf.fColorEsp[3]);
    glBegin(GL_LINES);
    // Left side
    glVertex2f(FeetCoords.X - (width / 2), FeetCoords.Y);
    glVertex2f(FeetCoords.X - (width / 2), HeadCoords.Y);

    // Top side
    glVertex2f(FeetCoords.X - (width / 2), HeadCoords.Y);
    glVertex2f(FeetCoords.X + (width / 2), HeadCoords.Y);

    // Right side
    glVertex2f(FeetCoords.X + (width / 2), HeadCoords.Y);
    glVertex2f(FeetCoords.X + (width / 2), FeetCoords.Y);

    // Bottom side
    glVertex2f(FeetCoords.X + (width / 2), FeetCoords.Y);
    glVertex2f(FeetCoords.X - (width / 2), FeetCoords.Y);
    glEnd();
}



void DrawCornerOutline(Vec2& FeetCoords, Vec2& HeadCoords, Config& cnf)
{
    glLineWidth(2.0f);
    float height = HeadCoords.Y - FeetCoords.Y;
    float width = height / 3.8f;

    float lineLength = width / cnf.fLineIndex; // Adjust this to control the length of the corner lines

    glColor4f(cnf.fColorEsp[0], cnf.fColorEsp[1], cnf.fColorEsp[2], cnf.fColorEsp[3]);
    glBegin(GL_LINES);

    // Top-left corner
    glVertex2f(FeetCoords.X - (width / 2), HeadCoords.Y);
    glVertex2f(FeetCoords.X - (width / 2) + lineLength, HeadCoords.Y);

    glVertex2f(FeetCoords.X - (width / 2), HeadCoords.Y);
    glVertex2f(FeetCoords.X - (width / 2), HeadCoords.Y - lineLength);

    // Top-right corner
    glVertex2f(FeetCoords.X + (width / 2), HeadCoords.Y);
    glVertex2f(FeetCoords.X + (width / 2) - lineLength, HeadCoords.Y);

    glVertex2f(FeetCoords.X + (width / 2), HeadCoords.Y);
    glVertex2f(FeetCoords.X + (width / 2), HeadCoords.Y - lineLength);

    // Bottom-left corner
    glVertex2f(FeetCoords.X - (width / 2), FeetCoords.Y);
    glVertex2f(FeetCoords.X - (width / 2) + lineLength, FeetCoords.Y);

    glVertex2f(FeetCoords.X - (width / 2), FeetCoords.Y);
    glVertex2f(FeetCoords.X - (width / 2), FeetCoords.Y + lineLength);

    // Bottom-right corner
    glVertex2f(FeetCoords.X + (width / 2), FeetCoords.Y);
    glVertex2f(FeetCoords.X + (width / 2) - lineLength, FeetCoords.Y);

    glVertex2f(FeetCoords.X + (width / 2), FeetCoords.Y);
    glVertex2f(FeetCoords.X + (width / 2), FeetCoords.Y + lineLength);

    glEnd();
}




void DrawArmorbar(Vec2& FeetCoords, Vec2& HeadCoords, Config& cnf, int armor)
{
    // Ensure the armor value is within the expected range
    armor = std::max(0, std::min(armor, 100));

    float height = HeadCoords.Y - FeetCoords.Y;
    float width = height / 3.8f;

    // Calculate the width of the armor bar based on the armor value
    float armorBarWidth = width * (armor / 100.0f);

    // Position the armor bar directly above the top of the box
    float armorBarYOffset = height * 0.05f; // Adjust this value for spacing between the box and armor bar
    float topOfBoxY = HeadCoords.Y + armorBarYOffset;

    // Draw the black outline of the armor bar
    glLineWidth(5.0f);
    glColor3f(0, 0, 0); // Black color for the outline
    glBegin(GL_LINES);
    glVertex2f(FeetCoords.X - (width / 2), topOfBoxY);
    glVertex2f(FeetCoords.X - (width / 2) + armorBarWidth, topOfBoxY);
    glEnd();

    // Set the color for the armor bar
    glColor3f(0, 0.5f, 1.0f); // Blue color for armor

    // Draw the actual armor bar
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(FeetCoords.X - (width / 2), topOfBoxY);
    glVertex2f(FeetCoords.X - (width / 2) + armorBarWidth, topOfBoxY);
    glEnd();
}





void DrawHealthbar(Vec2& FeetCoords, Vec2& HeadCoords, Config& cnf, int health)
{
    // Ensure the health value is within the expected range
    health = std::max(0, std::min(health, 100));

    float height = HeadCoords.Y - FeetCoords.Y;
    float width = height / 3.8f;

    // Calculate the height of the health bar based on the health value
    float healthBarHeight = height * (health / 100.0f);

    
    

    glLineWidth(7.0f);
    glColor3f(0, 0, 0); // Black color for the outline
    // Draw the outline 
    glBegin(GL_LINES);
    glVertex2f(FeetCoords.X - (width / 1.5), FeetCoords.Y);
    glVertex2f(FeetCoords.X - (width / 1.5), FeetCoords.Y + healthBarHeight);
    glEnd();



    // Determine the color based on the health value
    if (health >= 60) {
        glColor3f(0, 1, 0); // Green
    }
    else if (health >= 40) {
        glColor3f(1, 1, 0); // Yellow
    }
    else {
        glColor3f(1, 0, 0); // Red
    }

    glLineWidth(4.0f);
    // Draw the health bar
    glBegin(GL_LINES);
    glVertex2f(FeetCoords.X - (width / 1.5), FeetCoords.Y);
    glVertex2f(FeetCoords.X - (width / 1.5), FeetCoords.Y + healthBarHeight);
    glEnd();
}



void DrawSnaplinesBottom(Vec2& FeetCoords, Config& cnf)
{
    glLineWidth(2.0f);
    glColor4f(cnf.fColorSnapline[0], cnf.fColorSnapline[1], cnf.fColorSnapline[2], cnf.fColorSnapline[3]);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(FeetCoords.X, FeetCoords.Y);
    glEnd();
}

void DrawSnaplinesTop(Vec2& HeadCoords, Config& cnf)
{
    glLineWidth(2.0f);
    glColor4f(cnf.fColorSnapline[0], cnf.fColorSnapline[1], cnf.fColorSnapline[2], cnf.fColorSnapline[3]);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(HeadCoords.X, HeadCoords.Y);
    glEnd();
}

void DrawSnaplinesCenter(Vec2& HeadCoords, Config& cnf)
{
    glLineWidth(2.0f);
    glColor4f(cnf.fColorSnapline[0], cnf.fColorSnapline[1], cnf.fColorSnapline[2], cnf.fColorSnapline[3]);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(HeadCoords.X, HeadCoords.Y);
    glEnd();
}

Vec3 HSVtoRGB(float h, float s, float v)
{
    int i = int(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch (i % 6) {
    case 0: return Vec3(v, t, p); // r=v, g=t, b=p
    case 1: return Vec3(q, v, p); // r=q, g=v, b=p
    case 2: return Vec3(p, v, t); // r=p, g=v, b=t
    case 3: return Vec3(p, q, v); // r=p, g=q, b=v
    case 4: return Vec3(t, p, v); // r=t, g=p, b=v
    case 5: return Vec3(v, p, q); // r=v, g=p, b=q
    default: return Vec3(1.0f, 1.0f, 1.0f); // White as fallback color
    }
}

void DrawLine(Vec2& x, Vec2& y, Config& cnf)
{
    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    Vec3 skeletonColor;
    Vec3 glowColor;

    // Determine the color based on the selected effect
    switch (cnf.comboIndexSkeletonColor)
    {
    case 0: // Default glow effect
    {
        skeletonColor = Vec3(cnf.fColorSkeleton[0], cnf.fColorSkeleton[1], cnf.fColorSkeleton[2]);
        glowColor = skeletonColor;
        break;
    }
    case 1: // Rainbow glow effect
    {
        float hue = glfwGetTime() * 0.1f; // Cycle through colors over time
        glowColor = HSVtoRGB(fmod(hue, 1.0f), 1.0f, 1.0f);
        skeletonColor = glowColor;
        break;
    }
    case 2: // Pulse effect
    {
        float pulseIntensity = 0.5f + 0.5f * sin(glfwGetTime() * 2.0f); // Sinusoidal change
        skeletonColor = Vec3(cnf.fColorSkeleton[0] * pulseIntensity, cnf.fColorSkeleton[1] * pulseIntensity, cnf.fColorSkeleton[2] * pulseIntensity);
        glowColor = skeletonColor;
        break;
    }
    case 3: // Dynamic color shift effect
    {
        float timeFactor = glfwGetTime() * 0.5f;
        skeletonColor = Vec3((sin(timeFactor + 0) + 1) / 2.0f, (sin(timeFactor + 2) + 1) / 2.0f, (sin(timeFactor + 4) + 1) / 2.0f);
        glowColor = skeletonColor;
        break;
    }
    case 4: // Outer glow effect
    {
        skeletonColor = Vec3(cnf.fColorSkeleton[0], cnf.fColorSkeleton[1], cnf.fColorSkeleton[2]);
        glowColor = skeletonColor; // Use the same color but a more pronounced outer glow
        break;
    }
    case 5: // Strobe effect
    {
        if (fmod(glfwGetTime(), 0.5f) < 0.25f) { // Blink every half second
            skeletonColor = Vec3(1.0f, 1.0f, 1.0f); // White for strobe
        }
        else {
            skeletonColor = Vec3(0.0f, 0.0f, 0.0f); // Black (invisible) during off-phase
        }
        glowColor = skeletonColor;
        break;
    }
    case 6: // Gradient effect
    {
        skeletonColor = Vec3(cnf.fColorSkeleton[0], cnf.fColorSkeleton[1], cnf.fColorSkeleton[2]);
        glowColor = skeletonColor;
        break;
    }
    case 7: // Just the skeleton, no glow
    {
        skeletonColor = Vec3(cnf.fColorSkeleton[0], cnf.fColorSkeleton[1], cnf.fColorSkeleton[2]);
        break;
    }
    default:
    {
        skeletonColor = Vec3(cnf.fColorSkeleton[0], cnf.fColorSkeleton[1], cnf.fColorSkeleton[2]);
        glowColor = skeletonColor;
        break;
    }
    }

    // Draw the main skeleton line with the determined color
    glLineWidth(2.0f);
    glColor4f(skeletonColor.X, skeletonColor.Y, skeletonColor.Z, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(x.X, x.Y);
    glVertex2f(y.X, y.Y);
    glEnd();

    // If not just the skeleton, draw the glow effect with the same color
    if (cnf.comboIndexSkeletonColor != 7) {
        int glowPasses = 10;
        for (int i = 1; i <= glowPasses; i++) {
            float glowAlpha = 0.05f * (1.0f - (float)i / glowPasses);
            float glowWidth = 2.0f + i * 1.5f;

            glLineWidth(glowWidth);
            glColor4f(glowColor.X, glowColor.X, glowColor.Z, glowAlpha);
            glBegin(GL_LINES);
            glVertex2f(x.X, x.Y);
            glVertex2f(y.X, y.Y);
            glEnd();
        }
    }

    // Disable blending
    glDisable(GL_BLEND);
}





void DrawHeadBox(Vec2& FeetCoords, Vec2& HeadCoords, Config& cnf)
{
    // Farbe für die Box um den Kopf setzen
    //glColor4f(keybinds->color_enemy_box[0], keybinds->color_enemy_box[1], keybinds->color_enemy_box[2], keybinds->color_enemy_box[3]);

    // Höhe der Körperbox bestimmen
    float bodyHeight = HeadCoords.Y - FeetCoords.Y;

    // Höhe und Breite der Kopfbox dynamisch bestimmen (z.B. 10% der Körperboxhöhe)
    float headBoxHeight = bodyHeight * 0.1f;
    float headBoxWidth = headBoxHeight; // Gleiche Breite wie Höhe für eine quadratische Kopfbox

    // Position der Kopfbox berechnen und nach unten verschieben
    float headBoxTop = HeadCoords.Y - (bodyHeight * 0.1f); // Adjusting the top down by 5% of the body height
    float headBoxBottom = headBoxTop - headBoxHeight;
    float headBoxLeft = HeadCoords.X - (headBoxWidth / 2);
    float headBoxRight = HeadCoords.X + (headBoxWidth / 2);

    // Beginnen, die Linien zu zeichnen
    glBegin(GL_LINES);

    // Linke Linie
    glVertex2f(headBoxLeft, headBoxTop);
    glVertex2f(headBoxLeft, headBoxBottom);

    // Obere Linie
    glVertex2f(headBoxLeft, headBoxBottom);
    glVertex2f(headBoxRight, headBoxBottom);

    // Rechte Linie
    glVertex2f(headBoxRight, headBoxBottom);
    glVertex2f(headBoxRight, headBoxTop);

    // Untere Linie
    glVertex2f(headBoxRight, headBoxTop);
    glVertex2f(headBoxLeft, headBoxTop);

    glEnd();
}






void ShowHealthInText(Vec2& FeetCoords, GLuint& fontBase, Config& cnf, int health)
{
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    std::string healthString = std::to_string(health) + " HP";
    const char* healthCString = healthString.c_str();
    renderText(healthCString, fontBase, FeetCoords.X, FeetCoords.Y);
}

void ShowNameInText(Vec2& FeetCoords, GLuint& fontBase, const char* name)
{
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glLineWidth(4.0f);
    Vec2 NamePosition = FeetCoords;
    NamePosition.Y += 0.03;
    renderText(name, fontBase, NamePosition.X, NamePosition.Y);
}



// Function to draw a point on the radar
void drawRadarPoint(float x, float y, glm::vec3 color) {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_QUADS);
    glVertex2f(x - 2.0f, y - 2.0f);
    glVertex2f(x + 2.0f, y - 2.0f);
    glVertex2f(x + 2.0f, y + 2.0f);
    glVertex2f(x - 2.0f, y + 2.0f);
    glEnd();
}

// Function to draw the radar background
void drawRadarBackground(float radarSize) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-radarSize / 2, -radarSize / 2);
    glVertex2f(radarSize / 2, -radarSize / 2);
    glVertex2f(radarSize / 2, radarSize / 2);
    glVertex2f(-radarSize / 2, radarSize / 2);
    glEnd();
}

// Function to draw an arrow on the radar indicating the player's direction
void drawPlayerArrow(float radarSize, float playerYaw) {
    float arrowLength = 10.0f;
    float yawRad = glm::radians(-playerYaw); // Use negative yaw for correct orientation
    float arrowX = arrowLength * cos(yawRad);
    float arrowY = arrowLength * sin(yawRad);

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(arrowX, arrowY);
    glEnd();
}


