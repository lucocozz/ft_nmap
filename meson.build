project(
	'ft_nmap', ['c'],
	default_options: [
		'warning_level=3',
		'werror=true',
	]
)


cflags = [
	'-lpcap',
	'-lpthread',
]

cc = meson.get_compiler('c')

foreach cflag : cflags
	if cc.has_argument(cflag)
		add_project_arguments(cflag, language: 'c')
	endif
endforeach

subdir('sources')

executable(
	meson.project_name(),
	sources,
	include_directories: include_directories('includes'),
)
