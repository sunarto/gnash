desktopdir = $(datadir)/applications
desktop_DATA =

icons32dir = $(datadir)/icons/hicolor/32x32/apps
icons32_DATA =

splashdir = $(pkgdatadir)
splash_DATA = gnash-splash.swf

bin_SCRIPTS =

EXTRA_DIST = gnash-splash.swf \
             gnash.desktop \
             klash.desktop \
             gnash-gtk-launcher.in \
             gnash-qt-launcher.in

if BUILD_GTK_GUI
desktop_DATA += gnash.desktop
icons32_DATA += ../packaging/gnash.xpm
bin_SCRIPTS  += gnash-gtk-launcher
endif

if BUILD_QT4_GUI
desktop_DATA += klash.desktop
icons32_DATA += ../packaging/klash.xpm
bin_SCRIPTS  += gnash-qt-launcher
endif

validate-gnash-desktop: gnash.desktop
	( dfvalidate=`which desktop-file-validate`; \
	  if test x$$dfvalidate != x && test -x $$dfvalidate; then \
              $$dfvalidate $< || ( echo "* $< INVALID *"; exit 1 ) \
	  else \
	      echo "Can't find desktop-file-validate to validate $<; proceed with fingers crossed..."; \
          fi )

validate-klash-desktop: klash.desktop
	( dfvalidate=`which desktop-file-validate`; \
	  if test x$$dfvalidate != x && test -x $$dfvalidate; then \
              $$dfvalidate $< || ( echo "* $< INVALID *"; exit 1 ) \
	  else \
	      echo "Can't find desktop-file-validate to validate $<; proceed with fingers crossed..."; \
          fi )

install-data-hook: validate-gnash-desktop validate-klash-desktop
