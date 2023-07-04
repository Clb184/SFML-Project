#include "OBJModel.h"
#include <regex>


void OBJModel::loadFromFile(std::string input) {
	loadObj(input);
}


auto findReal = [](std::string num) {
	bool foundDot = false;
	int op = 0;
	int decimal = 1;
	for(std::string::iterator i = num.begin(); i != num.end() ; ++i)
		switch (const char n = *i) {
		case '0':	case '1':	case '2':	case '3':	case '4':
		case '5':	case '6':	case '7':	case '8':	case '9':
			op = op * 10 + (n - '0');
			if (foundDot)
				decimal *= 10;
			break;
		case '.':
			foundDot = true;
			break;
		case '-':
			decimal = -decimal;
			break;
		default:
			goto end;
		}
	end:
	double norm = op,
		dec = decimal;
	return norm / dec;
};

void OBJModel::parseObj() {
	std::string line;
	size_t pos = 0;
	const size_t size = m_Obj.size;
	bool firstMat = false;

	VertexGL vert;
	Material mat;
	VertexArray vertArr;
	Part part;
	Mesh mesh;
	_3DModel model;

	std::vector<Mesh>::iterator meshIt;
	std::vector<Part>::iterator partIt;
	while (pos < size) {
		line = "";
		size_t str_pos = 0;

		while (m_Obj.buffer[pos] != 0x0a) {
			const char c = m_Obj.buffer[pos++];
			line.push_back(c);
		}
		pos++;
		{
			auto getNextWord = [&]() {
				std::string ret = "";
				bool firstCharFound = false;
				while (str_pos != line.size()) {
					if ((line.at(str_pos) == ' ' || line.at(str_pos) == '	'))
						if (!firstCharFound)
							str_pos++;
						else
							return ret;
					else if (firstCharFound)
						if (line.at(str_pos) == '#')
							return ret;
						else
							ret.push_back(line.at(str_pos++));
					else
						firstCharFound = true;
				}
				return ret;
			};
			std::string keyword = getNextWord();
			auto returnVec4 = [&]() {
				glm::vec4 vertex(0.0);
				for (int i = 0; i < 4; i++) {
					std::string num = getNextWord();
					if (num != "") {
						switch (i) {
						case 0:
							vertex.x = findReal(num);
							break;
						case 1:
							vertex.y = findReal(num);
							break;
						case 2:
							vertex.z = findReal(num);
							break;
						case 3:
							vertex.w = findReal(num);
							break;
						}

					}
					else
						break;
				}
				return vertex;
			};

			if (keyword == "#")
				continue;
			else {
				if (keyword == "mtllib") {
					const std::regex layout("\\s+([\\w+\\.*\\/*\\:])+");
					const std::regex fNameLay("([\\w+\\.*\\/*\\:])+");
					std::smatch name;
					if (std::regex_search(line, name, layout)) {
						std::string fName = name.str(); 
						std::regex_search(fName, name, fNameLay);
						fName = name.str();
						std::cout << "OBJ Model Material -> " << fName << "\n";
						this->loadMaterial(fName);
					}
				}
				else if (keyword == "o") {
					mesh = Mesh();
					model.Meshes.push_back(mesh);
					meshIt = model.Meshes.end() - 1;
				}
				else if (keyword == "v") {
					const std::regex layout("(\\s+\\-?\\d+\\.?\\d*){3}");
					if (std::regex_match(line.begin() + str_pos, line.end(), layout)) {
						glm::vec4 vertex = returnVec4();
						this->m_Vec3Vec.push_back(vertex);
					}
				}
				else if (keyword == "vn") {
					glm::vec4 temp = returnVec4();
					glm::vec3 vertex(temp.x, temp.y, temp.z);
					this->m_NormalVec.push_back(vertex);
				}
				else if (keyword == "vt") {
					glm::vec4 temp = returnVec4();
					glm::vec3 vertex(temp.x, temp.y, temp.z);
					this->m_UVVec.push_back(vertex);
				}
				else if (keyword == "vp")
					continue;
				else if (keyword == "s") {
					
				}
				else if (keyword == "usemtl") {
					const std::regex layout("\\s+([\\w+\\.*])+");
					//if (std::regex_match(line.begin() + str_pos, line.end(), layout)) {
						std::string matName = getNextWord();
						part = Part{};
						part.material = this->m_MatArray[matName];
						part.PartName = matName; - 1;
						meshIt->Parts.push_back(part);
						partIt = meshIt->Parts.end() - 1;
					//}
				}
				else if (keyword == "f") {
					const std::regex layout("(\\s+\\d+\\/\\d*\\/\\d*){3}");
					if (std::regex_match(line.begin() + str_pos, line.end(), layout)) {
						for (int i = 0; i < 3; i++) {
							int vID = 0.0, uvID, nID;
							vert = VertexGL();
							const std::regex num_lay("(\\d)+");
							std::smatch digit;
							for (int i = 0; i < 3; i++) {
								std::string num;
								if (std::regex_search(line, digit, num_lay)) {
									for (const auto& x : digit) {
										//std::cout << x;
										num = x;
										break;
									}
								}
								line = digit.suffix().str();

								switch (i) {
								case 0:
									vID = findReal(num) - 1;
									vert.vx = this->m_Vec3Vec[vID].x;
									vert.vy = this->m_Vec3Vec[vID].y;
									vert.vz = this->m_Vec3Vec[vID].z;
									break;
								case 1:
									uvID = findReal(num) - 1;
									vert.u = this->m_UVVec[uvID].x;
									vert.v = this->m_UVVec[uvID].y;
									break;
								case 2:
									nID = findReal(num) - 1;
									vert.vni = this->m_NormalVec[nID].x;
									vert.vnj = this->m_NormalVec[nID].y;
									vert.vnk = this->m_NormalVec[nID].z;
									break;
								}
							}
							partIt->VxArray.push_back(vert);
						}
					}
				}
				else if(keyword == "l")
					continue;
			}
		}
	}
	for (meshIt = model.Meshes.begin(); meshIt != model.Meshes.end(); ++meshIt) {
		for (partIt = meshIt->Parts.begin(); partIt != meshIt->Parts.end(); ++partIt) {
			vertGroup verts;
			verts.texname = partIt->material.MatName;
			verts.tex = partIt->material.mat;

			const size_t size = partIt->VxArray.size();
			verts.size = size;
			verts.pVert = (VertexGL*)malloc(sizeof(VertexGL) * size);
			for (int i = 0; i < size; i++) {
				verts.pVert[i] = partIt->VxArray[i];
			}
			verts.obj.configureArray(&verts.pVert->vx, sizeof(VertexGL)* size, CLB_GL_3D); // Only use OpenGLObject::bind(), not bindEx()
			this->m_ModelVertex.push_back(verts);
		}
	}
}


void OBJModel::parseMat() {
	std::string line;
	int i = 0;
	size_t pos = 0;
	const size_t size = this->m_Mat.size;
	Material material;
	std::vector<Material> tempMatArr;
	std::vector<Material>::iterator matIt;
	while (pos < size) {
		line = "";
		size_t str_pos = 0;

		while (m_Mat.buffer[pos] != 0x0a) {
			const char c = m_Mat.buffer[pos++];
			line.push_back(c);
		}
		pos++;
		{
			auto getNextWord = [&]() {
				std::string ret = "";
				bool firstCharFound = false;
				while (str_pos != line.size()) {
					if ((line.at(str_pos) == ' ' || line.at(str_pos) == '	'))
						if (!firstCharFound)
							str_pos++;
						else
							return ret;
					else if (firstCharFound)
						if (line.at(str_pos) == '#')
							return ret;
						else
							ret.push_back(line.at(str_pos++));
					else
						firstCharFound = true;
				}
				return ret;
			};
			auto returnVec4 = [&]() {
				glm::vec4 vertex(0.0);
				for (int i = 0; i < 4; i++) {
					std::string num = getNextWord();
					if (num != "") {
						switch (i) {
						case 0:
							vertex.x = findReal(num);
							break;
						case 1:
							vertex.y = findReal(num);
							break;
						case 2:
							vertex.z = findReal(num);
							break;
						case 3:
							vertex.w = findReal(num);
							break;
						}

					}
					else
						break;
				}
				return vertex;
			};

			std::string keyword = getNextWord();
			if (keyword == "#")
				continue;
			else {
				if (keyword == "map_Kd") {
					const std::regex layout("\\s+([\\w+\\.*\\/*\\:\\\\*])+");
					const std::regex fNameLay("([\\w+\\.*\\/*\\:\\\\*])+");
					std::smatch name;
					if (std::regex_search(line, name, layout)) {
						std::string fName = name.str();
						std::regex_search(fName, name, fNameLay);
						fName = name.str();
						
						std::cout << "Material -> " << matIt->MatName << " | Texture: " << fName << "\n";
						//tempMatArr.push_back(Material());
						matIt->mat.loadFromFile(fName, false);
						//i++;
					}
				}
				else if (keyword == "Ka") {
					const std::regex layout("(\\s+\\-?\\d+\\.?\\d*){3}");
					if (std::regex_match(line.begin() + str_pos, line.end(), layout)) {
						glm::vec4 vertex = returnVec4();
						matIt->ar = vertex.r;
						matIt->ag = vertex.g;
						matIt->ab = vertex.b;
					}
				}
				else if (keyword == "Kd") {
					const std::regex layout("(\\s+\\-?\\d+\\.?\\d*){3}");
					if (std::regex_match(line.begin() + str_pos, line.end(), layout)) {
						glm::vec4 vertex = returnVec4();
						matIt->dr = vertex.r;
						matIt->dg = vertex.g;
						matIt->db = vertex.b;
					}
				}
				else if (keyword == "Ks") {
					const std::regex layout("(\\s+\\-?\\d+\\.?\\d*){3}");
					if (std::regex_match(line.begin() + str_pos, line.end(), layout)) {
						glm::vec4 vertex = returnVec4();
						matIt->sr = vertex.r;
						matIt->sg = vertex.g;
						matIt->sb = vertex.b;
					}
				}
				else if (keyword == "Ke") {
					const std::regex layout("(\\s+\\-?\\d+\\.?\\d*){3}");
					if (std::regex_match(line.begin() + str_pos, line.end(), layout)) {
						glm::vec4 vertex = returnVec4();
						matIt->er = vertex.r;
						matIt->eg = vertex.g;
						matIt->eb = vertex.b;
					}
				}
				else if (keyword == "newmtl") {
					const std::regex layout("\\s+([\\w+\\.*])+");
					//if (std::regex_match(line.begin() + str_pos, line.end(), layout)) {
						std::string matName = getNextWord();
						material = Material{};
						material.MatName = matName; -1;
						tempMatArr.push_back(material);
						matIt = tempMatArr.end() - 1;
					//}
				}
				else if (keyword == "d") {
					const std::regex layout("\\s + \\ - ? \\d + \\. ? \\d*");
					if (std::regex_match(line.begin() + str_pos, line.end(), layout)) {
						std::string alpha = getNextWord();
						matIt->alpha = findReal(alpha);
					}
				}
				else if (keyword == "Ns")
					continue;
				else if (keyword == "Ni")
					continue;
				else if (keyword == "illum")
					continue;
			}
		}
	}
	for (matIt = tempMatArr.begin(); matIt != tempMatArr.end(); ++matIt) {
		this->m_MatArray.insert({matIt->MatName, *matIt});
	}
}

void OBJModel::loadObj(std::string obj) {
	
	if (this->m_Obj.__load(obj)) {
		parseObj();
		this->m_Obj.__free();
	}
}

void OBJModel::loadMaterial(std::string mat) {
	if (this->m_Mat.__load(mat)) {
		parseMat();
		this->m_Mat.__free();
	}
}

char* OBJModel::__file::__load(std::string file) {
	FILE* fp;
	if (fp = fopen(file.c_str(), "r")) {
		fseek(fp, 0, SEEK_END);
		size_t size = ftell(fp);
		rewind(fp);
		this->buffer = (char*)malloc(size);
		this->size = size;
		fread(this->buffer, size, 1, fp);
		fclose(fp);
		return this->buffer;
	}
	return nullptr;
}

void OBJModel::__file::__free() {
	if (this->buffer) {
		free(this->buffer);
		this->buffer = nullptr;
	}
}

OBJModel::~OBJModel() {
	size_t size = this->m_ModelVertex.size();
	for (int i = 0; i < size; i++) {
		if (this->m_ModelVertex[i].pVert) {
			free(this->m_ModelVertex[i].pVert);
		}
	}
}