//
//   Copyright (C) 2005, 2006, 2007, 2008 Free Software Foundation, Inc.
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

#ifdef HAVE_CONFIG_H
#include "gnashconfig.h"
#endif

#include "Kde4Glue.h"

#include <QImage>
#include <boost/scoped_array.hpp>
#include <QPainter>

class QRect;

namespace gnash
{

class Kde4AggGlue : public Kde4Glue
{
  public:
    Kde4AggGlue();
    ~Kde4AggGlue();
    
    bool init(int argc, char **argv[]);
    void prepDrawingArea(QWidget *drawing_area);
    render_handler* createRenderHandler();
    void initBuffer(int width, int height);
    void resize(int width, int height);
    void render();
    void render(const QRect& updateRect);
    void setInvalidatedRegions(const InvalidatedRanges& ranges);

  private:
    int _width;
    int _height;
    boost::scoped_array<unsigned char> _offscreenbuf;
    render_handler* _renderer; // We don't own this pointer.
    geometry::Range2d<int> _validbounds;
    std::vector< geometry::Range2d<int> > _drawbounds;
    std::auto_ptr<QImage> _image;
    std::auto_ptr<QPainter> _painter;
};




}
