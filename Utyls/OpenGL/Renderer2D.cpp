#include "Renderer2D.h"
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <iostream>
#include "..\..\Commons.h"
//#include <algorithm>
//#include <ft2build.h>
//#include "..\..\LogFile.h"
//#include FT_FREETYPE_H  

constexpr bool VertexSpriteInfo::operator==(const VertexSpriteInfo& sample) {
	return this->x == sample.x &&
		this->y == sample.y&&
		this->u == sample.u&&
		this->v == sample.v&&
		this->tx == sample.tx&&
		this->ty == sample.ty&&
		this->qx == sample.qx&&
		this->qy == sample.qy&&
		this->sx == sample.sx&&
		this->sy == sample.sy&&
		this->dir == sample.dir&&
		this->layer == sample.layer &&
		this->ah == sample.ah &&
		this->av == sample.av &&
		this->r ==  sample.r &&
		this->g ==  sample.g &&
		this->b ==  sample.b &&
		this->a ==  sample.a ;
}

//Constructor
Renderer2D::Renderer2D() {

}

Renderer2D::Renderer2D(GLFWwindow* win) : m_pWin(win), m_pTriangles(nullptr), m_pIndices(nullptr) {

}


Renderer2D::~Renderer2D() {
	cleanUp();
	//sf::Shader::bind(NULL);
}


void Renderer2D::configureRenderer() {
	const int mem_alloc = 4 * ENEMY_MAX * sizeof(VertexSpriteInfo);//sizeof(SpriteBatchInfo);
	const int mem_index = 6 * ENEMY_MAX * sizeof(GLuint);//sizeof(SpriteBatchInfo);
	/*FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library.\n";
	}

	FT_Face face;
	if (FT_New_Face(ft, "resource/arial.ttf", 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font.\n";
	}*/
	this->m_AuxSprite.obj.configureArray(&this->m_AuxSprite.triangles->x, 4 * sizeof(VertexSpriteInfo), CLB_GL_2D);
	this->m_AuxSprite.obj.configureIndex(this->m_AuxSprite.indices, sizeof(GLuint) * 6);

	bool flag = false;
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << "line" << (__LINE__) << "\n";
	}
		this->m_pTriangles = (VertexSpriteInfo*)malloc(mem_alloc);
		this->m_pIndices = (GLuint*)std::malloc(mem_index);
		for (int j = 0; j < ENEMY_MAX; j++) {
			const int ind = j << 2;
			const int ind2 = j * 6;
			this->m_pIndices[ind2] = ind;
			this->m_pIndices[ind2 + 1] = ind + 1;
			this->m_pIndices[ind2 + 2] = ind + 3;
			this->m_pIndices[ind2 + 3] = ind + 1;
			this->m_pIndices[ind2 + 4] = ind + 3;
			this->m_pIndices[ind2 + 5] = ind + 2;
		}
		this->m_GLObject.configureArray(&this->m_pTriangles[0].x, mem_alloc, CLB_GL_2D);
		this->m_GLObject.configureIndex(this->m_pIndices, 4 * 6 * ENEMY_MAX);
}

//I'll only use the Vertex and Fragment shader...
//2023/05/05 - Gonna add the Geometry Shader.
//2023/05/08 - Removed Geometry Shader.
void Renderer2D::InitShader(std::string vert, std::string frag) {
	//Shader setup
	this->m_RenderShader.loadFromFile(vert, frag);
	this->m_RenderShader.useProgram();
	glm::mat4 Proj(1.0);
	Proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
	this->m_RenderShader.setUniform("camMat", Proj);
}

//2023/05/10 - Changed the way this thing sends info to the vertex shader
//2023/07/01 - Ditched unused old draw function
//void Renderer2D::draw(int slot, int quad, const SpriteBatchInfo& info)


//2023/05/11 - Receives a list with elements to draw, discards if triangles are similar.
//2023/06/29 - Sorting all the elements to draw layer by layer
//2023/06/30 - Reverted changes
//void Renderer2D::draw(std::map<int, std::vector<SpriteBatchInfo>>& drawList, uint32_t tm) {
void Renderer2D::draw(LayeredSpritebatch& drawList, uint32_t tm) {
	glDisable(GL_DEPTH_TEST);
	AnimeSlot* pSlot;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	this->m_RenderShader.useProgram();
#ifdef _DEBUG
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
	}
#endif
	this->m_RenderShader.setUniform("intime", ((float)tm));
#ifdef _DEBUG
	while (GLenum err = glGetError()) {
		std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
	}
#endif
	float overAll = 0.0;
	for (auto& layer : drawList) {
		auto& realLayer = layer.second;
		//std::sort(realLayer.begin(), realLayer.end(),
		//	[](const SpriteBatchInfo& a, const SpriteBatchInfo& b) {
		//		return a.texslot < b.texslot;
		//	});
		int y = 0;
		const size_t size = realLayer.size();
		
			int slot = realLayer.begin()->texslot;
			for (auto x = realLayer.begin(); x != realLayer.end();) {
				int cont = 0;
				pSlot = &this->m_Anim.m_AnimeArr[slot];
				glm::vec2 texsize = this->m_Textures[pSlot->texId].getSize();
				this->m_RenderShader.setUniform("quad", texsize);
#ifdef _DEBUG
				while (GLenum err = glGetError()) {
					std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
				}
#endif
				//drawCnt = drawList[slot].m_Size;
				// 
				// 
				// Normal
				//glBlendEquation(GL_FUNC_ADD);
				//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
				//Add
				//glBlendEquation(GL_FUNC_ADD);
				//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				//glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
				//glBlendEquation(GL_FUNC_ADD);
				this->m_GLObject.bind();
#ifdef _DEBUG
				while (GLenum err = glGetError()) {
					std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
				}
#endif
				VertexSpriteInfo* receive = (VertexSpriteInfo*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
#ifdef _DEBUG
				while (GLenum err = glGetError()) {
					std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
				}
#endif
				int j = 0;
				int temp = 0;
				int clamp = size - y;
				for (; j < clamp; j++, overAll++, ++x, y++) {
					const SpriteBatchInfo& info = *x;// rect.second;
					const int quad = info.quadid;
					//LogFile::writeLog("Renderer2D::draw() > Quad: " + std::to_string(quad));
					if (slot != info.texslot) {
						temp = info.texslot;
						break;
					}

					const int tInd = j << 2;
					VertexSpriteInfo test = {
						0.0, 0.0,
						pSlot->vRect[quad].x + info.ou,
						pSlot->vRect[quad].y + info.ov,
						info.x, info.y,
						pSlot->vRect[quad].w, pSlot->vRect[quad].h,
						info.sx, info.sy,
						info.dir,
						overAll * 0.000001,
						info.ah,
						info.av,
						info.r,
						info.g,
						info.b,
						info.a,
					};
					if (!(test == receive[tInd])) {

						receive[tInd] = test;
						receive[tInd + 1] = {
								pSlot->vRect[quad].w, 0.0,
								pSlot->vRect[quad].x + info.ou + pSlot->vRect[quad].w,
								pSlot->vRect[quad].y + info.ov,
								info.x, info.y,
								pSlot->vRect[quad].w, pSlot->vRect[quad].h,
								info.sx, info.sy,
								info.dir,
								overAll * 0.000001f,
								(float)info.ah,
								(float)info.av,
								(float)info.r,
								(float)info.g,
								(float)info.b,
								(float)info.a,
						};
						receive[tInd + 2] = {
								pSlot->vRect[quad].w, pSlot->vRect[quad].h,
								pSlot->vRect[quad].x + info.ou + pSlot->vRect[quad].w,
								pSlot->vRect[quad].y + info.ov + pSlot->vRect[quad].h,
								info.x, info.y,
								pSlot->vRect[quad].w, pSlot->vRect[quad].h,
								info.sx, info.sy,
								info.dir,
								overAll * 0.000001f,
								(float)info.ah,
								(float)info.av,
								(float)info.r,
								(float)info.g,
								(float)info.b,
								(float)info.a,
						};
						receive[tInd + 3] = {
								0.0, pSlot->vRect[quad].h,
								pSlot->vRect[quad].x + info.ou,
								pSlot->vRect[quad].y + info.ov + pSlot->vRect[quad].h,
								info.x, info.y,
								pSlot->vRect[quad].w, pSlot->vRect[quad].h,
								info.sx, info.sy,
								info.dir,
								overAll * 0.000001f,
								(float)info.ah,
								(float)info.av,
								(float)info.r,
								(float)info.g,
								(float)info.b,
								(float)info.a,
						};
					}
				}
				//x += j;
				glUnmapBuffer(GL_ARRAY_BUFFER);
#ifdef _DEBUG
				while (GLenum err = glGetError()) {
					std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
				}
#endif
				if (j) {
					this->m_GLObject.bindEx();
					this->m_Textures[pSlot->texId].bindTexture();
#ifdef _DEBUG
					while (GLenum err = glGetError()) {
						std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
					}
#endif
					glDrawElements(GL_TRIANGLES, j * 6, GL_UNSIGNED_INT, nullptr);

#ifdef _DEBUG
					while (GLenum err = glGetError()) {
						std::cerr << "OpenGL error code: " << err << " on " << (__FILE__) << " line " << (__LINE__) << "\n";
					}
#endif
				}
				slot = temp;
			}
		
	}
	glEnable(GL_DEPTH_TEST);
}

void Renderer2D::drawEx(TextureBase& tex, uint32_t tm, const SpriteBatchInfo& info) {
	glDisable(GL_DEPTH_TEST);
	this->m_RenderShader.useProgram();
	this->m_RenderShader.setUniform("intime", ((float)tm) / 60.0f);
	glm::vec2 size = tex.getSize();
	this->m_RenderShader.setUniform("quad", size);
	this->m_AuxSprite.obj.bind();
	VertexSpriteInfo* receive = (VertexSpriteInfo*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	receive[0] = {
		0.0, 0.0,
		info.ou, info.ov,
		info.x, info.y,
		size.x, size.y,
		info.sx, info.sy,
		info.dir,
		info.layer * 0.0001f,
		1.0,
		1.0,
		(float)info.r,
		(float)info.g,
		(float)info.b,
		(float)info.a,
	};

	receive[1] = {
		size.x, 0.0,
		size.x + info.ou, info.ov,
		info.x, info.y,
		size.x, size.y,
		info.sx, info.sy,
		info.dir,
		info.layer * 0.0001f,
		1.0,
		1.0,
		(float)info.r,
		(float)info.g,
		(float)info.b,
		(float)info.a,
	};

	receive[2] = {
		size.x, size.y,
		size.x + info.ou, info.ov + size.y,
		info.x, info.y,
		size.x, size.y,
		info.sx, info.sy,
		info.dir,
		info.layer * 0.0001f,
		1.0,
		1.0,
		(float)info.r,
		(float)info.g,
		(float)info.b,
		(float)info.a,
	};

	receive[3] = {
		0.0, size.y,
		info.ou, info.ov + size.y,
		info.x, info.y,
		size.x, size.y,
		info.sx, info.sy,
		info.dir,
		info.layer * 0.0001f,
		1.0,
		1.0,
		(float)info.r,
		(float)info.g,
		(float)info.b,
		(float)info.a,
	};
	glUnmapBuffer(GL_ARRAY_BUFFER);
	this->m_AuxSprite.obj.bindEx();
	tex.bindTexture();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glEnable(GL_DEPTH_TEST);
}

//2023/07/01 - Ditched old Load textures function
/*void Renderer2D::LoadTextures(char*& script) {
	this->m_Anim.Initialize(script);
}*/

void Renderer2D::LoadTextures(const std::vector<std::string>& fNameArray) {
	this->m_Anim.Initialize(fNameArray);
}

//Load Textures for general purpose
void Renderer2D::Initialize() {
	this->m_Textures = this->m_Anim.initializeTexture();
	//this->m_Anim.cleanUp();
}
/*
//Load Textures for menus and things
void Renderer2D::InitializeEx() {
	this->m_TexturesEx = this->m_Anim.initializeTexture();
	this->m_Anim.cleanUp();
}*/

void Renderer2D::cleanUp() {
	this->m_Textures.clear();
	this->m_Anim.cleanUp();
	//for (auto& i : this->m_Triangles)
	//	if (i) {
	//		free(i);
	//		i = nullptr;
	//	}
	//this->m_Triangles.clear();
	if (this->m_pIndices) {
		free(this->m_pIndices);
		this->m_pIndices = nullptr;
	}


}

//How many slots are loaded
size_t Renderer2D::getSlotCount() const {
	return this->m_Anim.m_AnimeArr.size();
}