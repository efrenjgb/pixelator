#include "bsp.h"

bspNode* bspNode_new()
{
	bspNode* node = malloc(sizeof(bspNode));
	ZeroMemory(node, sizeof(*node));
	return node;
}

polygon* polygon_new()
{
	polygon* poly = malloc(sizeof(polygon));
	ZeroMemory(poly, sizeof(*poly));
	return poly;
}

bspNode* initBsp(void)
{
	int BSPMAP[] = {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
					0,0,2,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,
					0,2,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,
					1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,
					0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
					0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,
					0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,3,1,
					0,2,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,
					1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,
					0,1,0,0,0,0,1,2,0,0,0,1,0,0,0,1,0,0,0,1,
					0,1,0,0,0,1,2,0,0,0,0,1,1,0,0,0,0,0,0,1,
					0,1,0,0,0,1,0,0,0,0,0,3,1,0,0,0,0,0,0,1,
					0,1,0,1,1,2,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
					1,2,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1, 
					1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
					1,0,0,1,2,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
					1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
					1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

	vec3 VERTLIST[4][4];
	polygon *polygonList=NULL;// this is a GLOBAL pointer
	polygon *child=NULL;
	int direction[4];

	for (int y=0;y< 40;y++)
	{
		for (int x=0;x< 20;x++)
		{
			ZeroMemory(direction,sizeof(int)*4);
			int offset=(y*20)+x;
	// check what the digit is in the current map location
			if (BSPMAP[offset]!=0)
			{
				if (BSPMAP[offset]==2)// North East Wall
				{	
					vec3 v1 = {x-10.5f,3.0f,(20.0f-y)-0.5f};
					vec3 v2 = {x-9.5f,3.0f,(20.0f-y)+0.5f};
					vec3 v3 = {x-9.5f,0.0f,(20.0f-y)+0.5f};
					vec3 v4 = {x-10.5f,0.0f,(20.0f-y)-0.5f};

					VERTLIST[0][0]=v1;
					VERTLIST[0][1]=v2;
					VERTLIST[0][2]=v3;
					VERTLIST[0][3]=v4;
					direction[0]=1;
				}
				if (BSPMAP[offset]==3)// North West Wall
				{
					vec3 v1 = {x-10.5f,3.0f,(20.0f-y)+0.5f};
					vec3 v2 = {x-9.5f,3.0f,(20.0f-y)-0.5f};
					vec3 v3 = {x-9.5f,0.0f,(20.0f-y)-0.5f};
					vec3 v4 = {x-10.5f,0.0f,(20.0f-y)+0.5f};

					VERTLIST[0][0]=v1;
					VERTLIST[0][1]=v2;
					VERTLIST[0][2]=v3;
					VERTLIST[0][3]=v4;
					direction[0]=1;
				}	

				if (BSPMAP[offset]==1)// Its a Standared wall
				{
					if (x > 0)
					{
						if (BSPMAP[offset-1]==0)// if theres nothing to the left add a left facing wall
						{
							vec3 v1 = {x-10.5f,3.0f,(20.0f-y)+0.5f};
							vec3 v2 = {x-10.5f,3.0f,(20.0f-y)-0.5f};
							vec3 v3 = {x-10.5f,0.0f,(20.0f-y)-0.5f};
							vec3 v4 = {x-10.5f,0.0f,(20.0f-y)+0.5f};

							VERTLIST[0][0]=v1;
							VERTLIST[0][1]=v2;
							VERTLIST[0][2]=v3;
							VERTLIST[0][3]=v4;
							direction[0]=1;
						}
					}

					if (x < 19)
					{
						if (BSPMAP[offset+1]==0)// if there is nothing to the right add a right facing wall
						{
							vec3 v1 = {x-9.5f,3.0f,(20.0f-y)-0.5f};
							vec3 v2 = {x-9.5f,3.0f,(20.0f-y)+0.5f};
							vec3 v3 = {x-9.5f,0.0f,(20.0f-y)+0.5f};
							vec3 v4 = {x-9.5f,0.0f,(20.0f-y)-0.5f};

							VERTLIST[1][0]=v1;
							VERTLIST[1][1]=v2;
							VERTLIST[1][2]=v3;
							VERTLIST[1][3]=v4;
							direction[1]=1;
						}
					}

					if (y > 0)
					{
						if (BSPMAP[offset-20]==0)// if there is nothing south add a south facing wall
						{
							vec3 v1 = {x-9.5f,3.0f,(20.0f-y)+0.5f};
							vec3 v2 = {x-10.5f,3.0f,(20.0f-y)+0.5f};
							vec3 v3 = {x-10.5f,0.0f,(20.0f-y)+0.5f};
							vec3 v4 = {x-9.5f,0.0f,(20.0f-y)+0.5f};
							
							VERTLIST[2][0]=v1;
							VERTLIST[2][1]=v2;
							VERTLIST[2][2]=v3;
							VERTLIST[2][3]=v4;
							direction[2]=1;
						}
					}

					if(y < 39)
					{	
						if (BSPMAP[offset+20]==0)// if there is nothing to the north add a north facing wall
						{
							vec3 v1 = {x-10.5f,3.0f,(20.0f-y)-0.5f};
							vec3 v2 = {x-9.5f,3.0f,(20.0f-y)-0.5f};
							vec3 v3 = {x-9.5f,0.0f,(20.0f-y)-0.5f};
							vec3 v4 = {x-10.5f,0.0f,(20.0f-y)-0.5f};

							VERTLIST[3][0]=v1;
							VERTLIST[3][1]=v2;
							VERTLIST[3][2]=v3;
							VERTLIST[3][3]=v4;
							direction[3]=1;
						}
					}	
				}// end for if offset==1

				// build the polygons
				for (int a=0;a<4;a++)
				{
					if (direction[a]!=0)
					{
						if (polygonList==NULL)
						{
							polygonList = polygon_add(NULL, &VERTLIST[a][0], 4);
							child = polygonList;
						}
						else
						{
							child = polygon_add(child, &VERTLIST[a][0], 4);
						}
					}//
				}////
			}// end for if offset!=0
		}
	}

	vec3 v0 = {-140.5,0.0,-20.0};
	vec3 v1 = {-140.5,0.0,20.0};
	vec3 v2 = {60.5,0.0,-20.0};
	vec3 v3 = {60.5,0.0,20.0};

	vec3 floor[4];
	floor[0] = v3;
	floor[1] = v2;
	floor[2] = v1;
	floor[3] = v0;

	child = polygon_add(child, floor, 4);

	bspNode* btrNode = bspNode_new();
	BuildBspTree(btrNode, polygonList);
	return btrNode;
}

polygon* polygon_add(polygon* parent, vec3 *vertices, int nov)
{	
	polygon* child = malloc(sizeof(polygon));
	child->vertexCount = nov;
	child->indicesCount = (nov - 2) * 3;
	child->next = NULL;

	int i;	
	for (i=0;i<nov;i++)
	{
		child->vertices[i] = vertices[i];
	}

	//calculate indices
	int v0,v1,v2;
	for (i=0;i<child->indicesCount/3;i++)
	{
		if (i==0)
		{
			v0=0;
			v1=1;
			v2=2;
		}
		else
		{
			v1=v2;
			v2++;
		}
		child->indices[i*3]=v0;
		child->indices[(i*3)+1]=v1;
		child->indices[(i*3)+2]=v2;
	}

	// generate polygon normal
	vec3 vec0 = child->vertices[0];
	vec3 vec1 = child->vertices[1];
	vec3 vec2 = child->vertices[child->vertexCount - 1];// the last vert
	vec3 edge1, edge2; 
	vec3_sub(&edge1, vec1, vec0);
	vec3_sub(&edge2, vec2, vec0);
	cross(&child->normal, edge1, edge2);
	normalize(&child->normal);

	if (parent!=NULL)
	{
		parent->next=child;
	}

	return child;
}

int ClassifyPoint(vec3 pos, polygon* plane)
{
	float result;
	vec3 v1 = plane->vertices[0];
	vec3 direction;
	vec3_sub(&direction, v1, pos);

	result = dot(direction, plane->normal);
	if (result < -0.001) return CP_FRONT;
	if (result > 0.001) return CP_BACK;
	return CP_ONPLANE;
}

int ClassifyPoly(polygon *plane, polygon *poly)
{
	int infront=0;
	int behind=0;
	int onplane=0;
	float result;

	vec3 v1 = plane->vertices[0];
	int a;
	for (a=0;a<poly->vertexCount;a++)
	{
		vec3 v2 = poly->vertices[a];
		vec3 direction;
		vec3_sub(&direction, v1, v2);
	
		result = dot(direction, plane->normal);
	
		if (result > 0.001)
		{
			behind++;
		}
		else if (result < -0.001)
		{
			infront++;
		}
		else
		{
			onplane++;
			infront++;
			behind++;
		}
	}

	if(onplane == poly->vertexCount) return CP_FRONT;// this would nomrally be CP_ONPLANE
	if(behind  == poly->vertexCount) return CP_BACK;
	if(infront == poly->vertexCount) return CP_FRONT;

	return CP_SPANNING;
}

polygon * selectBestSplitter(polygon *PolyList)
{
	polygon* Splitter = PolyList;
	polygon* CurrentPoly = NULL;
	unsigned long BestScore = 100000;// just set to a very high value to begin
	polygon * SelectedPoly = NULL;

	while (Splitter!=NULL)
	{
		CurrentPoly = PolyList;
		unsigned long score, splits, backfaces, frontfaces;
		score = splits = backfaces = frontfaces = 0;
		while (CurrentPoly!=NULL)
		{
			if (CurrentPoly!=Splitter)
			{
				int result = ClassifyPoly(Splitter, CurrentPoly);
				switch ( result)
				{
					case CP_ONPLANE:
					break;
					case CP_FRONT:
						frontfaces++;
					break;
					case CP_BACK:
						backfaces++;
					break;
					case CP_SPANNING:
						splits++;
					break;
					default:
					break;
				}
			}
			CurrentPoly = CurrentPoly->next;
		}// end while current poly

		score = abs(frontfaces - backfaces) + (splits * 8);
		if(score < BestScore)
		{
			BestScore=score;
			SelectedPoly = Splitter;
		}

		Splitter=Splitter->next;
	}// end while splitter == null	
	return SelectedPoly;
}


int Get_Intersect (vec3 *linestart, vec3 *lineend, vec3 *vertex, vec3 *normal, vec3 *intersection, float *percentage)
{
	vec3 direction, L1;
	float linelength, dist_from_plane;

	direction.x = lineend->x - linestart->x;
	direction.y = lineend->y - linestart->y;
	direction.z = lineend->z - linestart->z;

	linelength = dot(direction, *normal);

	if (fabsf(linelength)<0.0001)
	{
		return 0;
	}

	L1.x = vertex->x - linestart->x;
	L1.y = vertex->y - linestart->y;
	L1.z = vertex->z - linestart->z;

	dist_from_plane = dot(L1, *normal);
	*percentage = dist_from_plane / linelength; 

	if (*percentage < 0.0f || *percentage > 1.0f) 
	{
		return 0;
	}

	intersection->x = linestart->x + direction.x * (*percentage);
	intersection->y = linestart->y + direction.y * (*percentage);
	intersection->z = linestart->z + direction.z * (*percentage);
	return 1;
}

void Splitpolygon(polygon *Poly, polygon *Plane, polygon *FrontSplit, polygon *BackSplit)
{
	vec3 FrontList[20], BackList[20], FirstVertex;
	vec3 PlaneNormal, IntersectPoint, PointOnPlane, PointA, PointB;
	int FrontCounter=0, BackCounter=0, loop=0, CurrentVertex=0;
	float percent;	

	// Find any vertex on the plane to use later in plane intersect routine
	PointOnPlane = Plane->vertices[0];

	// first we find out if the first vertex belongs in front or back list
	FirstVertex = Poly->vertices[0];
	switch (ClassifyPoint(FirstVertex, Plane))
	{
		case CP_FRONT:
			FrontList[FrontCounter++] = FirstVertex;
		break;
		case CP_BACK:
			BackList[BackCounter++] = FirstVertex;
		break;
		case CP_ONPLANE:
			BackList[BackCounter++]=FirstVertex;
			FrontList[FrontCounter++]=FirstVertex;
		break;
		default:
		break;
	}

	for (loop=1;loop<Poly->vertexCount+1;loop++)
	{
		if (loop==Poly->vertexCount) 
		{
			CurrentVertex=0;
		}
		else
		{
			CurrentVertex=loop;
		}
		PointA = Poly->vertices[loop-1];
		PointB = Poly->vertices[CurrentVertex];

		PlaneNormal = Plane->normal;
		int Result=ClassifyPoint(PointB, Plane);
		if (Result==CP_ONPLANE)
		{
			BackList[BackCounter++]=Poly->vertices[CurrentVertex];
			FrontList[FrontCounter++]=Poly->vertices[CurrentVertex];
		}
		else
		{

			if (Get_Intersect(&PointA, &PointB, &PointOnPlane, &PlaneNormal, &IntersectPoint, &percent) == 1)
			{
				// float deltax,deltay,texx,texy;
				// deltax=Poly->VertexList[CurrentVertex].tu-Poly->VertexList[loop-1].tu;
				// deltay=Poly->VertexList[CurrentVertex].tv-Poly->VertexList[loop-1].tv;
				// texx=Poly->VertexList[loop-1].tu+(deltax*percent);
				// texy=Poly->VertexList[loop-1].tv+(deltay*percent);
				// D3DLVERTEX copy=D3DLVERTEX(IntersectPoint,RGB_MAKE(255,255,255),0,texx,texy);

				if (Result==CP_FRONT )
				{
					BackList[BackCounter++] = IntersectPoint;//=copy;
					FrontList[FrontCounter++] = IntersectPoint;//=copy;
					if (CurrentVertex!=0)
					{
						FrontList[FrontCounter++] = Poly->vertices[CurrentVertex];
					}
				}	

				if (Result==CP_BACK)
				{
					FrontList[FrontCounter++] = IntersectPoint;//=copy;
					BackList[BackCounter++] = IntersectPoint;//=copy;	
					if (CurrentVertex != 0)
					{
						BackList[BackCounter++] = Poly->vertices[CurrentVertex];
					}
				}	

			}// end if intersection (get intersect==true)
			else
			{
				if (Result==CP_FRONT)
				{
					if (CurrentVertex != 0)
					{
						FrontList[FrontCounter++] = Poly->vertices[CurrentVertex];
					}
				}

				if (Result==CP_BACK) 
				{
					if (CurrentVertex != 0)
					{
						BackList[BackCounter++] = Poly->vertices[CurrentVertex];
					}
				}
			}

		}
	}//end loop through each edge


	//OK THEN LETS BUILD THESE TWO polygonAL BAD BOYS

	FrontSplit->vertexCount = 0;
	BackSplit->vertexCount  = 0;

	for (loop=0;loop<FrontCounter;loop++)
	{
		FrontSplit->vertexCount++;
		FrontSplit->vertices[loop] = FrontList[loop];
	}

	for (loop=0;loop<BackCounter;loop++)
	{
		BackSplit->vertexCount++;
		BackSplit->vertices[loop] = BackList[loop];
	}

	BackSplit->indicesCount = (BackSplit->vertexCount - 2) * 3;
	FrontSplit->indicesCount = (FrontSplit->vertexCount - 2) * 3;

	// Fill in the Indices Array
	int v0,v1,v2;
	for (loop=0;loop<FrontSplit->indicesCount/3;loop++)
	{
		if (loop==0)
		{
			v0=0;
			v1=1;
			v2=2;
		}
		else
		{
			v1=v2;
			v2++;
		}
		FrontSplit->indices[loop*3]=v0;
		FrontSplit->indices[(loop*3)+1]=v1;
		FrontSplit->indices[(loop*3)+2]=v2;
	}

	for (loop=0;loop<BackSplit->indicesCount/3;loop++)
	{
		if (loop==0) 
		{
			v0=0;
			v1=1;
			v2=2;
		}
		else
		{
			v1=v2;
			v2++;
		}
		BackSplit->indices[loop*3]=v0;
		BackSplit->indices[(loop*3)+1]=v1;
		BackSplit->indices[(loop*3)+2]=v2;
	}

	// calculate polygon Normals

	vec3 edge1,edge2;
	//edge1=*(vec3 *)&FrontSplit->VertexList[FrontSplit->Indices[1]]-*(vec3 *)&FrontSplit->VertexList[FrontSplit->Indices[0]];
	vec3_sub(&edge1, FrontSplit->vertices[FrontSplit->indices[1]], FrontSplit->vertices[FrontSplit->indices[0]]);
	//edge2=*(vec3 *)&FrontSplit->VertexList[FrontSplit->Indices[FrontSplit->NumberOfIndices-1]]-*(vec3 *)&FrontSplit->VertexList[FrontSplit->Indices[0]];
	vec3_sub(&edge2, FrontSplit->vertices[FrontSplit->indices[FrontSplit->indicesCount - 1]], FrontSplit->vertices[FrontSplit->indices[0]]);

	//FrontSplit->normal = CrossProduct(edge1,edge2);
	cross(&FrontSplit->normal, edge1,edge2);
	//FrontSplit->normal=Normalize(FrontSplit->Normal);
	normalize(&FrontSplit->normal);

	//edge1=*(vec3 *)&BackSplit->VertexList[BackSplit->Indices[1]]-*(vec3 *)&BackSplit->VertexList[BackSplit->Indices[0]];
	//edge2=*(vec3 *)&BackSplit->VertexList[BackSplit->Indices[BackSplit->NumberOfIndices-1]]-*(vec3 *)&BackSplit->VertexList[BackSplit->Indices[0]];
	vec3_sub(&edge1, BackSplit->vertices[BackSplit->indices[1]], BackSplit->vertices[BackSplit->indices[0]]);
	vec3_sub(&edge2, BackSplit->vertices[BackSplit->indices[BackSplit->indicesCount - 1]], BackSplit->vertices[BackSplit->indices[0]]);
	//BackSplit->Normal=CrossProduct(edge1,edge2);
	//BackSplit->Normal=Normalize(BackSplit->Normal);
	cross(&BackSplit->normal, edge1,edge2);
	normalize(&BackSplit->normal);
}


void BuildBspTree(bspNode* CurrentNode, polygon* PolyList)
{
	polygon *polyTest 		= NULL;
	polygon *FrontList		= NULL;
	polygon *BackList		= NULL;
	polygon *Nextpolygon	= NULL;
	polygon *FrontSplit		= NULL;
	polygon *BackSplit		= NULL;
	CurrentNode->splitter = selectBestSplitter(PolyList);
	polyTest=PolyList;

	while (polyTest!=NULL)
	{
		Nextpolygon=polyTest->next;// remember because polytest-> Next will be altered
		if (polyTest != CurrentNode->splitter)
		{
			switch (ClassifyPoly(CurrentNode->splitter, polyTest))
			{
				case CP_FRONT:
					polyTest->next = FrontList;
					FrontList = polyTest;	
				break;

				case CP_BACK:
					polyTest->next = BackList;
					BackList = polyTest;	
				break;

				case CP_SPANNING:
					FrontSplit = polygon_new();
					BackSplit = polygon_new();
					//ZeroMemory(FrontSplit, sizeof(polygon));
					//ZeroMemory(BackSplit, sizeof(polygon));
					Splitpolygon(polyTest, CurrentNode->splitter, FrontSplit, BackSplit);
					free(polyTest);
					FrontSplit->next = FrontList;
					FrontList = FrontSplit;
					BackSplit->next = BackList;
					BackList = BackSplit;
				break;
				default:
				break;
			}
		}// end if polypoint!=CurrentNodesplitter
		polyTest = Nextpolygon;
	}// end while loop

	if (FrontList==NULL)
	{
		bspNode* leafnode = bspNode_new();
		//ZeroMemory(leafnode, sizeof(leafnode));
		leafnode->isLeaf = 1;
		leafnode->isSolid = 0;	
		CurrentNode->front = leafnode;
	}
	else
	{
		bspNode* newnode = bspNode_new();
		//ZeroMemory(newnode, sizeof(newnode));
		newnode->isLeaf = 0;
		CurrentNode->front = newnode;
		BuildBspTree(newnode, FrontList);
	}

	if (BackList==NULL)
	{
		bspNode* leafnode = bspNode_new();
		//ZeroMemory(leafnode, sizeof(leafnode));
		leafnode->isLeaf = 1;
		leafnode->isSolid = 1;	
		CurrentNode->back = leafnode;
	}
	else
	{
		bspNode* newnode = bspNode_new();
		//ZeroMemory(newnode, sizeof(newnode));
		newnode->isLeaf = 0;
		CurrentNode->back=newnode;
		BuildBspTree(newnode, BackList);
	}
}// end buildbsptree function