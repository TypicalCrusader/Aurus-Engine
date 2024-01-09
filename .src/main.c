#include <windows.h>
#include <gl/glut.h>
#include <stdlib.h>

void Display()
{
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
   
    glClear( GL_COLOR_BUFFER_BIT );
   
    glColor3f( 1.0, 0.0, 0.0 );

    glBegin( GL_POLYGON );
   
    glVertex3f( 0.0, 0.0, 0.0 );
    glVertex3f( 0.0, 1.0, 0.0 );
    glVertex3f( 1.0, 1.0, 0.0 );
    glVertex3f( 1.0, 0.0, 0.0 );
   
    glEnd();
   
    glFlush();
   
    glutSwapBuffers();
}


void Reshape( int width, int height )
{
    Display();
}


enum
{
    EXIT 
};


void Menu( int value )
{
    switch( value )
    {
    case EXIT:
        exit( 0 );
    }
}

int main( int argc, char * argv[] )
{
    glutInit( & argc, argv );
   
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
   
    glutInitWindowSize( 400, 400 );
   
    glutCreateWindow( "Aurus Engine" );
   
    glutDisplayFunc( Display );
   
    glutReshapeFunc( Reshape );
   
    glutCreateMenu( Menu );
   
    #ifdef WIN32
   
    glutAddMenuEntry( "Exit", EXIT );
    #else
   
    glutAddMenuEntry( "Exit", EXIT );
    #endif
   
    glutAttachMenu( GLUT_RIGHT_BUTTON );
   
    glutMainLoop();
    return 0;
}