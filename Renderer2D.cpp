#include "Renderer2D.h"
#include <memory>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

//Constructor
Renderer2D::Renderer2D() {

}

Renderer2D::Renderer2D(sf::RenderWindow* win) : m_pWin(win) {
}


Renderer2D::~Renderer2D() {
	cleanUp();
	for(auto& i : this->m_Triangles)
	if (i) {
		free(i);
		i = nullptr;
	}
	if (this->m_pIndices) {
		free(this->m_pIndices);
		this->m_pIndices = nullptr;
	}
	//sf::Shader::bind(NULL);
}
#define ENM_MAX 100000


void Renderer2D::configureRenderer() {
	const int mem_alloc = 6 * ENM_MAX * sizeof(VertexSpriteInfo);//sizeof(SpriteBatchInfo);
	//Vertex alloc
	//this->m_pTriangles = (GLfloat*)std::malloc(mem_alloc);
	const size_t size = this->m_Anim.m_AnimeArr.size();
	for (int i = 0; i < size; i++) {
		GLfloat* pTriangles = (GLfloat*)malloc(mem_alloc);
		std::memset(pTriangles, 0x00, mem_alloc);
		this->m_Triangles.push_back(pTriangles);
	}
	this->m_pIndices = (GLuint*)std::malloc(4 * 6 * ENM_MAX);
	for (int i = 0; i < ENM_MAX; i++) {
		const int ind = i << 2;
		const int ind2 = i * 6;
		m_pIndices[ind2] = ind;
		m_pIndices[ind2 + 1] = ind + 1;
		m_pIndices[ind2 + 2] = ind + 3;
		m_pIndices[ind2 + 3] = ind + 1;
		m_pIndices[ind2 + 4] = ind + 3;
		m_pIndices[ind2 + 5] = ind + 2;
	}
}

//I'll only use the Vertex and Fragment shader...
//2023/05/05 - Gonna add the Geometry Shader.
//2023/05/08 - Removed Geometry Shader.
void Renderer2D::InitShader(std::string vert, std::string geom, std::string frag) {

	//Shader setup
	this->m_RenderShader.loadFromFile(vert, frag);
	glm::mat4 Proj(1.0);
	Proj = glm::ortho(0.0f, 1280.0f / 1.5f, 480.0f, 0.0f, -1.0f, 0.0f);
	this->m_RenderShader.setUniform("camMat", sf::Glsl::Mat4(glm::value_ptr(Proj)));

	//sf::Shader::bind(&this->m_RenderShader);
	/*
	glGenVertexArrays(1, &this->m_VAO);
	glBindVertexArray(this->m_VAO);

	glGenBuffers(1, &this->m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * 4 * (2 + 2), this->m_pTriangles, GL_STATIC_DRAW);
	//X Y
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * (2 + 2), 0);
	glEnableVertexAttribArray(0);
	//U V
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * (2 + 2), (void*)2);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/
}

void Renderer2D::activateDraw(uint32_t time) {

	
	

	//glBindVertexArray(this->m_VAO);
	//QuadWH
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, this->m_pTriangles + 4);
	//glEnableVertexAttribArray(2);
	//Layer
	//glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, sizeof(GLfloat) * 4, this->m_pTriangles + 6);
	//glEnableVertexAttribArray(3);
}

void Renderer2D::deactivateDraw() {

}

//2023/05/10 - Changed the way this thing sends info to the vertex shader
void Renderer2D::draw(int slot, int quad, const SpriteBatchInfo& info) {
	int i = 0;
	AnimeSlot* pSlot = &this->m_Anim.m_AnimeArr[slot];

	VertexSpriteInfo vinfo[4]{
		{
			0.0, 0.0,
			pSlot->vRect[quad].x + info.ou,
			pSlot->vRect[quad].y + info.ov,
			info.x, info.y,
			pSlot->vRect[quad].w, pSlot->vRect[quad].h,
			info.sx, info.sy,
			info.dir,
			info.layer
		},
		{
			0.0 + pSlot->vRect[quad].w, 0.0,
			pSlot->vRect[quad].x + info.ou + pSlot->vRect[quad].w,
			pSlot->vRect[quad].y + info.ov,
			info.x, info.y,
			pSlot->vRect[quad].w, pSlot->vRect[quad].h,
			info.sx, info.sy,
			info.dir,
			info.layer
		},
		{
			0.0 + pSlot->vRect[quad].w, 0.0 + pSlot->vRect[quad].h,
			pSlot->vRect[quad].x + info.ou + pSlot->vRect[quad].w,
			pSlot->vRect[quad].y + info.ov + pSlot->vRect[quad].h,
			info.x, info.y,
			pSlot->vRect[quad].w, pSlot->vRect[quad].h,
			info.sx, info.sy,
			info.dir,
			info.layer
		},
		{
			0.0, 0.0 + pSlot->vRect[quad].h,
			pSlot->vRect[quad].x + info.ou,
			pSlot->vRect[quad].y + info.ov + pSlot->vRect[quad].h,
			info.x, info.y,
			pSlot->vRect[quad].w, pSlot->vRect[quad].h,
			info.sx, info.sy,
			info.dir,
			info.layer
		}

	};
	//std::memcpy(this->m_pTriangles, vinfo, sizeof(vinfo));

	this->m_RenderShader.setUniform("inColor", sf::Glsl::Vec4(info.r, info.g, info.b, info.a));
	this->m_RenderShader.setUniform("quadWH", sf::Glsl::Vec2(this->m_Textures[pSlot->texId].getSize()));

	sf::Texture::bind(&this->m_Textures[pSlot->texId]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, this->m_pIndices);
}

void Renderer2D::draw(const std::vector<FixedVector<std::pair<uint32_t, SpriteBatchInfo>>>& drawList) {
	const size_t size = drawList.size();
	size_t drawCnt;
	size_t split_cnt;
	AnimeSlot* pSlot;
	int i;


	sf::Shader::bind(&this->m_RenderShader);
	this->m_RenderShader.setUniform("time", float(0) / 60.0f);

	for (int slot = 0; slot < size; slot++) {
		i = 0;
		pSlot = &this->m_Anim.m_AnimeArr[slot];
		this->m_RenderShader.setUniform("quadWH", sf::Glsl::Vec2(this->m_Textures[pSlot->texId].getSize())); 
		this->m_RenderShader.setUniform("inColor", sf::Glsl::Vec4(1.0,1.0,1.0,1.0));


		//X Y
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexSpriteInfo), this->m_Triangles[slot]);
		glEnableVertexAttribArray(0);
		//U V
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexSpriteInfo), this->m_Triangles[slot] + 2);
		glEnableVertexAttribArray(1);
		//Translate
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexSpriteInfo), this->m_Triangles[slot] + 4);
		glEnableVertexAttribArray(2);
		//QuadWH
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexSpriteInfo), this->m_Triangles[slot] + 6);
		glEnableVertexAttribArray(3);
		//Scale
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(VertexSpriteInfo), this->m_Triangles[slot] + 8);
		glEnableVertexAttribArray(4);
		//Dir
		glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(VertexSpriteInfo), this->m_Triangles[slot] + 10);
		glEnableVertexAttribArray(5);
		//Layer
		glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(VertexSpriteInfo), this->m_Triangles[slot] + 11);
		glEnableVertexAttribArray(6);

		drawCnt = drawList[slot].m_Size;
		for (int j = 0; j < drawCnt; j++) {
			const std::pair<uint32_t, const SpriteBatchInfo&>& rect = drawList[slot].m_pData[j];
			const int quad = rect.first;
			const SpriteBatchInfo& info = rect.second;
			const int ind = i * sizeof(VertexSpriteInfo);
			//this->m_pTriangles[ind + 0] = this->m_pTriangles[ind + 1] = this->m_pTriangles[ind + 0]

			//20FPS glDrawTriangles

			VertexSpriteInfo vinfo[]{
				{
					0.0, 0.0,
					pSlot->vRect[quad].x + info.ou,
					pSlot->vRect[quad].y + info.ov,
					info.x, info.y,
					pSlot->vRect[quad].w, pSlot->vRect[quad].h,
					info.sx, info.sy,
					info.dir,
					info.layer
				},
				{
					pSlot->vRect[quad].w, 0.0,
					pSlot->vRect[quad].x + info.ou + pSlot->vRect[quad].w,
					pSlot->vRect[quad].y + info.ov,
					info.x, info.y,
					pSlot->vRect[quad].w, pSlot->vRect[quad].h,
					info.sx, info.sy,
					info.dir,
					info.layer
				},
				{
					pSlot->vRect[quad].w, pSlot->vRect[quad].h,
					pSlot->vRect[quad].x + info.ou + pSlot->vRect[quad].w,
					pSlot->vRect[quad].y + info.ov + pSlot->vRect[quad].h,
					info.x, info.y,
					pSlot->vRect[quad].w, pSlot->vRect[quad].h,
					info.sx, info.sy,
					info.dir,
					info.layer
				},
				{
					0.0, 0.0,
					pSlot->vRect[quad].x + info.ou,
					pSlot->vRect[quad].y + info.ov,
					info.x, info.y,
					pSlot->vRect[quad].w, pSlot->vRect[quad].h,
					info.sx, info.sy,
					info.dir,
					info.layer
				},
				{
					pSlot->vRect[quad].w, pSlot->vRect[quad].h,
					pSlot->vRect[quad].x + info.ou + pSlot->vRect[quad].w,
					pSlot->vRect[quad].y + info.ov + pSlot->vRect[quad].h,
					info.x, info.y,
					pSlot->vRect[quad].w, pSlot->vRect[quad].h,
					info.sx, info.sy,
					info.dir,
					info.layer
				},
				{
					0.0, pSlot->vRect[quad].h,
					pSlot->vRect[quad].x + info.ou,
					pSlot->vRect[quad].y + info.ov + pSlot->vRect[quad].h,
					info.x, info.y,
					pSlot->vRect[quad].w, pSlot->vRect[quad].h,
					info.sx, info.sy,
					info.dir,
					info.layer
				}
			
			}; 
			std::memcpy(&this->m_Triangles[slot][i * (sizeof(VertexSpriteInfo) >> 2) * 6], vinfo, sizeof(vinfo));
			i++;
		}
		if (drawCnt) {
			split_cnt = drawCnt;
			sf::Texture::bind(&this->m_Textures[pSlot->texId]);
			for (int i = 0; split_cnt; i++) {
				const size_t split = std::min((size_t)2000, split_cnt);
				split_cnt -= split;
				//glDrawArrays(GL_TRIANGLES, 6 * i * 2000, 6 * split);
				//glDrawElements(GL_TRIANGLES, split * 6, GL_UNSIGNED_INT, &this->m_pIndices[i * 6 * 2000]);
			}
			glDrawArrays(GL_TRIANGLES, 0, GLsizei(6 * drawCnt));
		}
	}

	

}

void Renderer2D::LoadTextures(char*& script) {
	this->m_Anim.Initialize(script);
}

void Renderer2D::LoadTextures(const std::list<std::string>& fNameArray) {
	this->m_Anim.Initialize(fNameArray);
}

//Load Textures for general purpose
void Renderer2D::Initialize() {
	this->m_Textures = this->m_Anim.initializeTexture();
	//this->m_Anim.cleanUp();
}

//Load Textures for menus and things
void Renderer2D::InitializeEx() {
	this->m_TexturesEx = this->m_Anim.initializeTexture();
	this->m_Anim.cleanUp();
}

void Renderer2D::cleanUp() {
	this->m_Textures.clear();
}

//How many slots are loaded
size_t Renderer2D::getSlotCount() const {
	return this->m_Anim.m_AnimeArr.size();
}