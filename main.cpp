/*************************
* Touhou Moon main window function
*
**************************/

#include <SFML/Window.hpp> //Includes all OpenGL functions as well

void glEnable2D()
{
	int vPort[4];

   glGetIntegerv(GL_VIEWPORT, vPort);

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();

   glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
}

void glDisable2D()
{
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
}

int main(int argc, char *argv[])
{
    //Create the main rendering window
    sf::Window window(sf::VideoMode(800, 600, 32), "Touhou Moon");
    //Clock for ensuring constant performance on all platforms
    sf::Clock clock;

    //Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.3, 0.15, 0.2, 0.15);

    //Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    window.SetActive();
    //Main loop, will be wrapped in a class eventually
    while(window.IsOpened())
    {
        sf::Event event;
        //Catch events
        while(window.GetEvent(event))
        {
            if(event.Type == sf::Event::Closed)
                window.Close();

            if((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
                window.Close();
            //Change OpenGL viewport size if window size is changed
            if (event.Type == sf::Event::Resized)
                glViewport(0, 0, event.Size.Width, event.Size.Height);

        }
        //Get the elapsed time since last frame update
        float elapsedTime = clock.GetElapsedTime();
        //Clear the screen each frame before rendering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        glEnable2D();

        glBegin(GL_TRIANGLES);
            glColor4ub(255, 200, 200, 255);
            glVertex2d(300, 200);

            glColor4ub(200, 255, 200, 200);
            glVertex2d(300, 400);

            glColor4ub(100, 100, 100, 100);
            glVertex2d(500, 400);

            glColor4ub(100, 100, 100, 100);
            glVertex2d(500, 200);
        glEnd();

        glDisable2D();

        //Display the results
        window.Display();
    }

    return 0;
}
