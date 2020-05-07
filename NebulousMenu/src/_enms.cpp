#include "_enms.h"

_enms::_enms()
{
    //ctor
    xPos = yPos = 0;
    zPos = -1;

    xSize = 1;
    ySize = 1;

    rotateX = rotateY = rotateZ = 0;

    frames = 7;

    xMin = yMin = 0.0;
    xMax = 1.0/(float)frames;
    yMax = 0.5;
    action = 0;
    xMove = 0.005;
    enemyFacing = NULL;


    enemyHealth = 20;   // Player deals 10 damage each strike
    enemyHit = false;

}

_enms::~_enms()
{
    //dtor
}
void _enms::drawEnemy(){
    glBindTexture(GL_TEXTURE_2D, EnemyTex);

    glPushMatrix();
        glTranslatef(xPos,yPos,zPos);
        glRotatef(rotateX,1.0,0.0,0.0);
        glRotatef(rotateY,0.0,1.0,0.0);
        glRotatef(rotateZ,0.0,0.0,1.0);
        glScalef(xSize,ySize,1);

    glBegin(GL_POLYGON);
        glTexCoord2f(xMin,yMin);
        glVertex3f(1.0, 1.0, 0.0);
        glTexCoord2f(xMax,yMin);
        glVertex3f(-1.0, 1.0, 0.0);
        glTexCoord2f(xMax,yMax);
        glVertex3f(-1.0, -1.0, 0.0);
        glTexCoord2f(xMin,yMax);
        glVertex3f(1.0, -1.0, 0.0);

    glEnd();
    glPopMatrix();

}

void _enms::placeEnemy(float x, float y, float z){
    xPos = x;
    yPos = y;
    zPos = z;
}

void _enms::initEnemy(GLuint tex){

    EnemyTex = tex;
    TE->start();

}

void _enms::actions(){
    switch(action){
    case 0:
        if(TE->getTicks()>60){
            xMin += 1.0/frames;
            xMax += 1.0/frames;
            yMin = 0.5;
            yMax = 1.0;

            if(xMax >= 1){
                xMin = 0;
                xMax = 1.0/frames;
                TE->reset();
            }
        }
        drawEnemy();

        break;

    case 1:
        if(TE->getTicks()>60){
            xMin += 1.0/frames;
            xMax += 1.0/frames;
            yMin = 0.0;
            yMax = 0.5;

            if(xMax >= 1){
                xMin = 0;
                xMax = 1.0/frames;
                TE->reset();
            }
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
    }

}

bool _enms::isEnemyLive(){

}
bool _enms::getHitStatus()
{
    return enemyHit;
}

int _enms::getHealth()
{
    return enemyHealth;
}
void _enms::updateEnemy()
{

}
