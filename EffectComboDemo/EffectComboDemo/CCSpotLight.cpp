#include "CCSpotLight.h"

CCSpotLight::CCSpotLight(void)
{
}

CCSpotLight::~CCSpotLight(void)
{
}

CCSpotLight* CCSpotLight::initSpotLight(CCRenderTexture* texture,
                                        float radius,
                                        ccColor4B color,
                                        CCPoint pt)
{
	CCSpotLight* spotLight = new CCSpotLight();
    spotLight->renderTexture = texture;
    spotLight->spotLightRadius = radius;
    spotLight->renderColor = color;
    spotLight->setPosition(pt);
    
	return spotLight;
}

void CCSpotLight::spreadOutAndRemove()
{
    schedule( schedule_selector(CCSpotLight::spreadOutTimer));
}

void CCSpotLight::spreadOutTimer()
{
    this->spotLightRadius += 3.5f;
    
    if(this->spotLightRadius > 300)
    {
        unschedule(schedule_selector(CCSpotLight::spreadOutTimer));
        unschedule(schedule_selector(CCSpotLight::tick));
        this->renderTexture->removeFromParentAndCleanup(true);
        this->removeFromParentAndCleanup(true);
    }
}


void CCSpotLight::runSpotEffect()
{
    schedule( schedule_selector(CCSpotLight::tick));
}

void CCSpotLight::tick(ccTime delta)
{
    int segs = 45;
	GLfloat *vertices = (GLfloat *)malloc( sizeof(GLfloat)*2*(segs));
	GLfloat *coordinates = (GLfloat *)malloc( sizeof(GLfloat)*2*(segs));
	ccColor4B *colors = (ccColor4B *)malloc( sizeof(ccColor4B)*(segs));
	
	memset(vertices,0, sizeof(GLfloat)*2*(segs));
	memset(coordinates,0, sizeof(GLfloat)*2*(segs));
	
    this->renderTexture->clear(this->renderColor.r, 
                               this->renderColor.g, 
                               this->renderColor.b, 
                               this->renderColor.a);
	
	colors[0] = ccc4(0, 0, 0, 255);
	for (int i = 1; i < segs; i++)
	{
		colors[i] = ccc4(0, 0, 0, 0);
	}
	
	const float coef = 2.0f * (float)M_PI/(segs-2) ;
	
	vertices[0] = this->getPositionX();
	vertices[1] = this->getPositionY();
	coordinates[0] = this->getPositionX();
	coordinates[1] = (this->getContentSize().height-this->getPositionY());
    
	for(int i=1;i<=segs;i++)
	{
		float rads = i*coef;
		float j = this->spotLightRadius * cosf(rads) + this->getPositionX();
		float k = this->spotLightRadius * sinf(rads) + this->getPositionY();
		
		vertices[i*2] = j;
		vertices[i*2+1] = k;
		
		coordinates[i*2] = (j);
		coordinates[i*2+1] = (this->getContentSize().height-k);
	}
    
    // Update the render texture
    this->renderTexture->begin();
	
    glBindTexture(GL_TEXTURE_2D, (GLuint)this->renderTexture);
	glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
	glColorMask(0.0f, 0.0f, 0.0f, 1.0f);
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, coordinates);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);
    
	glDrawArrays(GL_TRIANGLE_FAN, 0, segs);
	
	glColorMask(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	
    this->renderTexture->end();
	
	free(vertices);
	free(coordinates);
	free(colors);
} 