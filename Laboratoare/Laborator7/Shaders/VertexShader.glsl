#version 330
//spatiu obiect
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Uniforms for light properties - spatiu lume
uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;

// Output value to fragment shader
out vec3 color;

void main()
{
	float light;
	float factorAtenuare;
	// TODO: compute world space vectors
	vec3 world_position = vec3(Model * vec4(v_position,1));
	vec3 world_normal = vec3(Model * vec4(v_normal,0));

	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);

	// TODO: define ambient light component
	float ambient_light = material_kd * 0.25;

	// TODO: compute diffuse light component
	float diffuse_light_scalar = dot(N, L);
	float diffuse_light = 0;

	// TODO: compute specular light component
	float specular_light = 0;

	if (diffuse_light_scalar > 0)
	{
		diffuse_light = material_kd * diffuse_light_scalar;
		specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);

	}

	// TODO: compute light
	factorAtenuare = 1 / pow(length(light_position - world_position), 2);
	light = ambient_light + factorAtenuare * (specular_light + diffuse_light);

	// TODO: send color light output to fragment shader
	color = light * object_color;

	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
