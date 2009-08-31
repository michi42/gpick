#!/usr/bin/env python
v.Update(env)

tools.gpick.GetVersionInfo(env)

try:
	umask = os.umask(022)
except OSError:     # ignore on systems that don't support umask
	pass

def CheckPKG(context, name):
	context.Message( 'Checking for %s... ' % name )
	ret = context.TryAction('pkg-config --exists "%s"' % name)[0]
	context.Result( ret )
	return ret

if not env.GetOption('clean'):
	conf = Configure(env, custom_tests = { 'CheckPKG' : CheckPKG })

	tools.gpick.ConfirmLibs(conf, env, {
		'GTK_PC': 		{'checks':{'gtk+-2.0':'>= 2.12.0'}},
		'LUA_PC': 		{'checks':{'lua':'>= 5.1', 'lua5.1':'>= 5.1'}},
		'UNIQUE_PC': 		{'checks':{'unique-1.0':'>= 1.0.8'}},
		})
	
	env = conf.Finish()


Decider('MD5-timestamp')

env.Replace(
	SHCCCOMSTR = "Compiling ==> $TARGET",
	SHCXXCOMSTR = "Compiling ==> $TARGET",
	CCCOMSTR = "Compiling ==> $TARGET",
	CXXCOMSTR = "Compiling ==> $TARGET",
	SHLINKCOMSTR = "Linking shared ==> $TARGET",
	LINKCOMSTR = "Linking ==> $TARGET",
	LDMODULECOMSTR = "Linking module ==> $TARGET",
	ARCOMSTR = "Linking static ==> $TARGET",
	TARCOMSTR = "Archiving ==> $TARGET"
	)

env.Append(LINKFLAGS=['-s'])

executable = SConscript(['source/SConscript'], exports='env')

env.Alias(target="build", source=[
	executable
])

if 'debian' in COMMAND_LINE_TARGETS:
	SConscript("deb/SConscript", exports='env')

env.Alias(target="install", source=[
	env.InstallProgram(dir=env['DESTDIR'] +'/bin', source=[executable]),
	env.InstallData(dir=env['DESTDIR'] +'/share/applications', source=['share/applications/gpick.desktop']),
	env.InstallData(dir=env['DESTDIR'] +'/share/doc/gpick', source=['share/doc/gpick/copyright']),
	env.InstallData(dir=env['DESTDIR'] +'/share/gpick', source=[env.Glob('share/gpick/*.png'), env.Glob('share/gpick/*.lua'), env.Glob('share/gpick/*.txt')]),
	env.InstallData(dir=env['DESTDIR'] +'/share/man/man1', source=['share/man/man1/gpick.1']),
	env.InstallData(dir=env['DESTDIR'] +'/share/icons/hicolor/48x48/apps/', source=[env.Glob('share/icons/hicolor/48x48/apps/*.png')]),
	env.InstallData(dir=env['DESTDIR'] +'/share/icons/hicolor/scalable/apps/', source=[env.Glob('share/icons/hicolor/scalable/apps/*.svg')]),
])

env.Alias(target="nsis", source=[
	env.WriteNsisVersion("version.py")
])

env.Alias(target="tar", source=[
	env.Append(TARFLAGS = ['-z']),
	env.Prepend(TARFLAGS = ['--transform', '"s,^,gpick-'+str(env['GPICK_BUILD_VERSION'])+'.'+str(env['GPICK_BUILD_REVISION'])+'/,"']),
	env.Tar('gpick_'+str(env['GPICK_BUILD_VERSION'])+'.'+str(env['GPICK_BUILD_REVISION'])+'.tar.gz', tools.gpick.GetSourceFiles(env, "("+tools.gpick.RegexEscape(os.sep)+r"\.)|("+tools.gpick.RegexEscape(os.sep)+r"\.svn$)|(^"+tools.gpick.RegexEscape(os.sep)+r"build$)", r"(^\.)|(\.pyc$)|(~$)|(\.log$)|(^gpick-.*\.tar\.gz$)"))
])



env.Default(executable)
