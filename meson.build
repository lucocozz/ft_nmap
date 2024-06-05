project(
	'ft_nmap', ['c'],
	version: '0.1',
	default_options: [
		'warning_level=3',
		'werror=true',
		'debug=true',
	],
	subproject_dir: 'libs',
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


rbtree_dep = subproject('rbtree', required: true).get_variable('rbtree_dep')
toolbox_dep = subproject('toolbox', required: true).get_variable('toolbox_dep')
nessy_dep = subproject('nessy', required: true).get_variable('nessy_dep')


deps = [
	rbtree_dep,
	toolbox_dep,
	nessy_dep,
]

# subdir('libs')
subdir('sources')

executable(
	meson.project_name(),
	sources,
	dependencies: deps,
	include_directories: include_directories('includes'),
)
