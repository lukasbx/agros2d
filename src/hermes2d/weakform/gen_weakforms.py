#!/usr/bin/python

from xml_parser import XmlParser

modules = ['electrostatic', 'current', 'heat', 'acoustic']
xml_parser = XmlParser(modules)
xml_parser.process()