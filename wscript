#! /usr/bin/env python
# encoding: utf-8
# James Goppert 

VERSION = '0.0.0'
APPNAME = 'autopilotone'
SO_VERSION = '0.0.0'

top = '.'
out = 'build'

def options(opt):
    opt.load('compiler_cxx')

def configure(conf):
    conf.load('compiler_cxx')
    conf.check(header_name='stdio.h', features='cxx cxxprogram', mandatory=False)

def build(bld):
    #bld.shlib(source='a.cpp', target='mylib', vnum=SO_VERSION)
    #bld.stlib(target='foo', source='b.cpp')
    bld(name='common_includes',export_includes='src')
    bld.program(source='test/linux.cpp',target='linux.test',use='common_includes')

# vim:expandtab:ts=4:sw=4
