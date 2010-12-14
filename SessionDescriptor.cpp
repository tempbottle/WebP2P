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
 * Filename:    SessionDescriptor.cpp
 * Author(s):   Dries Staelens
 * Copyright:   Copyright (c) 2010 Dries Staelens
 * Description: Implementation of the SessionDescriptor class which implements
 *              a generic SDP message.
 * See also:    http://tools.ietf.org/html/rfc4566
**/

/* WebP2P includes */
#include "SessionDescriptor.hpp"
#include "SessionDescriptorGrammar.hpp"

SessionDescriptor::SessionDescriptor() {
}

SessionDescriptor::SessionDescriptor(const std::string& sdpString)
    throw(std::exception) {
    using namespace std;
    using namespace boost::spirit::qi;

    string::const_iterator begin = sdpString.begin();
    string::const_iterator end   = sdpString.end();
    SessionDescriptorGrammar sdpGrammar;
    bool success;
    
    std::cout << "Attempting to parse the following SDP string:\n"
              << sdpString;

    try {
        success = phrase_parse(begin, end, sdpGrammar, !byte_);
    } catch (std::exception ex) {
        std::cout << "Parse exception: " << ex.what() << "\n";
    }
    bool fullMatch = (begin == end);

    if(fullMatch) {
        std::cout << "Full match found!\n";
    }
    else if(success) { 
        std::cout << "Partial match found!\n";
    }
    else {
        std::cout << "No match found!\n";
    }
}

SessionDescriptor::~SessionDescriptor() {
}

SessionDescriptor::operator std::string() {
    return std::string("");
}