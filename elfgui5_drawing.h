#pragma once

#include <pix5.h>
#include "elfgui5.h"


void draw_panel(Texture* tex,int x,int y,int w,int h,bool inverted=false,bool disabled=false);
void draw_panel(Texture* tex,bool inverted=false,bool disabled=false);

void draw_text_align(Texture* tex,Align::Type,int offx,int offy,Font *font,const Color& col,const Str& text,bool kerning=true,BlendMode::Type blend=BlendMode::DestAlpha);

void draw_texture_align(Texture* dest,Align::Type align,int offx,int offy,Texture* src,bool alpha=true);


