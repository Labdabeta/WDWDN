/*******************************************************************************
 * @file gui.h
 * @author Louis Burke
 * @date 2014-01-26
 * @version 1.0
 *
 * @brief File containing a simple GUI API for use in WDWDN.
 *
 * This file defines a number of functions and datatypes for implementing a 
 * simple game using SDL. It is specifically tailored for use in the game 
 * Warp Do We Do Now? by ???
*******************************************************************************/

#ifndef WDWDN_GUI_H
#define WDWDN_GUI_H 1.0 //Version
 
typedef void *Sprite;/**< An opaque storage class for an image. */

/*******************************************************************************
 * @brief Loads a sprite from a file.
 *
 * This function loads the image at the relative file name indicated by @p
 * fileName. Internally, the SDL_Image library is used. Therefore the supported
 * filetypes are the same as in SDL_Image (@see 
 * https://www.libsdl.org/projects/SDL_image/ ). This function acts as the 
 * constructor for the Sprite type.
 *
 * @param fileName The name of the file to load.
 * @return The loaded sprite or NULL if unsuccessful.
*******************************************************************************/
Sprite loadSprite(const char *fileName);

/*******************************************************************************
 * @brief Cleans all resources loaded in a Sprite.
 *
 * This function de-allocates all resources (memory, files, etc.) held by the 
 * sprite indicated by @p spr. It acts as the destructor for the Sprite type.
 *
 * @param spr The sprite resource to clean.
*******************************************************************************/
void cleanSprite(Sprite spr);

/*******************************************************************************
 * @brief Draws the specified sprite to the screen.
 *
 * This function draws the sprite indicated by @p spr at the location specified
 * by the @p x and @p y coordinates. These coordinates represent the top-left
 * corner of where the sprite will be drawn. They are given in reflected
 * cartesian fashion (@see http://math.stackexchange.com/questions/284031/ ).
 *
 * @param spr The sprite to draw.
 * @param x The x coordinate of the left of the drawing area.
 * @param y The y coordinate of the top of the drawing area.
*******************************************************************************/
void drawSprite(Sprite spr, int x, int y);

/*******************************************************************************
 * @brief A structure to hold information about the state of the input.
 *
 * This structure holds the state of various facets of the input. In particular
 * it holds the location of the mouse, the state of the keyboard buttons and
 * the state of the mouse buttons. It is passed to most of the callback 
 * functions used in this event-driven API.
*******************************************************************************/
typedef struct InputStateTAG {
    int mx; /**< The x coordinate of the mouse. */
    int my; /**< The y coordinate of the mouse. */
    int ml; /**< True if the left mouse button is pressed. */
    int mr; /**< True if the right mouse button is pressed. */
    int keys[256]; /**< Each value is true if that key is pressed. */
}InputState,*InputStateHANDLE;

/*******************************************************************************
 * @brief A structure to hold callback functions to hook into each input event.
 *
 * This structure holds a number of function pointers that will be called at 
 * certain points in the event loop. See the description of each field for more
 * information on when it will be called.
*******************************************************************************/
typedef struct EventCallbacksTAG {
    /** Called before the event loop begins, but after SDL initializes. */
    void (*load)(); 
    /** Called after clearing the screen each frame. */
    void (*draw)(const InputStateHANDLE);
    /** Called before any events are handled or the screen is drawn. */
    int (*step)(const InputStateHANDLE);
    /** Called when a keydown event is received. */
    void (*onKeyDown)(int,const InputStateHANDLE);
    /** Called when a keyup event is received. */
    void (*onKeyUp)(int,const InputStateHANDLE);
    /** Called after step returns false. */
    void (*onQuit)();
}EventCallbacks,*EventCallbacksHANDLE;

/*******************************************************************************
 * @brief Runs the game, calling the specified callbacks until step returns 0.
 *
 * This function initializes sdl, then calls the provided load function, then
 * calls the provided step function until it returns 0, then calls the provided
 * onQuit function. Meanwhile it updates the screen with calls to draw and 
 * forwards events through the onKeyUp and onKeyDown callbacks. All of these
 * functions are provided to it through the @p callbacks parameter. Additional
 * information about the window is also provided.
 *
 * @param callbacks The callback functions to hook into.
 * @param width The width of the SDL window.
 * @param height The height of the SDL window.
 * @param fps The framerate of the SDL window.
 * @param title The title of the SDL window.
*******************************************************************************/
void RunGame(EventCallbacks *callbacks,int width,
                                       int height,
                                       int fps,
                                       const char *title);
#endif 
