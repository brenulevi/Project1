#version 330 core

in vec2 texCoord;

uniform sampler2D atlasTexture;

void main()
{
	gl_FragColor = texture(atlasTexture, texCoord);
}