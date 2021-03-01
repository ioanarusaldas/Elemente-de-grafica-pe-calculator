#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform int isSpot;

uniform vec3 object_color;

layout(location = 0) out vec4 out_color;

void main()
{
vec3 color;
	// TODO: define ambient light component
	float light;
	float factorAtenuare;

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


	float cut_off = radians(30);
	float spot_light = dot(-L, light_direction);
	float spot_light_limit = cos(cut_off);
	if(isSpot == 1) {
		if (spot_light > cos(cut_off))
		{
			// se calculeaza atenuarea luminii	
			float linear_att = (spot_light - spot_light_limit) / (1 - spot_light_limit);
			float light_att_factor = pow(linear_att, 2);
			// fragmentul este iluminat de spot, deci se calculeaza valoarea luminii conform  modelului Phong
			light = ambient_light + light_att_factor * (specular_light + diffuse_light);
		
			color = light * object_color;
		
		}else{
			color = object_color * ambient_light;
		}
	} else {
		factorAtenuare = 1 / pow(length(light_position - world_position), 2);
		light = ambient_light + factorAtenuare * (specular_light + diffuse_light);
		color = object_color * light;
	}

	

	// TODO: send color light output to fragment shader


	out_color = vec4(color, 1);
}