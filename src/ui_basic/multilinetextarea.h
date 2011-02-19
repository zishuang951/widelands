/*
 * Copyright (C) 2002, 2006-2009, 2011 by the Widelands Development Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef UI_MULTILINE_TEXTAREA_H
#define UI_MULTILINE_TEXTAREA_H

#include "align.h"
#include "panel.h"
#include "scrollbar.h"

#include <boost/scoped_ptr.hpp>

namespace UI {
struct Scrollbar;

/**
 * This defines an area, where a text can easily be printed.
 * The textarea transparently handles explicit line-breaks and word wrapping.
 */
struct Multiline_Textarea : public Panel {
	enum ScrollMode {
		ScrollNormal = 0, ///< (default) only explicit or forced scrolling
		ScrollLog = 1,    ///< follow the bottom of the text
	};

	Multiline_Textarea
		(Panel * const parent,
		 const int32_t x, const int32_t y, const uint32_t w, const uint32_t h,
		 const std::string & text         = std::string(),
		 const Align                      = Align_Left,
		 const bool always_show_scrollbar = false);
	~Multiline_Textarea();

	std::string const & get_text() const {return m_text;}
	ScrollMode get_scrollmode() const {return m_scrollmode;}

	void set_text(std::string const &);
	void set_align(Align);
	void set_scrollmode(ScrollMode mode);

	void set_font(std::string name, int32_t size, RGBColor fg);

	uint32_t scrollbar_w() const throw () {return 24;}
	uint32_t get_eff_w() const throw () {return get_w() - scrollbar_w();}

	void set_color(RGBColor fg) {m_fcolor = fg;}
	void set_bg_color(RGBColor bgc) {m_bg_color = bgc;} // TODO deprecated

	// Drawing and event handlers
	void draw(RenderTarget &);

	bool handle_mousepress  (Uint8 btn, int32_t x, int32_t y);

	const char *  get_font_name() {return m_fontname.c_str();} //TODO deprecate these?
	int32_t       get_font_size() {return m_fontsize;}
	RGBColor &    get_font_clr () {return m_fcolor;}

private:
	struct Impl;

	boost::scoped_ptr<Impl> m;

	void recompute();
	void scrollpos_changed(int32_t pixels);

	std::string m_text;
	Scrollbar   m_scrollbar;
	ScrollMode  m_scrollmode;

protected:
	virtual void layout();

	Align        m_align;
	std::string  m_fontname;
	int32_t  m_fontsize;
	RGBColor m_fcolor;
	RGBColor m_bg_color;    //TODO deprecated

	int32_t get_halign(); // TODO deprecated?
};

}

#endif
