// aos4_agg_glue.cpp:  Glue between AmigaOS4 and Anti-Grain Geometry, for Gnash.
//
//   Copyright (C) 2005, 2006, 2007, 2008, 2009 Free Software Foundation, Inc.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

#include "aos4_agg_glue.h"
#include "gnash.h"
#include "log.h"
#undef ACTION_END
#include "render_handler.h"
#include "render_handler_agg.h"
#include <cerrno>
#include <ostream>

using namespace std;

namespace gnash
{

AOS4AggGlue::AOS4AggGlue()
	:
_offscreenbuf(NULL),
_window(NULL),
_screen(NULL),
_agg_renderer(NULL),
_fullscreen(FALSE)
{
//    GNASH_REPORT_FUNCTION;
}

AOS4AggGlue::~AOS4AggGlue()
{
//    GNASH_REPORT_FUNCTION;
    delete [] _offscreenbuf;
	if (_window) 
	{
		IIntuition->CloseWindow(_window);
		_window = NULL;
	}
	
	_screen = NULL;
}

bool
AOS4AggGlue::init(int /*argc*/, char*** /*argv*/)
{
//    GNASH_REPORT_FUNCTION;

    return true;
}


render_handler*
AOS4AggGlue::createRenderHandler(int bpp)
{
//    GNASH_REPORT_FUNCTION;

    _bpp = bpp;

    switch (_bpp) {
      case 32:
        _agg_renderer = create_render_handler_agg("RGBA32");
        _btype        = BLITT_ARGB32;
        _ftype		  = RGBFB_R8G8B8;
        break;
      case 24:
        _agg_renderer = create_render_handler_agg("RGB24");
        _btype        = BLITT_RGB24;
        _ftype 		  = RGBFB_R8G8B8;
        break;
      case 16:
        _agg_renderer = create_render_handler_agg("RGBA16");
        _btype        = BLITT_CHUNKY;
        _ftype		  = RGBFB_R5G6B5;
        break;
      default:
        log_error (_("AGG's bit depth must be 16, 24 or 32 bits, not %d."), _bpp);
        abort();
    }
    return _agg_renderer;
}

render_handler*
AOS4AggGlue::createRenderHandler()
{
//    GNASH_REPORT_FUNCTION;
    _bpp = 24;

    _agg_renderer = create_render_handler_agg("RGB24");
    _btype        = BLITT_RGB24;

    return _agg_renderer;
}

void
AOS4AggGlue::setFullscreen()
{

	saveOrigiginalDimension(_width,_height);

	_screen = IIntuition->LockPubScreen("Workbench");
	int new_width   = _screen->Width;
	int new_height  = _screen->Height;
	IIntuition->UnlockPubScreen(NULL,_screen);
	if (_window) 
		IIntuition->CloseWindow(_window);
	_window = NULL;

    _fullscreen = true;
	
	resize(new_width, new_height);

}

void 
AOS4AggGlue::saveOrigiginalDimension(int width, int height)
{
	_orig_width  = width;
	_orig_height = height;
}

void
AOS4AggGlue::unsetFullscreen()
{
	if (_window) 
		IIntuition->CloseWindow(_window);
	_window = NULL;
	
    _fullscreen = false;

    resize(_orig_width, _orig_height);
}

bool
AOS4AggGlue::prepDrawingArea(int width, int height)
{
    int depth_bytes = _bpp / 8;  // TODO: <Udo> is this correct? Gives 1 for 15 bit modes!

    assert(_bpp % 8 == 0);

	_width = width;
	_height = height;

	if (NULL == _window)
	{
		_window = IIntuition->OpenWindowTags (NULL,
			WA_Activate, 		TRUE,
			WA_InnerWidth,  	width,
			WA_InnerHeight,		height,
			WA_SmartRefresh, 	TRUE,
			WA_RMBTrap, 		FALSE,
			WA_ReportMouse, 	TRUE,
			WA_MaxWidth,		~0,
			WA_MaxHeight,		~0,
			WA_IDCMP, 			IDCMP_MOUSEBUTTONS|
								IDCMP_RAWKEY|
								IDCMP_MOUSEMOVE|
								IDCMP_CLOSEWINDOW|
								IDCMP_NEWSIZE|
								IDCMP_SIZEVERIFY,
			WA_Borderless,		(_fullscreen==false) ? FALSE : TRUE,
			WA_DepthGadget, 	(_fullscreen==false) ? TRUE : FALSE,
			WA_DragBar, 		(_fullscreen==false) ? TRUE : FALSE,
			WA_SizeGadget,		(_fullscreen==false) ? TRUE : FALSE,
			WA_SizeBBottom,		(_fullscreen==false) ? TRUE : FALSE,
			WA_CloseGadget, 	(_fullscreen==false) ? TRUE : FALSE,
			WA_NewLookMenus,    TRUE,
		TAG_DONE);
	}

    if (!_window) 
    {
        log_error (_("prepDrawingArea() failed.\n"));
        exit(1);
    }
	
    _stride = width * depth_bytes;

#define CHUNK_SIZE (100 * 100 * depth_bytes)

    int bufsize = static_cast<int>(width * height * depth_bytes / CHUNK_SIZE + 1) * CHUNK_SIZE;

    _offscreenbuf = new unsigned char[bufsize];
	memset(_offscreenbuf,0x0,bufsize);
	
    log_debug (_("AOS4-AGG: %i byte offscreen buffer allocated"), bufsize);


    // Only the AGG renderer has the function init_buffer, which is *not* part of
    // the renderer api. It allows us to change the renderers movie size (and buffer
    // address) during run-time.
    render_handler_agg_base *renderer = static_cast<render_handler_agg_base *>(_agg_renderer);
    renderer->init_buffer(_offscreenbuf, bufsize, width, height, width*((_bpp+7)/8));

	struct RenderInfo ri;
	ri.Memory 		= _offscreenbuf;
	ri.BytesPerRow  = _stride;
	ri.RGBFormat 	= _ftype;

	if (_window)
		IP96->p96WritePixelArray(&ri,0,0,_window->RPort,_window->BorderLeft,_window->BorderTop,_width,_height);

    _validbounds.setTo(0, 0, width, height);

    return true;
}

struct Window *
AOS4AggGlue::getWindow(void)
{
	return _window;
}

void

AOS4AggGlue::setInvalidatedRegions(const InvalidatedRanges& ranges)
{
    _agg_renderer->set_invalidated_regions(ranges);
    _drawbounds.clear();

    for (unsigned int rno=0; rno<ranges.size(); rno++) 
    {
		// twips changed to pixels here
        geometry::Range2d<int> bounds = Intersection(_agg_renderer->world_to_pixel(ranges.getRange(rno)),_validbounds);

        // it may happen that a particular range is out of the screen, which
        // will lead to bounds==null.
        if (bounds.isNull()) continue;

        _drawbounds.push_back(bounds);
    }
}

void
AOS4AggGlue::render()
{
	if ( _drawbounds.size() == 0 ) return; // nothing to do..

    for (unsigned int bno=0; bno < _drawbounds.size(); bno++) 
	{
		geometry::Range2d<int>& bounds = _drawbounds[bno];
		render(bounds.getMinX(), bounds.getMinY(), bounds.getMaxX(), bounds.getMaxY() );
    }
}

void
AOS4AggGlue::render(int minx, int miny, int maxx, int maxy)
{
	// Update only the invalidated rectangle
	struct RenderInfo ri;
	ri.Memory 		= _offscreenbuf;
	ri.BytesPerRow = _stride;
	ri.RGBFormat 	= _ftype;

	IP96->p96WritePixelArray(&ri,minx , miny, _window->RPort, 
							minx+_window->BorderLeft,
							miny+_window->BorderTop,
							maxx - minx ,
							maxy - miny);

/*
	IGraphics->BltBitMapTags(
					BLITA_Source,			_offscreenbuf,
                    BLITA_SrcType,			_btype,
                    BLITA_SrcBytesPerRow,	_stride,
                    BLITA_Dest,				_window->RPort,
                    BLITA_DestType,			BLITT_RASTPORT,
                    BLITA_DestX,			minx,
                    BLITA_DestY,			miny,
                    BLITA_Width,			maxx,
                    BLITA_Height,			maxy,
                    TAG_END);
*/
}

void
AOS4AggGlue::resize(int width, int height)
{
    GNASH_REPORT_FUNCTION;
    if (!_offscreenbuf) {
      // If initialisation has not taken place yet, we don't want to touch this.
      return;
    }

    delete [] _offscreenbuf;
    prepDrawingArea(width, height);
}

} // namespace gnash