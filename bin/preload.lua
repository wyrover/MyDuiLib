
package.path = './?.lua;' .. package.path

_G.Lplus = require "Lplus"

_G.theApp = nil

local App = require "app"
theApp = App()