#pragma once

#include <pix5.h>
#include "elfgui5.h"


void draw_panel(Texture* tex,int x,int y,int w,int h,bool inverted=false,bool disabled=false);
void draw_panel(Texture* tex,bool inverted=false,bool disabled=false);

void draw_text_align(Texture* tex,int align,int offx,int offy,Font *font,const Color& col,const Str& text,BlendMode::Type blend = BlendMode::DestAlpha);


