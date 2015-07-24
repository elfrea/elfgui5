#pragma once

#include <pix5.h>
#include "elfgui5.h"


void draw_panel(Texture* tex,int x,int y,int w,int h,bool inverted,bool disabled,const Color& clight,const Color& cmedium,const Color& cdark,const Color& cdlight,const Color& cdmedium,const Color& cddark);
void draw_panel(Texture* tex,bool inverted=false,bool disabled=false,int x=0,int y=0,int w=0,int h=0);
void draw_edit_panel(Texture* tex,bool disabled=false,int x=0,int y=0,int w=0,int h=0);

void draw_text_align(Texture* tex,Align::Type,int offx,int offy,Font *font,const Color& col,const Str& text,bool kerning=true,BlendMode::Type blend=BlendMode::DestAlpha);

void draw_texture_align(Texture* dest,Align::Type align,int offx,int offy,Texture* src,bool alpha=true);


