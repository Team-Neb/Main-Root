#include "_npc.h"

_npc::_npc()
{
    //ctor
    xPos = yPos = 0;
    zPos = -5;

    xSize = 0.5;
    ySize = 0.5;

    rotateX = rotateY = rotateZ = 0;

    frames = 1;

    xMin = yMin = 0.0;
    xMax = 1.0/(float)frames;
    yMax = 1;

    // The left and right bounds for this object
    XPOS_MAX = 4.0;
    XPOS_MIN = -4.0;

    action = 0;
    previousAction = 0; // keep track of what the enemy was doing before action got updated

    enemyHealth = 20;   // Player deals 10 damage each strike
    enemyHit = false;

    srand(time(0));     // to truly place enemies randomly


}

_npc::~_npc()
{
    //dtor
}
void _npc::drawEnemy()
{
    glBindTexture(GL_TEXTURE_2D, this->npcTex);

    glPushMatrix();
        glTranslatef(xPos,yPos,zPos);
        glRotatef(rotateX,1.0,0.0,0.0);
        glRotatef(rotateY,0.0,1.0,0.0);
        glRotatef(rotateZ,0.0,0.0,1.0);
        glScalef(xSize,ySize,1);

    glBegin(GL_POLYGON);
        glTexCoord2f(xMin,yMin);
        glVertex3f(1.0, 1.0, -1.0);
        glTexCoord2f(xMax,yMin);
        glVertex3f(-1.0, 1.0, -1.0);
        glTexCoord2f(xMax,yMax);
        glVertex3f(-1.0, -1.0, -1.0);
        glTexCoord2f(xMin,yMax);
        glVertex3f(1.0, -1.0, -1.0);

    glEnd();
    glPopMatrix();
}

void _npc::placeEnemy(float x, float y, float z)
{
    xPos = x;
    yPos = y;
    zPos = z;
}

void _npc::initEnemy(GLuint tex)
{
    this->npcTex = tex;
    TE->start();
}

void _npc::actions(float playerX)
{
    switch(action){

    // MOVE RIGHT
    case 0:
        if(TE->getTicks()>60){
            (this->xPos < XPOS_MAX) ? (this->xPos += 0.02) : (this->action = 1);
            if(!this->enemyHit){
                this->checkCollision(playerX);
            }
            TE->reset();
        }
        drawEnemy();

        break;

    // MOVE LEFT
    case 1:
        if(TE->getTicks()>60){
            (this->xPos > XPOS_MIN) ? (this->xPos -= 0.02) : (this->action = 0);
            if(!this->enemyHit){
                this->checkCollision(playerX);
            }
            TE->reset();
        }
        drawEnemy();

        break;

    case 9: // enemies die

        xMin = 0;
        xMax = 0;
        yMin = 0;
        yMax = 0;
        drawEnemy();
        break;

    // This case is for enemy collision by movement ONLY
    case 10:
        // Enemy looses 15 health per movement collision
        if(this->enemyHealth > 5 && this->enemyHit){
            this->enemyHealth -= 15;
            this->enemyHit = false;

            // After collision make the enemy behave how it originally was
            this->action = this->previousAction;
            this->previousAction = 0;

            // Reposition the enemy after collision by making it bounce away from player
            switch(this->action){
                case 0:
                    this->xPos -= 0.8;
                    break;
                case 1:
                    this->xPos += 0.8;
                    break;
            }
            drawEnemy();

        }else if(this->enemyHealth <= 5 && this->enemyHit){
            this->action = 9;
        }
        else{};
    }
}

bool _npc::getHitStatus()
{
    return enemyHit;
}

int _npc::getHealth()
{
    return enemyHealth;
}

// Based on the direction the enemy is facing/moving towards
// Check the edge of the quad/ hitbox
void _npc::checkCollision(float playerPosX)
{

    //Check right edge of enemy hitbox is inside the hitbox of the player
    if(this->action == 0){
        if( ((this->xPos + 0.25) <= (playerPosX + 1.25)) && ((this->xPos + 0.25) >= (playerPosX) )){
            this->previousAction = this->action;        // save the direction the enemy was walking to
            this->action = 10;                          // give new action to the enemy after movement collision
            this->enemyHit = true;
            cout<<"ENEMY HAS BEEN HIT FROM THE RIGHT EDGE"<<endl;
        }
    // Check left edge
    }else if(this->action == 1){

        if( ((this->xPos) >= (playerPosX)) && ((this->xPos) <= (playerPosX + 1.25)) ){
            this->previousAction = this->action;
            this->action = 10;
            this->enemyHit = true;
            cout<<"ENEMY HAS BEEN HIT FROM THE LEFT EDGE"<<endl;
        }
    }else{}
}


// The sword distance is goes farther out than the xPos of the player
// so check player xPos + swordDistance
// sword distance extends hitbox of the player by 0.15 in either the left or right direction
// depending on player direction
void _npc::swordCollisionCheck(float playerPosX, int direction)
{
    switch(direction){
        case -1:
            if( (this->xPos + 0.25) <= (playerPosX + 0.75) && (this->xPos + 0.25) >= (playerPosX - 0.15)){
                this->action = 9;
            }
            break;
        case 1:
            if( (this->xPos) >= (playerPosX + 0.75) && (this->xPos) <= (playerPosX + 1.4) ) {
                this->action = 9;
            }
            break;
        default:
            break;
    }
}


// Places an enemy randomly on the x-axis of the screen.
void _npc::placeEnemyRandom()
{
    int temp = rand() % 2;
    int newPosition = (float)(rand() % (int)XPOS_MAX) + 1.5;

    (temp == 0) ? (this->xPos = -newPosition) : (this->xPos = newPosition); // place randomly on left or right side of player
    (temp == 0) ? (this->action = 0) : (this->action = 1);
    this->yPos = -1.45;
    this->zPos = -5.0;
}



