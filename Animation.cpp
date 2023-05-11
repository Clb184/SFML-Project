#include "Animation.h"
#include <regex>

void AnimationSetup::Initialize(char*& buffer) {
	if (buffer) {
		AnimeSlot temp;
		FILE* pCurrentAnime;
		char curChar;
		std::string fileName = "";

		while (curChar = *buffer++) {
			fileName.push_back(curChar);
		}
		if (pCurrentAnime = fopen(fileName.c_str(), "rb")) {
			size_t size, end;
			char* anmBuffer;

			fseek(pCurrentAnime, 0, SEEK_END);
			end = ftell(pCurrentAnime);
			rewind(pCurrentAnime);
			size = end - ftell(pCurrentAnime);
			anmBuffer = (char*)malloc(size);
			fread(anmBuffer, size, 1, pCurrentAnime);
			fclose(pCurrentAnime);

			temp = parseFile(anmBuffer, size);
			m_AnimeArr.push_back(temp);
			free(anmBuffer);
		}
		if (*buffer) {
			Initialize(buffer);
		}
	}
	return;
}

void AnimationSetup::Initialize(const std::list<std::string>& fileList){
	if (fileList.size() > 0) {
		for (auto& n : fileList) {
			AnimeSlot slot;
			FILE* fp;
			size_t size, end;
			char* buffer;

			if (fp = fopen(n.c_str(), "rb")) {
				fseek(fp, 0, SEEK_END);
				size = ftell(fp);
				rewind(fp);
				buffer = (char*)malloc(size);
				fread(buffer, size, 1, fp);
				fclose(fp);
				slot = parseFile(buffer, size);
				m_AnimeArr.push_back(slot);
				free(buffer);
			}
		}
	}
}


enum {
	RECT = 0x54434552,
	ANIM = 0x4d494e41
};

AnimeSlot AnimationSetup::parseFile(char* buffer, size_t size) {
	AnimeSlot ret;
	AnimeFileHeader File;

	//Animation tempAnimation;
	AnimeRect tempRect;
	Anime tempAnime;
	std::vector<Anime> tempVec;
	Rect tempRect2;

	size_t pos = 0;
	uint32_t Id = 0;
	memcpy(&File, buffer, sizeof(AnimeFileHeader));
	pos += sizeof(AnimeFileHeader);

	for (std::map<int, std::string>::iterator i = m_TexIDContainer.begin(); i != m_TexIDContainer.end(); ++i) {
		if (i->second == File.FileName)
			break;
		Id++;
	}
	ret.texId = Id;

	if (m_TexIDContainer.find(Id) == m_TexIDContainer.end()) {
		m_TexIDContainer.insert({Id, File.FileName});
	}

	while (pos < size) {
		switch (*(int*)(buffer + pos)) {
		case RECT:
			pos += 4;
			memcpy(&tempRect, buffer + pos, sizeof(AnimeRect));
			tempRect2.x = tempRect.x;
			tempRect2.y = tempRect.y;
			tempRect2.w = (tempRect.w > 8192) ? 8192 : tempRect.w;
			tempRect2.h = (tempRect.h > 8192) ? 8192 : tempRect.h;


			//ret.vRect.insert({ tempRect.id, tempRect });
			ret.vRect.insert({ uint32_t(tempRect.id), tempRect2});
			pos += sizeof(AnimeRect);
			break;
		//case ANIM:
		//	buffer += 4;
		//	tempAnime.frameCnt = *(int*)buffer;
		//	tempAnime.speed = *(int*)(buffer + 4);
		//	buffer += 8;
		//	tempAnime.frameIds = new int[tempAnime.frameCnt];
		//	memcpy(tempAnime.frameIds, buffer, sizeof(int) * (tempAnime.frameCnt));
		//	tempVec.push_back(tempAnime);
		//	buffer += tempAnime.frameCnt * 4;
		//	break;
		default:
			break;
		}
	}

	//for (std::vector<Anime>::iterator I = tempVec.begin(); I != tempVec.end(); ++I) {
	//	tempAnimation.setAnimation(*I, ret.vRect);
	//	ret.vAnime.push_back(tempAnimation);
	//	delete[] I->frameIds;
	//}

	return ret;
}


std::vector<sf::Texture> AnimationSetup::initializeTexture() {
	std::vector<sf::Texture> ret;
	if (!m_TexIDContainer.empty()) {
		sf::Texture temp;
		for (auto& it : m_TexIDContainer) {
			temp.loadFromFile(it.second);
			temp.generateMipmap();
			temp.setRepeated(true);
			ret.push_back(temp);
		}
	}
	return ret;
}

void AnimationSetup::cleanUp()
{
	for (std::vector<AnimeSlot>::iterator i = m_AnimeArr.begin(); i != m_AnimeArr.end(); ++i) {
		i->vRect.clear();
	}
	m_AnimeArr.clear();
	m_TexIDContainer.clear();
}

AnimationSetup::~AnimationSetup() {
	cleanUp();
}

/*
Animation::~Animation()
{
	if (m_frames) {
		delete[] m_frames;
	}
}

void Animation::setAnimation(const Anime& src, std::map<uint32_t, AnimeRect>& rectMap) {
	m_frameCnt = src.frameCnt;
	//m_frameSpeed = speed;
	m_frames = new AnimeRect[src.frameCnt];
	for (int i = 0; i < m_frameCnt; i++) {
		m_frames[i] = rectMap[src.frameIds[i]];
	}
}
*/