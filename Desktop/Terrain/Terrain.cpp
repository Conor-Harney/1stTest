// Terrain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
   
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#include <math.h>
#include "Camera.h"
#include "SFML/Graphics/Shader.hpp"

bool solid = true;
double m_Subdivisions = 200.0;
const double m_overallMeshSize = 500.0;

int _tmain(int argc, _TCHAR* argv[])
{

	return 0;
}
void drawShape(int sidesIn, const float radiusIn, float posXIn, float posYIn);

int main(){
	// Create the main window 
	//sf::Shader shader;
	//if(!shader.loadFromFile("vertex.glsl","fragment.glsl")){
    //    exit(1);
    //}
	//shader.setParameter("light_val",  0.5);
	//sf::Shader::bind(&shader);

    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML OpenGL"); 
   
    // Create a clock for measuring time elapsed     
    sf::Clock Clock;

    Camera camera;
    camera.Init(aiVector3D(0,100,0),aiVector3D(0,-1,0),aiVector3D(0,1,1));
	
    //prepare OpenGL surface for HSR 
    glClearDepth(1.f); 
    glClearColor(0.3f, 0.3f, 0.3f, 0.f); //background colour
    glEnable(GL_DEPTH_TEST); 
    glDepthMask(GL_TRUE); 
   
    //// Setup a perspective projection & Camera position 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
     
    //set up a 3D Perspective View volume
    gluPerspective(90.f, 1.f, 1.f, 300.0f);//fov, aspect, zNear, zFar 
 
    //set up a  orthographic projection same size as window
    //this mease the vertex coordinates are in pixel space
    //glOrtho(0,800,0,600,0,1); // use pixel coordinates
   
//image load
	sf::Image hight_map_img;
    sf::String hight_map_file = "Images/tester.png";
    if (!hight_map_img.loadFromFile(hight_map_file))
    {
        std::cout << "Could not load " << hight_map_file.getData();
         
    }
	GLuint hight_map_texture;
	glGenTextures(1, &hight_map_texture);
	glBindTexture(GL_TEXTURE_2D,hight_map_texture);

	// specify point sampling for minification and magnification, for current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   
	glTexImage2D(
		GL_TEXTURE_2D, 
		0,  //mip-map level
		GL_RGBA, //We want the internal texture to have RGBA components
		hight_map_img.getSize().x, hight_map_img.getSize().y,// size of texture
		0, //border (0=no border, 1=border)
		GL_RGBA, //format of the external texture data
		GL_UNSIGNED_BYTE, 
		hight_map_img.getPixelsPtr() //pointer to array of pixel data 
	);
//end image load   


    // Start game loop 
    while (App.isOpen()) 
    { 
        // Process events 
        sf::Event Event; 
        while (App.pollEvent(Event)) 
        { 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::D)){
            camera.MoveLeftRight(-1);
        }

        if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::A)){
            camera.MoveLeftRight(1);
        }
 
        if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::W)){
            camera.MoveForwardBack(1);
        }
        if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::S)){
            camera.MoveForwardBack(-1);
        }
 
        if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Right)){
            camera.TurnRightLeft(1);
        }
        if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Left)){
            camera.TurnRightLeft(-1);
        }
        if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up)){
            camera.TurnUpDown(1);
        }
        if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down)){
            camera.TurnUpDown(-1);
        }

		if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::M))
			if(solid == false)solid = true;
			else{solid = false;}

		if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
			m_Subdivisions += 2; 

		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
			m_Subdivisions -=2;

		if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::PageUp))
			m_Subdivisions = 200;
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::PageDown))
			m_Subdivisions = 10;

        // Close window : exit 
        if (Event.type == sf::Event::Closed) 
            App.close(); 
   
        // Escape key : exit 
        if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape)) 
            App.close(); 
        } 

        //Prepare for drawing 
        // Clear color and depth buffer 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
         
        double angle=Clock.getElapsedTime().asMilliseconds();
		if(solid == false){glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);}
		else{glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);}
		
		camera.ViewingTransform();

		double triangleSize = m_overallMeshSize / m_Subdivisions;
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,hight_map_texture);
		float vertexPosX;
		float vertexPosY;
		for(int iy = 0; iy < m_Subdivisions / 2; iy++){
			glBegin(GL_TRIANGLE_STRIP);
			for(int ix = 0; ix < (m_Subdivisions) / 2; ix++){
				
				vertexPosX = (ix) * triangleSize;
				vertexPosY = (iy) * triangleSize;
				sf::Color curCol =  hight_map_img.getPixel( vertexPosX / m_overallMeshSize * hight_map_img.getSize().x, vertexPosY / m_overallMeshSize * hight_map_img.getSize().y);
				
				glTexCoord2d((ix) / (m_Subdivisions / 2), (iy) / (m_Subdivisions / 2));

				glVertex3d((ix) * triangleSize, 0, (iy) * triangleSize); //specify a point
				//glColor3d(0,1,0);
				glTexCoord2d((ix + 1) / (m_Subdivisions / 2), (iy)  / (m_Subdivisions / 2));
				glVertex3d((ix + 1) * triangleSize, 0, (iy) * triangleSize); //specify a point
				//glColor3d(0,0,1);
				glTexCoord2d((ix) / (m_Subdivisions / 2), (iy + 1) / (m_Subdivisions / 2));
				glVertex3d((ix) * triangleSize, 0, (iy + 1) * triangleSize); //specify a point
				//glColor3d(1,0,0);
				glTexCoord2d((ix + 1) / (m_Subdivisions / 2), (iy + 1) / (m_Subdivisions / 2));
				glVertex3d((ix + 1) * triangleSize, 0, (iy + 1) * triangleSize); //specify a point
				//glColor3d(0,1,0);
				glTexCoord2d((ix + 1) / (m_Subdivisions / 2), (iy) / (m_Subdivisions / 2));
				glVertex3d((ix + 1) * triangleSize, 0, (iy) * triangleSize); //specify a point
				
			}
				
			
			glEnd(); //Trangle finished  
		}
		GLfloat light_color[]={0.0, 0.0, 1.0, 1.0};
		GLfloat light_position[]={0.0, 10.0, 0.0, 1.0};
 
 
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color); // set color of diffuse component
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_color); // set color of specular component
 
 
		glLightfv(GL_LIGHT0, GL_POSITION, light_position );   // set position
		float nowTime = Clock.getElapsedTime().asMilliseconds();
		// Finally, display rendered frame on screen 
        App.display(); 
        
	}
}




