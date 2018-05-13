#include "mesh.h"

void mesh_init(mesh* m, char* filename)
{
	FILE *fp;
	long lSize;
	char *buffer;

	fp = fopen ( filename , "rb" );
	if( !fp )
		perror("file could not be opened.");

	fseek( fp , 0L , SEEK_END);
	lSize = ftell( fp );
	rewind( fp );

	/* allocate memory for entire content */
	buffer = calloc( 1, lSize+1 );
	if( !buffer ) 
		fclose(fp),fputs("memory alloc fails",stderr);

	/* copy the file into the buffer */
	if( 1!=fread( buffer , lSize, 1 , fp) )
	  fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

	/* do your work here, buffer is a string contains the whole text */

	fclose(fp);
	
	//const char* text = contents.c_str();
	json_t *root;
	json_error_t error;

	root = json_loads(buffer, 0, &error);
	if(!root)
	{
		fprintf(stderr, "Error on line %d: %s\n", error.line, error.text);
		return;
	}

	json_t* meshes;
	meshes = json_object_get(root, "meshes");
	if(!meshes)
	{
		printf("didnt work.");
	}

	json_t* mesh;
	mesh = json_array_get(meshes, 0);
	if(!mesh)
	{
		printf("no mesh.\n");
	}

	json_t* vertices;
	vertices = json_object_get(mesh, "vertices");
	if(!vertices)
	{
		printf("no vertices.\n");
	}

	//printf("vertices: %lu\n", json_array_size(vertices)/6);
	const int verticesCount = json_array_size(vertices)/6;
	m->vertexCount = verticesCount;
	m->vertices = malloc(verticesCount * sizeof(vec3));
	int i;
	for(i=0;i<verticesCount;i++)
	{
		json_t* datax;
		json_t* datay;
		json_t* dataz;
		datax = json_array_get(vertices, i * 6);
		datay = json_array_get(vertices, i * 6 + 1);
		dataz = json_array_get(vertices, i * 6 + 2);

		//printf("%f\n", json_number_value(datax));
		vec3 v;
		v.x = (float)json_number_value(datax);
		v.y = (float)json_number_value(datay);
		v.z = (float)json_number_value(dataz);

		m->vertices[i] = v;
	}

	json_t* indices;
	indices = json_object_get(mesh, "indices");
	if(!indices)
	{
		printf("no indices.\n");
	}

	int indicesCount = json_array_size(indices)/3;
	m->faces = malloc(indicesCount * sizeof(face));
	//printf("indices: %d\n", indicesCount);
	m->faceCount = indicesCount;
	for(i=0;i<indicesCount;i++)
	{
		json_t* dataa;
		json_t* datab;
		json_t* datac;
		dataa = json_array_get(indices, i * 3);
		datab = json_array_get(indices, i * 3 + 1);
		datac = json_array_get(indices, i * 3 + 2);

		//printf("%f\n", json_number_value(data));
		face f;
		f.a = (int)json_number_value(dataa);
		f.b = (int)json_number_value(datab);
		f.c = (int)json_number_value(datac);
		m->faces[i] = f;
	}

	vec3 pr = {0.0f, 0.0f, 0.0f};

	m->position = pr;
	m->rotation = pr;

	free(buffer);
}

void mesh_map_init(char*filename)
{
	FILE *fp;
	long lSize;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen ( filename , "rb" );
	if( !fp )
		perror("file could not be opened.");

	while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
    }

	fclose(fp);
}

void mesh_free(mesh* m)
{
	free(m->vertices);
	free(m->faces);
}