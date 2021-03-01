//Savu Ioana Rusalda335CB
#version 330
layout(location = 0) in vec3 v_position;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;

out vec3 frag_color;


void main()
{
	frag_color = object_color;
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}