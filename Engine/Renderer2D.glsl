// Vertex shader

#type vertex
#version 330 core
					
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTextureCoordinate;

uniform mat4 uViewProjection;

out vec2 vTextureCoordinate;
out vec4 vColor;

void main()
{
	vColor = aColor;
	vTextureCoordinate = aTextureCoordinate;
	gl_Position = uViewProjection * vec4(aPosition, 1.0);
}

// Fragment shader

#type fragment
#version 330 core
					
layout(location = 0) out vec4 color;

in vec4 vColor;
in vec2 vTextureCoordinate;

uniform vec4 uColor;
uniform sampler2D uTexture;
uniform float uTilingFactor;

void main()
{
	//color = texture(uTexture, vTextureCoordinate * uTilingFactor) * uColor;
	color = vColor;
}