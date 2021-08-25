#include "GraphicsEngine.h"
#include "GameObjectFactory.h"
#include <iostream>
#include "Color.h"
#include "CCameraComponent.h"
#include "SkyboxVerts.h"

GraphicsEngine::GraphicsEngine()
	:m_window{ nullptr },
	m_renderer{ nullptr },
	m_glContext{ nullptr },
	m_camera{ nullptr },
	m_graphLib{ GraphicsLibrary::OPENGL },
	m_textureIDs{},
	m_skyboxInitialized{ false },
	m_skyboxTextures{}
{
}

GraphicsEngine* GraphicsEngine::instance() 
{
	static GraphicsEngine* engine = new GraphicsEngine();
	return engine;
}

bool GraphicsEngine::initialise(GraphicsLibrary renderer) 
{
	switch (renderer)
	{
	case GraphicsLibrary::OPENGL:
		return InitOpenGL();
	case GraphicsLibrary::DIRECTX:
		return InitDirectX();
	default:
		return false;
	}
}

bool GraphicsEngine::initLighting()
{
	glDisable(GL_LIGHTING);
	return true;
	//return InitOpenGLlighting();
}

void GraphicsEngine::GenMultiTexture(std::string tex1Key, std::string tex2Key)
{
	/*m_glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textureIDs.at(tex1Key));
	m_glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textureIDs.at(tex2Key));*/
}

void GraphicsEngine::UpdateSpotlight(const CSpotlight * light)
{
	/*glEnable(GL_LIGHT1);

	GLfloat lightPosition[] = { light->GetTransformConst().GetPosition().GetX() ,
								light->GetTransformConst().GetPosition().GetY() ,
								light->GetTransformConst().GetPosition().GetZ() };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
	GLfloat lightDirection[] = { light->GetTransformConst().GetRotation().GetX() ,
								light->GetTransformConst().GetRotation().GetY() ,
								light->GetTransformConst().GetRotation().GetZ() };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDirection);
	float f = (*light->GetColour())[0];
	GLfloat lightDiffuse[] = { (*light->GetColour())[0] ,
								(*light->GetColour())[1] ,
								(*light->GetColour())[2] };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);*/
	


}


void GraphicsEngine::newFrame() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	/*if (m_camera != nullptr) 
	{
		gluLookAt(
			m_camera->GetTransform().GetWorldTransform().GetPosition().GetX(), 
			m_camera->GetTransform().GetWorldTransform().GetPosition().GetY(), 
			m_camera->GetTransform().GetWorldTransform().GetPosition().GetZ(),
			(double)m_camera->GetTransform().GetWorldTransform().GetPosition().GetX() + m_camera->GetTransform().GetWorldTransform().GetForward().GetX(),
			(double)m_camera->GetTransform().GetWorldTransform().GetPosition().GetY() + m_camera->GetTransform().GetWorldTransform().GetForward().GetY(),
			(double)m_camera->GetTransform().GetWorldTransform().GetPosition().GetZ() + m_camera->GetTransform().GetWorldTransform().GetForward().GetZ(),
			(double)m_camera->GetTransform().GetWorldTransform().GetUp().GetX(),
			(double)m_camera->GetTransform().GetWorldTransform().GetUp().GetY(),
			(double)m_camera->GetTransform().GetWorldTransform().GetUp().GetZ()
		);
	}
	else 
	{
		gluLookAt(0, 0, 5, 0, 0, -1, 0, 1, 0); // DEBUG
	}*/

	// world axis debug
	//glPushMatrix();
	//glTranslatef(512, 250, 512);
	//glColor3f(1, 0, 0);
	//glBegin(GL_LINES);
	//glVertex3f(0, 0, 0);
	//glVertex3f(1000,0,0);
	//glColor3f(0, 0, 1);
	//glVertex3f(0, 0, 0);
	//glVertex3f(0, 0, 1000);
	//glEnd();
	//glPopMatrix();

	RenderSkybox();
}

void GraphicsEngine::renderObjects() {
	GameObjectFactory::instance()->render();
}

void GraphicsEngine::endFrame() {
	SDL_GL_SwapWindow(m_window);
}

void GraphicsEngine::SetDisplayCamera(CCamera* camera) 
{
	m_camera = camera;
}

CCamera* GraphicsEngine::GetDisplayCamera() 
{
	return m_camera;
}

void GraphicsEngine::GenerateTexture(std::string key, unsigned char* image, int width, int height)
{
	switch (m_graphLib)
	{
	case GraphicsLibrary::OPENGL:
		GenOpenGLTexture(image, width, height, key);
		break;
	case GraphicsLibrary::DIRECTX:
		// out of scope for ICT397
		break;
	}
}

void GraphicsEngine::DeleteTexture(std::string key)
{
	if (m_textureIDs.find(key) == m_textureIDs.end())
	{
		return;
	}

	unsigned int texId[] = { m_textureIDs.at(key) };
	glDeleteTextures(1, texId);
}

void GraphicsEngine::DrawModel(Model* model, const Transform& worldTrans) const // NOTE keep these commented out statements, we will need them for texturing
{
	if (!model)
	{
		return;
	}
	
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	shader->useShaderForLoop();
	glm::mat4 projection = glm::perspective(m_camera->GetCamera().FOV, 1.0f, m_camera->GetCamera().NearClip, m_camera->GetCamera().FarClip);
	shader->setMat4("projection", projection);

	glm::mat4 view = glm::lookAt(glm::vec3(m_camera->GetTransform().GetWorldTransform().GetPosition().GetX(), m_camera->GetTransform().GetWorldTransform().GetPosition().GetY(), m_camera->GetTransform().GetWorldTransform().GetPosition().GetZ()), 
	glm::vec3(m_camera->GetTransform().GetWorldTransform().GetPosition().GetX(), m_camera->GetTransform().GetWorldTransform().GetPosition().GetY(), m_camera->GetTransform().GetWorldTransform().GetPosition().GetZ()) + glm::vec3(m_camera->GetTransform().GetWorldTransform().GetForward().GetX(), m_camera->GetTransform().GetWorldTransform().GetForward().GetY(), m_camera->GetTransform().GetWorldTransform().GetForward().GetZ()), 
	glm::vec3(m_camera->GetTransform().GetWorldTransform().GetUp().GetX(), m_camera->GetTransform().GetWorldTransform().GetUp().GetY(), m_camera->GetTransform().GetWorldTransform().GetUp().GetZ()));
	
	shader->setMat4("view", view);
	
	glm::mat4 trans = glm::mat4(1.0f);
	
	glm::mat4 translation = glm::translate(trans, glm::vec3(worldTrans.GetPosition().GetX(), worldTrans.GetPosition().GetY(), worldTrans.GetPosition().GetZ()));

	glm::mat4 rotX = glm::rotate(trans, worldTrans.GetRotation().GetX(), glm::vec3(1.0f, 0.0f, 0.0));
	glm::mat4 rotY = glm::rotate(trans, worldTrans.GetRotation().GetY(), glm::vec3(0.0, 1.0f, 0.0));
	glm::mat4 rotZ = glm::rotate(trans, worldTrans.GetRotation().GetZ(), glm::vec3(0.0, 0.0f, 1.0f));
	

	glm::mat4 scale = glm::scale(trans, glm::vec3(worldTrans.GetScale().GetX(), worldTrans.GetScale().GetY(), worldTrans.GetScale().GetZ()));
	
	trans = translation * (rotX * rotY * rotZ) * scale;

	shader->setMat4("transform", trans);
	model->Draw(*shader);
	
	/* draw debug */
	//COLLISION->debugRender->getLinesArray()[0].point1.z;
	


}

void GraphicsEngine::DrawModelMovingTexture(Model* model, const Transform& worldTrans, const float texOffset) const // NOTE keep these commented out statements, we will need them for texturing
{
	/*if (!model)
	{
		return;
	}
	shader->useShaderForLoop();
	glm::mat4 projection = glm::perspective(m_camera->GetCamera().FOV, 1.0f, m_camera->GetCamera().NearClip, m_camera->GetCamera().FarClip);
	shader->setMat4("projection", projection);

	glm::mat4 view = glm::lookAt(glm::vec3(m_camera->GetTransform().GetWorldTransform().GetPosition().GetX(), m_camera->GetTransform().GetWorldTransform().GetPosition().GetY(), m_camera->GetTransform().GetWorldTransform().GetPosition().GetZ()),
	glm::vec3(m_camera->GetTransform().GetWorldTransform().GetPosition().GetX(), m_camera->GetTransform().GetWorldTransform().GetPosition().GetY(), m_camera->GetTransform().GetWorldTransform().GetPosition().GetZ()) + glm::vec3(m_camera->GetTransform().GetWorldTransform().GetForward().GetX(), m_camera->GetTransform().GetWorldTransform().GetForward().GetY(), m_camera->GetTransform().GetWorldTransform().GetForward().GetZ()),
	glm::vec3(m_camera->GetTransform().GetWorldTransform().GetUp().GetX(), m_camera->GetTransform().GetWorldTransform().GetUp().GetY(), m_camera->GetTransform().GetWorldTransform().GetUp().GetZ()));

	shader->setMat4("view", view);

	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 translation = glm::translate(trans, glm::vec3(worldTrans.GetPosition().GetX(), worldTrans.GetPosition().GetY(), worldTrans.GetPosition().GetZ()));

	glm::mat4 rotX = glm::rotate(trans, worldTrans.GetRotation().GetX(), glm::vec3(1.0f, 0.0f, 0.0));
	glm::mat4 rotY = glm::rotate(trans, worldTrans.GetRotation().GetY(), glm::vec3(0.0, 1.0f, 0.0));
	glm::mat4 rotZ = glm::rotate(trans, worldTrans.GetRotation().GetZ(), glm::vec3(0.0, 0.0f, 1.0f));


	glm::mat4 scale = glm::scale(trans, glm::vec3(worldTrans.GetScale().GetX(), worldTrans.GetScale().GetY(), worldTrans.GetScale().GetZ()));

	trans = translation * (rotX * rotY * rotZ) * scale;

	shader->setMat4("transform", trans);
	model->Draw(*shader);*/
	/*
	glPushMatrix();
	OpenGLTransformation(worldTrans);
	if (model->TextureKey != "NULL")
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_textureIDs.at(model->TextureKey));
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}
	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < model->NumFaces; i++)
	{
		glTexCoord2f(model->texverts[model->texfaces[i].GetX()].GetX(), model->texverts[model->texfaces[i].GetX()].GetY());
		glVertex3f(
			model->verts[model->faces[i].GetX()].GetX() + texOffset,
			model->verts[model->faces[i].GetX()].GetY(),
			model->verts[model->faces[i].GetX()].GetZ()

		);
		glTexCoord2f(model->texverts[model->texfaces[i].GetY()].GetX(), model->texverts[model->texfaces[i].GetY()].GetY());
		glVertex3f(
			model->verts[model->faces[i].GetY()].GetX() + texOffset,
			model->verts[model->faces[i].GetY()].GetY(),
			model->verts[model->faces[i].GetY()].GetZ()
		);
		glTexCoord2f(model->texverts[model->texfaces[i].GetZ()].GetX(), model->texverts[model->texfaces[i].GetZ()].GetY());
		glVertex3f(
			model->verts[model->faces[i].GetZ()].GetX() + texOffset,
			model->verts[model->faces[i].GetZ()].GetY(),
			model->verts[model->faces[i].GetZ()].GetZ()
		);
	}
	glEnd();
	glPopMatrix();*/
}

void GraphicsEngine::DrawTerrain()
{
	glCallList(1);
}

void GraphicsEngine::GenDisplayListTerrain(CBaseTerrain* terrain, bool withTexture, bool asWireframe)
{
	/*const unsigned DETAIL_MAP_REPEAT = 256;
	const unsigned TERRAIN_REPEAT = 1;

	if (!terrain->HasTerrainData())
	{
		return;
	}

	glNewList(1, GL_COMPILE);
	unsigned char hcolour; // colour of the height
	float texLeft, texBottom, texTop;

	if (asWireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	m_glActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D, m_textureIDs.at(terrain->GetTextureKey()));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	m_glActiveTextureARB(GL_TEXTURE1_ARB);
	if (!terrain->GetDetailMapKey().empty())
	{
		glBindTexture(GL_TEXTURE_2D, m_textureIDs.at(terrain->GetDetailMapKey()));
	}
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	glPushMatrix();
	// looping though the z axis
	for (unsigned int z = 0; z < terrain->GetSize() - 1; z++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (unsigned int x = 0; x < terrain->GetSize(); x++)
		{
			texLeft = (float)x / terrain->GetSize();
			texBottom = (float)z / terrain->GetSize();
			texTop = (float)(z + 1) / terrain->GetSize();

			// create the first point in the triangle strip
			hcolour = terrain->GetUnscaledHeightColour(x, z);
			glColor3ub(hcolour, hcolour, hcolour);
			m_glMultiTexCoord2fARB(GL_TEXTURE0_ARB, texLeft * TERRAIN_REPEAT, texBottom * TERRAIN_REPEAT);
			m_glMultiTexCoord2fARB(GL_TEXTURE1_ARB, texLeft * DETAIL_MAP_REPEAT, texBottom * DETAIL_MAP_REPEAT);
			glVertex3f(
				x * terrain->GetTransform().GetScale().GetX(),
				(int)terrain->GetUnscaledHeightColour(x, z) * terrain->GetTransform().GetScale().GetY(),
				z * terrain->GetTransform().GetScale().GetZ()
			);
			hcolour = terrain->GetUnscaledHeightColour(x, z + 1);
			glColor3ub(hcolour, hcolour, hcolour);
			m_glMultiTexCoord2fARB(GL_TEXTURE0_ARB, texLeft * TERRAIN_REPEAT, texTop * TERRAIN_REPEAT);
			m_glMultiTexCoord2fARB(GL_TEXTURE1_ARB, texLeft * DETAIL_MAP_REPEAT, texTop * DETAIL_MAP_REPEAT);
			glVertex3f(
				x * terrain->GetTransform().GetScale().GetX(),
				(int)terrain->GetUnscaledHeightColour(x, z + 1) * terrain->GetTransform().GetScale().GetY(),
				(z + 1) * terrain->GetTransform().GetScale().GetZ()
			);
		}
		glEnd();
	}

	m_glActiveTextureARB(GL_TEXTURE0_ARB);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPopMatrix();
	glEndList();*/
}

void GraphicsEngine::DrawGrid(float gridHeight, float lineThickness, float gridWidth, float cellWidth)
{
	/*glDisable(GL_TEXTURE_2D);
	glColor3dv(Colour::purple);

	for (float i = -gridWidth * 0.5f; i < gridWidth; i += cellWidth * 0.5f)
	{
		for (float j = -gridWidth * 0.5f; j < gridWidth; j += cellWidth * 0.5f)
		{
			glBegin(GL_LINE_LOOP);
			glVertex3f(i - 1, gridHeight, j - 1);
			glVertex3f(i - 1, gridHeight, j);
			glVertex3f(i, gridHeight, j);
			glVertex3f(i, gridHeight, j - 1);
			glEnd();
		}
	}*/
}

void GraphicsEngine::DrawImage(std::string key, int width, int height, int posX, int posY)
{
	/*int w, h;
	SDL_GetWindowSize(m_window, &w, &h);

	// TODO take params to set position. atm assume centre screen
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluOrtho2D(-(w/2), w/2, -(h / 2), h / 2);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	int topLeftX = -(w / 2);
	int topLeftY = (h / 2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textureIDs.at(key));
	glBegin(GL_QUADS);
		glTexCoord2i(1, 0);
		glVertex2f(topLeftX + posX, topLeftY - posY);

		glTexCoord2i(1, 1);
		glVertex2f(topLeftX + posX, topLeftY - height - posY);

		glTexCoord2i(0, 1);
		glVertex2f(topLeftX + width + posX, topLeftY - height - posY);

		glTexCoord2i(0, 0);
		glVertex2f(topLeftX + width + posX, topLeftY - posY);
	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();*/
}

unsigned GraphicsEngine::GetTexID(std::string key) const
{
	return m_textureIDs.at(key);
}


void GraphicsEngine::GetScreenSize(int& w, int& h)
{
	int wBuf, hBuf;
	SDL_GetWindowSize(m_window, &wBuf, &hBuf);
	w = wBuf;
	h = hBuf;
}

void GraphicsEngine::InitSkybox(std::string negx, std::string negy, std::string negz, std::string posx, std::string posy, std::string posz)
{

}

void GraphicsEngine::RenderSkybox()
{
	/*const float SCALE = 20000;
	glColor3f(0, 1, 0);
	glDisable(GL_FOG);
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(
		m_camera->GetTransform().GetWorldTransform().GetPosition().GetX(),
		m_camera->GetTransform().GetWorldTransform().GetPosition().GetY(),
		m_camera->GetTransform().GetWorldTransform().GetPosition().GetZ()
	);

	int i = 0;
	int j = 0;
	do
	{
		glBindTexture(GL_TEXTURE_2D, m_textureIDs.at(m_skyboxTextures[j++]));
		glBegin(GL_QUADS);
			glTexCoord2i(0, 0);
			glVertex3f(
				skyboxVertices[i++] * SCALE, 
				skyboxVertices[i++] * SCALE,
				skyboxVertices[i++] * SCALE
			);

			glTexCoord2i(1, 0);
			glVertex3f(
				skyboxVertices[i++] * SCALE,
				skyboxVertices[i++] * SCALE,
				skyboxVertices[i++] * SCALE
			);

			glTexCoord2i(1, 1);
			glVertex3f(
				skyboxVertices[i++] * SCALE,
				skyboxVertices[i++] * SCALE,
				skyboxVertices[i++] * SCALE
			);

			glTexCoord2i(0, 1);
			glVertex3f(
				skyboxVertices[i++] * SCALE,
				skyboxVertices[i++] * SCALE,
				skyboxVertices[i++] * SCALE
			);
		glEnd();
	} 	while (i < 3 * 4 * 6);

	glPopMatrix();

	glEnable(GL_FOG);*/
}

bool GraphicsEngine::InitOpenGL()
{
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	if ((m_window = SDL_CreateWindow("ICT397 - Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 700, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)) == nullptr)
	{
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if ((m_glContext = SDL_GL_CreateContext(m_window)) == nullptr)
	{
		std::cout << "OpenGL Context could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_GL_SetSwapInterval(0);
	glEnable(GL_DEPTH_TEST);

	shader = new Shader("../ICT397-GameEngine/ModernOpenGL/vertexShader.vs", "../ICT397-GameEngine/ModernOpenGL/colourShader.fs");

	return true;
}

bool GraphicsEngine::InitOpenGLlighting()
{

	/*// fog
	glEnable(GL_FOG);
	glFogf(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_DENSITY, 0.01f);
	glFogf(GL_FOG_START, 100);
	glFogf(GL_FOG_END, 300);
	glFogf(GL_FOG_INDEX, 0);
	glFogfv(GL_FOG_COLOR, new GLfloat[4]{ 0.1f, 0.1f, 0.1f, 0.1f });


	//this material makes everythign too bright???
	////start material
	//glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
	//GLfloat mat_specular[] = { 0.05f, 0.05f, 0.05f, 1 };
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//GLfloat mat_emission[] = { 0.01f, 0.01f, 0.01f, 1 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
	//GLfloat mat_shininess[] = { 128 };
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	////end material



	GLfloat globalAmbient[] = { 0.01f, 0.01f, 0.01f, 0.1f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	
	//Start Ambient
	GLfloat ambientLight[] = { 0.6f, 0.5f, 0.4f, 1.5f };
	GLfloat diffuseLight[] = {0.01f, 0.01f, 0.01f, 0.01f };
	GLfloat specularLight[] = { 0.05f, 0.01f, 0.01f, 0.01f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	//set ambient light position
	GLfloat lightPosition[] = { 550, 250, 550, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	//set Ambient light intensity & colour
	glEnable(GL_LIGHT0);

	/////End Ambient

	//this spotlight shit needs to be moved
	//start spotlight
	//glEnable(GL_LIGHT1);

	GLfloat spotlightPosition1[] = { 560, 140, 510, 1.0 };
	GLfloat spotAmbientLight[] = { 1, 1, 1, 1.0 };
	GLfloat spotDiffuseLight[] = { 1, 1, 1, 1.0 };
	GLfloat spotSpecularLight[] = { 0.75, 0.75, 0.75, 1.0 };
	GLfloat spotDirection[] = { 1,-1,0 };
	GLfloat spotExponent = .1f;
	GLfloat spotCutoff = 30;
	GLfloat constantAttenuation = 0.01f;
	GLfloat linearAttenuation = 0.005f;
	GLfloat quadraticAttenuation = 0.001f;

	glLightfv(GL_LIGHT1, GL_AMBIENT, spotAmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, spotDiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spotSpecularLight);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, constantAttenuation);
	//glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, linearAttenuation);
	//glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
	glLightfv(GL_LIGHT1, GL_POSITION, spotlightPosition1);

	//end spotlight*/
	
	return true;
}



bool GraphicsEngine::InitDirectX()
{
	// out of scope for ICT397
	return false;
}

void GraphicsEngine::GenOpenGLTexture(unsigned char* image, int width, int height, std::string key)
{
	/*unsigned texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	int mipMapError =	gluBuild2DMipmaps(
							GL_TEXTURE_2D, 
							GL_RGBA,     
							width,
							height,       
							GL_RGBA,     
							GL_UNSIGNED_BYTE,
							image
						);
	if (mipMapError != 0)
	{
		throw "gluBuild2DMipmaps error";
	}

	m_textureIDs.emplace(key, texID);*/
}

void GraphicsEngine::OpenGLTransformation(const Transform& t) const
{
	Vector3f euler = t.GetRotation().GetAxis();
	glTranslatef(t.GetPosition().GetX(), t.GetPosition().GetY(), t.GetPosition().GetZ());
	//glRotatef(t.GetRotation().GetAngleDegrees(), euler.GetX(), euler.GetY(), euler.GetZ());
	glMultMatrixf((Matrix4f::Cast(t.GetRotation().Conjugate())).GetTypePtr());
	glScalef(t.GetScale().GetX(), t.GetScale().GetY(), t.GetScale().GetZ());
}

void GraphicsEngine::DrawCollider(float maxX, float maxY, float maxZ, float minX, float minY, float minZ, const Transform& worldT)
{
	/*glPushMatrix();
	glTranslatef(worldT.GetPosition().GetX(), worldT.GetPosition().GetY(), worldT.GetPosition().GetZ());
	glScalef(worldT.GetScale().GetX(), worldT.GetScale().GetY(), worldT.GetScale().GetZ());
	glDisable(GL_TEXTURE_2D);
	glColor3dv(Colour::green);
	glColor3dv(Colour::lightgreen);
	glLineWidth(4);

	glBegin(GL_LINE_LOOP);
	glVertex3f(minX, minY, minZ);
	glVertex3f(minX, minY, maxZ);
	glVertex3f(minX, maxY, maxZ);
	glVertex3f(minX, maxY, minZ);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(maxX, maxY, maxZ);
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(maxX, minY, minZ);
	glVertex3f(maxX, minY, maxZ);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(maxX, maxY, maxZ);
	glVertex3f(minX, maxY, maxZ);

	glVertex3f(minX, minY, minZ);
	glVertex3f(maxX, minY, minZ);

	glVertex3f(minX, maxY, minZ);
	glVertex3f(maxX, maxY, minZ);

	glVertex3f(maxX, minY, maxZ);
	glVertex3f(minX, minY, maxZ);
	glEnd();
	glPopMatrix();*/
}