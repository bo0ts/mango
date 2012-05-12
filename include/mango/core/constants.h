/*
 Copyright (c) 2011, 2012 Amos Joshua
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/
#include "mango_opengl.h"

#ifndef MANGO_CONSTANTS
#define MANGO_CONSTANTS

// General Constants

#define ENGINE_MAX_EVENT_TYPES 8
#define ENGINE_INIT_EVENTS_STACK 256



// Event Constants
// Event constant flags, should be powers of two
#define PRE_STEP 4
#define STEP 8
#define POST_STEP 16
#define RENDER 1
#define DRAW 2
#define INPUT 32

#define ALL_EVENTS  PRE_STEP | STEP | POST_STEP | RENDER | DRAW | INPUT

// Event constant types, should be increasing sequence starting with 1
#define EVT_TYPE_RENDER 0
#define EVT_TYPE_DRAW 1
#define EVT_TYPE_PRE_STEP 2
#define EVT_TYPE_STEP 3
#define EVT_TYPE_POST_STEP 4
#define EVT_TYPE_INPUT 5
#define EVT_TYPE_MOUSE_MOVE 6




// Camera Constants
#define CAMERA_DEFAULT_MODE 0
#define LOCK_PAN 1
#define LOCK_DISTANCE 2
#define LOCK_ALPHA 4
#define LOCK_BETA 8
#define LOCK_GAMMA 16
#define FOCUS_FIXED 32
#define RMB_CYLINDRICAL_ROTATE 256
#define LMB_DRAG_FOCUS 512
#define ZOOM_SCALES 1024

#define LOCK_POSITION LOCK_DISTANCE | LOCK_ALPHA | LOCK_BETA | LOCK_GAMMA
#define LOCK_ALL LOCK_POSITION | LOCK_PAN


// Style Constants
#define WIRE GL_LINE_STRIP
#define WIRE_LOOP GL_LINE_LOOP
#define FILL GL_POLYGON









// Input Constants
// Note: a keyboard has keys, a mouse has buttons
#define MAX_KEYCODE_INDEX 400
#define TYPED_KEY_BUFFER_LENGTH 16
#define INPUT_EVENT_BUFFER_SIZE 32

#define ANY -1
#define KEYBOARD 1
#define MOUSE 2

#define PRESS 1
#define RELEASE 2
#define CLICK PRESS
#define DOUBLE_CLICK 3

#define KEY_STATE_UP       1
#define KEY_STATE_DOWN     2

#define BUTTON_STATE_UP    KEY_STATE_UP
#define BUTTON_STATE_DOWN  KEY_STATE_DOWN

#define BUTTON_LEFT   0
#define BUTTON_MIDDLE 1
#define BUTTON_RIGHT  2

#define KEY_BACKSPACE 8
#define KEY_TAB      9
#define KEY_ENTER    13
#define KEY_RETURN   13
#define KEY_ESCAPE   27
#define KEY_SPACE    32
#define KEY_DELETE   127

#define KEY_START    300
#define KEY_LBUTTON  301
#define KEY_RBUTTON  302
#define KEY_CANCEL   303
#define KEY_MBUTTON  304
#define KEY_CLEAR    305
#define KEY_SHIFT    306
#define KEY_ALT      307
#define KEY_CONTROL  308
#define KEY_MENU     309
#define KEY_PAUSE    310
#define KEY_CAPITAL  311
#define KEY_END      312
#define KEY_HOME     313
#define KEY_LEFT     314
#define KEY_UP       315
#define KEY_RIGHT    316
#define KEY_DOWN     317
#define KEY_SELECT   318
#define KEY_PRINT    319
#define KEY_EXECUTE  320
#define KEY_SNAPSHOT 321
#define KEY_INSERT   322
#define KEY_HELP     323
#define KEY_NUMPAD0  324
#define KEY_NUMPAD1  325
#define KEY_NUMPAD2  326
#define KEY_NUMPAD3  327
#define KEY_NUMPAD4  328
#define KEY_NUMPAD5  329
#define KEY_NUMPAD6  330
#define KEY_NUMPAD7  331
#define KEY_NUMPAD8  332
#define KEY_NUMPAD9  333
#define KEY_MULTIPLY 334
#define KEY_ADD      335
#define KEY_SEPARATOR 336
#define KEY_SUBTRACT 337
#define KEY_DECIMAL  338
#define KEY_DIVIDE   339
#define KEY_F1       340
#define KEY_F2       341
#define KEY_F3       342
#define KEY_F4       343
#define KEY_F5       344
#define KEY_F6       345
#define KEY_F7       346
#define KEY_F8       347
#define KEY_F9       348
#define KEY_F10      349
#define KEY_F11      350
#define KEY_F12      351
#define KEY_F13      352
#define KEY_F14      353
#define KEY_F15      354
#define KEY_F16      355
#define KEY_F17      356
#define KEY_F18      357
#define KEY_F19      358
#define KEY_F20      359
#define KEY_F21      360
#define KEY_F22      361
#define KEY_F23      362
#define KEY_F24      363
#define KEY_NUMLOCK  364
#define KEY_SCROLL   365
#define KEY_PAGEUP   366
#define KEY_PAGEDOWN 367

#define KEY_NUMPAD_SPACE     368
#define KEY_NUMPAD_TAB       369
#define KEY_NUMPAD_ENTER     370
#define KEY_NUMPAD_F1        371
#define KEY_NUMPAD_F2        372
#define KEY_NUMPAD_F3        373
#define KEY_NUMPAD_F4        374
#define KEY_NUMPAD_HOME      375
#define KEY_NUMPAD_LEFT      376
#define KEY_NUMPAD_UP        377
#define KEY_NUMPAD_RIGHT     378
#define KEY_NUMPAD_DOWN      379
#define KEY_NUMPAD_PAGEUP    380
#define KEY_NUMPAD_PAGEDOWN  381
#define KEY_NUMPAD_END       382
#define KEY_NUMPAD_BEGIN     383
#define KEY_NUMPAD_INSERT    384
#define KEY_NUMPAD_DELETE    385
#define KEY_NUMPAD_EQUAL     386
#define KEY_NUMPAD_MULTIPLY  387
#define KEY_NUMPAD_ADD       388
#define KEY_NUMPAD_SEPARATOR 389
#define KEY_NUMPAD_SUBTRACT  390
#define KEY_NUMPAD_DECIMAL   391
#define KEY_NUMPAD_DIVIDE    392

#define KEY_WINDOWS_LEFT     393
#define KEY_WINDOWS_RIGHT    394
#define KEY_WINDOWS_MENU     395



// Conversion table for special characters in GLUT:
//    KEY      CODE
//     F1        1
//     F2        2
//     F3        3
//     F4        4
//     F5        5
//     F6        6
//     F7        7
//     F8        8
//     F9        9
//     F10       10
//     F11       11
//     F12       12
//
//     up        101
//     left      100
//     right     102
//     down      103
//
//     pgup      104
//     pgdwn     105
//     end       107
//     home      106
//     insert    108

#endif // MANGO_CONSTANTS
