#include <math.h>


void calc_mesh_normals(vec3* normals,
		       const vec3* verts,
		       const int* faces,
		       int nverts, int nfaces) 
{

    vec3 *normals_of_faces = new vec3[nfaces];
    int face_counter;

    double vx1, vy1, vz1;
    double vx2, vy2, vz2;

    int counter_of_normals;
    double vector_length;
    
    for (face_counter = counter_of_normals = 0; face_counter < nfaces; face_counter += 3)
    {
	vx1 = verts[faces[face_counter]].x - verts[faces[face_counter + 1]].x;
	vy1 = verts[faces[face_counter]].y - verts[faces[face_counter + 1]].y;
	vz1 = verts[faces[face_counter]].z - verts[faces[face_counter + 1]].z;
       
	vx2 = verts[faces[face_counter + 1]].x - verts[faces[face_counter + 2]].x;
	vy2 = verts[faces[face_counter + 1]].y - verts[faces[face_counter + 2]].y;
	vz2 = verts[faecs[face_counter + 1]].z - verts[faces[face_counter + 2]].z;

	normals_of_faces[counter_of_normals].x = vy1*vz2 - vz1*vy2;
	normals_of_faces[counter_of_normals].y = vx1*vz2 - vz1*vx2;
	normals_of_faces[counter_of_normals].z = vx1*vy2 - vy1*vx2;

	vector_length = sqrt(pow(normals_of_faces[counter_of_normals].x, 2) +
			     pow(normals_of_faces[counter_of_normals].y, 2) +
			     pow(normals_of_faces[counter_of_normals].z, 2));
	
	normals_of_faces[counter_of_normals].x /= vector_length;
	normals_of_faces[counter_of_normals].y /= vector_length;
	normals_of_faces[counter_of_normals].z /= vector_length;
		
	counter_of_normals++;		
    }

    int vert_counter;
    int normals_pre_vertex;
    
    for (vert_counter = 0; vert_counter < nverts; vert_counter++)
    {
	normals_per_vertex = 0;
	for (face_counter = 0; face_counter < nfaces; face_counter++)
	{
	    if (verts[faces[face_counter]].x == verts[vert_counter].x &&
		verts[faces[face_counter]].y == verts[vert_counter].y &&
		verts[faces[face_counter]].z == verts[vert_counter].z)
	    {
		normals[vert_counter] += normals_of_faces[face_counter/3];
		normals_per_vertex++;
	    }
	}

	normals[vert_counter] /= normals_per_vertex;
    }
    
    
}
