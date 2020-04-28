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


    XPOS_MAX = 2;    // The left and right bounds for this object
    XPOS_MIN = -2;
    action = 0;
    enemyHealth = 20;   // Player deals 10 damage each strike
    enemyHit = false;
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
        if(this->enemyHealth > 5 && this->enemyHit){
            this->enemyHealth -= 15;
            this->enemyHit = false;
            this->action = 0;
            drawEnemy();

        }else if(this->enemyHealth <= 5 && this->enemyHit){
            xMin = 0;
            xMax = 0;
            yMin = 0;
            yMax = 0;
            drawEnemy();
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


void _npc::checkCollision(float playerPosX)
{
    // Based on the direction the enemy is facing/moving towards
    // Check the edge of the quad/ hitbox

    //Check right edge
    if(this->action == 0){
        if( ((this->xPos + 0.01) <= (playerPosX + 0.01)) && ((this->xPos + 0.01) >= (playerPosX - 0.01) )){
            this->action = 10;
            this->enemyHit = true;
            cout<<"ENEMY HAS BEEN HIT FROM THE RIGHT EDGE"<<endl;
            //cout<<"playerPosX: "<<playerPosX<<endl;
            //cout<<"enemyPosX: "<<this->xPos<<endl;
        }
    // Check left edge
    }else if(this->action == 1){
        // The higher the number is - the farther the enemy object will be before being "deleted"
        // The lower the number is - the closer the enemy object will be before being "deleted"
        if( ((this->xPos - 0.55) >= (playerPosX - 0.55)) && ((this->xPos - 0.55) <= (playerPosX + 0.55)) ){
            this->action = 10;
            this->enemyHit = true;
            //cout<<"playerPosX: "<<playerPosX<<endl;
            //cout<<"enemyPosX: "<<this->xPos<<endl;
            cout<<"ENEMY HAS BEEN HIT FROM THE LEFT EDGE"<<endl;
        }
    }else{}
}


// The sword distance is goes farther out than the xPos of the player
// so check player xPos + swordDistance
void _npc::swordCollisionCheck(float playerPosX, int direction)
{

    switch(direction){
        case -1:
            if( (this->xPos + 0.01) <= (playerPosX + 0.01) && (this->xPos + 0.01) >= (playerPosX - 0.3)){
                this->action = 9;
                this->enemyHit = true;
            }
            break;
        case 1:
            if( (this->xPos) >= (playerPosX + 0.75) && (this->xPos) <= (playerPosX + 1.4) ) {
                this->action = 9;
                this->enemyHit = true;
            }
            break;
        default:
            break;
    }
}






