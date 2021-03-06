/**
 * This file is part of WebP2P.
 *
 * WebP2P is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WebP2P is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WebP2P.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Filename:    WebP2PAPI.cpp
 * Author(s):   Dries Staelens (partly auto-generated by Firebreath)
 * Copyright:   Copyright (c) 2010 Dries Staelens
 * Description: Implementation of the browser plug-in javascript API.
**/

/* Boost includes */
#include <boost/make_shared.hpp>

/* Firebreath includes */
#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"

/* WebP2P includes */
#include "WebP2PAPI.hpp"
#include "ConnectionPeer.hpp"
#include "RegressionTests.hpp"

WebP2PAPI::WebP2PAPI(WebP2PPtr plugin, FB::BrowserHostPtr host)
	: m_plugin(plugin), m_host(host) {
    registerMethod("createConnectionPeer", 
    	make_method(this, &WebP2PAPI::createConnectionPeer));
    registerMethod("createRegressionTests",
        make_method(this, &WebP2PAPI::createRegressionTests));
}

WebP2PAPI::~WebP2PAPI() {
}

WebP2PPtr WebP2PAPI::getPlugin() {
    WebP2PPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

FB::JSAPIPtr WebP2PAPI::createConnectionPeer(
	const std::string& serverConfiguration) {
    return FB::JSAPIPtr(
    	boost::make_shared<ConnectionPeer>(serverConfiguration));
}

FB::JSAPIPtr WebP2PAPI::createRegressionTests() {
    return FB::JSAPIPtr(
        boost::make_shared<RegressionTests>());
}