
top = "."
out = "build"

VERSION = "0.0.1"
APPNAME = "XARC"

def options(ctx):
	ctx.add_option("--release",
	               action="store_false",
	               default=True,
	               help="Release build (disable debug)"
	               dest="debug")

def configure(ctx):
	conf.load("compiler_c")
	conf.check_cfg(atleast_pkgconfig_version="0.0.0")

	conf.check_cfg(package="glib-2.0", uselib_store="GLIB",
	               args=["--cflags","--libs"])
	


def build(ctx):
	bld.objects(source="
