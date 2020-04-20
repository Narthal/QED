// Vertex shader

#type vertex
#version 330 core
					
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTextureCoordinate;
layout(location = 3) in float aTextureIndex;
layout(location = 4) in float aTilingFactor;

uniform mat4 uViewProjection;

out vec2 vTextureCoordinate;
out vec4 vColor;
out float vTextureIndex;
out float vTilingFactor;

void main()
{
	vColor = aColor;
	vTextureCoordinate = aTextureCoordinate;
	vTextureIndex = aTextureIndex;
	vTilingFactor = aTilingFactor;
	gl_Position = uViewProjection * vec4(aPosition, 1.0);
}

// Fragment shader

#type fragment
#version 330 core
					
layout(location = 0) out vec4 color;

in vec4 vColor;
in vec2 vTextureCoordinate;
in float vTextureIndex;
in float vTilingFactor;

uniform sampler2D uTexture[32];

void main()
{
	color = texture(uTexture[int(vTextureIndex)], vTextureCoordinate * vTilingFactor) * vColor;
}