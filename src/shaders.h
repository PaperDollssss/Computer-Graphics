#pragma once
#include "texture_mapping.h"

void TextureMapping::initInstancedShader() {

	const char* vsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPosition;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"layout(location = 2) in vec2 aTexCoord;\n"
		"layout(location = 3) in mat4 aInstanceMatrix;\n"
		"out vec3 fPosition;\n"
		"out vec3 fNormal;\n"
		"out vec2 fTexCoord;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		//"uniform mat4 model;\n"

		"void main() {\n"
		"	fPosition = vec3(aInstanceMatrix * vec4(aPosition, 1.0f));\n"
		"	fNormal = mat3(transpose(inverse(aInstanceMatrix))) * aNormal;\n"
		"	fTexCoord = aTexCoord;\n"
		"	gl_Position = projection * view * aInstanceMatrix * vec4(aPosition, 1.0f);\n"

		"}\n";

	const char* fsCode =
		"#version 330 core\n"
		"in vec3 fPosition;\n"
		"in vec3 fNormal;\n"
		"in vec2 fTexCoord;\n"
		"out vec4 color;\n"

		"struct DirectionalLight {\n"
		"	vec3 direction;\n"
		"	vec3 color;\n"
		"	float intensity;\n"
		"};\n"

		"struct Material {\n"
		"	vec3 kds[2];\n"
		"	float blend;\n"
		"};\n"

		"uniform Material material;\n"
		"uniform DirectionalLight light;\n"
		"uniform sampler2D mapKds[2];\n"

		"vec3 calcDirectionalLight(vec3 normal) {\n"
		"	vec3 lightDir = normalize(-light.direction);\n"
		"	vec3 diffuse = light.color * max(dot(lightDir, normal), 0.0f) * (material.kds[0]+material.kds[1]);\n"
		"	return light.intensity * diffuse ;\n"
		"}\n"

		"void main() {\n"
		"	vec3 normal = normalize(fNormal);\n"
		"	vec3 diffuse = calcDirectionalLight(normal);\n"
		"	vec3 ambient = 0.08*light.color * light.intensity * (material.kds[0]+material.kds[1]);\n"
		"	color = mix(texture(mapKds[0], fTexCoord), texture(mapKds[1], fTexCoord), material.blend) * vec4(diffuse+ambient, 1.0f);\n"
		"}\n";

	_instancedShader.reset(new GLSLProgram);
	_instancedShader->attachVertexShader(vsCode);
	_instancedShader->attachFragmentShader(fsCode);
	_instancedShader->link();
}


void TextureMapping::initShader()
{
	const char* vsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPosition;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"out vec3 worldPosition;\n"
		"out vec3 normal;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main() {\n"
		"	normal = mat3(transpose(inverse(model))) * aNormal;\n"
		"	worldPosition = vec3(model * vec4(aPosition, 1.0f));\n"
		"	gl_Position = projection * view * vec4(worldPosition, 1.0f);\n"
		"}\n";

	const char* fsCode =
		"#version 330 core\n"
		"in vec3 worldPosition;\n"
		"in vec3 normal;\n"
		"out vec4 fragColor;\n"
		"void main() {\n"
		"vec3 lightPosition = vec3(100.0f, 100.0f, 100.0f);\n"
		"// ambient color\n"
		"float ka = 0.1f;\n"
		"vec3 objectColor = vec3(1.0f, 1.0f, 1.0f);\n"
		"vec3 ambient = ka * objectColor;\n"
		"// diffuse color\n"
		"float kd = 0.8f;\n"
		"vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);\n"
		"vec3 lightDirection = normalize(lightPosition - worldPosition);\n"
		"vec3 diffuse = kd * lightColor * max(dot(normalize(normal), lightDirection), 0.0f);\n"
		"fragColor = vec4(ambient + diffuse, 1.0f);\n"
		"}\n";

	_shader.reset(new GLSLProgram);
	_shader->attachVertexShader(vsCode);
	_shader->attachFragmentShader(fsCode);
	_shader->link();
}

void TextureMapping::initSimpleShader()
{
	const char* vsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPosition;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"layout(location = 2) in vec2 aTexCoord;\n"
		"out vec2 fTexCoord;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"

		"void main() {\n"
		"	fTexCoord = aTexCoord;\n"
		"	gl_Position = projection * view * model * vec4(aPosition, 1.0f);\n"
		"}\n";

	const char* fsCode =
		"#version 330 core\n"
		"in vec2 fTexCoord;\n"
		"out vec4 color;\n"
		"uniform sampler2D mapKd;\n"
		"void main() {\n"
		"	color = texture(mapKd, fTexCoord);\n"
		"}\n";

	_simpleShader.reset(new GLSLProgram);
	_simpleShader->attachVertexShader(vsCode);
	_simpleShader->attachFragmentShader(fsCode);
	_simpleShader->link();
}

void TextureMapping::initBlendShader()
{
	const char* vsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPosition;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"layout(location = 2) in vec2 aTexCoord;\n"
		"out vec3 fPosition;\n"
		"out vec3 fNormal;\n"
		"out vec2 fTexCoord;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"

		"void main() {\n"
		"	fPosition = vec3(model * vec4(aPosition, 1.0f));\n"
		"	fNormal = mat3(transpose(inverse(model))) * aNormal;\n"
		"	fTexCoord = aTexCoord;\n"
		"	gl_Position = projection * view * model * vec4(aPosition, 1.0f);\n"

		"}\n";

	const char* fsCode =
		"#version 330 core\n"
		"in vec3 fPosition;\n"
		"in vec3 fNormal;\n"
		"in vec2 fTexCoord;\n"
		"out vec4 color;\n"
		"struct DirectionalLight {\n"
		"	vec3 direction;\n"
		"	vec3 color;\n"
		"	float intensity;\n"
		"};\n"

		"struct Material {\n"
		"	vec3 kds[2];\n"
		"	float blend;\n"
		"};\n"

		"uniform Material material;\n"
		"uniform DirectionalLight light;\n"
		"uniform sampler2D mapKds[2];\n"

		"vec3 calcDirectionalLight(vec3 normal) {\n"
		"	vec3 lightDir = normalize(-light.direction);\n"
		"	vec3 diffuse = light.color * max(dot(lightDir, normal), 0.0f) * (material.kds[0]+material.kds[1]);\n"
		"	return light.intensity * diffuse ;\n"
		"}\n"

		"void main() {\n"
		"	vec3 normal = normalize(fNormal);\n"
		"	vec3 diffuse = calcDirectionalLight(normal);\n"
		"	vec3 ambient = 0.08*light.color * light.intensity * (material.kds[0]+material.kds[1]);\n"
		"	color = mix(texture(mapKds[0], fTexCoord), texture(mapKds[1], fTexCoord), material.blend) * vec4(diffuse+ambient, 1.0f);\n"
		"}\n";

	//----------------------------------------------------------------

	_blendShader.reset(new GLSLProgram);
	_blendShader->attachVertexShader(vsCode);
	_blendShader->attachFragmentShader(fsCode);
	_blendShader->link();
}

void TextureMapping::initCheckerShader()
{
	const char* vsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPosition;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"layout(location = 2) in vec2 aTexCoord;\n"
		"out vec2 fTexCoord;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"void main() {\n"
		"	fTexCoord = aTexCoord;\n"
		"	gl_Position = projection * view * model * vec4(aPosition, 1.0f);\n"
		"}\n";

	const char* fsCode =
		"#version 330 core\n"
		"in vec2 fTexCoord;\n"
		"out vec4 color;\n"

		"struct Material {\n"
		"	vec3 colors[2];\n"
		"	int repeat;\n"
		"};\n"

		"uniform Material material;\n"

		"void main() {\n"
		"   vec3 colorChoose = (int(fTexCoord.x * material.repeat) + int(fTexCoord.y * material.repeat)) % 2 == 0 ? material.colors[0] : material.colors[1];\n"
		"	color = vec4(colorChoose, 1.0f);\n"
		"}\n";
	//----------------------------------------------------------------

	_checkerShader.reset(new GLSLProgram);
	_checkerShader->attachVertexShader(vsCode);
	_checkerShader->attachFragmentShader(fsCode);
	_checkerShader->link();
}