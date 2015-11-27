#include "mesh.h"
#include <iostream>
#include <GLUT/glut.h>

TriangleMesh mesh("off_files/carro.off");
std::vector<Vec3<float> > bounding_box = mesh.getBoundingBox();
Vec3<float> min = bounding_box[0];
Vec3<float> max = bounding_box[1];
Vec3<float> centro((min.getX() + max.getX()) / 2,(min.getY() + max.getY()) / 2,(min.getZ() + max.getZ()) / 2);
Vec3<float> diagonal((max.getX() - min.getX()), (max.getY() - min.getY()), (max.getZ() - min.getZ()));
int tipo_normal = 3;


// Seleciona qual tipo de normal vai ser aplicada
// 1: por face , 2: por vertice ponderada por area 
// 3: por vertice ponderado por angulo
void keyboard(unsigned char key, int x, int y)
{
    switch(key) {
        case 'a':
            tipo_normal = 1;
        break;
        case 's':
            tipo_normal = 2;
        break;

        case 'd':
            tipo_normal = 3;
        break;
        default:
            tipo_normal = 3;
        break;
    }
    glutPostRedisplay(); 
}

void init(void)
{
    GLfloat matSpecular[] = { 1, 1, 1, 1.0 };
    GLfloat matShininess[] = { 36.0 };
    GLfloat lightPosition[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat whiteLight[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lmodelAmbient[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat material[] = { 1.0, 0.0, 0.0, 1.0 };
    glClearColor( 0, 0, 0, 0 );

    glShadeModel( GL_SMOOTH );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, matShininess );

    glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, whiteLight );
    glLightfv( GL_LIGHT0, GL_SPECULAR, whiteLight );
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lmodelAmbient );
    glLightModelf( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );

    glEnable( GL_COLOR_MATERIAL );

    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_DEPTH_TEST );
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    std::vector<Vec3<float> > vertices = mesh.getVertices();
    std::vector<Vec3<int> > triangles = mesh.getTriangles();
    std::vector<Vec3<float> > normal = mesh.getNormal();
    std::vector<Vec3<float> > normalArea = mesh.getNormalArea();
    std::vector<Vec3<float> > normalAngulo = mesh.getNormalAngulo();

    for(int i =0 ; i < triangles.size(); i++)
    {
        Vec3<float> v1 = vertices[triangles[i].getX()];
        Vec3<float> v2 = vertices[triangles[i].getY()];
        Vec3<float> v3 = vertices[triangles[i].getZ()];
        Vec3<float> n1, n2, n3;

        if(tipo_normal == 2)
        {
            n1 = normalArea[triangles[i].getX()];
            n2 = normalArea[triangles[i].getY()];
            n3 = normalArea[triangles[i].getZ()];
        }
        else if(tipo_normal == 3)
        {
            n1 = normalAngulo[triangles[i].getX()];
            n2 = normalAngulo[triangles[i].getY()];
            n3 = normalAngulo[triangles[i].getZ()];
        }
        else
        {
            n1 = normal[i];
            n2 = normal[i];
            n3 = normal[i];
        }
        

        glBegin(GL_TRIANGLES);
            glColor3d(1.0, 0.0, 0.0);
            glNormal3d(n1.getX(), n1.getY(), n1.getZ());
            glVertex3d(v1.getX(), v1.getY(), v1.getZ());

            glColor3d(1.0, 0.0, 0.0);
            glNormal3d(n2.getX(), n2.getY(), n2.getZ());
            glVertex3d(v2.getX(), v2.getY(), v2.getZ());

            glColor3d(1.0, 0.0, 0.0);
            glNormal3d(n3.getX(), n3.getY(), n3.getZ());
            glVertex3d(v3.getX(), v3.getY(), v3.getZ());
        glEnd();
        
    }

    glutSwapBuffers();
}

void reshape(int w, int h)
{

    Vec3<float> min = bounding_box[0];
    Vec3<float> max = bounding_box[1];
    Vec3<float> centro((min.getX() + max.getX()) / 2,(min.getY() + max.getY()) / 2,(min.getZ() + max.getZ()) / 2);
    Vec3<float> diagonal((max.getX() - min.getX()), (max.getY() - min.getY()), (max.getZ() - min.getZ()));

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(35.0, (GLfloat) w/(GLfloat) h, 0.1, 5000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(centro.getX()+ 2 * diagonal.norm() , centro.getY() , centro.getZ() , centro.getX() , centro.getY(), centro.getZ(), 0.0, 1.0, 0.0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}