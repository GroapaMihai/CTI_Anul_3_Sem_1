#version 330

#define MAX_NUMBER_WAVES 10

layout(location = 0) in vec3 v_position;		
layout(location = 1) in vec3 v_normal;		

uniform mat4 Model; 
uniform mat4 View;
uniform mat4 Projection;

uniform int numberOfWaves;
uniform float time;
uniform int gerstnerWaves;
uniform int renderWaves;
uniform float centersY;
uniform float w;
uniform float phases[MAX_NUMBER_WAVES];
uniform float centersX[MAX_NUMBER_WAVES];
uniform float centersZ[MAX_NUMBER_WAVES];
uniform float amplitudes[MAX_NUMBER_WAVES];

out vec3 world_position;
out vec3 world_normal;

void main()
{
	world_position = (Model * vec4(v_position, 1)).xyz;
	world_normal = normalize(mat3(Model) * v_normal);
	vec4 final = vec4(v_position, 1);

	vec3 wp = world_position;
	vec3 N = world_normal;
	vec3 centerDistance, circle_center;
	vec3 V1, V2, V3, V4, V5, V1i, V2i, V3i, V4i, V5i;

	float scalarProd, scalarProd2, scalarProd3, A, phi, Q;
	int i;
	bool gerstnerCondition = (gerstnerWaves == 1 && wp.y <= 1 && wp.y >= -1);
	bool circularCondition = (renderWaves == 1 && wp.y <= 1 && wp.y >= -1);

	if(gerstnerCondition)
	{
		A = amplitudes[0];
		phi = phases[0];
		Q = 1 / (w * A);
		vec3 N = world_normal;

		V1 = vec3(v_position.x, v_position.y, v_position.z);
		V2 = vec3(v_position.x - 1, v_position.y, v_position.z);
		V3 = vec3(v_position.x + 1, v_position.y, v_position.z);
		V4 = vec3(v_position.x, v_position.y, v_position.z - 1);
		V5 = vec3(v_position.x, v_position.y, v_position.z + 1);

		scalarProd = dot(vec3(1, 0, 1), V1);
		scalarProd2 = dot(vec3(0, 0, 1), V1);
		V1.y += Q * A * (cos(scalarProd * w + time * phi) + cos(scalarProd2 * w + time * phi));

		scalarProd = dot(vec3(1, 0, 1), V2);
		scalarProd2 = dot(vec3(0, 0, 1), V2);
		V2.y += Q * A * (cos(scalarProd * w + time * phi) + cos(scalarProd2 * w + time * phi));
	
		scalarProd = dot(vec3(1, 0, 1), V3);
		scalarProd2 = dot(vec3(0, 0, 1), V3);
		V3.y += Q * A * (cos(scalarProd * w + time * phi) + cos(scalarProd2 * w + time * phi));
	
		scalarProd = dot(vec3(1, 0, 1), V4);
		scalarProd2 = dot(vec3(0, 0, 1), V4);
		V4.y += Q * A * (cos(scalarProd * w + time * phi) + cos(scalarProd2 * w + time * phi));

		scalarProd = dot(vec3(1, 0, 1), V5);
		scalarProd2 = dot(vec3(0, 0, 1), V5);
		V5.y += Q * A * (cos(scalarProd * w + time * phi) + cos(scalarProd2 * w + time * phi));

		final = vec4(V1, 1); 
	}
	else if(circularCondition) 
	{
		V1 = V1i = vec3(world_position.x, 0, world_position.z); 
		V2 = V2i = vec3(world_position.x - 1, world_position.y, world_position.z);
		V3 = V3i = vec3(world_position.x + 1, world_position.y, world_position.z);
		V4 = V4i = vec3(world_position.x, world_position.y, world_position.z - 1);
		V5 = V5i = vec3(world_position.x, world_position.y, world_position.z + 1);

		for(i = 0; i < numberOfWaves; i++) 
		{
			circle_center = vec3(centersX[i], centersY, centersZ[i]);
			A = amplitudes[i];
			phi = phases[i];

			centerDistance = normalize(circle_center - V1i);
			scalarProd = dot(centerDistance, V1i);
			V1.y += A * (1 + sin(w * scalarProd + time * phi));
		
			centerDistance = normalize(circle_center - V2i);
			scalarProd = dot(centerDistance, V2i);
			V2.y += A * (1 + sin(w * scalarProd + time * phi));

			centerDistance = normalize(circle_center - V3i);
			scalarProd = dot(centerDistance, V3i);
			V3.y += A * (1 + sin(w * scalarProd + time * phi));

			centerDistance = normalize(circle_center - V4i);
			scalarProd = dot(centerDistance, V4i);
			V4.y += A * (1 + sin(w * scalarProd + time * phi));

			centerDistance = normalize(circle_center - V5i);
			scalarProd = dot(centerDistance, V5i);
			V5.y += A * (1 + sin(w * scalarProd + time * phi));
		}
	}

	if(gerstnerCondition || circularCondition) 
	{
		vec3 N1 = cross(V5 - V1, V3 - V1);
		vec3 N2 = cross(V5 - V1, V2 - V1);
		vec3 N3 = cross(V4 - V1, V2 - V1);
		vec3 N4 = cross(V3 - V1, V4 - V1);

		N.x = (N1.x + N2.x + N3.x + N4.x) / 4;
		N.y = (N1.y + N2.y + N3.y + N4.y) / 4;
		N.z = (N1.z + N2.z + N3.z + N4.z) / 4;

		world_normal = N;

		if(circularCondition)
			world_position = V1;
	}

	gl_Position = Projection * View * Model * final; 
}