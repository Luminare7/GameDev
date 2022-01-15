#include "raylib.h"   // se metto libraries in <> sto includendo librerie standard, altrimenti devo usare le "" per le librerie esterne. .h indica un header file


int main()
{
    // Dichiaro le dimensioni della finestra
    int width{800};
    int height{450};
    InitWindow(width, height, "Amos' Window!");

    // Dichiaro le coordinate e raggio del cerchio
    int circle_x{50};
    int circle_y{200};
    int circle_radius{25};

    //sponde del cerchio
    int l_circle_x{circle_x - circle_radius};
    int r_circle_x{circle_x + circle_radius};
    int u_circle_y{circle_y - circle_radius};
    int b_circle_y{circle_y + circle_radius};

    //Dichiaro coordinate e dimensioni del rettangolo
    int axe_x{200};
    int axe_y{0};
    int rect_height{50};
    int rect_width{50};

    //sponde dell'axe rettangolare
    int l_axe_x{axe_x};
    int r_axe_x{axe_x + rect_width};
    int u_axe_y{axe_y};
    int b_axe_y{axe_y + rect_height};


    int direction{10};

    SetTargetFPS(60);

    //Creo una variabile per verificare la collisione
    bool collision_with_axe = 
                (b_axe_y >= u_circle_y) && 
                (u_axe_y <= b_circle_y) && 
                (l_axe_x <= r_circle_x) && 
                (r_axe_x >= l_circle_x);

    //apro la finestra di gioco
    while(WindowShouldClose() == false)
    {
    BeginDrawing();
    ClearBackground(WHITE);


        if (collision_with_axe == true)
        {
            DrawText("Game Over!", 400, 200, 20, RED);
        }
        else
        {
            //comincia la logica del gioco

            //aggiorno i bordi delle figure
            l_circle_x = circle_x - circle_radius;
            r_circle_x = circle_x + circle_radius;
            u_circle_y = circle_y - circle_radius;
            b_circle_y = circle_y + circle_radius;
            
            l_axe_x = axe_x;
            r_axe_x = axe_x + rect_width;
            u_axe_y = axe_y;
            b_axe_y = axe_y + rect_height;

            //aggiorno collisione
            collision_with_axe = 
                (b_axe_y >= u_circle_y) && 
                (u_axe_y <= b_circle_y) && 
                (l_axe_x <= r_circle_x) && 
                (r_axe_x >= l_circle_x);


            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            DrawRectangle(axe_x, axe_y, rect_height, rect_width, RED);

            //Muoviamo l'axe (il rettangolino)
            axe_y += direction;
            if (axe_y > height || axe_y < 0)
            {
                direction = -direction;
            }

            if(IsKeyDown(KEY_D) && circle_x < width)
            {
                circle_x += 10;
            }
            if(IsKeyDown(KEY_A) && circle_x > 0)
            {
                circle_x -= 10;
            }
            //finisce la logica di gioco
            
        }

    EndDrawing();
    }
}